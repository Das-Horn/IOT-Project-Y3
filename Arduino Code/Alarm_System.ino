#include <ArduinoJson.h>          // Includes the ArduinoJson.h Library. https://github.com/bblanchon/ArduinoJson
#include <Arduino.h>              // Includes the Arduino.h Library. https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Arduino.h
#include <WiFi.h>                 // Includes the WiFi.h Library. https://github.com/arduino-libraries/WiFi
#include <WiFiMulti.h>            // Includes the WiFiMulti.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFiMulti.h
#include <HTTPClient.h>           // Includes the HTTPClient.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/HTTPClient/src/HTTPClient.h

WiFiMulti wifiMulti;

char ssid[] = "XD";               // SSID of the current WiFi network the device is connected to.
char pass[] = "11111111";         // Password of the current WiFi network the device is connected to.
char server[] = "192.168.43.149"; // Sets the Server IP Address to that of the database we want to connect to.

int buzzer = 5;             // Pin for buzzer.
int led = 4;                // Pin for led.
int inputPin = 2;           // Pin for PIR Sensor (KEEP AT PIN 2, PIN 4 DOES NOT WORK, I REPEAT DOES NOT WORK).
boolean pirState = LOW;     // Sets the state of the PIR Sensor to Low.
int value = 0;              // Variable for reading the pin status.
int serialData = 0;         // Sets the serial data to 0.
boolean activeSec = false;  // Sets the variable of activeSec (active security) to false.

void setup()                // Starts the void setup().
{
  Serial.begin(115200);     // Starts up the serial monitor communication at a baud rate of 115200.
  Serial.println();         // Prints off data into the serial monitor.
  Serial.println();         // Prints off more data into the serial monitor.
  Serial.println();         // Prints off even more data into the serial monitor.
  
  wifiMulti.addAP(ssid, pass);
  
  Serial.print("[LOCAL] Connecting... \n"); // Prints off that the ESP32 is connecting to the network.
  
  pinMode(buzzer, OUTPUT);  // Sets the buzzer as an OUTPUT.
  pinMode(led, OUTPUT);     // Sets the led as an OUTPUT.
  pinMode(inputPin, INPUT); // Sets the PIR Sensor as an INPUT.
}

void loop()                 // Start of the void loop().
{
  if((wifiMulti.run() == WL_CONNECTED)) // If statement for when the ESP32 has successfully connected.
  {
    Serial.print("[LOCAL] Connection established \n");  // Prints off that the ESP32 has established a connection.
    String url = "http://192.168.43.149:3000/api/Requests/jobs";  // This is the URL of our database which the ESP32 wants to connect to.
    Serial.print("[LOCAL] Attempting connection to DB... \n");  // Prints off that the ESP32 is attempting connection to the database.
    HTTPClient http;
    http.begin(url);            // Begins the HTTP protocol.
    int httpCode = http.GET();  // Requests data from the database.
    if(httpCode > 0)            // If statement for when the data given back from the database is set to 0.
    {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);  // Prints out the HTTP Code number, should be 200.
      if(httpCode == HTTP_CODE_OK)  // If statement for when the HTTP Code number is ok.
      {
        String inData = http.getString();
        DynamicJsonDocument doc(1023);
        DeserializationError error = deserializeJson(doc, inData);
        if (doc[0]["Action"] == true)
        {
          activeSec = true;
          Serial.print("[LOCAL] Security is active \n");  // Prints out that the Security has been turned on.
        }
        else  // Else statement for when the Security is turned off.
        {
          activeSec = false;          // Sets the activeSec to false.
          pirState = LOW;             // Sets the pirState to LOW.
          digitalWrite(led, LOW);     // Sets the led to a LOW state meaning it's turned off.
          digitalWrite(buzzer, LOW);  // Sets the buzzer to a LOW state meaning it's turned off.
          Serial.print("[LOCAL] Security is inactive \n");  // Prints out that the Security has been turned off.
        }
        if(error) // If statement for when an error has occured whilst trying to turn the Security on or off.
        {
          Serial.print(F("deserializeJson() failed: "));  // Prints out that the deserializeJson() has failed.
          Serial.println(error.f_str());                  // Prints out the error.
          return; // Terminate a function and return a value from a function to the calling function, if desired.
        }
      }
    }
    else  // Else statement if an error is to occur between the ESP32 and the connection to the database.
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();                     // HTTP has ended.
    value = digitalRead(inputPin);  // Value is equal to the digital read of the PIR Sensor.
    if (activeSec == true)          // If statement for when the security is activated.
    {
      if (value == HIGH)            // If statement for when the value is HIGH.
      {
        pirState = HIGH;            // Sets the pirState to HIGH.
      }
      if (pirState == HIGH)         // If statement for when the pirState is HIGH.
      {
        digitalWrite(led, HIGH);            // Sets the led on a HIGH state meaning it's turned on.
        digitalWrite(buzzer, HIGH);         // Sets the buzzer on a HIGH state meaning it's turned on.
        Serial.println("Motion detected!"); // Prints out a statement saying "Motion detected!".
      } // Ends the if (pirState == HIGH) statement.
    } // Ends the if (activeSec == true) statement.
  } // Ends the if((wifiMulti.run() == WL_CONNECTED)) statement.
} // Ends the void loop().

/*
#define BLYNK_TEMPLATE_ID "TMPLsQNRIqHr"                      // Template name that is used in the Blynk App.
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
