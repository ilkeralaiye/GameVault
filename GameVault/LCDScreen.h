#include "WString.h"
#ifndef LCDSCREEN_H
#define LCDSCREEN_H

#define LCDADDRESS 0x27
#define ROWCOUNT 2
#define COLUMNCOUNT 16

LiquidCrystal_I2C lcd(LCDADDRESS, COLUMNCOUNT, ROWCOUNT);

void setupLCD() {
  lcd.init();
  lcd.backlight();
}

void Display(char* text) {

  // Clear the Screen and Set cursor to Row = 0, Column = 0
  lcd.clear();
  lcd.setCursor(0, 0);

  int length = strlen(text);

  if (length > 16) {

    int divideIndex;
    for (int i=0;i<16;i++) {
      
      if (i > 6 && text[i] == ' ') {
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


#endif

