#define BLYNK_TEMPLATE_ID "TMPLsQNRIqHr"                      // Template name that is used in the Blynk App.
#define BLYNK_DEVICE_NAME "Quickstart Device"                 // Name of device connected to ESP32.
#define BLYNK_AUTH_TOKEN "yjk60Mym1MoYJpTYdtUCG6rH3HThYgDF"   // Authentication Token that is provided to us on the Blynk App.
#define BLYNK_PRINT Serial                                    // Prints out information about the Blynk Process to the Serial Monitor.

#include <WiFi.h>               // Includes the "WiFi.h" library.
#include <WiFiClient.h>         // Includes the "WiFiClient.h" library.
#include <BlynkSimpleEsp32.h>   // Includes the "BlynkSimpleEsp32.h" library.

char auth[] = BLYNK_AUTH_TOKEN; // Authentication Token that is provided to us on the Blynk App.
char ssid[] = "SKY5337D_5G";    // SSID of the current WiFi network the device is connected to.
char pass[] = "PFDESQSU";       // Password of the current WiFi network the device is connected to.

int LED = 0; // Defines the LED as an integer.

void setup()
{
  Serial.begin(115200);           // See the connection status in the Serial Monitor.
  pinMode(LED, OUTPUT);           // Sets the LED as an output.
  Blynk.begin(auth, ssid, pass);  // Connects the Arduino to the Blynk Cloud.
}

void loop()
{
  Blynk.run();  // Runs Blynk.
}

BLYNK_WRITE(V3) // Function that writes values to the Virtual Pin 3.
{
  int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable.
  if (pinValue == 1)            // If statement for when the pinValue is equal to 1.
  {
    digitalWrite(LED, HIGH);    // Turns the LED on.
  }
  else
  {
    digitalWrite(LED, LOW);     // Turns the LED off.
  }
}
