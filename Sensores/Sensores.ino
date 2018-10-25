// Libreria para sensor DHT
#include <DHT.h>

// Libreria para Display LCD
#include  <LiquidCrystal.h>

 // luminosidad
#define LUZ 9
int cant_luz;
int ldr;

// Teperatura y humedad
int SENSOR = 8;
int temp, humedad;

DHT dht (SENSOR, DHT11); //id del sensor. Puede ser DHT11 o DHT22

// Pantalla
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // pantalla

void setup (){
  
  Serial.begin(9600); //Inicia comunicación serial

//luz
  pinMode(LUZ,OUTPUT); //Configurar el pin 3 como una salida de PWM

// funcion dht
  dht.begin(); 

// función lcd. (numero_columnas, numero_filas)
  lcd.begin(16, 2);
   
}

void loop (){
    
  //Luminosidad();  // Al contar con el display lcd los valores se imprimen dentro de ese método
  //Humedad();
  Display();  
  
}

void Luminosidad (){
 /*
  Enciende un LED de manera proporcional de
  acuerdo a la cantidad de luz que incida en una
  fotocelda.
*/
  ldr = analogRead(A0);

//Verifica el valor máximo y realizar una conversión
  cant_luz = 700 - ldr;

//Condicional para establecer un valor absoluto
  if ( cant_luz < 0)
    cant_luz = cant_luz * -1; //Multiplicar por -1 porque es negativo
  //Imprimir datos del valor de la lectura análoga de la fotocelda
 
    Serial.print("LDR : ");
    Serial.print(ldr);
    Serial.println("");
  
  //Imprimir datos del valor de la conversión
    Serial.print("Luz : ");
    Serial.print(cant_luz);
    Serial.println("");
  
  //Escritura análoga de PWM en el LED de acuerdo a la conversión
  analogWrite(LUZ, cant_luz);
  delay(300);
  //Retardo para datos en la consola

}

void Humedad (){
  humedad = dht.readHumidity();  // lee temperatura
  temp = dht.readTemperature();

  Serial.print("Temperatura: ");
  Serial.println(temp);

  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println("%");

  delay(500);
}

void Display (){
// Inicia el mensaje al  inicio de la pantalla
  lcd.home();

// Impresion Lumosidad
  lcd.print(" Luz:");
  lcd.print(cant_luz);
  
// Impresion Temperatura
  lcd.print("Temperatura: ");
  lcd.print(temp);
  lcd.print("º");

// Impresion Humedad 
  lcd.setCursor(0,1); // columna 0, renglon 1
  lcd.print("Hum.:");
  lcd.print(humedad);
  lcd.print("%");

  
}



