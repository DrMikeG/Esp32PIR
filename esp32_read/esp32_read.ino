#define LED_BUILTIN 22

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("blink start");
  pinMode(GPIO_NUM_17, INPUT_PULLDOWN);
}

// the loop function runs over and over again forever
void loop() {
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  Serial.println("blink on");

  if(digitalRead(GPIO_NUM_17)==HIGH){
     Serial.println("HIGH");
  }else{
     Serial.println("LOW");
  }
  
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  Serial.println("blink off");
  delay(500);
}
