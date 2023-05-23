#include <LiquidCrystal.h>

// Pin assignments
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int ledPin = 7;
const int buzzerPin = 6;
const int heartRateSensorPin = A0;
#define RELAY_PIN 8

// Initialize the library
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

bool relayActivated = false;
unsigned long relayStartTime = 0;
const unsigned long relayDuration = 3000; // Relay activation duration in milliseconds

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  // Set the LED pin as OUTPUT
  pinMode(ledPin, OUTPUT);
  
  // Set the buzzer pin as OUTPUT
  pinMode(buzzerPin, OUTPUT);

  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  // Read heart rate from the sensor
  int heartRate = analogRead(heartRateSensorPin);
  heartRate = heartRate / 9;

  // Display heart rate on LCD
  lcd.setCursor(0, 0);
  lcd.print("Heart Rate:");
  lcd.setCursor(0, 1);
  lcd.print(heartRate);

  // Check if heart rate is above 90
  if (heartRate > 90) {
    // Toggle the LED
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);

    // Activate the relay if it is not already activated
    if (!relayActivated) {
      relayActivated = true;
      relayStartTime = millis();
      digitalWrite(RELAY_PIN, HIGH);
    }

    // Play a tone on the buzzer
    tone(buzzerPin, 1000, 100);
  }

  // Check if the relay activation duration has passed
  if (relayActivated && (millis() - relayStartTime >= relayDuration)) {
    digitalWrite(RELAY_PIN, LOW); // Turn off the relay
    relayActivated = false; // Reset the relay activation flag
  }

  delay(200);
}
