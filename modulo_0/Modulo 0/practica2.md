# Práctica 2: Control de Flujo en C++

## Objetivo

Aplicar estructuras de control en C++:

- Ramificación con `if / else`
- Uso de `switch`
- Operador ternario `?:`
- Bucles `for`, `while`, `do-while`
- Recorrido de `std::vector`
---

# Parte 1 — Clasificador de números

## Instrucciones

1. Pide al usuario un número entero.
2. Indica si el número es:
   - negativo
   - cero
   - positivo
3. Indica además si es:
   - par
   - impar

### Restricciones

- Usa `if / else`
- Usa `a & 1` para determinar si es par o impar

---

## Ejemplo esperado

Entrada:
```

-7

```

Salida:
```

negative
impar

```

---

# Parte 2 — Menú con switch

## Instrucciones

Crea un menú que muestre:

```

1 - Saludar
2 - Mostrar números del 1 al 5
3 - Mostrar números del 5 al 1
4 - Salir

````

El usuario debe ingresar una opción.

### Requisitos

- Usa `switch`
- Usa `for` para contar del 1 al 5
- Usa `while` o `do-while` para contar del 5 al 1
- Incluye `default`

---

# Parte 3 — Uso del operador ternario

## Instrucciones

1. Declara una variable entera `x`.
2. Usa el operador ternario para:
   - Asignar 100 si `x > 10`
   - Asignar 0 si no

Ejemplo:

```cpp
int resultado = x > 10 ? 100 : 0;
````

Imprime el resultado.

---

# Parte 4 — Trabajo con std::vector

## Instrucciones

1. Crea un `std::vector<int>` vacío.
2. Pide al usuario 5 números.
3. Guárdalos con `push_back`.
4. Imprime:

   * Todos los valores
   * Solo los valores mayores que 10
   * La suma total

### Requisitos

* Usa `for` basado en rango
* Usa una variable acumuladora

---

# Parte 5 — Bucle controlado por condición

Crea un programa que:

1. Pida números al usuario.
2. Los almacene en un vector.
3. Termine cuando el usuario escriba `0`.
4. Muestre:

   * Cuántos números ingresó
   * Cuántos fueron positivos
   * Cuántos fueron negativos

Usa:

* `while`
* `if`
* `vector`

---

# Parte 6 — Desafío extra (opcional)

Haz un pequeño "simulador de cajero":

* El saldo inicial es 1000.
* El usuario puede:

  * 1 → depositar
  * 2 → retirar
  * 3 → consultar saldo
  * 4 → salir

Requisitos:

* Usa `do-while`
* Usa `switch`
* Valida que no se pueda retirar más de lo disponible
* Usa operador ternario al menos una vez

---

# Reflexión Final

Responde:

1. ¿Cuándo usarías `switch` en lugar de `if`?
2. ¿Cuándo usarías `while` en lugar de `for`?
3. ¿Qué ventajas tiene el `for` basado en rango?