#include "images.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;
int x = 110;
int y = 200;
int angle = 0*3.14159/180.0;

class Camera{
	
	public:
	double error;
	int num_black;
	int num_red;
	int num_blue;
	int num_green;
	int row_start;
	int row_end;
	Camera();
	bool noBlackpix();
	double getLineErrorSignal();
	double numBlackInImg();
	double numRedInImg();
	double numBlueInImg();
	double numGreenInImg();
};
bool  Camera:: noBlackpix(){
	return false;
}
double Camera:: getLineErrorSignal(){
	for(int row = 0; row < 5; row++){
		for(int col = 0; col < camera_image.width; col++){ 
			if (get_camera_pixel(camera_image.height/2, col, 3) < 100 ){
				error = error + (col - 50);
			}
		}
	}
	return error;
}
double Camera:: numBlackInImg(){
	for(int row = 0; row < 5; row++){
		for(int col = 0; col < camera_image.width; col++){ 
			if (get_camera_pixel(camera_image.height/2, col, 3) < 100 ){
					num_black++;
			}
		}
	}
	return num_black;
}
double Camera:: numRedInImg(){
	for(int row = 0; row < 5; row++){
		for(int col = 0; col < camera_image.width; col++){ 
			if (get_camera_pixel(camera_image.height/2, col, 1) < 100 ){
					num_black++;
			}
		}
	}
	return num_red;
}
double Camera:: numBlueInImg(){
	return 0.0;
}
double Camera:: numGreenInImg(){
	return 0.0;
}

Camera::Camera(){
	error = 0;
	num_black = 0;
	num_red = 0;
	num_blue = 0;
	num_green = 0;
	row_start = 50;
	row_end = 55;
}

class Motor{
	private: 
	double kp;
	Camera camera;
	
	public:
	Motor();
	double calculateSpeed();
	void foward(int);
	void reversel(int);
	void turnRight(int);
};

void Motor:: foward(int speed){
	set_motors(10 + speed, 10 - speed);
}
void Motor:: reversel(int speed){
	set_motors(-speed, -speed);
}
void Motor:: turnRight(int speed){
	set_motors(speed, -speed);
}
Motor::Motor(){
	kp = 0.0025;
	camera = Camera();
}

class AVCRobot{
	private :
	int x;
	int y;
	double angle;
	Camera camera;
	Motor motor;
	double kp;
	
	
	public:
	AVCRobot(int, int, double);
	int part;
	void core();
	void completion();
	void challenge();
	void canSeeLine();
	void reverseUntilSeeLine();
	double calculateSpeed();
};
void AVCRobot:: core(){
	
}
void AVCRobot:: completion(){
	
}
void AVCRobot:: challenge(){
	
}
void AVCRobot:: canSeeLine(){
	
}
void AVCRobot:: reverseUntilSeeLine(){
	
}
double AVCRobot:: calculateSpeed(){
	int speed = camera.getLineErrorSignal() * kp;
	return speed;
}

AVCRobot::AVCRobot(int x, int y, double angle){
	x = x;
	y = y;
	angle = angle;
	part = 1;
	kp = 0.002;
	motor = Motor();
	camera = Camera();
}

int main(){
    std::cout<<"start simulation..."<<std::endl;
    AVCRobot avc = AVCRobot(x, y, angle);
    init(x, y, angle);
    update_sim(200);
    while(true){
		if(avc.part == 1){
			avc.core();
			avc.part = 2;
		}
		else if(avc.part == 2){
			avc.completion();
			avc.part = 3;
		}
		else if(avc.part == 3){
			avc.challenge();
			return 0;
		}
		else{
			set_motors(0,0);
			return -1;
		}
	}
}
