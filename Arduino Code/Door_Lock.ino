#include <ESP32Servo.h>     // Includes the ESP32Servo.h Library.
#include <ArduinoJson.h>    // Includes the ArduinoJson.h Library. https://github.com/bblanchon/ArdudooroJson
#include <Arduino.h>        // Includes the Arduino.h Library. https://github.com/esp8266/Ardudooro/blob/master/cores/esp8266/Ardudooro.h
#include <WiFi.h>           // Includes the WiFi.h Library. https://github.com/ardudooro-libraries/WiFi
#include <WiFiMulti.h>      // Includes the WiFiMulti.h Library. https://github.com/espressif/ardudooro-esp32/blob/master/libraries/WiFi/src/WiFiMulti.h
#include <HTTPClient.h>     // Includes the HTTPClient.h Library. https://github.com/espressif/ardudooro-esp32/blob/master/libraries/HTTPClient/src/HTTPClient.h

WiFiMulti wifiMulti;

char ssid[] = "XD";         // SSID of the current WiFi network the device is connected to.
char pass[] = "11111111";   // Password of the current WiFi network the device is connected to.

bool door = false;
int pos = 5;

Servo doorlock;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();

  wifiMulti.addAP(ssid, pass);
  
  Serial.print("[LOCAL] Connecting... \n"); // Prints off that the ESP32 is connecting to the network.
  
  while (!Serial);
  doorlock.attach(12);
  doorlock.write(pos);
}

void loop()
{
  if((wifiMulti.run() == WL_CONNECTED)) // If statement for when the ESP32 has successfully connected.
  {
    Serial.print("[LOCAL] Connection established \n");                    // Prints off that the ESP32 has established a connection.
    String url = "https://iot-project-y3.vercel.app/api/Requests/jobs";   // This is the URL of our database which the ESP32 wants to connect to.
    Serial.print("[LOCAL] Attempting connection to DB... \n");            // Prints off that the ESP32 is attempting connection to the database.
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
        if (doc[7]["Action"] == true)
        {
          door = true;
          Serial.print("[LOCAL] Door Lock has been activated \n");
        }
        else
        {
          door = false;
          Serial.print("[LOCAL] Door Lock has been deactivated \n");
        }
        if (door == true)
        {
          Serial.print("Door Locked \n");
          pos = 105;
          doorlock.write(pos);
        }
        else if (door == false)
        {
          Serial.print("Door Unlocked \n");
          pos = 5;
          doorlock.write(pos);
        }
      }
      else  // Else statement if an error is to occur between the ESP32 and the connection to the database.
      {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end(); // HTTP has ended.
    }
  }
} // Ends the void loop() statement.
