float temp;
void setup() {
  Serial.begin(115200);

}

void loop() {

  float temperature = 0.0;   // stores the calculated temperature
    int sample;                // counts through ADC samples
    float ten_samples = 0.0;   // stores sum of 10 samples
  
    // take 10 samples from the MCP9700
    for (sample = 0; sample < 10; sample++) {
        // convert A0 value to temperature
        temperature = analogRead(39);
        // sample every 0.1 seconds
        delay(100);
        // sum of all samples
        ten_samples = ten_samples + temperature;
    }
    // get the average value of 10 temperatures
    temperature = ten_samples / 10.0;

  //temp = analogRead(39);
  Serial.println(temperature);
  //delay(1000);

}
