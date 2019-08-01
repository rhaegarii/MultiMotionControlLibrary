#include <Servo.h>
Servo mygripper;
void setup() {
  // put your setup code here, to run once:
mygripper.attach(2);
//mygripper.write(0);
//mygripper.write(25);
//mygripper.write(0);
}

void loop() {
mygripper.write(160);
delay(3000);
mygripper.write(110);
delay(3000);

}
