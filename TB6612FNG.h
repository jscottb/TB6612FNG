// TB6612FNG Motor Driver Library
// based on the Adafruit Motor shield library
// this code is also public domain, enjoy!

#ifndef _TB6612FNG_h_
#define _TB6612FNG_h_

#include <inttypes.h>
#include <avr/io.h>

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 4
#define RELEASE 8
#define NOPWM 0
#define NOSTBY 0

class TB6612FNG_Motor {
public:
        TB6612FNG_Motor(uint8_t in1, uint8_t in2, uint8_t pwm, uint8_t standby);
	bool run(uint8_t);
	void setSpeed(uint8_t);
        uint8_t getSpeed(void);
	uint8_t getState(void);
	uint8_t getDirection(void);
      	
private:
	uint8_t motor_ia, motor_ib, motor_pwm, motor_stby, runstate, 
                currentspeed;
};

#endif
