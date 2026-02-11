# Práctica 1 - Decodificación de un Registro Binario en C++

---

### **Asignatura:** Programación de Sistemas Embebidos

### **Unidad:** Tipos Fundamentales y Operaciones Básicas

### **Lenguaje:** C++20

### **Entregable:** Código fuente + salida del programa

---

## 1. Objetivo de la práctica

Comprender cómo un **valor binario almacenado en memoria** puede representar múltiples datos distintos, y cómo extraerlos correctamente utilizando **tipos fundamentales**, **operaciones bit a bit**, **desplazamientos**, **comparaciones**, **operaciones lógicas** y **conversiones de tipo** en C++.

---

## 2. Contexto

En sistemas embebidos es común recibir información compactada en **registros binarios**.
Cada bit (o grupo de bits) tiene un significado específico definido por el hardware o el protocolo.

En esta práctica trabajaremos con un **registro de 32 bits**, interpretándolo completamente desde C++.

---

## 3. Registro de entrada

```cpp
std::uint32_t raw = 0b10101101'11100110'00010101'00110010;
```

### ¿Qué es `raw`?

* Es un **entero sin signo de 32 bits**
* Internamente solo es un conjunto de bits
* **No tiene significado por sí mismo**
* El significado se lo damos nosotros mediante el código

---

## 4. Distribución del registro

| Bits    | Campo                   |
| ------- | ----------------------- |
| 0 – 11  | Valor del sensor        |
| 12      | Estado del sistema      |
| 13      | Error                   |
| 14 – 15 | Modo                    |
| 16 – 23 | Temperatura (con signo) |
| 24 – 31 | Checksum                |

---

## 5. Código base

```cpp
#include <iostream>
#include <bitset>
#include <cstdint>
#include <limits>
#include <compare>

int main() {

    std::uint32_t raw = 0b10101101'11100110'00010101'00110010;

    std::cout << "Registro crudo:\n";
    std::cout << std::bitset<32>(raw) << "\n\n";
```

### ¿Qué ocurre aquí?

* `std::bitset<32>` **no cambia el valor**
* Solo nos permite **visualizar los bits**
* Esto es clave para depuración en sistemas embebidos

---

## 6. Extracción del valor del sensor (bits 0–11)

### Paso 1: Crear una máscara

Queremos quedarnos **solo con los primeros 12 bits**.

```cpp
std::uint32_t sensor_value = raw & 0xFFF;
```

### ¿Qué está pasando?

* `0xFFF` en binario es:

  ```
  0000 0000 0000 0000 0000 1111 1111 1111
  ```
* El operador `&`:

  * conserva los bits donde ambos son 1
  * elimina el resto
* No usamos desplazamiento porque el campo ya está alineado a la derecha

---

## 7. Extracción del estado del sistema (bit 12)

```cpp
bool state = (raw >> 12) & 1;
```

### Explicación:

1. `raw >> 12`

   * mueve el bit 12 a la posición 0
2. `& 1`

   * elimina todos los bits excepto el menos significativo
3. El resultado es `0` o `1`, convertible a `bool`

---

## 8. Extracción del indicador de error (bit 13)

```cpp
bool error = (raw >> 13) & 1;
```

### Observación importante

* El procedimiento es idéntico al del estado
* Solo cambia la posición del bit
* Esto refuerza la idea de **patrones repetibles**

---

## 9. Extracción del modo de operación (bits 14–15)

```cpp
std::uint32_t mode = (raw >> 14) & 0b11;
```

### ¿Qué ocurre aquí?

* Se desplazan los bits 14–15 a las posiciones 0–1
* `0b11` conserva solo dos bits
* El valor final está en el rango `[0, 3]`

---

## 10. Extracción de la temperatura (bits 16–23)

### Paso 1: Extraer como sin signo

```cpp
std::uint8_t temp_raw = (raw >> 16) & 0xFF;
```

### Paso 2: Interpretar como con signo

```cpp
std::int8_t temperature = static_cast<std::int8_t>(temp_raw);
```

### ¿Por qué esto funciona?

* `int8_t` usa **complemento a dos**
* El bit más significativo se interpreta como signo
* El patrón de bits es el mismo, cambia su interpretación

---

## 11. Extracción del checksum (bits 24–31)

```cpp
std::uint8_t checksum = (raw >> 24) & 0xFF;
```

### Concepto reforzado

* Mismo patrón: desplazar + enmascarar
* Diferente significado

---

## 12. Validaciones usando comparaciones

```cpp
bool sensor_ok = sensor_value <= 4095;

bool temp_ok =
    temperature >= std::numeric_limits<std::int8_t>::lowest() &&
    temperature <= std::numeric_limits<std::int8_t>::max();
```

### ¿Qué se está usando?

* Comparaciones binarias
* Límites reales del tipo de dato
* Evita supuestos incorrectos sobre rangos

---

## 13. Comparación de tres vías (`<=>`)

```cpp
const char* thermal_state;

if ((temperature <=> 25) < 0)
    thermal_state = "FRIA";
else if ((temperature <=> 25) == 0)
    thermal_state = "NORMAL";
else
    thermal_state = "CALIENTE";
```

### Ventaja del `<=>`

* Una sola operación define orden
* Menos comparaciones independientes
* Más expresivo conceptualmente

---

## 14. Lógica booleana y corto circuito

```cpp
bool system_active =
    state &&
    !error &&
    checksum != 0;
```

### ¿Por qué el orden importa?

* Si `state` es falso, lo demás **no se evalúa**
* Reduce operaciones innecesarias
* Fundamental en sistemas embebidos

---

## 15. Conversión y *narrowing*

```cpp
double voltage = sensor_value * 3.3 / 4095;

int volts_bad = voltage;        // conversión silenciosa
int volts_safe {voltage};       // detecta narrowing
```

### Qué observar

* Ambas compilan distinto
* `{}` protege contra pérdida de información
* Ejemplo real de bug silencioso

---

## 16. Reporte final

```cpp
std::cout << "\n--- REPORTE ---\n";
std::cout << "Sensor: " << sensor_value << "\n";
std::cout << "Estado: " << (state ? "ON" : "OFF") << "\n";
std::cout << "Error: " << (error ? "SI" : "NO") << "\n";
std::cout << "Modo: " << mode << "\n";
std::cout << "Temperatura: " << int(temperature) << " C\n";
std::cout << "Clasificacion: " << thermal_state << "\n";
std::cout << "Sistema activo: " << (system_active ? "SI" : "NO") << "\n";
std::cout << "Voltaje: " << voltage << " V\n";
std::cout << "----------------\n";
```

---

## 17. Conclusión

* Los bits no saben qué representan
* El tipo define cómo se interpretan
* Las operaciones básicas de C++ son suficientes para manipular hardware
* Errores pequeños en tipos pueden causar fallos graves