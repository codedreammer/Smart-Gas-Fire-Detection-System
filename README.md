# 🔥 Smart Gas & Fire Detection System 🚨

## 📌 Overview
This project detects gas leakage and fire using sensors and automatically triggers safety actions like:
- 🔊 Buzzer alert
- 🌀 Fan activation
- 💧 Water spray (pump)

## 🧠 Features
- Dual MQ2 gas sensors (A0, A1)
- Flame sensor detection
- LCD display (16x2 I2C)
- Relay-based automation (Fan + Pump)
- Real-time monitoring

## ⚙️ Components Used
- Arduino UNO / R4 WiFi
- MQ2 Gas Sensors (2x)
- Flame Sensor
- Relay Module (2-channel)
- 16x2 LCD (I2C)
- Buzzer
- DC Fan
- Water Pump

## 🔌 Working Logic
| Condition | Action |
|----------|--------|
| 🔥 Fire detected | Fan + Pump + Buzzer ON |
| 🌫 Gas detected | Fan + Buzzer ON |
| ✅ Safe | All OFF |

## 📸 Project Images
(check folder images)

## 💻 Code
Check `sketch_apr26b_FINAL.ino`

## 🚀 Future Improvements
- IoT alert (mobile notification)
- Mobile app control
- Auto calibration

---