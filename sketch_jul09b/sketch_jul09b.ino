#include <Servo.h>

const int triggerPin1 = 2;       // Trigger pin for ultrasonic sensor 1
const int echoPin1 = 3;          // Echo pin for ultrasonic sensor 1
const int triggerPin2 = 4;       // Trigger pin for ultrasonic sensor 2
const int echoPin2 = 5;          // Echo pin for ultrasonic sensor 2

const int thresholdDistance = 20;    // Distance threshold for detecting a parked car (in centimeters)
const int closedPosition = 0;        // Servo closed position (gate closed)
const int openPosition = 90;         // Servo open position (gate open)

Servo gateServo;                     // Servo object for controlling the gate

void setup() {
  Serial.begin(9600);                // Initialize serial communication
  pinMode(triggerPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  gateServo.attach(6);               // Attach the servo to pin 6
  gateServo.write(closedPosition);   // Set the initial position of the servo to closed
}

void loop() {
  int distance1 = getDistance(triggerPin1, echoPin1); // Get the distance from sensor 1
  int distance2 = getDistance(triggerPin2, echoPin2); // Get the distance from sensor 2

  if (distance1 < thresholdDistance && distance2 < thresholdDistance) {
    Serial.println("Parking slot occupied");
    closeGate();
  } else {
    Serial.println("Parking slot available");
    openGate();
  }

  delay(1000); // Delay between readings
}

int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; // Calculate the distance in centimeters

  return distance;
}

void openGate() {
  gateServo.write(openPosition);  // Set the position of the servo to open
}

void closeGate() {
  gateServo.write(closedPosition); // Set the position of the servo to closed
}
