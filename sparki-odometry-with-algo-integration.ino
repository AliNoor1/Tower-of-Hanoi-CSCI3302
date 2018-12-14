#include <Sparki.h>

int current_state = 0;
#define CALCULATE 0
#define GRAB_BLOCK 1
#define DROP_BLOCK 2

#define GRAB 1
#define PEG_DECIDE 2
#define FOLLOW_LINE 0
int line_status = 0;

int solution[3][3] ={{1,2,1},
                     {2,2,3},
                     {1,1,3}}; //[block, peg_from, peg_to]
bool get_solution = false;

int block = 0;

int current_peg = 0;
int next_peg = 0;
int pick_up_peg = 0;
int drop_off_peg = 0;

int solution_index = 0;

size_t size = sizeof(solution) / sizeof(solution[0]);

int decision_array[2] = {0,0};
bool sparki_grip  = 0;

void peg_decide(int current_peg, int next_peg);
void follow_line_pick_up(int current_peg, int next_peg);
void follow_line_drop_block(int block, int current_peg, int next_peg);
void drop_block(int block);

int left = 0, center = 0, right = 0;
int sparki_dist = 100;

void setup() {
  sparki.servo(SERVO_CENTER);
  sparki.gripperOpen();
  delay(1000);
  current_peg = 1;
  
}

void loop() 
{
  sparki.clearLCD(); // erase the lcd
  sparki.print("current status = ");
  sparki.println(current_state); // print the distance from when Sparki's head is facing center
  sparki.updateLCD(); // write the new LCD values to the screen
  
  switch(current_state)
  {
    case CALCULATE: 
    {
      sparki.RGB(RGB_PINK);
      if(get_solution == false)
      {
        //Algorithm
        get_solution == true;
      }
//      else
      
        // ERROR CHECK
        block = solution[0][0];
        pick_up_peg = solution[0][1];
        drop_off_peg = solution[0][2];
        
        solution_index++;
        current_state = GRAB_BLOCK;
      
    }
  
    case GRAB_BLOCK:
    {
      sparki.clearLCD(); // erase the lcd
      sparki.print("Block = ");
      sparki.println(block); // print the distance from when Sparki's head is facing center
      sparki.print("Current Peg = ");
      sparki.println(current_peg); // print the distance from when Sparki's head is facing center
      sparki.print("Pick up Peg = ");
      sparki.println(pick_up_peg); // print the distance from when Sparki's head is facing center
      sparki.updateLCD(); // write the new LCD values to the screen
      
      follow_line_pick_up(current_peg, pick_up_peg);
      //current_state = DROP_BLOCK;
      current_peg = pick_up_peg;
    }
  
    case DROP_BLOCK:
    {
      follow_line_drop_block(block, current_peg, drop_off_peg);
      
    }
    
  }
}

void follow_line_pick_up(int current_peg, int next_peg){
  int threshold = 200;  
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor
  int edgeLeft   = sparki.edgeLeft();   // measure the left edge IR sensor
  int edgeRight  = sparki.edgeRight();  // measure the right edge IR sensor

  switch(line_status){
    case FOLLOW_LINE:
    {
      sparki.RGB(RGB_RED);
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
      
      else if((lineCenter < threshold) && (edgeLeft < threshold) && (edgeRight < threshold) && decision_array[0] == 0){
        line_status = PEG_DECIDE;
        }

      else if((lineCenter < threshold) && (edgeLeft < threshold) && (edgeRight < threshold) && decision_array[0] == 1 && decision_array[1] == 0){
        line_status = GRAB;
      }

      else if((lineCenter < threshold) && (edgeLeft < threshold) && (edgeRight < threshold) && decision_array[0] == 1 && decision_array[1] == 1){
        current_state = DROP_BLOCK;
      }
      
      }
    
    case PEG_DECIDE:
    {
      sparki.RGB(RGB_YELLOW);
      sparki.moveForward();
      delay(500);
      decision_array[0] = 1;
      peg_decide(current_peg, next_peg);
      line_status = FOLLOW_LINE;
 
    }

    case GRAB:
    {
      decision_array[1] = 1;
      sparki.RGB(RGB_BLUE);
      sparki_dist = sparki.ping();
      sparki.moveForward();
      if( (sparki_dist < 4.2) && (sparki_dist != -1) && (sparki_grip == 0) )
      {
        sparki.moveStop();
        delay(1000);
        sparki.gripperClose(); // close the robot's gripper
        delay(2500);   
        sparki.gripperStop(); 
        sparki.moveBackward();
        delay(1500);
        sparki.moveRight(180);
      }
      line_status = FOLLOW_LINE;
      }
    
  }
//  if ( (lineCenter < threshold) && (edgeLeft < threshold) && (edgeRight < threshold) )
//  {
//      
//    else if((decision_array[0] == 1) && decision_array[1] == 0){
//      decision_array[1] = 1;
//      sparki.RGB(RGB_BLUE);
//      sparki_dist = sparki.ping();
//      sparki.moveForward();
//      if( (sparki_dist < 4.2) && (sparki_dist != -1) && (sparki_grip == 0) )
//      {
//        sparki.moveStop();
//        delay(1000);
//        sparki.gripperClose(); // close the robot's gripper
//        delay(2500);   
//        sparki.gripperStop(); 
//        sparki.moveBackward();
//        delay(1500);
//        sparki.moveRight(180);
//      }
//     }
//
//    else if((decision_array[0] == 1) && decision_array[1] == 1){
//      current_state = DROP_BLOCK;
//     }
//     
//  } 

}


void follow_line_drop_block(int block, int current_peg, int next_peg){
  sparki.RGB(RGB_RED);
  int threshold = 200;  
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor
  int edgeLeft   = sparki.edgeLeft();   // measure the left edge IR sensor
  int edgeRight  = sparki.edgeRight();  // measure the right edge IR sensor
  decision_array[0] = 0;
  decision_array[1] = 0;  
 
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
      peg_decide(current_peg, next_peg);
      }
      
    else if((decision_array[0] == 1) && (decision_array[1] == 0)){
      sparki.RGB(RGB_ORANGE);
      sparki.moveForward();
      delay(500);
      drop_block(block);
      sparki.moveBackward();
      delay(1500);
      sparki.moveRight(180);
//      sparki.moveStop();
//      delay(10000);
     }

    else if((decision_array[0] == 1) && decision_array[1] == 1){
      current_state = CALCULATE;
     }
     
  } 

}


void peg_decide(int current_peg, int next_peg){
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

void drop_block(int block){
  if(block == 1){
    sparki.moveForward(5);
    sparki.moveStop();
    delay(1000);
    sparki.gripperOpen(); // close the robot's gripper
    delay(2000); 
    }

    if(block == 2){
    sparki.moveForward(10);
    sparki.moveStop();
    delay(1000);
    sparki.gripperOpen(); // close the robot's gripper
    delay(2000); 
    }
    
    if(block == 3){
    sparki.moveForward(15);
    sparki.moveStop();
    delay(1000);
    sparki.gripperOpen(); // close the robot's gripper
    delay(2000); 
    }
    
  }
  // put your main code here, to run repeatedly:
//  sparki_dist = sparki.ping();


//##############RUNNING SPARKI AGAIN TO DROP THE BLOCK BY INDICATING WHERE IT CURRENTLY IS#################
//   if( (sparki_grip == 1) && (lineCenter < threshold) && (edgeLeft < threshold) && (edgeRight < threshold)){
//    decision_array[2] = 1;
//    //sparki_is_at_peg_2 = 1;
//    //sparki_is_at_peg_3 = 0;
//    decision = 1;
//    block = 1;
//    peg_decide(); 
//    }

//  sparki.clearLCD(); // erase the lcd
//  sparki.print("Distance = ");
//  sparki.println(sparki_dist); // print the distance from when Sparki's head is facing center
//  sparki.updateLCD(); // write the new LCD values to the screen
 

//      sparki.clearLCD(); // erase the lcd
//      sparki.print("Block = ");
//      sparki.println(block); // print the distance from when Sparki's head is facing center
//      sparki.print("Current Peg = ");
//      sparki.println(current_peg); // print the distance from when Sparki's head is facing center
//      sparki.print("Next Peg = ");
//      sparki.println(next_peg); // print the distance from when Sparki's head is facing center
//      sparki.print("i = ");
//      sparki.println(i); // print the distance from when Sparki's head is facing center
//      sparki.print("array size = ");
//      sparki.println(size); // print the distance from when Sparki's head is facing center
