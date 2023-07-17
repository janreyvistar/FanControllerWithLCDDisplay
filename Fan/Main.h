#include "Scene.h"
#include <LiquidCrystal_I2C.h>
#include "Fan.h"

#ifndef MAIN_H // Check if MY_HEADER_H is not defined
#define MAIN_H // Define MY_HEADER_H
class Main: public Scene
{
  private:
    unsigned long time=0,current=0;
    int numberOfReading;
    int rpmAdd;
    
  public:
    void update()
    {

      fan->addDuty();
      fan->subDuty();
      fan->update();
      this->current=millis();
    }
    void setup(Fan& fan)
    {
      this->fan=&fan;
 
    }
    void display(LiquidCrystal_I2C& lcd)
    {

    if(this->current-this->time>500)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Duty: ");
        lcd.setCursor(6, 0);
        lcd.print(this->fan->getDuty());
        lcd.setCursor(0, 1);
        lcd.print("RPM: ");
        lcd.setCursor(6, 1);
        lcd.print(this->fan->getRPM());  
        this->time=this->current;
      }
    }
};
#endif