#include <EEPROM.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>


#define PIN       9 // 
#define NUMPIXELS 3 // 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Choose two Arduino pins to use for software serial
int RXPin = 2; //TX auf dem Modul
int TXPin = 3; //RX auf dem Modul

int GPSBaud = 9600;
int LockPin = 8;

int counter = 0;

// GPS VARIABLEN

bool gps1 = false;
bool gps2 = false;
bool gps3 = false;

// EEPROM ADDRESS

int addgps1 = 0;
int addgps2 = 1;
int addgps3 = 2;

// EEPROM Var

int eeprom_gps1 = 0;
int eeprom_gps2 = 0;
int eeprom_gps3 = 0;

int debug = 2;

//Inbetriebnahme Koordinaten:
/*
float Latitude_1 = 52.489784;
float Longitude_1 = 13.444000;

float Latitude_2  = Latitude_1;
float Longitude_2 = Longitude_1;

float Latitude_3  = Latitude_1;
float Longitude_3 = Longitude_1;
*/

//LOCATION Coordinates:

float Latitude_1  = 52.490830;
float Longitude_1 = 13.445744;

float Latitude_2  = 52.490093;
float Longitude_2 = 13.442485;

float Latitude_3  = 52.489395;
float Longitude_3 = 13.443457;



float tolWindowLat = 0.0003;
float tolWindowLng = 0.0004;

// LOCATION WINDOW 1:

float UntereGrenzeLat_1 = Latitude_1 - tolWindowLat;
float ObereGrenzeLat_1 = Latitude_1 + tolWindowLat;
float UntereGrenzeLng_1 = Longitude_1 - tolWindowLng;
float ObereGrenzeLng_1 = Longitude_1 + tolWindowLng;

// LOCATION WINDOW 2:

float UntereGrenzeLat_2 = Latitude_2 - tolWindowLat;
float ObereGrenzeLat_2 = Latitude_2 + tolWindowLat;
float UntereGrenzeLng_2 = Longitude_2 - tolWindowLng;
float ObereGrenzeLng_2 = Longitude_2 + tolWindowLng;

// LOCATION WINDOW 3:

float UntereGrenzeLat_3 = Latitude_3 - tolWindowLat;
float ObereGrenzeLat_3 = Latitude_3 + tolWindowLat;
float UntereGrenzeLng_3 = Longitude_3 - tolWindowLng;
float ObereGrenzeLng_3 = Longitude_3 + tolWindowLng;


// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

//      __ _/_   _ 
//    _\/_'/ /_//_/
//             /  

void setup()
{
  // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);
  pinMode(LockPin, OUTPUT);

  // LEDS - NeoPixel

  pixels.begin();
  pixels.show();
  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);

Serial.println("##########################################");
Serial.println("Coord 1 Latitude low:");
Serial.println(UntereGrenzeLat_1,6);
Serial.println("Coord 1 Latitude high:");
Serial.println(ObereGrenzeLat_1,6);
Serial.println("Coord 1 Langitude low:");
Serial.println(UntereGrenzeLng_1,6);
Serial.println("Coord 1 Langitude high:");
Serial.println(ObereGrenzeLng_1,6);
Serial.println();

Serial.println("##########################################");
Serial.println("Coord 2 Latitude low:");
Serial.println(UntereGrenzeLat_2,6);
Serial.println("Coord 2 Latitude high:");
Serial.println(ObereGrenzeLat_2,6);
Serial.println("Coord 2 Langitude low:");
Serial.println(UntereGrenzeLng_2,6);
Serial.println("Coord 2 Langitude high:");
Serial.println(ObereGrenzeLng_2,6);
Serial.println();

Serial.println("##########################################");
Serial.println("Coord 3 Latitude low:");
Serial.println(UntereGrenzeLat_3,6);
Serial.println("Coord 3 Latitude high:");
Serial.println(ObereGrenzeLat_3,6);
Serial.println("Coord 3 Langitude low:");
Serial.println(UntereGrenzeLng_3,6);
Serial.println("Coord 3 Langitude high:");
Serial.println(ObereGrenzeLng_3,6);
Serial.println();

// EEPROM Read

eeprom_gps1 = EEPROM.read(addgps1);
eeprom_gps2 = EEPROM.read(addgps2);
eeprom_gps3 = EEPROM.read(addgps3);

pixels.setPixelColor(0, pixels.Color(0, 0, 0));
pixels.setPixelColor(1, pixels.Color(0, 0, 0));
pixels.setPixelColor(2, pixels.Color(0, 0, 0));




}

//     /_  _  _ 
//    //_//_//_/
//          /   

void loop()
{

switch (debug) {
  case 1:
  
// EEPROM eraser

  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  
    break;
  case 2:

  //eepromSetup();
  
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();
 
      
      
  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }
      
    break;
  default:

    break;
}
}

//      _/. __  /_     /_ _/|_ 
//    /_//_\/_///_|/_/// // /_/
//         /       _/      

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  }
  else
  {
    Serial.println("Location: Not Available");

    
    
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

eepromSetup();

// Check the Values:

  if ((UntereGrenzeLat_1 < gps.location.lat())&& (gps.location.lat()< ObereGrenzeLat_1)&&(UntereGrenzeLng_1 < gps.location.lng())&&(gps.location.lng() < ObereGrenzeLng_1)){
    
    gps1 = true;
    EEPROM.write(addgps1, gps1);
    Serial.println(gps.location.lng());
    Serial.println(gps.location.lat());
    Serial.println(gps1);
  }
    
  if ((UntereGrenzeLat_2 < gps.location.lat())&& (gps.location.lat()< ObereGrenzeLat_2)&&(UntereGrenzeLng_2 < gps.location.lng())&&(gps.location.lng() < ObereGrenzeLng_2)){
  
    gps2 = true;
    EEPROM.write(addgps2, gps2);
    Serial.println(gps.location.lng());
    Serial.println(gps.location.lat());
    Serial.println(gps2);
  }
    
  if ((UntereGrenzeLat_3 < gps.location.lat())&& (gps.location.lat()< ObereGrenzeLat_3)&&(UntereGrenzeLng_3 < gps.location.lng())&&(gps.location.lng() < ObereGrenzeLng_3)){
    
    gps3 = true;
    EEPROM.write(addgps3, gps3);
    Serial.println(gps.location.lng());
    Serial.println(gps.location.lat());
    Serial.println(gps3);
  }


// LED CONTROL...

  if (gps1 == true) {
    pixels.setPixelColor(0, pixels.Color(150, 0, 0));
    pixels.show();
  } 
  else
  {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
  }
  if(gps2 == true) {

     pixels.setPixelColor(1, pixels.Color(0, 150, 0));
     pixels.show();
  }
  else
  {
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.show();
  }
  if(gps3 == true) {

     pixels.setPixelColor(2, pixels.Color(0, 0, 150));
     pixels.show();
  }
  else
  {
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.show();
  }


//  UNLOCK THE LOCK....

  if((gps1 == true) && (gps2 == true) && (gps3 == true)){
  digitalWrite(LockPin, HIGH);   //open the Lock
  }

  
  Serial.println();
  Serial.println();
  delay(1000);
  
}



void eepromSetup()
{
    // Check the EEPROM values:

    // if there is a EEPROM value equal true then  set the corresponding LED RGB to its color.
    if (eeprom_gps1 == 1) {
        gps1 = true;
    }
    if (eeprom_gps2 == 1) {
        gps2 = true;
    }
    if (eeprom_gps3 == 1) {
        gps3 = true;
    }
    if (gps1 == true) {
        pixels.setPixelColor(0, pixels.Color(150, 0, 0));
        pixels.show();
    } 
    if(gps2 == true) {
        pixels.setPixelColor(1, pixels.Color(0, 150, 0));
        pixels.show();
    }
    if(gps3 == true) {
        pixels.setPixelColor(2, pixels.Color(0, 0, 150));
        pixels.show();
    }
}


