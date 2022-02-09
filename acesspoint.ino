#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char *ssid ="Commande";
const char *password = "ma commande lampe ";

WiFiServer server(80);
 
// initialisation broche 
const int led = 2;
const int lampe1 = 4;
const int lampe2 = 5;
const int lampe3 = 12;
const int lampe4 = 14;


void setup() {
Serial.begin(115200);
// Initialize the output variables as outputs
pinMode(led, OUTPUT);
pinMode(lampe1, OUTPUT);
pinMode(lampe2, OUTPUT);
pinMode(lampe3, OUTPUT);
pinMode(lampe4, OUTPUT);


WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

 Serial.println("Server started");}
 
 void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

            client.print("Click <a href=\"/L1ON\">here</a> to turn ON the lampe1.<br>");
            client.print("Click <a href=\"/L1OFF\">here</a> to turn OFF the lampe1.<br>");

            client.print("Click <a href=\"/L2ON\">here</a> to turn ON the lampe2.<br>");
            client.print("Click <a href=\"/L2OFF\">here</a> to turn OFF the lampe2.<br>");

            client.print("Click <a href=\"/L3ON\">here</a> to turn ON the lampe3.<br>");
            client.print("Click <a href=\"/L3OFF\">here</a> to turn OFF the lampe3.<br>");

            client.print("Click <a href=\"/L4ON\">here</a> to turn ON the lampe4.<br>");
            client.print("Click <a href=\"/L4OFF\">here</a> to turn OFF the lampe4.<br>");

            client.print("Click <a href=\"/ALLON\">here</a> to turn ON the LEDON.<br>");
            client.print("Click <a href=\"/ALLOFF\">here</a> to turn OFF the LEDOFF.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led, LOW);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /L1ON")) {
          digitalWrite(lampe1, HIGH);                // GET /L turns the lampe1 on
        }
        if (currentLine.endsWith("GET /L1OFF")) {
          digitalWrite(lampe1, LOW);                // GET /L turns the lampe1 off
        }
        if (currentLine.endsWith("GET /L2ON")) {
          digitalWrite(lampe2, HIGH);                // GET /L turns the lampe2 on
        }
        if (currentLine.endsWith("GET /L2OFF")) {
          digitalWrite(lampe2, LOW);                // GET /L turns the lampe2 off
        }
        if (currentLine.endsWith("GET /L3ON")) {
          digitalWrite(lampe3, HIGH);                // GET /L turns the lampe3 on
        } 
        if (currentLine.endsWith("GET /L3OFF")) {
          digitalWrite(lampe3, LOW);                // GET /L turns the lampe3 off
        }
        if (currentLine.endsWith("GET /L4ON")) {
          digitalWrite(lampe4, HIGH);                // GET /L turns the lampe4 on
        } 
        if (currentLine.endsWith("GET /L4OFF")) {
          digitalWrite(lampe4, LOW);                // GET /L turns the lampe4 off
        }
        
        if (currentLine.endsWith("GET /ALLON")) {
          digitalWrite(led, HIGH);                // GET /L turns the LED off
          digitalWrite(lampe1, HIGH);
          digitalWrite(lampe2, HIGH); 
          digitalWrite(lampe3, HIGH);
          digitalWrite(lampe4, HIGH);
          
        }  
        if (currentLine.endsWith("GET /ALLOFF")) {
          digitalWrite(led, LOW);                // GET /L turns the LED off
          digitalWrite(lampe1, LOW);
          digitalWrite(lampe2, LOW); 
          digitalWrite(lampe3, LOW);
          digitalWrite(lampe4, LOW);
        }  
          
      }
    }
    // close the connection: 
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
