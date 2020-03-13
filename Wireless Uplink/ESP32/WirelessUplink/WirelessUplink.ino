#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>



#include <Wire.h>
#include <ErriezBH1750.h>


// Light Sensor
// ADDR line LOW/open:  I2C address 0x23 (0x46 including R/W bit) [default]
// ADDR line HIGH:      I2C address 0x5C (0xB8 including R/W bit)
BH1750 sensor(LOW);

// WIFI Setup
const char* ssid = "PV_WLan";
const char* password =  "H5@dA56aQ";

WiFiMulti wifiMulti;

//Data Setup
int tranmissionNumber = 0;
float temperature;
uint16_t lux;


void setup() {
  Serial.begin(115200);

  delay(4000);   //Delay needed before calling the WiFi.begin
  Serial.println("test");
  setupLightSensor();
  setupWifi();


}

void setupWifi() {

  wifiMulti.addAP(ssid, password);

  //  WiFi.begin(ssid, password);
  //
  //  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
  //    delay(1000);
  //    Serial.println("Connecting to WiFi..");
  //  }
  //
  //  Serial.println("Connected to the WiFi network");
}

void setupLightSensor() {
  // Initialize I2C bus
  Wire.begin(25, 26);
  // Initialize sensor in continues mode, medium 1 lx resolution
  sensor.begin(ModeContinuous, ResolutionLow);

  // Start conversion
  sensor.startConversion();
}

uint16_t readLightSensor() {
  if (sensor.waitForCompletion()) {
    // Read light
    return sensor.read();
  }
}

void requestHttp() {

  if ((wifiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    http.begin("http://google.com");

    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        
        Serial.println(httpCode);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();

  }
  //  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
  //    tranmissionNumber = tranmissionNumber + 1;
  //
  //    HTTPClient http;
  //    //http.begin("http://jsonplaceholder.typicode.com/posts");  //Specify destination for HTTP request
  //    //http.begin("http://google.com");  //Specify destination for HTTP request
  //    http.addHeader("Content-Type", "text/plain");             //Specify content-type header
  //
  //    int httpResponseCode = http.get();   //Send the actual POST request
  //
  //    if (httpResponseCode > 0) {
  //
  //      //String response = http.getString();                       //Get the response to the request
  //
  //      Serial.println(httpResponseCode);   //Print return code
  //      // Serial.println(response);           //Print request answer
  //
  //    } else {
  //
  //      Serial.print("Error on sending POST: ");
  //      Serial.println(httpResponseCode);
  //
  //    }
  //
  //    http.end();  //Free resources
  //
  //  } else {
  //
  //    Serial.println("Error in WiFi connection");
  //
  //  }
}

void loop() {

  lux = readLightSensor();
  requestHttp();
  delay(10000);  //Send a request every 10 seconds

}
