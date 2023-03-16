// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <RTClib.h>
#include <Wire.h>

RTC_DS1307 rtc;

// LED, Buzzer og knap
#define LED_PIN 12
#define BUZZER 11
#define BUTTON_PIN 13 

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Array of int's to transmit
int array[6];

// bytes to determind button state
byte lastButtonState = LOW;
byte ledState = LOW;

void setup () {   
  Serial.begin(57600);
 
  #ifndef ESP8266
    while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  Wire.begin();

  // LED, Buzzer og knap
  pinMode(LED_PIN, HIGH);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () {
    // Clock and Date
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();


    array[0] = now.year();
    array[1] = now.month();
    array[2] = now.day();
    array[3] = now.hour();
    array[4] = now.minute();
    array[5] = now.second();    

    // Button, LED and Buzzer
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

    Wire.beginTransmission(9);
    for(int h = 0; h < 6; h++){
      Wire.write(array[h]);
    }
    Wire.endTransmission();
    
    Serial.println();
    delay(1000);
}
