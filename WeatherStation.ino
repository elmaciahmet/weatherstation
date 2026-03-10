#include "DHT.h"
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temperatur &");
  lcd.setCursor(0, 1);
  lcd.print("Luftfeuchtigkeit");

  delay(1500);
  lcd.clear();

  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    //Serial.println(F("Failed to read from DHT sensor!"));
    delay(1500);
    lcd.setCursor(0, 0);
    lcd.print(F("SENSOR READ"));
    lcd.setCursor(0, 1);
    lcd.print(F("FAILED!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.setCursor(0, 0);
  lcd.print(F("Temp.   "));
  lcd.print(t);
  lcd.print((char)223); // '°'
  lcd.print(F("C"));

  lcd.setCursor(0, 1);
  lcd.print(F("Feucht. "));
  lcd.print(h);
  lcd.print(F(" %"));

  delay(5000);
}
