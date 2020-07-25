#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>

//Datos del WiFi
const char* ssid = "WLAN_0051";
const char* password = "H8V4U4LXZHRW";
//String server = "www.aprendiendoarduino.com"; //Tutorial where I got the code
String server = "pedidos-fuenca.000webhostapp.com";
//byte google[] = { 64, 233, 187, 99 };

WiFiClient client;

int const variables = 1;
String valuesVariables[variables];

String Num_Arduino = "1";
String Mensaje = "ESP8366";

/*
*******************************************
            SETUP
*******************************************
*/

void setup()
{
  Serial.begin(115200);
  delay(10);

  pinMode(0, OUTPUT);

  // Conectar WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nConnection successfully, my Ip is: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  
  pideDatos();
  //mandaDatosGET();
  mandaDatosPOST();
  
}

/*
*******************************************
            LOOP
*******************************************
*/


void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
      pideDatos();
      //mandaDatosGET();
      mandaDatosPOST();
      realizaAcciones();
      delay(1000);
    
  } else { Serial.println("WiFi not available");}

  delay(2000);
}


/*
*******************************************
            PIDE DATOS SERIAL
*******************************************
*/


void pideDatosSerial () { //Función bloqueante
  Num_Arduino = "";
  Mensaje = "";

  Serial.println("----------------------\r\nIntroduce el numero de Arduino");
  while (Serial.available() == 0) {
    //espero a introducir el número de Arduino
  }
  do {
    char caracter_leido = Serial.read();
    if ((caracter_leido > '0') && (caracter_leido <  'z'))  //solo admito caracteres ascii entre 0 y z
      Num_Arduino += caracter_leido;
    delay(5);
  }  while (Serial.available() > 0);

  Serial.println("Introduce el mensaje que quieres mandar");
  while (Serial.available() == 0) {
    //espero a introducir el número de Arduino
  }
  do {
    char caracter_leido = Serial.read();
    if ((caracter_leido > '0') && (caracter_leido <  'z'))  //solo admito caracteres ascii entre 0 y z
      Mensaje += caracter_leido;
    delay(5);
  }  while (Serial.available() > 0);

  Serial.println("Arduino: " + Num_Arduino + "\r\nMensaje: " + Mensaje);
}


/*
*******************************************
            PIDE DATOS SERVER
*******************************************
*/

void pideDatos () { //Función bloqueante
  String webString = "";
  String post_string = "arduino=" + Num_Arduino + "&mensaje=" + Mensaje + "&led=" + valuesVariables[0];


  Serial.println("Esperando datos...");
  if (client.connect(server, 80)) {
    client.println("POST /Send_to_Arduino.php  HTTP/1.1");
    client.println("Host: pedidos-fuenca.000webhostapp.com");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(post_string.length());
    client.println("");
    client.println(post_string);
    client.println("");
  }
  else {
    Serial.println("connection failed");
  }

  while (client.available() == 0) {
    //Waiting answer to server
  }

  if (client.available()) {
    Serial.println("Respuesta para obtener datos del Servidor---->");
    while (client.available()) {
      char c = client.read();
      webString += c;
      if (webString.lastIndexOf("0OK") > 0) {
        break;
      }
    }
    Serial.println(webString);

    asignaVariables(webString);
    
    client.stop();
  }
}

/*
*******************************************
      ASIGNAR VALORES DEL SERVIDOR
*******************************************
*/

void asignaVariables(String webString){

  int beginValues[variables+1] = {0,};
  int endValues[variables+1] = {0,};

  for(int i=0 ; webString.indexOf("[", (beginValues[i]+1)) > 0 ; i++){
    
    beginValues[i+1] = webString.indexOf("[", beginValues[i]+1);
    endValues[i+1] = webString.indexOf("]", endValues[i]+1);

    valuesVariables[i] = webString.substring(beginValues[i+1]+1, endValues[i+1]);

    //Serial.println(beginValues[i]);
    //Serial.println(endValues[i]);
    Serial.println(valuesVariables[i] + "\n");

  }

}

/*
*******************************************
            MANDA DATOS GET
*******************************************
*/

void mandaDatosGET() {  //Función bloqueante
  String webString = "";

  Serial.println("enviando mensaje... ");
  Serial.println("connecting to server...");
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.print("GET /GET_Request.php?arduino=");
    client.print(Num_Arduino);
    client.print("&mensaje=");
    client.print(Mensaje);
    client.println(" HTTP/1.1");
    client.println("Host: pedidos-fuenca.000webhostapp.com");
    client.println("Connection: close");
    client.println();
    Serial.print("Peticion enviada: ");
    Serial.print("GET /GET_Request.php?arduino=");
    Serial.print(Num_Arduino);
    Serial.print("&mensaje=");
    Serial.println(Mensaje);
  }
  else {
    Serial.println("connection failed");
  }

  while (client.available() == 0) {
    //Espero respuesta del servidor
  }

  if (client.available()) {
    Serial.println("Respuesta del Servidor---->");
    while (client.available()) {
      char c = client.read();
      webString += c;
    }
    Serial.println(webString);

    if (webString.lastIndexOf("OK") > 0)
      Serial.println("Datos enviados correctamente");
    else
      Serial.println("Error al enviar los datos");

    client.stop();
  }
}

/*
*******************************************
            MANDA DATOS POST
*******************************************
*/

void mandaDatosPOST() {  //Función bloqueante

  String webString = "";

  //String del post
  String post_string = "arduino=" + Num_Arduino + "&mensaje=" + Mensaje + "&led=" + valuesVariables[0];

  if (client.connect(server, 80)) {
    Serial.println("Enviando datos...");
    client.println("POST /POST_Request.php  HTTP/1.1");
    client.println("Host: pedidos-fuenca.000webhostapp.com");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(post_string.length());
    client.println("");
    client.println(post_string);
    client.println("");
  }
  else {
    Serial.println("connection failed");
  }

  while (client.available() == 0) {
    //Espero respuesta del servidor
  }

  if (client.available()) {
    Serial.println("Respuesta al envio de los dato al servidor---->");
    while (client.available()) {
      char c = client.read();
      webString += c;
    }
    Serial.println(webString);

    if (webString.lastIndexOf("OK") > 0) {
      Serial.println("Datos enviados correctamente");
    } else {
      Serial.println("Error al enviar los datos");
    }
    
    Serial.println("CERRAMOS CONEXION\n\n\n");
    client.stop();
  }
}

void realizaAcciones()
{
  if(valuesVariables[0] == "1")
  {
    digitalWrite(0, LOW);
  }

  if(valuesVariables[0] == "2")
  {
    digitalWrite(0, HIGH);
  }

}