Proyecto SISER
==============

SIstema de SEnsado Remoto mediante protocolo DigiMesh con XBee (serial) con Golang en el servidor y Arduinos en los sistemas remotos.

Existen 2 tipos de Siser:

- Siser Master (maestro)
- Siser Slave (esclavo)

# Dispotivos Siser (Siser devices)

El sistema está pensado para conectar hasta 200 Siser Slave por cada Siser Master en una red DigiMesh.

## Siser Maestro
Compuesto por una Raspberry Pi que mediante protocolo serial está conectado a un Xbee que en modo broadcast pide

El Siser Master realiza la siguiente actividad:

```
1.  Por cada Siser del 1 al N: // N: N° de Siser Slave operando
2.    Envía orden por DigiMesh: {'R', 'E', 'Q', N}
3.    Espera por la trama de respuesta.
4.    Decofica la trama de bytes a JSON
5.    Envía el JSON por MQTT al tópico "incuba/peru"
6.    Vuelve al paso 1 hasta terminar su iteración.
7. Espera un periodo predefinido (minutos, horas o díás):
8. Vuelve al paso 1.
```

## Siser Slave
Compuesto por un Arduino Mega, XBee, sensores y GPS.
Es la unidad que sensa variables medioambientales de manera remota.

```
1. Espera un mensaje entrante {'R','E','Q',N}
2. Si el ID es igual N, va al paso 3, sino regresa al paso 1.
3. Lee los sensores y sistemas conectados a él.
4. Reporta trama de datos codificada.
5. Vuelve al paso 1.
```

Para más información sobre la configuración del Arduino y la trama datos revisar la siguiente [documentación](docs/arduino.md).

## Estructura DigiMesh
El protocolo DigiMesh se implementa en los transceptores XBee los cuales pueden tener una de dos configuraciones:

- xMaster:
  - Opera en modo broadcast al transmitir y al recibir tramas.
- xSlave:
  - Recibe los mensajes provenientes del xMaster a través de la Mesh.
  - Transimite los menssajes solo al xMaster a través de la Mesh.

# Estructura de carpetas del proyecto
El proyecto contiene la siguiente estructura de carpetas:

```
-- arduino    // Directorio reservado para proyectos Arduino.
 |- arduSiser // Carpeta del proyecto Siser Slave
-- config     // Paquete en Go para la configuración del Siser Master
 |- example   // Ejemplo de funcionamiento del paquete config.
-- dataframe  // Paquete para administrar la lectura de tramas recibidas desde los Siser Slave
 |- example   // Ejemplos de uso de las funcionalidades principales del paqueta.
-- doc        // Documentación básica del proyecto.
-- siserx     // Programa compilable para ejecutar en el Siser Master
```
