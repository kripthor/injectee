//ONLY INCLUDE IF TEENSY BOARD
#include <SoftwareSerial.h>
#define rxPin 2
#define txPin 3
#define ITERS 2000
#define LED LED_BUILTIN

#define arch_log(s) Serial.print(s); SerialObj.print(s);
#define arch_logt(s, t) Serial.print(s,t); SerialObj.print(s,t);

SoftwareSerial SerialObj = SoftwareSerial(rxPin,txPin);

void arch_setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  SerialObj.begin(115200);
  Serial.begin(115200);
  pinMode(LED, OUTPUT); 
}

inline void arch_blink(uint8_t times, uint16_t blinktime) {
  while(times-- > 0) {
    digitalWrite(LED, HIGH);
    delay(blinktime);
    digitalWrite(LED, LOW);
    delay(blinktime);
  }  
}                   
