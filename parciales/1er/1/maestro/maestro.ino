#include <Wire.h>
#include <Keypad.h>

//teclado
const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const byte led = 10;
const byte pulsador = 11;
const byte piezo = 12;
byte sound = 12;

//varialbes globales
String pass = "";
String pass_default = "123";
byte contadorErrores = 0;
bool login = false;

void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(pulsador, INPUT_PULLUP);
  Wire.begin();
}

void loop(){
  if(login == true){
      	Wire.requestFrom(2, 1);
    	
    if(Wire.available()){
      char c = Wire.read();
        
          switch(c){
          	case '1':
             Wire.beginTransmission(1);//Conecte al esclavo 1
          	Wire.write('2');//Envie el caracter 1, al esclavo
          	Wire.endTransmission();//Finaliza la comunicacion con el esclavo
            	break;
            case '2':
             Wire.beginTransmission(1);//Conecte al esclavo 1
          	Wire.write('3');//Envie el caracter 1, al esclavo
          	Wire.endTransmission();//Finaliza la comunicacion con el esclavo
            	break;
            case '3':
             Wire.beginTransmission(1);//Conecte al esclavo 1
          	Wire.write('4');//Envie el caracter 1, al esclavo
          	Wire.endTransmission();//Finaliza la comunicacion con el esclavo
            	break;
              case '4':
             Wire.beginTransmission(1);//Conecte al esclavo 1
            Wire.write('5');//Envie el caracter 1, al esclavo
            Wire.endTransmission();//Finaliza la comunicacion con el esclavo
              break;
              case '5':
             Wire.beginTransmission(1);//Conecte al esclavo 1
            Wire.write('6');//Envie el caracter 1, al esclavo
            Wire.endTransmission();//Finaliza la comunicacion con el esclavo
              break;
              case '6':
             Wire.beginTransmission(1);//Conecte al esclavo 1
            Wire.write('7');//Envie el caracter 1, al esclavo
            Wire.endTransmission();//Finaliza la comunicacion con el esclavo
              break;
          }
    }   
  }
  if(login == false){
  	loguearse();
  }
  
}

void loguearse(){
	char key = keypad.getKey();

  if (key != NO_KEY){
    tone(sound, 350, 35);
    if(key == 'D'){
        if(pass == pass_default){
          tone(sound, 500, 100);
          Serial.println("Correcto");
          login = true;
          Wire.beginTransmission(1);//Conecte al esclavo 1
          Wire.write('1');//Envie el caracter 1, al esclavo
          Wire.endTransmission();//Finaliza la comunicacion con el esclavo
          Wire.beginTransmission(2);
          Wire.write(1);
          Wire.endTransmission();
        }
      
      if(pass != pass_default){
        tone(sound, 70, 100);
        Serial.println("Incorrecto");
        contadorErrores++;
        pass = "";
        Wire.beginTransmission(1);
        Wire.write('0');
        Wire.endTransmission();
         Wire.beginTransmission(2);
        Wire.write(0);
        Wire.endTransmission();
      }
    }else{
      pass += key;
      Serial.println(pass);
    }
  }
  //cuando llegue 3 errores suena la alarma
  if(contadorErrores == 3){
    activarAlarma();
  }
  //para apagar la alarma
  if(digitalRead(pulsador) == 0){
    delay(250);
    contadorErrores = 0;
    apagarAlarma();
  }
}

void activarAlarma(){
  digitalWrite(led, HIGH);
  tone(piezo, 2000); //31 - 35532
}

void apagarAlarma(){
  digitalWrite(led, LOW);
  noTone(piezo);
}
