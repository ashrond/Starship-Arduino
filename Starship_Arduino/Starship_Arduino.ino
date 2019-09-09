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
const byte DeflectorPin = 6;      // (D6 PWM)
const byte ImpulsePin = 5;        // (D3 PWM)
const byte NacellePin = 3;        // (D5 PWM)
const byte TestPin = 13;        // (D5 PWM)

// Definitions
//int brightness = 0;
//int fadeAmount = 5;
int State = 0;  //integer to hold current State
int old = 0;    //integer to hold last State
int buttonPoll = 0;  //integer to hold button State
int MODE = 0, buttonState = 0, lastButtonState = 0;
const int buttonPin = ModePin; // One button connection to Pin 8, the other to GND


// Faders pin,min,max,millis on?,stop?
// Faders                           pin       min | max | millis | on? | stop?
//__________________________STARTUP MODE________________________________
LedFader RunningLightFader1   (RunningLightPin, 0,  10, 2000, true,  true);
LedFader DeflectorFader1      (DeflectorPin,  0,  30, 8000, true, true);
LedFader ImpulseFader1      (ImpulsePin,  0,  30, 300,  false,  false);
LedFader NacelleFader1      (NacellePin,  0,  45, 30000,  true,  true);
//__________________________IMPULSE MODE________________________________
LedFader RunningLightFader2    (RunningLightPin, 0,  50, 1000, true,  true);
LedFader DeflectorFader2      (DeflectorPin,  0,  80, 8000, true, true);
LedFader ImpulseFader2     (ImpulsePin,  15,  45, 5, false,  false);
LedFader NacelleFader2     (NacellePin,  45,  100,  30000,  true,  true);
//____________________________WARP MODE_________________________________
LedFader RunningLightFader3    (RunningLightPin, 0,  10, 1000, true,  true);
LedFader DeflectorFader3      (DeflectorPin,  0,  50, 8000, true, true);
LedFader ImpulseFader3     (ImpulsePin,  10,  25, 10000, false,  false);
LedFader NacelleFader3     (NacellePin,  100,  255,  30000,  true,  true);

// Flashers pin,off-time,on-time,on?
LedFlasher Strobes  (StrobesPin,  2000, 100,  true);
LedFlasher Navigation (NavigationPin, 2300, 600,  true);
LedFlasher Test (TestPin, 2300, 600,  true);

// enumerate states
enum eLightStates { eOff = 0, eFirst, eSecond, eThird, eFourth, eFifth, eMaxState };

void setup() {

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode (RunningLightPin, OUTPUT);
  pinMode (DeflectorPin, OUTPUT);
  pinMode (ImpulsePin, OUTPUT);
  pinMode (NacellePin, OUTPUT);

  // Start up faders, flashers
  Navigation.begin ();
  Strobes.begin ();
  RunningLightFader1.begin();
  RunningLightFader2.begin();
  RunningLightFader3.begin();
  DeflectorFader1.begin();
  DeflectorFader2.begin();
  DeflectorFader3.begin();
  ImpulseFader1.begin();
  ImpulseFader2.begin();
  ImpulseFader3.begin();
  NacelleFader1.begin();
  NacelleFader2.begin();
  NacelleFader3.begin();
}

void loop() {
  // Button read update
  buttonState = digitalRead(buttonPin);

  // Update faders, flashers
  Navigation.update ();
  Strobes.update ();
  RunningLightFader1.update();
  RunningLightFader2.update();
  RunningLightFader3.update();
  DeflectorFader1.update();
  DeflectorFader2.update();
  DeflectorFader3.update();
  ImpulseFader1.update();
  ImpulseFader2.update();
  ImpulseFader3.update();
  NacelleFader1.update();
  NacelleFader2.update();
  NacelleFader3.update();

  if (buttonState != lastButtonState) {
    if (MODE == eMaxState) {
      MODE = eFirst;
    }
  } else {  // same state as before
    lastButtonState = buttonState;
    return;
  }
  //Setup Case
  // if ( eOff < MODE && MODE < eMaxState ) {
  switch (MODE) {
    case eFirst:
      digitalWrite(TestPin,LOW); 
      delay(10);
      break;

    case eSecond:
      RunningLightFader1.on();
      delay(130);
      DeflectorFader1.on();
      delay(130);
      ImpulseFader1.on();
      delay(130);
      break;

    case eThird:
      RunningLightFader1.off();
      RunningLightFader2.on();
      delay(130);
      DeflectorFader1.off();
      DeflectorFader2.on();
      delay(130);
      ImpulseFader1.off();
      ImpulseFader2.on();
      delay(130);
      NacelleFader1.off();
      NacelleFader2.on();
      break;

    case eFourth:
      RunningLightFader2.off();
      RunningLightFader3.on();
      delay(130);
      DeflectorFader2.off();
      DeflectorFader3.on();
      delay(130);
      ImpulseFader2.off();
      ImpulseFader3.on();
      delay(130);
      NacelleFader2.off();
      NacelleFader3.on();
      break;

    case eFifth:
          digitalWrite(TestPin,HIGH); 
      RunningLightFader1.off();
      RunningLightFader2.off();
      RunningLightFader3.off();
      DeflectorFader1.off();
      DeflectorFader2.off();
      DeflectorFader3.off();
      ImpulseFader1.off();
      ImpulseFader2.off();
      ImpulseFader3.off();
      NacelleFader1.off();
      NacelleFader2.off();
      NacelleFader3.off();
      break;

    default:
      //  this should never happen however a good safety just to turn on the lights for safety
      //  hardware, memory corruption could happen.  Let's make it same as case high beam
      break;
      //  }
  }
  lastButtonState = buttonState;
  MODE = MODE + 1;

} // end of loop
