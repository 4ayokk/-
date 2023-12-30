#include "my_keyboard.h"

static uint8_t* KEYBOARD_OUTPUT_PINS;
static uint8_t* KEYBOARD_INPUT_PINS;

void keyboard_init(uint8_t* OUTPUTS, uint8_t* INPUTS) {
  KEYBOARD_OUTPUT_PINS = OUTPUTS;
  KEYBOARD_INPUT_PINS = INPUTS;
  for(uint8_t i = 0; i < KEYBOARD_SIZE; ++i) {
    pinMode(KEYBOARD_INPUT_PINS[i], INPUT_PULLUP);  

    pinMode(KEYBOARD_OUTPUT_PINS[i], OUTPUT);
    digitalWrite(KEYBOARD_OUTPUT_PINS[i], HIGH);
  }
}

uint8_t keyboard_get_key_from(const uint8_t TABLE[KEYBOARD_SIZE][KEYBOARD_SIZE]) {
  uint8_t res = 0xFF;
  for(uint8_t out = 0; out < KEYBOARD_SIZE; ++out) {
    digitalWrite(KEYBOARD_OUTPUT_PINS[out], LOW);
    for(uint8_t in = 0; in < KEYBOARD_SIZE; ++in ) {
      if(digitalRead(KEYBOARD_INPUT_PINS[in]) == KEY_ACTIVE) res =  TABLE[out][in];
    }
     digitalWrite(KEYBOARD_OUTPUT_PINS[out], HIGH);
  }
  return res;
}

uint8_t keyboard_get_char() {
    const uint8_t CHARS[4][4] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C', 
    '*', '0', '#', 'D'
  };
  return keyboard_get_key_from(CHARS);
}

uint8_t keyboard_get_int() {
  const uint8_t INTS[4][4] = {
    1,  2,   3,  10,
    4,  5,   6,  11,
    7,  8,   9,  12,
    14,  0,  15,  13,
  };
  return keyboard_get_key_from(INTS);
}

