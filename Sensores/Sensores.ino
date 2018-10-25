// Libreria para Sensor DHT
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

// Teclado
// Salidas digitales
#define pinF1 6   // Fila 1
#define pinC1 7   // Columna 1 = numero 1
#define pinC2 10  // Columna 2 = numero 2
#define pinC3 13  // Columna 3 = numero 3

void setup (){
  
  Serial.begin(9600); //Inicia comunicación serial

//luz
  pinMode(LUZ,OUTPUT); //Configurar el pin 3 como una salida de PWM

// funcion dht
  dht.begin(); 

// función lcd
  lcd.begin(16, 2);

// teclado
  pinMode(pinF1,OUTPUT);  // Fila 1
  pinMode(pinC1,INPUT_PULLUP);  //Columna 1, número = 1
  pinMode(pinC2,INPUT_PULLUP);  //Columna 2, número = 2
  pinMode(pinC3,INPUT_PULLUP);  //Columna 3, número = 3

   
}

void loop (){
    
// Se llaman para que los sensores comiencen su funcionamiento
  Luminosidad();  
  Humedad();

// Método del teclado despues de que el sensor comience
  Teclado();
   
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
  temp = dht.readTemperature();   // lee humedad

  Serial.print("Temperatura: ");
  Serial.println(temp);

  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println("%");

  delay(500);
}

void Teclado (){
  lcd.home(); // Iniciamos el curso del lcd en el inicio
  
  // Menu de selección
  lcd.print("Luz(1)");    
  lcd.print("   Temp(2)");
  lcd.setCursor(0,1);
  lcd.print("   Humedad(3)");
  
  
  digitalWrite(pinF1,LOW);  // detecta fila a usar

  // Al seleccionar 1, 2 o 3 imprime el valor de luz, temperatura o humedad respectivamente.
  // Numero 1
  if(digitalRead(pinC1)==LOW){  // luminosidad
      
      lcd.clear(); // limpia primero la pantalla
      lcd.print("  Luminosidad:");
      lcd.setCursor(0,1);     // (columna 0, renglon 1)
      lcd.print("  ");
      lcd.print(cant_luz);   // imprime valor en la pantalla
      lcd.print(" cd ");
      delay(3000);
    
    // numero 2
  }else  if(digitalRead(pinC2)==LOW){ // Temperatura

      lcd.clear(); // limpia primero la pantalla
      lcd.print("  Temperatura: ");
      lcd.setCursor(0,1); // (columna 0, renglon 1)
      lcd.print("    ");
      lcd.print(temp); // imprime valor en la pantalla
      lcd.print("º");  
      delay(3000);    
    
    // numero 3
  }else  if(digitalRead(pinC3)==LOW){ // Humedad

    lcd.clear();  // limpia primero la pantalla
    lcd.print("    Humedad");
    lcd.setCursor(0,1); // (columna 0, renglon 1)
    lcd.print("      ");
    lcd.print(humedad);   // imprime valor en la pantalla
    lcd.print("%");      
    delay(3000);
    
  }
}
