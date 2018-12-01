#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_LEDBackpack.h>
#include "push_button.h"

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

/***Variables***/
Adafruit_7segment ledDisplay = Adafruit_7segment();
int mode = 0;
int tempo = 120;

/*Button Vars*/
PushButton pwrBtn;
PushButton modeBtn;
PushButton incrBtn;
PushButton decrBtn;


void setup() {
  ledDisplay.begin(0x70);
  /*Init button objects*/
  pwrBtn.init(PWR_BTN_PIN, DEBOUNCE_TIME);
  modeBtn.init(MODE_BTN_PIN, DEBOUNCE_TIME);
  incrBtn.init(DECR_BTN_PIN, DEBOUNCE_TIME);
  decrBtn.init(INCR_BTN_PIN, DEBOUNCE_TIME);
}

void loop() {

  pwrBtn.readPin();
  modeBtn.readPin();
  incrBtn.readPin();
  decrBtn.readPin();
  
  /*Update selected mode on rising edge of (debounced) button press*/
  if(modeBtn.edgePos()){
    mode = (++mode) % NUM_MODE_STATES;
    
    /*Clear display and update with mode or tempo display values*/
    ledDisplay.clear();
    ledDisplay.writeDisplay();
    
    switch(mode){
      case TEMPO_STATE:
        ledDisplay.println(tempo);      
        break;

      case TIME_STATE:
        ledDisplay.writeDigitNum(1, 4);
        ledDisplay.drawColon(true);
        ledDisplay.writeDigitNum(3, 4);
        break;
    }
    ledDisplay.writeDisplay();  
  }
}
