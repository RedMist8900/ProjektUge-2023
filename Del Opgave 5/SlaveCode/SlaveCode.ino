// CONNECTIONS:
// DS1302 CLK/SCLK --> 6
// DS1302 DAT/IO --> 7
// DS1302 RST/CE --> 8
// DS1302 VCC --> 5v
// DS1302 GND --> GND

#include <ThreeWire.h>  // Include helper library to help create 					 the DS1302 object needed for this code
#include <Wire.h>

int array[6];
byte ahhh;

void setup () // Initialization code
{
  Serial.begin(57600); // Initialize Serial Monitor at 57600 baud

  Wire.begin(9);

  Wire.onReceive(receiveEvent);
}

void receiveEvent(int x){
    for(int i = 0; i < x; i++){
        array[i] = Wire.read();
        Serial.println(array[i]);
    }
    Serial.println("");
    array[0] = array[0] + 2048;
}

// Code to run continuously after initialization
void loop () 
{
  

  // Wait ten seconds then run loop again
  delay(10000);
}