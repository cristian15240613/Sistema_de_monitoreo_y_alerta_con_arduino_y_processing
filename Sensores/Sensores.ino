 // luminosidad
#define LUZ 9
int cant_luz;
int ldr;

void setup (){
//luz
  pinMode(LUZ,OUTPUT); //Configurar el pin 3 como una salida de PWM
   
}

void loop (){
    
  Luminosidad();

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


}
