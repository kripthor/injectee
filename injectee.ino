// Program to test hardware fault injections
// Burn on the target hardware and try yo make the number crunching fail.
// Whenever possible there are 3 outputs that can be monitored:
// Standard serial output 115200 8N1
// Software serial RX pin2 / TX pin3 115200 8N1
// Default LED blinks 2 times on boot, ~1 per sec and 5 times fast if a failure was detected 

#define VERSION "Injectee v0.0.1"

#ifdef ARDUINO_ARCH_RP2040
 #include "FI_RP2040.h"
#elif ESP8266
 #include "FI_ESP8266.h"
#elif ESP32
 #include "FI_ESP32.h"
#elif defined(__MK20DX256__)
 #include "FI_TEENSY.h"
#else
 #include "FI_GenericBoard.h"
#endif

char const str_to_crunch[] = "00000000000000000000000000000000\r\n"
                             "11111111111111111111111111111111\r\n"
                             "00000000000000000000000000000000\r\n"
                             "11111111111111111111111111111111\r\n"
                             "00000000000000000000000000000000\r\n";
                     
const int len_to_crunch = strlen(str_to_crunch);
uint32_t crunch_ok = 0;
uint32_t crunch_res = 0;
uint32_t counter = 0;

//inline 'dummy hash' function to crunch some data (minimize function calls to crash 'better')
//can and should be optimized a bit further
inline uint32_t crunch() {
  uint32_t x = 0;
  for(int i = 0;i<len_to_crunch;i++) x = (x + i * 31337) ^ (((uint32_t)str_to_crunch[i]) << (i%24));  
  return x;
}


//call arch specific setup functions and calculate initial crunch
void setup() {
  arch_setup();
  arch_blink(2,500);
  arch_log(VERSION);
  arch_log("\r\nInitializing number crunching of:\r\n");
  arch_log(str_to_crunch);
  crunch_ok = crunch();
  arch_log("Crunch = 0x");
  arch_logt(crunch_ok, HEX);
  arch_log("\r\nStarting loop...\r\n");
}

//loop forever calculating new crunch value and comparing with crunch value calculated on setup
//if failure, blink 5 times and print it 

void loop() {
  counter++;
  long start = millis();
  uint16_t lps = 0; // loops per second
  while (millis() - start < 1000) {
    lps++;
    for (int i = 0; i < ITERS; i++) {
    //CRUNCH SOME DATA
      crunch_res = crunch();
    
    //TEST FOR CALCULATION FAILURE
      if (crunch_res != crunch_ok)  {
        
        // FAULT INJECTION DETECTED: BLINK AND LOG (FURTHER EXECUTION IS HIGHLY UNSTABLE)
        arch_blink(5,100);
        arch_log("\r\noO ! CRUNCH FAILURE ! Oo\r\n");
        arch_logt(counter, DEC);
        arch_log(" | 0x"); arch_logt(crunch_ok, HEX);
        arch_log(" == 0x"); arch_logt(crunch_res, HEX);
        arch_log("\r\n");
        arch_log(str_to_crunch);
        delay(3000);
      }
    }
  }
  arch_blink(1,50);
  arch_logt(counter, DEC);
  arch_log(" | ");
  arch_logt(lps,DEC);
  arch_log(" lps | 0x"); arch_logt(crunch_ok, HEX);
  arch_log(" == 0x"); arch_logt(crunch_res, HEX);
  arch_log("\r\n");
}
