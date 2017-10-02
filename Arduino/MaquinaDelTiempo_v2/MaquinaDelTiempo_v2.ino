#include <OneWire.h>

#include <DallasTemperature.h>

#include <LiquidCrystal.h>

#define Pin 2 //Se declara el pin donde se conectará la DATA
 
OneWire ourWire(Pin); //Se establece el pin declarado como bus para la comunicación OneWire
 
DallasTemperature sensors(&ourWire); //Se instancia la librería DallasTemperature

LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);
 
void setup() {
delay(1000);
Serial.begin(9600);
sensors.begin(); //Se inician los sensores
lcd.begin(16, 2); //Se inicia la pantalla
}
 
void loop() {
sensors.requestTemperatures(); //Prepara el sensor para la lectura
 
Serial.print(sensors.getTempCByIndex(0)); //Se lee e imprime la temperatura en grados Celsius
Serial.println(" grados Centigrados");
Serial.print(sensors.getTempFByIndex(0)); //Se lee e imprime la temperatura en grados Fahrenheit
Serial.println(" grados Fahrenheit"); 

lcd.setCursor(0,0);
lcd.print("Hace ");
lcd.print(sensors.getTempCByIndex(0));
lcd.print("\337C");

lcd.setCursor(0,1);
if (sensors.getTempCByIndex(0) > 20) {
//  lcd.print("Winter is coming");
  lcd.print("Se acerca el inv");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("e acerca el invi");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print(" acerca el invie");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("acerca el invier");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("cerca el inviern");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("erca el invierno");
}
 
delay(60000); //Se provoca un lapso de 10 segundos antes de la próxima lectura
 
}
