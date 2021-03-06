#include <TB6612FNG.h>

TB6612FNG_Motor motor(7, 9, 10, 8);
TB6612FNG_Motor motor2(11, 12, 13, 0);

void setup() {
  // engage the motor's brake 
  motor.run(BRAKE);
  motor.setSpeed(255);
  motor2.run(BRAKE);
  motor2.setSpeed(255);
  Serial.begin(9600);
}

void loop() {
  Serial.println("loop");
  Serial.print(decodeState(motor.getState()));
  Serial.print(" ");
  Serial.println(decodeState(motor.getDirection()));
  // set direction to forward and release the brake in a single call
  motor.run(FORWARD|RELEASE);
  motor2.run(FORWARD|RELEASE);
  Serial.print(decodeState(motor.getState()));
  Serial.print(" ");
  Serial.println(decodeState(motor.getDirection()));
  delay(1500);
  // switch directions and engage the brake
  motor.run(BRAKE|BACKWARD);
  motor2.run(BRAKE|BACKWARD);
  Serial.print(decodeState(motor.getState()));
  Serial.print(" ");
  Serial.println(decodeState(motor.getDirection()));
  delay(1500);
  // release the brake now -- the motor should start running in the opposite direction
  motor.run(RELEASE);
  motor2.run(RELEASE);
  Serial.print(decodeState(motor.getState()));
  Serial.print(" ");
  Serial.println(decodeState(motor.getDirection()));
  delay(1500);
  motor.setSpeed(0);
  motor2.setSpeed(0);
  delay(1500);
  // engage the brake again
  motor.run(BRAKE);
  motor.setSpeed(255);
  motor2.run(BRAKE);
  motor2.setSpeed(255);
}

// helper function to print the motor's states in human-readable strings.
String decodeState(int state) {
  String result = "";
  switch (state) {
    case FORWARD:
      result = "Forward";
      break;
    case BACKWARD:
      result = "Backward";
      break;
    case BRAKE:
     result = "Brake";
     break;
   case RELEASE:
     result = "Release";
     break;
   }
  return result;
}
