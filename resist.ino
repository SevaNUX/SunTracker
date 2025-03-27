
#include "GyverButton.h"  //библиотека контроль кнопок
#include <Servo.h>   //плавное серво


//ServoSmooth servo;
uint32_t tmr;
boolean flagus;
#define BTN_PIN 3      //  пин кнопка
#define MODE_AM 3       // количество режимов
#define TimePeriod 100  // задержка в миллисекундах



GButton butt1(BTN_PIN, HIGH_PULL);  // инициируем кнопку
byte mode = 1;        // номер режима по умолчанию
int flag=0;           // флаг первого запуска режима

int DTL = A1; // пин фоторезистор TOP LEFT
int DTR = A2; // пин фоторезистор TOP RIGHT
int DBL = A3; // пин фоторезистор  BOTTOM LEFT
int DBR = A4; // пин фоторезистор BOTTOM RIGHT

float step = 1;   //  шаг сервы (в градусах)
float latitude = 66.05;   //Широта
float longitude = 76.40;   //Долгота

//------------

//Servo horizontal;
Servo azDrive;   // Серво поворота панели

int angleAz = 90;
int azLimitHigh = 180;
int azLimitLow = 0;

//Servo vertical;
Servo altDrive;  // Серво наклона панели
int angleAlt = 45;
int altLimitHigh = 180;
int altLimitLow = 0;
int sens = 100; //чувстительность фоторезисторов


//----------

void setup()
{
Serial.begin(9600);
Serial.println("---------------- GO -----------------");

azDrive.attach(6);   	// Поворот панели  6 пин
altDrive.attach(7);  	// Подъем понели   7 пин
azDrive.write(angleAz); // ставим серво на 90
altDrive.write(angleAlt); // ставим серво на 0

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
     Serial.println("-- режим 0--");
    flag=1;
  }

// читаем данные с фоторезисторов

  int TL = analogRead(DTL); // top left
  int TR = analogRead(DTR); // top right
  int BL = analogRead(DBL); // down left
  int BR = analogRead(DBR); // down rigt

// сичтаем средние значения
  int AVerT = (TL + TR) / 2; // среднне верх
  int AVerB = (BL + BR) / 2; // среднее низ
  int AVerL = (TL + BL) / 2; // среднее лево
  int AVerR = (TR + BR) / 2; // среднее право

  int dvert = abs(AVerT - AVerB);   // разница средних верх-низ
  int dhoriz = abs(AVerL - AVerR);  // разница средних лево-право

  Serial.print("Tl: ");
  Serial.print(TL);
  Serial.print(" ");
  Serial.print("tr: ");
  Serial.println(TR);
  Serial.print("BL: ");
  Serial.print(BL);
  Serial.print(" ");
  Serial.print("BR: ");
  Serial.println(BR);
  Serial.println("---------------");
  Serial.print("horis - ");
  Serial.println(dhoriz);
    Serial.print("vert - ");
  Serial.println(dvert);
 delay(2000);

//ровняем сервы

 if (dhoriz > sens){
    if (AVerL > AVerR){
      if (angleAz - 1 >= azLimitLow) angleAz--;
      Serial.println("Переход за предел сервы");
      delay (2000);
    }
    else if (AVerL < AVerR){
      if (angleAz + 1 <= azLimitHigh) angleAz++;
  delay (2000);
      Serial.println("Переход за предел сервы");
   
    }
    azDrive.write(angleAz);
  }
/*
  if (dvert > sens){
    if (AVerT > AVerB){
      if (angleAlt + 1 <= altLimitHigh) angleAlt++;
       Serial.println("Переход за предел сервы");
    }
    else if (AVerT < AVerB){
      if (angleAlt - 1 >= altLimitLow) angleAlt--;
       Serial.println("Переход за предел сервы");
    }
    altDrive.write(angleAlt);
  }
   */
}

void task_1() {


  if (flag==0){
     Serial.println("-- режим 1--");
  azDrive.write(0);

    flag=1;
  }
for (angleAz = 1; angleAz < 180; angleAz++) {
  // тело цикла
azDrive.write(angleAz);
 Serial.println(angleAz);
delay(100);
}
  
    
}

void task_2() {
 
   if (flag==0){
    Serial.println("-- режим 2--");

    flag=1;
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

/*
#include <Servo.h>        
#include "GyverButton.h"  //библиотека контроль кнопок
#include <SunPosition.h>  // библиотека расчет солнца
#include "UnixTime.h" // библиотека расчет времени

#define BTN_PIN 4       //  пин кнопка
#define MODE_AM 3       // количество режимов
#define TimePeriod 100 // время зажержки для таймера в миллисекундах

GButton butt1(BTN_PIN, HIGH_PULL);  // инициируем кнопку

int DTL = A1; // пин фоторезистор TOP LEFT
int DTR = A2; // пин фоторезистор TOP RIGHT
int DBL = A3; // пин фоторезистор  BOTTOM LEFT
int DBR = A4; // пин фоторезистор BOTTOM RIGHT


byte mode = 0;        // номер режима по умолчанию

int flag=0;           // флаг первого запуска режима
uint32_t timer=0;     // таймер для задерки



int direction;    // угол поворота панели
int angle;        // угол наклона панели

UnixTime stamp(5); //UTC+5

int year = 2023; 
int month = 6;
int day = 1;
int hour = 0;  //Часы
float latitude = 66.05;   //Широта
float longitude = 76.40;   //Долгота




void setup()
{
Serial.begin(9600);
Serial.println("---------------- GO -----------------");
azimuthDrive.attach(6);   	// Поворот панели  6 пин
altitudeDrive.attach(7);  	// Подъем понели   7 пин
azimuthDrive.write(90); // ставим серво на 90
altitudeDrive.write(0); // ставим серво на 0
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
     Serial.println("-- режим 0--");
     azimuthDrive.write(90); // ставим серво на 0
     altitudeDrive.write(1); // ставим серво на 0
    flag=1;
  }

 altitudeDrive.write(45); // ставим серво на 0
azimuthDrive.write(45); // ставим серво на 0
delay(500);

altitudeDrive.write(0); // ставим серво на 0
azimuthDrive.write(45); // ставим серво на 0
delay(500);
 altitudeDrive.write(90); // ставим серво на 0
azimuthDrive.write(45); // ставим серво на 0
delay(500);


}

// ------------------------

//режим вертикальный
void task_1() {


  if (flag==0){
     Serial.println("-- ражим  1--");
     
    azimuthDrive.write(90); // ставим серво на 0
    altitudeDrive.write(1); // ставим серво на 0
  
    
    //Параметры режима
    year = 2023;
    month = 8;
    day = 1;
    hour = 1;  //Часы
    // float latitude = 66.05;   //Широта
    // float longitude = 76.40;   //Долгота
    // UnixTime stamp(5); //UTC+5
    flag=1;
  }
  /*
  if (day<30){
    if ((millis() - timer >= TimePeriod*10)){ // таймер на millis()
      timer = millis(); // сброс
      if (hour<24){
        stamp.setDateTime(year, month, day, hour, 0, 0);
        uint32_t unix = stamp.getUnix();
        SunPosition sun(latitude, longitude, unix);
        direction = map(sun.azimuth(), 0, 360, 0,180);
        angle = map(sun.altitude(), 0, 90, 0, 90);
      
        altitudeDrive.write(angle); 
        hour++;
        Serial.print("day ");
        Serial.print(day);
        Serial.print(" ,hour ");
        Serial.print(hour);
         Serial.print(" ,angle ");
        Serial.print(angle);
    
         if(hour==1) {
  day++;
      }
      if(hour>=24) hour=1;
    }
  }
 
  if(day>=30) day=1;
  }

}





void task_2() {
 
 
  if (flag==0){
    Serial.println("-- режим 2--");
    azimuthDrive.write(90); // ставим серво на 0
     altitudeDrive.write(66); // ставим серво на 66
  
    
    //Параметры режима
    year = 2023;
    month = 8;
    day = 1;
    hour = 1;  //Часы
    // float latitude = 66.05;   //Широта
    // float longitude = 76.40;   //Долгота
    // UnixTime stamp(5); //UTC+5
    flag=1;
  }
  /*
  if (day<30){
    if ((millis() - timer >= TimePeriod*10)){ // таймер на millis()
      timer = millis(); // сброс
      if (hour<24){
        stamp.setDateTime(year, month, day, hour, 0, 0);
        uint32_t unix = stamp.getUnix();
        SunPosition sun(latitude, longitude, unix);
        direction = map(sun.azimuth(), 0, 360, 0,180);
        angle = abs(map(sun.altitude(), 0, 90, 0, 90));
       azimuthDrive.write(180-direction); // ставим серво на 0
    //   altitudeDrive.write(angle); // ставим серво на 0
        hour++;
        Serial.print("day ");
        Serial.print(day);
        Serial.print(" ,hour ");
        Serial.print(hour);
         Serial.print(" ,angle ");
        Serial.print(angle);
        Serial.print(" ,dir ");
        Serial.println(direction);
         if(hour==1) {
  day++;
      }
      if(hour>=24) hour=1;
    }
  }
 
  if(day>=30) day=1;
  }

}


// ------------------------
void task_3() {


  if (flag==0){
    Serial.println("-- режим 3--");
    
    azimuthDrive.write(90); // ставим серво на 0
     altitudeDrive.write(1); // ставим серво на 0
     
    //Параметры режима
    year = 2023;
    month = 8;
    day = 1;
    hour = 13;  //Часы
    // float latitude = 66.05;   //Широта
    // float longitude = 76.40;   //Долгота
    // UnixTime stamp(5); //UTC+5
    flag=1;
  }
  /*
  if (day<30){
    if ((millis() - timer >= TimePeriod*36000)){ // таймер на millis()
      timer = millis(); // сброс
      if (hour<24){
        stamp.setDateTime(year, month, day, hour, 0, 0);
        uint32_t unix = stamp.getUnix();
        SunPosition sun(latitude, longitude, unix);
        direction = map(sun.azimuth(), 0, 360, 0,180);
        angle = abs(map(sun.altitude(), 0, 90, 0, 90));
        azimuthDrive.write(180-direction); // ставим серво на 0
       altitudeDrive.write(angle); // ставим серво на 0
        hour++;
        Serial.print("day ");
        Serial.print(day);
        Serial.print(" ,hour ");
        Serial.print(hour);
         Serial.print(" ,angle ");
        Serial.print(angle);
        Serial.print(" ,dir ");
        Serial.println(direction);
         if(hour==1) {
  day++;
      }
      if(hour>=24) hour=1;
    }
  }
 
  if(day>=30) day=1;
  }

}


// ------------------------
void task_4() {

if (flag==0){
    Serial.println("-- режим 4--");
    azimuthDrive.write(90); // ставим серво на 90
    altitudeDrive.write(66); // ставим серво на 0
    flag=1;
  }


/*

  if (flag==0){
     Serial.println("Режим 0");
    azimuthDrive.write(90); // ставим серво на 0
     altitudeDrive.write(1); // ставим серво на 0
     
    //Параметры режима
    year = 2023;
    month = 8;
    day = 1;
    hour = 13;  //Часы
    // float latitude = 66.05;   //Широта
    // float longitude = 76.40;   //Долгота
    // UnixTime stamp(5); //UTC+5
    flag=1;
  }
  
  if (day<30){
    if ((millis() - timer >= TimePeriod*36000)){ // таймер на millis()
      timer = millis(); // сброс
      if (hour<24){
        stamp.setDateTime(year, month, day, hour, 0, 0);
        uint32_t unix = stamp.getUnix();
        SunPosition sun(latitude, longitude, unix);
        direction = map(sun.azimuth(), 0, 360, 0,180);
        angle = map(sun.altitude(), 0, 90, 0, 90);
           azimuthDrive.write(180-direction); // ставим серво на 0
       altitudeDrive.write(angle); // ставим серво на 0
        hour++;
        Serial.print("day ");
        Serial.print(day);
        Serial.print(" ,hour ");
        Serial.print(hour);
         Serial.print(" ,angle ");
        Serial.print(angle);
        Serial.print(" ,dir ");
        Serial.println(direction);
         if(hour==1) {
  day++;
      }
      if(hour>=24) hour=1;
    }
  }
 
  if(day>=30) day=1;
  }

}

*/
/*
#include <Servo.h>        
#include "GyverButton.h"  //библиотека контроль кнопок
#include <SunPosition.h>  // библиотека расчет солнца
#include "UnixTime.h" // библиотека расчет времени

#define BTN_PIN 4       //  пин кнопка
#define MODE_AM 3       // количество режимов
#define TimePeriod 100 // время зажержки для таймера в миллисекундах

GButton butt1(BTN_PIN, HIGH_PULL);  // инициируем кнопку

int DTL = A1; // пин фоторезистор TOP LEFT
int DTR = A2; // пин фоторезистор TOP RIGHT
int DBL = A3; // пин фоторезистор  BOTTOM LEFT
int DBR = A4; // пин фоторезистор BOTTOM RIGHT


byte mode = 0;        // номер режима по умолчанию

int flag=0;           // флаг первого запуска режима
uint32_t timer=0;     // таймер для задерки



int direction;    // угол поворота панели
int angle;        // угол наклона панели

UnixTime stamp(5); //UTC+5

int year = 2023; 
int month = 6;
int day = 1;
int hour = 0;  //Часы
float latitude = 66.05;   //Широта
float longitude = 76.40;   //Долгота

//Servo horizontal;
Servo azimuthDrive;   // Серво поворота панели

int servoh = 90;
int servohLimitHigh = 180;
int servohLimitLow = 0;

//Servo vertical;
Servo altitudeDrive;  // Серво наклона панели
int servov = 45;
int servovLimitHigh = 180;
int servovLimitLow = 0;

int tol = 100; //чувстительность фоторезисторов


void setup()
{
Serial.begin(9600);
Serial.println("---------------- GO -----------------");
azimuthDrive.attach(6);   	// Поворот панели  6 пин
altitudeDrive.attach(7);  	// Подъем понели   7 пин
azimuthDrive.write(90); // ставим серво на 90
altitudeDrive.write(0); // ставим серво на 0
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
     Serial.println("-- режим 0--");
     azimuthDrive.write(90); // ставим серво на 0
     altitudeDrive.write(1); // ставим серво на 0
    flag=1;
  }

 altitudeDrive.write(45); // ставим серво на 0
azimuthDrive.write(45); // ставим серво на 0
delay(500);

altitudeDrive.write(0); // ставим серво на 0
azimuthDrive.write(45); // ставим серво на 0
delay(500);
 altitudeDrive.write(90); // ставим серво на 0
azimuthDrive.write(45); // ставим серво на 0
delay(500);
// читаем данные с фоторезисторов

  int TL = analogRead(DTL); // top left
  int TR = analogRead(DTR); // top right
  int BL = analogRead(DBL); // down left
  int BR = analogRead(DBR); // down rigt

// сичтаем средние значения
  int AVerT = (TL + TR) / 2; // среднне верх
  int AVerB = (BL + BR) / 2; // среднее низ
  int AVerL = (TL + BL) / 2; // среднее лево
  int AVerR = (TR + BR) / 2; // среднее право

  int dvert = abs(AVerT - AVerB);   // разница средних верх-низ
  int dhoriz = abs(AVerL - AVerR);  // разница средних лево-право

  Serial.print("Tl: ");
  Serial.print(TL);
  Serial.print(" ");
  Serial.print("tr: ");
  Serial.println(TR);
/*

  Serial.print("BL: ");
  Serial.print(BL);
  Serial.print(" ");
  Serial.print("BR: ");
  Serial.println(BR);
  Serial.println("---------------");
  Serial.print("horis");
  Serial.println(dhoriz);
 delay(2000);

//ровняем сервы
/*
 if (dhoriz > tol){
    if (avl > avr){
      if (servoh - 1 >= servohLimitLow) servoh--;
      Serial.println("Переход за предел сервы");
      delay (2000);
    }
    else if (avl < avr){
      if (servoh + 1 <= servohLimitHigh) servoh++;
  delay (2000);
      Serial.println("Переход за предел сервы");
   
    }
    azimuthDrive.write(servoh);
  }

  if (dvert > tol){
    if (avt > avd){
      if (servov + 1 <= servovLimitHigh) servov++;
       Serial.println("Переход за предел сервы");
    }
    else if (avt < avd){
      if (servov - 1 >= servovLimitLow) servov--;
       Serial.println("Переход за предел сервы");
    }
    altitudeDrive.write(servov);
  }

}

// ------------------------

//режим вертикальный
void task_1() {


  if (flag==0){
     Serial.println("-- ражим  1--");
     
    azimuthDrive.write(90); // ставим серво на 0
    altitudeDrive.write(1); // ставим серво на 0
  
    
    //Параметры режима
    year = 2023;
    month = 8;
    day = 1;
    hour = 1;  //Часы
    // float latitude = 66.05;   //Широта
    // float longitude = 76.40;   //Долгота
    // UnixTime stamp(5); //UTC+5
    flag=1;
  }
  /*
  if (day<30){
    if ((millis() - timer >= TimePeriod*10)){ // таймер на millis()
      timer = millis(); // сброс
      if (hour<24){
        stamp.setDateTime(year, month, day, hour, 0, 0);
        uint32_t unix = stamp.getUnix();
        SunPosition sun(latitude, longitude, unix);
        direction = map(sun.azimuth(), 0, 360, 0,180);
        angle = map(sun.altitude(), 0, 90, 0, 90);
      
        altitudeDrive.write(angle); 
        hour++;
        Serial.print("day ");
        Serial.print(day);
        Serial.print(" ,hour ");
        Serial.print(hour);
         Serial.print(" ,angle ");
        Serial.print(angle);
    
         if(hour==1) {
  day++;
      }
      if(hour>=24) hour=1;
    }
  }
 
  if(day>=30) day=1;
  }

}





void task_2() {
 
 
  if (flag==0){
    Serial.println("-- режим 2--");
    azimuthDrive.write(90); // ставим серво на 0
     altitudeDrive.write(66); // ставим серво на 66
  
    
    //Параметры режима
    year = 2023;
    month = 8;
    day = 1;
    hour = 1;  //Часы
    // float latitude = 66.05;   //Широта
    // float longitude = 76.40;   //Долгота
    // UnixTime stamp(5); //UTC+5
    flag=1;
  }
  /*
  if (day<30){
    if ((millis() - timer >= TimePeriod*10)){ // таймер на millis()
      timer = millis(); // сброс
      if (hour<24){
        stamp.setDateTime(year, month, day, hour, 0, 0);
        uint32_t unix = stamp.getUnix();
        SunPosition sun(latitude, longitude, unix);
        direction = map(sun.azimuth(), 0, 360, 0,180);
        angle = abs(map(sun.altitude(), 0, 90, 0, 90));
       azimuthDrive.write(180-direction); // ставим серво на 0
    //   altitudeDrive.write(angle); // ставим серво на 0
        hour++;
        Serial.print("day ");
        Serial.print(day);
        Serial.print(" ,hour ");
        Serial.print(hour);
         Serial.print(" ,angle ");
        Serial.print(angle);
        Serial.print(" ,dir ");
        Serial.println(direction);
         if(hour==1) {
  day++;
      }
      if(hour>=24) hour=1;
    }
  }
 
  if(day>=30) day=1;
  }

}


// ------------------------
void task_3() {


  if (flag==0){
    Serial.println("-- режим 3--");
    
    azimuthDrive.write(90); // ставим серво на 0
     altitudeDrive.write(1); // ставим серво на 0
     
    //Параметры режима
    year = 2023;
    month = 8;
    day = 1;
    hour = 13;  //Часы
    // float latitude = 66.05;   //Широта
    // float longitude = 76.40;   //Долгота
    // UnixTime stamp(5); //UTC+5
    flag=1;
  }
  /*
  if (day<30){
    if ((millis() - timer >= TimePeriod*36000)){ // таймер на millis()
      timer = millis(); // сброс
      if (hour<24){
        stamp.setDateTime(year, month, day, hour, 0, 0);
        uint32_t unix = stamp.getUnix();
        SunPosition sun(latitude, longitude, unix);
        direction = map(sun.azimuth(), 0, 360, 0,180);
        angle = abs(map(sun.altitude(), 0, 90, 0, 90));
        azimuthDrive.write(180-direction); // ставим серво на 0
       altitudeDrive.write(angle); // ставим серво на 0
        hour++;
        Serial.print("day ");
        Serial.print(day);
        Serial.print(" ,hour ");
        Serial.print(hour);
         Serial.print(" ,angle ");
        Serial.print(angle);
        Serial.print(" ,dir ");
        Serial.println(direction);
         if(hour==1) {
  day++;
      }
      if(hour>=24) hour=1;
    }
  }
 
  if(day>=30) day=1;
  }

}


// ------------------------
void task_4() {

if (flag==0){
    Serial.println("-- режим 4--");
    azimuthDrive.write(90); // ставим серво на 90
    altitudeDrive.write(66); // ставим серво на 0
    flag=1;
  }


/*

  if (flag==0){
     Serial.println("Режим 0");
    azimuthDrive.write(90); // ставим серво на 0
     altitudeDrive.write(1); // ставим серво на 0
     
    //Параметры режима
    year = 2023;
    month = 8;
    day = 1;
    hour = 13;  //Часы
    // float latitude = 66.05;   //Широта
    // float longitude = 76.40;   //Долгота
    // UnixTime stamp(5); //UTC+5
    flag=1;
  }
  
  if (day<30){
    if ((millis() - timer >= TimePeriod*36000)){ // таймер на millis()
      timer = millis(); // сброс
      if (hour<24){
        stamp.setDateTime(year, month, day, hour, 0, 0);
        uint32_t unix = stamp.getUnix();
        SunPosition sun(latitude, longitude, unix);
        direction = map(sun.azimuth(), 0, 360, 0,180);
        angle = map(sun.altitude(), 0, 90, 0, 90);
           azimuthDrive.write(180-direction); // ставим серво на 0
       altitudeDrive.write(angle); // ставим серво на 0
        hour++;
        Serial.print("day ");
        Serial.print(day);
        Serial.print(" ,hour ");
        Serial.print(hour);
         Serial.print(" ,angle ");
        Serial.print(angle);
        Serial.print(" ,dir ");
        Serial.println(direction);
         if(hour==1) {
  day++;
      }
      if(hour>=24) hour=1;
    }
  }
 
  if(day>=30) day=1;
  }

}

*/