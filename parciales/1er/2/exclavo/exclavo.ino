#include <Wire.h>
#include <Keypad.h>

const byte ROWS = 1;//cuatro filas
const byte COLS = 3; //cuatro columnas
char keys[ROWS][COLS] = {
  {'1','2','3'}
};
byte rowPins[ROWS] = {8}; //conexion de las filas a los pines del arduino
byte colPins[COLS] = {9,10,11}; //conexion de las columnas a los pines del arduino
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const byte leds1 = 3;
const byte leds2 = 5;
const byte leds3 = 6;

bool teclas = false;
byte grupo = 0;
char key;
void setup(){
  pinMode(leds1, OUTPUT);
  pinMode(leds2, OUTPUT);
  pinMode(leds3, OUTPUT);
  Wire.begin(1);//Debe indicar el numero de eclaco que es
  Wire.onReceive(handler);
  Serial.begin(9600);
}

void loop(){
  key = keypad.getKey();
  if(grupo == 0){
  	apagar();
  }
  if(key!=NO_KEY){
    
    if(grupo == 1){
      Serial.println(grupo);
    	luminosidad(3);
    }
    if(grupo == 2){
    	luminosidad(5);
    }
    if(grupo == 3){
    	luminosidad(6);
    }
    if(grupo == 4){
    	luminosidad4();
    }
  }
}

void handler(int cant){
  if(Wire.available()>0){
    apagar();
    char entrada = Wire.read();
    Serial.println(entrada);
    if(entrada == '0' || entrada == '9'){
      grupo = 0;
      //luminosidad(0);
    }
    if(entrada == '1'){
      grupo = 1;
      //luminosidad(1);
    }
    if(entrada == '2'){
      grupo = 2;
      //luminosidad(2);
    }
    if(entrada == '3'){
      grupo = 3;
      //luminosidad(3);
    }
    if(entrada == '4'){
      grupo = 4;
      //luminosidad4();
    }
  }
  Serial.println(grupo);
}

void luminosidad(byte pin){
  if(key == '1'){
    Serial.println(11);
    analogWrite(pin, 0);
  }
  if(key == '2'){
    Serial.println(22);
    analogWrite(pin, 130);
  }
  if(key == '3'){
    Serial.println(33);
    analogWrite(pin, 255);
  }
}

void luminosidad4(){
  if(key == '1'){
    analogWrite(3, 0);
    analogWrite(5, 0);
    analogWrite(6, 0);
  }
  if(key == '2'){
    analogWrite(3, 130);
    analogWrite(5, 130);
    analogWrite(6, 130);
  }
  if(key == '3'){
    analogWrite(3, 255);
    analogWrite(5, 255);
    analogWrite(6, 255);
  }
}

void apagar(){
	analogWrite(3, 0);
    analogWrite(5, 0);
    analogWrite(6, 0);
}
