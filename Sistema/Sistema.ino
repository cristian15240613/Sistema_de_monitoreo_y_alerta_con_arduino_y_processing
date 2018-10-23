#include <Wire.h>               // Librería wire para comunicación de arduino con dispositivos I2C
#include <LiquidCrystal_I2C.h>  // Librería para controlar el LCD con el dispositivo I2C

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F, 16, 2); //

void setup() {
  Serial.begin(9600);

  // Inicializar el LCD
  lcd.init();

  //Encender la luz de fondo.
  lcd.backlight();

  // Escribimos el Mensaje Inicial en el LCD.
  lcd.print("Espero Mensaje");

}

void loop() {

  if (Serial.available()) {   // Si hay actividad en el puerto serial

    while (Serial.available() > 0 ) {     // Si hay algun mensaje en el puerto serial
      String textoSerie = Serial.readString();                        // Texto recibido por el puerto serial
      int tamaTexto = textoSerie.length();                            // Tamaño de todo el texto
      
      String mensajeSerial = textoSerie.substring(0,(tamaTexto-17));  // Solo el mensaje de todo el texto (17 son los caracteres que ocupa la fecha y hora)
      String textoFechaHora = textoSerie.substring(tamaTexto-17);     // Solo la fecha y hora en que se emitió el mensaje
      
      // Mostramos salida del texto por la izquierda
      for(int i=1; i<=mensajeSerial.length() ; i++){
        
        String texto = mensajeSerial.substring(i-1);    // Parte el string quitando un caracter cada vez que hace el ciclo
 
        //Situamos el cursor
        lcd.setCursor(0, 0);
 
        // Escribimos el texto
        lcd.print(texto);

        // Poner el cursero de texto en el segundo renglón del LCD
        lcd.setCursor(0,1);
        
        lcd.print(textoFechaHora);
        
        // Esperamos
        delay(300);
      }

      // Limpiamos la pantalla
      lcd.clear();
      // Volvemos a escribir el mensaje inicial
      lcd.print("Espero Mensaje");
    }
  }
}
