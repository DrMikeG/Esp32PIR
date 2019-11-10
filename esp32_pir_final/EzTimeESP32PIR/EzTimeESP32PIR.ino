/*******************************************************************
    
    With much credit to Brian Lough
    
    *******************************************************************/

#include <WiFi.h>
#include <ezTime.h>
// Library used for getting the time and adjusting for DST
// Search for "ezTime" in the Arduino Library manager
// https://github.com/ropg/ezTime

// ---- Stuff to configure ----
// Initialize Wifi connection to the router
char ssid[] = "VM4826469";     // your network SSID (name)
char password[] = "_8gGpcvqjhpk"; // your network key

// Set a timezone using the following list
// https://en.wikipedia.org/wiki/List_of_tz_database_time_zones
#define MYTIMEZONE "Europe/London"
#define LED_BUILTIN_GREEN 22

// Sets whether the clock should be 12 hour format or not.
bool twelveHourFormat = true;
Timezone myTZ;

unsigned long antiPesterLoopDue = 0;

void setup() {
  Serial.begin(115200);

  Serial.println("watchman start");
  pinMode(GPIO_NUM_17, INPUT_PULLDOWN);
  pinMode(LED_BUILTIN_GREEN, OUTPUT);
  digitalWrite(LED_BUILTIN_GREEN, LOW);
}
/*
void setMatrixTime() {
  String timeString = "";
  String AmPmString = "";
  if (twelveHourFormat) {
    // Get the time in format "1:15" or 11:15 (12 hour, no leading 0)
    // Check the EZTime Github page for info on
    // time formatting
    timeString = myTZ.dateTime("g:i");

    //If the length is only 4, pad it with
    // a space at the beginning
    if (timeString.length() == 4) {
      timeString = " " + timeString;
    }

    //Get if its "AM" or "PM"
    AmPmString = myTZ.dateTime("A");
    if (lastDisplayedAmPm != AmPmString) {
      Serial.println(AmPmString);
      lastDisplayedAmPm = AmPmString;
      // Second character is always "M"
      // so need to parse it out
      tetris2.setText("M", forceRefresh);

      // Parse out first letter of String
      tetris3.setText(AmPmString.substring(0, 1), forceRefresh);
    }
  } else {
    // Get time in format "01:15" or "22:15"(24 hour with leading 0)
    timeString = myTZ.dateTime("H:i");
  }

  // Only update Time if its different
  if (lastDisplayedTime != timeString) {
    Serial.println(timeString);
    lastDisplayedTime = timeString;
    tetris.setTime(timeString, forceRefresh);

    // Must set this to false so animation knows
    // to start again
    finishedAnimating = false;
  }
}
*/

void waitForWifi()
{
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }
  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup EZ Time
  setDebug(INFO);
  waitForSync();

  Serial.println();
  Serial.println("UTC:             " + UTC.dateTime());

  myTZ.setLocation(F(MYTIMEZONE));
  Serial.print(F("Time in your set timezone:         "));
  Serial.println(myTZ.dateTime());

  delay(2000);

  sendIveJustWokenUpTweet();

}


unsigned long GetTimeBetweenPIRChecksInMS()
{
  return 1000; // 1 second
}
unsigned long GetTimeBetweenTweetsInMS()
{
  return 15 * 60 * 1000; // 15 minutes
}

void loop() {
  unsigned long now = millis();
  
 // Check PIR
  if(digitalRead(GPIO_NUM_17)==HIGH)
  {
      digitalWrite(LED_BUILTIN_GREEN, HIGH);
  }
  else
  {
      digitalWrite(LED_BUILTIN_GREEN, LOW);
  }


  if (now > antiPesterLoopDue) {

    // Wait for Wifi
    waitForWifi();  
    antiPesterLoopDue = now + GetTimeBetweenPIRChecksInMS();
  }
}

void sendIveJustWokenUpTweet()
{
  //unsigned long now = millis();
  // send a tweet that wifi has just connected...
  //antiPesterLoopDue = now + GetTimeBetweenTweetsInMS();
  for (int i=0; i < 6; i++)
  {
    digitalWrite(LED_BUILTIN_GREEN, HIGH);
    delay(80);
    digitalWrite(LED_BUILTIN_GREEN, LOW);
    delay(80);
  }
}

void sendInaneTweet()
{
  unsigned long now = millis();
  // send a tweet that wifi has just connected...
  antiPesterLoopDue = now + GetTimeBetweenTweetsInMS();
}

String getRandomisedTimeAppropriateSaying()
{
  return "bob says high";
}
