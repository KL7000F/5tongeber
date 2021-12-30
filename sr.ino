/*
 5-Ton Geber
 Erzeugt mithilfe von 'asmsynth' (https://github.com/ezasm/asmsynth) 5-Ton-Folgen (Selektivruf) nach ZVEI1 / TR-BOS.
 Sinn und Zweck ist die akustische Simulation. Die Einbindung in BOS-Netze ist untersagt.

 Anschluss-Schema Arduino Nano:
 
           +C1-     +  -
        -- -||- --- Lspr -- 
       |                   | 
 ----  |                   |
|   _|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_
|  |12 11                 GND      |
|  | USB                           |
|  |_ _ _ _ _ _ _ _ _ _ _ 5V_ _ _ _|
|    | | | | | | | | | | | | | | |
|                          |
 --- Taster ---------------


 C1: 10µF
 Lspr: 8 Ohm, 3 Watt
     
 Dieser Code wurde unter CC-BY-3.0 (https://creativecommons.org/licenses/by/3.0/de/) veröffentlicht.
*/


#include <asmsynth.h>

#define DELAY70 delay_ms(70);
#define DELAY600 delay_ms(600);
#define DELAY5000 delay_ms(5000);

int taster=12; //Taster 'T'
int tasterstatus=0;
int frequenz[11];
int ton[6];

int tonfolge = 21705; //5-stelliger Integer - Bsp.: 21705
char sirene = 'W'; //F = Feueralarm, W = Warnung der Bevölkerung, E = Entwarnung, P = Probealarm, A = ABC-Alarm, X = Kein Doppelton

byte counter;


void setup()
{
  synthSetup();
  stop();
  pinMode(taster, INPUT);

  //Tonfrequenzen in Array schreiben
  frequenz[0] = 2400;
  frequenz[1] = 1060;
  frequenz[2] = 1160;
  frequenz[3] = 1270;
  frequenz[4] = 1400;
  frequenz[5] = 1530;
  frequenz[6] = 1670;
  frequenz[7] = 1830;
  frequenz[8] = 2000;
  frequenz[9] = 2200;
  frequenz[10] = 2600; //Wiederholton R


  //Schleife (Ziffern) in Array schreiben
  ton[5] = tonfolge % 10;
  ton[4] = (tonfolge / 10) % 10;
  ton[3] = (tonfolge / 100) % 10;
  ton[2] = (tonfolge / 1000) % 10;
  ton[1] = (tonfolge / 10000) % 10;

  //Prüfung für Wiederholton
  if (ton[1] == ton[2]) { ton[2] = 10; };
  if (ton[2] == ton[3]) { ton[3] = 10; };
  if (ton[3] == ton[4]) { ton[4] = 10; };
  if (ton[4] == ton[5]) { ton[5] = 10; };
}


void loop()
{
  tasterstatus = digitalRead(taster);

  if (tasterstatus == HIGH)
  {
    play();
  } 
}



start_interrupt
  //Fünftonfolge + Doppelton 1
  wave01();
  triangleWave();
  
  //Doppelton 2
  wave02();
  triangleWave();
end_interrupt

start_secondProgram
  //Lautstärke Fünftonfolge + Doppelton 1
  wave01_volume(120);
    
  //Lautstärke Doppelton 2
  wave02_volume(120);

  //Vorlauf (Sinnfrei in diesem Zweck)
  wave01_frequency(hz(0));
  wave02_frequency(hz(0));
  DELAY600

  //Doppelte Aussendung der Töne (je 70ms) mit 600ms Pause
  counter=0;
  while(counter<=1) 
  {
    wave01_frequency(hz(frequenz[ton[1]]));
    DELAY70
    wave01_frequency(hz(frequenz[ton[2]]));
    DELAY70
    wave01_frequency(hz(frequenz[ton[3]]));
    DELAY70
    wave01_frequency(hz(frequenz[ton[4]]));
    DELAY70
    wave01_frequency(hz(frequenz[ton[5]]));
    DELAY70
    
    wave01_frequency(hz(0));
    DELAY600
     
    counter++;
  }

  //Erzeugung Doppelton - 5sek.
  switch (sirene) {
    case 'F':
      wave02_frequency(hz(675));
      wave01_frequency(hz(1240));
      DELAY5000
      wave02_frequency(hz(0));
      wave01_frequency(hz(0));
      break;
    case 'W':
      wave02_frequency(hz(675));
      wave01_frequency(hz(825));
      DELAY5000
      wave02_frequency(hz(0));
      wave01_frequency(hz(0));
      break;
    case 'P':
      wave02_frequency(hz(675));
      wave01_frequency(hz(1860));
      DELAY5000
      wave02_frequency(hz(0));
      wave01_frequency(hz(0));
      break;
    case 'A':
      wave02_frequency(hz(1240));
      wave01_frequency(hz(1860));
      DELAY5000
      wave02_frequency(hz(0));
      wave01_frequency(hz(0));
      break;
    case 'E':
      wave02_frequency(hz(825));
      wave01_frequency(hz(1860));
      DELAY5000
      wave02_frequency(hz(0));
      wave01_frequency(hz(0));
      break;
    default:
      break;
  }
  
  stop();
end_secondProgram
