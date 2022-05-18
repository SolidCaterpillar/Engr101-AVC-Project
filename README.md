# ENGR101 - Project3 - AVC - Team 1


#### Team members
##### Contact Information

- dograarna@myvuw.ac.nz
- hsuchun1@myvuw.ac.nz
- ransomoliv@myvuw.ac.nz
- mclauczach@myvuw.ac.nz
- fongrick@mvuw.ac.nz


**Arnav Dogra - Project Manager**
- Ensures all tasks are completed to a high standard.
- Planning and organizing group meetings.
- Ensuring all deadlines are met.


**Jonanthan Hsu - Software Architect**
- Create the general design of the software
- Help the Software Engineers code and overcome problems they may face

 
**Ollie Ransom - Tester**
- Give valuable feedback to the group
- Find errors in the code the Software Architect and Software Engineers create

**Zach Mclauchlan, Ricky Fong - Software Engineers:**
- Works with the Software Architect to Implement code
- Main writers of code


#### General Design of the software

Have multiple methods and classes

Three classes
##### Camera
- Deals with all of the image processing
- Checking for black line
- Error calculation
- Sends data to the motors for them to be adjusted
- Intersection checking



##### Motor
- Changes the speeds, depending on the data from the camera class

##### Main AVC
- Gathers information from the  Camera and Motor classes 
- Processes the logic  about the robot itself

#### Roadmap
|start date	   |     task description	   |         responsible| team members	| end date	   |     outcome|
|------|------|-------|------|-----|----|
|9/5/22|Implement Code from lectures|Software Engineers + Software Architect | Zach, Jono and Ricky| 13/5/22|**Done** - Date Completed = 13/5/22 |
|13/5/22|Test code to find errors|Tester|Ollie|15/5/22|Not Done - Date Completed = |
|15/5/22|Finish Core | Software Engineers + Software Architect | Zach, Jono and Ricky|20/5/22|**Done** - Date Completed = 16/5/22|
|20/5/22|Completion | Software Engineers + Software  Architect |  Zach, Jono, ricky| 26/05/22|**Done** - Date Completed = 18/5/22|
|26/05/22|Testing |Tester|Ollie|26/05/2022|Not Done - Date Completed = |
|27/05/22|Feedback and improvements| Everyone| Zach, Jono, Ricky, Ollie  and Arnav| 28/05/22| Not done - Date Completed=|
|29/05/22|Attempt Challenge| Software Engineers + Software Architect | Zach, Jono, Ricky| 02/06/22|Not Done - Date Completed = |
|03/06/22|Finalise| Everyone| Zach, Jono, Ricky, Ollie  and Arnav| 03/06/22|Not Done - Date Completed = |
|04/06/2022| Final agreement and Submission| Everyone|Zach, Jono, Ricky, Ollie  and Arnav| 04/06/22| Not Done - Date Completed = |





#### Other notes about the general design of the software

| AVCRobot | |
|------|------|
|Variables| Int x, int y, double angle, int part, Motor motor, Camera camera |
|Functions|	void core   void completion   void challenge   void canSeeLine   void reverseUntilSeeLine |

| Motor | |
|------|------|
| Variables	| Int speedright, int speedleft |
| Functions	| double calculateSpeedright()   double calculateSpeedleft()   void setSpeedright()   void setSpeedleft()   void foward()   void reverse() |

| Camera | |
|------|------|
| Variables	| Double kp, double error, int num_black, int num_red, int num_blue, int num_green |
| Functions	| bool noBlackpix()   double getLineErrorSignal()   double numBlackInImg()   double numRedInImg()   double numBlueInImg()   double numGreenInImg() |




