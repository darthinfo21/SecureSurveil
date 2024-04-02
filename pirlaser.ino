#include <Wire.h>
#include <Servo.h>

Servo servoMotor; // Create a servo object
int pirPin = 2;   // PIR sensor output pin
int angle = 90;   // Initial angle for the servo motor
int laserPin = 13; // Pin for the laser module
int buzzerPin = 8; // Pin for the buzzer
bool motionDetected = false; // Flag to track motion detection

void setup() {
  Serial.begin(9600); // Initialize serial communication
  servoMotor.attach(9); // Attach the servo motor to pin 9
  pinMode(pirPin, INPUT); // Set PIR sensor pin as input
  pinMode(laserPin, OUTPUT); // Set laser pin as output
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  servoMotor.write(angle); // Move the servo motor to the initial angle
  delay(1000); // Delay for stabilization
}

void loop() {
  if (digitalRead(pirPin) == HIGH) { // If motion is detected
    if (!motionDetected) { // If motion was not previously detected
      motionDetected = true; // Set motion detected flag
      Serial.println("Motion detected!"); // Print message to serial monitor
      digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
      delay(500); // Delay for buzzer sound
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
      for (angle = 0; angle <= 180; angle += 1) { // Sweep from 0 to 180 degrees
        servoMotor.write(angle); // Move the servo motor to the new angle
        digitalWrite(laserPin, HIGH); // Turn on the laser module
        delay(15); // Delay to stabilize the servo motor
      }
      for (angle = 180; angle >= 0; angle -= 1) { // Sweep from 180 to 0 degrees
        servoMotor.write(angle); // Move the servo motor to the new angle
        digitalWrite(laserPin, HIGH); // Turn off the laser module
        delay(15); // Delay to stabilize the servo motor
      }
        digitalWrite(laserPin, LOW); // Turn off the laser module
    }
  } else {
    motionDetected = false; // Reset motion detected flag
  }
}















