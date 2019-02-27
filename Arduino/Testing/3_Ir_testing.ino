// Updated 12/10/18
// Simple Code to determine if IR is working (troubleshooting purposes)

// IRs
byte port_IR_8 = 8;
byte port_IR_10 = 10;
byte port_IR_11 = 11;

// if conditional states:
boolean led_switched_off = false;
boolean solenoid_active = false;

// boolean IR_previous_state_10;
boolean IR_previous_state_8;
boolean IR_previous_state_10;
boolean IR_previous_state_11;

// unsigned long led_off_time = 0; // out here as a global variable to be accessed by solenoid_operate()

// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

void setup(){

 //  pinMode(port_IR_4, INPUT);
  pinMode(port_IR_8, INPUT);
  pinMode(port_IR_10, INPUT);
  pinMode(port_IR_11, INPUT);

  Serial.begin(9600);

  delay(1500);
  Serial.println("Start Test Program");

}

// * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * * *

void loop() {
    record_IR();
}

void record_IR() {

  static unsigned long Poke_On_Time_8 = 0;
  static unsigned long Poke_Off_Time_8 = 0;

  byte read_gate_8 = digitalRead(port_IR_8);

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

  static unsigned long Poke_On_Time_10 = 0;
  static unsigned long Poke_Off_Time_10 = 0;

  byte read_gate_10 = digitalRead(port_IR_10);

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


static unsigned long Poke_On_Time_11 = 0;
static unsigned long Poke_Off_Time_11 = 0;

byte read_gate_11 = digitalRead(port_IR_11);

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

// * * * * * * * * * * * L O O P * * * * * * * * * * * * * * * *
