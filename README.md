--------------------------------
# Casa Inteligente
--------------------------------
### Autores:
- González Alcaraz Hernán Arturo
- Nava Torres Juana Cinthia Lizbeth
- Padilla Guerrero Paul Adrian
### Propósito del proyecto
Crear un prototipo de vivienda que cuente con un sistema de automatización avanzado que permite 
controlar distintas funciones de seguridad, luminosidad y temperatura de manera cómoda y sofisticada.
### Solución
Mediante la aplicacion web para el control de la casa se podra activar la alarma, cuando esta se encuentra activada y 
alguien abre la puerta se envia esta informacion por la pagina web y además se activa una alarma. 
(Esto se controla con la ayuda de un interruptor magnetico.)
Cuando no hay luz solar se encienden las luces de la habitación principal. (Se controla con una fotoresistencia.)
Cuando la temperatura dentro de la cocina es muy elevada se enciende un ventilador que ayuda a bajar la temperatura
dentro de la habitacion, también se cotrola la humedad. (Sensor de temperatura y sensor de humedad).

Dichas acciones se realizan automaticamente con las mediciones de los diferentes sensores pero también se pueden controlar
por la aplicación web.
Toda la informacion de la casa inteligente se puede consultar desde el sitio web.


### Materiales 
#### Hardware
- Protoboard
- Arduino Uno
- Placa shield ethernet w5100
- 1 Push-Button
- 1 Sensor de humedad dht11 (Temperatura y humedad)
- 1 Fotoresistencia
- 1 Interruptor Magnetico (Magnetic reed)
- 3 Leds verdes
- Resistencias de diferentes tamaños
- 1 buzzer
- 1 Motor a pasos 
- Cables Dupont(Jumpers) macho macho
- Cables Dupont(Jumpers) hembra macho
- Cable ethernet con conectores RJ-45
#### Software
- Arduino IDE
- Ubuntu 16.04

### Librerias
- SPI.h
- Ethernet.h
- DHT
### Conectividad
Soporta IPv4 y los protocolos TCP/UDP/HTTP/FTP

### Lenguaje de Boceto
![Imagen](https://github.com/CinthiaNT/SmartHouse/blob/master/SmartHouse/src/EsquemaGeneral/Diapositiva1.JPG)

## Diagrama de conexion de sensores
#### Sensor de Temperatura y humedad
![Imagen](https://github.com/CinthiaNT/SmartHouse/blob/master/SmartHouse/src/EsquemaGeneral/dht11.jpg)
#### Sensor de Luminosidad
![Imagen](https://github.com/CinthiaNT/SmartHouse/blob/master/SmartHouse/src/EsquemaGeneral/fotoresistencia.jpg)
#### Interruptor magnetico
![Imagen](https://github.com/CinthiaNT/SmartHouse/blob/master/SmartHouse/src/EsquemaGeneral/interruptormagnetico.jpg)
### Placa shield ethernet w5100
![Imagen](https://github.com/CinthiaNT/SmartHouse/blob/master/SmartHouse/src/EsquemaGeneral/esquema.jpg)

