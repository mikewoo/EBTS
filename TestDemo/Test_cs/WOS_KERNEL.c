/* for 初始化CCA  */
//*************Module PreWord SYS_*********************************************

#include "SYS_MCU.h"                /* special function register declarations   */
//#include "INTRINS.H"
//#include "string.h"

#include "WOS_KERNEL.H"
#include "WOS_WTYPE.H"
#include "WOS_INTERRUPT.H"

#define _nop_() {}

/*系统数据定义开始*/
bool        To_FeedWatchDog = True;
INT32S  data __SysTickCounter     = 0;  //Every one/10 ms a Tick
bool         __SysTickCounter_PV   = False;

//Begin********Internal Variable 
/*看门狗控制位*/
bool       WatchDog = 1;

INT16S data  RandomSeed = 0;  //Every one ms a Tick
bool         ToStopBee = 1;
//End**********Internal Variable

/*

//******外部中断0******************
//void interruptExt0() interrupt 0
void interruptExt0()
{
    //EX0 = 0;
	InterruptExt0_Process();
    //EX0=1;
}
//******外部中断1******************
//void interruptExt1() interrupt 2
void interruptExt1()
{
	//EX1 = 0;
	InterruptExt1_Process();
	//EX1 = 1;
}

//******T1中断*******************
//void interruptT1()   interrupt 3  
void interruptT1() 
{
    //EX0 = 0;
	//InterruptT1_Process();
    //EX0=1;
}

//******串口中断1************************
//void interruptUart() interrupt 4
void interruptUart()
{
//	ES = 0;
	//InterruptUart_Process();
//	ES = 1;
}


//void interruptTimer0() interrupt 1
void interruptTimer0()
{
    static INT8U  data SysTickCounter_Byte = 0;  //ms Tick's Buffer
    //Timer:1s
    static INT8U  data Timer0Count1s = 0;
    //Timer:100ms
    static INT8U  data  Timer0Count100ms = 0;
    //Timer:10ms
    static INT8U  data  Timer0Count10ms = 0;
    //Timer:0.1ms
    //Timer:1ms
    static INT8U  data  Timer0Count1ms = 0;
    //BOOL        Timer0Count100us = 0;
//    ET0 = 0;

    //TL0 = 0x34;  //f8cc//460.8 0.25ms
    //TH0 = 0xFE;  
    //TL0 = 0x80;  //fe80//382  1/4800s
    //TH0 = 0xFe;  //ff40//192  1/9600s
    //TL0 = 0x65;  //f8cc//1843.2 1ms 22.1184Mhz
    //TH0 = 0xFD;  //ff48//184.32
    //TL0 = 0xCE;  //f8cc//1843.2 1ms 22.1184Mhz
    //TH0 = 0xF8;  //ff48//184.32
    //TL0 = 0xA4;  //f8cc//1843.2
    //TH0 = 0xFF;  //ffA4//92.16	0.05ms
    //TL0 = 0xD4;  //FBD4//100us 1ms 11.0592*12Mhz
   // TH0 = 0xFB;  //
    //TL0 = 0xA9;  //FBD4//100us 1ms 11.0592*12Mhz
    //TH0 = 0xF7;  //
		//InterruptTime0_50us_Process();

	//Timer0Count100us = ~Timer0Count100us;
	//if (Timer0Count100us) {
	RandomSeed++;
    //0.1ms Begin****************************************************************
		InterruptTime0_100us_Process();
	SysTickCounter_Byte++;
	if (__SysTickCounter_PV == False)
	{
    	__SysTickCounter += SysTickCounter_Byte;
		SysTickCounter_Byte = 0;
		if (__SysTickCounter<0) __SysTickCounter += 0x80000000;
	}
    //0.1ms End  ****************************************************************
    Timer0Count1ms++;
    if (Timer0Count1ms > 20-1) {	  //10-1
    Timer0Count1ms=0;
//	SysTickCounter_Byte++;
    //1ms Begin******************************************************************
		InterruptTime0_1ms_Process();
    //1ms End  ******************************************************************

    Timer0Count10ms++;
    if ( (Timer0Count10ms == 1) || (Timer0Count10ms == 6) ) {
    //5ms Begin*****************************************************************
		InterruptTime0_5ms_Process();
    //5ms End  *****************************************************************
    }
    if (Timer0Count10ms > 10-1) {
    Timer0Count10ms=0;
    //10ms Begin*****************************************************************
		InterruptTime0_10ms_Process();
    //10ms End  *****************************************************************

    Timer0Count100ms++;
    if ( (Timer0Count100ms == 1) || (Timer0Count100ms == 5) ) {
    if (To_FeedWatchDog == True)
    { 
        To_FeedWatchDog = False;
        WatchDog  = !WatchDog;
//        WDI = WatchDog;
    }
    //50ms Begin****************************************************************
		InterruptTime0_50ms_Process();
    //50ms End  ****************************************************************
    }
    if (Timer0Count100ms > 10-1) {
    Timer0Count100ms=0;
    //100ms Begin****************************************************************
		InterruptTime0_100ms_Process();
    //100ms End  ****************************************************************

    Timer0Count1s++;
    if (Timer0Count1s > 10-1) 
    {
    Timer0Count1s=0;
    //1s Begin****************************************************************
		InterruptTime0_1s_Process();
    //1s End  ****************************************************************
    }//1s
    }//100ms
    }//10ms
    }//1ms
    //}//0.1ms
    //for Uart Rx Bytes Interval ms Count 
    //    if (Uart_RxTimeCount<100) {Uart_RxTimeCount++;}

//    ET0=1;
}

*/
void WOS_Halt()
{
    //EA = 0;
    while(1); //HaltMPu
	//#pragma asm
	//  JMP $
	//#pragma endasm
}


void WOS_InitReg()
{
//测试程序专用
/*
	IE = 0;
	EA = 0;
    IP = 0;

    P0=0xFF;
    P1=0xFF;
    P2=0xFF;
    P3=0xFF;

    __SysTickCounter = 0;

    //Timer,Series Port Set=T0,T1
    TMOD=0x21;  //T0-16位 ,T1-8位重装	  //

    TH0=0xFF;
    TL0=0x0;

    TCON=0x00;
    //T2CON=0x00;

    IT0 = 1;
    IT1 = 1;
    IP  = 0x30;  //0010 0000b  IPT2 = 1  IPUART=1
    IE  = 0x82;  //1000 0010b  EA,ET0 =1
    //EnalbeInterrupt_T0();
    //EnalbeInterrupt_All();
 
    PCON=0x80;   //SMod=1

    //------------------------------------------------
    //Setup the serial port for 19200 baud at 11.0592MHz.
    //------------------------------------------------


    TR0 = 1; // Open Interrupt T0

    //EX0 = 1;
*/
}

/*
long WOS_GetSysTickCounter()
{
    register long aInt32;
	__SysTickCounter_PV = True;
	aInt32 = __SysTickCounter;
	__SysTickCounter_PV = False;
    return aInt32;
}

short WOS_GetSysTickCounter_Int16()
{
    register short aInt16;
	__SysTickCounter_PV = True;
	aInt16 = __SysTickCounter & 0x7FFF;
	__SysTickCounter_PV = False;
    return aInt16;
}

long WOS_GetPassedSysTicks(long pValue)
{
    register long aInt32;
	aInt32 = WOS_GetSysTickCounter();
	aInt32 -= pValue;
	if (aInt32<0) 
	{
		aInt32 += 0x80000000;
    }
	return 	aInt32;
}

INT16S WOS_GetPassedSysTicks_Int16(short pValue)
{
    register short	aInt16;
	aInt16 = WOS_GetSysTickCounter_Int16();
	aInt16 -= pValue;
	if (aInt16<0) 
	{
		aInt16 += 0x8000;
    }
	return 	aInt16;
}

//------Delay-------------------------------------------------------------------
TFarProc _WatchDogProcess=NULL;
void WOS_SetDalayWatchDogProc(TFarProc pWatchDogProc)
{
	_WatchDogProcess = pWatchDogProc;
}

void WOS_DelayN100us(INT16U N)
{
    register long aInt32;
	N = N+N;
	aInt32 = WOS_GetSysTickCounter();
	while (WOS_GetPassedSysTicks(aInt32) <N )
	{
		//**启动喂系统看门狗**
		//if (_WatchDogProcess!=NULL) _WatchDogProcess();
	};
}

void WOS_DelayNms(INT16U N)
{
    register long aInt32;
	aInt32 = WOS_GetSysTickCounter();
	while (WOS_GetPassedSysTicks(aInt32) <(N*10) )
	{
	 	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	 	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	 	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	 	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		//*启动喂系统看门狗**
		if (_WatchDogProcess!=NULL) _WatchDogProcess();
	};
}

*/
