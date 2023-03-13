#define LED_PIN 12
#define BUTTON_PIN 13
#define BUZZER 11


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(BUTTON_PIN) == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER, 1000);
  }
  else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER);
  }
}
