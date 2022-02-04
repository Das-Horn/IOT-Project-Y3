#include <LiquidCrystal.h>      // Includes the LiquidCrystal.h Library for use with a LCD Display. https://github.com/arduino-libraries/LiquidCrystal
#include <DHT.h>                // Includes the DHT.h Library for use with the Temperature and Humidity Sensor. https://github.com/adafruit/DHT-sensor-library/blob/master/DHT.h

#define DHTPIN 4                // The Temperature and Humidity Sensor is plugged into Pin 4.
#define DHTYPE DHT11            // The Version of Temperature and Humidity Sensor we are using is the DHT11.

// Pins on the DHT11 (3 Pin Variant) from left to right, (1) Signal   (2) VCC (+)   (3) Ground (-)
// Pins on the DHT11 (4 Pin Variant) from left to right, (1) VCC (+)  (2) Signal    (3) Not Used    (4) Ground (-)

// Note: DHT11 (3 Pin Variant) also features a 10K Ohm Pull Up Resistor on the far left of the Sensor.

DHT dht(DHTPIN, DHTYPE);        // Initialise the DHT11 Sensor on Pin 4.

/*LiquidCrystal lcd(13, 12, 21, 19, 18, 5);*/

void printTempStats();          // Function to print off the values of Celsius, Fahrenheit and Humidity.

void setup()                    // Start of the void setup() function.
{
  Serial.begin(115200);         // Starts the Serial Communcation on a baud rate of 115200.
  /*lcd.begin(16, 2);
  lcd.print("Begining program...");*/
  dht.begin();                  // Begins the DHT
  delay(500);                   // Adds a delay of 500ms or 5 seconds.
  Serial.println("Starting Temperature and Humidity Sensor!");  // Prints out that the DHT Sensor has started.
}

void loop()                     // Start of the void loop() function.
{
  printTempStats();             // Go to the function called printTempStats().
  delay(500);                   // Adds a delay of 500ms or 5 seconds.
}

void printTempStats()           // Start of the printTempStats() function.
{
  int t = dht.readTemperature();      // Returns Value in Celsius.
  int f = dht.readTemperature(true);  // Returns Value in Fahrenheit.
  int h = dht.readHumidity();         // Returns Value in Humidity.
  Serial.print((float)t); Serial.print(" °C, ");  // Prints out the Temperature in Celsius.
  Serial.print((float)f); Serial.print(" °F, ");  // Prints out the Temperature in Fahrenheit.
  Serial.print((float)h); Serial.println(" H");   // Prints out the Humidity in Relative Humidity.
  /*lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humi : ");
  lcd.print(h);
  lcd.print("%");*/
  return;                             // Terminate a function and return a value from a function to the calling function, if desired.
}
