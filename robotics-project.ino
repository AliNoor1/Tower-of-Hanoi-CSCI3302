#include <Sparki.h>

bool sparki_is_at_peg_1 = 0;
bool sparki_is_at_peg_2 = 0;
bool sparki_is_at_peg_3 = 1;

int go_to_peg_1 = 1;
int go_to_peg_2 = 2;
int go_to_peg_3 = 3;

int decision = 2;
int decision_array[3] = {0,0,0};
bool sparki_grip  = 0;

void peg_decide();
void updateSensorReadings();
void follow_line();
void drop_block();

int left = 0, center = 0, right = 0;
int sparki_dist = 100;

int block = 0;
int block1 = 1;

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
  sparki_dist = sparki.ping();
  sparki.RGB(RGB_RED);
  int threshold = 200;
 
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor
  int edgeLeft   = sparki.edgeLeft();   // measure the left edge IR sensor
  int edgeRight  = sparki.edgeRight();  // measure the right edge IR sensor
    
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
      decision_array[1] = 1;
      sparki.RGB(RGB_BLUE);
      sparki.moveForward();
      delay(500);
     }
    else if((decision_array[0] == 1) && decision_array[1] == 1 && decision_array[2] == 1){
      sparki.RGB(RGB_ORANGE);
      sparki.moveForward();
      delay(500);
      drop_block();
      sparki.moveBackward();
      delay(1500);
      sparki.moveRight(180);
//      sparki.moveStop();
//      delay(10000);
     }
    
  } 
  
  if(sparki_dist < 4.2 && sparki_dist != -1 && sparki_grip == 0){
        sparki_grip = 1;
        sparki.moveStop();
        delay(1000);
        sparki.gripperClose(); // close the robot's gripper
        delay(2500);   
        sparki.gripperStop(); 
        sparki.moveBackward();
        delay(1000);
        sparki.moveRight(180);
      }

   if( (sparki_grip == 1) && (lineCenter < threshold) && (edgeLeft < threshold) && (edgeRight < threshold)){
    decision_array[2] = 1;
    sparki_is_at_peg_2 = 1;
    sparki_is_at_peg_3 = 0;
    decision = 1;
    block = 1;
    peg_decide(); 
    }


    
  sparki.clearLCD(); // erase the lcd
  sparki.print("Distance = ");
  sparki.println(sparki_dist); // print the distance from when Sparki's head is facing center
  sparki.updateLCD(); // write the new LCD values to the screen
  
}

void peg_decide(){
  sparki.RGB(RGB_GREEN);
  decision_array[0] == 1;
  sparki_dist = sparki.ping();
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
       delay(6000);
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
      delay(6500);
      sparki.moveLeft();
      delay(2600);
      sparki.moveForward();
      delay(500);
    }
  }
}

void drop_block(){
  
  if(block == block1){
    sparki.moveForward(20);
    sparki.moveStop();
    delay(1000);
    sparki.gripperOpen(); // close the robot's gripper
    delay(2000); 
    
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

