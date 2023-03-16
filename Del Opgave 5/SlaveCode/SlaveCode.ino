#include <ThreeWire.h>  // Include helper library to help create 					 the DS1302 object needed for this code
#include <Wire.h>
#include <SevSeg.h>
#include <RtcDS1302.h>

int array[6];

// Del Opgave 6
SevSeg sevseg;

char dt[16];
char tm[16];

int tim;

void setup () // Initialization code
{
  Serial.begin(57600); // Initialize Serial Monitor at 57600 baud

  Wire.begin(9);

  Wire.onReceive(receiveEvent);

  byte numDigits = 4;  
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = true;
  bool updateWithDelays = true;  
  // variable above indicates that 4 resistors were placed on the digit pins.
  // set variable to 1 if you want to use 8 resistors on the segment pins.
  byte hardwareConfig = COMMON_CATHODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void receiveEvent(int x){
    for(int i = 0; i < x; i++){
        array[i] = Wire.read();
        //Serial.println(array[i]);
    }
    array[0] = array[0] + 1792;
    //Serial.println(array[0]);
    //Serial.println();
}

// Code to run continuously after initialization
void loop () 
{   
  sprintf(dt, "%02d/%02d/%02d", array[0],array[1],array[2]);
  sprintf(tm, "%02d:%02d:%02d", array[3],array[4],array[5]);  

  tim = (array[3] * 100 + array[4]);

  Serial.println(dt);
  Serial.println(tm);
  
  sevseg.setNumber(1234);
  sevseg.refreshDisplay(); // Must run repeatedly

  // Wait ten seconds then run loop again
  //delayMicroseconds(300);
  delay(5000);
}