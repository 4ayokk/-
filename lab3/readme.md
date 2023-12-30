# Лабораторна робота №3

> Виконав: Студент Групи РС-31мп Калюта Дмитро Петрович
## Завдання: 
1. Підключити до мікроконтролера матричну клавіатуру;
2. Написати драйвер клавіатури;
3. Підключити до мікроконтролера 2 сервоприводи та запрограмувати їх таким чином щоб:
	- При натисканні клавіш "2" та "8" обертався сервопривід №1 на +90 та -90 градусів відповідно;
	- При натисканні клавіш "4" та "6" обертався сервопривід №1 на +90 та -90 градусів відповідно;

## Схема

Клавіатура підключена до пінів 2 - 9 (включно).
Сигнальні провідники сервоприводів підключені до піні 10 та 11 відповідно.

![[../src/Pasted image 20231227175456.png]]

## Драйвер Клавіатури

Драйвер Клавіатури складається із двох файлів. Файли `.h` (заголовок) та `.cpp` (файл з визначеннями).

1. Файл `my_keyboard.h`  : Цей файл містить декларації класів, функцій, констант, типів даних та інших елементів, які будуть доступні для користувачів бібліотеки. Він описує інтерфейс бібліотеки, представляючи доступні функції та їхні аргументи без реалізації.
2. Файл `my_keyboard.cpp` : Цей файл містить реалізацію функцій, які були оголошені у файлі `.h`. Він містить код функцій, що визначають їхню роботу та функціональність.

Така розділеність дозволяє створити чистий та організований інтерфейс для користувачів бібліотеки (у файлі `.h`), що відділяє інтерфейс від реалізації. Файли `.cpp` містять реалізацію функцій та дозволяють компілятору розміщувати реалізацію функцій у вихідних файлах програми.

### my_keyboard.h
``` cpp
#ifndef my_keyboard_h
#define my_keyboard_h

#include <stdint.h>
#include <Arduino.h>

#define KEYBOARD_SIZE 4
#define KEY_ACTIVE LOW

void      keyboard_init(uint8_t*, uint8_t*);
uint8_t   keyboard_get_key_from(const uint8_t**);
uint8_t   keyboard_get_char();
uint8_t   keyboard_get_int();

#endif /* my_keyboard_h */
```

### my_keyboard.cpp

``` cpp
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
      if(digitalRead(KEYBOARD_INPUT_PINS[in]) == KEY_ACTIVE) res =  TABLE[out][in];
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

    1,  2,   3,  10,

    4,  5,   6,  11,

    7,  8,   9,  12,

    14,  0,  15,  13,

  };
  return keyboard_get_key_from(INTS);
}

```


## Програма для сервоприводами (lab3.ino)

``` cpp
#include <Servo.h>
#include "my_keyboard.h"

uint8_t KOUT[] = {9, 8, 7, 6};    // KEYBOARD OUTPUT PINS
uint8_t  KIN[] = {5, 4, 3, 2};    // KEYBOARD INPUT  PINS

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
```

## Висновки:

1. **Підключення обладнання:** У рамках лабораторної роботи було успішно підключено до мікроконтролера матричну клавіатуру та два сервопривода.

2. **Створення драйвера клавіатури:** Було розроблено драйвер клавіатури, який складається із двох файлів: `.h` та `.cpp`. Файл `.h` містить оголошення функцій та констант, а файл `.cpp` - реалізацію цих функцій. Це дозволило створити зручний інтерфейс для користувачів бібліотеки та відділити його від реалізації.

3. **Програмування сервоприводів:** Сервоприводи були запрограмовані таким чином, що при натисканні певних клавіш (2, 4, 6, 8) вони оберталися на певні кути відповідно до вказаних у програмі значень.

4. **Використання драйвера клавіатури у головній програмі:** У головній програмі `lab3.ino` була використана раніше створена бібліотека для роботи з клавіатурою. Це дозволило зробити код головної програми більш організованим та зрозумілим.




