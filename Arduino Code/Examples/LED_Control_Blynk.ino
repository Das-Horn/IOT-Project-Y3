#define BLYNK_TEMPLATE_ID "TMPLsQNRIqHr"                      // Template name that is used in the Blynk App.
#define BLYNK_DEVICE_NAME "Quickstart Device"                 // Name of device connected to ESP32.
#define BLYNK_AUTH_TOKEN "yjk60Mym1MoYJpTYdtUCG6rH3HThYgDF"   // Authentication Token that is provided to us on the Blynk App.
#define BLYNK_PRINT Serial                                    // Prints out information about the Blynk Process to the Serial Monitor.

#include <WiFi.h>               // Includes the "WiFi.h" library.
#include <WiFiClient.h>         // Includes the "WiFiClient.h" library.
#include <BlynkSimpleEsp32.h>   // Includes the "BlynkSimpleEsp32.h" library.

char auth[] = BLYNK_AUTH_TOKEN; // Authentication Token that is provided to us on the Blynk App.
char ssid[] = "SKY5337D_5G";            // SSID of the current WiFi network the device is connected to.
char pass[] = "PFDESQSU";       // Password of the current WiFi network the device is connected to.
char server[] = "";             // Specify a server to connect to instead.

int LED = 21;

void setup()
{  
  pinMode(LED, OUTPUT); 
  pinMode(LED, HIGH);
  Serial.begin(115200);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");  
  Blynk.begin("Your auth token key", ssid, pass);
}

void loop()
{
  Blynk.run();
}
