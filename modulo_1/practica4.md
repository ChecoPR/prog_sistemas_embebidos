# Práctica 4. ESP8266 + WiFi + Servidor Web con apoyo de IA

## Objetivo

Desarrollar un sistema básico con ESP8266 que:

- Se conecte a una red WiFi
- Cree un servidor web
- Permita encender y apagar un LED desde el navegador
- Utilizar inteligencia artificial como herramienta de apoyo
- Comprender el código generado

---

# Reglas importantes

1. **Está permitido usar IA (ChatGPT, Claude, etc.)**
2. **No se permite copiar código sin entenderlo**
3. Todo el código debe poder ser explicado por el estudiante
4. El programa debe ser ejecutado en el ESP8266

---

# Parte 1 — Investigación guiada con IA

Cada estudiante deberá interactuar con una IA y documentar su proceso.

---

## 🔹 Preguntas para la IA

Deben copiar estas preguntas y luego analizar las respuestas:

1. ¿Cómo conectar un ESP8266 a una red WiFi usando Arduino IDE?
2. ¿Cómo crear un servidor web en ESP8266?
3. ¿Cómo encender un LED desde una página web en ESP8266?
4. ¿Qué librerías necesito para esto?
5. ¿Qué significa cada parte del código?

---

## 🔹 Entregable de esta parte

- Captura o texto del prompt para la IA
- Explicación propia de:
  - conexión WiFi
  - servidor web
  - control del LED

---

# Parte 2 — Implementación

## Requisitos técnicos

El programa debe:

1. Conectarse a WiFi:

```cpp
WiFi.begin(ssid, password);
````

2. Crear un servidor web:

```cpp
WiFiServer server(80);
```

3. Escuchar peticiones del navegador

4. Mostrar una página HTML simple

5. Incluir un botón:

* Encender LED
* Apagar LED

---

## Comportamiento esperado

Al entrar desde el navegador:

```
http://IP_DEL_ESP
```

Debe mostrarse una página con botones:

```
[ Encender LED ]
[ Apagar LED ]
```

---

# Parte 3 — Conexión física

* Usar LED integrado

---

# Parte 4 — Validación

* Conexión exitosa a WiFi
* Acceso al servidor desde celular o computadora
* Funcionamiento del botón
* LED responde correctamente

---

# Parte 5 — Explicación obligatoria

1. ¿Qué hace `WiFi.begin()`?
2. ¿Qué hace `server.begin()`?
3. ¿Qué es una dirección IP?
4. ¿Cómo sabe el ESP que presionaste el botón?
5. ¿Qué parte del código prende el LED?
