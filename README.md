# GPS_Lock_LED_Proto
The Project is built inside a Box which is then locked with the electro-magnet. To unlock the Box someone has to bring the box to three different programmable 
GPS - locations (order is not important). The position match is indicated with three 5V-leds. If all locations have found, all leds are on and the lock unlocks. 

Arduino - Project working with a Nano v3 / NeoPixel 5V LED stripe with 3 LEDs / Neo 6-m gps module with antenna / electro magnet lock 5V / Li-Ion 18650 Battery

In the actual version the Project got a toggle button on PIN4 of the Nano to "reset" the EEPROM.
If not pressed, the Nano saves the location - matches when powered off and loads them back if powered on again. (Until the button is pressed and the Memory ist reset)

![alt text](https://www.chip.de/ii/5/6/7/6/2/8/4/8/43dff6dc96b32060.jpeg)
