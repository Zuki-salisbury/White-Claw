#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// These values are adjusted for the MG996R
int servoMin = 120; // Minimum pulse length count (0 degrees)
int servoMax = 600; // Maximum pulse length count (180 degrees)

bool isElbowAtMax = true;
bool isForearmAtMax = true;
bool isWristAtMax = true;
bool isclawAtMax = true;
bool isShoulderFlipped = false; 

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);  // Set frequency to 50 Hz, suitable for MG996R

  //Elbow Joint
  pwm.setPWM(3, 0, servoMax);

  //Forearm Joint
  pwm.setPWM(2, 0, servoMax);

  //Wrist Joint
  pwm.setPWM(4, 0, servoMax);

  //Claw Joint
  pwm.setPWM(5, 0, servoMax);

  //Shoulder
  //pwm.setPWM(0, 0, servoMax);
  //pwm.setPWM(1, 0, servoMin);

  Serial.println("Type '1' to toggle the elbow joint position between min and max.");
  Serial.println("Type '2' to toggle the forearm joint position between min and max.");
  Serial.println("Type '3' to toggle the wrist joint position between min and max.");
  Serial.println("Type '4' to toggle the claw joint position between min and max.");
  Serial.println("Type '5' to toggle the shoulder joint positions.");
  
}

void loop() {
  //Move forearm based off input through seriel monitor
  // Check if data is available in the Serial Monitor
  if (Serial.available() > 0) {
    // Read the input as a single character
    char input = Serial.read();

    // If the input is '1', toggle the elbow joint position
    if (input == '1') {
      if (isElbowAtMax) {
        pwm.setPWM(3, 0, servoMin);  // Move elbow joint to min position
        Serial.println("Elbow joint moved to min position.");
      } else {
        pwm.setPWM(3, 0, servoMax);  // Move elbow joint to max position
        Serial.println("Elbow joint moved to max position.");
      }

      // Toggle the position flag
      isElbowAtMax = !isElbowAtMax;
    }
    // If the input is '2', toggle the Forearm joint position
    if (input == '2') {
      if (isForearmAtMax) {
        pwm.setPWM(2, 0, servoMin);  // Move Forearm joint to min position
        Serial.println("Forearm joint moved to min position.");
      } else {
        pwm.setPWM(2, 0, servoMax);  // Move Forearm joint to max position
        Serial.println("Forearm joint moved to max position.");
      }

      // Toggle the position flag
      isForearmAtMax = !isForearmAtMax;
    }
    // If the input is '3', toggle the Wrist joint position
    if (input == '3') {
      if (isWristAtMax) {
        pwm.setPWM(4, 0, servoMin);  // Move Wrist joint to min position
        Serial.println("Wrist joint moved to min position.");
      } else {
        pwm.setPWM(4, 0, servoMax);  // Move Wrist joint to max position
        Serial.println("Wrist joint moved to max position.");
      }

      // Toggle the position flag
      isWristAtMax = !isWristAtMax;
    }

    // If the input is '4', toggle the claw joint position
    if (input == '4') {
      if (isclawAtMax) {
        pwm.setPWM(5, 0, servoMin);  // Move claw joint to min position
        Serial.println("Claw joint moved to min position.");
      } else {
        pwm.setPWM(5, 0, servoMax);  // Move claw joint to max position
        Serial.println("Claw joint moved to max position.");
      }

      // Toggle the position flag
      isclawAtMax = !isclawAtMax;
    }

    /*

    // Toggle shoulder joint positions when '5' is pressed
    if (input == '5') {
      if (isShoulderFlipped) {
        pwm.setPWM(0, 0, servoMin); // Move port 1 to max
        pwm.setPWM(1, 0, servoMax); // Move port 2 to min
        Serial.println("Shoulder joint set: Port 1 at max, Port 2 at min.");
      } else {
        pwm.setPWM(0, 0, servoMax); // Move port 1 to min
        pwm.setPWM(1, 0, servoMin); // Move port 2 to max
        Serial.println("Shoulder joint set: Port 1 at min, Port 2 at max.");
      }
      
      // Toggle the shoulder position flag
      isShoulderFlipped = !isShoulderFlipped;
    }
    */
  }

  // Turn motor on port 0 to 0 degrees
  //pwm.setPWM(0, 0, servoMin);
  // Turn motor on port 1 to 0 degrees
  //delay(1000);

  //pwm.setPWM(1, 0, servoMax);

  //delay(1000);  // Wait for 1 second

  // forearm joint
  //wm.setPWM(2, 0, servoMax);

  //delay(1000);

  // Elbow joint
  //pwm.setPWM(3, 0, servoMax);

  //delay(1000);  // Wait for 1 second

  // forearm joint
  //pwm.setPWM(2, 0, servoMin);

  //delay(1000);  // Wait for 1 second

  // Elbow joint
  //pwm.setPWM(3, 0, servoMin);

  //delay(1000);
  
  // Turn motor on port 0 to 180 degrees
  //pwm.setPWM(0, 0, servoMax);

  //delay(1000);
  // Turn motor on port 1 to 180 degrees
  //pwm.setPWM(1, 0, servoMin);

  //delay(1000);  // Wait for 1 second

  //pwm.setPWM(2, 0, servoMin);

  //delay(1000); 

  //pwm.setPWM(3, 0, servoMin);

  //delay(1000);  // Wait for 1 second
}
