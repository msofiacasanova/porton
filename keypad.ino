
#include <Servo.h>
#include <Keypad.h>
Servo ServoMotor;

//contraseña inicial
char passDigit1 = '1';
char passDigit2 = '2';
char passDigit3 = '3';

//digito ingresado
char usedPass1 = "";
char usedPass2 = "";
char usedPass3 = "";
int contador = 0;

//matriz del keypad
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = { 8, 7, 6, 9 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  Serial.begin(9600);
  ServoMotor.attach(11);
  LockedPosition(true);
}
void loop()
{
  char key = keypad.getKey(); //obtiene el digito ingresado
  if (key == '*' || key == '#')
  {
    Serial.println("Cerrar");
    contador = 0;
    LockedPosition(true);
    
  } else if (key == 'A') {
    passDigit1 = random(0, 9) + '0'; //+0 convierte entero a char
    passDigit2 = random(0, 9) + '0';
    passDigit3 = random(0, 9) + '0';
    Serial.print("digit1: ");
    Serial.println(passDigit1);
    Serial.print("digit2: ");
    Serial.println(passDigit2);
    Serial.print("digit3: ");
    Serial.println(passDigit3);
    contador = 0;
    
  } else if (key == 'B' || key == 'C' || key == 'D') {
    contador = 0;
    Serial.println("Reiniciar");
    
  } else if (contador == 0 && key != NULL){ //registra solo cuando se ingresa algo 
    usedPass1 = key;
    contador = contador + 1;
    Serial.println(usedPass1);
    
  } else if (contador == 1 && key != NULL) {
    usedPass2 = key;
    contador = contador + 1;
    Serial.println(usedPass2);
    
  } else if (contador == 2 && key != NULL) {
    usedPass3 = key;
    contador = contador + 1;
    Serial.println(usedPass3);
  }



  if (contador == 3 && usedPass1 == passDigit1 && usedPass2 == passDigit2 && usedPass3 == passDigit3) {
    Serial.println("Abrir");
    LockedPosition(false);
    contador = 0;
  }



  delay(50);
}
void LockedPosition(int locked)
{
  if (locked)
  {
    ServoMotor.write(11);

  }
  else
  {
    ServoMotor.write(90);
  }
}
