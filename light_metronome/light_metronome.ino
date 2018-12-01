#include "light_metronome.h"
#include "push_button.h"
#include "metronome.h"
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
int brightnessPercent = 50;
int prevBrightnessPercent;
int brightnessVal;
int prevTempo;
int timeSignature = TIME_FOUR_FOUR;
bool metronomeEnabled;
unsigned long setTime;

/*Button Vars*/
PushButton pwrBtn;
PushButton modeBtn;
PushButton incrBtn;
PushButton decrBtn;
Metronome  metronome;

void updateDisplay();

void setup() {
  ledDisplay.begin(0x70);
  /*Setup PWM Outputs for RGB LED*/
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  /*Init button objects*/
  pwrBtn.init(PWR_BTN_PIN, DEBOUNCE_TIME, HOLD_TIME);
  modeBtn.init(MODE_BTN_PIN, DEBOUNCE_TIME, HOLD_TIME);
  incrBtn.init(INCR_BTN_PIN, DEBOUNCE_TIME, HOLD_TIME);
  decrBtn.init(DECR_BTN_PIN, DEBOUNCE_TIME, HOLD_TIME);

  metronome.init(tempo, timeSignature);
}

void loop() {
  
  pwrBtn.readPin();
  modeBtn.readPin();
  incrBtn.readPin();
  decrBtn.readPin();

  /*Update Metronome Enable on rising edge of button press*/
  if(pwrBtn.edgePos()){
    metronomeEnabled = !metronomeEnabled;
  }
  
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
      if(tempo != prevTempo){   
        updateDisplay();
        metronome.setTempo(tempo);
      }
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
      metronome.setTimeSignature(timeSignature);
      break;
      
     case BRIGHT_STATE:
      /*Increment by 1s to start then increment by 10 ever 200 ms if held*/
      if(incrBtn.edgePos())
        ++brightnessPercent;
      else if(incrBtn.held())
      {
        if(millis() % 200 == 0)
          brightnessPercent += 10;
      }
      else if(decrBtn.edgePos())
        --brightnessPercent;
      else if(decrBtn.held()){
        if(millis() % 200 == 0)
          brightnessPercent -= 10;
      }

      /*Limit tempo to min and max values*/
      if(brightnessPercent < MIN_BRIGHT_PERCENT)
          brightnessPercent = MIN_BRIGHT_PERCENT;
      if(brightnessPercent > MAX_BRIGHT_PERCENT)
          brightnessPercent = MAX_BRIGHT_PERCENT;

      /*Update display as needed*/
      if(brightnessPercent != prevBrightnessPercent){   
        updateDisplay();
      }
      break;
  }

  /*Run Metronome*/
  int action = metronome.runMetronome(metronomeEnabled);
  brightnessVal = MIN_BRIGHT_VAL + (MAX_BRIGHT_VAL - MIN_BRIGHT_VAL) * ((float)(brightnessPercent - MIN_BRIGHT_PERCENT)/(float)(MAX_BRIGHT_PERCENT - MIN_BRIGHT_PERCENT)); 
  switch (action)
  {
    case BEAT:
        setColor(0, 0, brightnessVal);
        setTime = millis();
      break;

    case MEASURE:
        setColor(brightnessVal,0,0);
        setTime = millis();
      break;
      
    default:
        if(millis() - setTime > BLINK_TIME)
          setColor(0,0,0);
      break;
  }
  
  prevTempo = tempo;
  prevBrightnessPercent = brightnessPercent;
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

       case BRIGHT_STATE:
        ledDisplay.println(brightnessPercent);
        ledDisplay.writeDigitRaw(0,P_BITMASK); 
        break;
    }
    ledDisplay.writeDisplay();   
}
