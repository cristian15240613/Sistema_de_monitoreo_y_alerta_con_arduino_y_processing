# Práctica 3

## Sistema de monitoreo y alerta con arduino y processing

###### Desarrollado por:
###### * Angel Christian Alvarez Trujillo
###### * Jessica Irais Nicasio Hernandez
###### * Sandra Guadalupe Mireles Tovar

<center><b>
Tecnológico Nacional de México <br>
Instituto Tecnológico de León <br>
Ingeniería en Sistemas Computacionales <br>
Sistemas programables <br>
</b></center>

### Material utilizado

* 2 LCD Display 16x2.
* 2 Arduino UNO.
* Jumpers Macho-Macho.
* Jumpers Hermbra-Macho.
* 2 Protoboard.
* 1 I2C.
* 1 Teclado matricial.
* 1 Sensor de humedad y temperatura DTH11.
* 1 Foto-resistencia.

### Software utilizado

* Arduino IDE.
* Processing IDE.
* Fritzing.
* Kubuntu 18.04.
* Git.
* Github.

## Librerias utilizadas

* LiquidCrystal_I2C
* Wire.h

## Contenido del repositorio

* Código de programas de arduino.
* Código de interfaz de software.
* Diagramas.
* README.me (este archivo).

## Funcionamiento

El circuito en el primer arduino siempre esta en espera de un mensaje via serial, cuando recibe el mensaje este lo imprime en la primera fila del display, mientras que en la segunda fila muestra la fecha y hora en que se emitió el mensaje en formato "dd/mm/aa hh:mm" , en el segundo arduino que contiene los sensores de humedad y temperatura y la foto-resistencia se encuentra un teclado matricial el cual el arduino espera que preciones una tecla para ver cualquier estado de algun sensor.