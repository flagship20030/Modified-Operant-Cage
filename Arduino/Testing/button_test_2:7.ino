// only initiates button for the duration of time it is pressed! 
// 2/7/19 
// JHL 

const byte button_Pin = 2;
byte old_button_State = HIGH;  // assume button_ open because of pull-up resistor

unsigned long debounceTime = 10;  // 10 milliseconds
unsigned long button_PressTime;  // when the button_ last changed state

const int led_Pin = LED_BUILTIN;

void setup () {
  
  Serial.begin (9600);
  pinMode (button_Pin, INPUT);
  pinMode (led_Pin, OUTPUT); 
    // end of setup
}

void loop () {
  
  // see if button_is open or closed
  byte button_State = digitalRead (button_Pin);
  
  // has it changed since last time?
  if (button_State != old_button_State) {
    
    // debounce
    if (millis () - button_PressTime >= debounceTime) {
       
       button_PressTime = millis ();  // when we closed the button_
       
       old_button_State =  button_State;  // remember for next time 
       if (button_State == LOW) {
          digitalWrite(led_Pin, HIGH);
          Serial.println ("button_closed.");
          
          }  // end if button_State is LOW
       else {
          digitalWrite(led_Pin, LOW);
          Serial.println ("button_opened.");
          
          }  // end if button_State is HIGH
           
       }  // end if debounce time up
        
    }  // end of state change
     
  // other code here ...
   
 }  // end of loop
