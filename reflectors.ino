
#include "GyverButton.h"  //библиотека контроль кнопок
#include <ServoSmooth.h>   //плавное серво
ServoSmooth servo;
uint32_t tmr;
boolean flagus;
#define BTN_PIN 3       //  пин кнопка
#define MODE_AM 3       // количество режимов
#define TimePeriod 100  // задержка в миллисекундах
GButton butt1(BTN_PIN, HIGH_PULL);  // инициируем кнопку
byte mode = 0;        // номер режима по умолчанию
int flag=0;           // флаг первого запуска режима
float step = 1;   //  шаг сервы (в градусах)
float latitude = 66.05;   //Широта
float longitude = 76.40;   //Долгота

void setup()
{
Serial.begin(9600);
Serial.println("---------------- GO -----------------");
servo.attach(5);      // подключить
servo.setSpeed(30);  // ограничить скорость
servo.setAccel(0.3);   	  // установить ускорение (разгон и торможение)
servo.tick();
}


void loop() {
butt1.tick(); // опрос нажатия кнопки выбора ражимов

  if (butt1.isClick() or butt1.isStep()) {   // переключение режимов
    if (++mode >= MODE_AM) mode = 0;
    flag=0; // сброс флага первого входа в режим
  }


// крутимся в цикле loop постоянно вызываем режимы 
  switch (mode) {
    case 0: task_0(); // режим фонарик
      break;
    case 1: task_1(); // режим вертикальный
      break;
    case 2: task_2(); // режим горизонтальный
      break;
    case 3: task_3(); // режим две оси
      break;
    case 4: task_4(); // режим резерв
      break;
  }
}


// Режимы
// ------------------------
void task_0() {

 if (flag==0){
     Serial.println("-- ражим 0--");
    flag=1;
  }

 servo.tick();
  if (millis() - tmr >= 3000) {   // каждые 3 сек
    tmr = millis();
    flagus = !flagus;
    servo.setTargetDeg(66);  // двигаем до 66 градусов
    }
   
}

void task_1() {


  if (flag==0){
     Serial.println("-- режим 1--");
  

    flag=1;
  }
  servo.tick();

  if (millis() - tmr >= 3000) {   
    tmr = millis();
    flagus = !flagus;
    servo.setTargetDeg(flagus ? 5 : 66);  // качаем от 5 до 66
 
    }
}

void task_2() {
 
   if (flag==0){
    Serial.println("-- режим 2--");

    flag=1;
  }
  servo.tick();

  if (millis() - tmr >= 3000) {   // каждые 3 сек
    tmr = millis();
    flagus = !flagus;
    servo.setTargetDeg(0);  // двигаем на 0
  
    
    }
}


// ------------------------
void task_3() {


  if (flag==0){
    Serial.println("-- режим 3--");
 
  

    flag=1;
  }
 // резерв
  
}


// ------------------------
void task_4() {

if (flag==0){
    Serial.println("-- режим начальный--");
   // altitudeDrive.write(66); // ставим серво на 0
    flag=1;
  }
//azDrive.write(1);

}