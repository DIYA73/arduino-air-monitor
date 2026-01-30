#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD I2C address and size
Servo myservo;

const int dustSensorLED = 2;  // Connect to dust sensor's LED control pin
const int analogPin     = A3; // Dust sensor output pin (Vo)
const int servoPin      = 9;

float voltage = 0;
float dustDensity = 0;
int threshold = 400; // Set based on environment

unsigned long previousServoMillis = 0;
const unsigned long servoInterval = 8000; // Every 8 seconds

void setup() {
  pinMode(dustSensorLED, OUTPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  myservo.attach(servoPin);
  myservo.write(0); // Start at 0 degrees
}

void loop() {
  // === Dust Sensor Reading ===
  digitalWrite(dustSensorLED, LOW);
  delayMicroseconds(280);
  int analogValue = analogRead(analogPin);
  delayMicroseconds(40);
  digitalWrite(dustSensorLED, HIGH);
  delayMicroseconds(9680);

  voltage = analogValue * (5.0 / 1024.0); // Convert analog value to voltage
  dustDensity = (voltage - 0.6) * 0.5;
  if (dustDensity < 0) dustDensity = 0;

  // === Gas Sensor Readings ===
  int gasmq2   = analogRead(A1);
  int gasmq7   = analogRead(A2);
  int gasmq135 = analogRead(A0);

  // === Display on Serial Monitor ===
  Serial.print("MQ2: ");   Serial.print(gasmq2);
  Serial.print(" | MQ7: "); Serial.print(gasmq7);
  Serial.print(" | MQ135: "); Serial.print(gasmq135);
  Serial.print(" | Voltage: "); Serial.print(voltage, 2);
  Serial.print("V | Dust: "); Serial.print(dustDensity, 2);
  Serial.println(" mg/m3");

  // === Display on LCD ===
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("G2:"); lcd.print(gasmq2);
  lcd.print(" Dust:"); lcd.print(dustDensity, 1);
  
  lcd.setCursor(0, 1);
  lcd.print("G135:"); lcd.print(gasmq135);
  lcd.print(" G7:"); lcd.print(gasmq7);

  // === Servo Cleaning Movement ===
  unsigned long currentMillis = millis();
  if (currentMillis - previousServoMillis >= servoInterval) {
    previousServoMillis = currentMillis;

    myservo.write(0);
    delay(500);
    myservo.write(180);
    delay(1000);
    myservo.write(0);
    delay(500);
  }

  delay(1000); // 1 second between readings
}