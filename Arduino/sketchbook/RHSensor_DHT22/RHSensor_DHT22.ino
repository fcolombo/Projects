/* Relative humidity and temperature monitoring
/* using the DHT22/AM2302 sensor
/* DHT Library: https://playground.arduino.cc/Main/DHTLib */

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

dht DHT; // create a DHT object
const int dataPin = 8;

void setup()
{
  Serial.begin(9600);
  Serial.println("Type,\tStatus,\tTemperature (C),\tHumidity (%)");
  
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
}

void loop()
{
  Serial.print("DHT22, \t");
 
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
  
  // present the results on the LCD as well
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(rh, 1);
  lcd.print(" %");
  
  delay(10000);
}
