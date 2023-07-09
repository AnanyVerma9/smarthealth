#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the LCD address if necessary

const int heartRateSensorPin = A0; // Pin connected to the heart rate sensor

void setup() {
  lcd.begin(16, 2);
  lcd.print(" Heart Monitor ");
  lcd.setCursor(0, 1);
  lcd.print("   Initializing ");
  delay(2000);
  lcd.clear();
}

void loop() {
  int heartRate = getHeartRate(); // Read the heart rate value

  // Display the heart rate on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Heart Rate: ");
  lcd.print(heartRate);
  lcd.print(" BPM");

  delay(1000); // Delay between readings
}

int getHeartRate() {
  int sensorValue = analogRead(heartRateSensorPin); // Read the analog value from the heart rate sensor
  int heartRate = map(sensorValue, 0, 1023, 0, 220); // Map the sensor value to a heart rate range

  return heartRate;
}
