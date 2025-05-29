# 🛡️ IoT-Enabled Smart Helmet for Miner Safety

A real-time safety monitoring system for underground miners using IoT and LoRa communication. This smart helmet enhances miner safety by detecting hazardous gases, tracking location and posture, and providing emergency alerts.

## 📌 Features

- 🚨 Real-time detection of hazardous gases (MQ2)
- 💧 Humidity monitoring (DHT11)
- 📍 GPS-based location tracking
- 🧭 Posture & movement detection (MPU6050)
- 📡 LoRa-based long-range communication
- 📊 Live web dashboard with alerts and analytics

## 🛠️ Hardware Requirements

- LoRa SX1278 Module
- MQ2 Gas Sensor
- DHT11 Humidity Sensor
- GPS Module
- MPU6050 Gyroscope + Accelerometer
- Arduino Uno/Nano
- Buzzer
- Connecting wires
- Safety helmet (for mounting)

## 🧰 Software Requirements

- Arduino IDE
- Web technologies: HTML, CSS, JavaScript

## 🔧 System Architecture

### Transmitter (Helmet Unit)
- Reads data from sensors
- Sends via LoRa to base station

### Receiver (Monitoring Unit)
- Receives LoRa data
- Displays live info on dashboard
- Issues emergency alerts

## 📈 Results

- Improved gas detection reliability
- Timely alerts during emergencies
- Effective posture & movement monitoring
- End-to-end data communication via LoRa

## 📚 References

1. [SMART SAFETY HELMET FOR COAL MINERS - ICCSP 2024](https://doi.org/10.1109/ICCSP60870.2024.10543398)
2. [IoT-enabled Smart Helmet for Health Monitoring - ICCUBEA 2023](https://ieeexplore.ieee.org)
3. [IoT Based Self Alert Generating Helmets - ICCINS 2023](https://doi.org/10.1109/ICCINS58907.2023.10450044)
4. [AI-Based Safety Helmet for Mining Workers - IEEE Sensors Journal 2023](https://ieeexplore.ieee.org)
5. [Intelligent Safety Helmet using SVM - NMITCON 2024](https://doi.org/10.1109/NMITCON62075.2024.10699127)

## 🧑‍💻 Authors

- NVS Abirama Arjun (1HK21EC075)
- Nelson Eugene D (1HK21EC084)
- Poornesh E M (1HK21EC090)
- R Vishal (1HK21EC094)

**Guided by**: Dr. Venkatesan C, Professor, Department of ECE, HKBKCE

## 🏫 Institution

**HKBK College of Engineering**, Department of Electronics and Communication Engineering, Bengaluru - 45

---

> Built with safety and innovation in mind for underground coal miners.
