// Starship Arduino
// Lighting control program for starship models
// GitHub Repository:  https://github.com/wilsonb/arduino/tree/master/libraries  
// LedFader.h> http://gammon.com.au/blink
// LedFlasher.h> http://gammon.com.au/blink

//Inclusions
#include <LedFader.h>
#include <LedFlasher.h>

//Pin Assignments
//NOTE: if modifying or altering, verrify that the connected pin is PWM if fading is desired or else fading will not work
//const byte ModePin = 0;
const byte StrobePin = 2;
//const byte RiggingPin = 13;   // (D9 PWM)
const byte NavPin = 4;
//const byte DeflectorPin = 6;   // (D6 PWM)
//const byte ImpulsePin = 5;   // (D3 PWM)
//const byte NacellePin = 9;   // (D5 PWM)

// Definitions
int brightness = 0;
int fadeAmount = 5;
int State = 0;  //integer to hold current State
int old = 0;    //integer to hold last State
int buttonPoll = 0;  //integer to hold button State
  
// Flashers pin,off-time,on-time,on?
  LedFlasher strobe (StrobePin, 2000, 100);
  LedFlasher navigation (NavPin, 2300, 600);
// set up some LEDs
          //                 pin  min max  millis
  LedFader Rigging1   (3, 0,  200, 2800);


 
void setup() 
  {

  strobe.begin ();
  navigation.begin ();
    Rigging1.begin ();
  }  // end of setup

void loop() 
  {
  // update lights
  strobe.update ();
  navigation.update ();
    Rigging1.update ();

  // do other useful stuff here ...
 
  }  // end of loop
