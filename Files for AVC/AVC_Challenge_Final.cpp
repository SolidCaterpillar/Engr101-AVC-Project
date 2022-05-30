#include "images.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;

int i = 0; // number of colour lane pass 
double kp = 0.0025; // estimation of multiply the error 
int vcr = 15; // speed of left and right motor going forward
bool isComplete = false;

// function for core to create a camera detection to move the robot 
void core(){
	
	int num_black = 0; //detect number of black pixel 
	double error = 0.0; // number of error 
	int vl,vr; 		// variable for left and right motor 
	int dv = 0; 	//variable for error multiply kp to find estimation in speed of turning left and right motors in the lowest number 
	int num_red = 0; 	//detect number of red pixel


	//function to detect black and red pixel by using half of the height camera 
	
	for (int col = 0; col < camera_image.width; col++){
		
		// if there black pixel detect in half of the height camera 
		
		if (get_camera_pixel(camera_image.height/2, col, 3) < 100 )
		{
			num_black++; // to detect number of black in half 
			// SIDE NOTE: when testing the number of black pixel, found out that the width (or a thickness) of the black track is 20 black pixel
			
			error = error + (col - 50); // error split into half of the column, the left side is negative error while the right side is postive error.
		}								// while middle of the column the error is zero. The purpose of it is to make a camera follow a black line in the middle as possible
		
		// if there a red pixel detect in half of the height camera
		
		if ((get_camera_pixel(camera_image.height/2, col, 0) > 2*get_camera_pixel(camera_image.height/2, col, 1))&&get_camera_pixel(camera_image.height/2, col, 0) > 2*get_camera_pixel(camera_image.height/2, col, 2))
		{
			num_red++;
		}
	}

        dv = error * kp; // dv is give the lowest number for motor to turn slightly 
        vl = vcr + dv;	// speed of left motor 
        vr = vcr - dv; //	speed of right motor 

        if (num_black <= 6 && error >=0 ){ // if number of black pixel is less than or equal to 6 in the right side of camera 
            set_motors(15,0);  				// the robot stop and move left by 15 
        } 
        else if (num_black <= 6 && error <= 0 ){ // if number of black pixel is less than or equal to 6 in the left side of camera 
            set_motors(0,15);				// the robot stop and move right  by 15
        }
		else if (error < -700){		// if negative error is higher than -700 far right of the camera when there black pixel 
            set_motors(vl,vr+10);			// the robot move to sightly right side by increase of 10  
		}
		else if (error >  700){		// if negative error is higher than 700 far right of the camera when there black pixel 
			set_motors(vl+10,vr);	// the robot move to sightly left side by increase of 10  
        } 
        else if (error == 0&&num_black <= 5){	// if error is at the middle of the camera but is black pixel is less
			set_motors(20,20); 	// speed up the robot
		}
        else if (num_red>0){	//if camera detected the red pixel
            i = 1; // i became 1 to switch to completion camera 
            return; // return to back to variable to store new value 
		}else set_motors(vl,vr); // if there not much turning the robot, use vl and vr 

		std::cout << "num of black: " << num_black << " error: " << error <<std::endl;
		std::cout << "num of red: " << num_red <<std::endl;
		std::cout << "dv: " << dv << " vl: " << vl << " vr:" << vr <<std::endl;
}

// Completion use boolean to check if the robot have pass the second cross intereection. There are two cross intersection
bool completion(bool check){  
	int num_black = 0; // detect number of black pixel on top of the camera 
	int num_Leftblack = 0; //detect number of black pixel on the left side of the camera
	int num_Rightblack = 0; //detect number of black pixel on the right side of the camera
	double error = 0.0;

	int vl,vr;
	int dv = 0;
	
	int num_blue = 0; //detect number of blue pixel

	for (int col = 0; col < camera_image.width; col++){
		// detect black pixel at top side of the camera
		if (get_camera_pixel(1, col, 3) < 100 )
		{
			num_black++;
			error = error + (col - 50);
		}
		// detect blue pixel at top of the camera
		 if ((get_camera_pixel(1, col, 2) > 2*get_camera_pixel(1, col, 0))&&get_camera_pixel(1, col, 2) > 2*get_camera_pixel(1, col, 1))
		{
			num_blue++;
		}

	}

	for (int row = 0; row < camera_image.height; row++){
		// detect black pixel at left side of the camera
		if (get_camera_pixel(row, 1, 3) < 100 )
		{
			num_Leftblack++;
		}
		// detect black pixel at right side of the camera
		 if (get_camera_pixel(row, camera_image.height, 3) < 100 )
		{
			num_Rightblack++;
		}
	}
	
	dv = error * kp;
	vl = vcr + dv;
	vr = vcr - dv;
        
	if (error < -700){
		set_motors(vl,vr+10);
	}
	else if (error >  700){
		set_motors(vl+10,vr);
	}
	else if (num_Leftblack==0 &&num_Rightblack>0 &&num_black ==0){ // turn right if there no black pixel detected on left and top side
		set_motors(25,0);
	}
	else if (num_Leftblack>0 &&num_Rightblack==0 &&num_black ==0){ // turn right if there no black pixel detected on left and top side
		set_motors(0,25);
	}
	else if (num_Leftblack>0 &&num_Rightblack>0 &&num_black ==0){ // turn left if there no black pixel detected on right and top side
		set_motors(0,25);
	}
	else if (num_Leftblack==20 &&num_Rightblack==20 &&num_black ==20&& !check){ // detect the 1st cross intersection when left, right and top equal to 20 black pixel. The width of the black track is 20 pixel 
		set_motors(vl,50); // a big left turn 
		check = true; // change to true to dectect the second cross intersection
	}
	else if (num_Leftblack==20 &&num_Rightblack==20 &&num_black ==20&&check){ // detect 2nd cross intersection when check is true
		set_motors(50,50); // go straight at high seed ignore left and right track 
	}
	else if (num_blue>0){ // if detect blue 
		i = 2; // make i equal to 2 to switch challenge camera 
		return i;
	}
	else if (num_black>0){
		set_motors(vl,vr);
	}

	std::cout << "num of black: " << num_black << " error: " << error <<std::endl;
	std::cout << "num of left black: " << num_Leftblack <<std::endl;
	std::cout << "num of right black: " << num_Rightblack <<std::endl;
	std::cout << "num of blue: " << num_blue <<std::endl;
	std::cout << "dv: " << dv << " vl: " << vl << " vr:" << vr <<std::endl;
	std::cout << "check: " << check <<std::endl; // checking true or false as in 1 and 0
	return check;
}

// In challenge there are not much change for camera to detect black pixel. The only changes is if conditions with 
void challenge(){
	int num_black = 0;
	int num_Leftblack = 0;
	int num_Rightblack = 0;
	double error = 0.0;

	int vl,vr;
	int dv = 0;
	
	int num_green = 0; //detect number of green pixel
	
//-------------- this code is from completion there not much changes but only detecting green pixel--------------------//

	for (int col = 0; col < camera_image.width; col++){
	
		if (get_camera_pixel(1, col, 3) < 100 )
		{
		num_black++;
		error = error + (col - 50);
		}
		
		// detect green pixel at top of the camera
		 if ((get_camera_pixel(1, col, 1) > 2*get_camera_pixel(1, col, 0))&&get_camera_pixel(1, col, 1) > 2*get_camera_pixel(1, col, 2))
		{
			num_green++;
		}
	}

	for (int row = 0; row < camera_image.height; row++){

		if (get_camera_pixel(row, 1, 3) < 100 )
		{
			num_Leftblack++;
		}
		 if (get_camera_pixel(row, camera_image.height, 3) < 100 )
		{
			num_Rightblack++;
		}
	}

//---------------------------------------------------------------------------------------------------------------------------------//       
        dv = error * kp;
        vl = vcr + dv;
        vr = vcr - dv;

       if (num_green>=70){ 		// if detect green pixel, make robot stop 
			set_motors(0,0); 
			isComplete = true;  
        }
        else { 
			if (error < -700){
				set_motors(vl,vr+10);
			}
            else if (error >  700){
				set_motors(vl+10,vr);
			}
			else if (num_Leftblack==0 &&num_Rightblack>0 &&num_black >0){ // if there no track on left side camera, move right 
				set_motors(10,0);
			}
			else if (num_Leftblack>0 &&num_Rightblack==0 &&num_black ==0){ // if there a track on left side camera, turn right??? 
				set_motors(0,25);
			}
			else if (num_Leftblack>0 &&num_Rightblack>0 &&num_black ==0){ // if there a track on the left and right side camera, turn left 
				set_motors(25,0);
			}	
			else if (num_Leftblack>=20 &&num_Rightblack==0 &&num_black >0){ // if there a track on the left and top camera, turn left
				set_motors(30,0);
			}
			else if (num_black>0){  // robot go forward by detect the top side of the camera
				set_motors(vl,vr);
			}
}

	std::cout << "num of black: " << num_black << " error: " << error <<std::endl;
	std::cout << "num of left black: " << num_Leftblack <<std::endl;
	std::cout << "num of right black: " << num_Rightblack <<std::endl;
	std::cout << "num of green: " << num_green <<std::endl;
	std::cout << "dv: " << dv << " vl: " << vl << " vr:" << vr <<std::endl;
	std::cout << "i: " << i <<std::endl;
        
}


int main()
{
    std::cout<<"start simulation..."<<std::endl;
    init(110,160,15*3.14159/180.0);

    bool check = false; // checking for cross intersection
    while(!isComplete){ 
   
		update_sim(300);
        
		if (i==0){ // when i equal 0 (no lane pass) use core camera
			core();
		}else if (i == 1) { //when i is 1 use completion camera 
			check = completion(check); // completion switch false/true for 'check' if detect cross intersection
		}else if (i == 2){
			challenge();
		}

		update_sim(300);
    }
    return 0;
}

