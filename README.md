# injectee
Test program for hardware fault injection supporting multiple platforms

Burn on the target hardware and try yo make the number cruncher fail.
Whenever possible there are 3 outputs that can be monitored:
* Standard serial output, speed 115200 8N1
* Software serial with default pins: RX pin 2, TX pin 3, speed 115200 8N1
* Default LED blinks 2 times on boot, ~1 per sec and 5 times fast if a failure was detected 
