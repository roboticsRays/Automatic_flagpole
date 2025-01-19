// Система управления флагштоком
// Автор: Robotics rays
// Дата: 01 2025
// Описание: Система управления флагштоком на основе Arduino с использованием HC-SR04 для активации и двигателя постоянного тока для подъёма флага.

// Определение пинов
const int trigPin = 3;
const int echoPin = 2;
const int motorPin1 = 7;
const int motorPin2 = 8;
const int ledPin = 10;

// Константы
const int distanceThreshold = 10; // Расстояние в см для активации мотора
const int ledBlinkDelay = 500;    // Задержка мигания светодиода в миллисекундах
const int motorRunTime = 1000;    // Время работы мотора в миллисекундах

void setup() {
  // Инициализация пинов
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Начальное состояние
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600); // Для отладки
}

// Функция измерения расстояния
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Перевод в см
  return distance;
}

// Функция для подъёма флага
void raiseFlag() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  delay(motorRunTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);

  // Мигание светодиода
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPin, HIGH);
    delay(ledBlinkDelay);
    digitalWrite(ledPin, LOW);
    delay(ledBlinkDelay);
  }
}

void loop() {
  long distance = measureDistance();

  Serial.print("Расстояние: ");
  Serial.print(distance);
  Serial.println(" см");

  if (distance < distanceThreshold) {
    raiseFlag();
    // Задержка, чтобы избежать повторного срабатывания
    delay(100000);
  }
}
