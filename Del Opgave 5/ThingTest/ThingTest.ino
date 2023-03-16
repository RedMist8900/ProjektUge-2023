#include <Wire.h>
#include <RTClib.h>

// LED, Buzzer og knap
#define LED 12
#define BUZZER 11
#define BUTTON 13 

// bytes to determind button state
byte lastButtonState = LOW;
byte ledState = LOW;

// Clock and Date
RTC_DS1307 rtc;

byte zero = 0x00;

char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

// Array of int's to transmit
int array[6];

void setup() {
  // Initialize Monitor
  Serial.begin(57600);

  // LED, Buzzer og knap
  pinMode(LED, HIGH);
  pinMode(BUTTON, INPUT);
  pinMode(BUZZER, OUTPUT);

  // CLock and Date
  Wire.begin();

  rtc.begin();

  // Adjusting time to pc time
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  // Run Once!! Sets the Clock on the hardware
  // rtc.setTime()
  //rtc.adjust(DateTime(2023, 3, 16, 9, 31, 0));
}

void loop() {
  // Button, LED and Buzzer
  byte buttonState = digitalRead(BUTTON);
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    if (buttonState == LOW) {
      ledState = (ledState == HIGH) ? LOW: HIGH;
      digitalWrite(LED, ledState);
      tone(BUZZER, 1000);
      delay(1000);
      noTone(BUZZER);
    }
  }

  // Getting the time and date into an object
  DateTime now = rtc.now();

  // Setting the values into variables
  int year = now.year();
  int month = now.month();
  int day = now.day();
  int hour = now.hour();
  int min = now.minute();
  int sec = now.second();

  // Basic Setting the variables into the array
  array[0] = year;
  array[1] = month;  
  array[2] = day;
  array[3] = hour;
  array[4] = min;
  array[5] = sec;

  // Printing array to check
  for(int k = 0; k < 6; k++){
    Serial.println(array[k]);
  }

  // Clear Transmit
  Wire.beginTransmission(9);
  Wire.write(zero);
  Wire.endTransmission();

  // Transmitting the data to the other Arduino Uno
  Wire.beginTransmission(9);
  for(int j = 0; j < 6; j++){
    Wire.write(array[j]);
  }
  Wire.endTransmission();

  // Delay 1 sec
  delay(1000);
}
