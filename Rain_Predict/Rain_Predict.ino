#include "dht.h"
#include <LiquidCrystal.h>
#define dht_apin A0 //  DHT Sensor
#define LDRpin A5 // LDR resistor
#define buzzer 7
dht DHT;
float LDRValue = 0.0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){

  lcd.begin(16, 2);

  pinMode(buzzer,OUTPUT);
  
  Serial.begin(9600);
  Serial.println("DHT11 Humidity & temperature Sensor\n");
  delay(1000);
 
}


void loop(){
 
    DHT.read11(dht_apin);

    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  \n");
    LDRValue = (float)analogRead(LDRpin);
     
    Serial.println(LDRValue); 
    float Humidity = DHT.humidity;
    float Temperature = DHT.temperature;
    float Light = LDRValue;
    delay(1000);
    int possibility;
    if(Humidity  > 70.0)
      if(Temperature >= -4.0 && Temperature < 10)
        if(Light < 500) possibility = 3;
        else if(Light < 700) possibility = 2;
        else if(Light < 800) possibility = 1;
        else if(Light < 1000) possibility = 0;
        else possibility = -1;
      else if(Temperature >= 10 && Temperature < 23)
        if(Light < 500) possibility = 4;
        else if(Light < 700) possibility = 3;
        else if(Light < 800) possibility = 2;
        else if(Light < 1000) possibility = 1;
        else possibility = 0;
      else if(Temperature >=23 && Temperature < 30)
        if(Light < 500) possibility = 5;
        else if(Light < 700) possibility = 4;
        else if(Light < 800) possibility = 3;
        else if(Light < 1000) possibility = 1;
        else possibility = 0;
      else if(Temperature >=30)
        if(Light < 500) possibility = 5;
        else if(Light < 700) possibility = 4;
        else if(Light < 800) possibility = 3;
        else if(Light < 1000) possibility = 1;
        else possibility = 0;
    else if(Humidity <= 65.0) possibility = 0;
    
    lcd.setCursor(0, 0);

    switch (possibility){
      case -1:
        Serial.print("There is no possibility of rain \n");
        lcd.print("no chance");
        delay(2000);
        showdata(Humidity,Temperature,Light);
        break;
      case 0:
        Serial.print("There is a very low possibility of rain \n");
        lcd.print("very low chance");
        delay(2000);
        showdata(Humidity,Temperature,Light);
        break;
      case 1:
        Serial.print("There is a low possibility of rain \n");
        lcd.print("low chance");
        delay(2000);
        showdata(Humidity,Temperature,Light);
        break;
      case 2:
        Serial.print("There is a slight chance of rain \n");
        lcd.print("slight chance");
        delay(2000);
        showdata(Humidity,Temperature,Light);
        break;
      case 3:
        Serial.print("There is moderate chance of rain \n");
        lcd.print("moderate chance");
        delay(2-000);
        showdata(Humidity,Temperature,Light);
        break;
      case 4:
        Serial.print("There is a high possibility of rain \n");
        lcd.print("high chance ");
        delay(200);
        showdata(Humidity,Temperature,Light);
        digitalWrite(buzzer,3);
        delay(200);
        digitalWrite(buzzer,0);
        break;
      case 5:
        Serial.print("There is a very high possibility of rain \n");
        lcd.print("very high chance");
        delay(200);
        showdata(Humidity,Temperature,Light);
        digitalWrite(buzzer,3);
        delay(200);
        digitalWrite(buzzer,0);
    }

 return;
}

void showdata(float humidity,float temperature,float light)
{
  String y="Hum   Temp  Lig";
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print(y);
  
  lcd.setCursor(0,1);
  String g="";
  g=g+humidity+" ";
  g=g+temperature+" ";
  g=g+light+" ";
  lcd.print(g);
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");

}

