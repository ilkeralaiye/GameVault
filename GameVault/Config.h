#ifndef CONFIG_H
#define CONFIG_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>

#define sdaPin 10
#define resetPin A0

typedef struct {

  int id;
  const char* cardID;
  int money;
  bool isBankruptcy;

} Player;


#endif