# ultrasonic-arduino

An Arduino-based ultrasonic distance module communicating through i2c protocol.

Hardware
--------
- US-100 or other compatible module
- Arduino Pro Mini

### Pin-Pin map
No|Trigger|Echo
----|-------|----
0|Pin 3|Pin 2
1|Pin 5|Pin 4
2|Pin 7|Pin 6
3|Pin 9|Pin 8

Usage
-----
Connect i2c wire to Arduino, configure your device as i2c master, then you are ready to go.

i2c address: 0x08

First, make a write call and write a byte (indicating No. of ultrasonic sensor)

Second, make a read call and read two byte (big endian), translate it and get final distance
