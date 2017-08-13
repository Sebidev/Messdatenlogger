/*
[Messdatenlogger Arduino Nano RFID]

Copyright (C) [2017]  [Tom Hoffmeister]

Dieses Programm ist freie Software. Sie können es unter den Bedingungen der GNU General Public License, wie von der Free Software Foundation veröffentlicht, weitergeben und/oder modifizieren, entweder gemäß Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren Version.

Die Veröffentlichung dieses Programms erfolgt in der Hoffnung, daß es Ihnen von Nutzen sein wird, aber OHNE IRGENDEINE GARANTIE, sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT FÜR EINEN BESTIMMTEN ZWECK. Details finden Sie in der GNU General Public License.

Sie sollten ein Exemplar der GNU General Public License zusammen mit diesem Programm erhalten haben. Falls nicht, siehe <http://www.gnu.org/licenses/>.
*/

/*
 * 26.04.2017
 *
 * 1X Encoder  UP / Down / OK
 * 1X RFID Reader RC522
 * 
 * 15 RFID Tags sind anlernbar
*/


#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Benuter Einstellungen
//===========================================
long TagNr1 = 2197610;                        //Berechtigter Tag 1   // Mitgelieferter  RFID-Tags
long TagNr2 = 382570;                         //Berechtigter Tag 2   // Mitgelieferter  RFID-Tags
long TagNr3 = 620060;                         //Berechtigter Tag 3   // Mitgelieferter  RFID-Tags
long TagNr4 = 2073590;                        //Berechtigter Tag 4   // Mitgelieferter  RFID-Tags
long TagNr5 = 870830;                         //Berechtigter Tag 5   // Mitgelieferter  RFID-Tags
long TagNr6 = 1702350;                        //Berechtigter Tag 6   // Mitgelieferter  RFID-Tags
long TagNr7 = 890410;                         //Berechtigter Tag 7   // Essenskarte Bene
long TagNr8 = 210310;                         //Berechtigter Tag 8   // Essenskarte Sebi 1
long TagNr9 = 2470810;                        //Berechtigter Tag 9   // Essenskarte Fatih
long TagNr10 = 1839310;                       //Berechtigter Tag 10  // Essenskarte Tom
long TagNr11 = 2396810;                       //Berechtigter Tag 11  // Essenskarte Erwin
long TagNr12 = 0;                        //Berechtigter Tag 12
long TagNr13 = 0;                        //Berechtigter Tag 13
long TagNr14 = 0;                        //Berechtigter Tag 14
long TagNr15 = 0;                        //Berechtigter Tag 15

int RunT = 200;                               //Anzahl der Loopschleifen in der die eingabe aktiv ist
//===========================================
int TagOk = 1;                                //Dise wariable Zeigt Ben Bedin sttus an  0=Gespert / 1=Aktiwirte eingabe
int Run = 0;                                  //Zählt die durchlauefenen Loopschleifen
int OkIn;                                     //erfast den Enkoder OK
int UpIn;                                     //erfast den Enkoder UP
int DownIn;                                   //erfast den Enkoder DOWN

void setup()
{
Serial.begin(9600);                            //Kann Ausargumentirt 
SPI.begin();                                   //  Muss da sein
mfrc522.PCD_Init();
pinMode (2, OUTPUT);                           // interupt angeschlossen)           //GRAU/W
pinMode (3, OUTPUT);                           // Ok Out                            //ROT/W
pinMode (4, OUTPUT);                           // down Out                          //GRÜN/W
pinMode (5, OUTPUT);                           // Up Out                            //BLAU/W
pinMode (A5, OUTPUT);                          // Display Hintergund beleuchtung    //GELB/W

pinMode (6, INPUT_PULLUP);                     // up In //                          //BLAU
pinMode (7, INPUT_PULLUP);                     // down In //                        //GRÜN
pinMode (8, INPUT_PULLUP);                     // Ok In //                          //ROT

pinMode (A6, INPUT_PULLUP);                    // Schlüsselschalter eingang         // Noch Nicht Implementirt
}//setup

void loop()
{ 
//bedinelemente
//===========================================

UpIn = digitalRead (6);
DownIn = digitalRead (7);
OkIn = digitalRead (8);

if ((TagOk==1)&&(UpIn==0))                   //U
  {                                          //UP
    digitalWrite(5,HIGH);                    //Up
  }                                          //Up
else                                         //Up
  {                                          //Up
    digitalWrite(5,LOW);                     //Up    //Noch Überarbeitungs würdig   
    delay(10);
  }                                          //Up

if ((TagOk==1)&&(DownIn==0))                 //Down
  {                                          //Down
    digitalWrite(4,HIGH);                    //Down
  }                                          //Down
else                                         //Down
  {                                          //Down
    digitalWrite(4,LOW);                     //Down  //Noch Überarbeitungs würdig   
    delay(10);
  }                                          //Down

if ((TagOk==1)&&(OkIn==0))                   //Ok
  {                                          //Ok
    digitalWrite(3,HIGH);                    //Ok
    delay(10);                               //Ok

  }                                          //Ok
else                                         //Ok
  {                                          //Ok
    digitalWrite(3,LOW);                     //Ok
    delay(10);                               //Ok
  }                                          //Ok

//Timer
//===========================================
Serial.println(Run);                         //Kann Ausargumentirt werden
//===========================================
  Run= Run+1;                                // Zäler für Program schleifen un dei zeit zu bestimmen die die Bedin elemente Aktiv sind
  
  if (Run == RunT)
    {
       Run = 0 ;
       TagOk = 0;
       analogWrite(A5,LOW);                  //Display beleuchtung //OFF
    }
//===========================================
Serial.print("Der Eingabestatus ist:");      //Kann Ausargumentirt werden
Serial.println(TagOk);                       //Kann Ausargumentirt werden
//===========================================
//RFID Begin
//===========================================

  if ( ! mfrc522.PICC_IsNewCardPresent())
    {
      return;
    }

  if ( ! mfrc522.PICC_ReadCardSerial())
    {
      return;
    }

long code=0;

  for (byte i = 0; i < mfrc522.uid.size; i++)
    {
     code=((code+mfrc522.uid.uidByte[i])*10);
    }
//===========================================
Serial.print("Die Kartennummer lautet:");    //Kann Ausargumentirt werden
Serial.println(code);                        //Kann Ausargumentirt werden
//===========================================

// TAG Aktionen
//===========================================
  
 if (code==TagNr1) // Wenn der Zahlencode tagnr1 lautet...
   {
      TagOk = 1;                              //Tag 1
      Run = 0;                                //Tag 1
      digitalWrite(A5,HIGH);                  //Display ON
      Serial.print("Benutzernummer 1");       //Kann Ausargumentirt werden
   }                                          

 if (code==TagNr2) // Wenn der Zahlencode tagnr2 lautet...
   {
      TagOk = 1;                             //Tag 2
      Run = 0;                               //Tag 2
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 2");      //Kann Ausargumentirt werden
   }

 if (code==TagNr3) // Wenn der Zahlencode tagnr3 lautet...
   {
      TagOk = 1;                             //Tag 3
      Run = 0;                               //Tag 3
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 3");      //Kann Ausargumentirt werden
   }

 if (code==TagNr4) // Wenn der Zahlencode tagnr4 lautet...
   {
      TagOk = 1;                             //Tag 4
      Run = 0;                               //Tag 4
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 4");      //Kann Ausargumentirt werden
   }   
 
 if (code==TagNr5) // Wenn der Zahlencode tagnr5 lautet...
   {
      TagOk = 1;                             //Tag 5
      Run = 0;                               //Tag 5
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 5");      //Kann Ausargumentirt werden
   }   
 
 if (code==TagNr6) // Wenn der Zahlencode tagnr6 lautet...
   {
      TagOk = 1;                             //Tag 6
      Run = 0;                               //Tag 6
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 6");      //Kann Ausargumentirt werden
   }   
 
 if (code==TagNr7) // Wenn der Zahlencode tagnr7 lautet...
   {
      TagOk = 1;                             //Tag 7
      Run = 0;                               //Tag 7
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 7");      //Kann Ausargumentirt werden
   }   
  
 if (code==TagNr8) // Wenn der Zahlencode tagnr8 lautet...
   {
      TagOk = 1;                             //Tag 8
      Run = 0;                               //Tag 8
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 8");      //Kann Ausargumentirt werden
   }   
  
 if (code==TagNr9) // Wenn der Zahlencode tagnr9 lautet...
   {
      TagOk = 1;                             //Tag 9
      Run = 0;                               //Tag 9
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 9");      //Kann Ausargumentirt werden
   }   
  
 if (code==TagNr10) // Wenn der Zahlencode tagnr10 lautet...
   {
      TagOk = 1;                             //Tag 10
      Run = 0;                               //Tag 10
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 10");     //Kann Ausargumentirt werden
   }   
  
 if (code==TagNr11) // Wenn der Zahlencode tagnr11 lautet...
   {
      TagOk = 1;                             //Tag 11
      Run = 0;                               //Tag 11
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 11");     //Kann Ausargumentirt werden
   }   
   
 if (code==TagNr12) // Wenn der Zahlencode tagnr12 lautet...
   {
      TagOk = 1;                             //Tag 12
      Run = 0;                               //Tag 12
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 12");     //Kann Ausargumentirt werden
   }   
   
 if (code==TagNr13) // Wenn der Zahlencode tagnr13 lautet...
   {
      TagOk = 1;                             //Tag 13
      Run = 0;                               //Tag 13
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 13");     //Kann Ausargumentirt werden
   }   
   
 if (code==TagNr14) // Wenn der Zahlencode tagnr14 lautet...
   {
      TagOk = 1;                             //Tag 14
      Run = 0;                               //Tag 14
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 14");     //Kann Ausargumentirt werden
   }   
   
 if (code==TagNr15) // Wenn der Zahlencode tagnr15 lautet...
   {
      TagOk = 1;                             //Tag 15
      Run = 0;                               //Tag 15
      digitalWrite(A5,HIGH);                 //Display ON
      Serial.print("Benutzernummer 15");     //Kann Ausargumentirt werden
   }   
 
} //loop
//end

/*Tom Hoffmeister
 * 
 * REV 1.0.0  25,04,2017 12:00 RFID Begonnen
 * REV 1.1.0  25,04,2017 17:30 RFID Laufzeit der Aktivirung
 * REV 1.1.1  25,04,2017 23:50 Programm auf gereumt
 * REV 1.2.0  26,04,2017 15:00 Encoder ein gefügt und debugt
 * REV 1.2.1  17,05,2017 16:30 Weitwere RFID transponder eingefügt
 * REV 1.2.2  18,05,2017 10:30 Weitwere RFID transponder eingefügt,Programm auf gereumt und debugt
 * REV 1.2.3  19,05,2017 08:10 Encoder debugt 
 */
