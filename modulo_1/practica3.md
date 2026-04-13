# Práctica 3 — Simulador de Sensor en Software

### **Asignatura:** Programación de Sistemas Embebidos
### **Módulo:** 1 — Hardware programable
### **Lenguaje:** C++20
### **Entregable:** Código fuente + salida del programa + respuestas a preguntas

---

## 1. Objetivo

Implementar un **sensor simulado por software** que genere lecturas de temperatura con ruido realista, empaquete los datos en un registro de 32 bits y produzca estadísticas básicas.

---

## 2. Contexto

En el desarrollo embebido real, los sensores físicos no siempre están disponibles desde el inicio.  
Antes de tener hardware, los ingenieros crean **sensores simulados** para:

- Probar la lógica del sistema sin hardware
- Reproducir condiciones específicas (valores extremos, errores)
- Automatizar pruebas

Esta práctica construye ese simulador paso a paso.

---

## 3. Registro de salida

El simulador debe producir lecturas empaquetadas en el mismo formato de 32 bits de la Práctica 1:

| Bits    | Campo                   |
|---------|-------------------------|
| 0 – 11  | Valor del sensor (ADC)  |
| 12      | Estado del sistema      |
| 13      | Error                   |
| 14 – 15 | Modo                    |
| 16 – 23 | Temperatura (con signo) |
| 24 – 31 | Checksum                |

En la Práctica 1 **leímos** este registro. Aquí lo vamos a **construir**.

---

## 4. Cabeceras necesarias

```cpp
#include <iostream>
#include <cstdint>
#include <bitset>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
```

### ¿Qué hay de nuevo?

- `<random>` — generadores de números aleatorios de C++11 en adelante
- `<cmath>` — funciones matemáticas (`std::round`, `std::abs`)
- `<algorithm>` — algoritmos de la STL (`std::min_element`, `std::max_element`)

---

## 5. Parte 1 — Sensor constante

El sensor más simple posible devuelve siempre el mismo valor.

```cpp
std::int8_t leer_temperatura_constante() {
    return 25;  // °C fija
}
```

### ¿Qué tipo usamos y por qué?

- `std::int8_t` → 8 bits **con signo**
- Rango: –128 a +127
- Suficiente para temperaturas ambiente
- Coincide con el campo de bits 16–23 del registro

### Tarea

Agrega una función `main` que llame a esta función 5 veces e imprima los resultados.  
Observa que siempre devuelve 25.

---

## 6. Parte 2 — Agregar ruido

Un sensor real no devuelve exactamente el mismo valor cada vez.  
Tiene **ruido**: pequeñas variaciones aleatorias.

```cpp
std::int8_t leer_temperatura(std::mt19937& gen, double base_temp) {
    std::normal_distribution<double> ruido(0.0, 1.5);
    double lectura = base_temp + ruido(gen);
    return static_cast<std::int8_t>(std::round(lectura));
}
```

### Explicación línea por línea

#### `std::mt19937& gen`

- `mt19937` es el generador **Mersenne Twister**
- Es pseudoaleatorio: dado el mismo punto de inicio (*seed*), siempre produce la misma secuencia
- Se pasa por referencia para no crear uno nuevo en cada llamada

#### `std::normal_distribution<double> ruido(0.0, 1.5)`

- Genera números con **distribución normal (gaussiana)**
- Media = 0.0 → el ruido está centrado en cero
- Desviación estándar = 1.5 → la mayoría de los valores caen entre –3 y +3

#### `ruido(gen)`

- Genera un número aleatorio con esa distribución
- Se suma a `base_temp`

#### `static_cast<std::int8_t>(std::round(lectura))`

- `round` redondea al entero más cercano
- `static_cast` convierte el `double` a `int8_t`
- Sin `round`, la conversión trunca (se pierde información)

---

### Código para inicializar el generador

```cpp
std::random_device rd;
std::mt19937 gen(rd());
```

- `random_device` obtiene entropía del sistema operativo
- Se usa solo para obtener la *seed*
- `mt19937` hace el trabajo real

### Tarea

Modifica `main` para usar `leer_temperatura` con `base_temp = 22.0`.  
Genera 10 lecturas. ¿Todas son iguales? ¿Cuánto varían?

---

## 7. Parte 3 — Empaquetar en un registro

Ahora construimos el registro de 32 bits.

```cpp
std::uint32_t empaquetar_registro(
    std::uint16_t adc_value,
    bool          estado,
    bool          error,
    std::uint8_t  modo,
    std::int8_t   temperatura
) {
    std::uint32_t reg = 0;

    // Bits 0–11: valor ADC
    reg |= (adc_value & 0xFFF);

    // Bit 12: estado
    reg |= (static_cast<std::uint32_t>(estado) << 12);

    // Bit 13: error
    reg |= (static_cast<std::uint32_t>(error) << 13);

    // Bits 14–15: modo
    reg |= (static_cast<std::uint32_t>(modo & 0b11) << 14);

    // Bits 16–23: temperatura
    reg |= (static_cast<std::uint32_t>(
                static_cast<std::uint8_t>(temperatura)
            ) << 16);

    // Bits 24–31: checksum simple
    std::uint8_t checksum = (adc_value ^ static_cast<std::uint8_t>(temperatura)) & 0xFF;
    reg |= (static_cast<std::uint32_t>(checksum) << 24);

    return reg;
}
```

### Explicación de cada campo

#### Bits 0–11: `reg |= (adc_value & 0xFFF)`

- `& 0xFFF` garantiza que no usamos más de 12 bits
- `|=` coloca los bits en el registro sin afectar el resto

#### Bit 12 y 13: desplazamiento de un `bool`

- `static_cast<std::uint32_t>(estado)` convierte `true/false` a `1/0`
- `<< 12` lo coloca en la posición correcta

#### Bits 14–15: modo con máscara

- `modo & 0b11` garantiza que el modo es 0, 1, 2 o 3 (máximo 2 bits)
- `<< 14` lo coloca en posición

#### Bits 16–23: temperatura con signo

- `static_cast<std::uint8_t>(temperatura)` reinterpreta el `int8_t` como patrón de bits sin signo
- Esto preserva la representación en complemento a dos
- `<< 16` lo coloca en posición

#### Bits 24–31: checksum

- XOR entre el byte bajo del ADC y la temperatura
- Técnica simple para detectar corrupción de datos

---

### Tarea

Llama a `empaquetar_registro` con:

```cpp
adc_value = 1234
estado    = true
error     = false
modo      = 2
```

Y la temperatura obtenida de `leer_temperatura`.

Imprime el resultado con `std::bitset<32>` y verifica visualmente que los campos están en el lugar correcto.

---

## 8. Parte 4 — Verificación cruzada

Ahora usa el código de la **Práctica 1** para desempaquetar el registro que acabas de construir y verifica que los valores coincidan.

```cpp
void desempaquetar_y_mostrar(std::uint32_t reg) {
    std::uint16_t adc    = reg & 0xFFF;
    bool          estado = (reg >> 12) & 1;
    bool          error  = (reg >> 13) & 1;
    std::uint8_t  modo   = (reg >> 14) & 0b11;
    std::int8_t   temp   = static_cast<std::int8_t>((reg >> 16) & 0xFF);
    std::uint8_t  check  = (reg >> 24) & 0xFF;

    std::cout << "ADC:   " << adc << "\n";
    std::cout << "Estado: " << (estado ? "ON" : "OFF") << "\n";
    std::cout << "Error: " << (error ? "SI" : "NO") << "\n";
    std::cout << "Modo:  " << static_cast<int>(modo) << "\n";
    std::cout << "Temp:  " << static_cast<int>(temp) << " C\n";
    std::cout << "Check: " << static_cast<int>(check) << "\n";
}
```

### Tarea

Llama a `desempaquetar_y_mostrar` con el registro que generaste en la Parte 3.  
¿Coinciden los valores originales con los recuperados?

---

## 9. Parte 5 — Historial de lecturas

Genera múltiples lecturas y guárdalas en un `std::vector`.

```cpp
std::vector<std::int8_t> generar_historial(
    std::mt19937& gen,
    double        base_temp,
    int           n
) {
    std::vector<std::int8_t> historial;
    historial.reserve(n);

    for (int i = 0; i < n; ++i) {
        historial.push_back(leer_temperatura(gen, base_temp));
    }

    return historial;
}
```

### Nota sobre `reserve`

- `reserve(n)` reserva espacio para `n` elementos
- No los crea, solo evita realocaciones internas
- Buena práctica cuando se conoce el tamaño de antemano

---

## 10. Parte 6 — Estadísticas

```cpp
void mostrar_estadisticas(const std::vector<std::int8_t>& datos) {
    if (datos.empty()) return;

    auto min_it = std::min_element(datos.begin(), datos.end());
    auto max_it = std::max_element(datos.begin(), datos.end());

    double suma = 0;
    for (auto v : datos) suma += v;
    double promedio = suma / static_cast<double>(datos.size());

    std::cout << "Lecturas: " << datos.size() << "\n";
    std::cout << "Mínimo:   " << static_cast<int>(*min_it) << " C\n";
    std::cout << "Máximo:   " << static_cast<int>(*max_it) << " C\n";
    std::cout << "Promedio: " << promedio << " C\n";
}
```

### Explicación

#### `std::min_element` / `std::max_element`

- Reciben iteradores de inicio y fin
- Devuelven un **iterador** al elemento mínimo/máximo
- Se desreferencia con `*` para obtener el valor

#### `static_cast<double>(datos.size())`

- `size()` devuelve `size_t` (entero sin signo)
- La división entre `double` y `size_t` puede causar comportamiento inesperado
- El cast explícito comunica la intención

---

### Tarea

Genera un historial de 50 lecturas con `base_temp = 22.0` y muestra las estadísticas.  
Luego genera otro con `base_temp = –5.0` y compara.

---

## 11. Integración final

Integra todas las partes en `main`:

```cpp
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    const double BASE_TEMP = 22.0;
    const int    N         = 20;

    std::cout << "=== Sensor Simulado ===\n\n";

    auto historial = generar_historial(gen, BASE_TEMP, N);
    mostrar_estadisticas(historial);

    std::cout << "\n=== Registros empaquetados ===\n";

    for (int i = 0; i < 5; ++i) {
        std::int8_t temp = leer_temperatura(gen, BASE_TEMP);
        std::uint32_t reg = empaquetar_registro(1024, true, false, 1, temp);

        std::cout << "\nLectura " << i + 1 << ":\n";
        std::cout << std::bitset<32>(reg) << "\n";
        desempaquetar_y_mostrar(reg);
    }

    return 0;
}
```

---

## 12. Salida esperada

```
=== Sensor Simulado ===

Lecturas: 20
Mínimo:   19 C
Máximo:   25 C
Promedio: 22.3 C

=== Registros empaquetados ===

Lectura 1:
01101101000000010000010000000000
ADC:   1024
Estado: ON
Error: NO
Modo:  1
Temp:  22 C
Check: 109
...
```

Los valores exactos variarán en cada ejecución.

---

## 13. Compilación

```bash
g++ -std=c++20 -o sensor sensor.cpp && ./sensor
```

---

## 14. Preguntas de reflexión

1. ¿Por qué se usa `std::int8_t` en lugar de `int` para la temperatura?

2. ¿Qué pasaría si usáramos `static_cast<int>(temperatura)` en lugar de `static_cast<std::uint8_t>(temperatura)` al empaquetar? ¿Seguiría funcionando para temperaturas negativas?

3. ¿Qué ventaja tiene `std::normal_distribution` sobre `rand() % N` para simular ruido de sensor?

4. En un microcontrolador sin sistema operativo, `std::random_device` puede no funcionar. ¿Qué alternativa usarías para la *seed*?

5. ¿Por qué el checksum usa XOR y no una suma simple?

---

## 15. Extensión opcional

Agrega un segundo tipo de falla al sensor:

- Con una probabilidad de 5%, el sensor devuelve un valor fuera del rango válido (por ejemplo, 127 o –128)
- El campo de error en el registro debe activarse automáticamente cuando esto ocurra
- Las estadísticas deben excluir las lecturas con error
