#define BLYNK_TEMPLATE_ID "TMPLsQNRIqHr"                      // Template name that is used in the Blynk App.
#define BLYNK_DEVICE_NAME "Quickstart Device"                 // Name of device connected to ESP32.
#define BLYNK_AUTH_TOKEN "yjk60Mym1MoYJpTYdtUCG6rH3HThYgDF"   // Authentication Token that is provided to us on the Blynk App.
#define BLYNK_PRINT Serial                                    // Prints out information about the Blynk Process to the Serial Monitor.

#include <WiFi.h>               // Includes the "WiFi.h" library.
#include <WiFiClient.h>         // Includes the "WiFiClient.h" library.
#include <BlynkSimpleEsp32.h>   // Includes the "BlynkSimpleEsp32.h" library.

char auth[] = BLYNK_AUTH_TOKEN; // Authentication Token that is provided to us on the Blynk App.
char ssid[] = "Brr";            // SSID of the current WiFi network the device is connected to.
char pass[] = "00000000";       // Password of the current WiFi network the device is connected to.

BlynkTimer timer; // Adds a timer to the Blynk Process.

BLYNK_WRITE(V0)   // This function is called every time the Virtual Pin 0 state changes.
{
  int value = param.asInt();      // Sets incoming value from Virtual Pin 0 to a variable.
  Blynk.virtualWrite(V1, value);  // Sends data in various formats to Virtual Pin 1.
}

BLYNK_CONNECTED() // This function is called every time the device is connected to the Blynk.Cloud
{
  Blynk.setProperty(V3, "offImageUrl", "Congratulations!"); // Changes the offImageUrl.
  Blynk.setProperty(V3, "onImageUrl", "Congratulations!");  // Changes the onImageUrl.
  Blynk.setProperty(V3, "url", "Congratulations!");         // Changes the url.
}

void myTimerEvent() // This function sends Arduino's uptime every second to Virtual Pin 2.
{
  Blynk.virtualWrite(V2, millis() / 1000); // Sends Arduino's uptime every 1000ms / every 1 second to Virtual Pin 2.
}

void setup()
{
  Serial.begin(115200);           // See the connection status in the Serial Monitor.
  Blynk.begin(auth, ssid, pass);  // Connects the Arduino to the Blynk Cloud.
  // Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);              // Specifying a server.
  // Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080); // Specifying a server.
  timer.setInterval(1000L, myTimerEvent); // Setup a function to be called every second.
}

void loop()
{
  Blynk.run();  // Runs Blynk, super magical stuff.
  timer.run();  // Runs the Timer, tick tock.
}
