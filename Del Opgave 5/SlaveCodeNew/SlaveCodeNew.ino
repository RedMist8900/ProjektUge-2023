#include <Wire.h>
#include <LiquidCrystal.h> 

int Contrast=75;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

int array[6];

char dt[16];
char tm[16];

void setup () // Initialization code
{
  Serial.begin(57600); // Initialize Serial Monitor at 57600 baud

  Wire.begin(9);

  Wire.onReceive(receiveEvent);

  analogWrite(6,Contrast);
  lcd.begin(16, 2);

}

// Handles the tranmission of data from other Arduino
void receiveEvent(int x){
    for(int i = 0; i < x; i++){
        array[i] = Wire.read();
    }
    array[0] = array[0] + 1792;
}

// Code to run continuously after initialization
void loop () 
{   
  sprintf(dt, "%02d/%02d/%02d", array[0],array[1],array[2]);
  sprintf(tm, "%02d:%02d:%02d", array[3],array[4],array[5]);  

  lcd.clear();
  lcd.noAutoscroll();
  
  //Serial.println(dt);
  //Serial.println(tm);
  
  lcd.setCursor(0, 0);
  lcd.print(dt);

  lcd.setCursor(0, 1);
  lcd.print(tm);

  // Wait ten seconds then run loop again
  //delayMicroseconds(300);
  delay(2000);
}