/* Final Testing in Operant Room (3 solenoids / 3 IRs / 3 LEDs + 1 Button)
* 2/27/19
* JHL
*
* Head Pokes trigger solenoid reward in each port respectively (for a given amount of time ex: 200ms)
* for ex) if port 8 detects head poke, delivers reward for 200ms and records it
*
* remove the LED blinking part
* retain the button functionality so that we can test solenoids working or not
*
* Future To-Dos: Refactor Code into functions with emphasis on modularity! 
*
*/


// coding schemes:
// On : 100
// Off: 001
// "component pin" + "on"
// i.e) IR at port 8 was poked in --> 8100  // poked out --> 8001


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
byte ledState_6 = LOW;           // ledState used to set the LED
byte ledState_7 = LOW;
byte ledState_9 = LOW;

//**Solenoid Variables States:
byte sol_State_3 = LOW;
byte sol_State_4 = LOW;
byte sol_State_5 = LOW;

// IR States
boolean IR_previous_state_8;
boolean IR_previous_state_10;
boolean IR_previous_state_11;

// boolean to see if IR was broken:
boolean poke_in_8 = false;
boolean poke_in_10 = false;
boolean poke_in_11 = false;

// constants won't change:
const long sol_interval = 20;           // LED + solenoid interval

// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

void setup() {

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

// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * *

void loop() {

  // blink_led();
  record_IR();
  solenoid_on();
  button_push();

}

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * *

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
    // low means IR has been broken
    if (read_gate_8 == LOW) {
      Poke_On_Time_8 = millis();
      Serial.print("8100: ");
      // Serial.print("Poke On at IR_8: ");
      Serial.println(Poke_On_Time_8);
      poke_in_8 = true;
    }
    if (read_gate_8 == HIGH){
      Poke_Off_Time_8 = millis();
      Serial.print("8001: ");
      // Serial.print("Poke Off at IR_8: ");
      Serial.println(Poke_Off_Time_8);
    }
  }

  IR_previous_state_8 = read_gate_8;

  if (read_gate_10 != IR_previous_state_10) {
    if (read_gate_10 == LOW) {
      Poke_On_Time_10 = millis();
      Serial.print("10100: ");
      // Serial.print("Poke On at IR_10: ");
      Serial.println(Poke_On_Time_10);
      poke_in_10 = true;
    }
    if (read_gate_10 == HIGH){
      Poke_Off_Time_10 = millis();
      Serial.print("10001: ");
      // Serial.print("Poke Off at IR_10: ");
      Serial.println(Poke_Off_Time_10);
    }
  }

  IR_previous_state_10 = read_gate_10;


if (read_gate_11 != IR_previous_state_11) {
  if (read_gate_11 == LOW) {
    Poke_On_Time_11 = millis();
    Serial.print("11100: ");
    // Serial.print("Poke On at IR_11: ");
    Serial.println(Poke_On_Time_11);
    poke_in_11 = true;
  }
  if (read_gate_11 == HIGH){
    Poke_Off_Time_11 = millis();
    Serial.print("11001: ");
    // Serial.print("Poke Off at IR_11: ");
    Serial.println(Poke_Off_Time_11);
  }
}

IR_previous_state_11 = read_gate_11;

}

void solenoid_on() {

   unsigned long currentMillis = millis();

   static unsigned long sol_on_3 = 0;
   static unsigned long sol_off_3 = 0;

   static unsigned long sol_on_4 = 0;
   static unsigned long sol_off_4 = 0;

   static unsigned long sol_on_5 = 0;
   static unsigned long sol_off_5 = 0;

   if (poke_in_8) {
       poke_in_8 = false;
       sol_State_3 = HIGH;
       digitalWrite(port_solenoid_3, sol_State_3);
       sol_on_3 = millis();
       // Serial.print("3100: ");
       Serial.print("solenoid On at 3: ");
       Serial.println(sol_on_3);
       // theoretically, currentMillis output and sol_on_3 output time should be the same!
      }

       // can't come in to this loop in the first place bc its nested in the if() above!!
    if (sol_State_3 == HIGH && currentMillis - sol_on_3 >= sol_interval) {  //poke_in_8 = false &&
        sol_State_3 = LOW;
        digitalWrite(port_solenoid_3, sol_State_3);
        sol_off_3 = millis();
        // Serial.print("3001: ");
        Serial.print("solenoid Off at 3: ");
        Serial.println(sol_off_3);
        // theoretically currentMillis should be sol_off_3 + sol_interval value
    }

   if (poke_in_10) {
       poke_in_10 = false;
       sol_State_4 = HIGH;
       digitalWrite(port_solenoid_4, sol_State_4);
       sol_on_4 = millis();
       // Serial.print("4100: ");
       Serial.print("solenoid On at 4: ");
       Serial.println(sol_on_4);
       // theoretically, currentMillis output and sol_on_4 output time should be the same!
       }

       // breaking out of above loop is crucial!!!

       // can't come in to this loop in the first place bc its nested in the if() above!!
    if (sol_State_4 == HIGH && currentMillis - sol_on_4 >= sol_interval) {  //poke_in_8 = false &&
        sol_State_4 = LOW;
        digitalWrite(port_solenoid_4, sol_State_4);
        sol_off_4 = millis();
        // Serial.print("4001: ");
        Serial.print("solenoid Off at 4: ");
        Serial.println(sol_off_4);
        // theoretically currentMillis should be sol_off_3 + sol_interval value
       }

    if (poke_in_11) {
       poke_in_11 = false;
       sol_State_5 = HIGH;
       digitalWrite(port_solenoid_5, sol_State_5);
       sol_on_5 = millis();
       // Serial.print("5100: ");
       Serial.print("solenoid On at 5: ");
       Serial.println(sol_on_5);
       // can't come in to this loop in the first place bc its nested in the if() above!!
    }

    if (sol_State_5 == HIGH && currentMillis - sol_on_5 >= sol_interval) {  //poke_in_8 = false &&
        sol_State_5 = LOW;
        digitalWrite(port_solenoid_5, sol_State_5);
        sol_off_5 = millis();
        // Serial.print("5001: ");
        Serial.print("solenoid Off at 5: ");
        Serial.println(sol_off_5);
        // theoretically currentMillis should be sol_off_3 + sol_interval value
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
