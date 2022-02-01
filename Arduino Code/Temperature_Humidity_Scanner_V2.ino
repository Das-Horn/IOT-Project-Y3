#include <DHT.h>
#include <ArduinoJson.h>          // Includes the ArduinoJson.h Library.
#include <Arduino.h>              // Includes the Arduino.h Library.
#include <WiFi.h>                 // Includes the WiFi.h Library.
#include <WiFiMulti.h>            // Includes the WiFiMulti.h Library.
#include <HTTPClient.h>           // Includes the HTTPClient.h Library.

#define DHTPIN 2
#define DHTTYPE DHT11

WiFiMulti wifiMulti;

char ssid[] = "XD";               // SSID of the current WiFi network the device is connected to.
char pass[] = "11111111";         // Password of the current WiFi network the device is connected to.
char server[] = "192.168.43.149"; // Sets the Server IP Address to that of the database we want to connect to.

int buzzer = 0;                   // Pin for buzzer.
int led = 0;                      // Pin for led.
const int pinDHT11 = 2;           // Pin for DHT11.
float temperature = 0;            // Makes a variable called temperature that is set to 0.
float humidity = 0;               // Makes a variable called humidity that is set to 0.
DHT dht(DHTPIN, DHTTYPE);                          // Starts the DHT11.

void setup()
{
  Serial.begin(115200);     // Starts up the serial monitor communication at a baud rate of 115200.
  Serial.println();         // Prints off data into the serial monitor.
  Serial.println();         // Prints off more data into the serial monitor.
  Serial.println();         // Prints off even more data into the serial monitor.
  
  pinMode(buzzer, OUTPUT);  // Sets the buzzer as an OUTPUT.
  pinMode(led, OUTPUT);     // Sets the led as an OUTPUT.
  pinMode(pinDHT11, INPUT); // Sets the DHT11 as an INPUT.

  dht.begin();
  
  wifiMulti.addAP(ssid, pass);
  
  Serial.print("[LOCAL] Connecting... \n"); // Prints off that the ESP32 is connecting to the network.

  while (wifiMulti.run() == WL_CONNECTED)
  {
    Serial.print("[LOCAL] Connection established \n");  // Prints off that the ESP32 has established a connection.
    String url = "http://192.168.43.149:3000/api/Requests/jobs";  // This is the URL of our database which the ESP32 wants to connect to.
    Serial.print("[LOCAL] Attempting connection to DB... \n");  // Prints off that the ESP32 is attempting connection to the database.
    HTTPClient http;
    /*server.on("/", serverOnline);
    server.onNotFound(serverOffline);*/
    http.begin(url);            // Begins the HTTP protocol.
    int httpCode = http.GET();  // Requests data from the database.
    Serial.print("Results: ");  // Prints out "Results: ".
    Serial.print((int)temperature); Serial.print(" *C, ");  // Prints out the Temperature in Celsius.
    Serial.print((int)humidity); Serial.println(" H");      // Prints out the Humidity in H.
    delay(100);                                             // Adds a delay of 100ms or 0.1 second.
  }
  /*Blynk.begin(auth, ssid, pass);        // Connects the Arduino to the Blynk Cloud.
  timer.setInterval(1000L, sendSensor);   // Setup a function to be called every second.*/
}

void loop()
{
  /*server.handleClient();*/
  /*Blynk.run();  // Runs Blynk, super magical stuff.
  timer.run();  // Runs the timer, tick tock.*/
}

/*
void serverOnline()
{
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  server.send(200, SendHTML(temperature, humidity));
}

void serverOffline()
{
  server.send(404, "text/plain", "Not Found");
}
*/

/*
#define BLYNK_TEMPLATE_ID "TMPLsQNRIqHr"                      // Template name that is used in the Blynk App.
#define BLYNK_DEVICE_NAME "Quickstart Device"                 // Name of device connected to ESP32.
#define BLYNK_AUTH_TOKEN "yjk60Mym1MoYJpTYdtUCG6rH3HThYgDF"   // Authentication Token that is provided to us on the Blynk App.
#define BLYNK_PRINT Serial                                    // Prints out information about the Blynk Process to the Serial Monitor.

#include <WiFi.h>                 // Includes the "WiFi.h" library.
#include <WiFiClient.h>           // Includes the "WiFiClient.h" library.
#include <BlynkSimpleEsp32.h>     // Includes the "BlynkSimpleEsp32.h" library.
#include <SimpleDHT.h>            // Includes the "SimpleDHT.h" library.

char auth[] = BLYNK_AUTH_TOKEN;   // Authentication Token that is provided to us on the Blynk App.

BlynkTimer timer;                 // Adds a timer to the Blynk Process.

BLYNK_WRITE(V0)   // This function is called every time the Virtual Pin 0 state changes.
{
  int value = param.asInt();      // Sets incoming value from Virtual Pin 0 to a variable.
  Blynk.virtualWrite(V1, value);  // Sends data in various formats to Virtual Pin 1.
}

BLYNK_CONNECTED() // This function is called every time the device is connected to the Blynk Cloud.
{
  Blynk.setProperty(V3, "offImageUrl", "Congratulations!"); // Changes the offImageUrl.
  Blynk.setProperty(V3, "onImageUrl", "Congratulations!");  // Changes the onImageUrl.
  Blynk.setProperty(V3, "url", "Congratulations!");         // Changes the url.
}
*/
