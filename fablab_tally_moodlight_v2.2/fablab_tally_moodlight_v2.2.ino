#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <WebSocketsServer.h>
#include <EEPROM.h>

ESP8266WiFiMulti wifiMulti;       // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);       // create a web server on port 80
WebSocketsServer webSocket(81);    // create a websocket server on port 81

String ssid = "Moodlight-"+WiFi.macAddress().substring(17-5);
String password = "";   // The password required to connect to it, leave blank for an open network

String wifi_ssid = "";         // Wi-Fi networks you want to connect to
String wifi_password = "";

#define LED_RED     D4            // specify the pins with an RGB LED connected
#define LED_GREEN   D5
#define LED_BLUE    D6

#define LED2_RED     D0            // specify the pins with an RGB LED connected
#define LED2_GREEN   D2
#define LED2_BLUE    D1

// LED 1 R:D0, G:D2, B:D1 
// LED 2 R:D4, G:D5, B:D6

String mac = WiFi.macAddress().substring(17-5);

String mdnsName = "moodlight"; // Domain name for the mDNS responder

/*__________________________________________________________SETUP__________________________________________________________*/

void setup() {
  pinMode(LED_RED, OUTPUT);    // the pins with LEDs connected are outputs
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  demoLED();

  Serial.begin(115200);        // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println("\r\n");

  startFlashMemory();         // Start FlashMemory to read stored ssid & password          

  startWiFi();                 // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
  
  startSPIFFS();               // Start the SPIFFS and list all contents

  startWebSocket();            // Start a WebSocket server
  
  startMDNS();                 // Start the mDNS responder

  startServer();               // Start a HTTP server with a file read handler and an upload handler
}

/*__________________________________________________________LOOP__________________________________________________________*/

bool rainbow = false;             // The rainbow effect is turned off on startup

unsigned long prevMillis = millis();
int hue = 0;

void loop() {
  webSocket.loop();                           // constantly check for websocket events
  server.handleClient();                      // run the server
  MDNS.update();

  if(rainbow) {                               // if the rainbow effect is turned on
    if(millis() > prevMillis + 32) {          
      if(++hue == 360)                        // Cycle through the color wheel (increment by one degree every 32 ms)
        hue = 0;
      setHue(hue);                            // Set the RGB LED to the right color
      prevMillis = millis();
    }
  }
}
