#include <Keypad.h>

#include <Wire.h>


const byte led = 11;
const byte piezo = 12;
const byte pulsador = 10;
const byte ROWS = 4; // cuatro filas
const byte COLS = 4; // cuatro columnas
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // conexion de las filas a los pines del arduino
byte colPins[COLS] = {5, 4, 3, 2}; // conexion de las columnas a los pines del arduino
String password = "";
String listaPassword[5] = {"123", "456", "789", "147", "258"};
bool estadoPassword = 0; // 0-> Contraseña incorrecta 1-> Contraseña correcta
byte contadorErrores = 0;
byte autenticacionCorrecta = 0;
byte alarmasActivadas = 0;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
// hpps
void setup()
{
  pinMode(led, OUTPUT);
  pinMode(piezo, OUTPUT);
  Serial.begin(9600);
  pinMode(pulsador, INPUT_PULLUP);
  Wire.begin();
}

void loop()
{
  char key = keypad.getKey();

  if (key != NO_KEY)
  {
    if (key == '#')
    {
      Serial.println(password);
      for (byte i = 0; i < 5; i++)
      {
        //       / Serial.println(listaPassword[i]);
        if (password == listaPassword[i])
        {
          Serial.println("Correcto");
          autenticacionCorrecta++;
          Wire.beginTransmission(1); // Conecte al esclavo 1
          Serial.println('1');
          Wire.write('1');           // Envie el caracter 1, al esclavo
          Wire.write(autenticacionCorrecta);
          
          Wire.write(alarmasActivadas);
          Wire.endTransmission(); // Finaliza la comunicacion con el esclavo
          contadorErrores = 0;
          estadoPassword = 1;
          break;
        }
      }
      if (estadoPassword == 0)
      {
        Serial.println("Incorrecto");
        Wire.beginTransmission(1);
        Wire.write('0');
        Wire.write(autenticacionCorrecta);
        Wire.write(alarmasActivadas); 
        Wire.endTransmission();
        contadorErrores++;
      }
      password = "";
      estadoPassword = 0;
    }
    else
    {
      Serial.println(key);
      password = password + key;
    }
  }
  if (contadorErrores == 3)
  {
    contadorErrores++;
    alarmasActivadas++;
    Wire.beginTransmission(1);
    Wire.write('0');
    Wire.write(autenticacionCorrecta);
    Wire.write(alarmasActivadas);
    Wire.endTransmission();
    activarAlarma();
  }
  if (digitalRead(pulsador) == 0)
  {
    delay(250);
    contadorErrores = 0;
    apagarAlarma();
  }
}

void activarAlarma()
{
  digitalWrite(led, HIGH);
  tone(piezo, 2000); // 31 - 35532
}
void apagarAlarma()
{
  digitalWrite(led, LOW);
  noTone(piezo);
}
