//ONLY INCLUDE IF ARCH IS FOR RPI2040. TESTED ON WAVESHARE RP2040-ZERO
#ifdef ARDUINO_ARCH_RP2040
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define ITERS 500

#define LED        16
#define NUMPIXELS 1

#define arch_log(s) Serial.print(s); SerialObj.print(s);
#define arch_logt(s, t) Serial.print(s,t); SerialObj.print(s,t);

Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_GRB + NEO_KHZ800);
SoftwareSerial SerialObj = SoftwareSerial(2,3);

void arch_setup() {
  delay(1000);
  SerialObj.begin(115200);
  Serial.begin(115200);
  pixels.begin();
  pixels.clear();  
  delay(1000);
}

inline void arch_blink(uint8_t times, uint16_t blinktime) {
  while(times-- > 0) {
    pixels.setPixelColor(0, pixels.Color(100, 0, 0));
    pixels.show();
    delay(blinktime);
    pixels.clear();
    pixels.show();
    delay(blinktime);
  }  
}                   
 
#endif
