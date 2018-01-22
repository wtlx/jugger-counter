

//**************************************************************//
//  Name    : Recognizes Soundpeaks, counts them and flashing LED in 1.5 sec intervals                      
//  Author  : Wolfgang L. 
//  Date    : 15 Januar, 2018    
//  Modified:                                 
//  Version : 1.1                                             
//  Notes   : First Sketch, have mercy :)                           //
//            calibrate the trigger volume directly on the  FC-04  //
//****************************************************************//

#include "SevSeg.h" //Die vorher hinzugefügte Library laden
SevSeg sevseg;      //Ein sieben Segment Objekt initialisieren

// Der FC-04 wird über den analogen Arduino Pin A0 angeschlossen 
int AudioPin = A0; // Der Analoge Pin 0 bekommt den Namen AudioPin
int zaehler = 0;
int set = 0;      // Dieser "Merker" sorgt dafür, dass nicht ein Trommelschlag 
                  // als mehrere erkannt werden weil sie zu lange nachhallen (Stichwort "entprellen")


///////////LED-Kram/////////////
int ledPin =  A5;                   // Pin-Nummer der LED
int ledState = LOW;                 // Status der LED
unsigned long previousMillis = 0;   // speichert, wann die LED an war
long OnTime = 250;                  // so lange soll die LED an sein (in Millisekunden)
long OffTime = 1250;                // so lange soll die LED an sein (in Millisekunden)





 
void setup() 
{         
pinMode(AudioPin, INPUT);
digitalWrite(AudioPin, HIGH); // Für echtes High bei Stille sorgen


pinMode(ledPin, OUTPUT);      // Den LED-Pin zum Outpu-Pin machen    

// ab hier komtt der Code für das 7Seg-Display         
byte numDigits = 4; //Hier wird die Anzahl der Ziffern angegeben
byte digitPins[] = {2, 3, 4, 5}; //Die Pins zu den Ziffern werden festgelegt
byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; //Die Pins zu den Segmenten werden festgelegt
sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins); 
// je nach Displayart COMMON_CATHODE oder COMMON_ANODE eintragen
}
 
void loop() {



/////////Hier wird die LED ein und ausgeschaltet////////////////////////
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();
 
  if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
  {
    ledState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }
  else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
  {
    ledState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(ledPin, ledState);    // Update the actual LED
  }
////////////////////////////////////////////////////////////////////////


/////////Hier wird auf Töne gehört und die gezählte Zahl ausgegeben/////
sevseg.refreshDisplay(); //hier nötig, da sonst die Zahl nur kurz blinkt
  if (digitalRead(AudioPin) == LOW && set == 0) {
    zaehler++;

sevseg.setNumber(zaehler); // Hier wird der Zählerstand an das Display übergeben...
sevseg.refreshDisplay(); // ...und hier dafür gesorgt, dass er angezeigt wird
sevseg.setBrightness(90); // Helligkeit von 0-100 

    set=1; // Hier beginnt die Magie des Entprellens
  }
 
  if (digitalRead(AudioPin) == HIGH && set == 1) {
    delay(550);
    set=0;
  }
////////////////////////////////////////////////////////////////////////
}










