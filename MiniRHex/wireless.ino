/*
  Based on the "Web Server Access Point (AP) Mode with MKR WiFi 1010" tutorial
  https://docs.arduino.cc/tutorials/mkr-wifi-1010/web-server-ap-mode
*/

#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

char ssid[] = "minirhex";
WiFiServer server(80);
const int RED = 25;
const int GREEN = 26;
const int BLUE = 27;

void begin_wifi() {
  WiFiDrv::pinMode(GREEN, OUTPUT);
  WiFiDrv::pinMode(RED, OUTPUT);
  WiFiDrv::pinMode(BLUE, OUTPUT);
  WiFiDrv::analogWrite(GREEN, 0);
  WiFiDrv::analogWrite(RED, 0);
  WiFiDrv::analogWrite(BLUE, 0);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("No WiFi module present");
    return;
  }
  if (WiFi.firmwareVersion() < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the WiFi firmware");
  }
  WiFi.config(IPAddress(10, 0, 0, 1));
  if (WiFi.beginAP(ssid) != WL_AP_LISTENING) {
    Serial.println("Creating WiFi network failed");
    return;
  }
  server.begin();
  wifi = true;

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("Website: http://");
  Serial.println(WiFi.localIP());
}

char update_wifi() {
  if (WiFi.status() == WL_AP_LISTENING) {
    WiFiDrv::analogWrite(RED, 0);
    WiFiDrv::analogWrite(GREEN, 20);
    WiFiDrv::analogWrite(BLUE, 0);
  } else if (WiFi.status() == WL_AP_CONNECTED) {
    WiFiDrv::analogWrite(RED, 0);
    WiFiDrv::analogWrite(GREEN, 0);
    if (millis() % 250 > 125) {
      WiFiDrv::analogWrite(BLUE, 20);
    } else {
      WiFiDrv::analogWrite(BLUE, 0);
    }
  } else {
    WiFiDrv::analogWrite(RED, 20);
    WiFiDrv::analogWrite(GREEN, 0);
    WiFiDrv::analogWrite(BLUE, 0);
  }
  WiFiClient client = server.available();   // listen for incoming clients
  char output = 0;
  if (client) {                             // if you get a client,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        if (c == '\n') {                    // if the byte is a newline character
          if (currentLine.length() == 0) {  // empty line is end of http request
            display_website(client);        // display the webpage
            break;
          } else {
            currentLine = "";    // clear currentLine
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
          if (currentLine.substring(currentLine.length() - 6, currentLine.length() - 1) == "GET /") {
            output = currentLine[currentLine.length() - 1]; // return the command
          }
        }
      }
    }
    client.stop();                                   // close the connection
  }
  if (output == ' ') output = 'q';                   // space is also e-stop
  return (output);
}

void display_website(WiFiClient client) {
  // HTTP headers
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  // Controls
  client.print("<div style=\"display:inline-grid; grid-template-columns: 70px 70px 70px; grid-template-rows: 70px 70px 70px 70px;\">");
  client.print("<b></b><button onclick=\"window.location.href='/r';\">Run<br>(r)</button><b></b>");
  client.print("<b></b><button onclick=\"window.location.href='/w';\">Forward<br>(w)</button><b></b>");
  client.print("<button onclick=\"window.location.href='/a';\">Left<br>(a)</button>");
  client.print("<button onclick=\"window.location.href='/q';\">Stop<br>(space/q)</button>");
  client.print("<button onclick=\"window.location.href='/d';\">Right<br>(d)</button>");
  client.print("<b></b><button onclick=\"window.location.href='/s';\">Reverse<br>(s)</button>");
  client.print("</div><br><br>");

  // Key listener
  client.print("<script>");
  client.print("document.onkeydown = function(evt) {");
  client.print("evt = evt || window.event;");
  client.print("window.location.href = \"/\"+evt.key;");
  client.print("};");
  client.print("</script>");

  // Terminate http response
  client.println();
}
