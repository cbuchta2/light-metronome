#include "metronome.h"

Metronome::Metronome()
{
}

void Metronome::init(int tempo, int timeSignature){
  _tempo = tempo;
  _timeSignature = timeSignature;
}

void Metronome::setTimeSignature(int timeSignature)
{
   _timeSignature = timeSignature;
}

void Metronome::setTempo(int tempo)
{
   _tempo = tempo;
}

int Metronome::runMetronome(bool enabled)
{
  _enabled = enabled;
  int measure;
  if(_enabled){
    switch(_timeSignature){
      case TIME_FOUR_FOUR:
        measure = 4;
        break;

      case TIME_THREE_FOUR:
        measure = 3;
        break;

      case TIME_TWO_FOUR:
        measure = 2;
      break; 
    }
    
    unsigned long timePerBeat = MS_PER_MIN / _tempo;

    if((millis() - _lastAction) > timePerBeat){
      _lastAction = millis();
      _count++;
      if(_count % measure == 0)
        return MEASURE;
      else
        return BEAT;
    }
    return 0;

    
  }
  else{
    _lastAction = 0;
    _count = 0;
    return 0;
  }
}
