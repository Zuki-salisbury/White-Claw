#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// These values are adjusted for the MG996R
int servoMin = 140; // Minimum pulse length count (0 degrees)
int servoMax = 330; // Maximum pulse length count (180 degrees)
int stepDelay = 0; // Delay between steps in milliseconds

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Set frequency to 50 Hz, suitable for MG996R
}

void slowMoveSimultaneous(int servo1, int servo2, int start1, int end1, int start2, int end2) {
  int pos1 = start1;
  int pos2 = start2;
  
  while (pos1 != end1 || pos2 != end2) {
    if (pos1 != end1) {
      pwm.setPWM(servo1, 0, pos1);
      pos1 += (start1 < end1) ? 1 : -1;
    }
    if (pos2 != end2) {
      pwm.setPWM(servo2, 0, pos2);
      pos2 += (start2 < end2) ? 1 : -1;
    }
    delay(stepDelay);
  }
}

void loop() {
  // Move both motors from 0 degrees to 180 degrees slowly
  slowMoveSimultaneous(0, 1, servoMin, servoMax, servoMin, servoMax);
  delay(2000);  // Wait for 2 seconds

  // Move both motors from 180 degrees to 0 degrees slowly
  slowMoveSimultaneous(0, 1, servoMax, servoMin, servoMax, servoMin);
  delay(2000);  // Wait for 2 seconds
}
