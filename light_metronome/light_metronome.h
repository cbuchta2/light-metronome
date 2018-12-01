#ifndef LIGHT_METRONOME_H_
#define LIGHT_METRONOME_H_

/*Constants*/
/*IO PIN Constants*/
#define PWR_BTN_PIN 7
#define MODE_BTN_PIN 8
#define DECR_BTN_PIN 12
#define INCR_BTN_PIN 13

/*Values*/
#define MAX_TEMPO 260
#define MIN_TEMPO 50
#define DEBOUNCE_TIME 50

/*Mode States*/
#define TEMPO_STATE 0
#define TIME_STATE 1
#define NUM_MODE_STATES 2

/*Time Signature Options*/
#define TIME_TWO_FOUR  0
#define TIME_THREE_FOUR 1
#define TIME_FOUR_FOUR 2
#define NUM_TIME_ELEM  3

#endif
