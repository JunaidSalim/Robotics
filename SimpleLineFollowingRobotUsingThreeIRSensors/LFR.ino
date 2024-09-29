int LeftIR = 8, CentreIR = 12, RightIR = 13;
int LeftForward = 5, LeftBackward = 9, RightForward = 10, RightBackward = 11;

int BaseSpeed = 200;
int TurnSpeed = 100;
int AdjustSpeed = 50;
int StabilityDelay = 40;

void setup() {
  // put your setup code here, to run once:
  pinMode(LeftForward, OUTPUT);
  pinMode(LeftBackward, OUTPUT);
  pinMode(RightForward, OUTPUT);
  pinMode(RightBackward, OUTPUT);

  // IR sensor pins setup
  pinMode(LeftIR, INPUT);
  pinMode(CentreIR, INPUT);
  pinMode(RightIR, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int left = digitalRead(LeftIR);
  int centre = digitalRead(CentreIR);
  int right = digitalRead(RightIR);

  int SensorState = (left * 4) + (centre * 2) + right;

  // Print the sensor state in decimal
  Serial.print("Sensor State: ");
  Serial.println(SensorState);

  switch (SensorState) {
    case 0:  // White On All Sensors
      Serial.println("Lost line, searching...");
      stopCar();
      break;

    case 1:  // Black on Right Sensor
      Serial.println("Full Right Turn");
      turnRight();
      break;

    case 2:  // Black on Centre
      Serial.println("Move Forward");
      moveForward();
      break;

    case 3:  // Black on Centre and Right
      Serial.println("Slight Left Turn");
      adjustLeft();
      break;

    case 4: // Black on Left
      Serial.println("Full Left Turn");
      turnLeft();
      break;

    case 5: // Black on Left and Right
      Serial.println("Full Right Turn");
      turnRight();
      break;

    case 6: // Black on Left and Centre
      Serial.println("Slight Right Turn");
      adjustRight();
      break;

    default:
      Serial.println("Default movement (Move Forward)");
      moveForward();
      break;
  }
  delay(StabilityDelay);
}

void moveForward() {
  analogWrite(LeftForward, BaseSpeed);
  analogWrite(LeftBackward, LOW);
  analogWrite(RightForward, BaseSpeed);
  analogWrite(RightBackward, LOW);
}

void turnRight() {
  analogWrite(LeftForward, TurnSpeed);
  analogWrite(LeftBackward, LOW);
  analogWrite(RightForward, LOW);
  analogWrite(RightBackward, LOW);
}

void adjustRight() {
  analogWrite(LeftForward, AdjustSpeed);
  analogWrite(LeftBackward, LOW);
  analogWrite(RightForward, LOW);
  analogWrite(RightBackward, LOW);
}

void turnLeft() {
  analogWrite(LeftForward, LOW);
  analogWrite(LeftBackward, LOW);
  analogWrite(RightForward, TurnSpeed);
  analogWrite(RightBackward, LOW);
}

void adjustLeft() {
  analogWrite(LeftForward, LOW);
  analogWrite(LeftBackward, LOW);
  analogWrite(RightForward, AdjustSpeed);
  analogWrite(RightBackward, LOW);
}

void stopCar() {
  analogWrite(LeftForward, LOW);
  analogWrite(LeftBackward, LOW);
  analogWrite(RightForward, LOW);
  analogWrite(RightBackward, LOW);
}