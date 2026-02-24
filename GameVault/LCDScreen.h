#ifndef LCDSCREEN_H
#define LCDSCREEN_H

#define LCDADDRESS 0x27
#define ROWCOUNT 2
#define COLUMNCOUNT 16

#include "WString.h"

LiquidCrystal_I2C lcd(LCDADDRESS, COLUMNCOUNT, ROWCOUNT);

void setupLCD() {
  lcd.init();
  lcd.backlight();
}

/*
Display the given txt at LCD screen
*/
void Display(char* text) {

  lcd.clear();
  lcd.setCursor(0, 0);

  int length = strlen(text);

  if (length > 16) {

    int divideIndex = 16;
    for (int i=0;i<16;i++) {
      
      if (i > 9 && text[i] == ' ') {
        divideIndex = i + 1;  
        break;
      } else {
        lcd.print(text[i]);
      }
      
    }
    lcd.setCursor(0, 1);
    lcd.print(&text[divideIndex]);

  } else {
    lcd.print(text);
  }

}

/*
Because of there is so much call of error message, this function
implemented for displaying message 0.5s and clear the screen.
*/
void displayGivenSec(char *txt = "Cannot Read Operation HALTED", int sec=500) {
  Display(txt);
  delay(sec);
  lcd.clear();  
}


#endif

