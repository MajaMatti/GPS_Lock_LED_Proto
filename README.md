# GPS_Lock_LED_Proto
The Project is built inside a Box which is then locked with the electro-magnet. To unlock the Box someone has to bring the box to three different programmable 
GPS - locations (order is not important). The position match is indicated with three 5V-leds. If all locations have found, all leds are on the lock unlocks. 

Arduino - Project working with a UNO / NeoPixel 5V LED stripe with 3 LEDs / Neo 6-m gps module with antenna / electro magnet lock 5V / Li-Ion 18650 Battery with 

In the actual version the Project got a toggle button on PIN4 of the UNO to "reset" the EEPROM.
If not pressed, the UNO saves the location - matches when powered off and loads them back if powered on again. (Until the button is pressed and the Memory ist reset)

