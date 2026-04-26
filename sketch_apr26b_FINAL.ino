#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// 🔥 Pins
int gasPin1 = A0;
int gasPin2 = A1;
int flamePin = 2;

int buzzerPin = 9;
int fanRelay = 7;    // K1 (fan)
int pumpRelay = 8;   // K2 (water pump)

// ⚠️ Adjust after testing
int gasThreshold = 600;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(buzzerPin, OUTPUT);
  pinMode(fanRelay, OUTPUT);
  pinMode(pumpRelay, OUTPUT);
  pinMode(flamePin, INPUT);

  // Relay OFF initially (active LOW)
  digitalWrite(fanRelay, HIGH);
  digitalWrite(pumpRelay, HIGH);
  digitalWrite(buzzerPin, LOW);

  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("System Init...");
  delay(2000);
  lcd.clear();
}

void loop() {
  int gasValue1 = analogRead(gasPin1);
  int gasValue2 = analogRead(gasPin2);
  int flame = digitalRead(flamePin);

  // 📟 Serial monitor
  Serial.print("G1:");
  Serial.print(gasValue1);
  Serial.print(" G2:");
  Serial.print(gasValue2);
  Serial.print(" F:");
  Serial.println(flame);

  // 📟 LCD Line 1
  lcd.setCursor(0, 0);
  lcd.print("G1:");
  lcd.print(gasValue1);
  lcd.print(" G2:");
  lcd.print(gasValue2);
  lcd.print("   ");

  // 🔥 FIRE (highest priority)
  if (flame == LOW) {
    lcd.setCursor(0, 1);
    lcd.print("FIRE ALERT!!! ");

    digitalWrite(buzzerPin, HIGH);
    digitalWrite(fanRelay, LOW);    // 🌀 Fan ON
    digitalWrite(pumpRelay, LOW);   // 💧 Pump ON
  }

  // 🌫 GAS ALERT
  else if (gasValue1 > gasThreshold || gasValue2 > gasThreshold) {
    lcd.setCursor(0, 1);
    lcd.print("GAS ALERT!!!  ");

    digitalWrite(buzzerPin, HIGH);
    digitalWrite(fanRelay, LOW);    // 🌀 Fan ON
    digitalWrite(pumpRelay, HIGH);  // ❌ Pump OFF
  }

  // ✅ SAFE
  else {
    lcd.setCursor(0, 1);
    lcd.print("Air is Safe   ");

    digitalWrite(buzzerPin, LOW);
    digitalWrite(fanRelay, HIGH);   // OFF
    digitalWrite(pumpRelay, HIGH);  // OFF
  }

  delay(500);
}