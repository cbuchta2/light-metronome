#include "light_metronome.h"
#include "push_button.h"
#include "helper_functions.h"
#include <gfxfont.h>
#include <stdint.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_LEDBackpack.h>

/***Variables***/
Adafruit_7segment ledDisplay = Adafruit_7segment();
int mode = 0;
int tempo = 120;
int prevTempo;
int timeSignature;

/*Button Vars*/
PushButton pwrBtn;
PushButton modeBtn;
PushButton incrBtn;
PushButton decrBtn;

void updateDisplay();

void setup() {
  ledDisplay.begin(0x70);
  /*Init button objects*/
  pwrBtn.init(PWR_BTN_PIN, DEBOUNCE_TIME, HOLD_TIME);
  modeBtn.init(MODE_BTN_PIN, DEBOUNCE_TIME, HOLD_TIME);
  incrBtn.init(INCR_BTN_PIN, DEBOUNCE_TIME, HOLD_TIME);
  decrBtn.init(DECR_BTN_PIN, DEBOUNCE_TIME, HOLD_TIME);
}

void loop() {
  
  pwrBtn.readPin();
  modeBtn.readPin();
  incrBtn.readPin();
  decrBtn.readPin();
  
  /*Update selected mode on rising edge of (debounced) button press*/
  if(modeBtn.edgePos()){
    mode = (++mode) % NUM_MODE_STATES; 
    updateDisplay();
  }
  /*Handle Increment and Decrement functionality based on mode selected*/
  switch(mode){
    case TEMPO_STATE:
      /*Increment by 1s to start then increment by 10 ever 200 ms if held*/
      if(incrBtn.edgePos())
        ++tempo;
      else if(incrBtn.held())
      {
        if(millis() % 200 == 0)
          tempo += 10;
      }
      else if(decrBtn.edgePos())
        --tempo;
      else if(decrBtn.held()){
        if(millis() % 200 == 0)
          tempo -= 10;
      }

      /*Limit tempo to min and max values*/
      if(tempo < MIN_TEMPO)
          tempo = MIN_TEMPO;
      if(tempo > MAX_TEMPO)
          tempo = MAX_TEMPO;

      /*Update display as needed*/
      if(tempo != prevTempo)   
        updateDisplay();

      break;

     case TIME_STATE:
      if(incrBtn.edgePos()){
        timeSignature = (++timeSignature) % NUM_TIME_ELEM;
        updateDisplay();
      }
      if(decrBtn.edgePos()){
        timeSignature = (--timeSignature + NUM_TIME_ELEM) % NUM_TIME_ELEM;
        updateDisplay();
      }
      break;
  }
  prevTempo = tempo;
}

void updateDisplay(){
/*Clear display and update with mode or tempo display values*/
    ledDisplay.clear();
    ledDisplay.writeDisplay();
    
    switch(mode){
      case TEMPO_STATE:
        ledDisplay.println(tempo);      
        break;

      case TIME_STATE:
        ledDisplay.writeDigitNum(1, setTimeSignatureUpper(timeSignature));
        ledDisplay.drawColon(true);
        ledDisplay.writeDigitNum(3, setTimeSignatureLower(timeSignature));
        break;
    }
    ledDisplay.writeDisplay();   
}
