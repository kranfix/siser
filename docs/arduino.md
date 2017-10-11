Arduino
=======

# Configurando Arduino IDE
El primer paso es la configuración del Arduino IDE.
Para esto hay que instalar librerías para el uso de diferentes sensores.
Alguna de estas se pueden instalar directamente desde el gestor de librerías, sin embargo, algunas necesitan instalación manual.

Librerías instalables desde el gestor de librerías:
- DHT sensor Library (by Adafruit)
- Adafruit unified sensor

Librerías de instalación manual:
- TinyGPS

# Sensores y sistemas empleados

Se han empleado los siguientes sensores y sistemas:

- Rain: Sesor de lluvia que hace uso de un LM393 como interfaz adaptadora al Arduino.
- MQ2: Mide concentración CO2 en ppm.
- DHT22: Sensor de temperatura (°C) y humedad relaitva.
- GPS: Sistema de posición gobal. Entrega la latitud y longitud en grados sexagesimanles (°).
- BH1750: Sensor de ilumminancia o luxes (lx).

# Uso de puertos seriales

El Arduino Mega cuenta ccon 4 puertos seriales:

- Serial o Serial0
- Serial1
- Serial2
- Serial3

## Puerto Serial0
Empleado para programación y debugging.
En modo debuging, se transmite los datos sensados en el siguiente formanto:

```
id: 1
rain: 50
gasppm: 950
dht: {t:23.5, h:50}
gps: {la:-12.01223, h:-77.04325}
lx: 123.3
```

## Puerto Serial1
Dedicada a transmitir tramas definidas en la siguiente sección a nivel bytes mediante un XBee.
Estas tipo de tramas están pensadas para reducir el procesamiento Siser Master (Raspberry Pi), reducir el ancho de banda necesario y promover una mayor rapidez de transferencia de datos.

## Puerto Serial2
Responsable de la lectura del GPS para adquirir la latitud y longitud de cada Siser.

## Puerto Serial3
Conectado a un módulo HC-05 Bluetooth que operar como maestro o como esclavo, sin embargo trabaja en modo esclavo.
Opera de la misma manera que el pruerto Serial0 y muestra el mismo mensaje para mostrar la información mediante una tablet o smartphone sin necesidad de una conexión serial.

# Trama de comunicación

La trama de comunicación envía la trama cruda tal como es guardada en memoria en formato little endian con una cabecera (header) "OPEN" y pie (footer) "CHAU" con una trama de comunicación.
El formato de la trama es la siguiente:

- HEAD:  byte[4] <--> 4 bytes
- ID:    uint8 <--> 1 bytes
- Rain:  uint8 <--> 1 bytes
- MQ2:   uint16 <--> 2 bytes
- DHT22: [float32,float32] <--> 8 bytes
- GPS:   [float32,float32] <--> 8 bytes
- lx:   float32 <--> 4 bytes
- FOOT:  byte[4] <--> 4 bytes

# TODO
En futuros trabajos, se plantear preparar el programa para trabajar un hilo en background que se encargue de la detección de rayos para generar alertas, sea de daño o de alerta temprana.
