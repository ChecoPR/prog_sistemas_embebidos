# Práctica 5 — Sensor Simulado con ESP8266 + Servidor Web

### **Asignatura:** Programación de Sistemas Embebidos
### **Módulo:** 1 — Hardware programable
### **Plataforma:** ESP8266 (NodeMCU / Wemos D1 Mini)
### **Entregable:** Código fuente + capturas de pantalla del navegador

---

## 1. Objetivo

Construir un sistema embebido que:

- Se conecte a una red WiFi
- Genere lecturas de un **sensor simulado por software** (sin hardware adicional)
- Sirva esas lecturas desde un **servidor web** accesible desde el navegador
- Muestre un **historial de las últimas lecturas** en tiempo real

---

## 2. ¿Por qué simular un sensor?

En el desarrollo embebido real, simular sensores es una práctica estándar:

- Permite probar el sistema **antes de tener hardware**
- Se pueden forzar valores extremos (temperaturas muy altas, errores)
- El código de comunicación y presentación se desarrolla independientemente del sensor

Al final de esta práctica podrás reemplazar la función del sensor simulado por una lectura real (DHT11, NTC, etc.) **sin cambiar el resto del código**.

---

## 3. Materiales

- ESP8266 (NodeMCU o Wemos D1 Mini)
- Cable USB
- Arduino IDE con soporte para ESP8266
- Red WiFi con acceso desde tu computadora o celular

---

## 4. Librerías necesarias

En Arduino IDE, verificar que estén instaladas:

- `ESP8266WiFi` — incluida con el paquete ESP8266
- `ESP8266WebServer` — incluida con el paquete ESP8266

No se necesita ninguna librería externa para esta práctica.

---

## 5. Parte 1 — Conexión a WiFi

Este bloque ya lo vimos en la Práctica 4. Se incluye aquí como punto de partida.

```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* SSID     = "TU_RED";
const char* PASSWORD = "TU_CLAVE";

ESP8266WebServer server(80);

void setup() {
    Serial.begin(115200);

    WiFi.begin(SSID, PASSWORD);
    Serial.print("Conectando");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConectado.");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}
```

### Antes de continuar

1. Reemplaza `TU_RED` y `TU_CLAVE` con los datos de tu red.
2. Carga solo este bloque (con un `loop()` vacío) y verifica en el **Monitor Serie** que aparezca la IP.
3. Anota la IP. La necesitarás para abrir el servidor desde el navegador.

**No continúes hasta tener la IP en el Monitor Serie.**

---

## 6. Parte 2 — El sensor simulado

Un sensor simulado es simplemente una función que devuelve un valor calculado.  
Usaremos dos técnicas combinadas:

### 6.1 Variación sinusoidal (tendencia lenta)

```cpp
#include <math.h>

float leer_temperatura() {
    float t        = millis() / 1000.0;   // segundos desde encendido
    float base     = 22.0;                // temperatura base en °C
    float amplitud = 5.0;                 // variación máxima ±5°C
    float periodo  = 60.0;               // ciclo completo cada 60 segundos

    return base + amplitud * sin(2.0 * M_PI * t / periodo);
}
```

### ¿Qué hace esta función?

- `millis()` devuelve los milisegundos transcurridos desde que encendió el ESP
- Dividido entre 1000.0 da los **segundos**
- `sin(...)` genera una onda que oscila entre –1 y +1
- Multiplicada por `amplitud` oscila entre –5 y +5
- Sumada a `base` → la temperatura oscila entre **17°C y 27°C**

La temperatura sube y baja suavemente cada minuto, como lo haría en un ambiente real.

### 6.2 Agregar ruido

Los sensores reales tienen pequeñas variaciones. Las simulamos así:

```cpp
float leer_temperatura() {
    float t        = millis() / 1000.0;
    float base     = 22.0;
    float amplitud = 5.0;
    float periodo  = 60.0;
    float tendencia = base + amplitud * sin(2.0 * M_PI * t / periodo);

    // Ruido: valor entre -1.0 y +1.0
    float ruido = (random(-100, 100)) / 100.0;

    return tendencia + ruido;
}
```

### Tarea — verificar en Monitor Serie

Agrega en `loop()`:

```cpp
void loop() {
    Serial.println(leer_temperatura());
    delay(1000);
}
```

Abre el Monitor Serie y observa cómo los valores cambian lentamente con pequeñas variaciones.  
**No continúes hasta verificar que la función produce valores razonables.**

---

## 7. Parte 3 — Servidor web con lectura actual

Ahora serviremos la lectura actual desde el navegador.

### 7.1 Función que genera la página HTML

```cpp
void handle_raiz() {
    float temp = leer_temperatura();

    String html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='utf-8'>";
    html += "<title>Sensor ESP8266</title>";
    html += "</head><body>";
    html += "<h1>Sensor de Temperatura</h1>";
    html += "<p>Temperatura actual: <strong>";
    html += String(temp, 1);      // un decimal
    html += " &deg;C</strong></p>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}
```

### ¿Qué hace `server.send`?

- Primer argumento: código HTTP (`200` = OK)
- Segundo argumento: tipo de contenido
- Tercer argumento: el cuerpo de la respuesta (la página HTML)

### 7.2 Registrar la ruta y arrancar el servidor

En `setup()`, después de conectar a WiFi:

```cpp
    server.on("/", handle_raiz);
    server.begin();
    Serial.println("Servidor iniciado.");
```

### 7.3 Atender peticiones en el loop

```cpp
void loop() {
    server.handleClient();
}
```

`handleClient()` revisa si hay una petición pendiente y la procesa.  
Debe llamarse continuamente, por eso va en `loop()`.

### Verificación

1. Carga el programa.
2. Abre el navegador y entra a `http://IP_DEL_ESP/`
3. Debes ver la temperatura actual.
4. Recarga la página. ¿Cambia el valor?

---

## 8. Parte 4 — Actualización automática

Recargar manualmente no es práctico. Agrega un **meta refresh** para que la página se actualice sola cada 3 segundos.

Modifica `handle_raiz`:

```cpp
    html += "<meta charset='utf-8'>";
    html += "<meta http-equiv='refresh' content='3'>";   // <-- nueva línea
```

### Verificación

Abre la página. Observa cómo el valor se actualiza solo cada 3 segundos.

---

## 9. Parte 5 — Historial de lecturas

Una sola lectura no es suficiente. Vamos a mantener un historial de las últimas 10.

### 9.1 Declarar el historial (variable global)

```cpp
const int MAX_LECTURAS = 10;
float     historial[MAX_LECTURAS];
int       indice = 0;
bool      lleno  = false;
```

### 9.2 Función para guardar una lectura

```cpp
void guardar_lectura(float valor) {
    historial[indice] = valor;
    indice = (indice + 1) % MAX_LECTURAS;
    if (indice == 0) lleno = true;
}
```

### ¿Qué hace `(indice + 1) % MAX_LECTURAS`?

- Cuando `indice` llega a 10, vuelve a 0
- El arreglo funciona como un **buffer circular**: las lecturas nuevas sobreescriben las más antiguas
- No necesitamos mover elementos ni usar memoria dinámica

### 9.3 Tomar una lectura cada 5 segundos

Sin usar `delay()` (que bloquearía el servidor):

```cpp
unsigned long ultima_lectura = 0;

void loop() {
    server.handleClient();

    if (millis() - ultima_lectura >= 5000) {
        ultima_lectura = millis();
        guardar_lectura(leer_temperatura());
    }
}
```

### ¿Por qué no usar `delay(5000)`?

Con `delay(5000)` el ESP estaría **bloqueado** 5 segundos y no podría atender peticiones del navegador.  
La técnica `millis() - ultima_lectura` compara tiempos sin bloquear el programa.  
Es el patrón estándar en Arduino para tareas temporizadas.

---

## 10. Parte 6 — Mostrar el historial en la página

Modifica `handle_raiz` para incluir la tabla de lecturas:

```cpp
void handle_raiz() {
    float temp = leer_temperatura();

    String html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='utf-8'>";
    html += "<meta http-equiv='refresh' content='3'>";
    html += "<title>Sensor ESP8266</title>";
    html += "<style>";
    html += "body { font-family: monospace; padding: 20px; }";
    html += "table { border-collapse: collapse; }";
    html += "td, th { border: 1px solid #ccc; padding: 6px 12px; }";
    html += "</style>";
    html += "</head><body>";

    html += "<h1>Sensor de Temperatura</h1>";
    html += "<p>Lectura actual: <strong>";
    html += String(temp, 1);
    html += " &deg;C</strong></p>";

    html += "<h2>Historial</h2>";
    html += "<table><tr><th>#</th><th>Temperatura</th></tr>";

    int total = lleno ? MAX_LECTURAS : indice;
    for (int i = 0; i < total; i++) {
        // Recorrer del más antiguo al más reciente
        int pos = lleno ? (indice + i) % MAX_LECTURAS : i;
        html += "<tr><td>";
        html += String(i + 1);
        html += "</td><td>";
        html += String(historial[pos], 1);
        html += " &deg;C</td></tr>";
    }

    html += "</table>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}
```

### Verificación

Abre la página y espera al menos 30 segundos.  
La tabla debe llenarse con lecturas nuevas cada 5 segundos.  
Cuando llegue a 10 filas, las más antiguas desaparecen y aparecen las nuevas.

---

## 11. Código completo

```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <math.h>

const char* SSID     = "TU_RED";
const char* PASSWORD = "TU_CLAVE";

ESP8266WebServer server(80);

const int MAX_LECTURAS = 10;
float     historial[MAX_LECTURAS];
int       indice = 0;
bool      lleno  = false;

unsigned long ultima_lectura = 0;

// --- Sensor simulado ---

float leer_temperatura() {
    float t         = millis() / 1000.0;
    float base      = 22.0;
    float amplitud  = 5.0;
    float periodo   = 60.0;
    float tendencia = base + amplitud * sin(2.0 * M_PI * t / periodo);
    float ruido     = (random(-100, 100)) / 100.0;
    return tendencia + ruido;
}

// --- Buffer circular ---

void guardar_lectura(float valor) {
    historial[indice] = valor;
    indice = (indice + 1) % MAX_LECTURAS;
    if (indice == 0) lleno = true;
}

// --- Servidor web ---

void handle_raiz() {
    float temp = leer_temperatura();

    String html = "<!DOCTYPE html><html><head>";
    html += "<meta charset='utf-8'>";
    html += "<meta http-equiv='refresh' content='3'>";
    html += "<title>Sensor ESP8266</title>";
    html += "<style>";
    html += "body { font-family: monospace; padding: 20px; }";
    html += "table { border-collapse: collapse; }";
    html += "td, th { border: 1px solid #ccc; padding: 6px 12px; }";
    html += "</style>";
    html += "</head><body>";

    html += "<h1>Sensor de Temperatura</h1>";
    html += "<p>Lectura actual: <strong>";
    html += String(temp, 1);
    html += " &deg;C</strong></p>";

    html += "<h2>Historial</h2>";
    html += "<table><tr><th>#</th><th>Temperatura</th></tr>";

    int total = lleno ? MAX_LECTURAS : indice;
    for (int i = 0; i < total; i++) {
        int pos = lleno ? (indice + i) % MAX_LECTURAS : i;
        html += "<tr><td>" + String(i + 1) + "</td><td>";
        html += String(historial[pos], 1) + " &deg;C</td></tr>";
    }

    html += "</table></body></html>";
    server.send(200, "text/html", html);
}

// --- Setup y loop ---

void setup() {
    Serial.begin(115200);

    WiFi.begin(SSID, PASSWORD);
    Serial.print("Conectando");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConectado.");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    server.on("/", handle_raiz);
    server.begin();
    Serial.println("Servidor iniciado.");
}

void loop() {
    server.handleClient();

    if (millis() - ultima_lectura >= 5000) {
        ultima_lectura = millis();
        float temp = leer_temperatura();
        guardar_lectura(temp);
        Serial.println(temp);
    }
}
```

---

## 12. Pasos de validación

Completar en orden:

- [ ] El Monitor Serie muestra la IP del ESP
- [ ] `http://IP_DEL_ESP/` abre en el navegador
- [ ] La lectura actual aparece en la página
- [ ] La página se actualiza sola cada 3 segundos
- [ ] La tabla de historial se llena con el tiempo
- [ ] El historial no supera las 10 filas (las antiguas desaparecen)
- [ ] El Monitor Serie muestra lecturas cada 5 segundos

---

## 13. Preguntas de reflexión

1. ¿Por qué usamos `millis()` en lugar de `delay(5000)` para tomar lecturas periódicas?

2. ¿Qué es un buffer circular? ¿Por qué es útil en sistemas con poca RAM?

3. La función `leer_temperatura` usa `sin()`. ¿Qué cambiarías en ella para simular:
   - Una temperatura que solo sube
   - Una temperatura que cambia bruscamente

4. ¿Qué pasaría si reemplazas `handle_raiz` con una función que lee un sensor DHT11 real? ¿Qué parte del código cambiaría y qué parte quedaría igual?

5. ¿Por qué el servidor devuelve el código `200`? ¿Qué significaría devolver `404`?
