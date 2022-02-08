#include <ArduinoJson.h>        // Includes the ArduinoJson.h Library. https://github.com/bblanchon/ArduinoJson
#include <Arduino.h>            // Includes the Arduino.h Library. https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Arduino.h
#include <WiFi.h>               // Includes the WiFi.h Library. https://github.com/arduino-libraries/WiFi
#include <WiFiMulti.h>          // Includes the WiFiMulti.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFiMulti.h
#include <HTTPClient.h>         // Includes the HTTPClient.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/HTTPClient/src/HTTPClient.h

WiFiMulti wifiMulti;
/*
void ledControl(String);
String connectDB();
*/
char ssid[] = "XD";             // SSID of the current WiFi network the device is connected to.
char pass[] = "11111111";       // Password of the current WiFi network the device is connected to.

int ledPin1 = 4;                // Sets the Pin of ledPin1 to 4.
int ledPin2 = 5;                // Sets the Pin of ledPin2 to 5.
int ledPin3 = 18;                // Sets the Pin of ledPin3 to 18.
int ledPin4 = 19;               // Sets the Pin of ledPin4 to 19.
boolean activeLED1 = false;      // Sets the variable of activeLED1 to false.
boolean activeLED2 = false;      // Sets the variable of activeLED2 to false.
boolean activeLED3 = false;      // Sets the variable of activeLED3 to false.
boolean activeLED4 = false;      // Sets the variable of activeLED4 to false.

void setup()                    // Starts the void setup().
{
  Serial.begin(115200);         // Starts up the serial monitor communication at a baud rate of 115200.
  Serial.println();             // Prints off data into the serial monitor.
  Serial.println();             // Prints off more data into the serial monitor.
  Serial.println();             // Prints off even more data into the serial monitor.
  
  wifiMulti.addAP(ssid, pass);
  
  Serial.print("[LOCAL] Connecting... \n"); // Prints off that the ESP32 is connecting to the network.
  
  pinMode(ledPin1, OUTPUT);     // Sets the ledPin as an Output.
  pinMode(ledPin2, OUTPUT);     // Sets the ledPin as an Output.
  pinMode(ledPin3, OUTPUT);     // Sets the ledPin as an Output.
  pinMode(ledPin4, OUTPUT);     // Sets the ledPin as an Output.
}

void loop()
{
  DynamicJsonDocument temp = connectDB();
  ledControl(temp);
}

DynamicJsonDocument connectDB() 
{
  DynamicJsonDocument doc(1023);
  if((wifiMulti.run() == WL_CONNECTED)) // If statement for when the ESP32 has successfully connected.
  {
    Serial.print("[LOCAL] Connection established \n");                  // Prints off that the ESP32 has established a connection.
    String url = "https://iot-project-y3.vercel.app/api/Requests/jobs"; // This is the URL of our database which the ESP32 wants to connect to.
    Serial.print("[LOCAL] Attempting connection to DB... \n");          // Prints off that the ESP32 is attempting connection to the database.
    HTTPClient http;
    http.begin(url);            // Begins the HTTP protocol.
    int httpCode = http.GET();  // Requests data from the database.
    if(httpCode > 0)            // If statement for when the data given back from the database is set to 0.
    {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);  // Prints out the HTTP Code number, should be 200.
      if(httpCode == HTTP_CODE_OK)  // If statement for when the HTTP Code number is ok.
      {
        String inData = http.getString();
        DeserializationError error = deserializeJson(doc, inData);
      } // Ends the if(httpCode == HTTP_CODE_OK) statement.
    } // Ends the if(httpCode > 0) statement.
    else // Else statement if an error is to occur between the ESP32 and the connection to the database.
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    } // Ends the else statement.
  http.end(); // HTTP has ended.
  return(doc);
  } // Ends the if((wifiMulti.run() == WL_CONNECTED)) statement.
}

int ledControl(DynamicJsonDocument doc) 
  {
      int leds[4] = {ledPin1, ledPin2, ledPin3, ledPin4};
        for(int i = 2; i < 6; i++)
        {
          if(doc[i]["Action"] == true)
          {
            digitalWrite(leds[i-3], HIGH);
          }
          else
          {
            digitalWrite(leds[i-3], LOW);
          }
        }
            
      return 0;
  } 
