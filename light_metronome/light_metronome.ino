#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_LEDBackpack.h>

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

/*Struct definition*/
/* button_typ
 *  Struct containing all variables need for edge detection 
 *  and deboucing of a press button input
 */
typedef struct button_typ
{
  int reading;
  int prevReading;
  unsigned long lastDebounceTime;
  int state;
  int prevState; 
} button_typ;

/***Variables***/
Adafruit_7segment ledDisplay = Adafruit_7segment();
int mode = 0;
int tempo = 120;

/*Button Vars*/
button_typ pwrBtn;
button_typ modeBtn;
button_typ incrBtn;
button_typ decrBtn;

void setup() {
  ledDisplay.begin(0x70);
  pinMode(MODE_BTN_PIN, INPUT);
  pinMode(DECR_BTN_PIN, INPUT);
  pinMode(INCR_BTN_PIN, INPUT);
}

void loop() {
  /*Check push button digital inputs and debounce*/
  modeBtn.reading = digitalRead(MODE_BTN_PIN);

  /*Check if reading has changed due to button press or noise*/
  if (modeBtn.reading != modeBtn.prevReading) {
    modeBtn.lastDebounceTime = millis();
  }
  /*Check reading again after debounce delay*/
  if ((millis() - modeBtn.lastDebounceTime) > DEBOUNCE_TIME) {
    /*If reading is different from the recorded state of the button, update state*/
    if (modeBtn.reading != modeBtn.state)
      modeBtn.state = modeBtn.reading;
  }

  /*Update selected mode on rising edge of (debounced) button press*/
  if(modeBtn.state && !modeBtn.prevState){
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

  
  
  
  /*Update prev reading variables for edge detection*/
  modeBtn.prevState = modeBtn.state;
  modeBtn.prevReading = modeBtn.reading;
}
