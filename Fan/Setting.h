#include "Scene.h"
#include "Fan.h"
#include <LiquidCrystal_I2C.h>

#define SELECT 2 //pin for add button of duty cycle
#define CHANGE_VALUE 3//pin for subtract button of duty cycle



#ifndef SETTING_H // Check if MY_HEADER_H is not defined
#define SETTING_H // Define MY_HEADER_H

class Setting:public Scene
{
  private:
   int selectorValue=2;
   bool key_pressed=false;
   unsigned long time=0,current=0;
   int dutyValueToAdd=0;
   void select()
   {
     if(digitalRead(SELECT)==HIGH)
     {
       if(!this->key_pressed)
       {
         this->selectorValue++;
         this->key_pressed=true;
       }
    }
    else
    {
        this->key_pressed=false;
    }
     if(this->selectorValue>3) this->selectorValue=2;
   }

    void changeValue()
    {
       if(digitalRead(CHANGE_VALUE)==HIGH)
       {
          switch(this->selectorValue)
           {
             case 2:
                this->fan->setDutyValue(1);
                break;
             case 3:
                this->fan->setDutyValue(5);
                break;
             default:
                break;
           };
        
       }
     
    }
   public:
    void update()
    {
      this->select();
      this->changeValue();
    }
    void setup(Fan& fan)
    {
      this->fan=&fan;
    }
    void display(LiquidCrystal_I2C& lcd)
    {
      current=millis();
      if(this->current-this->time>200)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("------Settings------");
        lcd.setCursor(0,1);
        lcd.print("Duty:");
        lcd.setCursor(6,1);
        lcd.print(this->fan->getDutyValue());
        lcd.setCursor(0,2);
        lcd.print("1");
        lcd.setCursor(0,3);
        lcd.print("5");
        lcd.setCursor(4,this->selectorValue);
        lcd.print("<--");
        this->time=current;
      }
    }
};
#endif