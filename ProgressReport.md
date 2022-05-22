# ENGR101 - Project3 - AVC - Team 1 
## Progress Report 

#### Progress Roadmap
|start date	   |     task description	   |         responsible| team members	| end date	   |     outcome|Actual progress as per 22nd of May|
|------|------|-------|------|-----|----|----|
|9/5/22|Implement Code from lectures|Software Engineers + Software Architect | Zach, Jono and Ricky| 13/5/22| Date Completed = 13/5/22 | **Done as scheduled**  |
|13/5/22|Test code to find errors|Tester|Ollie|15/5/22|Date Completed = | Still not done|
|15/5/22|Finish Core | Software Engineers + Software Architect | Zach, Jono and Ricky|20/5/22| Date Completed = 16/5/22| **Done as scheduled**|
|20/5/22|Completion | Software Engineers + Software  Architect |  Zach, Jono, ricky| 26/05/22| Date Completed = 18/5/22| **Done as scheduled**|
|26/05/22|Testing |Tester|Ollie|26/05/2022| Date Completed = | Still not done|
|27/05/22|Feedback and improvements| Everyone| Zach, Jono, Ricky, Ollie  and Arnav| 28/05/22| Date Completed=| Still not done|
|29/05/22|Attempt Challenge| Software Engineers + Software Architect | Zach, Jono, Ricky| 02/06/22| Date Completed = | Still not done|
|03/06/22|Finalise| Everyone| Zach, Jono, Ricky, Ollie  and Arnav| 03/06/22| Date Completed = | Still not done|
|04/06/2022| Final agreement and Submission| Everyone|Zach, Jono, Ricky, Ollie  and Arnav| 04/06/22|  Date Completed = | Still not done|




#### Analysis

The coding of the project went according to plan. Software engineers and software architect did an amazing job and completed all the coding for the Core and completion of the project before due dates. On the other hand testing of the code didn't go as planned. 
The tester did not test the core code before the deadline even though the code was done ahead of schedule. This happened because software engineer forgot to update the tester about the status of project and send the code. The tester also didn't remember to check in with team, to send the code for testing. The project manager also didn't checked in the project status.
As a result, this highlights the lack of communication among team members regarding project status and what stage is everyone working on. There is not  proper communication between the team members because of the fact that tester and project manager are distance students. 

Few Bottlenecks and Solutions

1. For core, the software engineers and software architect had to calculate values of the robot’s trajectory and make sure that robot follows the correct path. There was a challenged faced in calculating the values required for error correction (Double kp). It was difficult to make an estimate of a number that had to be multiplied with the “error” variable.
For example:(dv = kp*error) → 5*100 =500 for dv then add vcr 10 is 510 for vl (vl = dv+vcr) and 500 for vr by 500 - 10 (vr = dv-vcr)
To resolve the issues, we have to do multiple tries and errors testing the code to find the optimal number which turns out the kp is
0.0025 a very small number. Multiply by 100 give dv = 0.25 (0.0025*100) then add/subtract vcr
(vl/vr = 0.25 +/- 10) gives us 10.25 or 9.75 for the left and right motor.

2. For completion, the main difficulty was programming the robot to turn in the “correct” direction towards the “blue” completion mark. When the robot reached the first cross intersection we made a code to turn left when the robot detected black pixels from the top, left and right side of the camera. This also meant the second cross intersection turned left as well
but there was a dead end as there no black track left. We tried to make a robot go reverse by negative set_motor(-100,-100) when top, left and right did not track any black. This didn’t work out. The robot kept turning left because top, left and right detected black pixels.
To solve this issue , we created a variable “check” = 0 as a global variable that adds 1 when detecting the 1st cross intersection then when the robot reaches the 2nd cross intersection and checks have 1, it goes straight. This however does not work because of the while loop, which loops the whole statement meaning that it reuses the “check” variable that creates it which is 0
in every loop. 
The final solution  turned out,creating a boolean in int main(), put in completion parameter and change void completion to bool completion. (image below)

![For completion](/a.png)




Team recommendation on how to advance the Project:

So far the coding side of the project is going up to the mark. We need to keep up the good work and try to finish code for challenge as early as possible so that it is not  messed up in the end under pressure. Even though the code has been tested by the software engineers and software architect, the tester also needs to perform the assigned tasks. Another aspect to improve is communication between team members regarding the project. 

