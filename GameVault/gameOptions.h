#ifndef GAMEOPTIONS_H
#define GAMEOPTIONS_H

#include "Config.h"
#include "NFCReader.h"
#include "LCDScreen.h"
#include "inputKeypad.h"

int enterMoney() {

  Display("Enter the money star is enter");
  int money = moneyInput();
  char moneyString[11];
  
  snprintf(moneyString, sizeof(moneyString), "Money:%d", money);

  Display(moneyString);
  delay(1500);
  lcd.clear();

  return money;

}

// void handleBankruptcy() {}

Player* scanPayOperation(char *txt) {
  
  Display(txt);
  Player *player = scan();

  if (!player) {
    errorScan();
    return NULL;
  }

  Display("Scanned successfully.");
  delay(1000);
  lcd.clear();
  return player;
}

/*
KEY PRESSED = '#'
Display's current player card info.
*/
void showInfo() {

  Display("Scan your card.");
  
  Player *currentPlayer = scan();
  
  if (!currentPlayer) {
    errorScan();
  } else {

    char info[24]; 
    snprintf(info, sizeof(info), "Player No:%d Money:%d", currentPlayer->id, currentPlayer->money);

    Display(info);

    delay(2000);
    lcd.clear();
  }

}

void pay() {

  Display("PAY: Scan after delay");
  Player *from = scanPayOperation("Scan FROM who");

  if (!from) {
    return;
  }

  Player *to = scanPayOperation("Scan TO who");
  
  if (!to) {
    return;
  }

  int money = enterMoney();

  if (from->money < money) {

    Display("Insufficient Money.");
    delay(600);
    Display("Enter mortgage money.");
    delay(1000);
    int mortgageMoney = moneyInput();

    from->money += mortgageMoney;    

    if (mortgageMoney < money) {
      char mortgageText[30];
      snprintf(mortgageText, sizeof(mortgageText), "Player %d went bankrupt", from->id);
      Display(mortgageText);
      delay(1000);
      from->isBankruptcy = true;
      to->money += from->money;
      from->money = 0;
    } else {
      to->money += money;

      from->money -= money;
    }

  } else {
    from->money -= money;
    to->money += money;
    Display("Payment succedd.");
    delay(1000);
      
  }
  lcd.clear();
  return;
}

void getCash() {
  
  int money = enterMoney();
  Player *to = scanPayOperation("Scan TO who");

  to->money += money;


}

void giveCash() {

  int money = enterMoney();
  Player *from = scanPayOperation("Scan who is paying");

  from->money -= money;

  if (from->money < 0) {

    Display("Insufficient Money.");
    delay(600);
    Display("Enter mortgage money.");
    int mortgageMoney = moneyInput();
    lcd.clear();


    from->money += mortgageMoney;    
    delay(200);

    char info[24]; 
    snprintf(info, sizeof(info), "Player No:%d Money:%d", from->id, from->money);

    Display(info);

    delay(2000);
    lcd.clear();

    if (from->money < 0) {

      char mortgageText[30];
      snprintf(mortgageText, sizeof(mortgageText), "Player %d went bankrupt", from->id);
      Display(mortgageText);
  

      from->isBankruptcy = true;
      from->money = 0;

    } else {
      Display("Payment succedd.");
    }

    delay(1000);  
    lcd.clear();
    
  }

}


#endif
