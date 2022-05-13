#include "images.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;

class AVCRobot{
	private int x = 110;
	private int y = 200;
	private double angle = 0*3.14159/180.0;
	private int part = 1;
	
	public:
	AVCRobot();
	void core(){
		
	}
	void completion(){
		
	}
	void challenge(){
		
	}
	void canSeeLine(){
		
	}
	void reverseUntilSeeLine(){
		
	}	
}
AVCRobot::AVCRobot(int x, int y, double angle, Motor motor, Camera camera){
	//please initalise this properly I only know the java way
}

int main(){
    std::cout<<"start simulation..."<<std::endl;
    init(x, y, angle);
    update_sim(200);
    while(true){
		if(part == 1){
			core();
			part = 2;
		}
		else if(part == 2){
			completion();
			part = 3;
		}
		else if(part == 3){
			challenge();
			return 0;
		}
		else{
			setSpeed(0,0);
			return -1;
		}
}
