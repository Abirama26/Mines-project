#include <Wire.h>
#include <LoRa.h>  // Include LoRa library

// Define pins for LoRa module
#define NSS 10
#define RST 9
#define DIO0 2

void setup() {
  Serial.begin(9600);  // Start the serial monitor
  while (!Serial);     // Wait for Serial Monitor to be ready

  // Initialize LoRa
  if (!LoRa.begin(433E6)) {  // 433 MHz (ensure to match with the transmitter frequency)
    Serial.println("Starting LoRa failed!");
    while (1);  // Halt execution if LoRa initialization fails
  }

  LoRa.setPins(NSS, RST, DIO0);  // Set LoRa module pins
  Serial.println("LoRa Receiver Initialized!");
}

void loop() {
  // Check if LoRa has received a packet
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    // If a packet is received, read and print it
    Serial.print("Received packet: ");
    
    // Read all bytes of the packet and print them
    while (LoRa.available()) {
      char receivedChar = (char)LoRa.read();  // Read one byte
      Serial.print(receivedChar);              // Print the byte to the serial monitor
    }

    // Print a new line after each packet is received
    Serial.println();
  }

  // Small delay to avoid overwhelming the serial monitor
  delay(100);
}
