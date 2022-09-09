#include "main.h"
#include "driverassistant.hpp"
using namespace pros;

int stime = 0;

void updateDriveTimer(){
	while (true){
		stime++;
		// 1000 ms: 1 sec
		Task::delay(1000);
	}
}

void resetTimer(){
    stime = 0;
}

int getTime(){
    return stime;
}