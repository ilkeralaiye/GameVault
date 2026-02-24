#ifndef GAMEOPTIONS_H
#define GAMEOPTIONS_H

#include "Config.h"
#include "NFCReader.h"
#include "LCDScreen.h"
#include "inputKeypad.h"

// void handleBankruptcy() {}

/*
KEY PRESSED = '#'
Display's current player card info.
*/
void showInfo() {

  Display("Scan your card.");
  
  Player *currentPlayer = scan();
  
  if (!currentPlayer) {
    displayGivenSec(); // base variable is 500 ms
  } else {

    char info[24]; 
    snprintf(info, sizeof(info), "Player No:%d Money:%d", currentPlayer->id, currentPlayer->money);

    displayGivenSec(info, 1500);
  }

}

/*
KEY PRESSED = 'A'
Trade money 
FROM the first card TO the second card.
*/
void pay() {

  displayGivenSec("PAY: Scan after delay", 500);

  Player *from = scanPayOperation("Scan FROM who");
  if (!from) return;

  Player *to = scanPayOperation("Scan TO who");
  if (!to) return;

  int money = enterMoney();

  if (from->money < money) {

    displayGivenSec("Insufficient Money.", 1000);
    displayGivenSec("Enter mortgage money.", 1000);
    int mortgageMoney = moneyInput();

    from->money += mortgageMoney;    

    if (mortgageMoney < money) {
      char mortgageText[30];
      snprintf(mortgageText, sizeof(mortgageText), "Player %d went bankrupt", from->id);
      displayGivenSec(mortgageText, 1000);
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
    displayGivenSec("payment    succeeded", 1000);      
  }
  return;
}

/*
KEY PRESSED = 'B'
Trade money 
FROM the vaut TO the scanned card.
*/
void getCash() {
  
  displayGivenSec("Get cash from vault.");
  int money = enterMoney();
  Player *to = scanPayOperation("Scan TO who");
  to->money += money;
}

/*
KEY PRESSED = 'C'
Trade money 
FROM the vaut TO the scanned card.
*/
void giveCash() {

  displayGivenSec("Pay cash to vault.");
  Player *from = scanPayOperation("Scan who is paying");
  int money = enterMoney();  

  from->money -= money;

  if (from->money < 0) {

    displayGivenSec("Insufficient Money.", 800);
    displayGivenSec("Enter mortgage money.", 1000);
    int mortgageMoney = moneyInput();

    from->money += mortgageMoney;    
    delay(200);

    char info[24]; 
    snprintf(info, sizeof(info), "Player No:%d Money:%d", from->id, from->money);

    displayGivenSec(info, 2000);

    if (from->money < 0) {

      from->isBankruptcy = true;
      from->money = 0;

      char mortgageText[30];      
      snprintf(mortgageText, sizeof(mortgageText), "Player %d went bankrupt", from->id);
      displayGivenSec(mortgageText, 1000);
      
    } else {
      displayGivenSec("payment    succeeded", 1000);
    }
    
  }

}


#endif
