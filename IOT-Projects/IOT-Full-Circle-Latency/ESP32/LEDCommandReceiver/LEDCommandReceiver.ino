String incomingByte = "1";
int LED_BUILTIN = 32;
void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}
void loop() {

  if (Serial.available()) {
    // read the incoming byte:
   incomingByte = Serial.readString(); 
    // say what you got:
    //Serial.print("I: ");
    //Serial.println(incomingByte);
    LEDHandler(incomingByte);
  }
  
}

void LEDHandler(String command){
  if (command.equals("2")){
        digitalWrite(LED_BUILTIN, HIGH);
  } else if (command.equals("1")){
    digitalWrite(LED_BUILTIN, LOW);
  }

}
