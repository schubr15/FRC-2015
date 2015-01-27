#include"WPILib.h"

class Controller:public Joystick{
private:
	enum class Type:uint8_t{
		Joystick,
		GamePad
	}type;
};

enum class DriveMode:uint8_t{
	Arcade,
	Tank,
	Arm
};

class Robot:public IterativeRobot{
private:
	RobotDrive robot;
	Controller controller;
	Gyro gyro;
	Solenoid solenoidA;
	DoubleSolenoid solenoidB,solenoidC;
	DriveMode driveMode;
public:
	Robot():
		robot(0,1),
		controller(1),
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
		if(controller.GetAxisCount()==2){
			controller.type=Controller::Type::Joystick;
		}
		else if(controller.GetAxisCount()==6){
			controller.type=Controller::Type::GamePad;
		}
	}
	void TeleopPeriodic(){
		switch(driveMode){
		case DriveMode::Arcade:
			robot.ArcadeDrive(controller);
			break;
		case DriveMode::Tank:
			switch(controller.type){
			case Controller::Type::Joystick:
				robot.TankDrive(controller,controller);
				break;
			case Controller::Type::GamePad:
				robot.TankDrive(controller.GetRawAxis(1),controller.GetRawAxis(3));
			}
			break;
		case DriveMode::Arm:
			if(controller.GetRawButton(0)){
				solenoidA.Set(true);
			}
			else{
				solenoidA.Set(false);
			}
			break;
		}
	}
	void TestInit(){
		robot.SetSafetyEnabled(false);
		robot.TankDrive(1.0f,1.0f);
	}
	void TestPeriodic(){
	}
};
START_ROBOT_CLASS(Robot);