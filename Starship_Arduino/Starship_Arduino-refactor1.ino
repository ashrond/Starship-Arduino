// Starship Arduino
// Model Light control Program
// Arduino Code for Uno
// Version: Alpha
// Git Repo: https://github.com/ashrond/Starship-Arduino/tree/master/Starship_Arduino
// Considder adding in chasing led effect from : https://www.youtube.com/watch?v=6AF2it9XEIQ
// Additional libraries obtained from:  https://github.com/wilsonb/arduino/tree/master/libraries
#include <LedFader.h>
#include <LedFlasher.h>

//Pin Assignments
//NOTE: if modifying or altering, verrify that the connected pin is PWM if fading is desired or else fading will not work
const byte ModePin = A5;
const byte StrobesPin = 7;
const byte NavigationPin = 2;
const byte RunningLightPin = 9;   // (PWM)
const byte DeflectorPin = 6;      // (PWM)
const byte ImpulsePin = 5;        // (PWM)
const byte NacellePin = 3;        // (PWM)
const byte TestPin = 13;          // (PWM)

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
LedFader DeflectorFader1      (DeflectorPin,  0,  10, 8000, true, true);
LedFader ImpulseFader1      (ImpulsePin,  0,  20, 300,  false,  false);
LedFader NacelleFader1      (NacellePin,  0,  45, 30000,  true,  true);
//__________________________IMPULSE MODE________________________________
LedFader RunningLightFader2    (RunningLightPin, 0,  80, 1000, true,  true);
LedFader DeflectorFader2      (DeflectorPin,  0,  150, 8000, true, true);
LedFader ImpulseFader2     (ImpulsePin,  15,  150, 15, false,  false);
LedFader NacelleFader2     (NacellePin,  45,  100,  30000,  true,  true);
//____________________________WARP MODE_________________________________
LedFader RunningLightFader3    (RunningLightPin, 0,  30, 1000, true,  true);
LedFader DeflectorFader3      (DeflectorPin,  0,  50, 8000, true, true);
LedFader ImpulseFader3     (ImpulsePin,  10,  25, 10000, false,  false);
LedFader NacelleFader3     (NacellePin,  100,  255,  30000,  true,  true);

// Flashers pin,off-time,on-time,on?
LedFlasher Strobes  (StrobesPin,  2000, 100,  true);
LedFlasher Navigation (NavigationPin, 2300, 600,  true);

// enumerate states
enum eLightStates { eOff = 0, eFirst, eSecond, eThird, eFourth, eFifth, eMaxState };

void setup() {
MODE = 0; 
buttonState = 0; 
lastButtonState = 0;
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
  
  //Setup Case - any changes due to button state should modify mode first
  // if ( eOff < MODE && MODE < eMaxState ) {
 if (buttonState != lastButtonState) {
    if (MODE == eMaxState) {
      MODE = eFirst;
    } else {	
		MODE = MODE + 1;
	}
	changeMode(MODE);
	lastButtonState = buttonState;
  } 
	//else {  // same state as before
    //lastButtonState = buttonState;
    //return;
  //}

  // Update faders, flashers
  Navigation.update();
  Strobes.update();
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

} // end of loop

void changeMode(MODE) {
	
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
      RunningLightFader2.on();
      RunningLightFader1.off();
      delay(5);
      DeflectorFader2.on();
      DeflectorFader1.off();
      delay(5);
      ImpulseFader2.on();
      ImpulseFader1.off();
      delay(5);
      NacelleFader2.on();
      NacelleFader1.off();
      break;

    case eFourth:
      RunningLightFader3.on();
      RunningLightFader2.off();
      delay(5);
      DeflectorFader3.on();
      DeflectorFader2.off();
      delay(5);
      ImpulseFader3.on();
      ImpulseFader2.off();
      delay(5);
      NacelleFader3.on();
      NacelleFader2.off();
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
      //  }
  }
}