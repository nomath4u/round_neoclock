#include <Adafruit_NeoPixel.h>

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

#define NEOPIN 10
#define DEBUG_PIN 8

RTC_DS3231 rtc;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, NEOPIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel single = Adafruit_NeoPixel(1, DEBUG_PIN, NEO_GRBW + NEO_KHZ800);

uint32_t magenta = strip.Color(255, 0, 64, 0);
uint32_t green = strip.Color(0, 255, 0, 0);
uint32_t blue = strip.Color(0, 0, 255, 0);

void setup () {

strip.setBrightness(32);
  strip.begin();
  single.begin();
  Serial.begin(9600);

  //delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1){
      single.setPixelColor(0, blue); //Blue;
      single.show();
    }
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Uncomment this if the battery came out.
  }
  
}

void loop () {
    DateTime now = rtc.now();    

    DateTime future (now + TimeSpan(0, 0, 5, 0)); //__TIME__ seems to be off by a few minutes for some reason.
    uint8_t minute_place = future.minute() / 5;
    uint8_t hour_place = future.hour() % 12;
//    Serial.print(" now + 7d + 30s: ");
//    Serial.print(future.year(), DEC);
//    Serial.print('/');
//    Serial.print(future.month(), DEC);
//    Serial.print('/');
//    Serial.print(future.day(), DEC);
//    Serial.print(' ');
//    Serial.print(future.hour(), DEC);
//    Serial.print(':');
//    Serial.print(future.minute(), DEC);
//    Serial.print(':');
//    Serial.print(future.second(), DEC);
//    Serial.println();
//    
//    Serial.println();
//    Serial.print("Hour: ");
//    Serial.println(hour_place);
//    Serial.print("Minute: ");
//    Serial.println(minute_place);
    strip.clear();
    strip.setPixelColor( minute_place , magenta);
    strip.setPixelColor( hour_place, green);
       
    /* Combine hour and minute if needed*/
    if( minute_place == hour_place ){
      strip.setPixelColor( minute_place, magenta + green );
    }
    
    /* Combine Orientation marker with color if needed */
    uint32_t up = strip.getPixelColor(0) +  strip.Color(0,0,0,40);
    strip.setPixelColor(0, up);
    
    strip.show();
    delay(3000);
}
