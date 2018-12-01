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
    updateDisplay();
  }
  /*Handle Increment and Decrement functionality based on mode selected*/
  switch(mode){
    case TEMPO_STATE:
      
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
