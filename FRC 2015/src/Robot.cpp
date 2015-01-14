#include"WPILib.h"

class Robot:public IterativeRobot{
private:
	RobotDrive robot;
	Joystick stick;
	LiveWindow *lw;
public:
	Robot():
		robot(0,1),
		stick(1),
		lw(NULL)
	{
		robot.SetExpiration(0.1);
	}
	void RobotInit(){
		lw=LiveWindow::GetInstance();
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
	}
	void TeleopPeriodic(){
		robot.ArcadeDrive(stick);
	}
	void TestInit(){
	}
	void TestPeriodic(){
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
