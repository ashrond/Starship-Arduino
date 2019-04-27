//by learnelectronics
//Arduino Basics Handling Multiple States
//https://www.youtube.com/watch?v=ojflP6pvTMc

#define button  8    //pushbutton A5
#define redLED  A2    //red LED on A0
#define greenLED  6  //green led on D6
#define yellowLED 5  //yellow LED on D5

int State = 0;  //integer to hold current State
int old = 0;    //integer to hold last State
int buttonPoll = 0;  //integer to hold button State

void setup() {
pinMode (button, INPUT);  //BUTTON SET AS INPUT
pinMode (redLED, OUTPUT);    //leds set as outputs
pinMode (greenLED, OUTPUT);
pinMode (yellowLED, OUTPUT);
  
digitalWrite(redLED,LOW);    //set initial State as off
digitalWrite(greenLED,LOW);    //set internal State as off
digitalWrite(yellowLED,LOW);  //set initial State as off
  
}

void loop() {

  //debouncing routine to read button
  buttonPoll = digitalRead(button);             //poll the State of button
 if(buttonPoll == 0){                           //check if it has been pressed
  delay(50);                                    //wait 50ms
  buttonPoll = digitalRead(button);             //poll button agian
  if(buttonPoll == 1) {                         //if it is 0 considdered one press
    State = old + 1;                            //increase State by 1
  }}
  else{                                         //if button has not been pressed
  delay(100);                                   //wait100ms
  }
  switch (State) {                              //react to button press & State
    case 1:                                     //if State is 1
      digitalWrite(redLED,HIGH);                //red LED on
      digitalWrite(greenLED,LOW);               //green LED off
      digitalWrite(yellowLED,LOW);              //yellow led off
      old = State;                              //set old State as current State
      break;
    case 2:                                     //if State is 2
      digitalWrite(redLED,LOW);                 //red LED off
      digitalWrite(greenLED,HIGH);              //green LED ON
      digitalWrite(yellowLED,LOW);              //yellow led off
      old = State;                              //set old State as current State
      break;
    case 3:                                     //if State is 3
      digitalWrite(redLED,LOW);                 //red LED off
      digitalWrite(greenLED,LOW);               //green LED off
      digitalWrite(yellowLED,HIGH);             //yellow led ON
      old = State;                              //set old State as current State
      break;
    case 4:                                    //if State is not 1,2,3
      digitalWrite(redLED,LOW);                 //red LED off
      digitalWrite(greenLED,LOW);               //green LED off
      digitalWrite(yellowLED,LOW);              //yellow led off
      old = 0;                                  //reset to all off/State 0
      break;
  }
}
