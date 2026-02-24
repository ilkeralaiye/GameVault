#ifndef CONFIG_H
#define CONFIG_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>

#include "LCDScreen.h"
#include "inputKeypad.h"

#define startingMoney 1500
#define firstCard "AAE96E06"
#define secondCard "25DB6F06"
#define thirdCard "CE6E5906"
#define fourthCard "C7065906"
#define playerCount 4

// Player class
typedef struct {

  int id;
  const char* cardID;
  int money;
  bool isBankruptcy;

} Player;

// Players array
Player players[playerCount];

/*
Create cardIDArray with card ID'S
create Player objects with those ID's
*/
void setupPlayers() {
  
  static char* cardIDArray[playerCount] = {firstCard, secondCard, thirdCard, fourthCard};

  for (int i=0;i<playerCount;i++) {

    players[i].id = i+1;
    players[i].cardID = cardIDArray[i];
    players[i].money = startingMoney;
    players[i].isBankruptcy = false;
  }

}

// | ----- | ----- | Auxialry Functions | ----- | ----- |

/*
Displays the "Enter the money tap star to enter" message at screen.
ask user for a money input.
displays the entered money at screen, clear the screen and return money.
*/
int enterMoney() {

  Display("Enter the money tap star to enter");
  
  int money = moneyInput();
  
  char moneyString[11];
  snprintf(moneyString, sizeof(moneyString), "Money:%d", money);

  Display(moneyString);
  delay(1500);
  lcd.clear();

  return money;

}

/*
Check for isBankruptcy that every player object has, if the player
bankrupted, print a message
*/
bool checkBankrupted(Player *player) {
  
  if (player->isBankruptcy) {
    displayGivenSec("The player is bankrupted!", 1000);
    return true;
  }
  return false;
}



#endif