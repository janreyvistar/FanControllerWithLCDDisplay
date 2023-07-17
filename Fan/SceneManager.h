#include <LiquidCrystal_I2C.h>
#include "Scene.h"
#include "Main.h"
#include "Setting.h"
#include "Fan.h"
#define ADD_PIN 2 //pin for add button of duty cycle
#define SUB_PIN 3//pin for subtract button of duty cycle
#define SETTING 4 //pin for a setting

#define TACH_PIN 12 // pin tach
#define PWM_PIN 11// pin for pwm controller

#define NEW_SCENE_PIN 4

#define DEFAULT_DUTY_CYCLE 100

#define I2C_ADDRESS 0x27
#define COLUMNS 20
#define ROWS  4


#ifndef SCENE_MANAGER_H // Check if MY_HEADER_H is not defined
#define SCENE_MANAGER_H // Define MY_HEADER_H

enum State
{
  MAINS,
  SETTINGS,
  NONE
};
class SceneManager
{
  private:
  bool keypressed=false;
  LiquidCrystal_I2C* lcd;
  Scene* scene;
  Fan* fan;
  State state;
  public:
    void setScene()
    {
      switch(state)
      {
      case MAINS:
          delete this->scene;
          this->scene=new Main();
          this->scene->setup(*this->fan);
          break;
      case SETTINGS:
          delete this->scene;
          this->scene=new Setting();
          this->scene->setup(*this->fan);
      break;
          default:
          break;
        };
    }
    void goToNextScene()
    {
      if(digitalRead(NEW_SCENE_PIN)==1)
      {
        if(!this->keypressed)
        {
          switch(state)
          {
            case MAINS:
              state=SETTINGS;
              break;
            case SETTINGS:
              state=MAINS;
              break;
            default:
              break;
          };
          this->keypressed=true;
          this->setScene();
        }
      }
      else
      {
        keypressed=false;
      }
    }
    void setup()
    {
      this->state=MAINS;
      this->lcd=new LiquidCrystal_I2C(I2C_ADDRESS, COLUMNS, ROWS); // I2C address 0x27, 20 column and 4 rows
      this->lcd->init(); // initialize the lcd
      this->lcd->backlight();//initialized lcd backlight
      this->scene=new Main();
      this->fan=new Fan(ADD_PIN,SUB_PIN,PWM_PIN,TACH_PIN);
      this->fan->setup();
      this->fan->setDutyValue(1);
      this->fan->setDuty(DEFAULT_DUTY_CYCLE);
      this->scene->setup(*this->fan);
      pinMode(NEW_SCENE_PIN,INPUT);

    }
    void display()
    {
      this->scene->display(*this->lcd);
    }
    void update()
    {
      this->goToNextScene();
      this->scene->update();
    }
 
};
#endif