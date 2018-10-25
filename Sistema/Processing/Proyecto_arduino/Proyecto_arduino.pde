import controlP5.*;                        // importamos la librería que propocriona elementos para contruir una interfaz gráfica
import processing.serial.*;                // importamos la librería que permite enviar/recibir datos por el puerto serial

ControlP5 cp5;                             // Creamos un objeto de tipo ControlP5
Serial port;                               // Creamos un objeto Serial de nombre port (Encargado de enviar y recibir datos)

Button agregar, enviar;                    // Se crean dos botones, agregar (Agrega una nueva fila) y enviar (enviar los datos por el puerto)
Textlabel lblTexto[] = new Textlabel[15];  // Se define un arreglo de máximo 15 etiquetas
Textfield campos[] = new Textfield[15];    // Se define un arreglo de máximo 15 campos de texto
Button btnEliminar[] = new Button[15];     // Se define un arreglo de máximo 15 botones (Eliminar)
Textlabel error;

int espacio = 20, posicionX;               // Se crean las variables espacio (separación de filas) y posicionX (indica la posición en X de cada campo de texto)
int cantElementos = 1;                     // Variable que indica la cantidad de filas (etiqueta-campoDeTexto-botonEliminar) que se muestran en pantalla

/* Método que crea una nueva fila al presionar el botón de "agregar",  
   Parametros:
     - posicion indica la posición de cada elemento de la fila
     - textfield indica el contenido que tendrá el campo de texto al momento de ser creado
     - intemV define un nombre para cada elemento y les asigna un índice en el array
*/
void elementos(int posicion, String textfield, int itemV) {
  cp5 = new ControlP5(this);                        // Se define la nueva instancia de ControlP5 para crear controles en la ventana
  PFont font = createFont("arial", 14);             // Se define la fuente a utilizar

  /* Se agrega una etiqueta a la ventana */
  lblTexto[itemV-1] = cp5.addTextlabel(" "+itemV)   
    .setText(""+itemV)
    .setPosition(200, posicion+2)
    .setColorValue(255)
    .setFont(font)
    ;

  /* Se agrega un campo de texto a la ventana */
  campos[itemV-1] = cp5.addTextfield("")
    .setValue(""+textfield) 
    .setPosition(230, posicion)
    .setSize(200, 20)
    .setFont(font)
    .setFocus(true)
    .setColor(color(255, 255, 255))
    .setColorCursor(color(255, 255, 255))
    ;

  /* Se agrega un botón para eliminar la fila  */
  btnEliminar[itemV-1] = cp5.addButton(" X")
    .setValue(0)
    .setPosition(440, posicion)
    .setSize(20, 20)
    ;
}

/* Método que permite obtener una cadena de texto con la fecha y hora actual en el formato de dd/mm/aa hh:mm */
String obtenerFechaHora() {
  int d = day();      // Valores de 1 a 31 (Día/s)
  int mo = month();   // Valores de 1 a 12 (Mes)
  int y = year();     // Valores de 2015, 2014, etc (Año)
  int h = hour();     // Valores de 0 a 23 (Hora)
  int mi = minute();  // Valores de 0 a 59 (Minutos)

  return " "+d+"/"+mo+"/"+y+" "+h+":"+mi+" ";
}

void setup() {
  size(700, 420);                           // Se muestra la ventana con un tamaño de 700 x 420 pixeles
  ControlP5 cp5v2 = new ControlP5(this);    // Se define la nueva instancia de ControlP5 para crear controles en la ventana
  
  /* Se crea un mensaje de error */
  error = cp5v2.addTextlabel("Error")
    .setText("El mensaje a enviar debe de ser menor a 123 caracteres")
    .setColorValue(0)
    .setFont(createFont("arial", 14))
    .setPosition(150,380);
    ;

  /* Se agrega el botón de "agregar" a la ventana */
  agregar = cp5v2.addButton("Agregar")
    .setValue(0)
    .setPosition(120, 350)
    .setSize(200, 20)
    ;

  /* Se agrega el botón de "enviar" a la ventana */
  enviar = cp5v2.addButton("Enviar")
    .setValue(1)
    .setPosition(370, 350)
    .setSize(200, 20)
    ;

  /* Se agrega un campo de texto por default */
  elementos(espacio, "BIENVENIDOS", cantElementos);

  //println(Serial.list());
  //port = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
  background(0);        // Se designa un colo de fondo negro  

  /* Se define la acción que se realizará al presionar el botón de "agregar" 
     Si la cantidad de filas en pantalla es menor a 15 entonces...
       - Se incrementa la cantidad de elementos en pantalla
       - Se define la nueva posición de los elementos en la fila
       - Se agrega una nueva fila
       - Espera de 500 milisegundos
  */
  if (agregar.isPressed()) {
    if (cantElementos < 15) {
      cantElementos++;
      posicionX = espacio*cantElementos;
      elementos(posicionX, "", cantElementos);
      delay(500);
    } else {
      println("No puede haber más de 15 Textfields");
      delay(500);
    }
  }

  /* Se define la acción que se realizará al presionar el botón de "enviar" 
     Se recorre la cantidad de campos de texto y si alguno tiene el foco (isfocus())
       - Se almacena el texto del campo para saber la cantidad de caracteres que lo componen
       - Si el tamaño del texto es mayor a 123 entonces...
         - El texto del campo se vuelve rojo
         - Se manda el mensaje de error
       - Si el tamaño del texto es menor a 123 entonces...
         - El texto del campo se vuelve blanco
         - El mensaje de error desaparece
         - Se envia el mensaje (mensaje de campo de texto + resultado de la función obtenerFechaHora()) por el puerto
  */
  if (enviar.isPressed()) {
    for (int i = 0; i < cantElementos; i++) {
      if (campos[i].isFocus()) {
        String texto = campos[i].getText();
        int tamano = texto.length()+1;
        if(tamano > 123){
          campos[i].setColor(color(255,0,0));
          error.setColorValue(255);
          delay(500);
        }else{
          campos[i].setColor(color(255,255,255));
          error.setColorValue(0);
          //println(campos[i].getText() + obtenerFechaHora());          
          port.write(campos[i].getText() + obtenerFechaHora());
          delay(500);
        }
      }
    }
  }

  /* Se define la acción que se realizará al presionar el botón de "Eliminar" para cada fila 
     Se recorre la cantidad de filas en pantalla
     Si algún botón de eliminar es presionado...
       - Se eliminan todos los elementos de la fila correspondiente
       - Se decrementa el contador de elementos en pantalla
  */
  for (int j= 0; j<cantElementos; j++) {
    if (btnEliminar[j].isPressed()) {
      btnEliminar[j].remove();
      campos[j].remove();
      lblTexto[j].remove();
      cantElementos--;
    }
  }
}
