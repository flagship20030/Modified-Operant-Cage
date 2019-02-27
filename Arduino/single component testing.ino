// 5 -CSRT Test Program
// JHL, 11/7/18

// Program Starts after 2 seconds of delay

// Components: 1 LED / 1 solenoid / 1 IR

// 1) LED turns on for 5 seconds
// 2) LED turns off, simultaenously turning on solenoid for 50ms
// 3) Solenoid off triggers start of ITI
// 4) After ITI expires, LED turns on again
// 5) loop back to 1)

#define NUM_TIMES 5
int wait_interval[NUM_TIMES] = {7000, 3000, 5000, 5000, 5000};  // change here for ITI
// ITI starts when solenoid is turned off

byte port_IR = 5;
byte port_solenoid = 6;
byte port_led = 10;

// Durations

int led_on_duration = 5000;
int solenoid_on_duration = 50;  // 80 ms

// if conditional states:

boolean led_switched_off = false;
boolean solenoid_active = false;

boolean led_state;
boolean solenoid_state;
boolean IR_previous_state;

// unsigned long led_off_time = 0; // out here as a global variable to be accessed by solenoid_operate()

// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

void setup(){

  pinMode(port_IR, INPUT);
  pinMode(port_led, OUTPUT);
  pinMode(port_solenoid, OUTPUT);
  Serial.begin(9600);

  delay(2000);
  Serial.println("Start Test Program");

}

// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * *

void loop() {

  led_operate();
  record_IR();
  solenoid_operate();

}

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * *

void led_operate() {

  static unsigned long led_on_time = 0;
  static unsigned long led_off_time = 0;

  // operate led only after Wait Time expired

  if (solenoid_active == false) {
    if (led_state == LOW){
      led_state = HIGH;
      led_on_time = millis();
      digitalWrite(port_led, led_state);

      Serial.print("led_on_time: ");
      Serial.println(led_on_time);
    }

    // turn led off when time expires (after led_on_duration) and record time ;
    // toggle led_switched_off to true

    if (millis() - led_on_time > led_on_duration) {
      led_state = LOW;
      led_switched_off = true;
      led_off_time = millis();
      digitalWrite(port_led, led_state);

      Serial.print("led_off_time: ");
      Serial.println(led_off_time);

    }
  }
}

void solenoid_operate() {

  static unsigned long solenoid_on_time = 0;
  static unsigned long solenoid_off_time = 0;
  static int time_index = 0;

  // check if LED is turned off! (solenoid ON depends on led OFF)

  if (led_state == LOW) {

    // check if the LED was turned off after the on_duration (cue for solenoid to turn on)
     if (led_switched_off) {
       led_switched_off = false;
       solenoid_active = true;
       solenoid_state = HIGH;
       solenoid_on_time = millis();
       digitalWrite(port_solenoid, solenoid_state);

       Serial.print("solenoid_on: ");
       Serial.println(solenoid_on_time);
      }
        // turn off solenoid only when it was on! (2nd conditional can evaluate to true when solenoid is also off)

      if ((solenoid_state == HIGH) && (millis() - solenoid_on_time > solenoid_on_duration)) {
        solenoid_state = LOW;
        solenoid_off_time = millis();
        digitalWrite(port_solenoid, solenoid_state);

        Serial.print("solenoid_off: ");
        Serial.println(solenoid_off_time);

      }

       // WAITING (Idle) period
      if ((solenoid_state == LOW) && ((millis() - solenoid_off_time) >= wait_interval[time_index])) {

      // the solenoid off period has expired.
      // update solenoid_operate_Active so that led_operate() can turn the LED on again
      // and update the array index in preparation for the next solenoid activation phase

      solenoid_active = false;
      time_index += 1;

      if (time_index >= NUM_TIMES) {
        time_index = 0;
        }
      }
   }
}

void record_IR() {

  static unsigned long Poke_On_Time = 0;
  static unsigned long Poke_Off_Time = 0;

  byte read_gate = digitalRead(port_IR);

  if (read_gate != IR_previous_state) {
    if (read_gate == LOW) {
      Poke_On_Time = millis();
      Serial.print("PokeOn: ");
      Serial.println(Poke_On_Time);
    }
    if (read_gate == HIGH){
      Poke_Off_Time = millis();
      Serial.print("PokeOff: ");
      Serial.println(Poke_Off_Time);
    }
  }

  IR_previous_state = read_gate;

}
