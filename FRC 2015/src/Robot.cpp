#include<cinttypes>
#include<vector>
#include"WPILib.h"

class Robot:public IterativeRobot{
private:
	class Controller:public Joystick{
	private:
		enum class Type:uint8_t{
			Joystick,
			XBox
		}type;
	};
	enum class DriveMode:uint8_t{
		Arcade,
		Tank,
		Arm
	};
	RobotDrive robot;
	std::vector<Controller> controller={1};
	Gyro gyro;
	Solenoid solenoidA,solenoidB,solenoidC;
	DriveMode driveMode;
public:
	Robot():
		robot(0,1),
		gyro(1),
		solenoidA(1),
		solenoidB(2),
		solenoidC(3),
		driveMode(DriveMode::Arcade)
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
		for(uint8_t i;i<controller.size();++i){
			if(controller[i].GetAxisCount()==2){
				controller[i].type=Controller::Type::Joystick;
			}
			else if(controller[i].GetAxisCount()==6){
				controller[i].type=Controller::Type::XBox;
			}
		}
	}
	void TeleopPeriodic(){
		switch(driveMode){
		case DriveMode::Arcade:
			robot.ArcadeDrive(controller[1]);
			break;
		case DriveMode::Tank:
			switch(controller[1].type){
			case Controller::Type::Joystick:
				robot.TankDrive(controller[1],controller[2]);
				break;
			case Controller::Type::XBox:
				robot.TankDrive(controller[1].GetRawAxis(1),controller[1].GetRawAxis(3));
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
