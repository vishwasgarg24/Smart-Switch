/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Redmi"
#define WLAN_PASS       "abc12345"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "vishwasgarg"
#define AIO_KEY         "2773cd0cc7c74cc9bf626d4a178668c6"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish feed1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/feed1");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe feed2button = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/feed2");
Adafruit_MQTT_Subscribe feed3button = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/feed3");
Adafruit_MQTT_Subscribe feed4button = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/feed4");
Adafruit_MQTT_Subscribe feed5button = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/feed5");
Adafruit_MQTT_Subscribe feed6button = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/feed6");
Adafruit_MQTT_Subscribe feed7button = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/feed7");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&feed2button);
  mqtt.subscribe(&feed3button);
  mqtt.subscribe(&feed4button);
  mqtt.subscribe(&feed5button);
  mqtt.subscribe(&feed6button);
  mqtt.subscribe(&feed7button);
  
}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &feed2button) {
      Serial.print(F("Got: "));
      Serial.println((char *)feed2button.lastread);
      int k=atoi((char *)feed2button.lastread);
      if (k==1)
      digitalWrite(4,HIGH);
      else
      digitalWrite(4,LOW);
    }
    if (subscription == &feed3button) {
      Serial.print(F("Got: "));
      Serial.println((char *)feed3button.lastread);
      int k=atoi((char *)feed3button.lastread);
      if (k==1)
      digitalWrite(2,HIGH);
      else
      digitalWrite(2,LOW);
    }
    if (subscription == &feed4button) {
      Serial.print(F("Got: "));
      Serial.println((char *)feed4button.lastread);
      int k=atoi((char *)feed4button.lastread);
      if (k==1)
      digitalWrite(15,HIGH);
      else
      digitalWrite(15,LOW);
    }
    if (subscription == &feed5button) {
      Serial.print(F("Got: "));
      Serial.println((char *)feed5button.lastread);
      int k=atoi((char *)feed5button.lastread);
      if (k==1)
      digitalWrite(5,HIGH);
      else
      digitalWrite(5,LOW);
    }
        if (subscription == &feed6button) {
      Serial.print(F("Got: "));
      Serial.println((char *)feed6button.lastread);
      int k=atoi((char *)feed6button.lastread);
      if (k==1)
      digitalWrite(18,HIGH);
      else
      digitalWrite(18,LOW);
    }
        if (subscription == &feed7button) {
      Serial.print(F("Got: "));
      Serial.println((char *)feed7button.lastread);
      int k=atoi((char *)feed7button.lastread);
      if (k==1)
      digitalWrite(19,HIGH);
      else
      digitalWrite(19,LOW);
    }
    
  }

  // Now we can publish stuff!
  Serial.print(F("\nSending photocell val "));
  Serial.print(x);
  Serial.print("...");
  if (! feed1.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
