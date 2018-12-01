#ifndef METRONOME_H_
#define METRONOME_H_

#include "light_metronome.h"
#include <Arduino.h>

#define BEAT 1
#define MEASURE 2
#define MS_PER_MIN 60000

class Metronome{
  public:
    Metronome();
    void init(int tempo, int timeSignature);
    void setTimeSignature(int timeSignature);
    void setTempo(int tempo);
    int runMetronome(bool enabled);
  
  private:
    unsigned int _count;
    unsigned long _lastAction;
    int _tempo;
    int _timeSignature;
    bool  _enabled;
};

#endif
