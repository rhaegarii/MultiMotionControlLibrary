#include <AccelStepper.h>
const int ena = 5;
const int dir = 6;
const int pul = 7;

const int upperlim = 3;
const int lowerlim = 4;




AccelStepper stepper1(1, pul, dir);


void setup() {
//stepper1.setEnablePin(ena);
digitalWrite(ena, LOW);
//stepper1.setPinsInverted(false, false, true);

//Serial.begin(1000000);
stepper1.setSpeed(4000);
stepper1.setMaxSpeed(4000);
//stepper1.setAcceleration(10000.0);
//Serial.println("Starting Zeroing");
//while (digitalRead(lowerlim) == LOW) {
 // stepper1.run();

//}
//stepper1.moveTo(200);
//Serial.println("Starting Loop");
}

void loop() {
stepper1.runSpeed();
}
