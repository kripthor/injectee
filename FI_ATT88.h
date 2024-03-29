//ONLY INCLUDE IF NO KNOWN ARCH
#include <SoftwareSerial.h>
#define rxPin 2
#define txPin 3
#define ITERS 100
#define LED LED_BUILTIN
#define OVERRIDE_STR

#define arch_log(s)  SerialObj.print(s);
#define arch_logt(s, t)  SerialObj.print(s,t);

char const str_to_crunch[] = "000000000\r\n"
                             "111111111\r\n"
                             "000000000\r\n"
                             "111111111\r\n"
                             "000000000\r\n";

SoftwareSerial SerialObj = SoftwareSerial(rxPin,txPin);

void arch_setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  SerialObj.begin(115200);
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
