#ifndef CONFIG_H
#define CONFIG_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>

#define startingMoney 1500

typedef struct {

  int id;
  const char* cardID;
  int money;
  bool isBankruptcy;

} Player;

Player players[4];

void setupPlayers() {
  
  static char* cardIDArray[4] = {"AAE96E06", "25DB6F06", "CE6E5906", "C7065906"};

  for (int i=0;i<4;i++) {

    players[i].id = i+1;
    players[i].cardID = cardIDArray[i];
    players[i].money = startingMoney;
    players[i].isBankruptcy = false;
  }

}



#endif