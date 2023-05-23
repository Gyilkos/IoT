#include <WiFi.h>

#define LED 23      // GPIO23
  
const char* ssid = "UCN-V3";
const char* password = "a0b1c2d3e4f5";

WiFiServer servidor(80);      // creo servidor web en puerto 80

String estado = "off";

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.begin(115200);
  delay(2000);
  WiFi.begin(ssid, password);
  Serial.print("Conectando a " + String(ssid) + "...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.print(" Conectado. IP: ");
  Serial.println(WiFi.localIP());

  servidor.begin();
  Serial.println("Servidor Web iniciado.");
}
  
void loop() {
  WiFiClient cliente = servidor.available();  // recibe las conexiones de los clientes

  if (cliente) {                              // si hay un cliente
    Serial.println("Nuevo cliente.");
    String linea = "";

    while (cliente.connected()) {             // cliente conectado
      if (cliente.available()) {              // datos disponibles para ser leidos
        char c = cliente.read();              // lectura de byte
        Serial.write(c);                      // muestro los datos

        if (c == '\n') {                      // si el byte es un caracter de nuevo salto de linea
          if (linea.length() == 0) {          // si no hay caracteres, entonces lanzo html
            cliente.println("HTTP/1.1 200 OK");
            cliente.println("Content-type:text/html");
            cliente.println("Connection: close");
            cliente.println();

            cliente.println("<html>");
            cliente.println("<head>");
            cliente.println("<title>Servidor Web ESP32</title>");
            cliente.println("<style>html {font-family: Arial; text-align: center}</style>");
            cliente.println("</head>");
            cliente.println("<body>");
            cliente.println("<h1>Servidor Web ESP32</h1>");
            if (estado == "off") {
              cliente.println("<p>Estado LED: Apagado</p>");
            } else {
              cliente.println("<p>Estado LED: Encendido</p>");
            }
            cliente.println("<p><a href='/on'><button style='height:50px; width:100px; cursor:hand; background-color:#00ff00; font-size:20px'>ON</button></a></p>");
            cliente.println("<p><a href='/off'><button style='height:50px; width:100px; cursor:hand; background-color:#ff0000; font-size:20px'>OFF</button></a></p>");
            cliente.println("</body>");
            cliente.println("</html>");
            cliente.println();

            break;
          } else {
            linea = "";
          }
        } else if (c != '\r') {       // si no hay retorno de carro
          linea += c;                 // agrega al final de la linea
        }
            
        // revisando los datos recibidos del url
        if (linea.indexOf("GET /on") != -1) {
          digitalWrite(LED, HIGH);
          estado = "on";
        }

        if (linea.indexOf("GET /off") != -1) {
          digitalWrite(LED, LOW);
          estado = "off";
        }
      }
    }
    cliente.stop();
    Serial.println("Cliente desconectado.");
  }
}
