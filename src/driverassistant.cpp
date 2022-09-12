#include "main.h"
#include "driverassistant.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.h"
using namespace pros;

// Vision vsensor(11);

vision_signature_s_t RED = Vision::signature_from_utility(5, 6701, 8763, 7732, -1129, -541, -836, 3.6, 0);
vision_signature_s_t BLUE = Vision::signature_from_utility(6, -2453, -1587,-2020, 6337, 8753, 7546, 1.9, 0);

vision_object_s_t red = vsensor.get_by_sig(0, 5);
vision_object_s_t blue = vsensor.get_by_sig(0, 6);

int stime = 0;

void updateDriveTimer(){
	while (true){
		stime++;
		// 1000 ms: 1 sec
    controller.print(0, 0, "Fw: %d", getFly(), "fs %d", 20);
		Task::delay(1000);
	}
}

void resetTimer(){
    stime = 0;
}

void centerGoal(){

  
  //if you want to keep your previous stopping mode, change it after this function is called.
  driveBrake();

  int midx = 316/2;

  int x = 0;

//   while(x < 175){
	
	int redXmid = red.x_middle_coord;
	int blueXmid = blue.x_middle_coord;

    // if (red.height > 3 || blue.height > 3){
      if ((redXmid < midx - 20 && redXmid > 0)||(blueXmid < midx - 20 && blueXmid > 0)){
		setDrive(20/2, 20);
      }
      else if ((redXmid > midx + 20 && redXmid < 316)||(blueXmid > midx + 20 && blueXmid < 316)){
		setDrive(20, 20/2);
      }
      else if ((redXmid >= midx - 20 && redXmid <= midx + 20 && red.width > 20 )||(blueXmid >= midx - 20 && blueXmid <= midx + 20 && blue.width > 20)){
        setDrive(0,0);
        x++;
      }
    // }
    // else{
    //   setDrive(0,0);
    // }
    delay(30);
//   }
}

int getTime(){
    return stime;
}

