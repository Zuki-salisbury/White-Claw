#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// These values are adjusted for the MG996R
int servoMin = 120; // Minimum pulse length count (0 degrees)
int servoMax = 600; // Maximum pulse length count (180 degrees)

// Variables to track the current position of each joint
int elbowPosition = servoMax;
int forearmPosition = servoMax;
int wristPosition = servoMax;
int clawPosition = servoMax;
int shoulderPosition1 = servoMin;
int shoulderPosition2 = servoMax;

bool isElbowAtMax = true;
bool isForearmAtMax = true;
bool isWristAtMax = true;
bool isClawAtMax = true;
bool isShoulderFlipped = true;

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);  // Set frequency to 50 Hz, suitable for MG996R

  // Initialize each joint to its maximum position
  pwm.setPWM(3, 0, elbowPosition);  // Elbow
  pwm.setPWM(2, 0, forearmPosition);  // Forearm
  pwm.setPWM(4, 0, wristPosition);  // Wrist
  pwm.setPWM(5, 0, clawPosition);  // Claw
  pwm.setPWM(0, 0, shoulderPosition1);  // Shoulder Part 1
  pwm.setPWM(1, 0, shoulderPosition2);  // Shoulder Part 2

  Serial.println("Type '1' to toggle the elbow joint position between min and max.");
  Serial.println("Type '2' to toggle the forearm joint position between min and max.");
  Serial.println("Type '3' to toggle the wrist joint position between min and max.");
  Serial.println("Type '4' to toggle the claw joint position between min and max.");
  Serial.println("Type '5' to toggle the shoulder joint positions.");
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == '1') {
      if (isElbowAtMax) {
        elbowPosition = servoMin;  // Move elbow to min position
        // elbowPosition = 0;
      } else {
        elbowPosition = servoMax;  // Move elbow to max position
      }
      pwm.setPWM(3, 0, elbowPosition);
      Serial.print("Elbow position: ");
      Serial.println(elbowPosition);
      isElbowAtMax = !isElbowAtMax;
    }

    if (input == '2') {
      if (isForearmAtMax) {
        forearmPosition = servoMin;  // Move forearm to min position
      } else {
        forearmPosition = servoMax;  // Move forearm to max position
      }
      pwm.setPWM(2, 0, forearmPosition);
      Serial.print("Forearm position: ");
      Serial.println(forearmPosition);
      isForearmAtMax = !isForearmAtMax;
    }

    if (input == '3') {
      if (isWristAtMax) {
        wristPosition = servoMin;  // Move wrist to min position
      } else {
        wristPosition = servoMax;  // Move wrist to max position
      }
      pwm.setPWM(4, 0, wristPosition);
      Serial.print("Wrist position: ");
      Serial.println(wristPosition);
      isWristAtMax = !isWristAtMax;
    }

    if (input == '4') {
      if (isClawAtMax) {
        clawPosition = servoMin;  // Move claw to min position
      } else {
        clawPosition = servoMax;  // Move claw to max position
      }
      pwm.setPWM(5, 0, clawPosition);
      Serial.print("Claw position: ");
      Serial.println(clawPosition);
      isClawAtMax = !isClawAtMax;
    }

    if (input == '5') {
      if (isShoulderFlipped) {
        shoulderPosition1 = servoMin;
        shoulderPosition2 = servoMax;
      } else {
        shoulderPosition1 = servoMax;
        shoulderPosition2 = servoMin;
      }
      pwm.setPWM(0, 0, shoulderPosition1);
      pwm.setPWM(1, 0, shoulderPosition2);
      Serial.print("Shoulder positions: ");
      Serial.print("Position 1: ");
      Serial.print(shoulderPosition1);
      Serial.print(", Position 2: ");
      Serial.println(shoulderPosition2);
      isShoulderFlipped = !isShoulderFlipped;
    }
  }
}
