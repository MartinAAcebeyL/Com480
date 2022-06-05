#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>

//teclado
const byte ROWS = 2; 
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'}
};
byte rowPins[ROWS] = {6, 5};
byte colPins[COLS] = {4,3,2};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


/*
mando:
	0-> apaga todo
	1-> cortinas
    2-> puerta
    3-> l1
    4-> l2
    5 -> abre todo
    6 -> prende todo
*/
byte mando = 0;
//servo
Servo servoMotor;
Servo servoMotor1;
byte srv = 9;
byte srv1 = 8;
// led
byte led = 10;
byte led1 = 11;
//cortina
bool cortina = false;
//puerta
bool puerta = false;
//luz1
bool luz1 = false;
bool luz2 = false;

char key;

void setup(){ 
  Wire.begin(2);//Debe indicar el numero de eclaco que es
  Wire.onReceive(handler);
  Serial.begin(9600);
  servoMotor.attach(srv);
  servoMotor1.attach(srv1);
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  Wire.onRequest(requestEvent);
}

void loop(){
  if(mando != 0){
    key = keypad.getKey();
    if (key != NO_KEY){
      Serial.println(key);
      switch(key){
      	case '1':
          if(cortina){
              Serial.println("cortina cerrda");
            servoMotor.write(0);
          }else{
            Serial.println("cortina abierta");
            servoMotor.write(180);
          }
          //delay(1000);
           cortina = !cortina;
          break;
        case '2':
          if(puerta){
              Serial.println("puerta cerrda");
            servoMotor1.write(0);
          }else{
            Serial.println("puerta abierta");
            servoMotor1.write(180);
          }
           puerta = !puerta;
          break;
        case '3':
          if(luz1){
                Serial.println("luz 1 apagada");
              digitalWrite(led, LOW);
            }else{
              Serial.println("luz 1 prendida");
              digitalWrite(led, HIGH);
            }
             luz1 = !luz1;
            break;
        case '4':
          if(luz2){
                Serial.println("luz 2 apagada");
              digitalWrite(led1, LOW);
            }else{
              Serial.println("luz 2 prendida");
              digitalWrite(led1, HIGH);
            }
             luz2 = !luz2;
            break;
            case '5':
              digitalWrite(led, LOW);
              digitalWrite(led1, LOW);
              servoMotor1.write(0);
              servoMotor.write(0);
              luz2 = false;
              luz1 = false;
              puerta = false;
              cortina = false;
              break;
            case '6':
          digitalWrite(led, HIGH);
              digitalWrite(led1, HIGH);
              servoMotor1.write(180);
              servoMotor.write(180);
              luz2 = !false;
              luz1 = !false;
              puerta = !false;
              cortina = !false;
            break;
      }
    }
      
  }
}

void handler(int n){
  if(Wire.available()>0){
    mando = Wire.read();
    Serial.println(mando);
  }
}

void requestEvent() {
  Wire.write(key);
}
