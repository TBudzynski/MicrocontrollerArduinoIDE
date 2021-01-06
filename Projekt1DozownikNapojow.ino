  #include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <OneWire.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#define Temp 6
#define trigPIN 4
#define echoPIN 5
#define LED_B 10
#define LED_G 12
#define LED_R 11
#define LED_Y 8
#define guzik1 2   
#define guzik2 9 
#define pompka2 13 
#define guzik3 3

unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzas = 0;
unsigned long roznicaCzas = 0;

OneWire oneWire(Temp);
DallasTemperature sensors(&oneWire);
void setup() {
  lcd.init();
  lcd.backlight();
//  lcd.setCursor(0,1);
//  lcd.print("");
 
 
  Serial.begin(9600);
  pinMode(trigPIN, OUTPUT);
  pinMode(echoPIN, INPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(pompka2 , OUTPUT);
  pinMode(guzik1, INPUT_PULLUP);
  pinMode(guzik2, INPUT_PULLUP);
  pinMode(guzik3,INPUT_PULLUP);
digitalWrite(LED_Y,HIGH);
digitalWrite(pompka2,HIGH);
}
int dystans;
int czas;
bool czyGuzikWcisniety = false;
float temperature;

void loop() {
  startMenuDisplay();
  pomiarOdleglosci();
  pomiarTemp();
  /*
lcd.setCursor(0,0);
 lcd.print("Please,push");
 lcd.setCursor(1,1);
 lcd.print("button");
 */
 /*
lcd.setCursor(0,0);
lcd.print("temp C:");
lcd.print(sensors.getTempCByIndex(0));
lcd.setCursor(1,1);
lcd.print("dystans[cm]:");
lcd.print(dystans);
*/
  /*
     aktualnyCzas = millis();
    roznicaCzas = aktualnyCzas - zapamietanyCzas;

    //Jeśli różnica wynosi ponad sekundę
    if (roznicaCzas >= 1000UL) {
      //Zapamietaj aktualny czas
      zapamietanyCzas = aktualnyCzas;
      //Wyslij do PC
      Serial.println(aktualnyCzas);
    }
  */

  if (digitalRead(guzik1) == LOW)
  {
 //   wypisz();
    Serial.println("guzik1  wcisniety");
    obslugazbiornika1(dystans,temperature);
  }
  if (digitalRead(guzik2) == LOW)
  {
    resetowanieUkladu();
  }
  if (digitalRead(guzik3) == LOW)
  {
     Serial.println("guzik2  wcisniety");
    obslugaZbiornika2(dystans, temperature);
  }

}


float pomiarTemp()
{
  sensors.requestTemperatures();
 temperature = sensors.getTempCByIndex(0);
 return temperature;
}

int pomiarOdleglosci()
{
  digitalWrite(trigPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPIN, LOW);
  czas = pulseIn(echoPIN, HIGH);
  dystans = czas / 58;
  Serial.println(dystans);
  Serial.print("cm");

  return dystans;
}


void obslugazbiornika1(int dystans,float temperature)
{
  if (dystans > 0 && dystans < 8)
  {
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_Y, HIGH);
     digitalWrite(pompka2,HIGH);
    
    lcd.setCursor(0,0);
    lcd.print("temp C:    co1");
    lcd.print(sensors.getTempCByIndex(0));
    lcd.setCursor(0,1);
    lcd.print("Glass full.  co1  ");
  }
  if (dystans >= 11  && dystans <= 13)
  {
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_Y,LOW);
    digitalWrite(pompka2,LOW);
    lcd.setCursor(0,0);
    lcd.print("temp C:  ");
    lcd.print(sensors.getTempCByIndex(0));
    lcd.setCursor(0,1);
    lcd.print("Glass half full. co1");
  }
  if (dystans > 13 )
  {
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_Y, LOW);
    digitalWrite(pompka2,HIGH);
    lcd.setCursor(0,0);
    lcd.print("temp C:  ");
    lcd.print(sensors.getTempCByIndex(0));
    lcd.setCursor(0,1);
    lcd.print("Glass empty.    ");
  }
}


void resetowanieUkladu()
{
  lcd.setCursor(0,0);
  lcd.print("Thank you        ");
  lcd.setCursor(0,1);
  lcd.print("                 ");
  digitalWrite(guzik1, HIGH);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_Y, HIGH);
  digitalWrite(pompka2,HIGH);
}

/*
  int pomiarCzasu()
  {
  aktualnyCzas=millis();
  if(aktualnyCzas-zapamietanyCzas>1000UL)
  {
    zapamietanyCzas=aktualnyCzas;
    return aktualnyCzas;
  }
  }
*/


void startMenuDisplay()
  {
    if(digitalRead(guzik1)==HIGH && digitalRead(guzik3)==HIGH && digitalRead(guzik2)==HIGH)
    {
   lcd.setCursor(0,0);
   lcd.print("Wybierz napoj     ");
   lcd.setCursor(0,1);
   lcd.print("1-sok 3-woda       ");
    }
  }
 void obslugaZbiornika2(int dystans,float temperature)
 {
   if (dystans > 0 && dystans < 10)
  {
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_Y,HIGH);
    lcd.setCursor(0,0);
    lcd.print("temp C:    ");
    lcd.print(sensors.getTempCByIndex(0));
    lcd.setCursor(0,1);
    lcd.print("Glass full.  co2     ");
  }
  if (dystans >= 10 && dystans <= 13)
  {
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_Y, LOW);
    lcd.setCursor(0,0);
    lcd.print("temp C:  ");
    lcd.print(sensors.getTempCByIndex(0));
    lcd.setCursor(0,1);
    lcd.print("Glass half full. ");
  }
  if (dystans > 13 )
  {
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_Y,LOW);
    lcd.setCursor(0,0);
    lcd.print("temp C:  ");
    lcd.print(sensors.getTempCByIndex(0));
    lcd.setCursor(0,1);
    lcd.print("Glass empty.    ");
  }
 
  }
