# 🔥 Smart Gas & Fire Detection System 🚨

A real-time **IoT-based safety system** that detects gas leakage and fire hazards and automatically triggers preventive actions like ventilation and water spraying.

---

## 📌 Overview

This project uses multiple sensors to monitor environmental safety and responds instantly to dangerous conditions.

It can:

* Detect **gas leakage (MQ2 sensors)**
* Detect **fire (flame sensor)**
* Trigger **buzzer alerts**
* Activate **fan for ventilation**
* Activate **water pump for fire suppression**
* Display real-time data on **LCD**
* Send live data to **Firebase (IoT Dashboard ready)**

---

## 🧠 Features

* 🔥 Fire detection with automatic suppression
* 🌫 Dual gas sensors for improved accuracy
* 📟 Real-time LCD monitoring
* 🔊 Buzzer alert system
* 🌀 Automatic fan control
* 💧 Water spray system (fire condition only)
* ☁️ Firebase Realtime Database integration
* 🌐 Ready for React Web Dashboard

---

## ⚙️ Components Used

* Arduino UNO / UNO R4 WiFi
* MQ2 Gas Sensors (×2)
* Flame Sensor
* 2-Channel Relay Module
* 16x2 LCD (I2C)
* Buzzer
* DC Fan
* Water Pump
* Jumper Wires & Breadboard

---

## 🔌 Working Logic

| Condition        | Action                 |
| ---------------- | ---------------------- |
| 🔥 Fire Detected | Fan + Pump + Buzzer ON |
| 🌫 Gas Detected  | Fan + Buzzer ON        |
| ✅ Safe Condition | All OFF                |

---

## ☁️ IoT Integration

The system sends real-time data to Firebase:

```json
sensor: {
  gas1: value,
  gas2: value,
  flame: 0/1,
  status: "SAFE / GAS / FIRE"
}
```

This enables:

* Live monitoring
* Dashboard visualization
* Future mobile alerts

---

## 📸 Project Preview

*Add images/screenshots here (hardware setup + dashboard)*

---

## 💻 Code

👉 See full Arduino code:
`sketch_apr26b_FINAL.ino`

---

## 🚀 Future Improvements

* 📱 Mobile app integration
* 🔔 Push notifications (Fire/Gas alert)
* 📊 Advanced dashboard (charts & analytics)
* 🤖 Auto sensor calibration
* 🧠 AI-based hazard prediction

---

## 🧑‍💻 Tech Stack

* Arduino (Embedded C++)
* Firebase Realtime Database
* React (Dashboard - in progress)

---

## ⭐ Why This Project Matters

This system demonstrates:

* Real-world **IoT implementation**
* **Hardware + Software integration**
* **Automation for safety systems**
* Scalable architecture for smart homes / industries

---

## 📦 Required Libraries

Install these libraries from **Arduino Library Manager**:

### 🔹 Core Libraries

* `Wire.h` (built-in)
* `LiquidCrystal_I2C`
  👉 Used for LCD display

### 🔹 WiFi (for UNO R4 WiFi)

* `WiFiS3`
  👉 Handles WiFi connection

### 🔹 Firebase

* `Firebase ESP Client (by Mobizt)`
  👉 Used for sending data to Firebase Realtime Database

---

## ⚙️ Installation Steps

1. Open **Arduino IDE**
2. Go to: **Sketch → Include Library → Manage Libraries**
3. Search and install:

* LiquidCrystal_I2C
* Firebase ESP Client

( WiFiS3 is already available for UNO R4 )

---

## ⚠️ Important Notes

* Make sure you are using **Arduino UNO R4 WiFi** (required for WiFiS3)
* Update your **WiFi credentials** in the code
* Replace Firebase config with your project details

---

