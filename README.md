# GPS_Lock_LED_Proto
June 2020

The project is built inside a box, which is then locked by an electro-magnet. To unlock the box someone has to bring the box to three different programmable 
GPS - locations (order is not important). The position match is indicated with three 5V-leds. If all locations are found, all leds will turn on and the lock unlocks. 

Arduino - project working with a Nano v3 / NeoPixel 5V LED stripe with 3 LEDs / Neo 6-m gps module with antenna / electro magnet lock 5V / Li-Ion 18650 Battery

In the actual version the Project got a toggle button on PIN4 of the Nano to "reset" the EEPROM.
If not pressed, the Nano saves the location - matches when powered off and loads them back if powered on again. (Until the button is pressed and the Memory ist reset)

![git](https://user-images.githubusercontent.com/30718441/86538333-b7509d00-bef5-11ea-8610-ebcd58db8f13.PNG)

