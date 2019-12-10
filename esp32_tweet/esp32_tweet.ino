#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <TwitterWebAPIESP32.h>

const char* ssid = "";           // WiFi SSID
const char* password = "";   // WiFi Password
#define LED_BUILTIN 22

//static char const consumer_key[]    = "";
//static char const consumer_sec[]    = "";
//static char const accesstoken[]     = "-REI0k7pimbxDNA1kR6kMkVAOrKwRq8f";
//static char const accesstoken_sec[] = "";


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 0, 60000);  // NTP server pool, offset (in seconds), update interval (in milliseconds)
TwitterClient tcr(timeClient, consumer_key, consumer_sec, accesstoken, accesstoken_sec);

void setup(void){
  //Begin Serial
  Serial.begin(115200);
  // WiFi Connection
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to ");
  Serial.print(ssid);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected. yay!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(100);
  // Connect to NTP and force-update time
  tcr.startNTP();
  Serial.println("NTP Synced");
  delay(100);
  // Setup internal LED
  pinMode(LED_BUILTIN, OUTPUT);
  //if (twi_update_interval < 5) api_mtbs = 5000; // Cant update faster than 5s.
  
  digitalWrite(LED_BUILTIN, LOW);
  
  
  timeClient.update();
  delay(2000);
  Serial.println(timeClient.getFormattedTime());
  std::string timeStr = timeClient.getFormattedTime().c_str();
  std::string twitter_post_msg =  "Connected at " + timeStr;
  Serial.println(twitter_post_msg.c_str());
  tcr.tweet(twitter_post_msg);
  digitalWrite(LED_BUILTIN, HIGH);
  
}

/*void extractJSON(String tmsg) {
  const char* msg2 = const_cast <char*> (tmsg.c_str());
  DynamicJsonBuffer jsonBuffer;
  JsonObject& response = jsonBuffer.parseObject(msg2);
  
  if (!response.success()) {
    Serial.println("Failed to parse JSON!");
    Serial.println(msg2);
//    jsonBuffer.clear();
    return;
  }
  
  if (response.containsKey("statuses")) {
    String usert = response["statuses"][0]["user"]["screen_name"];
    String text = response["statuses"][0]["text"];
    if (text != "") {
      text = "@" + usert + " says " + text;
      search_msg = std::string(text.c_str(), text.length());
    }
  } else if(response.containsKey("errors")) {
    String err = response["errors"][0];
    search_msg = std::string(err.c_str(), err.length());
  } else {
    Serial.println("No useful data");
  }
  
  jsonBuffer.clear();
  delete [] msg2;
}
*/

void loop(void){

  /*
  if (millis() > api_lasttime + api_mtbs)  {
    digitalWrite(LED_BUILTIN, LOW);
    extractJSON(tcr.searchTwitter(search_str));
    Serial.print("Search: ");
    Serial.println(search_str.c_str());
    Serial.print("MSG: ");
    Serial.println(search_msg.c_str());
    api_lasttime = millis();
  }
  delay(2);
  yield();
  digitalWrite(LED_BUILTIN, HIGH);
  */
}
