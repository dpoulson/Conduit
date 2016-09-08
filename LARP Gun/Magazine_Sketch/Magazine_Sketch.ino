#include <EEPROM.h>;

#define AMMO_LEFT 0
#define TRIGGER 1
#define AMMO_ADD 2
#define AMMO_CLEAR 3


unsigned char ammo_count=2;
int clearState = 0;
int lastClearState = 0;
int buttonState = 0;
int lastButtonState = 0;
int triggerState = 0;
int lastTriggerState = 0;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(AMMO_LEFT, OUTPUT);
  pinMode(TRIGGER, INPUT);
  pinMode(AMMO_ADD, INPUT);
  pinMode(AMMO_CLEAR, INPUT);
  
  //EEPROM.write(0, ammo_count);
  ammo_count=EEPROM.read(0);
  
  if (ammo_count > 0) {
     digitalWrite(AMMO_LEFT, HIGH);   
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:


  // Clear button
  clearState = digitalRead(AMMO_CLEAR);
  if (clearState != lastClearState) {
    if (clearState == HIGH) {
       ammo_count=0;
    }
    EEPROM.write(0, ammo_count);
    digitalWrite(AMMO_LEFT, LOW);
  }
  lastClearState = clearState;

  // Add ammo button
  buttonState = digitalRead(AMMO_ADD);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      if (ammo_count <= 0 ){
        ammo_count=1;
      } else {
        ammo_count++;
      }
    }
    EEPROM.write(0, ammo_count);
    digitalWrite(AMMO_LEFT, HIGH);
  }
  lastButtonState = buttonState;

  // TRIGGER!!!! 
  triggerState = digitalRead(TRIGGER);
  if (triggerState != lastTriggerState) {
    if (triggerState == HIGH) {
      ammo_count--;
      if (ammo_count <= 0 ){
        ammo_count=0;
        digitalWrite(AMMO_LEFT, LOW);
      }
      EEPROM.write(0, ammo_count);   
    }
  }
  lastTriggerState = triggerState;

  
}



