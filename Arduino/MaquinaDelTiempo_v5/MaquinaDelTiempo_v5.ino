// Control de Riego MkI

//RTC:
#include <Wire.h>    // I2C-Bibliothek einbinden
#include <virtuabotixRTC.h> 

//Temperatura:
#include <OneWire.h>
#include <DallasTemperature.h>

// LCD:
#include <LiquidCrystal.h>

#undef int

#define DS18B20_PIN 2   //Se declara el pin donde se conectará el sensor de aire

OneWire ourWire(DS18B20_PIN); //Se establece el pin declarado como bus para la comunicación OneWire
DallasTemperature sensors(&ourWire); //Se instancia la librería DallasTemperature

DeviceAddress SensorAire = { 0x28, 0x09, 0xE1, 0xBF, 0x06, 0x00, 0x00, 0x45 }; 

LiquidCrystal lcd(13, NULL, 12, 7, 8, 9, 10);

//CLK a PIN 6
//DAT a PIN 5
//RST a PIN 4
virtuabotixRTC myRTC(6, 5, 4);


float  noentrar = 0;
float  TempActual = 0;
float  TempAnterior = 0;
float  ModoEdicion = 0;
float value = 0;   //variable que almacena el voltaje
float F1=0;
float PercentOfInput=0.0;
int sumahora ;
int hora;
int sumaminuto ;
int minuto;
int dia;
int mes;
int ano;
int sumadia;
int sumames;
int sumaano;
int HayCumple = 0;
int i = 0;
int s = 0;
int SenalDeOK = 0;
String Felicitacion1 = "  Feliz Cumple  ";
String Felicitacion2;
char *TempSatelite1;
char *HumSatelite1;
char HumSatelite2;
char *msg = "";

String inString = ""; 

void setup(void) {
  // Inicia el puerto I2C 
  Wire.begin();

  // Arrancando RTC:
  // segundos, min, hour, day of week, day of month, month, year
//   myRTC.setDS1302Time(19, 24, 19, 3, 18, 7, 2017);

  Serial.begin(9600);
  
  // Arrancando Sensor:  
  sensors.begin(); //Se inician los sensores
  sensors.setResolution(SensorAire, 10); // Ajusa la resolución a 10 bit (Puede ser de 9 a 12 bits.. lower is faster)
  
  // Arrancando LCD
  lcd.begin(16, 2); //Se inicia la pantalla
  lcd.setCursor(0, 0);

}
 
void loop() {

  myRTC.updateTime(); // Recoge la hora actual del RTC.

  void recibir ();

  hora = myRTC.hours;  
  minuto = myRTC.minutes;

  dia = myRTC.dayofmonth;
  mes = myRTC.month;
  ano = myRTC.year; 
     
// if (noentrar == 1) { 
  // Lee el pin analógico 0. Trae el voltaje del botón.
  int dato = analogRead(0);

  if (dato > 100)
  {
    if (dato > 500 && dato < 520) {
           if (ModoEdicion == 0) {
               ModoEdicion = 1; // Activo modo edicion hora
//               Serial.println("Activo modo edicion hora");
               }
               else {
                 if (ModoEdicion == 1) {
                   ModoEdicion = 2; // Activo modo edicion fecha
//                   Serial.println("Activo modo edicion fecha");
                 }
                 else {                 
                   ModoEdicion = 0; // Desactivo modo edicion
//                   Serial.println("Desactivo modo edicion");
                 }
               }
  
           delay(500);  
        }

    delay(500);
   } 
  

//    TempAnterior = 1;
    if (TempAnterior == 0) {
      lcd.setCursor(0,0);
      lcd.print("  OBTENIENDO    ");
      lcd.setCursor(0,1);
      lcd.print("  TEMPERATURA   ");
      delay(500);
      lcd.print("  OBTENIENDO    ");
      lcd.setCursor(0,1);
      lcd.print("  TEMPERATURA.  ");
      delay(500);
      lcd.setCursor(0,0);
      lcd.print("  OBTENIENDO    ");
      lcd.setCursor(0,1);
      lcd.print("  TEMPERATURA.. ");
      delay(500);
      lcd.setCursor(0,1);
      lcd.print("  TEMPERATURA...");
      delay(500);
    }
  
// Activar Cumpleaños
  if ((myRTC.dayofmonth == 26) && (myRTC.month == 8)) {
    HayCumple = 1;
    Felicitacion2 = "     Tatita     ";
    }
    else HayCumple = 0;
  if ((myRTC.dayofmonth == 2) && (myRTC.month == 2)) {
    HayCumple = 1;
    Felicitacion2 = "      Madre     ";
    }
    else HayCumple = 0;
  if ((myRTC.dayofmonth == 12) && (myRTC.month == 11)) {
    HayCumple = 1;
    Felicitacion2 = "      Padre     ";
    }
    else HayCumple = 0;
  if ((myRTC.dayofmonth == 5) && (myRTC.month == 8)) {
    HayCumple = 1;
    Felicitacion2 = "     Tatito     ";
    }
    else HayCumple = 0;
  if ((myRTC.dayofmonth == 9) && (myRTC.month == 12)) {
    HayCumple = 1;
    Felicitacion2 = "     Tperez     ";
    }
    else HayCumple = 0;

  if (ModoEdicion == 0) {

  if ((myRTC.minutes == 0 || myRTC.minutes == 5 || myRTC.minutes == 10 || myRTC.minutes == 15 || myRTC.minutes == 20 ||
      myRTC.minutes == 25 || myRTC.minutes == 30 || myRTC.minutes == 35 || myRTC.minutes == 40 || myRTC.minutes == 45 ||
      myRTC.minutes == 50 || myRTC.minutes == 55) && (myRTC.seconds < 5)) {  

      sensors.requestTemperatures(); //Prepara el sensor para la lectura
      
// OBTIENE LA TEMP DEL AIRE    
      TempActual = sensors.getTempC(SensorAire);
      TempActual = TempActual - 1;
      TempAnterior = TempActual;

    }
    else {

    if (TempAnterior || 0) {
      
// Programa para cuando NO hay cumpleaños:
       if (HayCumple == 0)  {
         
// Pinta HORA:
//            Serial.println("Pinta Hora y Fecha");
            
              lcd.setCursor(0,0);
              lcd.print(myRTC.hours);  
              lcd.print(+ ":") ;
              if (myRTC.minutes < 10) {
                lcd.print(+ "0") ;
                lcd.print(myRTC.minutes);
              }
              else {
                lcd.print(myRTC.minutes);
                }
              lcd.print("    ") ;
              lcd.print(TempAnterior);
              lcd.print("\337C"); 
// Pinta FECHA: 
              lcd.setCursor(0,1);
              lcd.print( "    ") ;
              lcd.print(myRTC.dayofmonth);
              lcd.print(+ "/") ;
              lcd.print(myRTC.month);
              lcd.print(+ "/") ;
              lcd.print(myRTC.year); 
              lcd.print("     ") ;
              
         }
         
// Programa para cuando hay cumpleaños:
       if (HayCumple == 1)  {
         
           if (((myRTC.seconds >= 0) && (myRTC.seconds < 30)) ||
               ((myRTC.seconds >= 45) && (myRTC.seconds < 60))) {
                    
              lcd.setCursor(0,0);
              lcd.print(Felicitacion1);
              lcd.setCursor(0,1);
              lcd.print(Felicitacion2);
              
            }  
            
           if ((myRTC.seconds >= 30) && (myRTC.seconds < 45)) {
                    
// Pinta HORA:
//            Serial.println("Pinta Hora y Fecha");
            
              lcd.setCursor(0,0);
              lcd.print( "      ") ;
              lcd.print(myRTC.hours);  
              lcd.print(+ ":") ;
              if (myRTC.minutes < 10) {
                lcd.print(+ "0") ;
                lcd.print(myRTC.minutes);
              }
              else {
                lcd.print(myRTC.minutes);
                }
              lcd.print("       ") ;
// Pinta FECHA: 
              lcd.setCursor(0,1);
              lcd.print( "    ") ;
              lcd.print(myRTC.dayofmonth);
              lcd.print(+ "/") ;
              lcd.print(myRTC.month);
              lcd.print(+ "/") ;
              lcd.print(myRTC.year); 
              lcd.print("     ") ;
              
            } 
         }
       
         
      } // if (TempAnterior || 0)
           
           
    } // else myRTC.minutes == 0 ...
    
    } // ModoEdicion == 0

    if (ModoEdicion == 1) {
      
// HORA:
        lcd.setCursor(0,1);
        lcd.print("                ");
        
        lcd.setCursor(0,0);
        lcd.print( "      ") ;


        if (dato > 100)
        {
          if (dato > 330 && dato < 350) {
                        hora = myRTC.hours;
                        sumahora = hora + 1;

                        if (sumahora == 25) {
                            sumahora = 0;
                            }
                        
                        myRTC.setDS1302Time(myRTC.seconds, myRTC.minutes, sumahora, myRTC.dayofweek, myRTC.dayofmonth, myRTC.month, myRTC.year);

                        lcd.setCursor(0,0);
                        lcd.print( "      ") ;
                        lcd.print(myRTC.hours);  
                        lcd.print(+ ":") ;
                        if (myRTC.minutes < 10) {
                          lcd.print(+ "0") ;
                          lcd.print(myRTC.minutes);
                        }
                        else {
                          lcd.print(myRTC.minutes);
                          }
                        lcd.print("        ") ;
        
                        delay(500);
                }
        }
        else {
            lcd.print(myRTC.hours);                  
             }

        lcd.print(+ ":") ;


        if (dato > 100)
        {
          if (dato > 244 && dato < 264) {
           
                    lcd.setCursor(0,0);
                    minuto = myRTC.minutes;
                    sumaminuto = minuto + 1; 
          
                    if (sumaminuto == 61) {
                        sumaminuto = 1;
                        }
                    
                    myRTC.setDS1302Time(myRTC.seconds, sumaminuto, myRTC.hours, myRTC.dayofweek, myRTC.dayofmonth, myRTC.month, myRTC.year);
                        
                    lcd.print( "      ") ;
                    lcd.print(myRTC.hours);  
                    lcd.print(+ ":") ;
                    if (myRTC.minutes < 10) {
                      lcd.print(+ "0") ;
                      lcd.print(myRTC.minutes);
                    }
                    else {
                      lcd.print(myRTC.minutes);
                      }
                    lcd.print("        ") ;
          
                    delay(500);
                }
        }
        else {
              if (myRTC.minutes < 10) {
                lcd.print(+ "0") ;
                lcd.print(myRTC.minutes);
              }
              else {
                lcd.print(myRTC.minutes);
                }
              lcd.print("        ") ;                  
             }
             
        lcd.print("     ") ; 
     }
     
     
    if (ModoEdicion == 2) {
      
// FECHA:
        lcd.setCursor(0,0);
        lcd.print("                ");

        lcd.setCursor(0,1);
        lcd.print( "    ") ;

        if (dato > 100)
        {
          if (dato > 330 && dato < 350) {
                        dia = myRTC.dayofmonth;
                        sumadia = dia + 1;

                        if (sumadia == 32) {
                            sumadia = 1;
                        }

                        myRTC.setDS1302Time(myRTC.seconds, myRTC.minutes, myRTC.hours, myRTC.dayofweek, sumadia, myRTC.month, myRTC.year);
                        
                        lcd.setCursor(0,1);
                        lcd.print( "    ") ;
                        lcd.print(myRTC.dayofmonth);
                        lcd.print(+ "/") ;
                        lcd.print(myRTC.month);
                        lcd.print(+ "/") ;
                        lcd.print(myRTC.year); 
                        lcd.print("     ") ;
                        delay(500);
                }
         } else {
           lcd.print(myRTC.dayofmonth);
           }
         
        lcd.print(+ "/") ;
         
        if (dato > 100)
        {
               if (dato > 244 && dato < 264) {
                        mes = myRTC.month;
                        sumames = mes + 1;
                        
                        if (sumames == 13) {
                            sumames = 1;
                        }
                        
                        myRTC.setDS1302Time(myRTC.seconds, myRTC.minutes, myRTC.hours, myRTC.dayofweek, myRTC.dayofmonth, sumames, myRTC.year);
                        
                        lcd.setCursor(0,1);
                        lcd.print( "    ") ;
                        lcd.print(myRTC.dayofmonth);
                        lcd.print(+ "/") ;
                        lcd.print(myRTC.month);
                        lcd.print(+ "/") ;
                        lcd.print(myRTC.year); 
                        lcd.print("     ") ;
                        delay(500);
                }
        } else {
          lcd.print(myRTC.month);
          }
         
        lcd.print(+ "/") ;
         
        if (dato > 100)
        {       
          if (dato > 190 && dato < 210) {
                        ano = myRTC.year;
                        sumaano = ano + 1;
                        myRTC.setDS1302Time(myRTC.seconds, myRTC.minutes, myRTC.hours, myRTC.dayofweek, myRTC.dayofmonth, myRTC.month, sumaano);
                        
                        lcd.setCursor(0,1);
                        lcd.print( "    ") ;
                        lcd.print(myRTC.dayofmonth);
                        lcd.print(+ "/") ;
                        lcd.print(myRTC.month);
                        lcd.print(+ "/") ;
                        lcd.print(myRTC.year); 
                        lcd.print("     ") ;
                        delay(500);
                }
        } else {
          lcd.print(myRTC.year); 
          }
        
          lcd.print("    ") ;

     }
//} // if no entrar 
}


