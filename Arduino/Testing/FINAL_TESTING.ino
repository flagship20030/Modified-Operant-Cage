// Final Testing (3 solenoids / 3 IRs / 3 LEDs + 1 Button)
// 2/6/19
// JHL 

// Solenoids and LED turn on for x seconds in alternation! 
// if you want to change the rate of change, 
// edit 'interval' AND 'previous_sol_millis' and set them equal

// 2/14/19 
// Button Functionality Added
// Dispenses Solenoid Output for the duration of button press

byte button_Pin = 2;
byte old_button_State = HIGH;
 
unsigned long debounceTime = 10;  // 10 milliseconds
unsigned long button_PressTime;  // when the button_ last changed state


// Solenoids 
byte port_solenoid_3 = 3; 
byte port_solenoid_4 = 4; 
byte port_solenoid_5 = 5; 

// LED constants
byte ledPin_6 =  6;// the number of the LED pin
byte ledPin_7 =  7;// the number of the LED pin
byte ledPin_9 =  9;// the number of the LED pin

// IRs
byte port_IR_8 = 8;
byte port_IR_10 = 10;
byte port_IR_11 = 11;

// LED variable states:
int ledState_6 = LOW;           // ledState used to set the LED 
int ledState_7 = LOW;
int ledState_9 = LOW;

//**Solenoid Variables States:
int sol_State_3 = LOW;             
int sol_State_4 = LOW;
int sol_State_5 = LOW;

// IR States
boolean IR_previous_state_8;
boolean IR_previous_state_10;
boolean IR_previous_state_11;

unsigned long previous_led_millis = 0;        // will store last time LED was updated
unsigned long previous_sol_millis = 2000;     // needed for solenoid interval time (blink in alternation with LED) 

// constants won't change:
const long interval = 2000;           // LED + solenoid interval 


// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

void setup() {
  // set the digital pin as output:

  pinMode (button_Pin, INPUT);

  // looks like the test program worked without solenoids set as OUTPUT 
  // but will include them just to make sure (and to see if code breaks)
  pinMode(port_solenoid_3, OUTPUT);
  pinMode(port_solenoid_4, OUTPUT);
  pinMode(port_solenoid_5, OUTPUT);
  
  pinMode(ledPin_6, OUTPUT);
  pinMode(ledPin_7, OUTPUT);
  pinMode(ledPin_9, OUTPUT);

  pinMode(port_IR_8, INPUT);
  pinMode(port_IR_10, INPUT);
  pinMode(port_IR_11, INPUT);

  Serial.begin(9600);

  // delay(2000);
  Serial.println("Start Test Program");

}

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * *

void loop() {
  
  blink_led();
  record_IR();
  // solenoid_on();
  button_push();
  
}


void blink_led() {
    // check to see if it's time to blink the LED; that is, if the difference
    // between the current time and last time you blinked the LED is bigger than
    // the interval at which you want to blink the LED.
    unsigned long currentMillis = millis();

    if (currentMillis - previous_led_millis >= interval) {
      // save the last time you blinked the LED
      previous_led_millis = currentMillis;

      
      // if the LED is off turn it on and vice-versa:
      if (ledState_6 == LOW) {
        ledState_6 = HIGH;
      } else {
        ledState_6 = LOW;
      }

      if (ledState_7 == LOW) {
        ledState_7 = HIGH;
      } else {
        ledState_7 = LOW;
      }

      if (ledState_9 == LOW) {
        ledState_9 = HIGH;
      } else {
        ledState_9 = LOW;
      }

          // set the LED with the ledState of the variable:
      digitalWrite(ledPin_6, ledState_6);
      digitalWrite(ledPin_7, ledState_7);
      digitalWrite(ledPin_9, ledState_9);
    }
   }

void record_IR() {

  static unsigned long Poke_On_Time_8 = 0;
  static unsigned long Poke_Off_Time_8 = 0;

  static unsigned long Poke_On_Time_10 = 0;
  static unsigned long Poke_Off_Time_10 = 0;

  static unsigned long Poke_On_Time_11 = 0;
  static unsigned long Poke_Off_Time_11 = 0;

  byte read_gate_8 = digitalRead(port_IR_8);
  byte read_gate_10 = digitalRead(port_IR_10);
  byte read_gate_11 = digitalRead(port_IR_11);

  if (read_gate_8 != IR_previous_state_8) {
    if (read_gate_8 == LOW) {
      Poke_On_Time_8 = millis();
      Serial.print("8000: ");
      Serial.println(Poke_On_Time_8);
    }
    if (read_gate_8 == HIGH){
      Poke_Off_Time_8 = millis();
      Serial.print("8001: ");
      Serial.println(Poke_Off_Time_8);
    }
  }

  IR_previous_state_8 = read_gate_8;

  if (read_gate_10 != IR_previous_state_10) {
    if (read_gate_10 == LOW) {
      Poke_On_Time_10 = millis();
      Serial.print("10000: ");
      Serial.println(Poke_On_Time_10);
    }
    if (read_gate_10 == HIGH){
      Poke_Off_Time_10 = millis();
      Serial.print("10001: ");
      Serial.println(Poke_Off_Time_10);
    }
  }

  IR_previous_state_10 = read_gate_10;


if (read_gate_11 != IR_previous_state_11) {
  if (read_gate_11 == LOW) {
    Poke_On_Time_11 = millis();
    Serial.print("11000: ");
    Serial.println(Poke_On_Time_11);
  }
  if (read_gate_11 == HIGH){
    Poke_Off_Time_11 = millis();
    Serial.print("11001: ");
    Serial.println(Poke_Off_Time_11);
  }
}

IR_previous_state_11 = read_gate_11;

}

void solenoid_on() {

   unsigned long currentMillis = millis();

   if (currentMillis - previous_sol_millis >= interval) {
    
     previous_sol_millis = currentMillis;
     
     Serial.print("3. first point when time enters this sol loop: ");
     Serial.println(currentMillis);
     
     // if the solenoid is off turn it on and vice-versa:
     if (sol_State_3 == LOW) {
       sol_State_3 = HIGH;
       Serial.print("4. sol on: ");
       Serial.println(currentMillis);
     } else {
      sol_State_3 = LOW;
       Serial.print("5. sol off: ");
       Serial.println(currentMillis);
     }

     if (sol_State_4 == LOW) {
      sol_State_4 = HIGH;
     } else {
       sol_State_4 = LOW;
     }

     if (sol_State_5 == LOW) {
       sol_State_5 = HIGH;
     } else {
       sol_State_5 = LOW;
     }

         
     digitalWrite(port_solenoid_3, sol_State_3);
     digitalWrite(port_solenoid_4, sol_State_4);
     digitalWrite(port_solenoid_5, sol_State_5);
   }
  }


void button_push() {    
  
// see if button_is open or closed
  byte button_State = digitalRead (button_Pin);
  
  // has it changed since last time?
  if (button_State != old_button_State) {
    
    // debounce
    if (millis () - button_PressTime >= debounceTime) {
       
       button_PressTime = millis ();  // time when we close the button
       
       old_button_State =  button_State;  // remember for next time 
       
       if (button_State == LOW) {
 
          Serial.println ("button_closed.");
          digitalWrite(port_solenoid_3, HIGH);
          digitalWrite(port_solenoid_4, HIGH);
          digitalWrite(port_solenoid_5, HIGH);
          
          }  // end if button_State is LOW
       else {
   
          Serial.println ("button_opened.");
          digitalWrite(port_solenoid_3, LOW);
          digitalWrite(port_solenoid_4, LOW);
          digitalWrite(port_solenoid_5, LOW);
          
          }  // end if button_State is HIGH
           
       }  // end if debounce time up
        
    }  // end of state change
     
}


