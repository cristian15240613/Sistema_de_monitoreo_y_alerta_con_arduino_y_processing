#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int led = 3;

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas

LiquidCrystal_I2C lcd(0x3F,16,2);

int pinR = 13;
int pinV = 12;
int pinA = 11;

void setup() {
  Serial.begin(9600);
  
  pinMode(pinR, OUTPUT);
  pinMode(pinV, OUTPUT);
  pinMode(pinA, OUTPUT);  

  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  
  // Escribimos el Mensaje en el LCD.
  lcd.print("Hola Mundo");

}

void loop() {
     // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 1);
   // Escribimos el número de segundos trascurridos
  lcd.print(millis()/1000);
  lcd.print(" Segundos");
  
  delay(100);
 
  if(Serial.available()>0)//Si el Arduino recibe datos a través del puerto serie
  {
    byte dato = Serial.read(); //Los almacena en la variable "dato"
    lcd.setCursor(0,0);
    lcd.print(dato);
  }

  colorRGB(255, 135, 0); 
}

void colorRGB (int r, int v, int a){
  #ifdef COMMON_ANODE
    r = 255 - r;
    v = 255 - v;
    a = 255 - a;
  #endif
  analogWrite(pinR, r);
  analogWrite(pinV, v);
  analogWrite(pinA, a);
  
}
