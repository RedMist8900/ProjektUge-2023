#define LED_PIN 12
#define BUTTON_PIN 13
#define BUZZER 11

byte lastButtonState = LOW;
byte ledState = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
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
}
