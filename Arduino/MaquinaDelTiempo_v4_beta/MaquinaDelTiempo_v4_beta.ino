
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
//#include <RCSwitch.h>

#include <OneWire.h>

#include <DallasTemperature.h>

#include <LiquidCrystal.h>

#include <Time.h>

#define Pin 2 //Se declara el pin donde se conectará la DATA
 
OneWire ourWire(Pin); //Se establece el pin declarado como bus para la comunicación OneWire
 
DallasTemperature sensors(&ourWire); //Se instancia la librería DallasTemperature

LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);

float  TempActual = 0;
float  TempAnterior = 0;

void setup() {
delay(1000);
Serial.begin(9600);
sensors.begin(); //Se inician los sensores
lcd.begin(16, 2); //Se inicia la pantalla
setTime(19,02,00,2,6,2015); // Las 19:58:00 del dia 1 de Junio de 2015

}
 
void loop() {
time_t t = now();

if (minute(t) == 0 || minute(t) == 15 || minute(t) == 30 || minute(t) == 40 || minute(t) == 50) {  
    sensors.requestTemperatures(); //Prepara el sensor para la lectura
  
    lcd.setCursor(0,0);
    lcd.print(" Hace ");
    TempActual = sensors.getTempCByIndex(0);
    lcd.print(TempActual);
    lcd.print("\337C");
    TempAnterior = TempActual;
  }
  else {
    lcd.setCursor(0,0);
    lcd.print(" Hace ");
    lcd.print(TempAnterior);
    lcd.print("\337C");
    
  }

lcd.setCursor(0,1);
      lcd.print(day(t));
      lcd.print(+ "/") ;
      lcd.print(month(t));
      lcd.print(+ "/") ;
      lcd.print(year(t)); 
      lcd.print( " ") ;
      lcd.print(hour(t));  
      lcd.print(+ ":") ;
      if (minute(t) < 10) {
        lcd.print(+ "0") ;
        lcd.print(minute(t));
      }
      else {
        lcd.print(minute(t));
        }

delay(60000); //Se provoca un lapso de 60 segundos antes de la próxima lectura

if (TempActual < 20) {
  lcd.setCursor(0,0);
  lcd.print("   JODER QUE    ");
  lcd.setCursor(0,1);
  lcd.print("   PUTO FRIO    ");
}

if (TempActual >= 20 && TempActual < 25) {
  lcd.setCursor(0,0);
  lcd.print("   SE ACERCA    ");
  lcd.setCursor(0,1);
  lcd.print("  EL INVIERNO   ");
}

if (TempActual >= 25 && TempActual < 28) {
  lcd.setCursor(0,0);
  lcd.print("   UN DIA MAS  ");
  lcd.setCursor(0,1);
  lcd.print("  EN EL PARAISO ");
}

if (TempActual >= 28) {
  lcd.setCursor(0,0);
  lcd.print("  PON EL AIRE   ");
  lcd.setCursor(0,1);
  lcd.print("     OSTIAS     ");
}

delay(10000); //Se provoca un lapso de 10 segundos antes de la próxima lectura

  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
}
