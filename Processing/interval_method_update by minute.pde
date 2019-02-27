// final version
//
// Logic:
// 1. Initialize the output instance at setup stage
// 2. write data to it (output.flush)
// 3. close the first instance at the if conditional (after interval elapses)
// 4. creates new output every 'x' time
//
// IMPORTANT to initialize the instance - otherwise you'll get a Null Pointer Exception...


import processing.serial.*;    // import the Processing serial library
PrintWriter output;

Serial myPort;

String [] months = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July",
"Aug", "Sept", "Oct", "Nov", "Dec"} ;

long time = 0;    // initialize variable for the current time since program started
String value;// initialize variable for serial data from Arduino
String am_pm;

long interval = 60000;  // in milliseconds
long current_millis = 0;
long last_Event_time = 0;

// time variables (year, month, day etc.)
int y = 0;
int mon = 0;
int d = 0;
int h = 0;
int m = 0;
int s = 0;
int prev_min = 0;

String title = "subject1.txt";

// * * * * * * * * * * * * * * * S E T U P * * * * * * * * * * * * * * *

void setup() {
  size(200,200);

  String portName = Serial.list()[3];  // change every time different port is used

  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');  // would I need this statement?

  //y = year();
  //mon = month();
  //d = day();
  //h = hour();
  //m = minute();
  //s = second();

  output = createWriter(year() + "/" + months[month() - 1] + " " + day() + "th " + String.format("%02d", hour()) + String.format("%02d", minute()) + " " + (hour() > 11? "pm ":"am ") + title);
  last_Event_time = millis();
}

// * * * * * * * * * * * * * * * L O O P  * * * * * * * * * * * * * * *

void draw() {

    record();
       }

void record() {

  current_millis = millis();

  if ( myPort.available() > 0) {  // If data is available,
  value = myPort.readStringUntil('\n'); // read until new line carriage

     // if there is something within serial:
     if (value != null) {

     // prints to console
     println(value);

        // create file after each inverval
        if (current_millis - last_Event_time >= interval){
            y = year();
            mon = month();
            d = day();
            h = hour();
            m = minute();
            s = second();
            am_pm = (hour() > 11)? "pm ":"am ";

            output.close();
            output = createWriter(y + "/" + months[mon-1] + " " + d + "th " + String.format("%02d", h) + String.format("%02d", m) + am_pm + title);

            println(output);
            last_Event_time = millis();

          }
           output.println(value);
           output.flush();
      // expected: outputs value to recently created textfile
     }  // end of (value != null)
   } // end of (myPort.available)
 } // end of void record()

void keyPressed(){

  output.flush();
  output.close();
  println("End Line");
  exit();
  }
