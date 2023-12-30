#ifndef my_keyboard_h
#define my_keyboard_h

#include <stdint.h>
#include <Arduino.h>

#define KEYBOARD_SIZE 4
#define KEY_ACTIVE LOW

void      keyboard_init(uint8_t*, uint8_t*);
uint8_t   keyboard_get_key_from(const uint8_t**);
uint8_t   keyboard_get_char();
uint8_t   keyboard_get_int();

#endif /* my_keyboard_h */