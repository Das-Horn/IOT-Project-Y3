#define BLYNK_TEMPLATE_ID "TMPLsQNRIqHr"                      // Template name that is used in the Blynk App.
#define BLYNK_DEVICE_NAME "Quickstart Device"                 // Name of device connected to ESP32.
#define BLYNK_AUTH_TOKEN "yjk60Mym1MoYJpTYdtUCG6rH3HThYgDF"   // Authentication Token that is provided to us on the Blynk App.
#define BLYNK_PRINT Serial                                    // Prints out information about the Blynk Process to the Serial Monitor.

#include <WiFi.h>                 // Includes the "WiFi.h" library.
#include <WiFiClient.h>           // Includes the "WiFiClient.h" library.
#include <BlynkSimpleEsp32.h>     // Includes the "BlynkSimpleEsp32.h" library.
#include <SimpleDHT.h>            // Includes the "SimpleDHT.h" library.

char auth[] = BLYNK_AUTH_TOKEN;   // Authentication Token that is provided to us on the Blynk App.
char ssid[] = "XD";              // SSID of the current WiFi network the device is connected to.
char pass[] = "11111111";         // Password of the current WiFi network the device is connected to.

const int pinDHT11 = 5;           // GPIO2 on our ESP32 WiFi Module.
SimpleDHT11 dht11;                // Starts DHT11.
BlynkTimer timer;                 // Adds a timer to the Blynk Process.

BLYNK_WRITE(V0)   // This function is called every time the Virtual Pin 0 state changes.
{
  int value = param.asInt();      // Sets incoming value from Virtual Pin 0 to a variable.
  Blynk.virtualWrite(V1, value);  // Sends data in various formats to Virtual Pin 1.
}

BLYNK_CONNECTED() // This function is called every time the device is connected to the Blynk Cloud.
{
  Blynk.setProperty(V3, "offImageUrl", "Congratulations!"); // Changes the offImageUrl.
  Blynk.setProperty(V3, "onImageUrl", "Congratulations!");  // Changes the onImageUrl.
  Blynk.setProperty(V3, "url", "Congratulations!");         // Changes the url.
}

void sendSensor()
{
  byte temperature = 0;           // Makes a variable called temperature that is equal to 0.
  byte humidity = 0;              // Makes a variable called humidity that is equal to 0.
  int err = SimpleDHTErrSuccess;  // Error exception that passes when DHT is successful.
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000); // Prints out that DHT11 failed.
    return;
  }
  Serial.print("Results: ");          // Prints out "Results: ".
  Serial.print((int)temperature); Serial.print(" *C, ");  // Prints out the Temperature in Celsius.
  Serial.print((int)humidity); Serial.println(" H");      // Prints out the Humidity in H.
  delay(1000);                          // Adds a delay of 1000ms or 1 second.
  Blynk.virtualWrite(V4, temperature);  // Writes temperature value to Virtual Pin 4.
  Blynk.virtualWrite(V5, humidity);     // Writes humidity value to Virtual Pin 5.
}

void setup()
{
  Serial.begin(9600);                   // Starts the Serial Monitor Communication.
  Blynk.begin(auth, ssid, pass);        // Connects the Arduino to the Blynk Cloud.
  timer.setInterval(1000L, sendSensor); // Setup a function to be called every second.
}

void loop()
{
  Blynk.run();  // Runs Blynk, super magical stuff.
  timer.run();  // Runs the timer, tick tock.
}
