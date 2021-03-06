#pragma config(Sensor, in3,    pot,            sensorPotentiometer)
#pragma config(Sensor, in4,    lineFollowerCENTER, sensorLineFollower)
#pragma config(Sensor, in5,    lineFollowerRIGHT, sensorLineFollower)
#pragma config(Sensor, in6,    lineFollowerLEFT, sensorLineFollower)
#pragma config(Sensor, dgtl1,  touch,          sensorTouch)
#pragma config(Sensor, dgtl4,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  sonar,          sensorSONAR_cm)
#pragma config(Motor,  port2,           clawMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           armMotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           leftMotor,     tmotorServoStandard, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                             	    - Triple Sensor Line Tracking -                                   *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program uses 3 VEX Line Follower Sensors to track a black line on a light(er) surface.       *|
|*  There is a two second pause at the beginning of the program.                                      *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  Lighting conditions, line darkness, and surface lightness change from place to place,       *|
|*        so the value of 'threshold' may need to be changed to better suit your environment.         *|
|*		3)  Follows a black line until sonar detects something and picks up a ball and drives back and  *|
|*				drops it in  a basket                      																									*|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor  - Port 2     rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor  - Port 3     leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Analog - Port 4     lineFollowerCENTER  VEX Light Sensor      Front-center, facing down         *|
|*    Analog - Port 5     lineFollowerRIGHT   VEX Light Sensor      Front-right, facing down          *|
|*    Analog - Port 6     lineFollowerLEFT    VEX Light Sensor      Front-left, facing down           *|
|*    Digt   - Port 1     touch               VEX Touch             Emergency button                  *|
\*-----------------------------------------------------------------------------------------------4246-*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
const float Dd = 2.559223300970874;

void lineFollowing(int dist){

	int threshold = 2505;

while(true)
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+
    displayLCDCenteredString(0, "LEFT  CNTR  RGHT");        //  Display   |
    displayLCDPos(1,0);                                     //  Sensor    |
    displayNextLCDNumber(SensorValue(lineFollowerLEFT));    //  Readings  |
    displayLCDPos(1,6);                                     //  to LCD.   |
    displayNextLCDNumber(SensorValue(lineFollowerCENTER));  //            |
    displayLCDPos(1,12);                                    //  L  C  R   |
    displayNextLCDNumber(SensorValue(lineFollowerRIGHT));   //  x  x  x   |
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+

    // RIGHT sensor sees dark:
    if(SensorValue(lineFollowerRIGHT) > threshold)
    {
      // counter-steer right:
      motor[leftMotor]  = 50;
      motor[rightMotor] = 0;
    }
    // CENTER sensor sees dark:
    // LEFT sensor sees dark:
    if(SensorValue(lineFollowerLEFT) > threshold)
    {
      // counter-steer left:
      motor[leftMotor]  = 0;
      motor[rightMotor] = 50;
    }
    if(SensorValue(lineFollowerCENTER) > threshold)
    {
      // go straight
      motor[leftMotor]  = 50;
      motor[rightMotor] = 50;
    }
    if(SensorValue(sonar) < dist)
  	{
  		break;
  	}
  }

}

void lowerArm(){

	while(SensorValue(pot) < 1800){
			motor[armMotor] = 63;


	}
	motor[armMotor] = 0;

}

void clawClose(){

	motor[clawMotor] = -127;
	wait1Msec(150);
	motor[clawMotor] = 0;

}

void clawOpen(){

		motor[clawMotor] = 127;
		wait1Msec(500);
		motor[clawMotor] = 0;

}


void liftArm(){
	while(SensorValue(pot) > 1722){
			motor[armMotor] = -63;


	}
	motor[armMotor] = 0;


}
void resetEncoders(){
		SensorValue[rightEncoder] = 0;
	  SensorValue[leftEncoder]  = 0;
}
void Turn(bool direct, float rot)
{   /* consistancy and accuracy. */
	resetEncoders();
	rot = rot * Dd;
  // While the encoders have not yet met their goal: (left is compared negativly since it will in reverse)
  //while(SensorValue[rightEncoder] < (r * rotations) && SensorValue[leftEncoder] > (-1 * r * rotations))
  if (direct == false){
	while(SensorValue[rightEncoder] < rot || SensorValue[leftEncoder] > -rot){
    motor[rightMotor] = 63;         // Run the right motor forward at half speed
    motor[leftMotor]  = -63;
  }
}
	else{
		while(SensorValue[leftEncoder] < rot || SensorValue[rightEncoder] > -rot){
		motor[rightMotor] = -63;         // Run the right motor forward at half speed
    motor[leftMotor]  = 63;
  }
  }
    // Run the left motor backward at half speed
           /* can act independantly as a "chunk" of code, without any loose ends. */
}

void motorStop()
{
	motor[rightMotor] = 0;		  // Motor on port2 is run at full (127) power forward
	motor[leftMotor]  = 0;

	wait1Msec(1000);

}

task Stop(){
	while(true){
	if (SensorValue[touch] == 1 || vexRT[Btn8D] == 1){
		StopAllTasks();
	}
}
}
task main()
{
	StartTask(Stop);
	wait1Msec(2000);
	lineFollowing(22);
  motorStop();
  wait1Msec(1000);
  lowerArm();
  wait1Msec(1000);
  clawClose();
  wait1Msec(1000);
  liftArm();
  Turn(true, 190);
  motorStop();
  wait1Msec(1000);
  lineFollowing(10);
  motorStop();
  wait1Msec(1000);
  clawOpen();




}
