// include library code
#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 4

#define DHTYPE DHT11

DHT dht(DHTPIN, DHTYPE);

// initialize library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 21, 19, 18, 5);

void printTempStats();

void setup() {
Serial.begin(9600);
  lcd.begin(16, 2);               
  lcd.print("Begining program...");
  dht.begin();
  delay(2000);
  Serial.println("starting ...");
}

void loop() {
  printTempStats();
  delay(2000);
}

void printTempStats(){
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Serial.println(t);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humi : ");
  lcd.print(h);
  lcd.print("%");
  return;
}