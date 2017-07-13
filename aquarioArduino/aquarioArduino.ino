// Autor: George Lincoln
// Data: 10/05/2017
// Projeto Aquario -- beta

#include <Stepper.h>
#include <virtuabotixRTC.h>
/// portas para o motor de passo
virtuabotixRTC myRTC(6, 7, 8);
  
 //Servo motor;
Stepper myStepper(500, 9, 10, 11, 12);
char readBluetooth = ' ';
int rele = 4;

/// Configuração da temperatura
double Thermister(int aux) 
{
  double Temp;
  Temp = log(((10240000/aux) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * pow(Temp, 3)));
  Temp = 273.15 - Temp;  // Converter Kelvin em Celcius
  return Temp;// a temperatura é captada invetida
  
}

void printTemp()
{
  Serial.println(Thermister(analogRead(0)));
  delay(300);
}

///Configuração do tempo
void data()
{
  /// Armazena a data 
  myRTC.updateTime(); 
  /// Verifica a hora e os minutos para manipular o relé
  TempLed(myRTC.hours, myRTC.minutes);
  /// Verifica a hora e os minutos para manipular o motor 5V
  TempAlimentador(myRTC.hours, myRTC.minutes);
}

///Configuração do tempo da iluminação
void TempLed(int horas, int minutos)
{
     if(!minutos)
        digitalWrite(rele, (horas == 19? LOW : (horas == 22 ? HIGH : LOW)));
     
}

///Configuração do tempo do alimentador
void TempAlimentador(int horas, int minutos)
{
     if(!minutos)
       if(horas == 7 || horas == 15 || horas == 23)
          alimentador();
}

void alimentador()
{
  int i;
  for(i = 0; i < 40000; i++)///2000 = 360 graus
      //Gira o motor no sentido anti-horario
      myStepper.step(-1);

  delay(500);
}

///Configuração do Bluetooth segundo o aplicativo
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
      /// Liga o motor de passo
    else if (readBluetooth == 'c')
      alimentador();    
  }  
}

//Função Principal
void setup()
{
  Serial.begin(9600);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH);
  /// velocidade do motor(alimentador)
  myStepper.setSpeed(50);
  // (segundos, minutos, hora, dia da semana, dia do mes, mes, ano)
  myRTC.setDS1302Time(54, 22, 9, 3, 11, 6, 2017);

}
//Loop Principal
void loop()
{
  printTemp();
  Bluetooth();
  data();

}



