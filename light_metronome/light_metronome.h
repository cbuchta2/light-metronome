#ifndef LIGHT_METRONOME_H_
#define LIGHT_METRONOME_H_

/*Constants*/
#define PWR_BTN_PIN 7
#define MODE_BTN_PIN 8
#define DECR_BTN_PIN 12
#define INCR_BTN_PIN 13

#define MAX_TEMPO 300
#define MIN_TEMPO 60
#define NUM_MODE_STATES 2

#define TEMPO_STATE 0
#define TIME_STATE 1
#define DEBOUNCE_TIME 50

/***Enuum***/
enum timeSignatureEnum{
  timeFOUR_FOUR,
  timeTHREE_FOUR,
  timeTWO_FOUR,
  timeNUM_ELEM
};

#endif
