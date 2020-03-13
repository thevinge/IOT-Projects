#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#include <ArduinoJson.h>

#include <Wire.h>
#include <ErriezBH1750.h>


// Light Sensor
// ADDR line LOW/open:  I2C address 0x23 (0x46 including R/W bit) [default]
// ADDR line HIGH:      I2C address 0x5C (0xB8 including R/W bit)
BH1750 sensor(LOW);

// WIFI Setup
const char* ssid = "PV_WLan";
const char* password =  "H5@dA56aQ";
const size_t capacity = JSON_OBJECT_SIZE(3); //Capacity for three entries

WiFiMulti wifiMulti;
HTTPClient http;

//Data Setup
int tranmissionNumber = 0;
int temperature;
int lux;


void setup() {
  Serial.begin(115200);
  setupLightSensor();
  setupWifi();
}

void setupWifi() {

  wifiMulti.addAP(ssid, password);
  http.setReuse(true);

}

void setupLightSensor() {
  // Initialize I2C bus
  Wire.begin(25, 26);
  // Initialize sensor in continues mode, medium 1 lx resolution
  sensor.begin(ModeContinuous, ResolutionLow);
  // Start conversion
  sensor.startConversion();
}

void readLightSensor() {
  if (sensor.waitForCompletion()) {
    // Read light
    lux = sensor.read();
  }
}

void requestHttp() {

  if ((wifiMulti.run() == WL_CONNECTED)) {
    tranmissionNumber = tranmissionNumber + 1;

    DynamicJsonDocument doc(capacity);

    //HTTPClient http;

    http.begin("http://167.172.184.103/api/insert");
    //http.begin("http://167.172.184.103/health");
    http.addHeader("Content-Type", "application/json");

    doc["temp"] = temperature;
    doc["light"] = lux;
    doc["reqno"] = tranmissionNumber;
    String requestjson;

    //requestjson = String("{\"temp\": 24,") + String("\"light\":") + lux + String( ",") + String( "\"reqno\":") + tranmissionNumber + String( "}");
    //serializeJsonPretty(doc,requestjson);
    serializeJson(doc, requestjson);
    Serial.println(requestjson);
    // start connection and send HTTP header
    
    int httpCode = http.POST(requestjson);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);
        Serial.println(httpCode);
      }
      

      if (httpCode == HTTP_CODE_CREATED) {
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();

  }

}

void readTemperature() {
  temperature = analogRead(39);
}

void loop() {

  readLightSensor();
  readTemperature();
  requestHttp();
  delay(1000);  //Send a request every 10 seconds

}
