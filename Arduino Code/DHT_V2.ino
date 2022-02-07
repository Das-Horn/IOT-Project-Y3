#include <ArduinoJson.h>          // Includes the ArduinoJson.h Library. https://github.com/bblanchon/ArduinoJson
#include <Arduino.h>              // Includes the Arduino.h Library. https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Arduino.h
#include <WiFi.h>                 // Includes the WiFi.h Library. https://github.com/arduino-libraries/WiFi
#include <WiFiMulti.h>            // Includes the WiFiMulti.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFiMulti.h
#include <HTTPClient.h>           // Includes the HTTPClient.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/HTTPClient/src/HTTPClient.h
#include <DHT.h>                  // Includes the DHT.h Library for use with the Temperature and Humidity Sensor. https://github.com/adafruit/DHT-sensor-library/blob/master/DHT.h

#define DHTPIN 4                  // The Temperature and Humidity Sensor is plugged into Pin 4.
#define DHTTYPE DHT11             // The Version of Temperature and Humidity Sensor we are using is the DHT11.

WiFiMulti wifiMulti;

DHT dht(DHTPIN, DHTTYPE);         // Initialise the DHT11 Sensor on Pin 4.

char ssid[] = "XD";             // SSID of the current WiFi network the device is connected to.
char pass[] = "11111111";       // Password of the current WiFi network the device is connected to.
char server[] = "10.147.19.10"; // Sets the Server IP Address to that of the database we want to connect to.
String add_Data_URL_Temp = "https://iot-project-y3.vercel.app/api/Update/Data/3/Temp/";   // URL for the Temperature Data.
String add_Data_URL_Humid = "https://iot-project-y3.vercel.app/api/Update/Data/3/Humid/"; // URL for the Humidity Data.
String add_Data_URL_Heat = "https://iot-project-y3.vercel.app/api/Update/Data/3/Heat/";   // URL for the Heat Index Data.
String sensor_ID = "1";

void setup()                      // Start of the void setup().
{
  Serial.begin(115200);           // Starts the Serial Communication and has it set at a baud rate of 115200.
  
  Serial.println();               // Prints off data into the serial monitor.
  Serial.println();               // Prints off more data into the serial monitor.
  Serial.println();               // Prints off even more data into the serial monitor.
  
  wifiMulti.addAP(ssid, pass);
  
  Serial.println(F("Start of the Temperature and Humidity Analysis!"));  // Prints out a statement stating the Program Name.

  Serial.print("[LOCAL] Connecting... \n");                 // Prints off that the ESP32 is connecting to the network.
  
  dht.begin();                                              // Begins the DHT sensor which will begin to analyse the current temperature, humiditity and heat index.
}

void loop() // Start of the void loop().
{
  if((wifiMulti.run() == WL_CONNECTED)) // If statement for when the ESP32 has successfully connected.
  {
    float h = dht.readHumidity();                     // Read humidity as H (the default).
    float t = dht.readTemperature();                  // Read temperature as Celsius (the default).
    float f = dht.readTemperature(true);              // Read temperature as Fahrenheit (isFahrenheit = true).if (isnan(h) || isnan(t) || isnan(f))       // If statement for the humidity, temperature (celsius), and temperature (fahrenheit).
    if (isnan(h) || isnan(t) || isnan(f))             // If statement for the humidity, temperature (celsius), and temperature (fahrenheit).
    {
      Serial.println(F("Failed to read from DHT sensor!")); // Prints out text when a reading from the DHT sensor has failed.
      return;                                               // Terminate a function and return a value from a function to the calling function, if desired.
    }
    float hif = dht.computeHeatIndex(f, h);         // Compute heat index in Fahrenheit (the default)
    float hic = dht.computeHeatIndex(t, h, false);  // Compute heat index in Celsius (isFahreheit = false)
    Serial.print("[LOCAL] Connection established. \n");         // Prints off that the ESP32 has established a connection.
    String urlTemp = add_Data_URL_Temp+t+"/"+sensor_ID;         // This is the URL for the Temperature which the ESP32 wants to connect to.
    String urlHumid = add_Data_URL_Humid+h+"/"+sensor_ID;       // This is the URL for the Humidity which the ESP32 wants to connect to.
    String urlHeat = add_Data_URL_Heat+hic+"/"+sensor_ID;       // This is the URL for the Heat Index which the ESP32 wants to connect to.
    Serial.print("[LOCAL] Attempting connection to DB... \n");  // Prints off that the ESP32 is attempting connection to the database.
    HTTPClient http;
    http.begin(urlTemp);            // Begins the HTTP protocol.
    int httpCode = http.GET();      // Requests data from the database.
    if(httpCode > 0)                // If statement for when the data given back from the database is set to 0.
    {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);  // Prints out the HTTP Code number, should be 200.
      if(httpCode == HTTP_CODE_OK)                          // If statement for when the HTTP Code number is ok.
      {
        String inData = http.getString();
        DynamicJsonDocument doc(1023);
        DeserializationError error = deserializeJson(doc, inData);
        Serial.print("[LOCAL] DHT is sending data. \n");   // Prints out that the DHT is sending data.
        delay(2000);                                // Adds a delay of 2 seconds between each reading.
        int h = dht.readHumidity();                 // Read humidity as H (the default).
        int t = dht.readTemperature();              // Read temperature as Celsius (the default).
        int f = dht.readTemperature(true);          // Read temperature as Fahrenheit (isFahrenheit = true).
        if (isnan(h) || isnan(t) || isnan(f))       // If statement for the humidity, temperature (celsius), and temperature (fahrenheit).
        {
          Serial.println(F("Failed to read from DHT sensor!")); // Prints out text when a reading from the DHT sensor has failed.
          return;                                               // Terminate a function and return a value from a function to the calling function, if desired.
        }
        int hif = dht.computeHeatIndex(f, h);         // Compute heat index in Fahrenheit (the default)
        int hic = dht.computeHeatIndex(t, h, false);  // Compute heat index in Celsius (isFahreheit = false)
        Serial.print(F("Humidity: "));                  // Prints out the text "Humidity: ".
        Serial.print(h);                                // Prints out the value of the variable "h".
        Serial.print(F("%,  Temperature: "));           // Prints out the text "%,  Temperature: ".
        Serial.print(t);                                // Prints out the value of the variable "t".
        Serial.print(F("°C / "));                       // Prints out the text "°C / ".
        Serial.print(f);                                // Prints out the value of the variable "f".
        Serial.print(F("°F,  Heat Index: "));           // Prints out the text "°F,  Heat Index: ".
        Serial.print(hic);                              // Prints out the value of the variable "hic".
        Serial.print(F("°C / "));                       // Prints out the text "°C / ".
        Serial.print(hif);                              // Prints out the value of the variable "hif".
        Serial.println(F("°F"));                        // Prints out the text "°F".
        http.end();                                     // HTTP has ended.
      } // Ends the if(httpCode == HTTP_CODE_OK) statement.
    }   // Ends the if(httpCode > 0) statement.
    http.begin(urlHumid);                 // Begins the HTTP protocol.
    int httpCodeHumid = http.GET();       // Requests data from the database.
    if(httpCodeHumid > 0)                 // If statement for when the data given back from the database is set to 0.
    {
      Serial.printf("[HTTP] GET... code: %d\n", httpCodeHumid);  // Prints out the HTTP Code number, should be 200.
      if(httpCodeHumid == HTTP_CODE_OK)                          // If statement for when the HTTP Code number is ok.
      {
        String inData = http.getString();
        DynamicJsonDocument doc(1023);
        DeserializationError error = deserializeJson(doc, inData);
        Serial.print("[LOCAL] DHT is sending data. \n");   // Prints out that the DHT is sending data.
        delay(2000);                                // Adds a delay of 2 seconds between each reading.
        int h = dht.readHumidity();                 // Read humidity as H (the default).
        int t = dht.readTemperature();              // Read temperature as Celsius (the default).
        int f = dht.readTemperature(true);          // Read temperature as Fahrenheit (isFahrenheit = true).
        if (isnan(h) || isnan(t) || isnan(f))       // If statement for the humidity, temperature (celsius), and temperature (fahrenheit).
        {
          Serial.println(F("Failed to read from DHT sensor!")); // Prints out text when a reading from the DHT sensor has failed.
          return;                                               // Terminate a function and return a value from a function to the calling function, if desired.
        }
        int hif = dht.computeHeatIndex(f, h);         // Compute heat index in Fahrenheit (the default)
        int hic = dht.computeHeatIndex(t, h, false);  // Compute heat index in Celsius (isFahreheit = false)
        Serial.print(F("Humidity: "));                  // Prints out the text "Humidity: ".
        Serial.print(h);                                // Prints out the value of the variable "h".
        Serial.print(F("%,  Temperature: "));           // Prints out the text "%,  Temperature: ".
        Serial.print(t);                                // Prints out the value of the variable "t".
        Serial.print(F("°C / "));                       // Prints out the text "°C / ".
        Serial.print(f);                                // Prints out the value of the variable "f".
        Serial.print(F("°F,  Heat Index: "));           // Prints out the text "°F,  Heat Index: ".
        Serial.print(hic);                              // Prints out the value of the variable "hic".
        Serial.print(F("°C / "));                       // Prints out the text "°C / ".
        Serial.print(hif);                              // Prints out the value of the variable "hif".
        Serial.println(F("°F"));                        // Prints out the text "°F".
        http.end();                                     // HTTP has ended.
      } // Ends the if(httpCode == HTTP_CODE_OK) statement.
    }   // Ends the if(httpCode > 0) statement.
    http.begin(urlHeat);                 // Begins the HTTP protocol.
    int httpCodeHeat = http.GET();       // Requests data from the database.
    if(httpCodeHeat > 0)                 // If statement for when the data given back from the database is set to 0.
    {
      Serial.printf("[HTTP] GET... code: %d\n", httpCodeHeat);  // Prints out the HTTP Code number, should be 200.
      if(httpCodeHeat == HTTP_CODE_OK)                          // If statement for when the HTTP Code number is ok.
      {
        String inData = http.getString();
        DynamicJsonDocument doc(1023);
        DeserializationError error = deserializeJson(doc, inData);
        Serial.print("[LOCAL] DHT is sending data. \n");   // Prints out that the DHT is sending data.
        delay(2000);                                // Adds a delay of 2 seconds between each reading.
        int h = dht.readHumidity();                 // Read humidity as H (the default).
        int t = dht.readTemperature();              // Read temperature as Celsius (the default).
        int f = dht.readTemperature(true);          // Read temperature as Fahrenheit (isFahrenheit = true).
        if (isnan(h) || isnan(t) || isnan(f))       // If statement for the humidity, temperature (celsius), and temperature (fahrenheit).
        {
          Serial.println(F("Failed to read from DHT sensor!")); // Prints out text when a reading from the DHT sensor has failed.
          return;                                               // Terminate a function and return a value from a function to the calling function, if desired.
        }
        int hif = dht.computeHeatIndex(f, h);         // Compute heat index in Fahrenheit (the default)
        int hic = dht.computeHeatIndex(t, h, false);  // Compute heat index in Celsius (isFahreheit = false)
        Serial.print(F("Humidity: "));                  // Prints out the text "Humidity: ".
        Serial.print(h);                                // Prints out the value of the variable "h".
        Serial.print(F("%,  Temperature: "));           // Prints out the text "%,  Temperature: ".
        Serial.print(t);                                // Prints out the value of the variable "t".
        Serial.print(F("°C / "));                       // Prints out the text "°C / ".
        Serial.print(f);                                // Prints out the value of the variable "f".
        Serial.print(F("°F,  Heat Index: "));           // Prints out the text "°F,  Heat Index: ".
        Serial.print(hic);                              // Prints out the value of the variable "hic".
        Serial.print(F("°C / "));                       // Prints out the text "°C / ".
        Serial.print(hif);                              // Prints out the value of the variable "hif".
        Serial.println(F("°F"));                        // Prints out the text "°F".
        http.end();                                     // HTTP has ended.
      } // Ends the if(httpCode == HTTP_CODE_OK) statement.
    }   // Ends the if(httpCode > 0) statement.
  }     // Ends the if((wifiMulti.run() == WL_CONNECTED)) statement.
}       // Ends the void loop().
