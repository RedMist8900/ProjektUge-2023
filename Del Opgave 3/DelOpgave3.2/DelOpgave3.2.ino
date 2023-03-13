// CONNECTIONS:
// DS1302 CLK/SCLK --> 6
// DS1302 DAT/IO --> 7
// DS1302 RST/CE --> 8
// DS1302 VCC --> 5v
// DS1302 GND --> GND

#include <ThreeWire.h>  // Include helper library to help create 					 the DS1302 object needed for this code
#include <RtcDS1302.h>  // Include DS1302 library with the correct 				 methods and properties

#define CLOCK 6   // Define the constant variable CLOCK to be equal to 5 (the pin CLK is connected to)
#define DATE 7    // Define the constant variable DATE to be equal to 4 (the pin DAT is connected to)
#define RESET 8   // Define the constant variable RESET to be equal to 2 (the pin RST is connected to)

// Del Opgave 2
#define LED_PIN 12
#define BUTTON_PIN 13

// Del Opgave 3.2
#define BUZZER 11

// Make a special ThreeWire class variable that holds all three wire connections
ThreeWire myWire(DATE,CLOCK,RESET); 

// Make an RTCDS1302 class variable (with the ThreeWire variable) to use for all time and date methods
RtcDS1302<ThreeWire> Rtc(myWire);


void setup () // Initialization code
{
  Serial.begin(57600); // Initialize Serial Monitor at 57600 baud

  // Del Opgave 2
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // Del Opgave 3
  pinMode(BUZZER, OUTPUT);
  
  Rtc.Begin(); // Initialize the RTCDS1302 variable to use with    clock and date methods

  // Get current date and time in the right format from the DS1302 module
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__); 
  
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
  // Del Opgave 2
  if (digitalRead(BUTTON_PIN) == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER, 1000);
  }
  else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER);
  }

  // Get current Date and Time and place it in the variable "now" that is of type RtcDateTime (object)
  RtcDateTime now = Rtc.GetDateTime(); 

  // Get Year from "now" variable and put into variable Year
  int Year = now.Year();      

  // Get Month from "now" variable and put into variable Month
  int Month = now.Month();    
  
  // Same as above…
  int Day = now.Day();        
  int Hour = now.Hour();
  int Minute = now.Minute();
  int Second = now.Second();

  // Print text in Serial Monitor without line break
  Serial.print("Year: ");
  
  // Print value of variable Year in Serial Monitor and then insert line break
  Serial.println(Year);
  
  // Print text in Serial Monitor
  Serial.print("Month: ");

  // Print value of variable Month in Serial Monitor and then insert line break
  Serial.println(Month);
  
  // Same as above....
  Serial.print("Day: ");
  Serial.println(Day);
  Serial.print("Hour: ");
  Serial.println(Hour);
  Serial.print("Minute: ");
  Serial.println(Minute);
  Serial.print("Second: ");
  Serial.println(Second);
  Serial.println();

  // If the fetched time is not valid
  if (!now.IsValid()) 
  {
    // Common Causes:
    // The battery on the device is low or even missing and the power line was disconnected
    Serial.println("RTC lost confidence in the DateTime!"); 
    // Print status message in Serial Monitor
  }

  // Wait ten seconds then run loop again
  delay(1000);
}
