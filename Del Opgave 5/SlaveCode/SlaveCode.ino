// CONNECTIONS:
// DS1302 CLK/SCLK --> 6
// DS1302 DAT/IO --> 7
// DS1302 RST/CE --> 8
// DS1302 VCC --> 5v
// DS1302 GND --> GND

#include <ThreeWire.h>  // Include helper library to help create 					 the DS1302 object needed for this code
#include <Wire.h>
#include <SevSeg.h>
#include <RtcDS1302.h>

int array[6];
byte ahhh;

// Del Opgave 6
SevSeg sevseg;

char dt[16];
char tm[16];

int dat;
int tim;

String time = "";

int a = 6;
int b = 7;
int c = 8;
int d = 9;
int e = 10;
int f = 11;
int g = 12;
int h = 13;

void setup () // Initialization code
{
  Serial.begin(57600); // Initialize Serial Monitor at 57600 baud

  Wire.begin(9);

  Wire.onReceive(receiveEvent);

  pinMode(a, HIGH);
  pinMode(b, HIGH);
  pinMode(c, HIGH);
  pinMode(d, HIGH);
  pinMode(e, HIGH);
  pinMode(f, HIGH);
  pinMode(g, HIGH);
  pinMode(h, HIGH);

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
        Serial.println(array[i]);
    }
    Serial.println("");
    array[0] = array[0] + 2048;
}

// Code to run continuously after initialization
void loop () 
{
  clearLEDs();    
  sprintf(dt, "%02d/%02d/%02d", array[0],array[1],array[2]);
  sprintf(tm, "%02d:%02d:%02d", array[3],array[4],array[5]);  

  dat = array[3] + array[4];
  tim = array[4];  

  ahhh = array[5];

  time = (int)array[1] + ":" + (int)array[2];

  Serial.println(tim);
  Serial.println("");

  sevseg.setNumber(tim, 2);
  sevseg.refreshDisplay(); // Must run repeatedly

  // Wait ten seconds then run loop again
  //delayMicroseconds(300);
  delay(100);
}

void clearLEDs(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}