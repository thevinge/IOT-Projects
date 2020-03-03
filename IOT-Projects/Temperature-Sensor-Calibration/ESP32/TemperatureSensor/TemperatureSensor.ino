float temp;
void setup() {
  Serial.begin(115200);

}

void loop() {
  
  temp = analogRead(39);
  
  Serial.println(temp);
  delay(5000);

}
