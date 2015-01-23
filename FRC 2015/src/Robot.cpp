#include"WPILib.h"

enum DriveMode{
	arcade,
	tank,
	arm
};

enum Controller{
	joystick,
	xbox
};

class Robot:public IterativeRobot{
private:
	RobotDrive robot;
	Joystick left,right;
	Gyro gyro;
	Solenoid solenoidA,solenoidB,solenoidC;
	DriveMode driveMode=tank;
	Controller controller=joystick;
public:
	Robot():
		robot(0,1),
		left(1),
		right(2),
		gyro(1),
		solenoidA(1),
		solenoidB(2),
		solenoidC(3)
	{
		robot.SetExpiration(0.1f);
	}
	void RobotInit(){
	}
	void DisabledInit(){
		robot.SetSafetyEnabled(true);
	}
	void DisabledPeriodic(){
	}
	void AutonomousInit(){
		robot.SetSafetyEnabled(false);
	}
	void AutonomousPeriodic(){
	}
	void TeleopInit(){
		robot.SetSafetyEnabled(true);
		if(left.GetAxisCount()==2){
			controller=joystick;
		}
		else if(left.GetAxisCount()==6){
			controller=xbox;
		}
	}
	void TeleopPeriodic(){
		switch(driveMode){
		case arcade:
			robot.ArcadeDrive(left);
			break;
		case tank:
			switch(controller){
			case joystick:
				robot.TankDrive(left,right);
				break;
			case xbox:
				robot.TankDrive(left.GetRawAxis(1),left.GetRawAxis(3));
				break;
			}
			break;
		case arm:
			break;
		}
	}
	void TestInit(){
		robot.SetSafetyEnabled(false);
		robot.Drive(1.0f,1.0f);
	}
	void TestPeriodic(){
	}
};
START_ROBOT_CLASS(Robot);
