//ONLY INCLUDE IF ARCH IS FOR ESP32
//The ESP32-S2/C3/S3/C2 has a built-in temperature sensor. 
#ifdef CONFIG_IDF_TARGET_ESP32C3
 #define LED 12
#else
 #define LED LED_BUILTIN
#endif

#define ITERS 500

#define arch_log(s) Serial.print(s); Serial1.print(s);
#define arch_logt(s, t) Serial.print(s,t); Serial1.print(s,t);

void arch_setup() {
  Serial1.begin(115200, SERIAL_8N1, 2, 3);
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
