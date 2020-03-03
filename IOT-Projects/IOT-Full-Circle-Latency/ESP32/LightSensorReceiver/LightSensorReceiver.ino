#include <Wire.h>
#include <ErriezBH1750.h>

// ADDR line LOW/open:  I2C address 0x23 (0x46 including R/W bit) [default]
// ADDR line HIGH:      I2C address 0x5C (0xB8 including R/W bit)
BH1750 sensor(LOW);


bool lookForHigh = true;
void setup()
{
    Serial.begin(115200);
    while (!Serial) {
        ;
    }

    // Initialize I2C bus
    Wire.begin(25,26);

    // Initialize sensor in continues mode, medium 1 lx resolution
    sensor.begin(ModeContinuous, ResolutionMid);

    // Start conversion
    sensor.startConversion();
}

void loop()
{
    uint16_t lux;

    // Wait for completion (blocking busy-wait delay)
    if (sensor.isConversionCompleted()) {
        // Read light
        lux = sensor.read();

        sendReceived(lux);
        // Print light
        //Serial.print(F("Light: "));
        //Serial.print(lux);
        //Serial.println(F(" LUX"));
    }
}

void sendReceived(uint16_t received){
  //Serial.print(received);
  if (lookForHigh && received > 0){
    Serial.println(1);
    lookForHigh = false;
  } else if (!lookForHigh && received == 0) {
    Serial.println(1);
    lookForHigh = true;
  }
  
}
