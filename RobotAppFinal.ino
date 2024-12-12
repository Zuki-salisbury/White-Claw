include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>
// Constants
SoftwareSerial mySerial(7, 8); // RX, TX
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
const int SERVO_FREQ = 50;
const int SHOULDER_MIN = 179; // Minimum position for Shoulder 1
const int SHOULDER_MAX = 487; // Maximum position for Shoulder 1

// Degree mappings
int degrees[] = {103, 128, 154, 179, 205, 231, 256, 282, 308, 333, 359, 384, 410, 436, 461, 487, 513, 538, 564};
// Joint positions
int shoulderPos[2], elbowPos, forearmPos, wristPos, clawPos;
// Function prototypes
void initializeServos();
void moveJoint(int &currentPos, int step, int channel, const char *jointName);
void moveShoulder(int step);
void handleInput(char input);
void sayHello();
void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  mySerial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  initializeServos();
}
void loop() {
  if (mySerial.available()) {
    char input = mySerial.read();
    if (input != '\n' && input != '\r') {
      handleInput(input);
    }
  }
}
void initializeServos() {
  // Initialize servos to default positions
  shoulderPos[0] = 487; // Degrees 0
  shoulderPos[1] = 179;
  elbowPos = wristPos = clawPos = degrees[6]; // Degrees 0
  forearmPos = degrees[15];
  pwm.setPWM(0, 0, shoulderPos[0]);
  pwm.setPWM(1, 0, shoulderPos[1]);
  pwm.setPWM(2, 0, elbowPos);
  pwm.setPWM(3, 0, forearmPos);
  pwm.setPWM(4, 0, wristPos);
  pwm.setPWM(5, 0, clawPos);
}
void moveJoint(int &currentPos, int step, int channel, const char *jointName) {
  int currentIndex = -1;
  for (int i = 0; i < sizeof(degrees) / sizeof(degrees[0]); i++) {
    if (degrees[i] == currentPos) {
      currentIndex = i;
      break;
    }
  }
  int newIndex = currentIndex + step;
  if (newIndex >= 0 && newIndex < sizeof(degrees) / sizeof(degrees[0])) {
    int newPosition = degrees[newIndex];
    // Check limits for Shoulder 1 and Shoulder 2
    if ((channel == 0 && (newPosition == SHOULDER_MIN || newPosition == SHOULDER_MAX)) || 
        (channel == 1 && (newPosition == SHOULDER_MIN || newPosition == SHOULDER_MAX))) {
      Serial.print(jointName);
      Serial.println(" Movement out of bounds (limit reached)");
      return;
    }
    if ((channel == 2 && (newPosition >= 256))) {
      Serial.print(jointName);
      Serial.println(" Movement out of bounds (limit reached)");
      return;
    }
    // Update position and move the servo
    currentPos = newPosition;
    pwm.setPWM(channel, 0, currentPos);
    Serial.print(jointName);
    Serial.print(" Position1: ");
    Serial.println(currentPos);
  } else {
    Serial.print(jointName);
    Serial.println(" Movement out of bounds (invalid index)");
  }
}
void moveShoulder(int step) {
  moveJoint(shoulderPos[0], step, 0, "Shoulder 1");
  moveJoint(shoulderPos[1], -step, 1, "Shoulder 2");
}
void handleInput(char input) {
  switch (input) {
    case '0': moveShoulder(-1); break; // Move shoulder Up
    case '1': moveShoulder(1); break;  // Move shoulder Down
    case '2': moveJoint(elbowPos, 1, 2, "Elbow\n"); break;  // Move elbow Up
    case '3': moveJoint(elbowPos, -1, 2, "Elbow\n"); break; // Move elbow Down
    case '4': moveJoint(forearmPos, 1, 3, "Forearm\n"); break; // Move forearm Down
    case '5': moveJoint(forearmPos, -1, 3, "Forearm\n"); break; // Move forearm Up
    case '6': moveJoint(wristPos, 1, 4, "Wrist\n"); break;    // Move wrist Right
    case '7': moveJoint(wristPos, -1, 4, "Wrist\n"); break;   // Move wrist Left
    case '8': moveJoint(clawPos, 1, 5, "Claw\n"); break;     // Open claw
    case '9': moveJoint(clawPos, -1, 5, "Claw\n"); break;    // Close claw
    case 'h': sayHello(); break;
    case 's': initializeServos(); break;
    default: Serial.println("-"); return;
  }
}
void sayHello() {
  for (int i = 0; i < 3; i++) {
    Serial.println("Saying Hello!");
    // Move to degrees[10] (high position)
    forearmPos = degrees[12];
    pwm.setPWM(3, 0, forearmPos);
    delay(500); // Pause for 500ms
    // Move to degrees[3] (low position)
    forearmPos = degrees[6];
    pwm.setPWM(3, 0, forearmPos);
    delay(500); // Pause for 500ms
  }
}
