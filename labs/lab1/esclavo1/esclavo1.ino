#include <IRremote.hpp>

#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);
const byte control = 8;
byte cantidadAutenticados = 0;
byte cantidadAlarmas = 0;
byte estadoMensaje = 1;// false-> Autenticacion; true-> Cant Trabajadores

void setup()
{
  lcd.begin(16,2);//Define el tamaño de la pantalla lcd
  mensajeInicial();
  Serial.begin(9600);
  Wire.begin(1);//Debe indicar el numero de eclaco que es
  Wire.onReceive(handler);
  IrReceiver.begin(control);
}

void loop()
{
  
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume(); // Enable receiving of the next value
    if(IrReceiver.decodedIRData.decodedRawData == 0xF20DFF00){
      mostrarCantidadAlarmas();
      estadoMensaje = 3;
    }
    if(IrReceiver.decodedIRData.decodedRawData == 0xE916FF00){
      mensajeInicial();
      estadoMensaje = 1;
    }
    else
      if(IrReceiver.decodedIRData.decodedRawData == 0xE619FF00){
        mostrarCantidadTrabajadores();
        estadoMensaje = 2;
      }
  }
}

void handler(int cantidad){
  
  if(Wire.available()>0){
    char entrada = Wire.read();
    cantidadAutenticados = Wire.read();
    cantidadAlarmas = Wire.read();
    Serial.println(entrada);
    lcd.clear();
   
    if(estadoMensaje == 1){
      //Serial.println("123");
      if(entrada == '1'){
        Serial.println("123");
        lcd.setCursor(2,0);
        lcd.print("Autenticacion");
        lcd.setCursor(4,1);
        lcd.print("correcta");
      }
      else{
        Serial.println("456");
        lcd.setCursor(2,0);
        lcd.print("Autenticacion");
        lcd.setCursor(3,1);
        lcd.print("incorrecta");
      }
      delay(100000);
     mensajeInicial();
     //delay(8000);
    }
    if(estadoMensaje == 2){
      mostrarCantidadTrabajadores();
    }
    if(estadoMensaje == 3){
      mostrarCantidadAlarmas();
    }
  }

}

void mensajeInicial(){
  lcd.clear();
  lcd.setCursor(3,0);// Se situa en una determinada celda para escribir el mensaje
  lcd.print("Ingrese su");//Escribe el mensaje en la pantalla lcd
  lcd.setCursor(4,1);
  lcd.print("password");
}

void mostrarCantidadTrabajadores(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Trabajadores: ");
  lcd.setCursor(7,1);
  lcd.print(cantidadAutenticados);
}

void mostrarCantidadAlarmas(){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Alarmas: ");
  lcd.setCursor(7,1);
  lcd.print(cantidadAlarmas);
}
