#include <Servo.h>

Servo baseServo;   // Servo for base rotation
Servo armServo;    // Servo for arm movement
Servo wristServo;  // Servo for wrist movement
Servo gripperServo;// Servo for gripper control

int baseInitialPosition = 90;    // Initial position of base servo
int armInitialPosition = 0;     // Initial position of arm servo
int wristInitialPosition = 90;   // Initial position of wrist servo
int gripperInitialPosition = 110;// Initial position of gripper servo

const int baudRate = 9600;  // Serial communication baud rate
int gripperDelay = 1000;    // Delay before gripper movement

void setup() {
  Serial.begin(baudRate);  // Initialize serial communication
  baseServo.attach(6);
  armServo.attach(7);
  wristServo.attach(8);
  gripperServo.attach(9);
  armServo.attach(7);


  // Initialize servos to their initial positions
  baseServo.write(baseInitialPosition);
  armServo.write(armInitialPosition);
  wristServo.write(wristInitialPosition);
  gripperServo.write(gripperInitialPosition);

  // Add any additional setup code here
}

void loop() {
  // Read serial data sent from the computer
  while (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');

    // Parse data received from the computer
    int centerX, centerY, distance;
    sscanf(data.c_str(), "<%d,%d,%d>", &centerX, &centerY, &distance);

    // Control the arm based on the detected object's center point and distance
    if (centerX < 1097 && centerY < 270) {
      // Move servos for left movement
      // Adjust the angles according to your setup
      baseServo.write(90);
      armServo.write(90);
      wristServo.write(145);
      delay(1000); // Delay after wrist movement
      gripperServo.write(0);
      delay(gripperDelay); // Delay before gripper movement

    } else if (centerX < 1079 && centerY > 685) {
      // Move servos for left movement
      // Adjust the angles according to your setup
      baseServo.write(90);
      armServo.write(0);
      wristServo.write(180);
      delay(1000); // Delay after wrist movement
      gripperServo.write(0);
      delay(gripperDelay); // Delay before gripper movement
    }

    if (centerY > 298 && centerY < 685 && centerX > 0 && centerX < 598) {
     // Move servos for left movement
      // Adjust the angles according to your setup
      baseServo.write(105);
      armServo.write(40);
      wristServo.write(150);
      delay(1000); // Delay after wrist movement
      gripperServo.write(0);
      delay(gripperDelay); // Delay before gripper movement
    } else if (centerY > 274 && centerY < 685 && centerX > 731 && centerX < 1097) {
      // Move servos for left movement
      // Adjust the angles according to your setup
      baseServo.write(68);
      armServo.write(40);
      wristServo.write(150);
      delay(1000); // Delay after wrist movement
      gripperServo.write(0);
      delay(gripperDelay); // Delay before gripper movement
    }

    // Return servos to initial positions
    delay(1000); // Adjust delay as needed

    baseServo.write(baseInitialPosition);
    armServo.write(armInitialPosition);
    wristServo.write(wristInitialPosition);

    // Open gripper once arm is back to initial position
    delay(1000); // Adjust delay as needed
    gripperServo.write(120);  // Open gripper

    delay(1000); // Adjust delay as needed
  }
}
