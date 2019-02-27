/*Processing Sketch for Arduino
/ TimeStamp Functionality Included
/ Outputs to txtfile and can read any data type (string, float, int etc.) 
/
/ *IMPT to create directory in which the output file will be saved in*
/
/ JHL. 11/7/18
/
/
*/

import processing.serial.*;    // import the Processing serial library
PrintWriter output;  

Serial myPort; 

String [] months = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", 
"Aug", "Sept", "Oct", "Nov", "Dec"} ;   

long time=0;    // initialize variable for the current time since program started
String value;// initialize variable for serial data from Arduino
int y = 0;
int idx =0;
int d = 0;
int h = 0;
int m = 0;
String am_pm;

String title = "mouse1.txt";

void setup() {
  size(200,200);
  
  String portName = Serial.list()[3];  // change every time different port is used
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');  // would I need this statement?
  
  y = year();
  idx = month();
  d = day();
  h = hour();
  m = minute();

// AM/PM functionality

  if (h > 11) {
    h = h - 12; 
    am_pm = "PM";
  }
  else {
    am_pm = "AM";
  }
  
  output = createWriter(y + "/" + months[idx-1] + " " + d + "th " + h + "." + m + am_pm + "_" + title);
 
}

// "/" creates directory (in above example, creates year(2018) directory)

void draw()
{
 record();
}

void record() {
 if ( myPort.available() > 0) {  // If data is available,
  value = myPort.readStringUntil('\n'); // read until new line carriage 
  
  if (value != null) {
    
   println(value);
   output.print(value);
  }
 }
}
  
void keyPressed(){
  
  output.flush();
  output.close();
  println("End Line");
  exit();
  }
