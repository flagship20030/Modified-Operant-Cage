/*Processing Sketch for Arduino
/ TimeStamp Functionality Included
/ Outputs to txtfile and can read any data type (string, float, int etc.)
/
/ *IMPT to create directory in which the output file will be saved in*
/
/ JHL. 11/7/18
/
/ updated 2/12/19 (saves outputevery x hour / x minute)
/ using the (prev_min != minute) logic

/ Key Reference:
/ https://forum.processing.org/two/discussion/25401/createwriter-ouput-based-on-time-of-the-day
/
/
/ Secondary (not actually used - just for fun in the future)
/ https://forum.processing.org/one/topic/printwriter-to-multiple-files.html
*/

// output format: mmddyy_hhmm(am/pm)_mouse_#.txt  (Ex: 020419_1234pm_mouse_1.txt)
//

import processing.serial.*;    // import the Processing serial library
PrintWriter output;

Serial myPort;

// String [] months = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sept", "Oct", "Nov", "Dec"} ;

long time=0;    // initialize variable for the current time since program started
String value;// initialize variable for serial data from Arduino

int y = 0;
int mon = 0;
int d = 0;
int h = 0;
int m = 0;
int s = 0;
String am_pm;

String title = "mouse_1.txt";

int prev_min = minute();

// * * * * * * * * * * * * * * * * S E T U P * * * * * * * * * * * * * *

void setup() {
  size(200,200);

  String portName = Serial.list()[3];  // change every time different port is used
  // look it from Arduino Side (simple indexing from 0)

  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');  // would I need this statement?



  // first
  // "/" makes the directory: in this example, creates a directory named "2019"
  // output format: mmddyy_hhmm(am/pm)_mouse_#.txt  (Ex: 020419_1234pm_mouse_1.txt)
  // first instance of output:

  output = createWriter(year() + "/" + String.format("%02d", month()) + String.format("%02d", day()) + String.format("%04d", year()) + "_" +
  String.format("%02d", hour()) + String.format("%02d", minute()) + (hour() > 11? "pm ":"am ") + title);

}

// * * * * * * * * * * * * * * * * L O O P * * * * * * * * * * * * * *

void draw()
{
 record();
}

// * * * * * * * * * * * * * * * * F U N C T I O N * * * * * * * * * * * * * *

void record() {

  if (myPort.available() > 0) {  // If data is available,
    value = myPort.readStringUntil('\n'); // read until new line carriage


    if (value != null) {

    // prints to console
      println(value);

      // creates output instance every minute:
      if (prev_min != minute()) {

        output.close(); // close the first instance --loops around--> close the next instances

        output = createWriter(year() + "/" + String.format("%02d",month()) + String.format("%02d",day()) + String.format("%04d",year()) + "_" +
                  String.format("%02d", hour()) + String.format("%02d", minute()) + (hour() > 11? "pm ":"am ") + title);

        prev_min = minute();

      }
      output.print(value);
      output.flush();

  } // end of (value != null)
 } // end of (myPort.available() > 0)
} // end of function

// just to exit out of the program:
void keyPressed(){

  output.flush();
  output.close();
  println("End Line");
  exit();
  }
