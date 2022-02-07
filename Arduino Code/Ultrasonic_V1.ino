#include <ArduinoJson.h>    // Includes the ArduinoJson.h Library. https://github.com/bblanchon/ArduinoJson
#include <Arduino.h>        // Includes the Arduino.h Library. https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Arduino.h
#include <WiFi.h>           // Includes the WiFi.h Library. https://github.com/arduino-libraries/WiFi
#include <WiFiMulti.h>      // Includes the WiFiMulti.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFiMulti.h
#include <HTTPClient.h>     // Includes the HTTPClient.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/HTTPClient/src/HTTPClient.h

WiFiMulti wifiMulti;

char ssid[] = "XD";         // SSID of the current WiFi network the device is connected to.
char pass[] = "11111111";   // Password of the current WiFi network the device is connected to.

int trigPin = 2;            // Defines Ultrasonic Transmitter Pin Number.
int echoPin = 4;            // Defines Ultrasonic Receiver Pin Number.
int ledPin = 18;            // Defines Arduino LED Pin Number.
int buzzerPin = 5;          // Defines Arduino Buzzer Pin Number.
boolean ultraState = LOW;   // Sets the state of the Ultrasonic Sensor to Low.
int distance;               // Variable for Distance.
int safeSpace;              // Variable for Safe Space.
long duration;              // Variable for Duration.
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
  
  pinMode(trigPin, OUTPUT);     // Sets the trigPin as an Output.
  pinMode(echoPin, INPUT);      // Sets the echoPin as an Input.
  pinMode(ledPin, OUTPUT);      // Sets the ledPin as an Output.
  pinMode(buzzerPin, OUTPUT);   // Sets the buzzerPin as an Output.
}

void loop()                     // Start of the void loop().
{
  if((wifiMulti.run() == WL_CONNECTED)) // If statement for when the ESP32 has successfully connected.
  {
    digitalWrite(trigPin, LOW);     // Give a short LOW pulse to ensure a clean HIGH pulse.
    delayMicroseconds(2);           // Adds a delay of 2 microseconds.
    digitalWrite(trigPin, HIGH);    // Sends out a HIGH pulse.
    delayMicroseconds(10);          // Adds a delay of 10 microseconds.
    digitalWrite(trigPin, LOW);     // Sends out a LOW pulse.
    duration = pulseIn(echoPin, HIGH);          // Reads the echoPin, returns the sound wave travel time in microseconds.
    distance = duration * 0.0343 / 2;           // Distance = travel time * speed of sound / 2 (wave transmitted and received).
    safeSpace = distance;                       // Variable safeSpace equals distance.
    Serial.print("[LOCAL] Connection established \n");            // Prints off that the ESP32 has established a connection.
    String url = "https://iot-project-y3.vercel.app/api/Requests/jobs";  // This is the URL of our database which the ESP32 wants to connect to.
    Serial.print("[LOCAL] Attempting connection to DB... \n");    // Prints off that the ESP32 is attempting connection to the database.
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
          activeSec = false;            // Sets the activeSec to false.
          ultraState = LOW;             // Sets the pirState to LOW.
          digitalWrite(ledPin, LOW);    // Sets the led to a LOW state meaning it's turned off.
          digitalWrite(buzzerPin, LOW); // Sets the buzzer to a LOW state meaning it's turned off.
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
    value = distance;  // Value is equal to the digital read of the Ultrasonic Sensor.
    if (activeSec == true)            // If statement for when the security is activated.
    {
      if (value <= 25)                // If statement for when the value is HIGH.
      {
        ultraState = HIGH;            // Sets the pirState to HIGH.
      }
      Serial.println(value);
      Serial.println(ultraState);
      digitalWrite(ledPin, ultraState);         // Sets the led on a HIGH state meaning it's turned on.
      digitalWrite(buzzerPin, ultraState);      // Sets the buzzer on a HIGH state meaning it's turned on.
      Serial.println("Motion detected!"); // Prints out a statement saying "Motion detected!".
    } // Ends the if (activeSec == true) statement.
    http.end(); // HTTP has ended.
  } // Ends the if((wifiMulti.run() == WL_CONNECTED)) statement.
} // Ends the void loop().
