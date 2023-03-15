// CONNECTIONS:
// DS1302 CLK/SCLK --> 6
// DS1302 DAT/IO --> 7
// DS1302 RST/CE --> 8
// DS1302 VCC --> 5v
// DS1302 GND --> GND

#include <Wire.h>
#include <ThreeWire.h>  // Include helper library to help create 					 the DS1302 object needed for this code
#include <RtcDS1302.h>  // Include DS1302 library with the correct 				 methods and properties
#include <RTClib.h>

#define CLOCK 6   // Define the constant variable CLOCK to be equal to 5 (the pin CLK is connected to)
#define DATE 7    // Define the constant variable DATE to be equal to 4 (the pin DAT is connected to)
#define RESET 8   // Define the constant variable RESET to be equal to 2 (the pin RST is connected to)

// Del Opgave 2
#define LED_PIN 12
#define BUTTON_PIN 13

// Del Opgave 3.2
#define BUZZER 11

byte lastButtonState = LOW;
byte ledState = LOW;

int array[6];


// Make a special ThreeWire class variable that holds all three wire connections
ThreeWire myWire(DATE,CLOCK,RESET); 

// Make an RTCDS1302 class variable (with the ThreeWire variable) to use for all time and date methods
RtcDS1302<ThreeWire> Rtc(myWire);

RTC_DS3231 rtc;


void setup () // Initialization code
{
  Serial.begin(57600); // Initialize Serial Monitor at 57600 baud

  // Del Opgave 2
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // Del Opgave 3
  pinMode(BUZZER, OUTPUT);

  Wire.begin();
  
  
  Rtc.Begin(); // Initialize the RTCDS1302 variable to use with    clock and date methods

  rtc.begin();

  //Rtc.SetDateTime(00, 31, 13, 3, 15, 3, 2023);  

  // Get current date and time in the right format from the DS1302 module
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__); 
  
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2023, 3, 15, 14, 35, 0));

  // If the Rtc-object doesn't contain a valid date/time format
  if (!Rtc.IsDateTimeValid())  
  {
    // Common Causes:
    //    1) first time running and device wasn't running yet
    //    2) the battery on the device is low or even missing

    // Print error to Serial Monitor
    Serial.println("RTC lost confidence in the DateTime!");
      
    // Take the date and time from the module and put it in the Rtc-object
    Rtc.SetDateTime(compiled);  
  }

  // If the Rtc-object for some reason is write protected
  if (Rtc.GetIsWriteProtected()) 
  {
    // Remove write protection from Rtc-variable
    Serial.println("RTC was write protected, enabling writing   now"); // Print error to Serial Monitor
    Rtc.SetIsWriteProtected(false); 
  }

  // If the Rtc-object didn't start properly and isn't running
  if (!Rtc.GetIsRunning()) 
  {
    // Print error to Serial Monitor
    Serial.println("RTC was not actively running, starting now"); 

    // Set the Rtc-object to be running    
    Rtc.SetIsRunning(true);
  }

  // Get current Date and Time and place it in the variable "now" that is of type RtcDateTime (object)
  RtcDateTime now = Rtc.GetDateTime(); 
  
  // If the time just fetched is older that the time currently saved in the module
  if (now < compiled) 
  {
    // Print status message to Serial Monitor
    Serial.println("RTC is older than compile time!  (Updating DateTime)"); 

    // Set current date and time in the module (update the modules date and time)
    Rtc.SetDateTime(compiled); 
  }
  // If the time just fetched is newer than the time currently saved in the modul
  else if (now > compiled) 
  {
    // Print status message to Serial Monitor
    Serial.println("RTC is newer than compile time. (this is expected)"); 
  }
  // If the time just fetched is equal to the time currently saved in the modul
  else if (now == compiled) 
  {
    // Print status message to Serial Monitor
    Serial.println("RTC is the same as compile time! (not expected but all is fine)"); 
  }
}

// Code to run continuously after initialization
void loop () 
{
  // Del Opgave 3.2
  byte buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    if (buttonState == LOW) {
      ledState = (ledState == HIGH) ? LOW: HIGH;
      digitalWrite(LED_PIN, ledState);
      tone(BUZZER, 1000);
      delay(1000);
      noTone(BUZZER);
    }
  }

  //Rtc.updateTime();

  // Get current Date and Time and place it in the variable "now" that is of type RtcDateTime (object)
  DateTime now = rtc.now(); 

  

  // Get Year from "now" variable and put into variable Year
  int Year = now.year();      

  // Get Month from "now" variable and put into variable Month
  int Month = now.month();    
  
  // Same as above…
  int Day = now.day();        
  int Hour = now.hour();
  int Minute = now.minute();
  int Second = now.second();

  // If the fetched time is not valid
  /*if (!now.IsValid()) 
  {
    // Common Causes:
    // The battery on the device is low or even missing and the power line was disconnected
    Serial.println("RTC lost confidence in the DateTime!"); 
    // Print status message in Serial Monitor
  }*/

    array[0] = Year;
    array[1] = Month;
    array[2] = Day;
    array[3] = Hour;
    array[4] = Minute;
    array[5] = Second;

  //Del Opgave 5
    Wire.beginTransmission(9);
    for(int i = 0; i < 6; i++){
        Wire.write(array[i]);
        Serial.println(array[i]);        
    }
    Wire.endTransmission();

  // Wait ten seconds then run loop again
  delay(1000);
}

