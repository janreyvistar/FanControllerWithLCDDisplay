#include <LiquidCrystal_I2C.h>
#include "Fan.h"
#ifndef SCENE_H // Check if MY_HEADER_H is not defined
#define SCENE_H // Define MY_HEADER_H
class Scene{
  protected:
    Fan* fan;
  public:
    virtual void update()=0;
    virtual void setup(Fan& fan)=0;
    virtual void display(LiquidCrystal_I2C& lcd)=0;

};
#endif