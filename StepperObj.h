/*
  Jansen
 */
#ifndef StepperObj_h
#define StepperObj_h

#include "Arduino.h"

class StepperObj
{
public:
  StepperObj(int _ENABLE_PIN, int _DIR_PIN, int _STEP_PIN, int _MIN_PIN,  int _MAX_PIN);

  void power_on();
  void power_off();
  void step(int);
  void direction(bool);
  bool readMin();
  bool readMax();
private:
  int _STEP_PIN;
  int _DIR_PIN;
  int _ENABLE_PIN;
  int _MIN_PIN;
  int _MAX_PIN;
};

#endif



