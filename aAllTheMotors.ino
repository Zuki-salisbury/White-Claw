#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// These values are adjusted for the MG996R
int servoMin = 120; // Minimum pulse length count (0 degrees)
int servoMax = 600; // Maximum pulse length count (180 degrees)

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);  // Set frequency to 50 Hz, suitable for MG996R
}

void loop() {
  // Turn Arm to 0 degrees
  pwm.setPWM(0, 0, servoMin);
  delay(1000);
  // Turn Arm to 0 degrees
  pwm.setPWM(1, 0, servoMax);
  delay(1000);

  // joint 1
  pwm.setPWM(2, 0, servoMax);
  delay(1000);

  // joint 2
  pwm.setPWM(3, 0, servoMax);
  delay(1000);

  // wrist joint
  pwm.setPWM(4, 0, servoMax);
  delay(1000);

  // claw
  pwm.setPWM(5, 0, servoMax);
  delay(1000);

  // ---------------------------------------
  
  // Turn arm to 180 degrees
  pwm.setPWM(0, 0, servoMax);
  delay(1000);

  // Turn arm to 180 degrees
  pwm.setPWM(1, 0, servoMin);
  delay(1000);

  // joint 1
  pwm.setPWM(2, 0, servoMin);
  delay(1000); 

  // joint 2
  pwm.setPWM(3, 0, servoMin);
  delay(1000);

  // wrist joint
  pwm.setPWM(4, 0, servoMin);
  delay(1000);

  // claw
  pwm.setPWM(5, 0, servoMin);
  delay(1000);
}