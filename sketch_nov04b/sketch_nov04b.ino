/*
*  4.11.21
*  взаимодействие через последовательный порт. 
*  Необходимо выбрать мотор командой servo, задать угол командой angle и выполнить команрду start.
*  Была необходимость запоминать положение двигателя и я это реализовал, но оказывается в библиотеке предусмотрена такая возможность.
*/


// Подклоючаем библиотеку Servo
#include <Servo.h> 

// Пин для сервопривода
int servo_1_Pin = 3;
int servo_2_Pin = 5;
int servo_3_Pin = 6;
int servo_4_Pin = 9;
int servo_5_Pin = 10;
int servo_6_Pin = 11;

// Создаем объект
Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
Servo Servo6;

int angle = 0;
int servo = 0;
int angle_servo_1 = 90;
int angle_servo_2 = 90;
int angle_servo_3 = 90;
int angle_servo_4 = 90;
int angle_servo_5 = 90;
int angle_servo_6 = 90;

int readdata(){                              //Эта функция возвращает значение переменной в int, введенной в Serialmonitor  
  byte getByte;
  int outByte=0;
  do{
    while(Serial.available()!=0){ 
      getByte=Serial.read()-48;     // Вычитаем из принятого символа 48 для преобразования из ASCII в int
      outByte=(outByte*10)+getByte; //Сдвигаем outByte на 1 разряд влево, и прибавляем getByte 
      delay(500);                   // Чуть ждем для получения следующего байта из буфера (Чем больше скорость COM, тем меньше ставим задержку. 500 для скорости 9600, и приема 5-значных чисел)
    }
    }while (outByte==0);            //Зацикливаем функцию для получения всего числа
  Serial.println("Ok");
  Serial.flush();                   //Вычищаем буфер (не обязательно)
  return outByte;
}

void controlUart(){                          // Эта функция позволяет управлять системой из монитора порта
  if (Serial.available()) {         // есть что на вход
    String cmd;
    cmd = Serial.readString();
    if (cmd.equals("angle")) {           
      Serial.println("введите угол");      
      angle = readdata();
      switch (servo){
        case 1:
          angle_servo_1 = angle;
          break;
        case 2:
          angle_servo_2 = angle;
          break;
        case 3:
          angle_servo_3 = angle;
          break;
        case 4:
          angle_servo_4 = angle;
          break;
        case 5:
          angle_servo_5 = angle;
          break;
        case 6:
          angle_servo_6 = angle;
          break;
      }
      Serial.print("угол: ");
      Serial.println(angle);
    }else 
      if (cmd.equals("start")) {          
        Serial.println("Поехали!");
        switch(servo){
          case 1:
            Servo1.write(angle);
            break;
          case 2:
            Servo2.write(angle);
            break;
          case 3:
            Servo3.write(angle);
            break;
          case 4:
            Servo4.write(angle);
            break;
          case 5:
            Servo5.write(angle);
            break;
          case 6:
            Servo6.write(angle);
            break; 
        }
    }else 
      if(cmd.equals("help")){
        terminal();
      }
    else 
      if(cmd.equals("servo")){
        Serial.println("введите номер мотора");
        servo = readdata();
      }
    else 
      if(cmd.equals("help servo")){
        Serial.println("+----------------------------------+");
        Serial.print("+ ");
        Serial.print("мотор 1: ");
        Serial.print(angle_servo_1);
        Serial.println(" +");
        Serial.print("+ ");
        Serial.print("мотор 2: ");
        Serial.print(angle_servo_2);
        Serial.println(" +");
        Serial.print("+ ");
        Serial.print("мотор 3: ");
        Serial.print(angle_servo_3);
        Serial.println(" +");
        Serial.print("+ ");
        Serial.print("мотор 4: ");
        Serial.print(angle_servo_4);
        Serial.println(" +");
        Serial.print("+ ");
        Serial.print("мотор 5: ");
        Serial.print(angle_servo_5);
        Serial.println(" +");
        Serial.print("+ ");
        Serial.print("мотор 6: ");
        Serial.print(angle_servo_6);
        Serial.println(" +");
        Serial.println("+----------------------------------+");
      }
    else{
      Serial.println("error");    // ошибка
    }
  }
}

void terminal(){                             // Эта функция выводит в монитор порта информацию о настройках системы
  Serial.println("Готов");
  Serial.println("+----------------------------------+");
  Serial.print("+ ");
  Serial.print("Команда \"angle\" (от 0 до 180): ");
  Serial.print(angle);
  Serial.println(" +");
  Serial.print("+ ");
  Serial.print("Команда \"servo\" (от 1 до 6): ");
  Serial.print(servo);
  Serial.println(" +");
  Serial.print("+ ");
  Serial.print("Команда \"start\"");
  Serial.println("                  +");
  Serial.print("+ ");
  Serial.print("Команда \"help\"");
  Serial.println("                   +");
  Serial.print("+ ");
  Serial.print("Команда \"help servo\"");
  Serial.println("                   +");
  Serial.println("+----------------------------------+");
}

void setup() {
  // Нам нужно подключить сервопривод к используемому номеру пина
  Servo1.attach(servo_1_Pin);
  Servo2.attach(servo_2_Pin);
  //Servo3.attach(servo_3_Pin);
  Servo4.attach(servo_4_Pin);
  Servo5.attach(servo_5_Pin);
  Servo6.attach(servo_6_Pin);
  Serial.begin(9600);
  terminal();
}

void loop(){
  controlUart();
}
