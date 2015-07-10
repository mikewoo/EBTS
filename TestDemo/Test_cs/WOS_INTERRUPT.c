/* for 系统过程  */
//*************Module PreWord SYS_*********************************************

#include "SYS_MCU.h"                /* special function register declarations   */
//#include <ABSACC.H>
#include "string.h"

#include "WOS_INTERRUPT.H"

#include "WOS_KERNEL.H"

#include "WOS_DEFINE.H"
//#include "Function.h"

//#include "Display.h"

//#include "SysDef_Port.h"
//#include "Uart_KeyLcd.h"
//#include "KeyBoard.h"
//#include "Sound.h"
//#include "Infrared.h"
#include "Input.h"

bool _IsTimer10ms = FALSE;
bool _IsTimer1ms = FALSE;
bool _IsTimer1s = FALSE;

 TInterruptProc INTERRUPT_UARTRxd=NULL;
 TInterruptProc INTERRUPT_UARTTxd=NULL;

code TInterruptProc INTERRUPT_EXT0=NULL; //Input.h
code TInterruptProc INTERRUPT_EXT1=NULL; //Input.h
code TInterruptProc INTERRUPT_T1  =NULL; //ISR_Infrared_TimerEtu;		//Infrared.h  

code TInterruptProc INTERRUPT_T01s =NULL;
code TInterruptProc INTERRUPT_T01ms=NULL;
code TInterruptProc INTERRUPT_T05ms=NULL;
code TInterruptProc INTERRUPT_T10ms=NULL;

code TInterruptProc INTERRUPT_Bee = NULL;//SND_ISR_Bee; //"Sound.h"

/*
void EnalbeInterrupt_All()
{
//    EA=1;
}
void DisalbeInterrupt_All()
{
//    EA=0;
}

void EnalbeInterrupt_Uart()
{
//    ES=1;
}
void DisalbeInterrupt_Uart()
{
//    ES=0;
}

void EnalbeInterrupt_T0()
{
//    ET0=1;
}
void DisalbeInterrupt_T0()
{
//    ET0=0;
}

void InterruptExt0_Process()
{
    if (INTERRUPT_EXT0 != NULL) 
	{
//		INTERRUPT_EXT0();
	}
	IN_Counter0();
    //KBD_SetToGetKey();
    //EnableBee();
    //DelayNms(20);
    //DisableBee();
}

void InterruptExt1_Process()
{
    if (INTERRUPT_EXT1 != NULL) 
	{
//		INTERRUPT_EXT1();
	}
	IN_Counter1();

	//RFC_IntReceiveRounting();

	//KBD_SetToGetKey();
	//EnableBee();
	//DelayNms(20);
	//DisableBee();

}

void InterruptT1_Process()
{
    if (INTERRUPT_T1 != NULL) 
	{
		INTERRUPT_T1();
	}

	//RFC_IntReceiveRounting();

	//KBD_SetToGetKey();
	//EnableBee();
	//DelayNms(20);
	//DisableBee();

}

void InterruptUart_Process()
{
//	if (RI==1)
	{
	    if (INTERRUPT_UARTRxd != NULL)
		{
		    INTERRUPT_UARTRxd();
//		    RI = 0;
		}
	}
//	else
//	if (TI==1)
	{
	    if (INTERRUPT_UARTTxd != NULL) 
		{
//		    INTERRUPT_UARTTxd();
//	        TI=0;
		}
	}   
}


//void InterruptTime0_50us_Process()
//{
//	if (ILD_ToSend)
//	{
//		RFC_IntTimer_50us();       
//	}
//}

void InterruptTime0_100us_Process()
{
    if (INTERRUPT_Bee != NULL) 
	{
	    INTERRUPT_Bee();
	}
}

void InterruptTime0_1ms_Process()
{
	//RFC_IntTimer_Ms();  专用IC卡
//    UartReceive_OverTimeSet(); //串口超时设置,防止错包
    if (INTERRUPT_T01ms != NULL) 
	{
	    INTERRUPT_T01ms();
	}
	_IsTimer1ms = 1;
}

void InterruptTime0_5ms_Process()
{
    if (INTERRUPT_T05ms != NULL) 
	{
	    INTERRUPT_T05ms();
	}
}

void InterruptTime0_10ms_Process()
{
    if (INTERRUPT_T10ms != NULL) 
	{
	    INTERRUPT_T10ms();
	}
}

void InterruptTime0_50ms_Process()
{
}

void InterruptTime0_100ms_Process()
{
	//KBD_SetToGetKey();

//	if (PRG_ShowData_TimeCount_100ms > 0)  PRG_ShowData_TimeCount_100ms--;
}

data Byte InterruptTime0_1s_Count5s= 0;
void InterruptTime0_1s_Process()
{

	InterruptTime0_1s_Count5s += 1;
	InterruptTime0_1s_Count5s %= 5;
	//5秒计数
	if ( InterruptTime0_1s_Count5s == 0 )
	{
//*************5SUserProcess Begin**********************************************************************
//*************5SUserProcess End**********************************************************************
	}
	//1s定时器
    if (INTERRUPT_T01s != NULL) 
	{
	    INTERRUPT_T01s();
	}
	_IsTimer1s = 1;
}

void WOS_Set_InterruptProc(unsigned char pIntIdx,TInterruptProc pIntProc)
{
    switch(pIntIdx)
	{
	     case IntIndex_UartRxd:
		     INTERRUPT_UARTRxd = pIntProc;
		     break;
		 case IntIndex_UartTxd:
		     INTERRUPT_UARTTxd = pIntProc;
			 break;
	     case IntIndex_Ext0:
		     //INTERRUPT_EXT0 = pIntProc;
		     break;
		 case IntIndex_Ext1:
		     //INTERRUPT_EXT1 = pIntProc;
			 break;
		 case IntIndex_T01s:
		     //INTERRUPT_T01s = pIntProc;
			 break;
		 case IntIndex_T01ms:
		     //INTERRUPT_T01ms = pIntProc;
			 break;
		 case IntIndex_T05ms:
		     //INTERRUPT_T05ms = pIntProc;
			 break;
		 case IntIndex_T10ms:
		     //INTERRUPT_T10ms = pIntProc;
			 break;
	}
}
*/
//-----------------------------------------------------------------------------

