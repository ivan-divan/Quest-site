#include <Servo.h> //используем библиотеку для работы с сервоприводом

Servo myservo; //объявляем переменную servo типа Servo
int val; // переменная с резистора
int potpin = A0; // пин резистора
int sw1 = 3; // пин переключателя режимов
int sw2 = 2; // пин переключателя режимов
int lazer = 4; // пин лазера
int phoneOff = 6; // пин сброса телефона
int phoneAnsver = 5; // пин ответа от телефона
int state = 0; // переменная хранения состояния 
int pause = 1000;
int pause_r = 3000;
int valL;
int valR;
int full;
int go;
int statSwitch = 0;

void lazerMove (int times); // подвигаться вправо влево заданое колво раз
void lazerMove (int times);
void setup() //процедура setup

{
pinMode(potpin, INPUT);
pinMode(sw1, INPUT);
pinMode(sw2, INPUT);
pinMode(7, OUTPUT); // СД1
pinMode(8, OUTPUT); //  СД2
pinMode(lazer, OUTPUT); 
pinMode(phoneAnsver, INPUT);
pinMode(phoneOff, OUTPUT);
myservo.attach(10); //привязываем привод к порту 10
Serial.begin(9600);

}


void loop() {


if (digitalRead (sw1) == 1 && digitalRead (sw2) == 0) {
    digitalWrite (7, HIGH);
    statSwitch = 1;
} else if (digitalRead (sw2) == 1 && digitalRead (sw1) == 0){ 
    digitalWrite (8, HIGH);
    statSwitch = 2;
} else {
  digitalWrite (8, LOW);
  digitalWrite (7, LOW);
  statSwitch = 0;
}
//delay (1000); // ХЗ может ну его!!!!!!!!!!!!!!!!!!!

Serial.println(statSwitch);

val = analogRead(potpin);
val = map(val,0,1023, 0,1000);
valL = 1500-val;
valR = 1500+val;
full = (valR - valL) / 33;
go = valL;


switch (statSwitch) {
    case 1:

digitalWrite(lazer,HIGH);
for (int stepLazer=1; stepLazer <= 33;  stepLazer++) 
{
myservo.writeMicroseconds(go);
go = go + full; 
delay(pause_r);
//Serial.println(stepLazer);
//Serial.println(go);
} 
digitalWrite(lazer,LOW);
    
    break;
    case 2:
    
lazerMove (1);
    
    break;
    case 0:

if (digitalRead (phoneAnsver) == 0) {

delay(700);
digitalWrite(phoneOff,HIGH);
delay(700);
digitalWrite(phoneOff,LOW);

lazerMove (2);
digitalWrite(lazer,LOW);
delay(pause);

woeds (5);
woeds (10);
woeds (13);
woeds (33);
woeds (14);
woeds (1);
woeds (25);
woeds (1);
woeds (7);
woeds (28);
woeds (15);
woeds (21);
woeds (1);
woeds (5);
woeds (18);
woeds (20);
woeds (12);
woeds (1);
}

    break; 
  }
  
}

void woeds (int bukva){

myservo.writeMicroseconds(valL+(full*(bukva-1)));
//delay (100);
digitalWrite(lazer,HIGH);
delay(pause);
digitalWrite(lazer,LOW);
delay (100);
digitalWrite(lazer,HIGH);
delay (100);
digitalWrite(lazer,LOW);
delay (100);
digitalWrite(lazer,HIGH);
delay(pause);  
digitalWrite(lazer,LOW);
delay(pause);
}

void lazerMove (int times){
for (int t=1;  t<= times;  t++){

digitalWrite(lazer,HIGH);   
myservo.writeMicroseconds(valL);//ставим вал под 0
Serial.println(valL);
delay(700); //ждем 2 секунды
myservo.writeMicroseconds(valL+(full*32));//ставим вал под 180
delay(700); //ждем 2 секунды
Serial.println(valL+(full*32));
digitalWrite(lazer,LOW);
}

}
