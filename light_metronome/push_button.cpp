#include "push_button.h"

PushButton::PushButton()
{    
}

void PushButton::init(int pin, unsigned long debounceDelay)
{
  _pin = pin;
  _debounceDelay = debounceDelay;
  pinMode(_pin, INPUT);
}

void PushButton::readPin()
{
  /*Check push button digital inputs and debounce*/
  _reading = digitalRead(_pin);

  /*Check if reading has changed due to button press or noise*/
  if (_reading != _prevReading) {
    _lastDebounceTime = millis();
  }
  /*Check reading again after debounce delay*/
  if ((millis() - _lastDebounceTime) > _debounceDelay) {
    /*If reading is different from the recorded state of the button, update state*/
    if (_reading != _state)
      _state = _reading;
  }

  /*Record edge detection before updating previous values*/
  _edgePos = (_state && !_prevState);
  _edgeNeg - (!_state && _prevState);

  /*Update prev reading variables for edge detection*/
  _prevState = _state;
  _prevReading = _reading;
}

bool PushButton::edgePos() const
{
  return _edgePos;
}

bool PushButton::edgeNeg() const
{
  return _edgeNeg;;
}

int PushButton::getState() const
{
  return _state;
}
