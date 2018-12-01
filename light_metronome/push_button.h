#ifndef PUSH_BUTTON_H_
#define PUSH_BUTTON_H_

#include <Arduino.h>

class PushButton
{
  public:
    PushButton();
    void init(int pin, unsigned long debounceDelay);
    void readPin();
    int  getState() const;
    bool  edgePos() const;
    bool  edgeNeg() const;
    void setDebounceDelay(unsigned long debounceDelay);
    
  private:
    int _pin;
    int _reading;
    int _prevReading;
    int _state;
    int _prevState;
    bool _edgePos;
    bool _edgeNeg;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay; 
};

#endif
