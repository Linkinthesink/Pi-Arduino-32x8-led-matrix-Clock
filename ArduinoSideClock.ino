// Program to demonstrate the MD_Parola library
//
// Display the time in one zone and other information scrolling through in
// another zone.
// - Time is shown in a user defined fixed width font
// - Scrolling text uses the default font
// - Temperature display uses user defined characters
// - Optional use of DS1307 module for time and DHT11 sensor for temp and humidity
// - DS1307 library (MD_DS1307) found at https://github.com/MajicDesigns/DS1307
// - DHT11 library (DHT11_lib) found at http://arduino.cc/playground/Main/DHT11Lib
//
// NOTE: MD_MAX72xx library must be installed and configured for the LED
// matrix type being used. Refer documentation included in the MD_MAX72xx
// library or see this link:
// https://majicdesigns.github.io/MD_MAX72XX/page_hardware.html
//

// Use the DHT11 temp and humidity sensor
#define USE_DHT11 0

// Use the DS1307 clock module
#define USE_DS1307 0

// Header file includes
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#include "Font_Data.h"

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10


// Hardware SPI connection
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary output pins
// MD_Parola P = MD_Parola(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

#define SPEED_TIME  75
#define PAUSE_TIME  0

#define MAX_MESG  20

// Turn on debug statements to the serial output
#define DEBUG 0

// Global variables
char szTime[9];    // mm:ss\0
char szMesg[MAX_MESG+1] = "";

int lt [2] = {0};
int county = 0;

char *mon2str(uint8_t mon, char *psz, uint8_t len)


// Get a label from PROGMEM into a char array
{
  static const __FlashStringHelper* str[] =
  {
    F("Jan"), F("Feb"), F("Mar"), F("Apr"),
    F("May"), F("Jun"), F("Jul"), F("Aug"),
    F("Sep"), F("Oct"), F("Nov"), F("Dec")
  };

  strncpy_P(psz, (const char PROGMEM *)str[mon-1], len);
  psz[len] = '\0';

  return(psz);
}

char *dow2str(uint8_t code, char *psz, uint8_t len)
{
  static const __FlashStringHelper*	str[] =
  {
    F("Sunday"), F("Monday"), F("Tuesday"),
    F("Wednesday"), F("Thursday"), F("Friday"),
    F("Saturday")
  };

  strncpy_P(psz, (const char PROGMEM *)str[code-1], len);
  psz[len] = '\0';

  return(psz);
}

int getHr(){
  int count = 0;
  while(!digitalRead(6)){
    delay(0.001);
  }
  while (digitalRead(6)){
        if (digitalRead(7)){
            count++;
            while (digitalRead(7)){
              delay (0.001);
            }
        }

  }
  return (count);
}

int getMin(){
  int count2 = 0;
  while(!digitalRead(6)){
    delay(0.001);
  }
  while (digitalRead(6)){

      if (digitalRead(8)){
        count2++;
        while (digitalRead(8)){
          delay (0.001);
        }
      }
    }

    return (count2);

}

void printTime(char *psz, bool f = true, bool g = true, int inhr = 0, int inm = 0)
// Code for reading clock time
{
  int h = inhr;
  int m = inm;

  sprintf(psz, "%02d%s%02d", h, (f ? ":" : " "), m);


}


void setup(void)
{
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  

  P.begin(2);
  P.setInvert(false);
  P.setCharSpacing(1);

  P.setZone(0, 0, MAX_DEVICES-5);
  P.setZone(1, MAX_DEVICES-4, MAX_DEVICES-1);
  //P.setFont(1, numeric7Seg);
  P.setIntensity(0, 0);
  P.setIntensity(1, 0);
  P.setIntensity(2, 0);
  P.setIntensity(3, 0);

  P.displayZoneText(1, szTime, PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);
  P.displayZoneText(0, szMesg, PA_CENTER, SPEED_TIME, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);


  //getTime(szTime);
}

void loop(void)
{


  static uint32_t lastTime = 0; // millis() memory
  static uint8_t  display = 0;  // current display mode
  static bool flasher = false;  // seconds passing flasher
  static bool ge = false;
  int timer = 0;
  int min = 0;
  int hr = 0;
  int readcnt = 0;

  P.displayAnimate();

  if(digitalRead(6)){

    hr = getHr();
    if (hr != 0){
      min = getMin();
    }

    lastTime = millis();
    printTime(szTime, flasher, ge, hr, min);
    if (county == 20){
      flasher = !flasher;
      county = 0;
    }
    county++;
    readcnt = 0;
    ge = !ge;
    P.displayReset(1);
  }
  

}