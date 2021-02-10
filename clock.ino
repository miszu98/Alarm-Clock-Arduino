#include "RTClib.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int odczyt = 0;
int index = 0;
int index_alarm = 0;
int index_petla = 0;
int alarm_godzina = 1;
int alarm_minuty = 1;
int alarm_sekundy = 0;
int alarm_dzien = 1;
int alarm_miesiac = 1;
int alarm_rok = 2020;
int alarm_licznik = 0;
int buzzer = 11;
int stan_alarm = 0;


int dodaj = 6;
int odejmij = 7;
int select = 9;
int buttonPin = 5;
int button1Pin = 4;


void setup () 
{
  lcd.begin();
  pinMode(buzzer, OUTPUT);
  pinMode(dodaj, INPUT_PULLUP);
  pinMode(odejmij, INPUT_PULLUP);
  pinMode(select, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(button1Pin, INPUT_PULLUP);
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () 
{

    odczyt = analogRead(A0);
    DateTime now = rtc.now();
    String minuty(now.minute());
    String sekundy(now.second());
    String godziny(now.hour());
    if (sekundy.length() == 1){
      sekundy = '0'+String(sekundy);
    }
    else if(minuty.length() == 1){
      minuty = '0'+String(minuty);
    }
    else if(godziny.length() == 1){
      godziny = '0'+String(godziny);
    }
   

    if (digitalRead(odejmij) == HIGH){ //zaprogramowanie przycisku right
      index_alarm = index_alarm + 1;
      delay(500);
      if (index_alarm > 5) index_alarm = 0;}

    else if (digitalRead(dodaj)== HIGH){ //zaprogramowanie przycisku left
      index_alarm = index_alarm - 1;
      delay(500);
      if (index_alarm < 0) index_alarm = 5;
       }
    else if (digitalRead(select)==HIGH){ //zaprogramowanie przycisku select
      index = index + 1;
      delay(500);
      if (index > 3) index = 0;
      }
    
    else if (index_alarm == 3 && index == 2){ //ustawianie godziny alarmu

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(alarm_godzina);
    lcd.print(':');
    lcd.print(minuty);
    lcd.print(':');
    lcd.print(sekundy);
    lcd.print("  ");

    lcd.setCursor(0, 0);
    lcd.print(alarm_dzien);
    lcd.print('/');
    lcd.print(alarm_miesiac);
    lcd.print('/');
    lcd.print(alarm_rok);
    delay(100);
      
      if (digitalRead(buttonPin)==HIGH){
        delay(50);
        alarm_godzina = alarm_godzina + 1;
        delay(50);
        if (alarm_godzina > 24) alarm_godzina = 1;}
      else if (digitalRead(button1Pin)==HIGH){
        delay(50);
        alarm_godzina = alarm_godzina - 1;
        delay(50);
        if (alarm_godzina < 1) alarm_godzina = 24;}
    }
    
    else if (index_alarm == 4 && index == 2){ //ustawianie minut alarmu

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(alarm_godzina);
    lcd.print(':');
    lcd.print(alarm_minuty);
    lcd.print(':');
    lcd.print(sekundy);
    lcd.print("  ");

    lcd.setCursor(0, 0);
    lcd.print(alarm_dzien);
    lcd.print('/');
    lcd.print(alarm_miesiac);
    lcd.print('/');
    lcd.print(alarm_rok);
    delay(100);
    
      if (digitalRead(buttonPin)==HIGH){
        delay(50);
        alarm_minuty = alarm_minuty + 1;
        delay(50);
        if (alarm_minuty > 59) alarm_minuty = 0;}
      else if (digitalRead(button1Pin)==HIGH){
        delay(50);
        alarm_minuty = alarm_minuty - 1;
        delay(50);
        if (alarm_minuty < 1) alarm_minuty = 59;
      }
      
    }
     else if (index_alarm == 5 && index == 2){ //ustawianie sekund alarmu

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(alarm_godzina);
    lcd.print(':');
    lcd.print(alarm_minuty);
    lcd.print(':');
    lcd.print(alarm_sekundy);
    lcd.print("  ");

    lcd.setCursor(0, 0);
    lcd.print(alarm_dzien);
    lcd.print('/');
    lcd.print(alarm_miesiac);
    lcd.print('/');
    lcd.print(alarm_rok);
    delay(100);
    
      if (digitalRead(buttonPin)==HIGH){
        delay(50);
        alarm_sekundy = alarm_sekundy + 1;
        delay(50);
        if (alarm_sekundy > 59) alarm_sekundy = 0;}
      else if (digitalRead(button1Pin)==HIGH){
        delay(50);
        alarm_sekundy = alarm_sekundy - 1;
        delay(50);
        if (alarm_sekundy < 0) alarm_sekundy = 59;
      }
      
    }
      

     
     else if (index_alarm == 0 && index == 2){  //ustawianie dnia alarmu
    
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(godziny);
    lcd.print(':');
    lcd.print(minuty);
    lcd.print(':');
    lcd.print(sekundy);
    lcd.print("  ");

    lcd.setCursor(0, 0);
    lcd.print(alarm_dzien);
    lcd.print('/');
    lcd.print(now.month());
    lcd.print('/');
    lcd.print(now.year());
    delay(100);
    
      if (digitalRead(buttonPin)==HIGH){
        delay(50);
        alarm_dzien = alarm_dzien + 1;
        delay(50);
        if (alarm_dzien > 31) alarm_dzien = 1;}
        
      else if (digitalRead(button1Pin)==HIGH){
        delay(50);
        alarm_dzien = alarm_dzien - 1;
        delay(50);
        if (alarm_dzien < 1) alarm_dzien = 31;
      }
      
    }
     else if (index_alarm == 1 && index == 2){ //ustawianie miesiaca alarmu

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(godziny);
    lcd.print(':');
    lcd.print(minuty);
    lcd.print(':');
    lcd.print(sekundy);
    lcd.print("  ");

    lcd.setCursor(0, 0);
    lcd.print(alarm_dzien);
    lcd.print('/');
    lcd.print(alarm_miesiac);
    lcd.print('/');
    lcd.print(now.year());
    delay(100);
    
      if (digitalRead(buttonPin)==HIGH){
        delay(50);
        alarm_miesiac = alarm_miesiac + 1;
        delay(50);
        if (alarm_miesiac > 12) alarm_miesiac = 1;}
        
      else if (digitalRead(button1Pin)==HIGH){
        delay(50);
        alarm_miesiac = alarm_miesiac - 1;
        delay(50);
        if (alarm_miesiac < 1) alarm_miesiac = 12;
      }
      
    }
     else if (index_alarm == 2 && index == 2){ //ustawianie roku alarmu

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(godziny);
    lcd.print(':');
    lcd.print(minuty);
    lcd.print(':');
    lcd.print(sekundy);
    lcd.print("  ");

    lcd.setCursor(0, 0);
    lcd.print(alarm_dzien);
    lcd.print('/');
    lcd.print(alarm_miesiac);
    lcd.print('/');
    lcd.print(alarm_rok);
    delay(100);
    
      if (digitalRead(buttonPin)==HIGH){
        delay(50);
        alarm_rok = alarm_rok + 1;
        delay(50);
        }
      else if (digitalRead(button1Pin)==HIGH){
        delay(50);
        alarm_rok = alarm_rok - 1;
        delay(50);
      }
      
    }
   
    if (index == 0){
 
    lcd.setCursor(0, 1);
    lcd.print(godziny);
    lcd.print(':');
    lcd.print(minuty);
    lcd.print(':');
    lcd.print(sekundy);
    lcd.print("  ");

    lcd.setCursor(0, 0);
    lcd.print(now.day());
    lcd.print('/');
    lcd.print(now.month());
    lcd.print('/');
    lcd.print(now.year());
    delay(100);
    
    lcd.setCursor(10,1);
    clock.forceConversion();
    lcd.print(clock.readTemperature()); lcd.print("C");
   
    }
    
    else if (index == 1 ){
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Yes - select");
    lcd.setCursor(0, 0);
    lcd.print("Set alarm?");
    delay(100);
    }

    else if (index == 3){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alarm set");
    lcd.setCursor(0, 1);
    lcd.print("Press select");
    delay(100);
 
    }

   delay(50);
    
    if (index == 0){
    if(now.hour() == alarm_godzina && now.minute() == alarm_minuty && now.second() == alarm_sekundy && now.day() == alarm_dzien && now.month() == alarm_miesiac && now.year() == alarm_rok){
      stan_alarm = 1;
      Alarm();
      }
    
      }
  
}         
  
void Alarm(){
  while (stan_alarm == 1){
  tone(buzzer, 450);
  delay(500);
  noTone(buzzer);
  delay(500);
  if (digitalRead(buttonPin) == HIGH){
      stan_alarm = 0;
    }
  }
}


 


    
   
