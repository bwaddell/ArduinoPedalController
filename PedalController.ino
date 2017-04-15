//#include <Keyboard.h>

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 20;

//up arrow - 0xDA
const int gasKey = 0xDA;

//down arrow - 0xD9
const int brakeKey = 0xD9;

//pro micro pins
const int gasInputPin = 9;
const int brakeInputPin = 10;
const int powerLEDPin = 2;
const int gasLEDPin = 7;
const int brakeLEDPin = 14;

//state of buttons
int gasStateCurrent = 0;
int gasStateLast = 0;
int brakeStateCurrent = 0;
int brakeStateLast = 0;

void setup() {
    Serial.begin(9600);
  
    pinMode(gasInputPin, INPUT_PULLUP);
    pinMode(brakeInputPin, INPUT_PULLUP);
    pinMode(powerLEDPin, OUTPUT);
    pinMode(gasLEDPin, OUTPUT);
    pinMode(brakeLEDPin, OUTPUT);
    digitalWrite(powerLEDPin, HIGH);
    digitalWrite(gasLEDPin, LOW);
    digitalWrite(brakeLEDPin, LOW);

    //begin emulating keyboard
    Keyboard.begin();
}

//loop continuously
void loop(){

    //get state of gas button
    gasStateCurrent = digitalRead(gasInputPin);

    //if state has changed, perform key press or release
    if (gasStateCurrent != gasStateLast){
      
      //millis() is time in miliseconds since program started
      lastDebounceTime = millis();

      //Debounce to ignore noise
      if ((millis() - lastDebounceTime) > debounceDelay){
        if (gasStateCurrent == LOW) {
          Keyboard.press(gasKey);
          digitalWrite(gasLEDPin, HIGH);
        }
        else{
          Keyboard.release(gasKey);
          digitalWrite(gasLEDPin, LOW);
        }
        gasStateLast = gasStateCurrent;
      }
    }

    //get state of brake button 
    brakeStateCurrent = digitalRead(brakeInputPin); 

    //if state changed, perform key press or release
    if (brakeStateCurrent != brakeStateLast){
      
      lastDebounceTime = millis();
    
      if ((millis() - lastDebounceTime) > debounceDelay){
        if (brakeStateCurrent == LOW) {
          Keyboard.press(brakeKey);
          digitalWrite(brakeLEDPin, HIGH);
        }
        else{
          Keyboard.release(brakeKey);
          digitalWrite(brakeLEDPin, LOW);
        }
        brakeStateLast = brakeStateCurrent;
      }
    }
}

