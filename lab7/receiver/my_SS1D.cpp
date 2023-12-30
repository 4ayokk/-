#include "my_SS1D.h"

static uint8_t SS1D_PINS_COUNT = 7; 
static uint8_t* SS1D_PINS;
  
void SS1D_init(const uint8_t pins[]) {
  SS1D_PINS = pins;
  for(uint8_t i = 0; i < SS1D_PINS_COUNT; ++i) {
    pinMode(SS1D_PINS[i], OUTPUT);
    digitalWrite(SS1D_PINS[i], LOW);
  }
}

void SS1D_clear(void) {
  for(uint8_t i = 0; i < 7; ++i) {
    digitalWrite(SS1D_PINS[i], LOW); 
  }
}

void SS1D_write_int(const uint8_t num) {
      byte numbersToDisplay[] = { 
        B00111111,  //  0
        B00000110,  //  1
        B01011011,  //  2
        B01001111,  //  3
        B01100110,  //  4
        B01101101,  //  5
        B01111101,  //  6
        B00000111,  //  7
        B01111111,  //  8
        B01101111,  //  9
        B01110111,  //  A
        B01111100,  //  B
        B00111001,  //  C
        B01011110,  //  D
        B01111001,  //  E
        B01110001,  //  F
        B01010010  //  Error1
        //B01110110
        //B00000000
    };

  SS1D_clear();
  for(uint8_t i = 0; i < 7; ++i) {
    if(num < 0 || num > 15) {
      digitalWrite(SS1D_PINS[i], bitRead(numbersToDisplay[16], i));
    }
    digitalWrite(SS1D_PINS[i], bitRead(numbersToDisplay[num], i));
  }
}

void SS1D_write_char(const uint8_t c) {
  uint8_t num = (c >= '0' && c <= '9') ? c - '0' :  
      (c >= 'A' && c <= 'F') ? c - 'A' + 10 : 
      (c == '*') ? 14 : 
      (c == '#') ? 15 : 16;

  SS1D_write_int(num);
}

