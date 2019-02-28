/*
* Work in Progress (2/27/19)
*
* Goal: Implement KFY (or just a random shuffle algorithm to sort the ITIs)
* (see ! flag below)
*
*/

    // change here for ITI
    #define NUM_TIMES 5
    int wait_interval[NUM_TIMES] = {3000, 5000, 7000, 9000, 11000};
    // ITI resets after run_Type = 1 Or run_Type = 2

    #define POKE_TIMES 3

    // Ports
    byte port_IR = 5;
    byte port_solenoid = 6;
    byte port_led = 9;

    // count function
    int poke_count = 0;
    int during_led_nose_poke = 0;

    // Durations
    int led_on_duration = 5000;
    int solenoid_on_duration = 1000;  // 1000 ms

    // IF conditional states:
    boolean solenoid_active = false;
    boolean poke_count_reached = false;
    boolean reset_ITI = false;

    // Output States
    boolean led_state;
    boolean solenoid_state;
    boolean IR_previous_state;

    // run_Type = 1 is reward
    // run_Type = 2 is no reward (punishment)
    int run_Type = 0;

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

      // solenoid_active becomes false only after ITI time expires

      if (solenoid_active == false) {
        if (led_state == LOW){

          led_state = HIGH;
          led_on_time = millis();

          // nose_poke count when LED is on:

          during_led_nose_poke = 0;
          digitalWrite(port_led, led_state);

          Serial.print("led_on_time: ");
          Serial.println(led_on_time);
        }

        // If mouse pokes 3 times DURING when LED is turned on,
        // stores the status in poke_count_reached boolean

        if (led_state == HIGH && during_led_nose_poke == 3){
            poke_count_reached = true;
        }

        // LED turns off after on_duration, regardless of nosepokes
        // * LED doesn't immediately react after nose poke count has been reached *

        if (millis() - led_on_time > led_on_duration) {

            led_state = LOW;
            led_off_time = millis();
            digitalWrite(port_led, led_state);

            Serial.print("led_off_time: ");
            Serial.println(led_off_time);

            if (poke_count_reached) {
                run_Type = 1;
                delay(20);
                // reward (solenoid_output)
            }
            else {
                run_Type = 2;
                delay(20);
                // no reward (no solenoid)
            }
            Serial.print("Run Type is: ");
            Serial.println(run_Type);
        }
    }
}

    void solenoid_operate() {

        static unsigned long solenoid_on_time = 0;
        static unsigned long solenoid_off_time = 0;
        static unsigned long ITI_start_time = 0;
        static int time_index = 0;

        // solenoid only operates once led is turned off
        if (led_state == LOW) {

            if (run_Type == 1) {
                run_Type = 0;
                poke_count_reached = false;
                solenoid_active = true;
                solenoid_state = HIGH;
                solenoid_on_time = millis();
                digitalWrite(port_solenoid, solenoid_state);

                Serial.print("solenoid_on: ");
                Serial.println(solenoid_on_time);
            }

            // solenoid turns off after duration elapses:
            // must be in an IF loop (NOT ELIF) b/c arduino has to constantly
            // check the time while going through the loop
            // -> If using ELIF, it won't allow this statement to be run,
            // if any previous IF statements evaluate to true

            if ((solenoid_state == HIGH) && (millis() - solenoid_on_time > solenoid_on_duration)) {
              solenoid_state = LOW;
              solenoid_off_time = millis();
              digitalWrite(port_solenoid, solenoid_state);

              // reset the ITI and record the time (for run Type = 1)
              reset_ITI = true;
              ITI_start_time = millis();

              Serial.print("solenoid_off: ");
              Serial.println(solenoid_off_time);
            }

            if (run_Type == 2) {
                run_Type = 0;
                solenoid_active = true;
                // ^ solenoid isn't actually active but need to change state so
                // that it doesn't get stuck inside LED_OPERATE loop
                // (need to find an alternative name for an overarching state)

                // reset the ITI and record the time (for run Type = 2)
                reset_ITI = true;
                ITI_start_time = millis();

            }

            // ! possibly where I would need to implement the KFY 
            if (reset_ITI) {
                // reset_ITI = false;
                // ^changing state here will enable the following if clause Just ONCE
                // because duration is involved, need to check the if clause multiple times
                if ((millis() - ITI_start_time) >= wait_interval[time_index]) {
                    reset_ITI = false;
                    solenoid_active = false;
                    time_index += 1;

                    if (time_index >= NUM_TIMES) {
                        time_index = 0;
                    }
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
          Serial.print(Poke_On_Time);
          poke_count += 1;
          during_led_nose_poke += 1;
          Serial.print(" Poke count: ");
          Serial.println(poke_count);
        }

        if (read_gate == HIGH){
          Poke_Off_Time = millis();
          Serial.print("PokeOff: ");
          Serial.println(Poke_Off_Time);
        }
      }

      IR_previous_state = read_gate;
}
