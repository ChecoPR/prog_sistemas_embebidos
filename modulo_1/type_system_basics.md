# Sistema de tipos

## Declarar constantes con `const`

**Sintaxis:** `Tipo const nombre_variable = valor;`

- El valor no puede cambiar después de la asignación
- El valor inicial puede ser dinámico (establecido en tiempo de ejecución)

```cpp
int i = 0;
cin >> i;
int const k = i;  // "constante entera"
k = 5;  //  ERROR DE COMPILACIÓN: ¡k es const!
```

**Buena práctica:** "¡Declara siempre las variables como `const` si no necesitas cambiar su valor después de la asignación inicial!"

Beneficios:
- Evita errores al prevenir modificaciones accidentales
- Aclara la intención del código
- Puede mejorar el rendimiento mediante optimizaciones del compilador

---

## Alias de tipos: `using`

**Sintaxis moderna (C++11):** `using NuevoTipo = TipoAntiguo;`

**Sintaxis antigua (C++98):** `typedef TipoAntiguo NuevoTipo;`

```cpp
using real         = double;
using ullim        = std::numeric_limits<unsigned long>;
using index_vector = std::vector<std::uint_least64_t>;
```

---

## Deducción de tipos: `auto` `[C++11]`

**Sintaxis:** `auto variable = expresión;`

- El tipo de la variable se deduce del lado derecho de la asignación
- Suele ser más conveniente, más seguro y más resistente a cambios futuros
- Importante para la programación genérica (independiente del tipo)

```cpp
auto i = 2;                 // int
auto u = 56u;               // unsigned int
auto d = 2.023;             // double
auto f = 4.01f;             // float
auto l = -78787879797878l;  // long int
auto x = 0 * i;             // x: int
auto y = i + d;             // y: double
auto z = f * d;             // z: double
```

---

## Expresiones constantes: `constexpr` `[C++11]`

`constexpr` es una **promesa al compilador**: "este valor puede calcularse en tiempo de compilación".

El compilador *exige* cumplir esa promesa únicamente cuando el resultado se necesita en tiempo de compilación, es decir, cuando el destino también es `constexpr`. A eso se le llama **contexto `constexpr`**.

Fuera de un contexto `constexpr`, una función `constexpr` se comporta como cualquier función normal y se evalúa en tiempo de ejecución.

Restricciones de funciones `constexpr`:
- C++11: solo una sentencia `return`
- C++14+: se permiten múltiples sentencias

```cpp
constexpr int cxf (int i) { return i*2; }  // puede evaluarse al compilar
          int foo (int i) { return i*2; }  // solo puede evaluarse al ejecutar

constexpr int i = 2;        // OK: '2' es una literal (valor conocido al compilar)
constexpr int j = cxf(5);   // OK: cxf es constexpr y '5' es una literal
constexpr int k = cxf(i);   // OK: cxf e i son constexpr

int x = 0;                  // x es una variable normal (valor desconocido al compilar)
int l = cxf(x);             // OK: destino no es constexpr → se evalúa al ejecutar

constexpr int m = cxf(x);   // ERROR: contexto constexpr, pero x no lo es
constexpr int n = foo(5);   // ERROR: contexto constexpr, pero foo no lo es
```

La pregunta clave ante cualquier uso de `constexpr` es:
**¿el resultado se necesita en tiempo de compilación?**
Si el destino es `constexpr`, sí — y entonces todo lo que intervenga en el cálculo también debe serlo.
