#ifndef LIGHT_METRONOME_H_
#define LIGHT_METRONOME_H_

/*Constants*/
/*IO PIN Constants*/
#define PWR_BTN_PIN 7
#define MODE_BTN_PIN 8
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11
#define DECR_BTN_PIN 12
#define INCR_BTN_PIN 13

/*Values*/
#define MAX_TEMPO 260
#define MIN_TEMPO 50
#define MAX_BRIGHT_PERCENT 100
#define MIN_BRIGHT_PERCENT 1
#define MAX_BRIGHT_VAL 255
#define MIN_BRIGHT_VAL 1
#define DEBOUNCE_TIME 50
#define HOLD_TIME 200
#define BLINK_TIME 100
#define P_BITMASK 115

/*Mode States*/
#define TEMPO_STATE 0
#define TIME_STATE 1
#define BRIGHT_STATE 2
#define NUM_MODE_STATES 3

/*Time Signature Options*/
#define TIME_TWO_FOUR  0
#define TIME_THREE_FOUR 1
#define TIME_FOUR_FOUR 2
#define NUM_TIME_ELEM  3

#endif
