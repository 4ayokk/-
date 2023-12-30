// Лаболаторна робота №1
// Код для плати STM32F103C8T6
// 
// Автор: Калюта Дмитро 
// Група: РС-31мп

#define LedPin PC13

void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LedPin, LOW);  // Подати на пін низький рівень (0)
  delay(100);   // затримка
  digitalWrite(LedPin, HIGH);   // Подати на пін високий рівень (1)
  delay(100); // затримка
}
