#define BLYNK_TEMPLATE_ID "TMPLsQNRIqHr"                      // Template name that is used in the Blynk App.
#define BLYNK_DEVICE_NAME "Quickstart Device"                 // Name of device connected to ESP32.
#define BLYNK_AUTH_TOKEN "yjk60Mym1MoYJpTYdtUCG6rH3HThYgDF"   // Authentication Token that is provided to us on the Blynk App.
#define BLYNK_PRINT Serial                                    // Prints out information about the Blynk Process to the Serial Monitor.

#include <WiFi.h>               // Includes the "WiFi.h" library.
#include <WiFiClient.h>         // Includes the "WiFiClient.h" library.
#include <BlynkSimpleEsp32.h>   // Includes the "BlynkSimpleEsp32.h" library.
#include <Arduino.h>            // Includes the "Arduino.h" library.

char auth[] = BLYNK_AUTH_TOKEN; // Authentication Token that is provided to us on the Blynk App.
char ssid[] = "SKY5337D_5G";    // SSID of the current WiFi network the device is connected to.
char pass[] = "PFDESQSU";       // Password of the current WiFi network the device is connected to.

const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

BlynkTimer timer; // Adds a timer to the Blynk Process.

void timerStart()
{
  Blynk.virtualWrite(V2, trigPin);   // Writes the value of the "trigPin" variable to Virtual Pin 2.
  Blynk.virtualWrite(V3, echoPin);   // Writes the value of the "echoPin" variable to Virtual Pin 3.
}

void setup()
{
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Blynk.begin(auth, ssid, pass);  // Begins the Blynk Process by connecting the Arduino.
  timer.setInterval(100L, timerStart);
}

void loop(void)
{
  Blynk.run();
  timer.run();
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  
  delay(1000);
}
