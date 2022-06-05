#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);

void setup(){
  Wire.begin(1);//Debe indicar el numero de eclaco que es
  Wire.onReceive(handler);
  lcd.begin(16,2);
  Serial.begin(9600);
  mensaje_sis();
}

void loop(){
	
}

void handler(int n){
  if(Wire.available() == 1){
    char tipo_orden = Wire.read();//del ascensor o cuarto('A' o 'C')
    Serial.println(tipo_orden);
    if(tipo_orden == '1'){
      login("Correcta");
    }else if(tipo_orden == '0'){
      login("Incorrecta");
    }else if(tipo_orden == '2'){
      mensajes_cuarto(1);
    }else if(tipo_orden == '3'){
      mensajes_cuarto(2);
    }else if(tipo_orden == '4'){
      mensajes_cuarto(3);
    } else if(tipo_orden == '5'){
      mensajes_cuarto(4);
    } else if(tipo_orden == '6'){
      mensajes_cuarto(5);
    } else if(tipo_orden == '7'){
      mensajes_cuarto(6);
    } 
  }
}



void login(String tipo){
  	lcd.clear();
	lcd.setCursor(2,0);
    lcd.print("Autenticacion");
    lcd.setCursor(3,1);
    lcd.print(tipo);
    for(int posicion = 0; posicion < 16; posicion++){
      lcd.scrollDisplayLeft(); 
      delay(8000);
    }
    for(int posicion = 0; posicion < 32; posicion++){
      lcd.scrollDisplayRight(); 
      delay(8000); 
    }
  	for(int posicion = 0; posicion < 16; posicion++){
      lcd.scrollDisplayLeft(); 
      delay(8000);
    }
}

void mensaje_sis(){
lcd.clear();
  lcd.setCursor(3,0);// Se situa en una determinada celda para escribir el mensaje
  lcd.print("Edificio: ");//Escribe el mensaje en la pantalla lcd
  lcd.setCursor(3,1);
  lcd.print("Compilado");
}
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
void mensajes_cuarto(byte i){
  switch(i){
    case 0:
    	lcd.clear();
  		lcd.setCursor(3,0);
  		lcd.print("Apagado");//Escribe el mensaje en la pantalla lcd
    	break;
    case 1:
    	lcd.clear();
  		lcd.setCursor(3,0);
  		lcd.print("Cortinas");//Escribe el mensaje en la pantalla lcd
    	break;
    case 2:
    	lcd.clear();
  		lcd.setCursor(3,0);// Se situa en una determinada celda para escribir el mensaje
  		lcd.print("Puerta");//Escribe el mensaje en la pantalla lcd
    	break;
    case 3:
    	lcd.clear();
  		lcd.setCursor(3,0);// Se situa en una determinada celda para escribir el mensaje
  		lcd.print("Luz 1");//Escribe el mensaje en la pantalla lcd
    	break;
    case 4:
    	lcd.clear();
  		lcd.setCursor(3,0);// Se situa en una determinada celda para escribir el mensaje
  		lcd.print("Luz 2");//Escribe el mensaje en la pantalla lcd
    	break;
    case 5:
    	lcd.clear();
  		lcd.setCursor(3,0);// Se situa en una determinada celda para escribir el mensaje
  		lcd.print("apagando");//Escribe el mensaje en la pantalla lcd
    	break;
    case 6:
    	lcd.clear();
  		lcd.setCursor(2,0);// Se situa en una determinada celda para escribir el mensaje
  		lcd.print("prendiendo");//Escribe el mensaje en la pantalla lcd
    	break;
  }
  delay(1000);
 // mensaje_sis();
}
