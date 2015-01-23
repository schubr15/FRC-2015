#include"WPILib.h"

enum DriveMode{
	arcade,
	tank,
	arm
};

class Robot:public IterativeRobot{
private:
	RobotDrive robot;
	Joystick left,right;
	Gyro gyro;
	Solenoid solenoidA,solenoidB,solenoidC;
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
	}
	void DisabledPeriodic(){
	}
	void AutonomousInit(){
	}
	void AutonomousPeriodic(){
	}
	void TeleopInit(){
		robot.SetSafetyEnabled(true);
	}
	void TeleopPeriodic(){
		switch(DriveMode){
		case arcade:
			robot.ArcadeDrive(left);
			break;
		case tank:
			robot.TankDrive(left,right);
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
