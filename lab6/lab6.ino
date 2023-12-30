// Лаболаторна робота №4
// Код для плати STM32F103C8T6
// 
// Автор: Калюта Дмитро 
// Група: РС-31мп
//
// Завдання:
//  Підключити до проекту семисегментного індикатора (ЛР4) приймач MX-RM5v
// та запрограмувати МК для отримання даних

#include "my_SS1D.h"
#include <VirtualWire.h>

uint8_t buf[2] = {0, 0};

uint8_t SEGMENT[] = {26, 24, 22, 23, 25, 27, 28}; // 7S PINS (a, b, c... g, dp)

void setup() {
  vw_setup(1200);
  vw_set_rx_pin(8);
  SS1D_init(SEGMENT);
}
void loop() {
  vw_rx_start(); 
  if (vw_have_message()) { 
    if (vw_get_message(buf, 2)) { 
      vw_rx_stop();
    }
  }
  SS1D_write_char(buf[0]);
}






