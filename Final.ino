#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); // RX, TX
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// convert real world degrees to MG 996R degrees
int degrees0 = 103;
int degrees10 = 128;
int degrees20 = 154;
int degrees30 = 179;
int degrees40 = 205;
int degrees50 = 231;
int degrees60 = 256;
int degrees70 = 282;
int degrees80 = 308;
int degrees90 = 333;
int degrees100 = 359;
int degrees110 = 384;
int degrees120 = 410;
int degrees130 = 436;
int degrees140 = 461;
int degrees150 = 487;
int degrees160 = 513;
int degrees170 = 538;
int degrees180 = 564;

// int degrees0 = 205;
// int degrees10 = 216;
// int degrees20 = 228;
// int degrees30 = 239;
// int degrees40 = 250;
// int degrees50 = 262;
// int degrees60 = 273;
// int degrees70 = 284;
// int degrees80 = 296;
// int degrees90 = 307;
// int degrees100 = 319;
// int degrees110 = 330;
// int degrees120 = 341;
// int degrees130 = 353;
// int degrees140 = 364;
// int degrees150 = 375;
// int degrees160 = 387;
// int degrees170 = 398;
// int degrees180 = 410;

// variable to keep every motor's cuurent positions
int currentPos[2];
int elbowPos;
int forearmPos;
int wristPos;
int clawPos;

void setup() {
  // Begin serial communication for monitoring
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // Initialize software serial for the HM-10 Bluetooth module
  mySerial.begin(9600);

  pwm.begin();
  // Set frequency to 50 Hz, suitable for MG996R
  pwm.setPWMFreq(50);

  // Initialize each joint to zero degrees
  // Initialize shoulder joint
  // pwm.setPWM(0, 0, degrees0);
  // pwm.setPWM(1, 0, degrees180);
  // currentPos[0] = degrees0;
  // currentPos[1] = degrees180;
  pwm.setPWM(0, 0, degrees90);
  pwm.setPWM(1, 0, degrees90);
  currentPos[0] = degrees90;
  currentPos[1] = degrees90;
  // pwm.setPWM(0, 0, degrees100);
  // pwm.setPWM(1, 0, degrees80);
  // currentPos[0] = degrees100;
  // currentPos[1] = degrees80;

  // Initialize elbow joint
  pwm.setPWM(3, 0, degrees0);
  elbowPos = degrees0;
  // Initialize forearm joint
  pwm.setPWM(2, 0, degrees0);
  forearmPos = degrees0;
  // Initialize wrist joint
  pwm.setPWM(4, 0, degrees0);
  wristPos = degrees0;
  // Initialize claw joint
  pwm.setPWM(5, 0, degrees0);
  clawPos = degrees0;

  Serial.print("current shoulder position is: ");
  Serial.print(currentPos[0]);
  Serial.print(", ");
  Serial.println(currentPos[1]);
}

void loop() {
  if (mySerial.available()) {
    String bluetooth_input = mySerial.readStringUntil('\n');
    Serial.print("Input: ");
    char input = bluetooth_input[0];
    Serial.println(input);

    // move shoulder joint based on the input
    if (input == '0') {
      if (currentPos[0] == degrees90 || currentPos[1] == degrees90) {
        pwm.setPWM(0, 0, degrees80);
        pwm.setPWM(1, 0, degrees100);
        currentPos[0] = degrees80;
        currentPos[1] = degrees100;
      }
      else if (currentPos[0] == degrees80 || currentPos[1] == degrees100) {
        pwm.setPWM(0, 0, degrees70);
        pwm.setPWM(1, 0, degrees110);
        currentPos[0] = degrees70;
        currentPos[1] = degrees110;
      }
      else if (currentPos[0] == degrees70 || currentPos[1] == degrees110) {
        pwm.setPWM(0, 0, degrees60);
        pwm.setPWM(1, 0, degrees120);
        currentPos[0] = degrees60;
        currentPos[1] = degrees120;
      }
      else if (currentPos[0] == degrees60 || currentPos[1] == degrees120) {
        pwm.setPWM(0, 0, degrees50);
        pwm.setPWM(1, 0, degrees130);
        currentPos[0] = degrees50;
        currentPos[1] = degrees130;
      }
      else if (currentPos[0] == degrees50 || currentPos[1] == degrees130) {
        pwm.setPWM(0, 0, degrees40);
        pwm.setPWM(1, 0, degrees140);
        currentPos[0] = degrees40;
        currentPos[1] = degrees140;
      }
      else if (currentPos[0] == degrees40 || currentPos[1] == degrees140) {
        pwm.setPWM(0, 0, degrees30);
        pwm.setPWM(1, 0, degrees150);
        currentPos[0] = degrees30;
        currentPos[1] = degrees150;
      }
      else if (currentPos[0] == degrees30 || currentPos[1] == degrees150) {
        pwm.setPWM(0, 0, degrees20);
        pwm.setPWM(1, 0, degrees160);
        currentPos[0] = degrees20;
        currentPos[1] = degrees160;
      }
      else if (currentPos[0] == degrees20 || currentPos[1] == degrees160) {
        pwm.setPWM(0, 0, degrees10);
        pwm.setPWM(1, 0, degrees170);
        currentPos[0] = degrees10;
        currentPos[1] = degrees170;
      }
      else if (currentPos[0] == degrees10 || currentPos[1] == degrees170) {
        pwm.setPWM(0, 0, degrees0);
        pwm.setPWM(1, 0, degrees180);
        currentPos[0] = degrees0;
        currentPos[1] = degrees180;
      }
      else if (currentPos[0] == degrees0 || currentPos[1] == degrees180) {
        Serial.print("The motor can only go down");
      } 
      else {
        Serial.print("it can only go down");
      }
    }
    if (input == '1') {
      if (currentPos[0] == degrees0 || currentPos[1] == degrees180) {
        pwm.setPWM(0, 0, degrees10);
        pwm.setPWM(1, 0, degrees170);
        currentPos[0] = degrees10;
        currentPos[1] = degrees170;
      }
      else if (currentPos[0] == degrees10 || currentPos[1] == degrees170) {
        pwm.setPWM(0, 0, degrees20);
        pwm.setPWM(1, 0, degrees160);
        currentPos[0] = degrees20;
        currentPos[1] = degrees160;
      }
      else if (currentPos[0] == degrees20 || currentPos[1] == degrees160) {
        pwm.setPWM(0, 0, degrees30);
        pwm.setPWM(1, 0, degrees150);
        currentPos[0] = degrees30;
        currentPos[1] = degrees150;
      }
      else if (currentPos[0] == degrees30 || currentPos[1] == degrees150) {
        pwm.setPWM(0, 0, degrees40);
        pwm.setPWM(1, 0, degrees140);
        currentPos[0] = degrees40;
        currentPos[1] = degrees140;
      }
      else if (currentPos[0] == degrees40 || currentPos[1] == degrees140) {
        pwm.setPWM(0, 0, degrees50);
        pwm.setPWM(1, 0, degrees130);
        currentPos[0] = degrees50;
        currentPos[1] = degrees130;
      }
      else if (currentPos[0] == degrees50 || currentPos[1] == degrees130) {
        pwm.setPWM(0, 0, degrees60);
        pwm.setPWM(1, 0, degrees120);
        currentPos[0] = degrees60;
        currentPos[1] = degrees120;
      }
      else if (currentPos[0] == degrees60 || currentPos[1] == degrees120) {
        pwm.setPWM(0, 0, degrees70);
        pwm.setPWM(1, 0, degrees110);
        currentPos[0] = degrees70;
        currentPos[1] = degrees110;
      }
      else if (currentPos[0] == degrees70 || currentPos[1] == degrees110) {
        pwm.setPWM(0, 0, degrees80);
        pwm.setPWM(1, 0, degrees100);
        currentPos[0] = degrees80;
        currentPos[1] = degrees100;
      }
      else if (currentPos[0] == degrees80 || currentPos[1] == degrees100) {
        pwm.setPWM(0, 0, degrees90);
        pwm.setPWM(1, 0, degrees90);
        currentPos[0] = degrees90;
        currentPos[1] = degrees90;
      }
      else if (currentPos[0] == degrees90 || currentPos[1] == degrees90) {
        Serial.println("The motor can only go up");
      }
    }

    // move elbow joint based on the input
    if (input == "2") {
      if (elbowPos == degrees0) {
        elbowPos = degrees10;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees10) {
        elbowPos = degrees20;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees20) {
        elbowPos = degrees30;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees30) {
        elbowPos = degrees40;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees40) {
        elbowPos = degrees50;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees50) {
        elbowPos = degrees60;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees60) {
        elbowPos = degrees70;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees70) {
        elbowPos = degrees80;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees80) {
        elbowPos = degrees90;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees90) {
        elbowPos = degrees100;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees100) {
        elbowPos = degrees110;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees110) {
        elbowPos = degrees120;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees120) {
        elbowPos = degrees130;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees130) {
        elbowPos = degrees140;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees140) {
        elbowPos = degrees150;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees150) {
        elbowPos = degrees160;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees160) {
        elbowPos = degrees170;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees170) {
        elbowPos = degrees180;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees180) {
        Serial.println("The motor can only go down");
      }
    } 
    else if (input == "3") {
      if (elbowPos == degrees180) {
        elbowPos = degrees170;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees170) {
        elbowPos = degrees160;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees160) {
        elbowPos = degrees150;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees150) {
        elbowPos = degrees140;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees140) {
        elbowPos = degrees130;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees130) {
        elbowPos = degrees120;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees120) {
        elbowPos = degrees110;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees110) {
        elbowPos = degrees100;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees100) {
        elbowPos = degrees90;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees90) {
        elbowPos = degrees80;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees80) {
        elbowPos = degrees70;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees70) {
        elbowPos = degrees60;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees60) {
        elbowPos = degrees50;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees50) {
        elbowPos = degrees40;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees40) {
        elbowPos = degrees30;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees30) {
        elbowPos = degrees20;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees20) {
        elbowPos = degrees10;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees10) {
        elbowPos = degrees0;
        pwm.setPWM(2, 0, elbowPos);
      }
      else if (elbowPos == degrees0) {
        Serial.print("The motor can only go up");
      }
    }

    // move forearm joint based on the input
    if (input == "4") {
      if (forearmPos == degrees0) {
        forearmPos = degrees10;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees10) {
        forearmPos = degrees20;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees20) {
        forearmPos = degrees30;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees30) {
        forearmPos = degrees40;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees40) {
        forearmPos = degrees50;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees50) {
        forearmPos = degrees60;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees60) {
        forearmPos = degrees70;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees70) {
        forearmPos = degrees80;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees80) {
        forearmPos = degrees90;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees90) {
        forearmPos = degrees100;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees100) {
        forearmPos = degrees110;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees110) {
        forearmPos = degrees120;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees120) {
        forearmPos = degrees130;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees130) {
        forearmPos = degrees140;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees140) {
        forearmPos = degrees150;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees150) {
        forearmPos = degrees160;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees160) {
        forearmPos = degrees170;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees170) {
        forearmPos = degrees180;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees180) {
        Serial.println("The motor can only go down");
      }
    } 
    else if (input == "5") {
      if (forearmPos == degrees180) {
        forearmPos = degrees170;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees170) {
        forearmPos = degrees160;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees160) {
        forearmPos = degrees150;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees150) {
        forearmPos = degrees140;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees140) {
        forearmPos = degrees130;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees130) {
        forearmPos = degrees120;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees120) {
        forearmPos = degrees110;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees110) {
        forearmPos = degrees100;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees100) {
        forearmPos = degrees90;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees90) {
        forearmPos = degrees80;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees80) {
        forearmPos = degrees70;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees70) {
        forearmPos = degrees60;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees60) {
        forearmPos = degrees50;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees50) {
        forearmPos = degrees40;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees40) {
        forearmPos = degrees30;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees30) {
        forearmPos = degrees20;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees20) {
        forearmPos = degrees10;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees10) {
        forearmPos = degrees0;
        pwm.setPWM(3, 0, forearmPos);
      }
      else if (forearmPos == degrees0) {
        Serial.print("The motor can only go up");
      }
    }

    // move wrist joint based on the input
    if (input == "6") {
      if (wristPos == degrees0) {
        wristPos = degrees10;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees10) {
        wristPos = degrees20;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees20) {
        wristPos = degrees30;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees30) {
        wristPos = degrees40;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees40) {
        wristPos = degrees50;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees50) {
        wristPos = degrees60;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees60) {
        wristPos = degrees70;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees70) {
        wristPos = degrees80;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees80) {
        wristPos = degrees90;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees90) {
        wristPos = degrees100;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees100) {
        wristPos = degrees110;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees110) {
        wristPos = degrees120;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees120) {
        wristPos = degrees130;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees130) {
        wristPos = degrees140;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees140) {
        wristPos = degrees150;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees150) {
        wristPos = degrees160;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees160) {
        wristPos = degrees170;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees170) {
        wristPos = degrees180;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees180) {
        Serial.println("The motor can only go down");
      }
    } 
    else if (input == "7") {
      if (wristPos == degrees180) {
        wristPos = degrees170;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees170) {
        wristPos = degrees160;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees160) {
        wristPos = degrees150;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees150) {
        wristPos = degrees140;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees140) {
        wristPos = degrees130;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees130) {
        wristPos = degrees120;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees120) {
        wristPos = degrees110;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees110) {
        wristPos = degrees100;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees100) {
        wristPos = degrees90;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees90) {
        wristPos = degrees80;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees80) {
        wristPos = degrees70;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees70) {
        wristPos = degrees60;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees60) {
        wristPos = degrees50;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees50) {
        wristPos = degrees40;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees40) {
        wristPos = degrees30;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees30) {
        wristPos = degrees20;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees20) {
        wristPos = degrees10;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees10) {
        wristPos = degrees0;
        pwm.setPWM(4, 0, wristPos);
      }
      else if (wristPos == degrees0) {
        Serial.print("The motor can only go up");
      }
    }

    // move claw joint based on the input
    if (input == "8") {
      if (clawPos == degrees0) {
        clawPos = degrees10;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees10) {
        clawPos = degrees20;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees20) {
        clawPos = degrees30;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees30) {
        clawPos = degrees40;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees40) {
        clawPos = degrees50;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees50) {
        clawPos = degrees60;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees60) {
        clawPos = degrees70;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees70) {
        clawPos = degrees80;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees80) {
        clawPos = degrees90;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees90) {
        clawPos = degrees100;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees100) {
        clawPos = degrees110;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees110) {
        clawPos = degrees120;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees120) {
        clawPos = degrees130;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees130) {
        clawPos = degrees140;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees140) {
        clawPos = degrees150;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees150) {
        clawPos = degrees160;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees160) {
        clawPos = degrees170;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees170) {
        clawPos = degrees180;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees180) {
        Serial.println("The claw can only close");
      }
    } 
    else if (input == "9") {
      if (clawPos == degrees180) {
        clawPos = degrees170;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees170) {
        clawPos = degrees160;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees160) {
        clawPos = degrees150;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees150) {
        clawPos = degrees140;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees140) {
        clawPos = degrees130;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees130) {
        clawPos = degrees120;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees120) {
        clawPos = degrees110;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees110) {
        clawPos = degrees100;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees100) {
        clawPos = degrees90;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees90) {
        clawPos = degrees80;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees80) {
        clawPos = degrees70;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees70) {
        clawPos = degrees60;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees60) {
        clawPos = degrees50;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees50) {
        clawPos = degrees40;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees40) {
        clawPos = degrees30;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees30) {
        clawPos = degrees20;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees20) {
        clawPos = degrees10;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees10) {
        clawPos = degrees0;
        pwm.setPWM(5, 0, clawPos);
      }
      else if (clawPos == degrees0) {
        Serial.print("The motor can only go open");
      }
    }

    // printing the positions of each joint
    Serial.print("Shoulder Position: ");
    Serial.print(currentPos[0]);
    Serial.print(", ");
    Serial.println(currentPos[1]);
    // Serial.print("Elbow Position: ");
    // Serial.println(elbowPos);
    // Serial.print("forearm Position: ");
    // Serial.println(forearmPos);
    // Serial.print("wrist Position: ");
    // Serial.println(wristPos);
    // Serial.print("claw Position: ");
    // Serial.println(clawPos);
  }
}