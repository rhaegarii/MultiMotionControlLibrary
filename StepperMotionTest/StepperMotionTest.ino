//Includes Libraries for Linear Motion as well as Servo Control
#include <StepperMotion.h>
#include <MultiMotion.h>
#include <Servo.h>


unsigned long lasttick = 0; //Number for keeping track of the number of microseconds since the program started
StepperMotion Stepper1(7, 6, 5, 4, 3, 8.0, 200.0, 300, 404.0); //Initializes z stage 1 motor by creating StepperMotion instance
StepperMotion Stepper2(10, 9, 8, 11, 12, 5, 200, 600, 438); //Initializes x motor by creating StepperMotion instance
StepperMotion Stepper3(26, 24, 22, 32, 33,5, 400, 500, 380); //Initializes z stage 2 motor by creating StepperMotion instance
MultiMotion xz(Stepper1, Stepper2); // Combines z stage 1 and x motors into MultiMotion class

//Initializes the variables used for keyboard control
static int desiredx;
static int desiredz;
static int desiredserv;
String inputloc;
String xstring;
String zstring;

//Begin Setup Function
void setup() {

Serial.begin(1000000); //Opens Serial port interface with laptop to allow communication


xz.servoInit(); //initializes servo
xz.retrieveBattery(); //grabs battery in lower receiver and removes it
xz.moveToMulti(200,100); // moves to arbitrary location for testing
xz.batteryNumber = 2; //Switches focus to upper battery box receiver
xz.returnBattery(); //"returns" battery to the upper receiver and forks disengage
xz.moveToMulti(300,300); //travels to arbitrary location for testing
xz.retrieveBattery(); //reenters battery (now in upper receiver) and removes it
xz.moveToMulti(200,100); //travels to arbitrary location for testing
xz.batteryNumber = 1; //Switches focus to lower battery box receiver
xz.returnBattery(); //"returns" battery to lower receiver and forks disengage


Serial.println("Enter Desired Location");//Asks Serial Monitor for coordinateto travel to
}

void loop() {

//wait until there is new data coming from the computer
while (Serial.available() > 0)
{
  //reads available value
  inputloc = Serial.readString();

  //if its more than 5 characters its a coordinate; convert input to int and travel there
  if (inputloc.length() > 5)
  {
    Serial.println(inputloc);
    xstring = inputloc.substring(0, 3);
    desiredx = xstring.toInt();
    zstring = inputloc.substring(4, 7);
    desiredz = zstring.toInt();
    xz.moveToMulti(desiredx, desiredz);
    String inputloc;
  }
  //if the input is between 2 and 4 characters it is a servo position; move servo there
  else if (inputloc.length() <= 4 && inputloc.length() >= 2)
  {
    Serial.print("Servo Pos: ");
    Serial.println(inputloc);
    desiredserv = inputloc.toInt();
    //gripper.write(desiredserv);
    String inputloc;
  }
}

}
