#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiS3.h>
#include <Firebase_ESP_Client.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// 🔑 WiFi
const char* ssid = "TP-Link_5FF6";
const char* password = "86512619";

// 🔥 Firebase
#define DATABASE_URL "https://iot-fire-safety-default-rtdb.asia-southeast1.firebasedatabase.app/"

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// 🔌 Pins
int gasPin1 = A0;
int gasPin2 = A1;
int flamePin = 2;

int buzzerPin = 9;
int fanRelay = 7;    // K1
int pumpRelay = 8;   // K2

int gasThreshold = 600;

void setup() {
  Serial.begin(9600);

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

  // 🌐 Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");

  // 🔥 Firebase setup
  config.database_url = DATABASE_URL;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  lcd.setCursor(0, 0);
  lcd.print("System Init...");
  delay(2000);
  lcd.clear();
}

void loop() {
  int gasValue1 = analogRead(gasPin1);
  int gasValue2 = analogRead(gasPin2);
  int flame = digitalRead(flamePin);

  String status = "SAFE";

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

  // 🔥 FIRE
  if (flame == LOW) {
    status = "FIRE";

    lcd.setCursor(0, 1);
    lcd.print("FIRE ALERT!!! ");

    digitalWrite(buzzerPin, HIGH);
    digitalWrite(fanRelay, LOW);    // ON
    digitalWrite(pumpRelay, LOW);   // ON
  }

  // 🌫 GAS
  else if (gasValue1 > gasThreshold || gasValue2 > gasThreshold) {
    status = "GAS";

    lcd.setCursor(0, 1);
    lcd.print("GAS ALERT!!!  ");

    digitalWrite(buzzerPin, HIGH);
    digitalWrite(fanRelay, LOW);    // ON
    digitalWrite(pumpRelay, HIGH);  // OFF
  }

  // ✅ SAFE
  else {
    status = "SAFE";

    lcd.setCursor(0, 1);
    lcd.print("Air is Safe   ");

    digitalWrite(buzzerPin, LOW);
    digitalWrite(fanRelay, HIGH);   // OFF
    digitalWrite(pumpRelay, HIGH);  // OFF
  }

  // ☁️ Upload to Firebase
  Firebase.RTDB.setInt(&fbdo, "/sensor/gas1", gasValue1);
  Firebase.RTDB.setInt(&fbdo, "/sensor/gas2", gasValue2);
  Firebase.RTDB.setInt(&fbdo, "/sensor/flame", flame);
  Firebase.RTDB.setString(&fbdo, "/sensor/status", status);

  delay(2000);
}