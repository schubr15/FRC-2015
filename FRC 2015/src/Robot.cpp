#include"WPILib.h"

class Robot:public IterativeRobot{
private:
	enum class DriveMode{
		Arcade,
		Tank,
		Arm
	};
	enum class Controller{
		Joystick,
		XBox
	};
	RobotDrive robot;
	Joystick left,right;
	Gyro gyro;
	Solenoid solenoidA,solenoidB,solenoidC;
	DriveMode driveMode=DriveMode::Tank;
	Controller controller=Controller::Joystick;
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
			controller=Controller::Joystick;
		}
		else if(left.GetAxisCount()==6){
			controller=Controller::XBox;
		}
	}
	void TeleopPeriodic(){
		switch(driveMode){
		case DriveMode::Arcade:
			robot.ArcadeDrive(left);
			break;
		case DriveMode::Tank:
			switch(controller){
			case Controller::Joystick:
				robot.TankDrive(left,right);
				break;
			case Controller::XBox:
				robot.TankDrive(left.GetRawAxis(1),left.GetRawAxis(3));
				break;
			}
			break;
		case DriveMode::Arm:
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
