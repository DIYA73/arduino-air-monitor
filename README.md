# 🌫️ Arduino Air Quality Monitoring System

An Arduino-based air quality monitoring system that measures dust concentration and harmful gases using multiple MQ sensors. The system displays real-time data on an LCD, outputs readings to the Serial Monitor, and uses a servo motor for automatic cleaning/actuation.

---

## 🚀 Features

* 📊 Real-time air quality monitoring
* 🌪️ Dust concentration measurement
* 🧪 Gas detection (MQ-2, MQ-7, MQ-135)
* 📟 16x2 I2C LCD display
* 🔁 Automatic servo movement for cleaning
* 💻 Serial Monitor logging

---

## 🧰 Hardware Components

* Arduino Uno (or compatible)
* Dust Sensor (e.g. GP2Y1010AU0F)
* MQ-2 Gas Sensor
* MQ-7 Gas Sensor
* MQ-135 Gas Sensor
* 16x2 LCD with I2C module
* Servo Motor (SG90)
* Jumper wires
* Breadboard
* External power supply (recommended)

---

## 🔌 Pin Connections

### 📟 LCD (I2C)

| LCD Pin | Arduino |
| ------- | ------- |
| VCC     | 5V      |
| GND     | GND     |
| SDA     | A4      |
| SCL     | A5      |

### 🌪️ Dust Sensor

| Dust Sensor Pin | Arduino |
| --------------- | ------- |
| LED Control     | D2      |
| Vo (Analog)     | A3      |
| VCC             | 5V      |
| GND             | GND     |

### 🧪 Gas Sensors

| Sensor | Arduino Analog Pin |
| ------ | ------------------ |
| MQ-135 | A0                 |
| MQ-2   | A1                 |
| MQ-7   | A2                 |

### 🔁 Servo Motor

| Servo Pin | Arduino |
| --------- | ------- |
| Signal    | D9      |
| VCC       | 5V      |
| GND       | GND     |

---

## 🧠 How It Works

1. The dust sensor measures particulate matter using an infrared LED and photodiode.
2. Gas sensors detect different air pollutants and output analog values.
3. Arduino processes sensor data and converts it into readable values.
4. Data is shown on:

   * LCD screen
   * Serial Monitor
5. A servo motor activates every 8 seconds to simulate a cleaning or mechanical action.

---

## 📟 LCD Display Format

**Line 1**

```
G2:xxx Dust:x.x
```

**Line 2**

```
G135:xxx G7:xxx
```

---

## 🛠️ Installation & Usage

1. Clone the repository:

```bash
git clone https://github.com/your-username/your-repo-name.git
```

2. Open the `.ino` file in **Arduino IDE**

3. Install required libraries:

* `LiquidCrystal_I2C`
* `Servo`

4. Select correct **Board** and **Port**

5. Upload the code

6. Open **Serial Monitor (9600 baud)**

---

## 📂 File Structure

```
📁 Arduino-Air-Quality-Monitor
 ┣ 📄 AirQualityMonitor.ino
 ┣ 📄 README.md
 ┣ 📄 LICENSE
 ┗ 📁 images (optional)
```
