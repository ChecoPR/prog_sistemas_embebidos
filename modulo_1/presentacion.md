# Investigación: Comparación entre microcontroladores y computadoras Embebidas

## Objetivo

Analizar y comparar arquitecturas de hardware programable:

- Microcontroladores (MCU)
- Computadoras embebidas de propósito general (SBC)

Desarrollar criterio técnico para distinguir:

- Arquitectura
- Modelo de programación
- Sistema operativo
- Recursos disponibles
- Casos de uso reales

---

# Organización

Se dividirá el grupo en dos equipos:

## Equipo 1 — Microcontroladores (MCU)

Investigar:

- Arduino (Uno / Mega)
- ESP8266
- ESP32
- STM32
- Raspberry Pi Pico (RP2040)

---

## Equipo 2 — Computadoras embebidas (SBC)

Investigar:

- Raspberry Pi (modelos recientes)
- NVIDIA Jetson Nano
- BeagleBone Black
- Orange Pi

---

# Marco conceptual

Antes de investigar, es importante entender:

### Microcontrolador (MCU)

- CPU + RAM + periféricos integrados en un solo chip
- Recursos limitados
- Normalmente sin sistema operativo
- Ejecuta un único programa
- Tiempo real o cercano a tiempo real

### Single Board Computer (SBC)

- Placa con CPU, RAM y almacenamiento externo
- Ejecuta un sistema operativo (generalmente Linux)
- Soporta multitarea
- Más cercana a una computadora tradicional

---

# Preguntas

Cada equipo debe responder las siguientes preguntas.

---

## 1 ¿Qué procesador utiliza?

Especificar:

- Arquitectura (AVR, ARM Cortex-M, ARM Cortex-A, etc.)
- Número de núcleos
- Frecuencia de reloj (MHz / GHz)
- Soporte para FPU (si aplica)

Ejemplo de nivel esperado:
> ESP32 usa arquitectura Xtensa LX6, dual-core, hasta 240 MHz.

---

## 2 ¿Tiene sistema operativo?

Especificar:

- No tiene sistema operativo (bare-metal)
- Usa RTOS (FreeRTOS, por ejemplo)
- Ejecuta Linux u otro sistema operativo

Explicar brevemente:

- ¿Qué implica programar sin sistema operativo?
- ¿Qué implica programar sobre Linux?

---

## 3 ¿Cuánta RAM y almacenamiento tiene?

Indicar:

- RAM disponible (KB, MB, GB)
- Flash interna
- Almacenamiento externo (SD, eMMC)

Comparar magnitudes:

- MCU típicamente: KB a pocos MB
- SBC típicamente: cientos de MB o varios GB

---

## 4 ¿Para qué tipo de proyectos es ideal?

Clasificar en categorías:

- IoT
- Automatización industrial
- Procesamiento de señales
- Visión por computadora
- Control en tiempo real
- Servidores ligeros
- Edge AI

Deben justificar técnicamente la elección.

---

## 5 ¿Es más cercana a C++ bare-metal o a Linux?

Analizar:

- ¿Se programa directamente sobre registros?
- ¿Se usan bibliotecas de alto nivel?
- ¿Se trabaja con drivers?
- ¿Se tiene acceso a procesos y multitarea?

Ejemplo esperado:

- STM32 → C/C++ bare-metal, control de registros, periféricos directos.
- Raspberry Pi → Linux, procesos, archivos, sockets.

---

# Entregable

Cada equipo debe presentar:

- Tabla comparativa
- Análisis técnico
- Conclusión

---

# Estructura de la presentación

## 1. Introducción
Definición del tipo de dispositivo.

## 2. Especificaciones técnicas
Procesador, RAM, almacenamiento, conectividad.

## 3. Modelo de programación
Bare-metal, RTOS, Linux.

## 4. Limitaciones técnicas
Memoria, consumo energético, latencia, potencia de cómputo.

## 5. Aplicaciones reales
Ejemplos industriales o comerciales.

## 6. Conclusión comparativa
¿Cuándo elegir MCU?
¿Cuándo elegir SBC?
