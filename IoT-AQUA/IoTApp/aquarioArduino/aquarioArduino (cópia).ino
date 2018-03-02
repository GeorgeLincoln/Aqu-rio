// Autores: George Lincoln e Iesus Batista
// Data: 05/10/2017
// Projeto Aquario -- beta

//incluindo biblioteca para controles
//#include <Stepper.h>
#include <virtuabotixRTC.h>
//#include "Servo.h"
#include <Servo.h>

int seg = 0;
int val = 0;
//Criando um objeto da classe Servo
Servo motor;
virtuabotixRTC myRTC(6, 7, 8);
char readBluetooth = ' ';
int rele = 4;
int buzzer = 3;
int pushButton = 2; // digital pin 2 has a pushbutton attached to it. Give it a name:
int buttonState;
double Temp;

// Configuração da temperatura
double Thermister(int aux)
{
  Temp = log(((10240000/aux) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * pow(Temp, 3)));
  
  Temp = 273.15 - Temp;  // Converter Kelvin em Celcius
  
  return Temp;// a temperatura é captada invertida
  
}

///Configuração do Bluetooth segundo o aplicativo feito no AppInventor
void Bluetooth()
{
   if (Serial.available())
  {
    readBluetooth = Serial.read();
    
    if(readBluetooth == 'a')
      /// Iluminação Ligada
      digitalWrite(rele, LOW);
    else if(readBluetooth == 'b')
      /// Iluminação Desligada
      digitalWrite(rele, HIGH);
    else if (readBluetooth == 'c')
      ///ligando o servo motor
      ServAlimentador();
   /* else if(readBluetooth == 'd')
       ///Ligando o alarme
      alarme(buttonState);
    else if(readBluetooth == 'e')
    {
      ///Desligando o alarme
      buttonState = digitalRead(1);
      ///Desligando o buzzer.
      digitalWrite(buzzer, LOW); 
    }*/
  }  
}

void printTemp()
{
  if(seg != myRTC.seconds){
  ///Serial.print("Temp: ");
  
  ///Serial.println(buttonState);
  ///Serial.print("Hora: ");
  ///Serial.print(myRTC.hours);
  ///Serial.print(":");
  ///Serial.print(myRTC.minutes);
  ///Serial.print(":");
  ///Serial.println(myRTC.seconds);
  seg = myRTC.seconds;
  }
}

///Configuração do tempo
void data()
{
  /// Armazena a data
  myRTC.updateTime(); 
  /// Verifica a hora e os minutos para manipular o relé 
 TempLed(myRTC.hours, myRTC.minutes);
  /// Verifica a hora e os minutos para manipular o servo motor
 /// TempAlimentador(myRTC.hours, myRTC.minutes);
}

///Configuração do tempo para a iluminação
void TempLed(int horas, int minutos)
{
    if(horas >= 19 && horas < 22)
        digitalWrite(rele, LOW);
        ///Serial.println("Ligado");
    else
      digitalWrite(rele, HIGH);
    ///Serial.println("Desligado");
}

///Configuração do tempo para o alimentador
/*void TempAlimentador(int horas, int minutos)
{
  motor.write(0);
  if(minutos == 0){
    if(horas == 7 || horas == 15 || horas == 23)
        ServAlimentador();
  }
/*    if(!minutos)
        if(horas == 19 || horas == 15 || horas == 23){
          Serial.print("Alimentando");
          ServAlimentador();
       }
}*/

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

//Função Alarme
void alarme(int estado)
{
    if (estado == 0){
    //Liga o buzzer
    digitalWrite(buzzer, HIGH); 
    delay(15);
  }else {
    //Desligando o buzzer.
    digitalWrite(buzzer, LOW);
    delay(15);
  }
}


//Função Principal
void setup()
{
    
  ///serial comunicação na velocidadde de 9600 bits por segundo
  Serial.begin(9600);
  pinMode(rele, OUTPUT);/// setando o relé como saída
  digitalWrite(rele, HIGH);/// desligando o relé
  
  motor.attach(9);/// ligando o servo na porta 9
  
  // (segundos, minutos, hora, dia da semana, dia do mes, mes, ano)
  myRTC.setDS1302Time(35, 43, 9, 6, 6, 9, 2017);
   
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  
  pinMode(buzzer,OUTPUT);
  delay(1); /// Atraso entre as leituras para a estabilidade
}

//Loop Principal
void loop()
{
  motor.write(0);
  Bluetooth();
  //delay(400);
  ///chamando funções para controle
  buttonState = digitalRead(pushButton);
  alarme(buttonState);
  Serial.println(Thermister(analogRead(0)));
  data();
}

