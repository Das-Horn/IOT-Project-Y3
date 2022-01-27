#define BLYNK_TEMPLATE_ID "TMPLsQNRIqHr"                      // Template name that is used in the Blynk App.
#define BLYNK_DEVICE_NAME "Quickstart Device"                 // Name of device connected to ESP32.
#define BLYNK_AUTH_TOKEN "yjk60Mym1MoYJpTYdtUCG6rH3HThYgDF"   // Authentication Token that is provided to us on the Blynk App.
#define BLYNK_PRINT Serial                                    // Prints out information about the Blynk Process to the Serial Monitor.

#include <WiFi.h>               // Includes the "WiFi.h" library.
#include <WiFiClient.h>         // Includes the "WiFiClient.h" library.
#include <BlynkSimpleEsp32.h>   // Includes the "BlynkSimpleEsp32.h" library.
#include <Arduino.h>            // Includes the "Arduino.h" library.
#include <U8x8lib.h>            // Includes the "U8x8lib.h" library.

char auth[] = BLYNK_AUTH_TOKEN; // Authentication Token that is provided to us on the Blynk App.
char ssid[] = "SKY5337D_5G";    // SSID of the current WiFi network the device is connected to.
char pass[] = "PFDESQSU";       // Password of the current WiFi network the device is connected to.

// Resets the OLED display.
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

const int trigPin = 5;      // Defines Ultrasonic Transmitter Pin Number.
const int echoPin = 18 ;    // Defines Ultrasonic Receiver Pin Number.
const int ledPin = 4;       // Defines Led Pin Number.
const int buzzerPin = 2;    // Defines Buzzer Pin Number.
int distance;         // Variable for Distance.
int safeSpace;        // Variable for Safe Space.
long duration;        // Variable for Duration.

BlynkTimer timer; // Adds a timer to the Blynk Process.

void timerStart()
{
  Blynk.virtualWrite(V2, trigPin);   // Writes the value of the "T" variable to Virtual Pin 2.
  Blynk.virtualWrite(V3, echoPin);   // Writes the value of the "E" variable to Virtual Pin 2.
  Blynk.virtualWrite(V4, ledPin);    // Writes the value of the "L" variable to Virtual Pin 2.
  Blynk.virtualWrite(V5, buzzerPin); // Writes the value of the "B" variable to Virtual Pin 2.
}

void setup(void)
{
  pinMode(trigPin, OUTPUT);       // Sets the trigPin as an Output.
  pinMode(echoPin, INPUT);        // Sets the echoPin as an Input.
  pinMode(ledPin, OUTPUT);        // Sets the ledPin as an Output.
  pinMode(buzzerPin, OUTPUT);     // Sets the buzzerPin as an Output.
  Serial.begin(9600);             // Starts the Serial Monitor Communication.
  delay(10);
  Blynk.begin(auth, ssid, pass);  // Begins the Blynk Process by connecting the Arduino.
  timer.setInterval(100L, timerStart);
  u8x8.begin();                   // Begin the OLED display.
  u8x8.setPowerSave(0);           // Disables Power Save Mode for the Display.
  u8x8.setFlipMode(1);            // Enables Flip Mode, 180 Degree Rotation of the Display Content.
}

void loop(void)
{
  Blynk.run();
  timer.run(); 
  digitalWrite(trigPin, LOW);         // Give a short LOW pulse to ensure a clean HIGH pulse.
  delayMicroseconds(2);               // Adds a delay of 2 microseconds.
  digitalWrite(trigPin, HIGH);        // Sends out a HIGH pulse.
  delayMicroseconds(10);              // Adds a delay of 10 microseconds.
  digitalWrite(trigPin, LOW);         // Sends out a LOW pulse.
  duration = pulseIn(echoPin, HIGH);          // Reads the echoPin, returns the sound wave travel time in microseconds.
  distance = duration * 0.0343 / 2;           // Distance = travel time * speed of sound / 2 (wave transmitted and received).
  u8x8.setFont(u8x8_font_chroma48medium8_r);  // Sets the font of the OLED display.
  u8x8.setCursor(0, 1);                   // Sets the positioning of the text on the OLED display.
  u8x8.print("Distance: ");               // Prints out what’s said on the OLED display.
  u8x8.print(distance);                   // Prints out the variable "distance" on the OLED display.
  safeSpace = distance;                   // Variable safeSpace equals distance.
  if (safeSpace >= 25 || safeSpace<= 0)   // Over the value of 25cm will not turn the buzzer or LED on.
  {
    u8x8.setFont(u8x8_font_chroma48medium8_r);  // Sets the font of the OLED display.
    u8x8.setCursor(0, 0);       // Sets the positioning of the text on the OLED display.
    u8x8.print("Area Clear!");  // Prints out what’s said on the OLED display.
    digitalWrite(buzzerPin, LOW);  // Sets the buzzer to a LOW state, which is OFF.
    digitalWrite(ledPin, LOW);  // Sets the LED to a LOW state, which is OFF.
  }
  else
  {
    u8x8.setFont(u8x8_font_chroma48medium8_r);  // Sets the font of the OLED display.
    u8x8.setCursor(0, 0);         // Sets the positioning of the text on the OLED display.
    u8x8.print("Intruder!!!");    // Prints out what’s said on the OLED display.
    digitalWrite(buzzerPin, HIGH);  // Sets the buzzer to a HIGH state, which is ON.
    digitalWrite(ledPin, HIGH);   // Sets the LED to a HIGH state, which is ON.
  }
  // Prints the distance on the Serial Monitor.
  Serial.print("Distance in CM: "); // Prints out the distance in the Arduino Program.
  Serial.println(distance);         // Prints out the Variable with the actual number of the distance in the Arduino Program.
}
