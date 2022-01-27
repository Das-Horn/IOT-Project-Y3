#define BLYNK_TEMPLATE_ID "TMPLsQNRIqHr"                      // Template name that is used in the Blynk App.
#define BLYNK_DEVICE_NAME "Quickstart Device"                 // Name of device connected to ESP32.
#define BLYNK_AUTH_TOKEN "yjk60Mym1MoYJpTYdtUCG6rH3HThYgDF"   // Authentication Token that is provided to us on the Blynk App.
#define BLYNK_PRINT Serial                                    // Prints out information about the Blynk Process to the Serial Monitor.

#include <WiFi.h>               // Includes the "WiFi.h" library.
#include <WiFiClient.h>         // Includes the "WiFiClient.h" library.
#include <BlynkSimpleEsp32.h>   // Includes the "BlynkSimpleEsp32.h" library.
#include <SimpleDHT.h>          // Includes the "SimpleDHT.h" library.
#include <Arduino.h>            // Includes the "Arduino.h" library.
#include <U8x8lib.h>            // Includes the "U8x8lib.h" library.

char auth[] = BLYNK_AUTH_TOKEN; // Authentication Token that is provided to us on the Blynk App.
char ssid[] = "SKY5337D_5G";    // SSID of the current WiFi network the device is connected to.
char pass[] = "PFDESQSDU";      // Password of the current WiFi network the device is connected to.
char server[] = "";             // Specify a server to connect to instead.

// Resets the OLED display.
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

const int trigPin = 5;      // Defines Ultrasonic Transmitter Pin Number.
const int echoPin = 8;      // Defines Ultrasonic Receiver Pin Number.
const int ledPin = 4;       // Defines Arduino LED Pin Number.
const int buzzerPin = 2;    // Defines Arduino Buzzer Pin Number.
int distance;         // Variable for Distance.
int safeSpace;        // Variable for Safe Space.
long duration;        // Variable for Duration.

int LED = 0;         // Defines the LED as an integer.

const int pinDHT11 = 5; // GPIO2 on our ESP32 WiFi Module.
SimpleDHT11 dht11;      // Starts DHT11.
BlynkTimer timer; // Adds a timer to the Blynk Process.

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

void arduinoUptime() // This function sends Arduino's uptime every second to Virtual Pin 2.
{
  Blynk.virtualWrite(V2, millis() / 1000); // Sends Arduino's uptime every 1000ms / every 1 second to Virtual Pin 2.
}

void temperatureHumidity()
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

void ledControl()
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
  pinMode(LED, OUTPUT);           // Sets the LED as an output.
  Serial.begin(115200);           // See the connection status set at 115200 baud in the Serial Monitor.
  delay(10);
  Blynk.begin(auth, ssid, pass);  // Connects the Arduino to the Blynk Cloud.
  // Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);              // Specifying a server.
  // Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080); // Specifying a server.
  timer.setInterval(1000L, arduinoUptime);        // Setup a function to be called every second.
  timer.setInterval(1000L, temperatureHumidity);  // Setup a function to be called every second.
  timer.setInterval(1000L, ledControl);           // Setup a function to be called every second.
  timer.setInterval(1000L, timerStart);           // Setup a function to be called every second.
  u8x8.begin();                   // Begin the OLED display.
  u8x8.setPowerSave(0);           // Disables Power Save Mode for the Display.
  u8x8.setFlipMode(1);            // Enables Flip Mode, 180 Degree Rotation of the Display Content.
}

void loop(void)
{
  Blynk.run();  // Runs Blynk, super magical stuff.
  timer.run();  // Runs the Timer, tick tock.
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
