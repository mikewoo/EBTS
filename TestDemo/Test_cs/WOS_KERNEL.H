/******************************************************************************/
/*接口说明:
/*----------------------------------------------------------------------------*/
/*MacroDefs:
/*	SysDef_WatchDogFeed()					/*宏:看门狗复位*/
/*Functions:
/*	void Sys_WatchDogReset();				/*:看门狗复位*/
/*	void Sys_To_FeedWatchDog();				/*启动看门狗喂狗*/
/*
/*	void Sys_Halt();						/*系统停止，等待硬件复位*/
/*	void Sys_InitReg();						/*系统寄存器初始化*/
/*	long Sys_GetSysTickCounter();		          	/*系统读取系统总计数器*/
/*	long Sys_GetPassedSysTicks(long pValue);                /*系统计算系统经过时间*/
/*	void Sys_DelayNms(Word N);				/*系统N毫秒延时(0..30000)*/
/******************************************************************************/
#ifndef _UWOSKERNELH_
#define _UWOSKERNELH_

#include "WOS_WTYPE.H"

extern void WOS_Halt();
extern void WOS_InitReg();

extern long  WOS_GetSysTickCounter();
extern short WOS_GetSysTickCounter_Int16();
extern long  WOS_GetPassedSysTicks(long pValue);
extern short WOS_GetPassedSysTicks_Int16(short pValue);

extern void WOS_SetDalayWatchDogProc(TFarProc pWatchDogProc);
extern void WOS_DelayN100us(Word N);
extern void WOS_DelayNms(Word N);

#endif

//Begin********External Variable 
//End**********External Variable

//Begin********Internal Variable 
//End**********Internal Variable

