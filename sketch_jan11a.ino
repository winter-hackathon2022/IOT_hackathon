#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "index.h"

char result = '0';

// Set WiFi credentials
#define WIFI_SSID "bssm_free"
#define WIFI_PASS "bssm_free"

// Create a new web server
ESP8266WebServer webserver(80);

// Handle Root
void handleRoot() {
  String s = MAIN_page;
  webserver.send(200, "text/html", s);
}

void handleLed() {
  switch (result)
  {
    case '0':
      webserver.send(200, "text/plane", "OFF");
      break;
    case '1':
      webserver.send(200, "text/plane", "ON");
  }
}

void setup()
{
  // Setup serial port
  Serial.begin(115200);
  Serial.println();

  //Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  // WiFi Connected
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Start Web Server
  webserver.on("/", handleRoot);
  webserver.on("/setLed", handleLed);
  webserver.begin();

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
}

// Listen for HTTP requests
void loop(void) {
  if (Serial.available() > 0) {
    result = Serial.read();
  }
  switch (result)
  {
    case '0':
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      break;
    case '1':
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      break;
  }
  webserver.handleClient();
}
