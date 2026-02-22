#ifndef INPUTKEYPAD_H
#define INPUTKEYPAD_H

const byte rows[4] = {2, 3, 4, 5};
const byte columns[4] = {6, 7, 8, 9};

char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};

Keypad keypad = Keypad(makeKeymap(keys), rows, columns, 4, 4);

#endif