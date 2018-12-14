#include <Sparki.h>

int solution[4][4] = {  {1, 1, 3},
                        {0, 3, 1},
                        {2, 1, 2},
                        {1, 3, 2} }; //[block, peg_from, peg_to]

int block = 0;
int current_peg = 0;
int next_peg = 0;
size_t size = sizeof(solution) / sizeof(solution[0]);
int end_func = 0; 
int i = 0;

int decision_array[3] = {0,0,0};
bool sparki_grip  = 0;

void peg_decide(int block, int current_peg, int next_peg);
bool follow_line(int block, int current_peg, int next_peg);
void pick_up_block();
void drop_block();

int left = 0, center = 0, right = 0;
int sparki_dist = 100;

int block1 = 1;

void setup() {
  sparki.servo(SERVO_CENTER);
  sparki.gripperOpen();
  delay(1000);
}

void loop() {
  if(i < size){ 
      block = solution[i][0];
      current_peg = solution[i][1];
      next_peg = solution[i][2];
      
      sparki.clearLCD(); // erase the lcd
      sparki.print("Block = ");
      sparki.println(block); // print the distance from when Sparki's head is facing center
      sparki.print("Current Peg = ");
      sparki.println(current_peg); // print the distance from when Sparki's head is facing center
      sparki.print("Next Peg = ");
      sparki.println(next_peg); // print the distance from when Sparki's head is facing center
      sparki.print("i = ");
      sparki.println(i); // print the distance from when Sparki's head is facing center
      sparki.print("array size = ");
      sparki.println(size); // print the distance from when Sparki's head is facing center
      sparki.print("end_func = ");
      sparki.println(end_func); // print the distance from when Sparki's head is facing center
      sparki.updateLCD(); // write the new LCD values to the screen
      
      if (end_func == 0){
        follow_line(block, current_peg, next_peg); 
      }
      
      if(end_func == 1){
        i++;
      }
      end_func = 0;
  }
}

bool follow_line(int block, int current_peg, int next_peg){
  // put your main code here, to run repeatedly:
  sparki_dist = sparki.ping();
  sparki.RGB(RGB_RED);
  int threshold = 200;  
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor
  int edgeLeft   = sparki.edgeLeft();   // measure the left edge IR sensor
  int edgeRight  = sparki.edgeRight();  // measure the right edge IR sensor
    
  if ( lineLeft < threshold )
  {  
    sparki.moveLeft(); // turn left
  }
 
  if ( lineRight < threshold ) 
  {  
    sparki.moveRight(); // turn right
  }
 
  if ( (lineCenter < threshold) && (lineLeft > threshold) && (lineRight > threshold) )
  {
    sparki.moveForward(); // move forward
  }  

  if ( (lineCenter < threshold) && (edgeLeft < threshold) && (edgeRight < threshold) )
  {
    
     
    if(decision_array[0] == 0){
      sparki.moveForward();
      delay(500);
      decision_array[0] = 1;
//      block = solution[0][0];
//      current_peg = solution[0][1];
//      next_peg = solution[0][2];
      
      //###########################################################################
      //###########################################################################
      //##############add code to pick up block 1 first############################
      //###########################################################################
      //###########################################################################
      
      peg_decide(block, current_peg, next_peg);
      
      }
      
    else if((decision_array[0] == 1) && decision_array[1] == 0){
      decision_array[1] = 1;
      sparki.RGB(RGB_BLUE);
      sparki.moveForward();
      delay(800);
      sparki.moveStop();
      delay(800);
      sparki.gripperClose();
      sparki.moveStop();
      delay(2000);
      
     }
     
    else if((decision_array[0] == 1) && decision_array[1] == 1 && decision_array[2] == 1){
      sparki.RGB(RGB_ORANGE);
      sparki.moveForward();
      delay(9000);
      drop_block();
      sparki.moveBackward();
      delay(1500);
      sparki.moveRight();
      delay(4500);
      decision_array[0] = 0;
      decision_array[1] = 0;
      decision_array[2] = 0;
      
      end_func = 1;
      
//      sparki.moveStop();
//      delay(10000);
     }
     if((decision_array[0] == 1) && decision_array[1] == 1 && decision_array[2] == 0){
      sparki.RGB(RGB_PINK);
      sparki.moveRight();
      delay(5000);
      sparki.moveBackward();
      delay(1000);
      sparki.moveForward();
      delay(100);
      decision_array[2] = 1;
      peg_decide(block, next_peg, current_peg);
     }

    

  }

/*
  if( (sparki_dist < 4.2) && (sparki_dist != -1) && (sparki_grip == 0) ){
        end_func=1;
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
      */

//##############RUNNING SPARKI AGAIN TO DROP THE BLOCK BY INDICATING WHERE IT CURRENTLY IS#################
//   if( (sparki_grip == 1) && (lineCenter < threshold) && (edgeLeft < threshold) && (edgeRight < threshold)){
//    decision_array[2] = 1;
//    //sparki_is_at_peg_2 = 1;
//    //sparki_is_at_peg_3 = 0;
//    decision = 1;
//    block = 1;
//    peg_decide(); 
//    }

  sparki.clearLCD(); // erase the lcd
  sparki.print("Distance = ");
  sparki.println(sparki_dist); // print the distance from when Sparki's head is facing center
  sparki.updateLCD(); // write the new LCD values to the screen
  
}

void peg_decide(int block, int current_peg, int next_peg){
 
  sparki.RGB(RGB_GREEN);
  
  if(current_peg == 1){
    if(next_peg == 2)
    {
       sparki.moveForward();
       delay(5000);
       sparki.moveRight();
       delay(500);
    }
    else if(next_peg == 3)
    {
      sparki.moveForward();
      delay(5500);
      sparki.moveLeft();
      delay(500);
    }
  }

  else if(current_peg == 2){
    if(next_peg == 1)
    {
       sparki.moveForward();
       delay(6000);
       sparki.moveLeft();
       delay(500);
    }
    else if(next_peg  == 3)
    {
      sparki.moveForward();
      delay(4800);
      sparki.moveRight();
      delay(2200);
    }
  }

  else if(current_peg == 3 ){
    if(next_peg == 1)
    {
       sparki.moveForward();
       delay(5000);
       sparki.moveRight();
       delay(500);
    }
    else if(next_peg == 2)
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

void pick_up_block() {
    if( (sparki_dist < 4.2) && (sparki_dist != -1) && (sparki_grip == 0) ){
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
  } 

void drop_block(){
  if(block == block1){
    sparki.moveForward();
    sparki.moveStop();
    delay(1000);
    sparki.gripperOpen(); // close the robot's gripper
    delay(2000); 
    
    }
  }

