#include <ArduinoJson.h>        // Includes the ArduinoJson.h Library. https://github.com/bblanchon/ArduinoJson
#include <Arduino.h>            // Includes the Arduino.h Library. https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Arduino.h
#include <WiFi.h>               // Includes the WiFi.h Library. https://github.com/arduino-libraries/WiFi
#include <WiFiMulti.h>          // Includes the WiFiMulti.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFiMulti.h
#include <HTTPClient.h>         // Includes the HTTPClient.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/HTTPClient/src/HTTPClient.h

WiFiMulti wifiMulti;

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

void loop()                     // Start of the void loop().
{
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
        DynamicJsonDocument doc(1023);
        DeserializationError error = deserializeJson(doc, inData);
        if (doc[2]["Action"] == true)
        {
          activeLED1 = true;            // Sets the activeLED1 to true.
          digitalWrite(ledPin1, HIGH);  // Sets ledPin1 to a HIGH State.
          Serial.print("[LOCAL] LED 1 has been activated \n");    // Prints out that LED 1 has been turned on.
        }
        else // Else statement for when the LEDs are turned off.
        {
          activeLED1 = false;           // Sets the activeLED1 to false.
          digitalWrite(ledPin1, LOW);   // Sets ledPin1 to a LOW State.
          Serial.print("[LOCAL] LED 1 has been deactivated \n");  // Prints out that LED 1 has been turned off.
        }
        if (doc[3]["Action"] == true)
        {
          activeLED2 = true;            // Sets the activeLED2 to true.
          digitalWrite(ledPin2, HIGH);  // Sets ledPin2 to a HIGH State.
          Serial.print("[LOCAL] LED 2 has been activated \n");    // Prints out that LED 2 has been turned on.
        }
        else // Else statement for when the LEDs are turned off.
        {
          activeLED2 = false;           // Sets the activeLED2 to false.
          digitalWrite(ledPin2, LOW);   // Sets ledPin2 to a LOW State.
          Serial.print("[LOCAL] LED 2 has been deactivated \n");  // Prints out that LED 2 has been turned off.
        }
        if (doc[4]["Action"] == true)
        {
          activeLED3 = true;            // Sets the activeLED3 to true.
          digitalWrite(ledPin3, HIGH);  // Sets ledPin3 to a HIGH State.
          Serial.print("[LOCAL] LED 3 has been activated \n");    // Prints out that LED 3 has been turned on.
        }
        else // Else statement for when the LEDs are turned off.
        {
          activeLED3 = false;           // Sets the activeLED3 to false.
          digitalWrite(ledPin3, LOW);   // Sets ledPin3 to a LOW State.
          Serial.print("[LOCAL] LED 3 has been deactivated \n");  // Prints out that LED 3 has been turned off.
        }
        if (doc[5]["Action"] == true)
        {
          activeLED4 = true;            // Sets the activeLED4 to true.
          digitalWrite(ledPin4, HIGH);  // Sets ledPin4 to a HIGH State.
          Serial.print("[LOCAL] LED 4 has been activated \n");    // Prints out that LED 4 has been turned on.
        }
        else // Else statement for when the LEDs are turned off.
        {
          activeLED4 = false;           // Sets the activeLED4 to false.
          digitalWrite(ledPin4, LOW);   // Sets ledPin4 to a LOW State.
          Serial.print("[LOCAL] LED 4 has been deactivated \n");  // Prints out that LED 4 has been turned off.
        }
        if(error) // If statement for when an error has occured whilst trying to turn the LEDs on or off.
        {
          Serial.print(F("deserializeJson() failed: "));    // Prints out that the deserializeJson() has failed.
          Serial.println(error.f_str());                    // Prints out the error.
          return; // Terminate a function and return a value from a function to the calling function, if desired.
        }
      } // Ends the if(httpCode == HTTP_CODE_OK) statement.
    } // Ends the if(httpCode > 0) statement.
    else // Else statement if an error is to occur between the ESP32 and the connection to the database.
    {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    } // Ends the else statement.
  http.end(); // HTTP has ended.
  } // Ends the if((wifiMulti.run() == WL_CONNECTED)) statement.
} // Ends the void loop() statement.
