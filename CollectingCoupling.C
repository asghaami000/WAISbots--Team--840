#include <kipr/wombat.h>

// West is toward the large start box
// East is toward the coupler


int leftlight = 0;
int rightlight = 1;
int left = 0;
int right = 3;
int white = 1600; 

void followLine(int type, int port, int direction){
    if (type == 0){
        while (digital(8) == 0 && digital(9) == 0){
            if (analog(port) < white){
                motor(left, 90*direction);
                motor(right, 5*direction);
            }
            else if (analog(port) > white){
                motor(left, 5*direction);
                motor(right, 90*direction);
            }
        }
    }
}

void followLine2(int type){
    if (type == 0){
        while (digital(8) == 0 && digital(9) == 0){
            if (analog(leftlight) <= white && analog(rightlight) <= white){
                motor(left, 50);
                motor(right, 50);
            }
            else if (analog(leftlight) > white && analog(rightlight) <= white){
                motor(left, 5);
                motor(right, 90);
            }
            else if (analog(leftlight) <= white && analog(rightlight) > white){
                motor(left, 90);
                motor(right, 5);
            }
            else if (analog(leftlight) > white && analog(rightlight) > white){
                motor(left, 60);
                motor(right, 60);
            }
            else{
                printf("what is happening now?!");
            }
        }
    }
}

void servo(int servoNum, int finalPos, int endTime, int up){
    int startPos = get_servo_position(servoNum);
    int currentPos = startPos;
    double startTime = 0;
    double currentTime = startTime;
    double timePercent;
    int waitFactor;

    enable_servos();
    while ((currentPos*up) < (finalPos*up)){
        currentTime += .1;
        timePercent = (currentTime-startTime) / (endTime-startTime);
        currentPos = (timePercent*(finalPos-startPos)) + startPos;
        waitFactor = (currentTime*currentTime)*0.1; 

        set_servo_position(servoNum,currentPos);
        msleep(waitFactor);
    }
    disable_servos();
}

void lineSquare(int speed){
    while (analog(leftlight) <= white || analog(rightlight) <= white){
        if (analog(leftlight) <= white && analog(rightlight) <= white){
            mav(left, speed);
            mav(right, speed);
        }
        else if (analog(leftlight) > white && analog(rightlight) <= white){
            motor(left, -10);
            motor(right, 70);
        }
        else if (analog(leftlight) <= white && analog(rightlight) > white){
            motor(left, 70);
            motor(right, -10);
        }
        else{
            printf("Que?!");
        }
    }
}


//motors: motor 3 right -- motor 0 left 
//touch sensors: digital 9 right --- digital 8 left 
//- analog 0 tophat left -- analog 1 right
// servo port 3 
int main()   
{
    // Move pincer claw up
    servo(2,600,20,-1);
    // Open claw
    servo(3,800,20,-1);

    // go untuil edge of small strt box
    while(analog(0) < white){
        motor(0, 80);
        motor(3, 80); 
    } 

    //turn right to the side with PVC
    motor(3, 70);
    motor(0, -20);
    msleep(1500);

    //follow line until hit wall
    /*
    while(digital(9) == 0 && digital(8) == 0){

       if(analog(0) < white && analog(1) > white){
           motor(0, 50);
           
       }else if(analog(0) > white && analog(1) < white){
           
           motor(3, 50);     

       }else{
           motor(0, 50);
           motor(3, 50);
       }
    }
  	*/

    // follow the E-W center line until East edge pipe
    followLine(0, 0, 1);

    //turn backward so stinger face cupling
    motor(3, -90);
    motor(0, -12);
    msleep(2400);
    
    // pause
    motor(3, 0);
    motor(0, 0);
    msleep(15);

    // lower pincer
    servo(3,1560,20,1);
    	//jiggle to help pincer in

             motor(left, 50);
         	 motor(right, -10);
    		 msleep(500);
     		 motor(left, -10);
         	 motor(right, 50);
    		 msleep(500);
    
    
     // go untuil see cetner black line
    while(analog(0) < white){
        motor(0, 80);
        motor(3, 80); 
    } 
    //followline to middle using teiks
    cmpc(0);
    while(gmpc(0) <9300){
    	 if (analog(0) < white){
                motor(left, 90);
                motor(right, 5);
            }
            else if (analog(0) > white){
                motor(left, 5);
                motor(right, 90);
            }
    }
    
    //turn right to set up at the botgal place 
    motor(3, 90);
    motor(0, -30);
    msleep(1300);



    return 0;
}


