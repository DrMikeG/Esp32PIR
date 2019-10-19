#define LED_BUILTIN_GREEN 22
#define LED_BUILTIN_RED 10

boolean isAntiSpamTimerRunnng;
long antiSpamTimer;
long antiSpamMinimum;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN_GREEN, OUTPUT);
  pinMode(LED_BUILTIN_RED, OUTPUT);
  Serial.begin(115200);
  Serial.println("watchman start");
  pinMode(GPIO_NUM_17, INPUT_PULLDOWN);

  digitalWrite(LED_BUILTIN_GREEN, HIGH);   // turn the LED on (HIGH is the voltage level)
  
  isAntiSpamTimerRunnng = false;

  // 

}

void ensureWifiConnected()
{

  
}


void startAntiSpamTimer()
{
  isAntiSpamTimerRunnng = true;
  antiSpamTimer = 0;
}


void reactToPirDetection()
{
   Serial.println("There is a PIR signol");
   
}


// the loop function runs over and over again forever
void loop() {

  if(digitalRead(GPIO_NUM_17)==HIGH)
  {
    for (int i=0; i < 5; i++)
    {
     digitalWrite(LED_BUILTIN_GREEN, LOW);    // turn the LED off by making the voltage LOW
     delay(20);
     digitalWrite(LED_BUILTIN_GREEN, HIGH);    // turn the LED off by making the voltage LOW
     delay(20);
    }
    delay(800);
  }
  else {
     Serial.println("LOW");
   }
  
  delay(100);
}
