#ifndef NFCREADER_H
#define NFCREADER_H

#define sdaPin 10
#define resetPin A0

#include "config.h"

MFRC522 reader(sdaPin, resetPin);
MFRC522::MIFARE_Key key;

void setupReader() {

  SPI.begin();
  reader.PCD_Init();
}

bool readingFailed() {

  return (!reader.PICC_IsNewCardPresent() || !reader.PICC_ReadCardSerial());

}

Player* readCard() {

  if (readingFailed()) {
    return NULL;
  }

  char input[18];
  int size = reader.uid.size;

  for (byte i = 0; i < size; i++) {
    sprintf(&input[i * 2], "%02X", reader.uid.uidByte[i]);
  }

  for (int i=0; i<4; i++) {

    if (strcmp(input, players[i].cardID) == 0) {

      reader.PICC_HaltA();
      reader.PCD_StopCrypto1();
      return &players[i];

    }

  }

  reader.PICC_HaltA();
  reader.PCD_StopCrypto1();
  return NULL;

}




#endif