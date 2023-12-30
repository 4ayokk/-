// Лаболаторна робота №2
// Код для плати ARDUINO UNO
// 
// Автор: Калюта Дмитро 
// Група: РС-31мп
//
// Завдання:
// Запрограмувати мікроконтролер таким чином щоб при натисканні однієї кнопки
// Сервомотор повертав ліворуч на 90 градусів
// А при натисканні іншої праворуч на 90 градусів
// Якщо жодна кнопка не натиснута сервомотор повертається в цетральне положення

#include <Servo.h>

#define servoPin 3
#define b1Pin 8
#define b2Pin 9


Servo s1; 

void setup() {
  // put your setup code here, to run once:
  s1.attach(servoPin);
  pinMode(b1Pin, INPUT_PULLUP); // 1!
  pinMode(b2Pin, INPUT_PULLUP); // 1!
}

void loop() {
  if(digitalRead(b1Pin) == 0) s1.write(0);
  else if(digitalRead(b2Pin) == 0) s1.write(180);
  else s1.write(90);
}

