#include <ArduinoJson.h>        // Includes the ArduinoJson.h Library. https://github.com/bblanchon/ArduinoJson
#include <Arduino.h>            // Includes the Arduino.h Library. https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Arduino.h
#include <WiFi.h>               // Includes the WiFi.h Library. https://github.com/arduino-libraries/WiFi
#include <WiFiMulti.h>          // Includes the WiFiMulti.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFiMulti.h
#include <HTTPClient.h>         // Includes the HTTPClient.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/HTTPClient/src/HTTPClient.h

WiFiMulti wifiMulti;

char ssid[] = "XD";             // SSID of the current WiFi network the device is connected to.
char pass[] = "11111111";       // Password of the current WiFi network the device is connected to.

const int flamePin = 4;         // Sets the Pin of flamePin to 4.
const int buzzerPin = 5;        // Sets the Pin of buzzerPin to 5.
int flame = HIGH;               // Sets the integer value of flame to HIGH.
int redLED = 18;                // Sets the Pin of redLED to 18.
int greenLED = 19;              // Sets the Pin of greenLED to 19.
boolean activeFlame = false;    // Sets the variable of activeFlame to false.

void setup()                    // Starts the void setup().
{
  Serial.begin(115200);         // Starts up the serial monitor communication at a baud rate of 115200.
  Serial.println();             // Prints off data into the serial monitor.
  Serial.println();             // Prints off more data into the serial monitor.
  Serial.println();             // Prints off even more data into the serial monitor.
  
  wifiMulti.addAP(ssid, pass);
  
  Serial.print("[LOCAL] Connecting... \n"); // Prints off that the ESP32 is connecting to the network.
  
  pinMode(flamePin, INPUT); // Sets the flamePin as an INPUT.
  pinMode(buzzerPin, OUTPUT); // Sets the buzzerPin as an Output.
  pinMode(redLED, OUTPUT); // Sets the redLED as an Output.
  pinMode(greenLED, OUTPUT); // Sets the greenLED as an Output.
}

void loop()                     // Start of the void loop().
{
  if((wifiMulti.run() == WL_CONNECTED)) // If statement for when the ESP32 has successfully connected.
  {
    flame = digitalRead(flamePin);
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
        if (doc[6]["Action"] == true)
        {
          activeFlame = true;             // Sets the activeFlame variable to true.
          flame = LOW;                    // Sets the flame variable to LOW.
          digitalWrite(buzzerPin, HIGH);  // Sets the buzzerPin to HIGH, turned on.
          digitalWrite(greenLED, LOW);    // Sets the greenLED to LOW, turned off.
          digitalWrite(redLED, HIGH);     // Sets the redLED to HIGH, turned on.
          Serial.print("[LOCAL] FIRE DETECTED! \n");    // Prints out that a fire has been detected.
        }
        else // Else statement for when no fire has been detected.
        {
          activeFlame = false;          // Sets the activeFlame to false.
          digitalWrite(buzzerPin, LOW); // Sets the buzzerPin to LOW, turned off.
          digitalWrite(greenLED, HIGH); // Sets the greenLED to HIGH, turned on.
          digitalWrite(redLED, LOW);    // Sets the redLED to LOW, turned off.
          Serial.print("[LOCAL] Area Clear! \n");  // Prints out that the area is clear.
        }
        if(error) // If statement for when an error has occured during the Flame Sensor process.
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
