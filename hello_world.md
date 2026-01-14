
# Hola Mundo en C++


```cpp
#include <iostream>
// our first program
int main ()
{
 std::cout << "Hello World\n";
}
```

## Archivo fuente: `hello.cpp`

```cpp
#include <iostream>
````

Esta línea será reemplazada por el contenido del archivo `iostream`.

`iostream` es un archivo de cabecera que se encuentra en los directorios del compilador y proporciona funcionalidades de entrada y salida.

* `#include "ruta/al/archivo"`
  Inserta el contenido de un archivo específico.

* `#include <archivo>`
  Hace lo mismo, pero busca el archivo en todos los directorios de inclusión estándar.

El preprocesamiento ocurre **antes de la compilación**, por lo que el compilador solo ve el archivo ya preprocesado.

```cpp
// nuestro primer programa
```

Los comentarios son ignorados por el compilador.

```cpp
// comentario de una sola línea
```

```cpp
/* Comentario estilo C
   de múltiples líneas */
```

```cpp
int main ()
```

Define una función llamada `main`.

* Todo programa en C++ comienza ejecutando la función `main`.
* `int` es el único tipo de retorno permitido para `main` (entero).
* `()` es una lista vacía de parámetros.

```cpp
{
```

Los bloques de instrucciones se encierran entre llaves `{ … }`.

* Cada instrucción termina con punto y coma `;`.

```cpp
    std::cout << "Hello World\n";
```

Esta instrucción escribe texto en la consola.

* `std` es el *namespace* de la biblioteca estándar.
* `cout` (abreviatura de *character out*) representa la salida estándar (consola).
* `"Hello World\n"` es un literal de cadena (secuencia de caracteres).
* `\n` es un carácter especial de salto de línea.

```cpp
}
```

El programa termina después de ejecutar la función `main`.

* Si no se especifica un `return`, el programa retorna automáticamente `0`, lo que indica éxito.
* Códigos de retorno distintos de `0` son interpretados como errores por el sistema operativo.

---

## Compilación de `hello.cpp`

C++ es un **lenguaje compilado**:

* El código fuente no puede ejecutarse directamente.
* El código se escribe para una máquina abstracta.
* El compilador traduce el código fuente a código binario entendido por la CPU.
* El resultado es un archivo ejecutable.

```bash
$ g++ hello.cpp -o sayhello
$ ./sayhello
Hello World!
```

* Compilar y enlazar
* Ejecutar el archivo `sayhello`
* Salida del programa

Este es un ejemplo de cómo compilar un solo archivo.

---

## Terminología

* **Error del compilador**
  El programa no se puede compilar y el compilador se detiene.

* **Advertencia del compilador (Warning)**
  El programa se compila, pero existe código problemático que puede causar errores en tiempo de ejecución.

* **static**
  Fijo en tiempo de compilación (queda integrado en el ejecutable).

* **dynamic**
  Cambiable en tiempo de ejecución (por ejemplo, mediante entrada del usuario).

---

## Banderas del compilador (Compiler Flags)

Banderas recomendadas para tus primeros programas en C++:

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic -Wshadow input.cpp -o output
```

### Descripción de las banderas

* `-std=c++20`
  Establece el estándar C++20. **Altamente recomendado**.

* `-Wall`

* `-Wextra`

* `-Wpedantic`

* `-Wshadow`

Habilitan advertencias del compilador.
No activan *todas* las advertencias, sino las más importantes sin generar demasiado ruido.

* `-o <nombre>`
  Define el nombre del archivo ejecutable de salida.

> Es 2025: usa C++20 (o al menos C++17 si tu compilador es antiguo).

---

## ❌ No uses `using namespace std;`

Muchos ejemplos muestran algo como:

```cpp
using namespace std;

int main () {
    cout << "bla\n";
}
```

Esto se hace para evitar escribir `std::cout`.

### Pero esto es una mala práctica:

* Importa **todos** los símbolos del namespace `std` al namespace global.
* Puede causar conflictos de nombres y ambigüedades.
* Puede generar errores difíciles de detectar, incluso en tiempo de ejecución.

**Contaminar el namespace global es un problema serio en código de producción.**
Evita este anti-patrón desde el inicio.

---

