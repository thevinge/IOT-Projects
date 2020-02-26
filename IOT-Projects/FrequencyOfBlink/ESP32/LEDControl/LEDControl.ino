int LED_BUILTIN = 32;
int LED_BUILTIN2 = 33;

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  pinMode (LED_BUILTIN2, OUTPUT);
  digitalWrite(LED_BUILTIN2, LOW);
}
void loop() {
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
    
}
