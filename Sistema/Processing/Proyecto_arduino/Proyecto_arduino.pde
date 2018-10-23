import controlP5.*;
import processing.serial.*;

ControlP5 cp5;
Serial port;
Button agregar, enviar;
int posicionY = 20;
int cantElementos = 1;
Textfield campos[] = new Textfield[15];
Button btnEliminar[] = new Button[15];
Textlabel lblTexto[] = new Textlabel[15];
byte posicion=0;


void elementos(int posicion, String textfield,int itemV){
  cp5 = new ControlP5(this);
  PFont font = createFont("arial",14);
  
  lblTexto[itemV-1] = cp5.addTextlabel(" "+itemV)
      .setText(""+itemV)
      .setPosition(200,posicion+2)
      .setColorValue(255)
      .setFont(font)
      ;
  
  campos[itemV-1] = cp5.addTextfield("")
     .setValue(""+textfield) 
     .setPosition(230,posicion)
     .setSize(200,20)
     .setFont(font)
     .setFocus(true)
     .setColor(color(255,255,255))
     ;

  btnEliminar[itemV-1] = cp5.addButton(" X")
     .setValue(0)
     .setPosition(440,posicion)
     .setSize(20,20)
     ;
}

void setup() {
  size(700,400);
  ControlP5 cp5v2 = new ControlP5(this);
  
  agregar = cp5v2.addButton("Agregar")
     .setValue(0)
     .setPosition(120,350)
     .setSize(200,20)
     ;
     
  enviar = cp5v2.addButton("Enviar")
     .setValue(1)
     .setPosition(370,350)
     .setSize(200,20)
     ;
  
  elementos(posicionY,"BIENVENIDOS",cantElementos);
     
  println(Serial.list());
  port = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
  background(0);
  fill(255);
  
  if(agregar.isPressed()){
    if(cantElementos < 15){
      posicionY += 21;
      cantElementos++;
      println("Presionado");
      elementos(posicionY,"",cantElementos);
      delay(500);
    }else{
      println("No puede haber más de 15 Textfields");
      delay(500);
    }
  }
  
  if(enviar.isPressed()){
    for(int i = 0; i < cantElementos; i++){
      if(campos[i].isFocus()){
        port.write(campos[i].getText());
        delay(500);
      }
    }
  }
  
  for(int j= 0;j<cantElementos;j++){
    if(btnEliminar[j].isPressed()){
      btnEliminar[j].remove();
      campos[j].remove();
      lblTexto[j].remove();
    }
  }
}
