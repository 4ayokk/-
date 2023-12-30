// Лаболаторна робота №4
// Код для плати STM32F103C8T6
// 
// Автор: Калюта Дмитро 
// Група: РС-31мп
//
// Завдання:
// Реалізувати драйвер семисегментного індикатора

#include "my_SS1D.h"

uint8_t SEGMENT[] = {PA0, PA1, PA2, PA3, PA4, PA5, PA6}; // 7S PINS (a, b, c... g, dp)

void setup() {
  SS1D_init(SEGMENT);
}
void loop() {
  for(int i = 0; i < 20; ++i) {
    SS1D_write_int(i);
    delay(250);
  }
}

