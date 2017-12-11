/* Play tune, synchronized with LEDs and
/* text messages on a LCD display */

#include <LiquidCrystal.h>
#include "Note.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7;
const int en = 6;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String txtMessage1 = "Frohe Weihnachten!";
String txtMessage2 = "Buon Natale!";

// note frequencies
int DO  = 262;
int RE  = 294;
int MI  = 330;
int FA  = 349;
int SOL = 392;
int LA  = 440;
int SI  = 494;
int DOM = 523;
int REM = 587;

// length of notes and delay between notes
int quarter = 200;
int half    = quarter * 2;
int whole   = quarter * 4;
int noteDelay = 500;

// output pins
const int solLEDPin = 8;
const int laLEDPin  = 9;
const int siLEDPin  = 10;
const int domLEDPin = 11;
const int remLEDPin = 12;
const int piezoPin  = 13;

// melody to play
notes* jingleBells[] = {
  create_notes(SI, quarter),
  create_notes(SI, quarter),
  create_notes(SI, half),
  create_notes(SI, quarter),
  create_notes(SI, quarter),
  create_notes(SI, half),
  create_notes(SI, quarter),
  create_notes(REM, quarter),
  create_notes(SOL, quarter),
  create_notes(LA, quarter),
  create_notes(SI, whole),
  create_notes(DOM, quarter),
  create_notes(DOM, quarter),
  create_notes(DOM, half),
  create_notes(SI, quarter),
  create_notes(SI, quarter),
  create_notes(SI, half),
  create_notes(SI, quarter),
  create_notes(LA, quarter),
  create_notes(LA, quarter),
  create_notes(SI, quarter),
  create_notes(LA, half),
  create_notes(REM, half),
  create_notes(SI, quarter),
  create_notes(SI, quarter),
  create_notes(SI, half),
  create_notes(SI, quarter),
  create_notes(SI, quarter),
  create_notes(SI, half),
  create_notes(SI, quarter),
  create_notes(REM, quarter),
  create_notes(SOL, quarter),
  create_notes(LA, quarter),
  create_notes(SI, whole),
  create_notes(DOM, quarter),
  create_notes(DOM, quarter),
  create_notes(DOM, half),
  create_notes(SI, quarter),
  create_notes(SI, quarter),
  create_notes(SI, half),
  create_notes(REM, quarter),
  create_notes(REM, quarter),
  create_notes(DOM, quarter),
  create_notes(LA, quarter),
  create_notes(SOL, whole)
};

// extract substrings from string
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void setup()
{
  Serial.begin(9600);
  
  // 2 seconds delay
  delay(2000);
  
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  // set LED pins
  for(int pinNumber = 8; pinNumber < 13; pinNumber++)
  {
    pinMode(pinNumber, OUTPUT);
    delay(200);
    digitalWrite(pinNumber, HIGH);
  }
  
  delay(500);
  
  for(int pinNumber = 8; pinNumber < 13; pinNumber++)
  {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
  
  delay(1000);
}

void loop()
{ 
  int txtStartLine1 = 0;
  int txtStartLine2 = 0;
  String firstWord = getValue(txtMessage1,' ', 0);
  String secondWord = getValue(txtMessage1, ' ', 1);
  
  if (firstWord.length() <= 16) {
    txtStartLine1 = floor((16 - firstWord.length()) / 2.0);
  }
  if (secondWord.length() <= 16) {
    txtStartLine2 = floor((16 - secondWord.length()) / 2.0);
  }
    
  for(int iter = 0; iter < sizeof(jingleBells)/sizeof(jingleBells[0]); iter++) {
    
    int freq = jingleBells[iter]->frequency;
    int len = jingleBells[iter]->length;
    Serial.println("Frequency: " + String(freq) + "\t Length: " + String(len));

    // play tone
    tone(piezoPin, freq, len);
    
    // show first text message
    if (iter < firstWord.length()) {
      lcd.setCursor(txtStartLine1 + iter, 0);
      lcd.print(firstWord[iter]);
    }
    else if (iter < (firstWord.length() + secondWord.length())) {
      lcd.setCursor(txtStartLine2 + (iter - firstWord.length()), 1);
      lcd.print(secondWord[iter - firstWord.length()]);
    }
    
    // switch LEDs rhythmically on and off
    if (freq == SOL | freq == LA | freq == SI | freq == DOM | freq == REM) {      
      if (freq == SOL){
        digitalWrite(solLEDPin, HIGH);
        delay(noteDelay/2);
        digitalWrite(solLEDPin, LOW);
        delay(noteDelay/2);
      }
      else if (freq == LA){
        digitalWrite(laLEDPin, HIGH);
        delay(noteDelay/2);
        digitalWrite(laLEDPin, LOW);
        delay(noteDelay/2);
      }
      else if (freq == SI){
        digitalWrite(siLEDPin, HIGH);
        delay(noteDelay/2);
        digitalWrite(siLEDPin, LOW);
        delay(noteDelay/2);
      }
      else if (freq == DOM){
        digitalWrite(domLEDPin, HIGH);
        delay(noteDelay/2);
        digitalWrite(domLEDPin, LOW);
        delay(noteDelay/2);
      }
      else {
        digitalWrite(remLEDPin, HIGH);
        delay(noteDelay/2);
        digitalWrite(remLEDPin, LOW);
        delay(noteDelay/2);
      }
    }
    else {
      delay(noteDelay);
    }
  
  }
  
  // fly-in effect for second text message
  int startPoint = 2;   //set starting point
  int endPoint = txtMessage2.length() + startPoint;    //set ending point
  lcd.clear();

  //for each letter of the string starting from the last one.
  for (int i = txtMessage2.length() - 1; i >= 0; i--)
  {
    startPoint = 0;

    //for each position on the LCD display
    for (int j = 0; j < endPoint; j++)
    {

      lcd.setCursor(startPoint, 0);
      lcd.print(txtMessage2[i]);

      delay(50);

      if (startPoint != endPoint - 1) {
        lcd.setCursor(startPoint, 0);
        lcd.print(' ');
      }
      
      startPoint++;
    }
    endPoint--;
    delay(50);
  }
  
  // blink effect for second text message
  for(int counter = 0; counter < 4; counter++)
  {
    lcd.noDisplay();
    delay(300);
    lcd.display();
    delay(300);
  }
  
  // one minute pause
  delay(60000);
  
  lcd.clear();
}
