ArduSiser2
==========

Esta versión de Siser está pensada para trabajar bajo Arduino Nano,
el cual está en modo sleep para ahorrar la mayor cantidad de energía
y se despierta mediante un pulsador o mediante una interrupción generada
por un Real Time Clock (RTC, [click para ver su configuración](RTC.md)).


## Dependencias

### Instalables mediante el library manager

- DHT sensor libray by Adafruit
- Adafruit unified sensor by Adafruit (requerido por DHT sensor)

### Instalable mediante zip

Descargar como `.zip`:

- [RTClibExtended](https://github.com/FabioCuomo/FabioCuomo-DS3231/)

## Configuración (config.h)

### Pinout

En este archivo puede modificarse el pinout, sin embargo,
existen pines reservados:

- I2C: A4, A5
- Interrupción por RTC: D2
- Interrupción por Pulsador: D3

El resto de pines quedan a su completa disposición.

### Modo DEBUG
En caso no se cuente con los sensores, al actibar el modo  DEBUG
(`#define DEBUG`), el programa fijará datos para las variables medidas
y así no enviar valores no legibles (como NAN).
