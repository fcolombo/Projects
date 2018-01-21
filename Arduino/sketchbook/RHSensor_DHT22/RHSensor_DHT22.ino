/* Relative humidity and temperature monitoring
/* using the DHT22/AM2302 sensor
/* DHT Library: https://playground.arduino.cc/Main/DHTLib
/* Initialization procedure from
/* https://forum.arduino.cc/index.php?topic=184356.msg1753894#msg1753894 */

#include <LiquidCrystal.h>
#include "dht.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7;
const int en = 6;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int dataPin = 8;
const int vccPin = 9;

void setup()
{
  Serial.begin(9600);
  Serial.println("Status,\tTemperature (C),\tHumidity (%)");
  
  pinMode(vccPin, OUTPUT);
  digitalWrite(vccPin, LOW);
  
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  lcd.setCursor(0, 1);
  lcd.print("Wait 120 sec");
}

void loop()
{ 
  // wait 120 seconds
  delay(120000);
  
  // bring VCC to high status
  digitalWrite(vccPin, HIGH);
  
  // delay 1 second
  delay(1000);
  
  dht DHT; // create a DHT instance
  
  // wait 15 seconds
  delay(15000);
  
  int data = DHT.read22(dataPin); // reads the data from the sensor
  
  switch(data)
  {
    case DHTLIB_OK:  
      Serial.print("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t"); 
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t"); 
      break;
    default:
      Serial.print("Unknown error,\t"); 
      break;
  }
  
  float temp = DHT.temperature; // gets the values of the temperature
  float rh = DHT.humidity; // gets the values of the humidity
  
  Serial.print(temp, 1);
  Serial.print(",\t");
  Serial.println(rh, 1);
  
  // output the results on the LCD as well
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp = ");
  lcd.print(temp, 1);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("RH = ");
  lcd.print(rh, 1);
  lcd.print(" %");
  
  // bring VCC to low status
  digitalWrite(vccPin, LOW);
}
