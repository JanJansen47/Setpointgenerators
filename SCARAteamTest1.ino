/*
 SCARA Team
 Om een nieuwe hardware opstelling te controleren op werking van schakelaars, draairichting en enkele gymnastische oefeningen.
 versie 0.001  14-01-2015
 versie 0.1 21-01-2015 Harrie zijn suggesties voor een handiger test interface voor de homing switches en accelstepper ipv de home brew stepper.
 */

#include "Arduino.h"
#include "StepperObj.h"
#include "pins.h"
#include "AccelStepper.h"

// definitions for accelstepper
int lstep, laccel, ldecel , lspeed, numberrepeats;
char lax;
int StepX_min = 1, StepX_max = 1,StepY_min = 1, StepY_max = 1,StepZ_min = 1, StepZ_max = 1;

StepperObj::StepperObj(int ENABLE_PIN, int DIR_PIN, int STEP_PIN, int MIN_PIN, int MAX_PIN )

{
  _STEP_PIN  =  STEP_PIN;
  _DIR_PIN   =  DIR_PIN;
  _ENABLE_PIN = ENABLE_PIN;
  _MIN_PIN    = MIN_PIN;
  _MAX_PIN    = MAX_PIN;

  pinMode(_STEP_PIN, OUTPUT); 
  pinMode (_DIR_PIN, OUTPUT); 
  pinMode(_ENABLE_PIN, OUTPUT); 
  pinMode(_MIN_PIN, INPUT_PULLUP); 
  pinMode(_MAX_PIN, INPUT_PULLUP);
  digitalWrite(ENABLE_PIN, LOW);


}

void StepperObj::power_on()
{
  digitalWrite(_ENABLE_PIN, LOW);

}
void StepperObj::power_off()
{
  digitalWrite(_ENABLE_PIN, HIGH);
}
void StepperObj::direction(bool DIR)
{
  if (DIR) digitalWrite(_DIR_PIN, HIGH); 
  else digitalWrite(_DIR_PIN, LOW);
}
void StepperObj::step(int T)
{
  digitalWrite(_STEP_PIN, HIGH);
  delayMicroseconds(T);
  digitalWrite(_STEP_PIN, LOW);
  delayMicroseconds(T);  
}
bool StepperObj::readMin()
{
  return (digitalRead(_MIN_PIN));
}
bool StepperObj::readMax()
{
  return (digitalRead(_MAX_PIN));
}

//initiate class
StepperObj StepX(X_ENABLE_PIN, X_DIR_PIN, X_STEP_PIN, X_MIN_PIN, X_MAX_PIN);
StepperObj StepY(Y_ENABLE_PIN, Y_DIR_PIN, Y_STEP_PIN, Y_MIN_PIN, Y_MAX_PIN);
StepperObj StepZ(Z_ENABLE_PIN, Z_DIR_PIN, Z_STEP_PIN, Z_MIN_PIN, Z_MAX_PIN);
StepperObj StepE(E0_ENABLE_PIN, E0_DIR_PIN, E0_STEP_PIN, 200, 200); //dummy values for E0 min and max

// initiate accel classes
AccelStepper Theta   (AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper Psi     (AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper Z_axis  (AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper Extruder(AccelStepper::DRIVER, E0_STEP_PIN, E0_DIR_PIN);

void setup()
{
  Serial.begin(9600);
}

void loop()
{  
  Serial.println("=============================versie 0.1 21-01-2015 ===========");
  Serial.println("Menu:");
  Serial.println("Test Homing Switches                  => s");
  Serial.println("Allocation check for all axis         => a");
  Serial.println("Rotation direction check for all axis => r");
  Serial.println("Constant speed profiles               => e");
  Serial.println("Velocity profiles                     => l");
  Serial.println("===============================================================");
  Serial.println("Make your choice");
  Serial.println();
  while(Serial.available()==0);

  int incomingByte = Serial.read();

  switch (incomingByte) {
  case 's':    
    Serial.println("============================================================");
    Serial.println(" Open en closed switches at the start");
    Serial.print("(Theta ) X-MIN=>>  "); 
    if(StepX.readMin()) Serial.print("Open contact   "); 
    else Serial.print("Closed contact"); 
    Serial.print(" X-MAX=>>  ");
    if(StepX.readMax()) Serial.println("Open contact"); 
    else Serial.println("Closed contact");
    Serial.print("(Psi   ) Y-MIN=>>  "); 
    if(StepY.readMin()) Serial.print("Open contact   "); 
    else Serial.print("Closed contact"); 
    Serial.print(" Y-MAX=>>  ");
    if(StepY.readMax()) Serial.println("Open contact"); 
    else Serial.println("Closed contact");
    Serial.print("(Z-axis) Z-MIN=>>  "); 
    if(StepZ.readMin()) Serial.print("Open contact   "); 
    else Serial.print("Closed contact"); 
    Serial.print(" Z-MAX=>>  ");
    if(StepZ.readMax()) Serial.println("Open contact"); 
    else Serial.println("Closed contact");
    Serial.println("============================================================");
    Serial.println();
    Serial.println("============================================================");
    Serial.println("Activate switch and check the result here");
    Serial.println("We use X-MAX (psi) , Y-MAX (theta) and Z_MAX (Z)   ");
    Serial.println("they MUST close at activation  !!  ");
    Serial.println("Hit  space  and return on serial monitor to leave this test    ");
    Serial.println("============================================================");

    while(true) {
      if (StepX.readMax() != StepX_max || StepX.readMin() != StepX_min ||
        StepY.readMax() != StepY_max || StepY.readMin() != StepY_min || 
        StepZ.readMax() != StepZ_max || StepZ.readMin() != StepZ_min )


      {
        Serial.println("============================================================");        
        Serial.println(" Open en closed switches during test ");
         Serial.print("(Theta ) X-MIN=>>  "); 
    if(StepX.readMin()) Serial.print("Open contact   "); 
    else Serial.print("Closed contact"); 
    Serial.print(" X-MAX=>>  ");
    if(StepX.readMax()) Serial.println("Open contact"); 
    else Serial.println("Closed contact");
    Serial.print("(Psi   ) Y-MIN=>>  "); 
    if(StepY.readMin()) Serial.print("Open contact   "); 
    else Serial.print("Closed contact"); 
    Serial.print(" Y-MAX=>>  ");
    if(StepY.readMax()) Serial.println("Open contact"); 
    else Serial.println("Closed contact");
    Serial.print("(Z-axis) Z-MIN=>>  "); 
    if(StepZ.readMin()) Serial.print("Open contact   "); 
    else Serial.print("Closed contact"); 
    Serial.print(" Z-MAX=>>  ");
    if(StepZ.readMax()) Serial.println("Open contact"); 
    else Serial.println("Closed contact");
        //wait for a change!
        StepX_min = StepX.readMin(); 
        StepX_max = StepX.readMax();
        StepY_min = StepY.readMin(); 
        StepY_max = StepY.readMax();
        StepZ_min = StepZ.readMin(); 
        StepZ_max = StepZ.readMax();
        Serial.println("============================================================");
      };

      if(Serial.available()!=0){
        Serial.read();
        break;
      }
    }


    break;
  case 'a':
    Serial.println("============================================================");
    Serial.println("Check if the motor is connected to the desired axis");
    Serial.println("Steppers are activated one after each other to check correct");
    Serial.println("wiring. First Psi is activated for 10 seconds. Feel the ");
    Serial.println("spindel and check whether you can turn it"); 
    Serial.println("Thereafter Theta, Z-axis and extruder are activated");
    Serial.println("============================================================");
    Serial.println();
    // all steppers off
    StepX.power_off();
    StepY.power_off();
    StepZ.power_off();
    StepE.power_off();
    Serial.println("Theta axis power IS NOW on for 10 seconds"); 
    StepX.power_on();
    delay(10000);
    StepX.power_off();
    Serial.println("Psi axis power IS NOW  on for 10 seconds"); 
    StepY.power_on();
    delay(10000);
    StepY.power_off();
    Serial.println("Z axis power IS NOW  on for 10 seconds"); 
    StepZ.power_on();
    delay(10000);
    StepZ.power_off();
    Serial.println("E0 axis power IS NOW  on for 10 seconds"); 
    StepE.power_on();
    delay(10000);
    StepE.power_off();
    break;
  case 'r':
    Serial.println("====================================================================================");
    Serial.println(" You need to check the movement direction of the axis" );
    Serial.println("The Psi axis will turn '1000 steps' in CW (direction ZERO degrees) in 5 seconds");
    Serial.println("====================================================================================");
    Serial.println();
    delay(5000); 
    StepX.power_on();
    StepX.direction (true);
    for (int i=0; i<1000;) {
      StepX.step(300);
      i++;
    }
    Serial.println("The Theta axis will turn 'by 1000 steps' in CCW (direction 90 degrees) in 5 seconds");
    delay(5000);
    StepX.direction (false);
    for (int i=0; i<1000;) {
      StepX.step(300);
      i++;
    }  
    Serial.println("The Theta axis will turn 'by 1000 steps' in CW (direction ZERO degrees) in 5 seconds");
    delay(5000); 
    StepY.power_on();
    StepY.direction (false);
    for (int i=0; i<1000;) {
      StepY.step(300);
      i++;
    }
    Serial.println("The Psi axis    will turn 'by 1000 steps' in CCW (direction 90 degrees) in 5 seconds");
    delay(5000); 
    StepY.direction (true);
    for (int i=0; i<1000;) {
      StepY.step(300);
      i++;
    }  
    Serial.println("The Z axis                                 will turn 'by 1000 steps' up in 5 seconds");
    delay(5000); 
    StepZ.power_on();
    StepZ.direction (true);
    for (int i=0; i<1000;) {
      StepZ.step(300);
      i++;
    }
    Serial.println("The Z axis                               will turn 'by 1000 steps' down in 5 seconds");
    delay(5000); 
    StepZ.direction (false);
    for (int i=0; i<1000;) {
      StepZ.step(300);
      i++;
    }  
    Serial.println("The E0 axis                             will turn 'in'  'by 1000 steps'  in 5 seconds");
    delay(5000); 
    StepE.power_on();
    StepE.direction (true);
    for (int i=0; i<1000;) {
      StepE.step(300);
      i++;
    }
    Serial.println("The E0 axis                              will turn 'out' 'by 1000 steps' in 5 seconds");
    delay(5000);
    StepE.direction (false);
    for (int i=0; i<1000;) {
      StepE.step(300);
      i++;
    }    
    // Switch power off the steppers 
    StepX.power_off();
    StepY.power_off();
    StepZ.power_off();
    StepE.power_off();
    break;
  case 'l':
    Serial.println("====================================================================================");
    Serial.println("This test is to accelarate and decelerate one of your axis at a time" );
    Serial.println("The test is using the modified LeibRamp 'Accelstepper'");
    Serial.println("the max speed is ~ 20k steps/second");
    Serial.println("====================================================================================");
    Serial.println();

    // read steps/sec
    Serial.println("AccelStepper"); 
    Serial.print("input axis (p, t, z, e0) to move       >> ");
    while(Serial.available()==0);
    lax = Serial.read();
    //lax = Serial.parseInt();
    Serial.println(lax);
    Serial.print("input the number of steps              >> ");
    while(Serial.available()==0);
    lstep = Serial.parseInt();
    Serial.println(lstep);
    Serial.print("input the speed in step/sec            >> ");
    while(Serial.available()==0);
    lspeed = Serial.parseInt();
    Serial.println(lspeed);
    Serial.print("input the acceleration steps/secsec    >> ");
    while(Serial.available()==0);
    laccel = ldecel = Serial.parseInt();
    Serial.println(laccel);
    // read number of sequences
    Serial.print("input the number of repeats            >> ");
    while(Serial.available()==0);
    numberrepeats = Serial.parseInt();
    Serial.println(numberrepeats);


    switch (lax)  {  
    case'p':
      Psi.setMaxSpeed(lspeed);
      Psi.setAcceleration(laccel);
      for (int i=0; i< numberrepeats;) {
        Psi.runToNewPosition(lstep);
        Psi.runToNewPosition(-lstep);
        i++;
      }
      break;   
    case't':
      Theta.setMaxSpeed(lspeed);
      Theta.setAcceleration(laccel);
      for (int i=0; i< numberrepeats;) {
        Theta.runToNewPosition(lstep);
        Theta.runToNewPosition(-lstep);
        i++;
      }
      break;   
    case'z':
      Z_axis.setMaxSpeed(lspeed);
      Z_axis.setAcceleration(laccel);
      for (int i=0; i< numberrepeats;) {
        Z_axis.runToNewPosition(lstep);
        Z_axis.runToNewPosition(-lstep);
        i++;
      }
      break;   
    case'e0':
      Extruder.setMaxSpeed(lspeed);
      Extruder.setAcceleration(laccel);
      for (int i=0; i< numberrepeats;) {
        Extruder.runToNewPosition(lstep);
        Extruder.runToNewPosition(-lstep);
        i++;
      }
      break;  
    }

    break;

  case 'e':     
    Serial.println("====================================================================================");
    Serial.println("Constant speed tests" );
    Serial.println("Do  scara constant speed movement tests; position scara in the centre of the bed"); 
    Serial.println("close to the 'Main' axis. First movement is away from the 'Main' axis");
    Serial.println("start with 500 steps to get an idea");
    Serial.println("Warning =>> steps/sec must NOT exceed 32000");
    Serial.println("====================================================================================");
    Serial.println();
    Serial.print("input the steps/sec >>  ");
    int x;
    int T;
    String str;
    // read steps/sec
    while(Serial.available()==0);

    x = Serial.parseInt();
    T = (1000000/x)/4; //time in microseconds
    Serial.println(x);

    // read number of sequences
    Serial.print("input the number of repeats >>  ");
    while(Serial.available()==0);
    x = Serial.parseInt();
    Serial.println(x);
    //Serial.print("Number of repeats =  ");
    //Serial.println( x);
    delay(2000);
    StepX.power_on();
    StepY.power_on();
    for(int j=0; j <x;) {  
      delay(100);
      StepX.direction (false);
      StepY.direction (false);
      for (int i=0; i<1000;) {
        StepX.step(T);
        StepY.step(T); 
        i++;
      }
      delay(100);
      StepX.direction(true);
      StepY.direction (true);
      for (int i=0; i<1000;) {
        StepX.step(T);
        StepY.step(T); 
        i++;
      }
      j++;
    }
    break;

    delay(2000);
    StepX.power_off();
    StepY.power_off();


  }

}










