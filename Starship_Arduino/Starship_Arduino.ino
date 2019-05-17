// Version 36
// Starship Model Light control for Arduino
// Arduino Code for Uno
// Additional libraries needed from:  https://github.com/wilsonb/arduino/tree/master/libraries

#include <LedFader.h>
#include <LedFlasher.h>

//Pin Assignments
//NOTE: if modifying or altering, verrify that the connected pin is PWM if fading is desired or else fading will not work
const byte ModePin = 8;
const byte StrobesPin = 7;
const byte NavigationPin = 2;
const byte RunningLightPin = 9;   // (D9 PWM)
const byte DeflectorPin = 6;   // (D6 PWM)
const byte ImpulsePin = 5;   // (D3 PWM)
const byte NacellePin = 3;   // (D5 PWM)

// Definitions
//int brightness = 0;
//int fadeAmount = 5;
int State = 0;  //integer to hold current State
int old = 0;    //integer to hold last State
int buttonPoll = 0;  //integer to hold button State

// Faders pin,min,max,millis on?,stop?
// Faders                           pin         min  max  millis    on?    stop?
//__________________________STARTUP MODE________________________________ 
LedFader RunningLightFader1   (RunningLightPin, 0,  10, 2000, false,  true);
LedFader DeflectorFader1      (DeflectorPin,  0,  30, 8000, false, true);
LedFader ImpulseFader1      (ImpulsePin,  0,  30, 300,  false,  false);
LedFader NacelleFader1      (NacellePin,  0,  45, 30000,  false,  true);
//__________________________IMPULSE MODE________________________________
LedFader RunningLightFader2    (RunningLightPin, 0,  50, 1000, false,  true);
LedFader DeflectorFader2      (DeflectorPin,  0,  80, 8000, false, true);
LedFader ImpulseFader2     (ImpulsePin,  15,  45, 5, false,  false);
LedFader NacelleFader2     (NacellePin,  45,  100,  30000,  false,  true);    
//____________________________WARP MODE_________________________________
LedFader RunningLightFader3    (RunningLightPin, 0,  10, 1000, false,  true);
LedFader DeflectorFader3      (DeflectorPin,  0,  50, 8000, false, true);
LedFader ImpulseFader3     (ImpulsePin,  10,  25, 10000, false,  false);
LedFader NacelleFader3     (NacellePin,  100,  255,  30000,  false,  true);   
    
// Flashers pin,off-time,on-time,on?
LedFlasher Strobes  (StrobesPin,  2000, 100,  true);
LedFlasher Navigation (NavigationPin, 2300, 600,  true);


const int buttonPin = 8; // One button connection to Pin 2, the other to GND

const int NUMBER_OF_MODES = 4;

int MODE = 0, buttonState = 0, lastButtonState = 0;

void setup() {

pinMode(buttonPin, INPUT_PULLUP);
  pinMode (RunningLightPin, OUTPUT);
  pinMode (DeflectorPin, OUTPUT);
  pinMode (ImpulsePin, OUTPUT);
  pinMode (NacellePin, OUTPUT);

  // set up faders, flashers
 //STARTUP
  ImpulseFader1.begin ();     
  DeflectorFader1.begin ();
  NacelleFader1.begin ();
  Navigation.begin ();
  Strobes.begin ();
  RunningLightFader1.begin ();
 //IMPULSE MODE 
    ImpulseFader2.begin ();     
    DeflectorFader2.begin ();
    NacelleFader2.begin ();
    RunningLightFader2.begin ();  
 //WARP MODE  
      ImpulseFader3.begin ();     
      DeflectorFader3.begin ();
      NacelleFader3.begin ();
      RunningLightFader3.begin ();      
}

void loop() {
 //STARTUP
  ImpulseFader1.update ();      
  DeflectorFader1.update ();
  NacelleFader1.update ();
  Navigation.update ();
  Strobes.update ();
  RunningLightFader1.update ();
  //IMPULSE MODE 
    ImpulseFader2.update ();     
    DeflectorFader2.update ();
    NacelleFader2.update ();
    RunningLightFader2.update ();  
   //WARP MODE  
      ImpulseFader3.update ();     
      DeflectorFader3.update ();
      NacelleFader3.update ();
      RunningLightFader3.update ();    
      
buttonState = digitalRead(buttonPin);

if (buttonState != lastButtonState) {

if (buttonState == LOW) { // Inverted due to using INPUT_PULLUP

MODE++;

if (MODE==NUMBER_OF_MODES) { MODE = 0; }

// do anything else you want here, eg resetting any variables or other counters.

}

}

lastButtonState = buttonState;

switch (MODE){

case 1:
      RunningLightFader1.on();
      delay(130);
        RunningLightFader1.update ();
        delay(130);
      DeflectorFader1.on();
      delay(130);
        DeflectorFader1.update ();
        delay(130);
      ImpulseFader1.on();
      delay(130);
        ImpulseFader1.update ();
        delay(130);
break;

case 2:
    RunningLightFader1.off();
          delay(130);
      RunningLightFader1.update ();
            delay(130);
        RunningLightFader2.on();
              delay(130);
    DeflectorFader1.off();
          delay(130);
      DeflectorFader1.update ();
            delay(130);
        DeflectorFader2.on();
              delay(130);
    ImpulseFader1.off();
          delay(130);
      ImpulseFader1.update ();
            delay(130);
        ImpulseFader2.on();
              delay(130);
    NacelleFader1.on();
          delay(130);
break;

case 3:
      RunningLightFader2.on();
            delay(130);
    DeflectorFader2.off();
          delay(130);
    DeflectorFader2.update ();
          delay(130);
      DeflectorFader3.on();
            delay(130);
    ImpulseFader2.off();
          delay(130);
    ImpulseFader2.update ();
          delay(130);
      ImpulseFader3.on();
            delay(130);
    NacelleFader2.off();
          delay(130);
    NacelleFader2.update ();
          delay(130);
      NacelleFader3.on();
            delay(130);
break;

case 4:
      RunningLightFader1.off();
      RunningLightFader1.update ();
        RunningLightFader2.off();
        RunningLightFader2.update ();
          RunningLightFader3.off();
          RunningLightFader3.update ();
       // delay(3000);
      DeflectorFader1.off();
      DeflectorFader1.update ();
        DeflectorFader2.off();
        DeflectorFader2.update ();
          DeflectorFader3.off();
          DeflectorFader3.update ();
      //  delay(3000);
    ImpulseFader1.off();
    ImpulseFader1.update ();
      ImpulseFader2.off();
      ImpulseFader2.update ();
        ImpulseFader3.off();
        ImpulseFader3.update ();
      //  delay(3000);
    NacelleFader1.off();
    NacelleFader1.update ();
      NacelleFader2.off();
      NacelleFader2.update ();
        NacelleFader3.off();
        NacelleFader3.update ();
break;
default:

//do something

break;

}

// update faders, flashers

}
