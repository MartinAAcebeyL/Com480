#include <Wire.h>

#include <LiquidCrystal.h>
#include <IRremote.h>

LiquidCrystal lcd(2,3,4,5,6,7);
const byte control = 8;
const byte led = 9;
bool estado_sis = false;
void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  IrReceiver.begin(control);
  Wire.begin();
  pinMode(led, OUTPUT);
  mensajeApagado();
  
}

void loop(){
  if (IrReceiver.decode()) {
    //Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume();
    if(IrReceiver.decodedIRData.decodedRawData == 0xBF40FF00){
//        lcd.clear();
      IrReceiver.resume();
    	estado_sis= !estado_sis;
      //Serial.println(estado_sis);
      mensajePrendido();
      
    }
    if(estado_sis == true){
      //Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      	IrReceiver.resume();
      	//
      if(IrReceiver.decodedIRData.decodedRawData == 0xAD52FF00){
      	//0
        mostrarGrupo("0");
        Wire.beginTransmission(1);//Conecte al esclavo 1
        Wire.write('0');//Envie el caracter 1, al esclavo
        Wire.endTransmission();//Finaliza la comunicacion con el esclavo
      }
      if(IrReceiver.decodedIRData.decodedRawData == 0xE916FF00){
      	//1
        mostrarGrupo("1");
        Wire.beginTransmission(1);//Conecte al esclavo 1
        Wire.write('1');//Envie el caracter 1, al esclavo
        Wire.endTransmission();//Finaliza la comunicacion con el esclavo
      }
      if(IrReceiver.decodedIRData.decodedRawData == 0xE619FF00){
      	//2
        mostrarGrupo("2");
        Wire.beginTransmission(1);//Conecte al esclavo 1
        Wire.write('2');//Envie el caracter 1, al esclavo
        Wire.endTransmission();//Finaliza la comunicacion con el esclavo
      }
      if(IrReceiver.decodedIRData.decodedRawData == 0xF20DFF00){
      	//3
        mostrarGrupo("3");
        Wire.beginTransmission(1);//Conecte al esclavo 1
        Wire.write('3');//Envie el caracter 1, al esclavo
        Wire.endTransmission();//Finaliza la comunicacion con el esclavo
      }
      if(IrReceiver.decodedIRData.decodedRawData == 0xF30CFF00){
      	//4
        mostrarGrupo("4");
        Wire.beginTransmission(1);//Conecte al esclavo 1
        Wire.write('4');//Envie el caracter 1, al esclavo
        Wire.endTransmission();//Finaliza la comunicacion con el esclavo
      }
      
      	
      
    }else if(estado_sis == false){
      	mensajeApagado();
      	Wire.beginTransmission(1);//Conecte al esclavo 1
        Wire.write('9');//Envie el caracter 1, al esclavo
        Wire.endTransmission();
    }
    IrReceiver.resume();
  }
  
}

void mensajeApagado(){

  lcd.setCursor(2,0);// Se situa en una determinada celda para escribir el mensaje
  lcd.print("Sis. Apagado");//Escribe el mensaje en la pantalla lcd
  lcd.setCursor(4,1);
  lcd.print("Grupo 0");
  digitalWrite(led, LOW);
}

void mensajePrendido(){

  lcd.setCursor(2,0);// Se situa en una determinada celda para escribir el mensaje
  lcd.print("Sis. Prendido");//Escribe el mensaje en la pantalla lcd
  lcd.setCursor(4,1);
  lcd.print("Grupo 0");
  digitalWrite(led, HIGH);
}

void mostrarGrupo(String num){
  lcd.clear();
  lcd.setCursor(2,0);// Se situa en una determinada celda para escribir el mensaje
  lcd.print("Sis. Prendido:");//Escribe el mensaje en la pantalla lcd
  Serial.println(num);
  String grupo = "Grupo: " + num; 
  lcd.setCursor(2,1);
  lcd.print(grupo);
  digitalWrite(led, HIGH);
}
