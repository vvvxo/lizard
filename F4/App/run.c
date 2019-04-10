#include "run.h"

//There is s simple test.
//Code could be wrote better
//void RunTask(void){
//		StandByMotor(LS);
//		StandByMotor(LM);
//		StandByMotor(RS);
//		StandByMotor(RM);
//	
//		//left slave motor run 
//		SetSpeed(LS,100);
//		SetAngle(LS,50);
//		
//		//when the foot be lifted up a angle,break the loop,10 just a example,as a parameter should be adjust,
//		while(ReturnAngle(LS) >= 10)
//			;
//		
//		//left master run
//		SetSpeed(LM,100);
//		SetAngle(LM,50);	

//		//the data should be limit at a ..,break the loop
//		while(ReturnAngle(LM) >= 50 && ReturnAngle(LS) >= 50)
//			;
//		
//		SetSpeed(LS,100);
//		SetAngle(LS,-50);
//		while(ReturnAngle(LS) == 50)
//			;
//		
//	while(1){
//		StandByMotor(LS);
//		SetSpeed(LM,100);
//		SetAngle(LM,-50);
//		Delay(1);
//		SetSpeed(RS,100);
//		SetAngle(RS,50);
//		while(ReturnAngle(LS) >= 10)
//			;
//		
//		SetSpeed(RM,100);
//		SetAngle(RM,50);	
//		while(ReturnAngle(RM) >= 50 && ReturnAngle(RS) >= 50)
//			;
//		
//		SetSpeed(RS,100);
//		SetAngle(RS,-50);
//		while(ReturnAngle(RS) == 50)
//			;
//		
//		StandByMotor(RS);
//		SetSpeed(RM,100);
//		SetAngle(RM,-50);		
//		SetSpeed(LS,100);
//		SetAngle(LS,50);
//		while(ReturnAngle(LS) >= 10)
//			;
//		
//		SetSpeed(LM,100);
//		SetAngle(LM,50);	
//		while(ReturnAngle(LM) >= 50 && ReturnAngle(LS) >= 50)
//			;
//		
//		SetSpeed(LS,100);
//		SetAngle(LS,-50);
//		while(ReturnAngle(LS) == 50)
//			;
//	}
//}
