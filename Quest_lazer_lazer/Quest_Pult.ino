#include <Keypad.h>
#include <SPI.h>  
#include "RF24.h"

byte onOff = 0; // переменная состояния 
RF24 myRadio (A4, A5);   // CE, CSN инициализация NRF24L01

struct package
{
  int msg = 0;
};
byte addresses[][6] = {"0"};
typedef struct package Package;
Package data;



#define LED1 A1 // красный светодиод
#define LED2 A2 //. зеленый светодиод реле на замок
#define ZOOMER A3 // зумер
//#define BUT A6 // переключатель режим програмирования
#define NUM_KEYS 5 // количество знаков в коде


char key;
char myarraw[NUM_KEYS] = { '1', '2', '3', '4', '5'}; // массив с верным кодом
char button_pressed[NUM_KEYS]; //массив для хранения нажатых кнопок
int k = 0; // счетчик нажатий
int s = 0; // счетчик совпадений нажатых кнопок с верными
const byte ROWS = 4; // количество строк в матрице клавиатуры
const byte COLS = 4; // количество столбцов
char keys[ROWS][COLS] = { // таблица соответствия кнопок символам
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', '0', 'A', 'B'},
  {'C', 'D', 'E', 'F'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; // пины подключенных строк
byte colPins[COLS] = {9, 8, 7, 6}; // пины подключенных столбцов

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // создаем объект клавиатуры для работы с ней

void setup() {
  pinMode(LED1, OUTPUT); // красный светодиод
  pinMode(LED2, OUTPUT); // зеленый светодиод
  pinMode(ZOOMER, OUTPUT); // пищалка
//  pinMode(BUT, INPUT); // режим програмирования
  
  myRadio.begin();  
  myRadio.setChannel(115);           // Диапазон 115 находится выше WIFI
  myRadio.setPALevel(RF24_PA_MIN);   // минимальная выходная мощность
  myRadio.setDataRate(RF24_250KBPS); // Минимальная скорость

}

void loop (){ 
  
  
  key = keypad.getKey(); // спрашиваем у клавиатуры, есть нажатая кнопка?

  if ( key != NO_KEY ) // если она все-таки есть
  {
      digitalWrite(ZOOMER, HIGH);
      delay (40);
      digitalWrite(ZOOMER, LOW);

    button_pressed [k] = key; //сохраняем эту кнопочку в массиве
    k = k + 1; // запоминаем сколько уже кнопок нажали
    if (k == NUM_KEYS) // если нажали нужное количество кнопок
    { for ( uint8_t i = 0; i < NUM_KEYS; i++) // пройдемся по всему массиву
      {
        if (button_pressed[i] == myarraw[i]) // и проверим нажатые кнопки с верным кодом
        { s = s + 1; // плюсуем счетчик совпадений


        }

      }

      if (s == NUM_KEYS) //если у нас все кнопки совпали с кодом, то включаем реле
      {
        digitalWrite (LED2, HIGH); // зажгли зеленый светик (пользователь ввел верный код)
        digitalWrite(ZOOMER, HIGH); delay (100); 
        digitalWrite(ZOOMER, LOW); delay (100);
        digitalWrite(ZOOMER, HIGH); delay (200); 
        digitalWrite(ZOOMER, LOW); 
        data.msg = 800;
        WriteData();
        delay (5000); // ждем 5 секунд пока горит светик зеленый и включено реле
        digitalWrite (LED2, LOW); // гасим светик


        k = 0; //сбрасываем счетчик нажатий нашей переменной
        s = 0; // сбрасываем счетчик совпадений нашей переменной
      } else { // если не все кнопки совпали с верным кодом

        tone(ZOOMER, 1900, 800);
        digitalWrite (LED1, HIGH); // включаем красный светик (пользователь ввел неверный код)
        delay (5000); // ждем 5 секунд
        digitalWrite (LED1, LOW); // гасим красн светик
        k = 0; // обнуляем счетчики, чтобы начать все заново
        s = 0; //
      }
    }
  }
}

void WriteData() // программа передачи данных 
{ 
  myRadio.stopListening();                // Остановить прием и начать передачу
  myRadio.openWritingPipe( 0xF0F0F0F0AA); // Отправить данные на этот 40-разрядный адрес
  myRadio.write(&data, sizeof(data)); 
//  delay(300);
}
