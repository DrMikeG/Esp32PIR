/*******************************************************************
    
    With much credit to Brian Lough & Debashish Sahu
    
*******************************************************************/

//#include <WiFi.h>
//#include <ezTime.h>

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <TwitterWebAPIESP32.h>

// Library used for getting the time and adjusting for DST
// Search for "ezTime" in the Arduino Library manager
// https://github.com/ropg/ezTime

// ---- Stuff to configure ----
// Initialize Wifi connection to the router
char ssid[] = "VM4826469";     // your network SSID (name)
char password[] = ""; // your network key

static char const consumer_key[]    = "G";
static char const consumer_sec[]    = "S";
static char const accesstoken[]     = "76";
static char const accesstoken_sec[] = "FL0m";

// Set a timezone using the following list
#define LED_BUILTIN_GREEN 22

// Sets whether the clock should be 12 hour format or not.
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 0, 60000);  // NTP server pool, offset (in seconds), update interval (in milliseconds)
TwitterClient tcr(timeClient, consumer_key, consumer_sec, accesstoken, accesstoken_sec);


unsigned long antiPesterLoopDue = 0;

void setup() {
  Serial.begin(115200);

  Serial.println("watchman start");
  pinMode(GPIO_NUM_17, INPUT_PULLDOWN);
  pinMode(LED_BUILTIN_GREEN, OUTPUT);
  digitalWrite(LED_BUILTIN_GREEN, LOW);
}

std::string getTimeString() {
  timeClient.update();
  std::string timeStr = timeClient.getFormattedTime().c_str();
  return timeStr;
}

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

  tcr.startNTP();
  Serial.println("NTP Synced");
  delay(100);
  timeClient.update();
  
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
  bool isHigh = false;
 // Check PIR
  if(digitalRead(GPIO_NUM_17)==HIGH)
  {
      digitalWrite(LED_BUILTIN_GREEN, HIGH);
      isHigh = true;
  }
  else
  {
      digitalWrite(LED_BUILTIN_GREEN, LOW);
  }


  if (now > antiPesterLoopDue && isHigh) {
    // Wait for Wifi
    waitForWifi();
    sendInaneTweet();
  }
  //else
  //{
  //  Serial.print("Time now is ");
  //  Serial.print(now);
  //  Serial.print(" blocked from sending until ");
  //  Serial.println(antiPesterLoopDue);
 // }
}

void sendIveJustWokenUpTweet()
{
  //unsigned long now = millis();
  // send a tweet that wifi has just connected...
  //antiPesterLoopDue = now + GetTimeBetweenTweetsInMS();
  std::string timeStr = timeClient.getFormattedTime().c_str();
  std::string localIPstr = WiFi.localIP().toString().c_str();
  std::string twitter_post_msg =  "Yawn, finally connected as "+ localIPstr +" at " + timeStr;
  Serial.println(twitter_post_msg.c_str());
  tcr.tweet(twitter_post_msg);
}

void sendInaneTweet()
{
  unsigned long now = millis();
  // send a tweet that wifi has just connected...
  std::string localIPstr = WiFi.localIP().toString().c_str();
  std::string twitter_post_msg = getTimeString() + ": " + getRandomisedTimeAppropriateSaying().c_str();
  //tcr.tweet(twitter_post_msg);
  Serial.println(twitter_post_msg.c_str());
  tcr.tweet(twitter_post_msg);
  antiPesterLoopDue = now + GetTimeBetweenTweetsInMS();
}

#define ARRAYSIZE 93
String results[ARRAYSIZE] = {
"Frankly, my dear, I don't give a damn.",
"I'm going to make him an offer he can't refuse.",
"I could've been a contender.",
"Toto, I've got a feeling we're not in Kansas anymore.",
"Here's looking at you, kid.",
"Go ahead, make my day.",
"May the Force be with you.",
"You talkin' to me?",
"What we've got here is failure to communicate.",
"I love the smell of napalm in the morning.",
"Love means never having to say you're sorry.",
"The stuff that dreams are made of.",
"E.T. phone home.",
"Rosebud.",
"Louis, I think this is the beginning of a beautiful friendship.",
"A census taker once tried to test me. I ate his liver with some fava beans and a nice Chianti.",
"Bond. James Bond.",
"There's no place like home.",
"Show me the money!",
"Play it, Sam. Play it again",
"You can't handle the truth!",
"After all, tomorrow is another day.",
"Round up the usual suspects.",
"I'll have what she's having.",
"You're gonna need a bigger boat.",
"I'll be back.",
"If you build it, he will come.",
"We rob banks.",
"We'll always have Paris.",
"I see dead people.",
"Well nobody's perfect.",
"It's alive! It's alive!",
"Houston, we have a problem.",
"You've got to ask yourself one question: 'Do I feel lucky?' Well, do ya, punk?",
"There's no crying in baseball!",
"A boy's best friend in his mother.",
"Greed, for lack of a better word, is good.",
"Keep your friends close, but your enemies closer.",
"Mrs. Robinson, you're trying to seduce me.",
"Gentlemen, you can't fight in here this is the War Room.",
"Elementary, my dear Watson.",
"Get your stinking paws off me you damned, dirty ape.",
"Of all the gin joints in all the towns in all the world she walks into mine.",
"Here's Johnny!",
"They're here.",
"Hasta la vista, baby.",
"Open the bay doors, HAL.",
"I am serious and don't call me Shirley.",
"Listen to them. Children of the night. What music they make.",
"It wasn't the airplanes. It was Beauty killed the Beast.",
"My precious.",
"A martini. Shaken, not stirred.",
"I feel the need. The need for speed.",
"Carpe diem. Seize the day, boys. Make your lives extraordinary.",
"Nobody puts Baby in the corner.",
"To infinity and beyond!",
"This list is an absolute good. This list is life.",
"I wish I knew how to quit you.",
"I am your father.",
"They may take our lives, but they'll never take our freedom!",
"Come with me if you want to live.",
"I'm funny how? Funny like I'm a clown? I amuse you?",
"We're on a mission from God.",
"You shall not pass!",
"Why so serious?",
"You'd best start believing in ghost stories, Miss Turner. You're in one.",
"Remember who you are. You are my son and the one true king.",
"Game over, man! Game over!",
"Welcome to Jurassic Park.",
"First rule of Fight Club is you don't talk about Fight Club.",
"This is Sparta!",
"Pay no attention to that man behind the curtain.",
"Get to the chopper!",
"That'll do, pig. That'll do.",
"Roads? Where we're going we don't need roads.",
"You are a toy!",
"Hello. My name is Inigo Montoya. You killed my father. Prepare to die.",
"What are the Thirty Nine Steps?",
"That's no moon. That's a space station.",
"Hey, you guys!",
"This is the day that you almost caught Captain Jack Sparrow.",
"No one can be told what the Matrix is. You have to see it for yourself.",
"Mary Poppins, practically perfect in every way.",
"I'm here to talk to you about the Avengers Initiative.",
"Lions and tigers and bears, oh my!",
"Today we celebrate our Independence Day.",
"What's in the box!?",
"I am the law!",
"Wax on, wax off.",
"Come quietly or there will be trouble.",
"It's just a flesh wound.",
"I'm not bad. I'm just drawn that way.",
"These go to eleven."
};

String getRandomisedTimeAppropriateSaying()
{
  
  int baseI = random(ARRAYSIZE);
  if (baseI < 0 || baseI > (ARRAYSIZE-1))
  {
    baseI = 0;
  }
  
  return results[baseI];
}
