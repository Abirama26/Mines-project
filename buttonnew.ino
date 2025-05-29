#include <SoftwareSerial.h>
#include <Wire.h>
#include <MPU6050.h>
#include <DHT.h>
#include <LoRa.h>
#include <TinyGPS++.h>


// LoRa Module Pins
#define NSS 10
#define RST 9
#define DIO0 2
#define BUZZER_PIN 6  // Buzzer connected to pin 6

// MQ-2 Smoke Detection
int mq2Pin = A0;
int mq2Value = 0;
int mq2Threshold = 650; // Updated MQ-2 threshold

// DHT11 Sensor
#define DHTPIN 5
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
float temperature = 0.0;
float humidity = 0.0;
float temperatureThreshold = 40.0;  // Temperature threshold in Celsius
float humidityThreshold = 70.0;    // Humidity threshold

// MPU6050 Accelerometer and Gyroscope
MPU6050 mpu;
int16_t ax, ay, az;
float accelX, accelY, accelZ;
float stableThreshold = 1.5;

// GPS Setup
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup() {
    Serial.begin(9600);
    ss.begin(GPSBaud);

    // Initialize LoRa
    if (!LoRa.begin(433E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    LoRa.setPins(NSS, RST, DIO0);

    // Initialize MPU6050
    Wire.begin();
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed!");
        while (1);
    }

    // Initialize MQ-2 sensor
    pinMode(mq2Pin, INPUT);

    // Initialize DHT11 sensor
    dht.begin();

    // Initialize Buzzer
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
    // **Fall Detection Logic**
    mpu.getAcceleration(&ax, &ay, &az);
    accelX = ax / 16384.0;
    accelY = ay / 16384.0;
    accelZ = az / 16384.0;
    float totalAccel = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);

    String stabilityStatus = "Stable";
    if (totalAccel > 1.2) {
        stabilityStatus = "Movement Detected";
    }

    // **MQ-2 Smoke Detection**
    mq2Value = analogRead(mq2Pin);

    // **DHT11 Sensor Readings**
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
    }

    // **Trigger Buzzer Logic**
    if (temperature >= temperatureThreshold || humidity >= humidityThreshold || mq2Value >= mq2Threshold) {
        digitalWrite(BUZZER_PIN, HIGH);  // Turn on the buzzer
    } else {
        digitalWrite(BUZZER_PIN, LOW);   // Turn off the buzzer
    }

    // **GPS Reading**
    String gpsData = "";
    while (ss.available() > 0) {
        if (gps.encode(ss.read())) {
            gpsData = displayGPSInfo();
        }
    }

    if (millis() > 5000 && gps.charsProcessed() < 10) {
        Serial.println(F("No GPS detected: check wiring."));
        //while(true);
    }

    // LoRa Communication - Sending all data
    String dataString = "Temp:" + String(temperature) + "C," +
                        "Humidity:" + String(humidity) + "%," +
                        "MQ2:" + String(mq2Value) + "," +
                        "Stability:" + stabilityStatus + "," +
                        "GPS:" + gpsData;
    LoRa.beginPacket();
    LoRa.print(dataString);
    LoRa.endPacket();

    // Print all data to Serial Monitor
    Serial.println(dataString);
    delay(1000);
}

// Function to Display GPS Info
String displayGPSInfo() {
    String gpsData = "";
    gpsData += "Location: ";
    if (gps.location.isValid()) {
        gpsData += String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
    } else {
        gpsData += "INVALID";
    }

    gpsData += " Date/Time: ";
    if (gps.date.isValid()) {
        gpsData += String(gps.date.month()) + "/" + String(gps.date.day()) + "/" + String(gps.date.year());
    } else {
        gpsData += "INVALID";
    }

    gpsData += " ";
    if (gps.time.isValid()) {
        gpsData += String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second());
    } else {
        gpsData += "INVALID";
    }

    return gpsData;
}
