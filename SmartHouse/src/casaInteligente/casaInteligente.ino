/*
 *Instituto Tecnologico de León
 *Sistemas Programables
 *    Martes y Jueves 7:00-8:40
 *Autores: González Alcaraz Hernán Arturo 
 *         Nava Torres Juaan Cinthia Lizbeth
 *         Padilla Guerrero Paul Adrian 
 *"Casa Inteligente"
 *
 */

/*
 * Se incluyen librerias necesarias
 * SPI. Conexion del puerto spi de arduino con placa shield 
 * Ethernet. Conexion de placa shield y con la pagina de internet 
 * DHT. Funcionamiento de los sensores de temperatura y luminosidad
 * Stepper. Funcionamineto del motor a pasas que simula ventilador
 * 
 * */
#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>
#include <Stepper.h>
/*
 * Se definen los distitos componentes en los pines
 * Interruptor Magnetico. Pin 15
 * Bocina. Pin 2
 * Led 1. Pin 9
 * Led 2.Pin 3
 * Led 3.Pin 4
 * Fotoresistencia. Pin analogico A0
 */
#define reed 15
#define bocina 2
#define led1 9
#define led2 3
#define led3 4
#define lumi A0

/*
 * Se asigna una direccion mac a la placa shield
 * Se asigna una direccion IP a la placa shield
 * Se asigna el puerto 80 para el servidor http 
 * que escucha una peticion hecha por el cliente
 * */
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
EthernetServer server(80);
//lee los caracteres de una secuencia en una cadena.
String readString=String(30); 
//Variable para almacenar valor de la temperatura
float t = 0;
//Variable parfa almacenar valor de la humedad
float h = 0;
//Se asigna el puerto 16 para el sensor de temperatura
DHT dht(16, DHT11);
//Resistencia a la oscuridad en KΩ
const long A = 1000;
//Resistencia a la luz (10 Lux) en KΩ
const int B = 15;
//Resistencia calibracion en KΩ
const int Rc = 10;
//Variable para almacenar valor de luminosidad
int V;
//Variable para almacenar valor de luminosidad
int i;
boolean sensorLumi = true;
boolean alarma = false;
//Se inicializa interuptor magnetico en Low 
int reedSwitch = LOW;
/*Motor a pasos. Se asignan el numero de pasos que dara en una vuelta, y los puertos
 * en los que se conecto. 
 */
Stepper vuelta(2048,5,7,6,8);
int length = 26;
//Variables utilizadas para el sonido que emitira la bocina 
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
int tempo = 150;

void setup()
{
  Serial.begin(9600);
  dht.begin();
  //Velocidad del motor a pasos
  vuelta.setSpeed(10);
  pinMode(led1, OUTPUT);//Pin del led como salida
  pinMode(led2, OUTPUT);//Pin del led como salida
  pinMode(led3, OUTPUT);//Pin del led como salida
  pinMode(reed, INPUT_PULLUP);//Se configura pin como entrada con resistencia pull-up interna para sensor magnetico
  pinMode(bocina,OUTPUT); //Pin de bocina como salida
  Ethernet.begin(mac, ip); //Se le asigna la direccion mac e ip 
  server.begin();
  //sensorLumi = true;
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}
 
void loop()
{
  //Cliente de ethernet
  EthernetClient client = server.available();
  //Lectura de temperatura
  t = dht.readTemperature();
  //Lectura de Humedad
  h = dht.readHumidity(); 
  //Lectura de luminosidad
  V = analogRead(lumi);
  i = ((long)(1024 - V) * A * 10) / ((long)B * Rc * V);
  bool currentLineIsBlank;
  //Si el cliente esta disponible comienza la lectura
  if (client)
  {
    Serial.println("new client");
    currentLineIsBlank = true;
    String cadena = "";
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        //Serial.write(c);
       if(readString.length()<30) {
          readString.concat(c);
          //Cliente conectado
          //Leemos petición HTTP caracter a caracter
          //Almacenar los caracteres en la variable readString
          } 
        
        // Al recibir linea en blanco, servir página a cliente
        if (c == '\n' && currentLineIsBlank)
        {

          int LED = readString.indexOf("LED="); 
          if(readString.substring(LED,LED+5)=="LED=T") {
             sensorLumi= false;
             digitalWrite(led1,HIGH);
             digitalWrite(led2,HIGH);
             digitalWrite(led3,HIGH);
            } else if (readString.substring(LED,LED+5)=="LED=F") {
               sensorLumi= false;
                digitalWrite(led1,LOW);
                digitalWrite(led2,LOW);
                digitalWrite(led3,LOW);
            }else if (readString.substring(LED,LED+5)=="LED=L") {
               sensorLumi= true;
            }else if(readString.substring(LED,LED+5)=="LED=A"){
               alarma = true;
            }else if(readString.substring(LED,LED+5)=="LED=P"){
              alarma = false;
            }
            client.println(F("HTTP/1.1 200 OK\nContent-Type: text/html"));
            client.println();
            //Se crea la pagina web con html basico
            //Titulo del sitio web
            client.println(F("<html>\n<head>\n<title>Casa Inteligente</title>\n</head>\n<body>"));
            client.println(F("<div style='text-align:center;'>"));

          //Imprime valor de sensor de temperatura
            client.println(F("<h2>Sensor de temperatura</h2>"));
            client.println("TEMPERATURA");
            client.println(" = ");
            client.println(t);
            client.print(F("<br />"));
            client.print(F("<br />"));
           //Imprime valor de sensor de humedad
            client.println(F("<h2>Sensor de humedad</h2>"));
            client.print("HUMEDAD");
            client.print(" = ");
            client.print(h);
            client.println(F("<br />"));
            client.println("<br /><br />");
            //Imprime valor de fotoresistencia para el control de luz 
            client.println(F("<h2>Sensor de luminosidad</h2>"));
            client.print("Lumenes");
            client.print(" = ");
            client.print(i);
            client.println(F("<br />"));
            client.println(F("<br />"));

            //Control de luces de manera manual
            //Se tiene 3 botones
            client.println(F("<h2>Luces</h2>"));
            //Prende las luces de manera manual
            client.println("<input type=submit value=ON style=width:200px;height:75px onClick=location.href='./?LED=T\'>"); 
            client.println(F("  "));
            //Apaga las luces de manera manual
            client.println("<input type=submit value=OFF style=width:200px;height:75px onClick=location.href='./?LED=F\'>");
            client.println(F("  "));
            //Reestablece al funcionamiento de manera automatica
            client.println("<input type=submit value=ReestablecerSensor style=width:200px;height:75px onClick=location.href='./?LED=L\'>"); 

            //Control para activar/desactivar alarma
            
            client.println(F("<h2>Alarma</h2>"));
            //Se activa la alarma 
            client.println("<input type=submit value=ON style=width:200px;height:75px onClick=location.href='./?LED=A\'>"); 
            client.println(F("  "));
            //Se desactiva la alarma
            client.println("<input type=submit value=OFF style=width:200px;height:75px onClick=location.href='./?LED=P\'>");
            client.println(F("<br />"));
            client.println(F("<br />"));
            client.println(F("<br />"));
            //Actualiza los valores de la informacion mostrada en el sitio web
            client.println(F("<a href='http://192.168.1.177'>Refrescar</a>"));
            client.println(F("</div>\n</body></html>"));
            break;
        }
        if (c == '\n') 
        {
          currentLineIsBlank = true;
        }
        else if (c != '\r') 
        {
          currentLineIsBlank = false;
        }
      }
    }
    client.print(sensorLumi);
    delay(1);
    //Se termina el modo cliente
    client.stop();
    readString="";
  } 
  if(sensorLumi == 1){
    luces();
  }
  ventilador();
  if(alarma == 1){
    alarmaON();
  }
  
  }
//Metodo para el funcionamiento de las luces.
void luces(){
   if((i > 10)){
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      }else{
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        digitalWrite(led3,HIGH); 
      }
}

//Metodo para el funcionamiento del motor a pasos que simula
//el ventilador
void ventilador(){
  t = dht.readTemperature();
  while(t>=25){
    t = dht.readTemperature();
    Serial.print(t);
     vuelta.step(2048);
     if(t<25){
      break;
     }
  }
}

//Metodo paa el funcionamiento de bocina que simulara una alarma
void alarmaON(){
  reedSwitch= digitalRead(reed);
  while(reedSwitch == HIGH){
    sonido();    // esperar 20 segundos
    reedSwitch= digitalRead(reed);
  }
}

/*Metodos utilizados para que la bocina
 *reproduzca una melodia
 */
void sonido(){ 
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo);
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    //Pausa entre las notas
    delay(tempo / 2); 
  }
}
void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
      digitalWrite(bocina, HIGH);
      delayMicroseconds(tone);
      digitalWrite(bocina, LOW);
      delayMicroseconds(tone);    
    }
}
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
 
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
