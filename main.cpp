#include <SoftwareSerial.h>
#include <Servo.h>

// SoftwareSerial for Bluetooth communication (change pins if needed)
SoftwareSerial mySerial(7, 8); // RX, TX

// Create a Servo object to control a servo motor
Servo myServo;

int angle = 90;    // Start at 90 degrees (middle position)
int increment = 5; // Amount of angle change per step

void setup()
{
    // Begin serial communication for monitoring
    Serial.begin(115200);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    // Initialize software serial for the HM-10 Bluetooth module
    mySerial.begin(9600);

    // Attach the servo motor to pin 9
    myServo.attach(9);

    // Initialize servo to the middle (90-degree) position;
    myServo.write(angle);
    Serial.println("Servo initialized at 90 degrees.");
}

void loop()
{
    // Check if there is data available from the Bluetooth module
    if (mySerial.available())
    {
        // Read the incoming data (either J0 or J1)
        String input = mySerial.readStringUntil('\n'); // Read until newline
        Serial.print("Input: ");
        Serial.println(input); // Print the input for debugging

        // Check if input is J0 or J1
        if (input.startsWith("up"))
        {
            // rotateRight(); // Call the function to rotate right (clockwise)
            Serial.print("arm up");
        }
        else if (input.startsWith("J1"))
        {
            rotateLeft(); // Call the function to rotate left (counterclockwise)
        }
        else
        {
            Serial.println("Invalid input received.");
        }
    }

    // Optionally, check if there is data from the Serial Monitor for testing
    if (Serial.available())
    {
        // Forward data from the Serial Monitor to the Bluetooth module
        mySerial.write(Serial.read());
    }
}

// Function to rotate servo to the right (clockwise)
void rotateRight()
{
    angle += increment; // Increase angle
    if (angle > 180)
    {              // Keep angle within bounds (0-180)
        angle = 0; // Wrap around to 0 degrees
    }
    myServo.write(angle); // Move the servo
    Serial.print("Servo rotated right to ");
    Serial.print(angle);
    Serial.println(" degrees.");
    delay(50); // Adjust delay to control speed of rotation
}

// Function to rotate servo to the left (counterclockwise)
void rotateLeft()
{
    angle -= increment; // Decrease angle
    if (angle < 0)
    {                // Keep angle within bounds (0-180)
        angle = 180; // Wrap around to 180 degrees
    }
    myServo.write(angle); // Move the servo
    Serial.print("Servo rotated left to ");
    Serial.print(angle);
    Serial.println(" degrees.");
    delay(50); // Adjust delay to control speed of rotation
}