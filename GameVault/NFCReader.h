#ifndef NFCREADER_H
#define NFCREADER_H

#define sdaPin 10
#define resetPin A0

#include "config.h"
#include "LCDScreen.h"

MFRC522 reader(sdaPin, resetPin);
MFRC522::MIFARE_Key key;

// |-----|-----| Auxilary Functions |-----|-----|

/*
Setup function for rfid module
*/
void setupReader() {

  SPI.begin();
  reader.PCD_Init();
}
/*
Check for if there is card or the card's id can be readened by our rfid sensor,
if both true return true,
*/
bool readingFailed() {
  return (!reader.PICC_IsNewCardPresent() || !reader.PICC_ReadCardSerial());
}

// |-----|-----| Read Functions |-----|-----|
/*
If reading was not failed,
-> save the reader.uid.uidByte datatype into a string.
-> If the card is from our cardArray and the card's player not bankrupt, return the card.
*/
Player* readCard() {

  if (readingFailed()) return NULL;

  char input[18];

  for (byte i = 0, size = reader.uid.size; i < size; i++) {
    sprintf(&input[i * 2], "%02X", reader.uid.uidByte[i]);
  }

  for (int i=0; i<playerCount; i++) {

    if ( strcmp(input, players[i].cardID) == 0 && !checkBankrupted(&players[i]) ) {
      return &players[i];
    }
      

  }
  return NULL;
}

/*
Call the function for scanning the card.
This function wait for the scan for 3s, and then return the card.
If there is no card, return null obviously.
*/
Player* scan() {

  unsigned long initialTime = millis();
  Player *currentPlayer;

  do {
    currentPlayer = readCard();
  } while (!currentPlayer && millis() - initialTime<3000);
  return currentPlayer;
}
/*
Functionalize the process of scanning for money trades.
*/
Player* scanPayOperation(char *txt) {
  
  Display(txt);
  Player *player = scan();

  if (!player) {
    displayGivenSec();
    return NULL;
  }

  displayGivenSec("Scanned successfully.", 1000);
  return player;
}


#endif