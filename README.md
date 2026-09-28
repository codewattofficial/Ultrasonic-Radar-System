# 📡 Arduino Ultrasonic Radar System

An interactive real-time object tracking and distance detection system built using **Arduino Uno**, an **HC-SR04 Ultrasonic Sensor**, and an **SG90 Servo Motor**. 

The servo sweeps the ultrasonic sensor continuously from $0^\circ$ to $180^\circ$ and back, capturing object distances. The data is output over Serial Communication (`angle,distance.`) to feed a web or Processing-based visual radar interface.

---

## 🛠️ Features
- **180° Area Scanning:** Sweeps seamlessly back and forth using a servo motor.
- **Real-Time Distance Calculation:** Accurately measures distances up to 100 cm using ultrasonic sound waves.
- **Serial Output:** Transmits structured data (`angle,distance.`) at 9600 baud rate, ready to be parsed by web applications (HTML/JS) or Processing IDE.
- **Non-blocking Timeout:** Uses a 30ms echo timeout to prevent blocking during empty scans.

---

## 🔌 Hardware Components & Wiring

| Component | Arduino Pin / Connection | Notes |
| :--- | :--- | :--- |
| **Servo Signal** | `D9` | Controls sweep motion ($0^\circ - 180^\circ$) |
| **HC-SR04 TRIG** | `D10` | Triggers ultrasonic pulse |
| **HC-SR04 ECHO** | `D11` | Receives echo signal |
| **Servo VCC / GND** | External 5V Supply / GND | Recommended to avoid current overload on Arduino |
| **HC-SR04 VCC / GND** | 5V / GND | Powered directly from Arduino |

> **Note:** Common GND must be connected between external power supply and the Arduino board.

---

## 💻 Code Overview

The main logic operates inside `setup()` and `loop()`:
1. **Sweep Logic:** Modifies angle step-by-step (`STEP_DEGREES = 2`) with small delays (`STEP_DELAY_MS = 40`) to ensure mechanical stability.
2. **Distance Measure:** Calculates distance using sound speed formula:
   $$\text{Distance (cm)} = \frac{\text{Duration (}\mu\text{s)} \times 0.0343}{2}$$
3. **Data Formatting:** Sends string data formatted as `ANGLE,DISTANCE.` over Serial.

---

## 🚀 Getting Started

1. **Clone or Download** this repository.
2. Open the `.ino` file in the **Arduino IDE**.
3. Install the **Servo** library (included in Arduino IDE by default).
4. Connect your hardware according to the wiring table.
5. Select your Board and Port from `Tools` menu.
6. **Upload** the code to your Arduino Uno.
7. Open the **Serial Monitor** (set baud rate to **9600**) or connect your web/Processing frontend to view the output!

---

## 📄 License
This project is open-source and available under the [MIT License](LICENSE).