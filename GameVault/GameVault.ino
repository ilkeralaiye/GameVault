#include "Config.h"
#include "NFCReader.h"
#include "LCDScreen.h"
#include "inputKeypad.h"
#include "gameOptions.h"

void setup() {
  // put your setup code here, to run once:
  setupLCD();
  setupPlayers();
  setupReader();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  char key = keypad.getKey();

  switch (key) {

    case NO_KEY:
      break;
    case '#': {
      showInfo();
      break;
    }
    case 'A':
      pay();
    
  }
      
}

