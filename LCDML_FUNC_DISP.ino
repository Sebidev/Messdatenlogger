/*
[Datenlogger v1.1.0]

Copyright (C) [2017]  [Sebastian Bürger & Tom Hoffmeister]

Dieses Programm ist freie Software. Sie können es unter den Bedingungen der GNU General Public License, wie von der Free Software Foundation veröffentlicht, weitergeben und/oder modifizieren, entweder gemäß Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren Version.
Die Veröffentlichung dieses Programms erfolgt in der Hoffnung, daß es Ihnen von Nutzen sein wird, aber OHNE IRGENDEINE GARANTIE, sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT FÜR EINEN BESTIMMTEN ZWECK. Details finden Sie in der GNU General Public License.
Sie sollten ein Exemplar der GNU General Public License zusammen mit diesem Programm erhalten haben. Falls nicht, siehe <http://www.gnu.org/licenses/>. 
*/
/* ===================================================================== *
 *                                                                       *
 * DISPLAY SYSTEM                                                        *
 *                                                                       *
 * ===================================================================== *
 * every "disp menu function" needs three functions 
 * - void LCDML_DISP_setup(func_name)    
 * - void LCDML_DISP_loop(func_name)     
 * - void LCDML_DISP_loop_end(func_name)
 *
 * EXAMPLE CODE:
    void LCDML_DISP_setup(..menu_func_name..) 
    {
      // setup
      // is called only if it is started

      // starts a trigger event for the loop function every 100 millisecounds
      LCDML_DISP_triggerMenu(100);  
    }
    
    void LCDML_DISP_loop(..menu_func_name..)
    { 
      // loop
      // is called when it is triggert
      // - with LCDML_DISP_triggerMenu( millisecounds ) 
      // - with every button status change

      // check if any button is presed (enter, up, down, left, right)
      if(LCDML_BUTTON_checkAny()) {         
        LCDML_DISP_funcend();
      } 
    }
    
    void LCDML_DISP_loop_end(..menu_func_name..)
    {
      // loop end
      // this functions is ever called when a DISP function is quit
      // you can here reset some global vars or do nothing  
    } 
 * ===================================================================== *
 */
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include <OneWire.h>
#include "SdFat.h"
#include "TimerOne.h"

SdFat SD;
File myFile;
  tmElements_t tm;

int messungtyp = 0;
int int_messzeitintervall = 180;
int timerzahl;

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_information)
// *********************************************************************
{
  // setup function 
  lcd.setCursor(0, 0);
  lcd.print(F("Datenlogger v1.0"));
  lcd.setCursor(0, 1);
  lcd.print(F("Entwickler:"));
  lcd.setCursor(0, 2);
  lcd.print(F("Tom Hoffmeister"));
  lcd.setCursor(0, 3);
  lcd.print(F("Sebastian Buerger"));
}

void LCDML_DISP_loop(LCDML_FUNC_information) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function
  
  if(LCDML_BUTTON_checkAny()) { // check if any button is presed (enter, up, down, left, right)
    // LCDML_DISP_funcend calls the loop_end function
    LCDML_DISP_funcend();
  } 
}

void LCDML_DISP_loop_end(LCDML_FUNC_information)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing  
}  

void LCDML_DISP_setup(strommessungtyp) {}
void LCDML_DISP_loop(strommessungtyp)
{
   messungtyp = 1;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(strommessungtyp) {}

void LCDML_DISP_setup(spannungsmessungtyp) {}
void LCDML_DISP_loop(spannungsmessungtyp)
{
   messungtyp = 2;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(spannungsmessungtyp) {}

void LCDML_DISP_setup(leistungsmessungtyp) {}
void LCDML_DISP_loop(leistungsmessungtyp)
{
   messungtyp = 3;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(leistungsmessungtyp) {}

void LCDML_DISP_setup(wetterfroschmessungtyp) {}
void LCDML_DISP_loop(wetterfroschmessungtyp)
{
   messungtyp = 4;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(wetterfroschmessungtyp) {}

void LCDML_DISP_setup(tempaturmessungtyp) {}
void LCDML_DISP_loop(tempaturmessungtyp)
{
   messungtyp = 5;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(tempaturmessungtyp) {}

void LCDML_DISP_setup(lichtmodultyp) {}
void LCDML_DISP_loop(lichtmodultyp)
{
   messungtyp = 6;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(lichtmodultyp) {}

void LCDML_DISP_setup(regenmodul) {}
void LCDML_DISP_loop(regenmodul)
{
   messungtyp = 7;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(regenmodul) {}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.print('0');
  }
  lcd.print(number);
}

void LCDML_DISP_setup(x30sek) {}
void LCDML_DISP_loop(x30sek)
{
   int_messzeitintervall = 30;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(x30sek) {}

void LCDML_DISP_setup(x1min) {}
void LCDML_DISP_loop(x1min)
{
   int_messzeitintervall = 60;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(x1min) {}

void LCDML_DISP_setup(x5min) {}
void LCDML_DISP_loop(x5min)
{
   int_messzeitintervall = 300;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(x5min) {}

void LCDML_DISP_setup(x10min) {}
void LCDML_DISP_loop(x10min)
{
   int_messzeitintervall = 600;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(x10min) {}

void LCDML_DISP_setup(x15min) {}
void LCDML_DISP_loop(x15min)
{
   int_messzeitintervall = 900;
   LCDML.goRoot();
}
void LCDML_DISP_loop_end(x15min) {}

void LCDML_DISP_setup(show_uhr_date) {}
void LCDML_DISP_loop(show_uhr_date)
{
  tmElements_t tm;
  if (RTC.read(tm))
  {
    lcd.clear();
    print2digits(tm.Hour);
    lcd.print(":");
    print2digits(tm.Minute);
    lcd.print(":");
    print2digits(tm.Second);

    lcd.setCursor(0,2);
    print2digits(tm.Day);
    lcd.print(".");
    print2digits(tm.Month);
    lcd.print(".");
    print2digits(tmYearToCalendar(tm.Year));
  }
  else
  {
     if (RTC.chipPresent())
     {
      lcd.clear();
      lcd.print("Uhrzeit/Datum muss");
      lcd.setCursor(0,1);
      lcd.print("erst eingestellt");
      lcd.setCursor(0,2);
      lcd.print("werden!");
     }
  }
    if(LCDML_BUTTON_checkAny()) { 
    LCDML_DISP_funcend();
  } 
}
void LCDML_DISP_loop_end(show_uhr_date) {}

//////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//------------------------------MESSUNG FUNCKION---------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////

void funk_wetterfroschmessung()
{
    float LoggSensorValue1;
    float LoggSensorValue2;
    float LoggSensorValue3;

    OneWire  ds(5);

    float sensorValue3;                                                
    float sensorValue2;        
                                                                  
    sensorValue2 = analogRead(A2);                                   
    LoggSensorValue2 = map (sensorValue2, 0, 1024, 100, -1);        
  
    sensorValue3 = analogRead(A3);                                   
    LoggSensorValue3 = map (sensorValue3, 0, 1024, 100, -1);        

    byte i;
    byte present = 0;
    byte type_s;
    byte data[12];
    byte addr[8];
    float celsius;
  
    if ( !ds.search(addr))
    {
      ds.reset_search();
      delay(250);
      return;
    }

    if (OneWire::crc8(addr, 7) != addr[7]) 
    {
      return;
    }
    
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);
    delay(1000);     
    present = ds.reset();
    ds.select(addr);    
    ds.write(0xBE);
 
    for ( i = 0; i < 9; i++)
    {  
      data[i] = ds.read();
    }
    int16_t raw = (data[1] << 8) | data[0];
    if (type_s)
    {
      raw = raw << 3;
      if (data[7] == 0x10)
      {
        raw = (raw & 0xFFF0) + 12 - data[6];
      } 
   } 
 else 
   {
   byte cfg = (data[4] & 0x60);
   if (cfg == 0x00) raw = raw & ~7;
   else if (cfg == 0x20) raw = raw & ~3; 
   else if (cfg == 0x40) raw = raw & ~1; 
   }
 celsius = (float)raw / 16.0;
 celsius * 1.8 + 32.0;

LoggSensorValue1 = celsius;

 lcd.clear();
 lcd.print("Celsius:");
 lcd.setCursor(9,0);
 lcd.print(LoggSensorValue1);
 lcd.setCursor(14,0);
 lcd.print((char)223);
 lcd.setCursor(15,0);
 lcd.print("C");
 lcd.setCursor(0,1);
 lcd.print("Regen: ");
 lcd.setCursor(7,1);
 lcd.print(LoggSensorValue2);
 lcd.setCursor(12,1);
 lcd.print("%");
 lcd.setCursor(0,2);
 lcd.print("Licht: ");
 lcd.setCursor(7,2);
 lcd.print(LoggSensorValue3);
 lcd.setCursor(12,2);
 lcd.print("%");
 lcd.setCursor(0,3);
 lcd.print("Messung leuft...");
  
    if (!SD.begin(10))
    {
        return;
    }

  myFile = SD.open("messdaten.txt", FILE_WRITE);
  tmElements_t tm;
  RTC.read(tm);
  
  
  if (myFile) {
    myFile.print(tm.Hour);
    myFile.print(":");
    myFile.print(tm.Minute);
    myFile.print(":");
    myFile.print(tm.Second);
    myFile.print(",");
    myFile.print(tm.Day);
    myFile.print(".");
    myFile.print(tm.Month);
    myFile.print(".");
    myFile.print(tmYearToCalendar(tm.Year));
    myFile.print(",");
    myFile.print("Celsius,");
    myFile.print(LoggSensorValue1);
    myFile.print(",");
    myFile.print("Regen,");
    myFile.print(LoggSensorValue2);
    myFile.print(",");
    myFile.print("Licht,");
    myFile.println(LoggSensorValue3);
    // close the file:
    myFile.close();
  }
    if(LCDML_BUTTON_checkAny())
    { 
      Timer1.detachInterrupt();
      LCDML_DISP_funcend();
    }
}

void LCDML_DISP_setup(messung) {}
void LCDML_DISP_loop(messung)
{
   if(messungtyp == 0)
   {
       lcd.clear();
       lcd.print("Messadapter bitte");
       lcd.setCursor(0,1);
       lcd.print("auswaehlen!");
       if(LCDML_BUTTON_checkAny())
       { 
           LCDML_DISP_funcend();
       } 
   }

   if(messungtyp == 4)
   {      
      lcd.setCursor(0,3);
      lcd.print("Messung leuft.....");
      Timer1.initialize(1*1000000);
      Timer1.attachInterrupt(timerinterput);
      if(timerzahl == int_messzeitintervall)
      {
        funk_wetterfroschmessung();
      }
      if(LCDML_BUTTON_checkAny())
      { 
           Timer1.detachInterrupt();
           LCDML_DISP_funcend();
      } 
   }
}
void LCDML_DISP_loop_end(messung) {}

void timerinterput()
{
  timerzahl++;
}
