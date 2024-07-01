// Define sensor pins
const int trigPinFront = 2;
const int echoPinFront = 3;
const int trigPinRight = 4;
const int echoPinRight = 5;
const int trigPinLeft = 6;
const int echoPinLeft = 7;

// Define LED pins
const int ledFront = 9;
const int ledRight = 10;
const int ledLeft = 11;

// Variables for distance measurement
long duration;
int distance;

// Threshold distance for proximity (in cm)
const int thresholdDistance = 100;

void setup() {
  // Initialize sensor pins
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);

  // Initialize LED pins
  pinMode(ledFront, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledLeft, OUTPUT);

  // Initialize Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Measure distance from the front sensor
  distance = getDistance(trigPinFront, echoPinFront);

  controlLED(ledFront, distance);
  if (distance < thresholdDistance) {
    // Measure distance from the right sensor
    distance = getDistance(trigPinRight, echoPinRight);

    controlLED(ledRight, distance);
    if (distance < thresholdDistance) {
      // Measure distance from the left sensor
      distance = getDistance(trigPinLeft, echoPinLeft);

      controlLED(ledLeft, distance);
    }
  }
  delay(100);
}

// Function to get distance from ultrasonic sensor
int getDistance(int trigPin, int echoPin) {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin and calculate the distance
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

// Function to control LED brightness based on distance
void controlLED(int ledPin, int distance) {
  if (distance < thresholdDistance) {
    analogWrite(ledPin, map(distance, thresholdDistance, 200, 0, 255));
  } else {
    analogWrite(ledPin, 0);
  }
}
