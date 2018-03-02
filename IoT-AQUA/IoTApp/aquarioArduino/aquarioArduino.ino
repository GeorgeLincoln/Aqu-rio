// Autores: George Lincoln e Iesus Batista
// Data: 05/10/2017
// Projeto Aquario -- beta

//incluindo biblioteca para controles

#include <Servo.h>

#include <SPI.h>
#include "Adafruit_MAX31855.h"

#define MAXDO   10
#define MAXCS   11
#define MAXCLK  12

// initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

int val = 0;
//Criando um objeto da classe Servo
Servo motor;

char readBluetooth = ' ';
int Rele_Luz = 4;
int Rele_Aerador = 2; 
int buzzer = 3;
int pushButton = 12;
int buttonState;



///Configuração do Bluetooth segundo o aplicativo feito no AppInventor
void Bluetooth()
{
   if (Serial.available())
  {
    readBluetooth = Serial.read();
    
    if(readBluetooth == 'a')
      /// Iluminação Ligada
      digitalWrite(Rele_Luz, LOW);
    else if(readBluetooth == 'b')
      /// Iluminação Desligada
      digitalWrite(Rele_Luz, HIGH);
    else if (readBluetooth == 'c')
      ///ligando o servo motor
      ServAlimentador();
    else if(readBluetooth == 'd')
      /// Aerador Ligado
      digitalWrite(Rele_Aerador, LOW);
    else if(readBluetooth == 'e')
      /// Aerador Desligado
      digitalWrite(Rele_Aerador, HIGH);
  }  
}

///Configuração do angulo para o servo motor
void ServAlimentador()
{
  motor.write(0);
  val = 180;
  motor.write(val);
  delay(3000);
  val = 0;
  motor.write(val);
  delay(3000);
}

//Função Principal
void setup()
{
  ///serial comunicação na velocidadde de 9600 bits por segundo
  Serial.begin(9600);
  pinMode(Rele_Luz, OUTPUT);/// setando o relé como saída
  digitalWrite(Rele_Luz, HIGH);/// desligando o relé
  
    motor.attach(9);/// ligando o servo na porta 9
   
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  
  ///pinMode(buzzer,OUTPUT);
  delay(1); /// Atraso entre as leituras para a estabilidade
  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc

  //Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  pinMode(Rele_Aerador, OUTPUT);
  digitalWrite(Rele_Aerador, HIGH);
  delay(500);
}

//Loop Principal
void loop()
{

  Bluetooth();
  ///chamando funções para controle
  buttonState = digitalRead(pushButton);
  Serial.println(thermocouple.readCelsius());
 
}

