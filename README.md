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
