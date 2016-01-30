// TB6612FNG Motor driver Library
// based on the Adafruit Motor shield library
// this code is also public domain, enjoy!

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include <avr/io.h>
#include "WProgram.h"
#endif

#include "TB6612FNG.h" 

TB6612FNG_Motor::TB6612FNG_Motor(uint8_t in1, uint8_t in2, 
                                 uint8_t pwm, uint8_t standby) {
   motor_ia = in1;
   motor_ib = in2;
   motor_pwm = pwm;
   motor_stby = standby;
   pinMode(motor_ia, OUTPUT); 
   pinMode(motor_ib, OUTPUT);

   if (motor_pwm) { 
      pinMode(motor_pwm, OUTPUT);
   }

   if (motor_stby) { 
      pinMode(motor_stby, OUTPUT); 
   }
}

bool TB6612FNG_Motor::run(uint8_t cmds) {
   if (((FORWARD | BACKWARD) & cmds) == (FORWARD | BACKWARD)) {
      return false;
   }

   if (((BRAKE | RELEASE) & cmds) == (BRAKE | RELEASE)) {
      return false;
   }

   if ((cmds & FORWARD) == FORWARD) {
      digitalWrite(motor_ia, LOW);
      digitalWrite(motor_ib, HIGH);
      analogWrite(motor_pwm, currentspeed);
      runstate = (runstate & (BRAKE | RELEASE)) | FORWARD;
   }

   if ((cmds & BACKWARD) == BACKWARD) {
      digitalWrite(motor_ia, HIGH);
      digitalWrite(motor_ib, LOW);
      analogWrite(motor_pwm, currentspeed);
      runstate = (runstate & (BRAKE | RELEASE)) | BACKWARD;
   }

   if ((cmds & RELEASE) == RELEASE) {
      if (motor_stby) { 
         digitalWrite(motor_stby, HIGH);
//         digitalWrite(motor_stby, LOW);
      }
      if ((runstate & FORWARD) == FORWARD) {
         digitalWrite(motor_ia, LOW);
         digitalWrite(motor_ib, HIGH);
         analogWrite(motor_pwm, currentspeed);
      }

      if ((runstate & BACKWARD) == BACKWARD) {
         digitalWrite(motor_ia, HIGH);
         digitalWrite(motor_ib, LOW);
         analogWrite(motor_pwm, currentspeed);
      } 

      runstate = (runstate & (FORWARD | BACKWARD)) | RELEASE;
   }

   if ((cmds & BRAKE) == BRAKE) {
      digitalWrite(motor_ia, LOW);
      digitalWrite(motor_ib, LOW);
      analogWrite(motor_pwm, 255);
	  
      if (motor_stby) { 
//         digitalWrite(motor_stby, HIGH);
         digitalWrite(motor_stby, LOW);
      }

      runstate = (runstate & (FORWARD | BACKWARD)) | BRAKE;
   }

   return true;
}

void TB6612FNG_Motor::setSpeed(uint8_t speed) {
   if (speed > 255) speed = 255;
   else if (speed < 0) speed = 0;
   currentspeed = speed;

   if ((runstate & FORWARD) == FORWARD) {
      digitalWrite(motor_ia, LOW);
      digitalWrite(motor_ib, HIGH);
      analogWrite(motor_pwm, currentspeed);
   }

   if ((runstate & BACKWARD) == BACKWARD) {
      digitalWrite(motor_ia, HIGH);
      digitalWrite(motor_ib, LOW);
      analogWrite(motor_pwm, currentspeed);
   } 
}

uint8_t TB6612FNG_Motor::getSpeed(void) {
   return (uint8_t) currentspeed;
}

uint8_t TB6612FNG_Motor::getState(void) {
   return runstate & (BRAKE | RELEASE);
}

uint8_t TB6612FNG_Motor::getDirection(void) {
   return runstate & (FORWARD | BACKWARD);
}

