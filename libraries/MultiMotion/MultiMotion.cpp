#include "Arduino.h"
#include "MultiMotion.h"
#include "Servo.h"

MultiMotion::MultiMotion(StepperMotion Stepperz, StepperMotion Stepperx)
{
  x = Stepperx;
  z = Stepperz;
  //grabber.attach(servopin);
  //grabber.write(servohome);
}

MultiMotion::MultiMotion()
{

}

void MultiMotion::moveToMulti(double desiredx, double desiredz)
{
	Serial.println("Traveling to: ");
	Serial.print(desiredx);
	Serial.print(", ");
	Serial.println(desiredz);
  unsigned long intervalx = x.getInterval();
  unsigned long intervalz = z.getInterval();
  boolean hasArrivedx = false;
  boolean hasArrivedz = false;
  unsigned long lasttickx = micros();
  unsigned long lasttickz = micros();
  unsigned long newtime;
  while(hasArrivedx == false || hasArrivedz == false)
  {  
	newtime = micros();
	if (newtime >= lasttickx + intervalx)
	{
		if (x.loc < desiredx && !hasArrivedx)
		{
			x.frontstep(0);
			lasttickx = micros();
			if (x.loc >= desiredx)
				hasArrivedx = true;
		}
		else if (x.loc > desiredx && !hasArrivedx)
		{
			x.backstep(0);
			lasttickx = micros();
			if (x.loc <= desiredx) 
				hasArrivedx = true;
			}
		else
			hasArrivedx = true;
	}
	
	if (newtime >= lasttickz + intervalz)
	{
		if (z.loc < desiredz && !hasArrivedz)
		{
			z.frontstep(0);
			lasttickz = micros();
			if (z.loc >= desiredz)
				hasArrivedz = true;
		}
		else if (z.loc > desiredz && !hasArrivedz)
		{
			z.backstep(0);
			lasttickz = micros();
			if (z.loc <= desiredz)
				hasArrivedz = true;
		}
		else
			hasArrivedz = true;
	}
	//delayMicroseconds(interval);
  }
	
}


void MultiMotion::approachBattery()
{
	moveToMulti(forktouchX-5, batteryholderZ[batteryNumber-1]);
}

void MultiMotion::enterBattery()
{
	x.moveTo(forkflushX);
}

void MultiMotion::removeBattery()
{
	x.moveTo(batteryexitX-20);
}

void MultiMotion::approachWithBattery()
{
	moveToMulti(batteryexitX - 15, batteryholderZ[batteryNumber-1]+ withbatteryoffsetZ);
}

void MultiMotion::insertBattery()
{
	x.moveTo(batteryexitX + withbatteryoffsetX);
}

void MultiMotion::recenterBattery()
{
	z.moveTo(batteryholderZ[batteryNumber-1]);
}

void MultiMotion::gripBattery()
{
	delay(100);
	grabber.write(servolocked);
	delay(100);
}

void MultiMotion::releaseBattery()
{
	delay(100);
	grabber.write(servohome);
	delay(100);
}

void MultiMotion::retrieveBattery()
{
	approachBattery();
	enterBattery();
	gripBattery();
	removeBattery();
}

void MultiMotion::returnBattery()
{
	approachWithBattery();
	insertBattery();
	recenterBattery();
	enterBattery();
	releaseBattery();
	approachBattery();
}

void MultiMotion::servoInit()
{
	//Servo grabber;
	grabber.attach(servopin);
	grabber.write(servohome);
	grabber.write(servolocked);
	grabber.write(servohome);
}