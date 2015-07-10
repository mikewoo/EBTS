#include "Process.h"

#include "PortConfig.h"
//#include "KeyBoard.h"
#include "System.h"
#include "Memory.h"
#include "Output.h"
#include "UI.h"


//控制状态		 
unsigned char  _Status=0;
//
unsigned char  Motor_Status_Action=0;
unsigned char  Motor_Status_Running=0;
unsigned long  Motor_Status_TickCountLast=0;


void Event_Keyboard(unsigned char pKey)
{
	if (pKey == 0xFF) return;
	
	Led_OnOff(2,1);	
	if((pKey & 0x01) != 0x00) 
		{ 	Mot_OnOff(1,1,0); AppStatus.Mot1_ToAutoInit = 0;//自动初始化结束
		}

	if((pKey & 0x02) != 0x00) 
		{	Mot_OnOff(1,1,1); AppStatus.Mot1_ToAutoInit = 0;//自动初始化结束
		}
	
	if((pKey & 0x04) != 0x00) Mot_OnOff(2,1,0);
	if((pKey & 0x08) != 0x00) Mot_OnOff(2,1,1);
	if((pKey & 0x10) != 0x00) Mot_OnOff(3,1,0);
	if((pKey & 0x20) != 0x00) Mot_OnOff(3,1,1);
	
}

void Event_Comm()
{

	if (AppStatus.Power_ToPreOff  )
	{
		AppStatus.Power_ToPreOff = 0;
		return;
	}

	if (AppStatus.Mot1_ToP  )
	{
		AppStatus.Mot1_ToP = 0;
		Mot_OnOff(1,1,0);
		AppStatus.Mot1_ToAutoInit = 0;//自动初始化结束	
	}
	
	if (AppStatus.Mot1_ToN  )
	{
		AppStatus.Mot1_ToN = 0;
		Mot_OnOff(1,1,1);
		AppStatus.Mot1_ToAutoInit = 0;//自动初始化结束	
	}

	if (AppStatus.Mot2_ToP  )
	{
		AppStatus.Mot2_ToP = 0;
		Mot_OnOff(2,1,0);
	}
	
	if (AppStatus.Mot2_ToN  )
	{
		AppStatus.Mot2_ToN = 0;
		Mot_OnOff(2,1,1);
	}
	if (AppStatus.Mot3_ToP  )
	{
		AppStatus.Mot3_ToP = 0;
		Mot_OnOff(3,1,0);
	}
	
	if (AppStatus.Mot3_ToN  )
	{
		AppStatus.Mot3_ToN = 0;
		Mot_OnOff(3,1,1);
	}

		
}

void Event_Auto()
{
	if (AppStatus.Mot1_ToAutoInit == 1) 	Mot_OnOff(1,1,0);;
}

//void ACT_ClearStatus()
//{
//	void Motor_Stop();
//	_Status = 0;
//	Count_Waiting = 0;
//	Motor_Stop();
//}

//void ClrCounter()
//{
//	Count_Back  = 0;
//}

//控制动作
//void Motor_BackUp();
//void Motor_BackDown();
//void Motor_LegBend();
//void Motor_LegFlat();

//
//void Action_BackUp()
//{
	//
	//Motor_BackUp();
//}


