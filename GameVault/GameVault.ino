#include "Config.h"
#include "NFCReader.h"
#include "LCDScreen.h"
#include "inputKeypad.h"

void setup() {
  // put your setup code here, to run once:
  setupLCD();
  Display("Hello, World!");
}

void loop() {
  // put your main code here, to run repeatedly:

  char key = keypad.getKey();

  if (key) {

    if (key == '#') {
      Display("# is Pressed.");
      delay(2000);
      lcd.clear();
    }

  }



}
