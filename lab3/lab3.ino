#include <Servo.h>
#include "my_keyboard.h"

uint8_t KOUT[] = {9, 8, 7, 6};    // KEYBOARD OUTPUT PINS
uint8_t  KIN[] = {5, 4, 3, 2};    // KEYBOARD INPUT  PINS

#define s1Pin 10
#define s2Pin 11

Servo s1; 
Servo s2; 

uint8_t s1_deg;
uint8_t s2_deg;
uint8_t key;

void setup() {
  keyboard_init(KOUT, KIN);
  s1.attach(s1Pin);
  s2.attach(s2Pin);
}

void loop() {
  key = keyboard_get_int();
  s1_deg = (key == 2) ? 0 : (key == 8) ? 180 : 90;
  s2_deg = (key == 4) ? 0 : (key == 6) ? 180 : 90;

  s1.write(s1_deg);
  s2.write(s2_deg);
}

