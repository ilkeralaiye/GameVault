#include "Config.h"
#include "NFCReader.h"
#include "LCDScreen.h"
#include "inputKeypad.h"

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
      Display("Scan your card.");
      int initialTime = millis();
      Player *currentPlayer;

      do {
        currentPlayer = readCard();
      } while (!currentPlayer && millis() - initialTime<3000);
      
      if (!currentPlayer) {
        Display("Cannot Read Operation HALTED");
      } else {

        char info[24]; 
        snprintf(info, sizeof(info), "Player No:%d Money:%d", currentPlayer->id, currentPlayer->money);

        Display(info);


        delay(2000);
        lcd.clear();
      }



    }
      

  }
}

