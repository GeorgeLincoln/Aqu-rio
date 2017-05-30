// Autor: George Lincoln
// Data: 10/05/2017
// Projeto Aquario -- beta

 void setup()
 {

  Serial.begin(9600);
 
 }
   
 void loop()
 {
  
   printTemp();
 
 }

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

  Serial.println(Thermister(analogRead(1)));
  
 }

 
