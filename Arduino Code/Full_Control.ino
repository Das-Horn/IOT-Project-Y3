#include <ESP32Servo.h>     // Includes the ESP32Servo.h Library. (╯°□°)╯︵ ┻━┻
#include <HTTPClient.h>
#include <ArduinoJson.h>        // Includes the ArduinoJson.h Library. https://github.com/bblanchon/ArduinoJson
#include <Arduino.h>            // Includes the Arduino.h Library. https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Arduino.h
#include <WiFi.h>               // Includes the WiFi.h Library. https://github.com/arduino-libraries/WiFi
#include <WiFiMulti.h>          // Includes the WiFiMulti.h Library. https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFiMulti.h
#include <DHT.h>

WiFiMulti wifiMulti;

#define DHTPIN 33            // The Temperature and Humidity Sensor is plugged into Pin 4.
#define DHTTYPE DHT11             // The Version of Temperature and Humidity Sensor we are using is the DHT11.

char ssid[] = "Brr";             // SSID of the current WiFi network the device is connected to.
char pass[] = "00000000";       // Password of the current WiFi network the device is connected to.
String add_Data_URL_Temp = "https://iot-project-y3.vercel.app/api/Update/Data/3/Temp/";   // URL for the Temperature Data.
String add_Data_URL_Humid = "https://iot-project-y3.vercel.app/api/Update/Data/3/Humid/"; // URL for the Humidity Data.
String add_Data_URL_Heat = "https://iot-project-y3.vercel.app/api/Update/Data/3/Heat/";   // URL for the Heat Index Data.
String sensor_ID = "1";


// Variables for the LEDs 
int ledPin1 = 19;                // Sets the Pin of ledPin1 top right.
int ledPin2 = 18;                // Sets the Pin of ledPin2 top left.
int ledPin3 = 21;                // Sets the Pin of ledPin3 bottom left.
int ledPin4 = 4;                 // Sets the Pin of ledPin4 bottom right.

// Variables for the ultra-sonic sensor
int trigPin = 26;            // Defines Ultrasonic Transmitter Pin Number.
int echoPin = 27;            // Defines Ultrasonic Receiver Pin Number.
int buzzerPin = 22;          // Defines Arduino Buzzer Pin Number.
boolean ultraState = LOW;   // Sets the state of the Ultrasonic Sensor to Low. (╯°□°)╯︵ ┻━┻
int distance;               // Variable for Distance.
int safeSpace;              // Variable for Safe Space.
long duration;              // Variable for Duration.
boolean activeSec = false;  // Sets the variable of activeSec (active security) to false.

// Variables for the flame sensor
int flame = HIGH;               // Sets the integer value of flame to HIGH.
int redLED = 23;                // Sets the Pin of redLED
boolean activeFlame = false;    // Sets the variable of activeFlame to false.

// Variables for the door lock
bool door = false;
int pos = 5;
Servo doorlock;
// Variables for temperature sensor
float temperature = 0;            // Makes a variable called temperature that is set to 0.
float humidity = 0;               // Makes a variable called humidity that is set to 0.
DHT dht(DHTPIN, DHTTYPE);                          // Starts the DHT11.

void setup()                    // Starts the void setup().
{
  Serial.begin(115200);         // Starts up the serial monitor communication at a baud rate of 115200.
  Serial.println();             // Prints off data into the serial monitor.
  Serial.println();             // Prints off more9 data into the serial monitor.
  Serial.println();             // Prints off even more data into the serial monitor.
  
  wifiMulti.addAP(ssid, pass);
  
  Serial.print("[LOCAL] Connecting... \n"); // Prints off that the ESP32 is connecting to the network.

  // Pinmode declaration for the LEDs.
  pinMode(ledPin1, OUTPUT);     // Sets the ledPin as an Output.
  pinMode(ledPin2, OUTPUT);     // Sets the ledPin as an Output.
  pinMode(ledPin3, OUTPUT);     // Sets the ledPin as an Output.
  pinMode(ledPin4, OUTPUT);     // Sets the ledPin as an Output.

  // Pinmode declaration for the security system.
  pinMode(trigPin, OUTPUT);     // Sets the trigPin as an Output.
  pinMode(echoPin, INPUT);      // Sets the echoPin as an Input.
  pinMode(buzzerPin, OUTPUT);   // Sets the buzzerPin as an Output.

  // Pinmode declaration for the flame sensor example.
  pinMode(redLED, OUTPUT); // Sets the redLED as an Output. UwU

  // Setup for the doorlock
  doorlock.attach(32);
  doorlock.write(pos);

  // Setup for the dht11
  dht.begin();
  
}

void loop()
{
  DynamicJsonDocument jasonData = connectDB();
  ledControl(jasonData);
  secSystem(jasonData);
  flameSensorEx(jasonData);
  doorLock(jasonData);
  tempSensor(jasonData);
  secSystem(jasonData);

  Serial.print("------------------------------------ \n");
}

DynamicJsonDocument connectDB() 
{
  DynamicJsonDocument doc(1023);
  if((wifiMulti.run() == WL_CONNECTED)) // If statement for when the ESP32 has successfully connected.
  {
    Serial.print("[LOCAL] Connection established \n");                  // Prints off that the ESP32 has established a connection.
    String url = "https://iot-project-y3.vercel.app/api/Requests/jobs"; // This is the URL of our database which the ESP32 wants to connect to. (╯°□°)╯︵ ┻━┻
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
            digitalWrite(leds[i-2], HIGH);
          }
          else
          {
            digitalWrite(leds[i-2], LOW);
          }
        }
            
      return 0;
  } 

 int secSystem(DynamicJsonDocument doc)
  {
    digitalWrite(trigPin, LOW);     // Give a short LOW pulse to ensure a clean HIGH pulse.
    delayMicroseconds(2);           // Adds a delay of 2 microseconds.
    digitalWrite(trigPin, HIGH);    // Sends out a HIGH pulse.
    delayMicroseconds(10);          // Adds a delay of 10 microseconds.
    digitalWrite(trigPin, LOW);     // Sends out a LOW pulse.
    duration = pulseIn(echoPin, HIGH);          // Reads the echoPin, returns the sound wave travel time in microseconds.
    distance = duration * 0.0343 / 2;           // Distance = travel time * speed of sound / 2 (wave transmitted and received).
    safeSpace = distance;                       // Variable safeSpace equals distance.

    if (doc[1]["Action"] == true)
        {
          activeSec = true;
          Serial.print("[LOCAL] Security is active \n");  // Prints out that the Security has been turned on.
        }
    else  // Else statement for when the Security is turned off.
        {
          activeSec = false;            // Sets the activeSec to false.
          ultraState = LOW;             // Sets the pirState to LOW.
          digitalWrite(buzzerPin, LOW); // Sets the buzzer to a LOW state meaning it's turned off.
        }
    if (activeSec == true)            // If statement for when the security is activated.
    {
      if (distance <= 18)                // If statement for when the value is HIGH.
      {
        ultraState = HIGH;            // Sets the pirState to HIGH.
      }
      Serial.println(distance);
      digitalWrite(buzzerPin, ultraState);      // Sets the buzzer on a HIGH state meaning it's turned on.++
      
    } // Ends the if (activeSec == true) statement.
    return 0;
  }

 int flameSensorEx(DynamicJsonDocument doc)
 {
  if (doc[6]["Action"] == true)
        {
          activeFlame = true;             // Sets the activeFlame variable to true.
          flame = LOW;                    // Sets the flame variable to LOW.
          digitalWrite(buzzerPin, HIGH);  // Sets the buzzerPin to HIGH, turned on.
          delay(100);
          digitalWrite(buzzerPin, LOW);  // Sets the buzzerPin to LOW, turned off.
          delay(100);
          digitalWrite(buzzerPin, HIGH);  // Sets the buzzerPin to HIGH, turned on.
          delay(100);
          digitalWrite(buzzerPin, LOW);  // Sets the buzzerPin to LOW, turned off.
          digitalWrite(redLED, HIGH);     // Sets the redLED to HIGH, turned on.
          Serial.print("[LOCAL] FIRE DETECTED! \n");    // Prints out that a fire has been detected.
        }
        else if (doc[6]["Action"] != true)  // Else statement for when no fire has been detected.
        {
          activeFlame = false;          // Sets the activeFlame to false.
          digitalWrite(redLED, LOW);    // Sets the redLED to LOW, turned off.
        }
   return 0;
 }

 int doorLock(DynamicJsonDocument doc)
 {
  if (doc[7]["Action"] == true)
        {
          door = true;
        }
        else
        {
          door = false;
        }
        if (door == true)
        {
          pos = 105;
          doorlock.write(pos);
        }
        else if (door == false)
        {
          pos = 5;
          doorlock.write(pos);
        }
 }

int tempSensor(DynamicJsonDocument doc)
{
  if((wifiMulti.run() == WL_CONNECTED)) // If statement for when the ESP32 has successfully connected. (╯°□°)╯︵ ┻━┻
  {
    float h = dht.readHumidity();                     // Read humidity as H (the default).
    float t = dht.readTemperature();                  // Read temperature as Celsius (the default).
    float f = dht.readTemperature(true);              // Read temperature as Fahrenheit (isFahrenheit = true).if (isnan(h) || isnan(t) || isnan(f))       // If statement for the humidity, temperature (celsius), and temperature (fahrenheit).
    if (isnan(h) || isnan(t) || isnan(f))             // If statement for the humidity, temperature (celsius), and temperature (fahrenheit).
    {
      Serial.println(F("Failed to read from DHT sensor!")); // Prints out text when a reading from the DHT sensor has failed.
      return 0;                                               // Terminate a function and return a value from a function to the calling function, if desired.
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
    if(httpCode > 0)                // If statement for when the data given back from the database is set to 0. (╯°□°)╯︵ ┻━┻
    {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);  // Prints out the HTTP Code number, should be 200.
      if(httpCode == HTTP_CODE_OK)                          // If statement for when the HTTP Code number is ok.
      {
        String inData = http.getString();
        DynamicJsonDocument doc(1023);
        DeserializationError error = deserializeJson(doc, inData);
        Serial.print("[LOCAL] DHT is sending data. \n");   // Prints out that the DHT is sending data.
        delay(500);                                // Adds a delay of 1 seconds between each reading.
        int h = dht.readHumidity();                 // Read humidity as H (the default).
        int t = dht.readTemperature();              // Read temperature as Celsius (the default).
        int f = dht.readTemperature(true);          // Read temperature as Fahrenheit (isFahrenheit = true).
        if (isnan(h) || isnan(t) || isnan(f))       // If statement for the humidity, temperature (celsius), and temperature (fahrenheit).
        {
          Serial.println(F("Failed to read from DHT sensor!")); // Prints out text when a reading from the DHT sensor has failed.
          return 0;                                               // Terminate a function and return a value from a function to the calling function, if desired.
        }
        int hif = dht.computeHeatIndex(f, h);         // Compute heat index in Fahrenheit (the default)
        int hic = dht.computeHeatIndex(t, h, false);  // Compute heat index in Celsius (isFahreheit = false)
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
        delay(500);                                // Adds a delay of 1 seconds between each reading.
        int h = dht.readHumidity();                 // Read humidity as H (the default).
        int t = dht.readTemperature();              // Read temperature as Celsius (the default).
        int f = dht.readTemperature(true);          // Read temperature as Fahrenheit (isFahrenheit = true).
        if (isnan(h) || isnan(t) || isnan(f))       // If statement for the humidity, temperature (celsius), and temperature (fahrenheit).
        {
          Serial.println(F("Failed to read from DHT sensor!")); // Prints out text when a reading from the DHT sensor has failed.
          return 0;                                               // Terminate a function and return a value from a function to the calling function, if desired.
        }
        int hif = dht.computeHeatIndex(f, h);         // Compute heat index in Fahrenheit (the default)
        int hic = dht.computeHeatIndex(t, h, false);  // Compute heat index in Celsius (isFahreheit = false)
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
        delay(500);                                // Adds a delay of 1 seconds between each reading.
        int h = dht.readHumidity();                 // Read humidity as H (the default).
        int t = dht.readTemperature();              // Read temperature as Celsius (the default).
        int f = dht.readTemperature(true);          // Read temperature as Fahrenheit (isFahrenheit = true).
        if (isnan(h) || isnan(t) || isnan(f))       // If statement for the humidity, temperature (celsius), and temperature (fahrenheit).
        {
          Serial.println(F("Failed to read from DHT sensor!")); // Prints out text when a reading from the DHT sensor has failed.
          return 0;                                               // Terminate a function and return a value from a function to the calling function, if desired.
        }
        int hif = dht.computeHeatIndex(f, h);         // Compute heat index in Fahrenheit (the default)
        int hic = dht.computeHeatIndex(t, h, false);  // Compute heat index in Celsius (isFahreheit = false) (╯°□°)╯︵ ┻━┻
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
  }
}
