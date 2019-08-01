#ifndef MultiMotion_h
#define MultiMotion_h

#include "Arduino.h"
#include "StepperMotion.h"
#include "Servo.h"

class MultiMotion
{
  public:
	MultiMotion(StepperMotion Stepperx, StepperMotion Stepperz);
	MultiMotion();
	
	StepperMotion x;
	StepperMotion z;
	
	Servo grabber;
	int servopin = 2;
	int servohome = 160;
	int servolocked = 110;
	
	double forktouchX = 398;
	double forkflushX = 436;
	double batteryexitX = 236;
	double batteryentranceX = 241;
	double withbatteryoffsetZ = 5;
	double withbatteryoffsetX = 4;
	
	int batteryNumber = 1;
	double batteryholderZ[2] = {47, 382};
	
	void moveToMulti(double desiredx, double desiredz);
	void approachBattery();
	void enterBattery();
	void removeBattery();
	void approachWithBattery();
	void insertBattery();
	void recenterBattery();
	void gripBattery();
	void releaseBattery();
	void retrieveBattery();
	void returnBattery();
	void servoInit();
	
  private:

};

#endif