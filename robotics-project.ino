#include <Sparki.h>

bool sparki_is_at_peg_1 = 0;
bool sparki_is_at_peg_2 = 0;
bool sparki_is_at_peg_3 = 1;

int go_to_peg_1 = 1;
int go_to_peg_2 = 2;
int go_to_peg_3 = 3;

int decision = 1;
int decision_array[2] = {0,0};

void peg_decide();
void updateSensorReadings();
void follow_line();

int left = 0, center = 0, right = 0;
int sparki_dist = 100;

void setup() {
  // put your setup code here, to run once:
  sparki.servo(SERVO_CENTER); // rotate the servo to is 0 degree postion (forward)
  sparki.gripperOpen();  // open the robot's gripper
  delay(1000);
}

void loop() {
  follow_line();
}

void follow_line(){
  // put your main code here, to run repeatedly:
  sparki.RGB(RGB_RED);
  int threshold = 300;
 
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor
  int edgeLeft   = sparki.edgeLeft();   // measure the left edge IR sensor
  int edgeRight  = sparki.edgeRight();  // measure the right edge IR sensor
  
  sparki.dist = sparki.ping();
  if(sparki_dist == 4){
    sparki.RGB(RGB_BLUE);
    sparki.moveStop();
    sparki.gripperClose(); // close the robot's gripper
    delay(1000);   
    }
  
  
  if ( lineLeft < threshold ) // if line is below left line sensor
  {  
    sparki.moveLeft(); // turn left
  }
 
  if ( lineRight < threshold ) // if line is below right line sensor
  {  
    sparki.moveRight(); // turn right
  }
 
  // if the center line sensor is the only one reading a line
  if ( (lineCenter < threshold) && (lineLeft > threshold) && (lineRight > threshold) )
  {
    sparki.moveForward(); // move forward
  }  

  if ( (lineCenter < threshold) && (edgeLeft < threshold) && (edgeRight < threshold) )
  {
    if(decision_array[0] == 0){
      decision_array[0] = 1;
      peg_decide();
      }
    else if((decision_array[0] == 1) && decision_array[1] == 0){
      //sparki.moveStop();
      //delay(1000);
      //TO DO: call a function to reset Odometry
      //
      //
      //
      //   
      pick_up_box();   
      center = sparki.ping(); // get the distance from the distance sensor
      updateSensorReadings(); // refresh the screen
      }
  } 
 
 /* sparki.clearLCD(); // wipe the screen
 
  sparki.print("Line Left: "); // show left line sensor on screen
  sparki.println(lineLeft);
 
  sparki.print("Line Center: "); // show center line sensor on screen
  sparki.println(lineCenter);
 
  sparki.print("Line Right: "); // show right line sensor on screen
  sparki.println(lineRight);
 
  sparki.updateLCD(); // display all of the information written to the screen
 
  delay(100); // wait 0.1 seconds*/
  }

void pick_up_box(){
  sparki.RGB(RGB_BLUE);
  
  if(sparki_dist == 3){
    sparki.RGB(RGB_BLUE);
    sparki.moveStop();
    sparki.gripperClose(); // close the robot's gripper
    delay(1000);   
    }
  }


void peg_decide(){
  sparki.RGB(RGB_GREEN);
  decision_array[0] == 1;
  
  if(sparki_is_at_peg_1){
    if(decision == go_to_peg_2)
    {
       sparki.moveForward();
       delay(5000);
       sparki.moveRight();
       delay(500);
    }
    else if(decision == go_to_peg_3)
    {
      sparki.moveForward();
      delay(5500);
      sparki.moveLeft();
      delay(500);
    }
  }

  else if(sparki_is_at_peg_2){
    if(decision == go_to_peg_1)
    {
       sparki.moveForward();
       delay(5000);
       sparki.moveLeft();
       delay(500);
    }
    else if(decision == go_to_peg_3)
    {
      sparki.moveForward();
      delay(4800);
      sparki.moveRight();
      delay(2200);
    }
  }

  else if(sparki_is_at_peg_3){
    if(decision == go_to_peg_1)
    {
       sparki.moveForward();
       delay(5000);
       sparki.moveRight();
       delay(500);
    }
    else if(decision == go_to_peg_2)
    {
      sparki.moveForward();
      delay(4800);
      sparki.moveLeft();
      delay(2200);
    }
  }
}

void updateSensorReadings()
{
  // refresh all the display data at once:
  sparki.clearLCD(); // erase the lcd
  sparki.print("Center = ");
  sparki.println(center); // print the distance from when Sparki's head is facing center
  sparki.updateLCD(); // write the new LCD values to the screen
}

