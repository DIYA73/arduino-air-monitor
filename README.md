# 🌍 Arduino Air Quality Monitoring System

**IoT-based environmental monitoring system using Arduino to measure air pollution with gas and dust sensors, real-time LCD display, and automated servo response.**

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=flat-square&logo=arduino&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![IoT](https://img.shields.io/badge/IoT-Enabled-success?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-blue.svg?style=flat-square)

---

## 📖 Overview

An Arduino-based air quality monitoring system designed to measure environmental air pollution using multiple gas sensors and a dust sensor. The system provides real-time feedback through an I2C LCD display and triggers mechanical responses via a servo motor when air quality exceeds safe thresholds.

**Note:** This repository contains **code and system design documentation only**. No physical hardware is required to understand the project architecture and implementation.

### 🎯 Key Features

- **🔬 Multi-Sensor Detection**: MQ-2, MQ-7, MQ-135 gas sensors + dust sensor
- **📊 Real-Time Display**: 16x2 I2C LCD for live air quality readings
- **⚙️ Automated Response**: Servo motor activation based on pollution levels
- **🔔 Threshold Alerts**: Visual/mechanical warnings for poor air quality
- **📈 Data Logging**: Optional serial monitor data output
- **🧩 Modular Code**: Clean, well-documented Arduino sketches
- **📐 System Design**: Complete circuit diagrams and documentation

---

## 🛠️ Hardware Components

### Required Components

**Microcontroller:**
- Arduino Uno / Nano / Mega (any ATmega328P-based board)

**Sensors:**
- **MQ-2**: Smoke and combustible gas sensor (LPG, propane, methane)
- **MQ-7**: Carbon monoxide (CO) sensor
- **MQ-135**: Air quality sensor (NH3, NOx, benzene, smoke, CO2)
- **GP2Y1010AU0F**: Optical dust sensor (PM2.5/PM10)

**Display & Output:**
- **16x2 I2C LCD**: Display module with I2C interface
- **SG90 Servo Motor**: For mechanical response (e.g., ventilation control)
- **LED Indicators**: Status lights (optional)
- **Buzzer**: Audio alarm (optional)

**Power Supply:**
- 5V DC adapter or USB power
- 9V battery backup (optional)

**Miscellaneous:**
- Breadboard / PCB
- Jumper wires
- Resistors (220Ω, 10kΩ)
- Capacitors (for sensor stability)

---

## 🏗️ System Architecture

### Block Diagram

```
┌─────────────────────────────────────────┐
│          Arduino Uno (ATmega328P)       │
├─────────────────────────────────────────┤
│                                         │
│  ┌──────────┐  ┌──────────┐            │
│  │  MQ-2    │  │  MQ-7    │            │
│  │  (A0)    │  │  (A1)    │  Gas       │
│  └──────────┘  └──────────┘  Sensors   │
│                                         │
│  ┌──────────┐  ┌──────────┐            │
│  │  MQ-135  │  │  Dust    │            │
│  │  (A2)    │  │  (A3)    │            │
│  └──────────┘  └──────────┘            │
│                                         │
│  ┌─────────────────────────┐           │
│  │   I2C LCD (16x2)        │  Display  │
│  │   SDA: A4, SCL: A5      │           │
│  └─────────────────────────┘           │
│                                         │
│  ┌──────────┐  ┌──────────┐            │
│  │  Servo   │  │  Buzzer  │  Output   │
│  │  (D9)    │  │  (D10)   │            │
│  └──────────┘  └──────────┘            │
│                                         │
└─────────────────────────────────────────┘
```

### Data Flow

1. **Sensor Reading**: Analog sensors read air quality data
2. **Data Processing**: Arduino processes raw values into PPM/µg/m³
3. **Threshold Check**: Compare values against safe limits
4. **Display Update**: Show readings on LCD
5. **Response Trigger**: Activate servo/buzzer if thresholds exceeded
6. **Serial Output**: Log data for monitoring (optional)

---

## 💻 Software Architecture

### File Structure

```
arduino-air-monitor/
├── src/
│   ├── main.ino                # Main Arduino sketch
│   ├── sensors.ino             # Sensor reading functions
│   ├── display.ino             # LCD display functions
│   ├── actuators.ino           # Servo motor control
│   └── config.h                # Configuration & thresholds
├── doce/                       # Documentation
│   ├── circuit-diagram.png     # Wiring diagram
│   ├── schematic.fzz           # Fritzing file
│   └── system-design.md        # Design documentation
├── LICENSE
└── README.md
```

### Code Modules

**1. Main Control Loop** (`main.ino`)
```cpp
void loop() {
  // Read all sensors
  float mq2Value = readMQ2();
  float mq7Value = readMQ7();
  float mq135Value = readMQ135();
  float dustValue = readDustSensor();
  
  // Calculate air quality index
  int aqi = calculateAQI(mq2Value, mq7Value, mq135Value, dustValue);
  
  // Update display
  updateLCD(aqi, mq7Value, dustValue);
  
  // Check thresholds and respond
  if (aqi > DANGER_THRESHOLD) {
    activateServo();
    soundAlarm();
  }
  
  delay(UPDATE_INTERVAL);
}
```

**2. Sensor Reading** (`sensors.ino`)
```cpp
float readMQ2() {
  int sensorValue = analogRead(MQ2_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float ppm = convertToPPM(voltage);
  return ppm;
}
```

**3. LCD Display** (`display.ino`)
```cpp
void updateLCD(int aqi, float co, float dust) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AQI: ");
  lcd.print(aqi);
  
  lcd.setCursor(0, 1);
  lcd.print("CO:");
  lcd.print(co);
  lcd.print(" PM:");
  lcd.print(dust);
}
```

---

## 🔧 Installation & Setup

### 1. Arduino IDE Setup

**Install Arduino IDE:**
- Download from [arduino.cc](https://www.arduino.cc/en/software)
- Install for your operating system

**Install Libraries:**
```
Sketch → Include Library → Manage Libraries

Search and install:
- LiquidCrystal I2C (by Frank de Brabander)
- Servo (built-in)
```

### 2. Clone Repository

```bash
git clone https://github.com/DIYA73/arduino-air-monitor.git
cd arduino-air-monitor
```

### 3. Upload Code

1. Open `src/main.ino` in Arduino IDE
2. Connect Arduino board via USB
3. Select board: **Tools → Board → Arduino Uno**
4. Select port: **Tools → Port → COM3** (or your port)
5. Click **Upload** button

### 4. Configure Thresholds (Optional)

Edit `src/config.h`:
```cpp
// Air Quality Thresholds (PPM)
#define GOOD_THRESHOLD 50
#define MODERATE_THRESHOLD 100
#define DANGER_THRESHOLD 200

// Sensor Calibration
#define MQ2_R0 10.0   // Calibrate in clean air
#define MQ7_R0 10.0
#define MQ135_R0 10.0

// Update Interval (milliseconds)
#define UPDATE_INTERVAL 2000
```

---

## 🔌 Wiring Diagram

### Pin Connections

**MQ Gas Sensors:**
```
MQ-2  → Arduino A0
MQ-7  → Arduino A1
MQ-135 → Arduino A2
VCC   → 5V
GND   → GND
```

**Dust Sensor:**
```
GP2Y1010AU0F:
  LED   → Arduino D2 (via 150Ω resistor)
  VO    → Arduino A3
  VCC   → 5V
  GND   → GND
```

**I2C LCD (16x2):**
```
SDA → Arduino A4
SCL → Arduino A5
VCC → 5V
GND → GND
```

**Servo Motor:**
```
Signal → Arduino D9
VCC    → 5V
GND    → GND
```

**Buzzer (Optional):**
```
Positive → Arduino D10
Negative → GND
```

---

## 📊 Sensor Specifications

### MQ-2 (Smoke & Gas)
- **Detection Range**: 300 - 10,000 ppm
- **Detects**: LPG, propane, methane, hydrogen, alcohol, smoke
- **Response Time**: < 10 seconds
- **Warm-up Time**: 20-30 seconds

### MQ-7 (Carbon Monoxide)
- **Detection Range**: 20 - 2,000 ppm
- **Detects**: Carbon monoxide (CO)
- **Response Time**: < 60 seconds
- **Operating Voltage**: 5V DC

### MQ-135 (Air Quality)
- **Detection Range**: 10 - 1,000 ppm
- **Detects**: NH3, NOx, alcohol, benzene, smoke, CO2
- **Sensitivity**: High sensitivity to ammonia
- **Warm-up Time**: 24 hours for accurate readings

### GP2Y1010AU0F (Dust Sensor)
- **Detection Range**: 0 - 500 µg/m³
- **Particle Size**: PM2.5 and PM10
- **Response Time**: < 10 seconds
- **Output**: Analog voltage (proportional to dust density)

---

## 🧪 Calibration

### Gas Sensor Calibration

1. **Clean Air Baseline:**
   - Power sensors in clean outdoor air for 24 hours
   - Record resistance (R0) value
   - Update in `config.h`

2. **Known Gas Test:**
   - Expose to known concentration
   - Adjust conversion formulas if needed

### Dust Sensor Calibration

```cpp
// Convert analog reading to µg/m³
float convertDustDensity(int analogValue) {
  float voltage = analogValue * (5.0 / 1024.0);
  float dustDensity = 0.17 * voltage - 0.1;  // Adjust coefficients
  return max(0.0, dustDensity * 1000);        // µg/m³
}
```

---

## 📈 Air Quality Index (AQI) Calculation

```cpp
int calculateAQI(float mq2, float mq7, float mq135, float dust) {
  // Weighted average of all sensors
  int aqi = 0;
  
  // MQ-2 contribution (0-100)
  aqi += map(mq2, 0, 1000, 0, 25);
  
  // MQ-7 contribution (0-100)
  aqi += map(mq7, 0, 200, 0, 25);
  
  // MQ-135 contribution (0-100)
  aqi += map(mq135, 0, 500, 0, 25);
  
  // Dust contribution (0-100)
  aqi += map(dust, 0, 500, 0, 25);
  
  return constrain(aqi, 0, 100);
}
```

**AQI Levels:**
- **0-50**: Good (Green)
- **51-100**: Moderate (Yellow)
- **101-150**: Unhealthy for sensitive groups (Orange)
- **151-200**: Unhealthy (Red)
- **201+**: Very Unhealthy (Purple)

---

## 🚀 Usage

### Serial Monitor Output

Open Serial Monitor (Tools → Serial Monitor) at **9600 baud** to see real-time data:

```
=== Air Quality Monitor ===
Initializing sensors...
MQ-2:  250 ppm
MQ-7:  30 ppm (CO)
MQ-135: 120 ppm
Dust:  85 µg/m³
AQI: 65 (Moderate)
---

MQ-2:  260 ppm
MQ-7:  35 ppm (CO)
MQ-135: 125 ppm
Dust:  90 µg/m³
AQI: 68 (Moderate)
WARNING: CO levels elevated
---
```

### LCD Display Format

```
AQI: 65 MODERATE
CO:30 PM:85 ug/m
```

### Servo Response

- **AQI < 100**: Servo at 0° (ventilation off)
- **AQI ≥ 100**: Servo sweeps 0° - 90° (ventilation on)

---

## 🔬 Testing & Validation

### Test Scenarios

**1. Smoke Test:**
- Light a match near MQ-2
- Expected: PPM spike, AQI increase

**2. CO Test (Caution):**
- Use CO calibration gas (if available)
- Never use car exhaust indoors

**3. Dust Test:**
- Use incense or fine powder
- Expected: Dust sensor reading increase

**4. Clean Air Test:**
- Place outdoors in fresh air
- Expected: All readings near baseline

---

## 🗺️ Roadmap

### ✅ Phase 1: Basic System (Completed)
- [x] Multi-sensor integration
- [x] LCD display
- [x] Servo motor control
- [x] Threshold alerts

### 🚧 Phase 2: Enhanced Features (Planned)
- [ ] SD card data logging
- [ ] WiFi connectivity (ESP8266/ESP32)
- [ ] Web dashboard
- [ ] Mobile app notifications
- [ ] Battery backup
- [ ] Temperature & humidity sensors

### 📋 Phase 3: Advanced Features (Future)
- [ ] Machine learning for predictions
- [ ] Multi-zone monitoring
- [ ] Cloud data storage
- [ ] Integration with smart home systems
- [ ] GPS location tracking
- [ ] Solar-powered operation

---

## 🛡️ Safety Considerations

⚠️ **Important Safety Notes:**

- **Gas Sensors**: Warm-up time required (30 min - 24 hours)
- **Calibration**: Perform in well-ventilated area
- **High Readings**: If CO levels dangerous, evacuate and ventilate
- **Power Supply**: Use stable 5V, avoid voltage spikes
- **Sensor Lifespan**: MQ sensors degrade over time (1-2 years)
- **Not Medical Grade**: For informational purposes only

---

## 📚 Resources

### Documentation
- [MQ-2 Datasheet](https://www.pololu.com/file/0J309/MQ2.pdf)
- [MQ-7 Datasheet](https://www.sparkfun.com/datasheets/Sensors/Biometric/MQ-7.pdf)
- [MQ-135 Datasheet](https://www.olimex.com/Products/Components/Sensors/SNS-MQ135/resources/SNS-MQ135.pdf)
- [GP2Y1010AU0F Datasheet](https://global.sharp/products/device/lineup/data/pdf/datasheet/gp2y1010au_e.pdf)

### Tutorials
- [Arduino Air Quality Sensor Guide](https://www.arduino.cc)
- [I2C LCD Tutorial](https://www.arduino.cc/en/Reference/LiquidCrystal)
- [Servo Motor Control](https://www.arduino.cc/en/Reference/Servo)

---

## 🤝 Contributing

Contributions welcome! Areas for improvement:

- Enhanced calibration algorithms
- Additional sensor support
- Data visualization tools
- Mobile app development
- PCB design files

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author

**DIYA73**
- GitHub: [@DIYA73](https://github.com/DIYA73)
- LinkedIn: [linkedin.com/in/didi-86b00329a](https://www.linkedin.com/in/didi-86b00329a/)

---

## 🙏 Acknowledgments

- Arduino community for libraries and tutorials
- Sensor manufacturers for datasheets
- Open-source hardware movement

---

**⭐ If you find this project useful, please star the repository!**

**🌍 Monitoring air quality, one sensor at a time.**

---

**Made with ❤️ for environmental awareness and IoT enthusiasts**
