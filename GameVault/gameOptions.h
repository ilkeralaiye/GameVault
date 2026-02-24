#ifndef GAMEOPTIONS_H
#define GAMEOPTIONS_H

#include "Config.h"
#include "NFCReader.h"
#include "LCDScreen.h"
#include "inputKeypad.h"

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

  Display("Scan from who.");
  delay(500);
  Player *from = scan();

  if (!from) {
    errorScan();
  }

  Display("Scan to who.");
  delay(500);
  Player *to = scan();
  
  if (!to) {
    errorScan();
  }

  Display("Enter the money star is enter");
  int money = moneyInput();
  char moneyString[11];
  
  snprintf(moneyString, sizeof(moneyString), "Money:%d", money);

  Display(moneyString);
  delay(1500);
  lcd.clear();

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

#endif
