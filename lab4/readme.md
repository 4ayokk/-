# Лабораторна робота №4

> Виконав: Студент Групи РС-31мп Калюта Дмитро Петрович
## Завдання: 
Реалізувати драйвер семисегментного індикатора

## Побудована схема на мікроконтролері STM32F103C8T6


![Pasted image 20231227220110](https://github.com/4ayokk/-/assets/113011334/f48725ab-5b59-4e16-b64d-0b1c90278388)

Тип семисегментного індикатора - спільний катод, і він підключається до землі.  Решта пінів семисегментного індикатора підключаються до GPIO-пінів STM32, по порядку (Сегмент А підключається до першого піна, В до другого і так далі). На платі STM32 використано піни A0 - A6.

## Вихідний код драйвера

### my_SS1D.h
``` cpp
#ifndef my_SS1D_h
#define my_SS1D_h

#include <stdint.h>
#include <Arduino.h>

void SS1D_init(uint8_t*);
void SS1D_clear(void);
void SS1D_write_int(uint8_t);
void SS1D_write_char(uint8_t);

#endif /* my_SS1D_h */
```

### my_SS1D.cpp

``` cpp
#include "my_SS1D.h"

static uint8_t SS1D_PINS_COUNT = 7;
static uint8_t* SS1D_PINS;

void SS1D_init(uint8_t pins[]) {
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

void SS1D_write_int(uint8_t num) {
      byte numbersToDisplay[] = {
        B00111111,  //  0
        B00000110,  //  1
        B01011011,  //  2
        B01001111,  //  3
        B01100110,  //  4
        B01101101,  //  5
        B01111101,  //  6
        B00000111,  //  7
        B01111111,  //  8
        B01101111,  //  9
        B01110111,  //  A
        B01111100,  //  B
        B00111001,  //  C
        B01011110,  //  D
        B01111001,  //  E
        B01110001,  //  F
        B01010010  //  Error
    };

  SS1D_clear();
  for(uint8_t i = 0; i < 7; ++i) {
    if(num < 0 || num > 15) num = 16;
    digitalWrite(SS1D_PINS[i], bitRead(numbersToDisplay[num], i));
  }
}

void SS1D_write_char(uint8_t c) {
  uint8_t num = (c >= '0' && c <= '9') ? c - '0' :  
      (c >= 'A' && c <= 'F') ? c - 'A' + 10 :
      (c == '*') ? 14 :
      (c == '#') ? 15 : 16;
  SS1D_write_int(num);
}
```

## Код який керує МК (lab4.ino)

``` cpp
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
```

## Результат роботи 

https://github.com/4ayokk/-/assets/113011334/da5a2310-e60f-4203-84ec-354108928e8a


## Висновки
Лабораторна робота була успішно виконана, і був створений драйвер для ефективного керування семисегментним індикатором за допомогою мікроконтролера STM32F103C8T6. Розроблений код дозволяє відображати числа на індикаторі та може бути використаний у подальших проектах для відображення інформації на семисегментному індикаторі. Функції бібліотеки `SS1D_init`, `SS1D_clear`, `SS1D_write_int` та `SS1D_write_char` дозволяють ефективно керувати індикатором. У головній програмі `lab4.ino` був використаний створений драйвер для відображення чисел від 0 до 19 на семисегментному індикаторі з паузою в 250 мілісекунд між числами. Відео, представлене в роботі, демонструє коректне відображення чисел на семисегментному індикаторі у відповідності до програмованої послідовності.
    
