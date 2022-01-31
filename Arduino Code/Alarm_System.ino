#include <ArduinoJson.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti wifiMulti;

char ssid[] = "XD";               // SSID of the current WiFi network the device is connected to.
char pass[] = "11111111";         // Password of the current WiFi network the device is connected to.
char server[] = "192.168.43.149";

int buzzer = 5;         // Pin for Buzzer.
int led = 4;            // Pin for LED.
int inputPin = 2;       // Pin for PIR Sensor.
boolean pirState = LOW; // Sets the state of the PIR Sensor to Low.
int value = 0;          // Variable for reading the pin status.
int serialData = 0;
boolean activeSec = false;

void setup()
{
  Serial.begin(115200);

    Serial.println();
    Serial.println();
    Serial.println();

    wifiMulti.addAP(ssid, pass);
    Serial.print("[LOCAL] Connecting... \n");
  
 
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(inputPin, INPUT);
}

void loop()
{
  if((wifiMulti.run() == WL_CONNECTED)) {
    Serial.print("[LOCAL] Connection established \n"); 
    String url = "http://192.168.43.149:3000/api/Requests/jobs";
    Serial.print("[LOCAL] Attempting connection to DB... \n");
    HTTPClient http;
    
    http.begin(url);
    int httpCode = http.GET();

     // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String inData = http.getString();
                DynamicJsonDocument doc(1023);
                DeserializationError error = deserializeJson(doc, inData);
                if (doc[0]["Action"] == true)
                    {
                     activeSec = true;
                     Serial.print("[LOCAL] Security is active \n");
                    }
                else
                {
                  activeSec = false;
                  pirState = LOW;
                  digitalWrite(led, LOW);
                  digitalWrite(buzzer, LOW);
                  Serial.print("[LOCAL] Security is inactive \n");
                }
                if (error) {
                  Serial.print(F("deserializeJson() failed: "));
                  Serial.println(error.f_str());
                  return;
                }
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
         
    http.end();

    value = digitalRead(inputPin);  // Read input value.
    if (activeSec == true)
    {
      if (value == HIGH)              // Check if the input is HIGH.
      {
        pirState = HIGH;
        
      }
       
      if (pirState == HIGH)
      {
        digitalWrite(led, HIGH);      // Turn LED ON.
        digitalWrite(buzzer, HIGH);
        Serial.println("Motion detected!");
      }
    }
  } 
 }


/* #define BLYNK_TEMPLATE_ID "TMPLsQNRIqHr"                      // Template name that is used in the Blynk App.
#define BLYNK_DEVICE_NAME "Quickstart Device"                 // Name of device connected to ESP32.
#define BLYNK_AUTH_TOKEN "yjk60Mym1MoYJpTYdtUCG6rH3HThYgDF"   // Authentication Token that is provided to us on the Blynk App.
#define BLYNK_PRINT Serial                                    // Prints out information about the Blynk Process to the Serial Monitor.

#include <WiFi.h>                 // Includes the "WiFi.h" library.
#include <WiFiClient.h>           // Includes the "WiFiClient.h" library.
#include <BlynkSimpleEsp32.h>     // Includes the "BlynkSimpleEsp32.h" library.

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
