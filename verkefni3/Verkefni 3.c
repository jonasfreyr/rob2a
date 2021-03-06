#pragma config(Sensor, dgtl1,  touchSensor,    sensorTouch)
#pragma config(Motor,  port2,           clawMotor,     tmotorVex269, openLoop)
#pragma config(Motor,  port3,           armMotor,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           rightMotor,    tmotorVex393, openLoop)
#pragma config(Motor,  port6,           leftMotor,     tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                - Clawbot Single Joystick Control -                                 *|
|*                                      ROBOTC on VEX 2.0 Cortex                                      *|
|*                                                                                                    *|
|*  This program uses a single joystick, either right or left to drive the robot. Use notes below     *|
|*  to reconfigure which joystick is used. The joystick buttons are used to raise and lower the arm.	*|
|*  The joystick buttons are used to open and close the claw.	Also added the emergency button					*|
|*																																																		*|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)	Ch1 is the X axis and Ch2 is the Y axis for the RIGHT joystick.                             *|
|*    2)	Ch3 is the Y axis and Ch4 is the X axis for the LEFT joystick.                              *|
|*		3)	Button 5U and 5L are on the front left side of the joystick.																*|
|*		3)	Button 6U and 6L are on the front right side of the joystick.                               *|
|*    4)  Button 8D is for the emergency button                                                       *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]        [Name]          [Type]                               [Description]						*|
|*		Sensor - Dgt 1	 touchSensor   VEX Button														 Emergency button           *|
|*    Motor - Port 2   rightMotor    VEX 393 Motor                         Right drive motor          *|
|*    Motor - Port 6   clawMotor     VEX 393 Motor w/ Motor Controler 29   Claw motor                 *|
|*    Motor - Port 7   armMotor      VEX 393 Motor w/ Motor Controler 29   Arm motor                  *|
|*    Motor - Port 10  leftMotor     VEX 393 Motor                         Left drive motor           *|
\*----------------------------------------------------------------------------------------------------*/

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
bool button = false;
task main ()
{

	while(button == false)
	{
		motor[leftMotor]  = vexRT[Ch3];
    motor[rightMotor] = vexRT[Ch2];


		if(vexRT[Btn5U] == 1)
		{
			motor[armMotor] = 63;
		}
		else if(vexRT[Btn5D] == 1)
		{
			motor[armMotor] = -63;
		}
		else
		{
			motor[armMotor] = 0;
		}


		if(vexRT[Btn6U] == 1)
		{
			motor[clawMotor] = 127;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[clawMotor] = -127;
		}
		else
		{
			motor[clawMotor] = 0;
		}

		if(vexRT[Btn8D] == 1 || SensorValue(touchSensor) == 1)
		{
			button = true;
		}
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
