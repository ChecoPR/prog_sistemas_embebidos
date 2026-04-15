# Funciones

## Entradas y Salidas

**Primer ejemplo — función que calcula la media de 2 números:**

```cpp
#include <iostream>
double mean (double a, double b) {
  return (a + b) / 2;
}
int main () {
  std::cout << mean(2, 6) <<'\n';  // imprime 4
}
```

**Ventajas:**

- Encapsulación de los detalles de implementación
- Facilita razonar sobre la corrección y las pruebas al dividir los problemas en funciones separadas
- Evita repetir código para tareas comunes

---

## Tipos de Retorno

**Un solo valor:**

```cpp
double square (double x) {
  return (x * x);
}
int max (int x, int y) {
  if (x > y) return x; else return y;
}
```

**O nada (`void`):**

```cpp
void print_squares (int n) {
  for (int i = 1; i <= n; ++i)
    cout << square(i) << '\n';
}
```

**Deducción automática del tipo de retorno `[C++14]`:**

```cpp
auto foo (int i, double d) {
  // ...
  return i;
}
//  OK: tipo de retorno: int
```

```cpp
auto foo (int i, double d) {
  return i;  //  int
  // ...
  return d;  //  double
}
//  ERROR: ¡Tipos de retorno inconsistentes!
```

---

## Parámetros

- Ninguno: `f()`
- Uno o varios: `g(int a, double b, int c, …)`
- Los nombres de los parámetros deben ser únicos dentro de la lista

### Parámetros `const`

```cpp
int foo (int a, int const b) {
  a += 5;   // OK
  b += 10;  //  ERROR DE COMPILACIÓN: no se puede modificar un parámetro const
  return (a + b);
}
// llamando a foo:
foo(2,9);  // el const no tiene efecto aquí
```

> Cualquier segundo argumento pasado a `foo` se copia en la variable local `b`. El hecho de que `b` sea `const` no tiene efecto fuera de `foo`.

**Buena práctica:** "Si no necesitas o no debes modificar los valores de los parámetros dentro de la función, decláralos `const`."

### Parámetros con valor por defecto

```cpp
double f (double a, double b = 1.5) {
  return (a * b);
}
int main () {
  cout <<  f(2);     // 1 argumento  → 3.0
  cout <<  f(2, 3);  // 2 argumentos → 6.0
}
```

```cpp
void foo (int i = 0);
void foo (int n, double x = 2.5);
void foo (int a, int b = 1, float c = 3.5f);
void foo (int a, int b = 1, int c );  //  ERROR
```

**Regla:** "¡Cada parámetro después del primer valor por defecto también debe tener valor por defecto!"

---

## Sobrecarga

- Funciones con el mismo nombre pero listas de parámetros diferentes
- No se puede sobrecargar únicamente en el tipo de retorno

**Mismo nombre, listas de parámetros distintas:**

```cpp
int abs (int i) {
  return ((i < 0) ? -i : i);
}

double abs (double d) {
  return ((d < 0.0) ? -d : d);
}
int a = -5;
double b = -2.23;
auto x = abs(a); // int abs(int)
auto y = abs(b); // double abs(double)
```

**Mismo nombre, mismas listas de parámetros:**

```cpp
int foo (int i) {
  return (2 * i);
}

double foo (int i) {
  return (2.5 * i);
}

// NO COMPILA
```

---

## Implementación

### Recursión

**Definición:** Una función que se llama a sí misma.

**Características:**
- Necesita una condición de salida
- Parece más elegante que los bucles, pero suele ser más lenta
- La profundidad de recursión está limitada por el tamaño del stack

**Ejemplo:**

```cpp
int factorial (int n) {
    // condición de salida:
    if (n < 2) return 1;
    // llamada recursiva: n! = n * (n-1)!
    return (n * factorial(n - 1));
}
```

---

### Declaración vs. Definición

- Solo se pueden llamar funciones ya conocidas (declaradas antes o arriba)
- Solo se permite una definición por archivo fuente (unidad de traducción)
- Está permitido tener cualquier número de declaraciones = anunciar la existencia de una función especificando su firma

**Ejemplo — ¡roto!**

```cpp
#include <iostream>
//  ERROR DE COMPILACIÓN: 'odd'/'even' no son conocidas antes de 'main'
//  ERROR DE COMPILACIÓN: 'odd' no es conocida antes de 'even'
int main () {
  std::cout << "ingresa un entero: ";  int i = 0;
  std::cin >> i;
  if (odd(i))  std::cout << "es impar\n";
  if (even(i)) std::cout << "es par\n";
}
bool even (int n) {
  return !odd(n);
}
bool odd (int n) {
  return (n % 2);
}
```

**Versión correcta:**

```cpp
#include <iostream>
bool even (int);  // declaración
bool odd (int);   // declaración
int main () {     // definición de 'main'
  std::cout << "ingresa un entero: ";  int i = 0;
  std::cin >> i;
  if (odd(i))  std::cout << "es impar\n";   // OK, ya declarada
  if (even(i)) std::cout << "es par\n";     // OK, ya declarada
}
bool even (int n) { // definición de 'even'
  return !odd(n);   // OK, ya declarada
}
bool odd (int n) {  // definición de 'odd'
  return (n % 2);
}
```

---

## Diseño

> "Las interfaces deben ser fáciles de usar correctamente y difíciles de usar incorrectamente." — Scott Meyers

### Contratos

**Al diseñar una función, pensar en:**

- **Precondiciones:** ¿Qué esperas/exiges de los valores de entrada?
- **Postcondiciones:** ¿Qué garantías debes dar sobre los valores de salida?
- **Invariantes:** ¿Qué esperan los usuarios que no cambie?
- **Propósito:** ¿Tiene tu función un propósito claramente definido?
- **Nombre:** ¿El nombre de la función refleja su propósito?
- **Parámetros:** ¿Puede un usuario confundir fácilmente su significado?

---

### Verificación de precondiciones

**Funciones de contrato amplio (Wide contract):** Realizan verificaciones de precondiciones, es decir, comprueban la validez de los valores de los parámetros de entrada (o del estado del programa).

**Funciones de contrato estrecho (Narrow contract):** No realizan verificaciones de precondiciones. El llamante debe asegurarse de que los argumentos de entrada (y el estado del programa) sean válidos.

---

### Atributo `[[nodiscard]]` `[C++17]`

Algunas funciones existen únicamente para calcular y devolver un valor. Llamarlas sin usar ese valor no tiene ningún sentido — y casi siempre indica un error.

Sin `[[nodiscard]]`, el compilador no dice nada. Con `[[nodiscard]]`, emite una advertencia.

```cpp
[[nodiscard]] bool prime (int i) { /* ... */ }

// valor de retorno usado — correcto:
bool const yes = prime(47);
if (prime(47)) { /* ... */ }

// valor de retorno descartado — advertencia:
prime(47);  //  ADVERTENCIA DEL COMPILADOR
```

Un caso clásico de confusión: `empty()` y `clear()` en `std::vector`.

- `empty()` **consulta** si el vector está vacío. Devuelve `true` o `false`. No modifica nada.
- `clear()` **vacía** el vector. No devuelve nada.

Son nombres parecidos pero hacen cosas completamente distintas. Si alguien escribe `v.empty()` queriendo vaciar el vector, la línea no hace nada — y sin `[[nodiscard]]` el compilador lo dejaría pasar en silencio.

```cpp
std::vector<int> v;
// ...
if (v.empty()) { /* ... */ }  // OK: el valor de retorno se usa
v.empty();  // C++20: ADVERTENCIA — ¿se quiso escribir v.clear()?
```

**Usa `[[nodiscard]]` cuando:**
- Ignorar el valor de retorno no tiene sentido en ningún contexto.
- El nombre de la función puede confundirse con otra que sí modifica el estado.

---

### Garantía de no lanzar excepciones: `noexcept` `[C++11]`

En C++, una **excepción** es la forma que tiene el lenguaje de señalar un error en tiempo de ejecución que no puede manejarse localmente. Cuando ocurre ese error, se "lanza" (`throw`) una excepción que sube por la pila de llamadas hasta que algo la "atrape" (`catch`).

`noexcept` es una promesa: esta función nunca dejará escapar una excepción.

```cpp
void foo () noexcept { /* ... */ }
```

Si a pesar de la promesa una excepción escapa, el programa llama inmediatamente a `std::terminate()` — se aborta sin posibilidad de recuperación.

**¿Por qué usarlo?**

- Documenta la intención: quien llame a la función sabe que no necesita manejar excepciones.
- El compilador puede generar código más eficiente.
- En muchos entornos embebidos las excepciones están desactivadas por completo para reducir el tamaño del binario y el overhead en tiempo de ejecución.

---

## Algunas Funciones Matemáticas

`#include <cmath>`

| Función | Notación | Descripción |
|---------|----------|-------------|
| `double sqrt (double x)` | √x | raíz cuadrada |
| `double pow (double a, double b)` | a^b | potencia |
| `double abs (double x)` | \|x\| | valor absoluto |
| `double sin (double x)` | sin(x) | seno |
| `double cos (double x)` | cos(x) | coseno |
| `double exp (double x)` | e^x | exponencial |
| `double log (double x)` | log(x) | logaritmo |
| `double floor (double x)` | ⌊x⌋ | entero menor más cercano |
| `double ceil (double x)` | ⌈x⌉ | entero mayor más cercano |
| `double fmod (double x, double y)` | — | resto de x/y |
