#include <TFT_eSPI.h>

#include "WiFi.h"

#include "ESPAsyncWebServer.h"

#include <ArduinoJson.h>

const char * ssid = "ssid";
const char * password = "***";

TFT_eSPI tft = TFT_eSPI();
AsyncWebServer server(80);

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());
  tft.init();
  tft.begin();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setRotation(3);
  startServer();

}
void startServer() {
  server.on(
    "/post",
    HTTP_POST,
    [](AsyncWebServerRequest * request) {},
    NULL,
    [](AsyncWebServerRequest * request, uint8_t * data, size_t len, size_t index, size_t total) {
      printToscreen(data);
      request -> send(200);
    });
  server.begin();
}
void loop() {}

void printToscreen(uint8_t * data) {

  String received = String((const char * ) data);
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, received);
  JsonObject obj = doc.as < JsonObject > ();

  int GPU = obj["GPU"];
  int CPU = obj["CPU"];

  Serial.print(GPU);

  drawRectangle(CPU, "CPU", 0, 0, 120, 135);
  drawRectangle(GPU, "GPU", 120, 0, 120, 135);

}
void drawRectangle(int temp, String label, int x, int y, int widthy, int heightx) {

  if (temp < 60) {
    tft.fillRect(x, y, widthy, heightx, TFT_BLUE);
  } else if (temp >= 60 && temp < 85) {
    tft.fillRect(x, y, widthy, heightx, TFT_ORANGE);
  } else if (temp > 85) {
    tft.fillRect(x, y, widthy, heightx, TFT_RED);
  }
  tft.setTextSize(3);
  tft.setCursor(x + 35, tft.height() / 8);
  tft.print(label);
  tft.setTextSize(5);
  if (temp < 100) {
    tft.setCursor(x + 30, tft.height() / 2);
  } else {
    tft.setCursor(x + 10, tft.height() / 2);
  }
  tft.print(temp);
  tft.setTextSize(2);
  tft.print((char) 247);

}
