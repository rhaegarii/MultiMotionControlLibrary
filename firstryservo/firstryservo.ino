
static double pos = 1.00;
static double loc = 1.00;
char inputnum;
String inputString = "";
boolean firstLoop = true;
boolean numGot = false;
static int desiredloc = 100;
int pitch = 8; //8mm per rotation
int steplength = 200; //200 steps per rotation
const int enasmall = 5; //Pin for ENA signal (small stepper)
const int dirsmall = 6; //pin for DIR signal (small stepper)
const int pulsmall = 7; //pin for PUL signal (small stepper)
const int enabig = 9; //pin for ENA signal (large stepper)
const int dirbig = 8; //pin for DIR signal (large stepper)
const int pulbig = 10; //pin for PUL signal (large stepper)
const int button = 2; //pin for on/off bump switch
const int upperlim = 3; //pin for upper limit switch
const int lowerlim = 4; //pin for lower limit switch
const int interval = 500; //Default interval between steps (inverse relation to speed)
boolean smallpulse = LOW; //starting value for small motor pulse 
boolean bigpulse = LOW; //starting value for large motor pulse

void setup() {

  //sets the pin modes for each of the small motor pins then sets the value 
  pinMode(enasmall, OUTPUT);
  pinMode(dirsmall, OUTPUT);
  pinMode(pulsmall, OUTPUT);
  digitalWrite(enasmall, LOW);
  digitalWrite(dirsmall, LOW); //change to change direction of movement
  digitalWrite(pulsmall, HIGH);

  //Sets pin modes for each large motor pins then sets the value
  pinMode(enabig, OUTPUT);
  pinMode(dirbig, OUTPUT);
  pinMode(pulbig, OUTPUT);
  digitalWrite(enabig, LOW);
  digitalWrite(dirbig, LOW);
  digitalWrite(pulbig, HIGH);

  //Sets pin mode for each limit switch
  pinMode(button, INPUT);
  pinMode(lowerlim, INPUT);
  pinMode(upperlim, INPUT);

  //sets Baud rate and initiates output
  Serial.begin(1000000);

  //Returns the z back to lowest point then sets the position value to zero
  zzero(lowerlim, pulsmall, smallpulse, dirsmall, interval);
  Serial.println("done");
  pos = 0;
  digitalWrite(dirsmall, HIGH);


}

void loop() {
  if (numGot == false){
    if (firstLoop == true)
      Serial.print("Enter Desired Location in mm: ");
      firstLoop = false;
    if (Serial.available()){
      inputString = Serial.readString();
      desiredloc = inputString.toInt();
      Serial.print(desiredloc);
      if (desiredloc >= 0 && desiredloc <= 350)
        numGot = true;
      else
        firstLoop = true;
    }

  }
  else if (digitalRead(button) == LOW &&
      digitalRead(upperlim) == LOW && loc <= desiredloc){
        smallpulse = ssf(pulsmall, smallpulse, interval);
        pos+=0.5;
        loc = pos*pitch/steplength;
        //Serial.println(loc);
        
  }  
  //delayMicroseconds(interval);
}


void zzero(int lowerlim, int pul, boolean pulse, int dir, int interval) {
  Serial.print("Starting zero...");
  digitalWrite(dir, LOW);
  while (digitalRead(lowerlim) == LOW){
    pulse = ssf(pul, pulse, interval);
    //Serial.print(digitalRead(lowerlim));
  }
  digitalWrite(dir, HIGH);
  Serial.print("Standing off");
  while (digitalRead(lowerlim) == HIGH) {
    pulse = ssf(pul, pulse, interval);
    //delayMicroseconds(20);
  }
  
 
}


boolean ssf(int pul, boolean pulse, int interval) 
{
  //digitalWrite(dir, HIGH);
  pulse = !pulse;
  digitalWrite(pul, pulse);
  delayMicroseconds(interval);
  return pulse;
}

/*boolean ssb(int pul, boolean pulse, int interval) {
 // Serial.print("ssb \n");
  //digitalWrite(dir, LOW);
  pulse = !pulse;
  digitalWrite(pul, pulse);
  delayMicroseconds(interval);
  return pulse;
}*/
