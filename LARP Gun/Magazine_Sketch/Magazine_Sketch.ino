#include <EEPROM.h>;

#define AMMO_LEFT 0
#define TRIGGER 1
#define AMMO_ADD 2
#define AMMO_CLEAR 3

unsigned char ammo_count=0;
int buttonState = 0;
int lastButtonState = 0;

void setup() {
  // put your setup code here, to run once:

  GIMSK = 0b00100000;
  PCMSK = 0b00000010;
  sei();
  
  pinMode(AMMO_LEFT, OUTPUT);
  pinMode(TRIGGER, INPUT);
  pinMode(AMMO_ADD, INPUT);
  pinMode(AMMO_CLEAR, INPUT);
  
  ammo_count=EEPROM.read(0);
  
  if (ammo_count > 0) {
     digitalWrite(AMMO_LEFT, HIGH);   
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (digitalRead(AMMO_CLEAR == HIGH)) {
    ammo_count=0;
    digitalWrite(AMMO_LEFT, LOW);
    EEPROM.write(0, ammo_count);
  }
  
  buttonState = digitalRead(AMMO_ADD);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      ammo_count++;
    }
  }
  lastButtonState = buttonState;
}

ISR(PCINT0_vect) {
  ammo_count--;
  EEPROM.write(0, ammo_count);
  if (ammo_count <= 0 ){
    digitalWrite(AMMO_LEFT, LOW);
  }
}

