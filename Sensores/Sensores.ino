// libreria para senssor DHT
#include <DHT.h>

 // luminosidad
#define LUZ 9
int cant_luz;
int ldr;

// Teperatura y humedad
int SENSOR = 8;
int temp, humedad;

//id del sensor, se especifica el tipo de sensor a usar, puede ser DHT11 o DHT22
DHT dht (SENSOR, DHT11); 

void setup (){
// Comunicación serial para visualizar valores
  Serial.begin(9600); 
 
//luz
  pinMode(LUZ,OUTPUT); //Configurar el pin 3 como una salida de PWM

// Inicia funcion sensor DHT
  dht.begin(); 
   
}

void loop (){
    
  Luminosidad();
  HumedadTemperatura();
  
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

void HumedadTemperatura (){
  // DHT -> sensor de temperatura y humedad
  
  humedad = dht.readHumidity();  // lee humedad
  temp = dht.readTemperature(); // lee temperatura

  Serial.print("Temperatura: ");
  Serial.println(temp);

  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println("%");

  delay(500);
}

