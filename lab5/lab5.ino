#include <VirtualWire.h>
#include "my_keyboard.h"


uint8_t KOUT[] = {9, 8, 7, 6};    // KEYBOARD OUTPUT PINS
uint8_t  KIN[] = {5, 4, 3, 2}; 

uint8_t msg[] = {'0', '\0'};


void setup() {
  vw_setup(1200);
  vw_set_tx_pin(12);
  keyboard_init(KOUT, KIN);
}

void loop() {
  msg[0] = keyboard_get_char();
  vw_send((uint8_t *)msg, 2);
  vw_wait_tx();
}

