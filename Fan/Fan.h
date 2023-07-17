#ifndef FAN_H // Check if FAN_H is not defined
#define FAN_H // Define FAN_H
class Fan
{
  private:
    long m_time=0;
    double m_toggle1=false;
    double m_toggle2=false;
    byte m_AddPin,m_SubPin,m_PWMPin,m_tachPin;
    double m_Duty;
    byte m_DutyValue=0;
    unsigned long m_rpm;
    double m_frequency;
    double m_period;
    //setting the register to 25khz
    void setTo25K()
    {
      TCCR1A=0;
      TCCR1B=0;
      TCNT1=0;
      TCCR1A = _BV (COM1A1) // non-inverted PWM on ch. A
          | _BV (COM1B1) // same on ch. B
          | _BV (WGM11); // mode 14: fast PWM, TOP = ICR1
      TCCR1B = _BV (WGM13) // ditto
          | _BV (WGM12) // ditto
          | _BV (CS10); // prescaler = 1
      ICR1 = 640; // TOP = 640
    // OCR1A = OCR2B =320; // duty cycle = ~50%
      pinMode(this->m_PWMPin,OUTPUT);
    }

    void calculateRPM()
    {
      this->m_period = pulseIn (this->m_tachPin, HIGH);
      int frequency = 1000000.0 /(2*this->m_period);
      this->m_rpm=(frequency/2)*60;
    }
    void updateDuty()
    {
      int val=(this->m_Duty*640)/100;
      analogWrite(this->m_PWMPin,val);
    }
  public:
    Fan(byte addPin,byte subPin,byte pWMPin,byte tachPin)
    {
      this->m_AddPin=addPin;
      this->m_SubPin=subPin;
      this->m_PWMPin=pWMPin;
      this->m_Duty=0;
      this->m_tachPin=tachPin;
      this->m_time=micros();
    }
    double getDuty()const {return this->m_Duty;}
    double getDutyValue()const {return this->m_DutyValue;}
    
   // void readTach();
    double getRPM()const{return this->m_rpm;};
    void setDutyValue(int value)
    {
      this->m_DutyValue=value;
      if(this->m_DutyValue>10)
      {
        this->m_DutyValue=10;
      }
      else if(this->m_DutyValue<0)
      {
        this->m_DutyValue=0;
      }
    }
    void addDuty()
    {
      if(digitalRead(this->m_AddPin)==1)
      {
          if(!this->m_toggle1)
            {
              this->m_Duty+=this->m_DutyValue;
              this->m_toggle1=true;
            }
      }
      else{
        this->m_toggle1=false;
      }
      if(this->m_Duty>100) this->m_Duty=100;
    }
    void subDuty()
    {
      if(digitalRead(this->m_SubPin)==1)
      {
        if(!this->m_toggle2)
          {
            this->m_Duty-=this->m_DutyValue;
            this->m_toggle2=true;
          }
       
      }
      else
      {
       this->m_toggle2=false;
      }
    if(this->m_Duty<0) this->m_Duty=0;
    }
    void setDuty(int value)
    {
      this->m_Duty=value;
    }
    void update()
    {
      this->calculateRPM();
      this->updateDuty();
    }
    void setup()
    {
      pinMode(this->m_AddPin,INPUT);
      pinMode(this->m_SubPin,INPUT);
      pinMode(this->m_tachPin,INPUT);
      this->setTo25K();
    }
};

#endif