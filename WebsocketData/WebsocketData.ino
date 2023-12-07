#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Adafruit_BMP085.h>
#include <Ticker.h>

Ticker timer;
Adafruit_BMP085 bmp;

char* ssid = "Guenther-Home";
char* password = "marina2004";

ESP8266WebServer server;

char webpage[] PROGMEM = R"=====(
<html>
<head></head>
<body>
<div>
<canvas id="line-chart" width="800" height="450"></canvas>
</div>
</body>
</html>
)=====";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("start ...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send_P(200, "text/html", webpage);
  });
  server.begin();

  bmp.begin();
  timer.attach(5, getData);
}

void loop() {
}

void getData() {
  Serial.println(bmp.readTemperature());
}
