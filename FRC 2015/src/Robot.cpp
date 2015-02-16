#include"WPILib.h"

class Robot:public IterativeRobot{
private:
	class DriveController:public Joystick{
	public:
		enum class Type:uint8_t{
			Joystick,
			GamePad
		}type;
	};
	enum class DriveMode:uint8_t{
		Arcade,
		Tank
	}driveMode=DriveMode::Tank;
	RobotDrive robot;
	DriverStation * driverStation;
	std::vector<DriveController> controller;
	Gyro gyro;
	Compressor compressor();
	Solenoid yAxis,zAxis;
	DoubleSolenoid xAxis;
public:
	Robot():
		robot(0,1),
		driverStation(),
		gyro(1),
		yAxis(1),
		zAxis(2),
		xAxis(3,4)
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
		for(uint8_t i;i<DriverStation::kJoystickPorts-1;++i){
			if(driverStation->GetStickAxisCount(i)){
				if(controller[i].GetAxisCount()==2){
					controller[i].type=DriveController::Type::Joystick;
				}
				else{
					controller[i].type=DriveController::Type::GamePad;
				}
			}
		}
	}
	void TeleopPeriodic(){
		switch(driveMode){
		case DriveMode::Arcade:
			switch(controller[1].type){
			case DriveController::Type::Joystick:
				robot.ArcadeDrive(controller[1]);
				break;
			case DriveController::Type::GamePad:
				robot.ArcadeDrive(controller[1]);
				if(controller[1].GetRawAxis(3)<0.5f){
					yAxis.Set(true);
					zAxis.Set(true);
				}
				else{
					yAxis.Set(false);
					zAxis.Set(false);
				}
				if(controller[1].GetRawAxis(2)<0.5f){
					xAxis.Set(DoubleSolenoid::kReverse);
				}
				else if(controller[1].GetRawAxis(2)>0.5f){
					xAxis.Set(DoubleSolenoid::kForward);
				}
				else{
					xAxis.Set(DoubleSolenoid::kOff);
				}
				if(controller[1].GetRawButton(10)){
					driveMode=DriveMode::Tank;
				}
				break;
			}
			break;
		case DriveMode::Tank:
			switch(controller[1].type){
			case DriveController::Type::Joystick:
				robot.TankDrive(controller[1],controller[2]);
				break;
			case DriveController::Type::GamePad:
				robot.TankDrive(controller[1].GetRawAxis(1),controller[1].GetRawAxis(3));
				if(controller[1].GetRawButton(7)&&controller[1].GetRawButton(8)){
					yAxis.Set(true);
					zAxis.Set(true);
				}
				else{
					yAxis.Set(false);
					zAxis.Set(false);
				}
				if(controller[1].GetRawButton(5)){
					xAxis.Set(DoubleSolenoid::kForward);
				}
				else if(controller[1].GetRawButton(6)){
					xAxis.Set(DoubleSolenoid::kReverse);
				}
				else{
					xAxis.Set(DoubleSolenoid::kOff);
				}
				if(controller[1].GetRawButton(9)){
					driveMode=DriveMode::Arcade;
				}
				break;
			}
			break;
		}
	}
	void TestInit(){
		robot.SetSafetyEnabled(false);
		robot.TankDrive(0.2f,0.2f);
	}
	void TestPeriodic(){
	}
};
START_ROBOT_CLASS(Robot);