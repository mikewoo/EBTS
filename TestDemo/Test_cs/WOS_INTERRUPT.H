/******************************************************************************/
/*文件:SYSTEM.H
/*----------------------------------------------------------------------------*/
/*接口:
/*
/******************************************************************************/
#ifndef _UWOSINTERRUPTH_
#define _UWOS_INTERRUPTH_

#include "WOS_DEFINE.H"
#include "WOS_WTYPE.H"

#define IntIndex_Ext0 0x00
#define IntIndex_Ext1 0x20

#define IntIndex_UartRxd 0x51
#define IntIndex_UartTxd 0x52

#define IntIndex_T01s 0x10
#define IntIndex_T01ms 0x11
#define IntIndex_T05ms 0x12
#define IntIndex_T10ms 0x13

extern bool _IsTimer10ms;
extern bool _IsTimer1ms;
extern bool _IsTimer1s;
extern long _Systemtick;

extern void EnalbeInterrupt_All(void);
extern void DisalbeInterrupt_All(void);
extern void EnalbeInterrupt_Uart(void);
extern void DisalbeInterrupt_Uart(void);

extern void InterruptExt0_Process(void);
extern void InterruptExt1_Process(void);
extern void InterruptT1_Process(void);
extern void InterruptUart_Process(void);

extern void InterruptTime0_100us_Process();
extern void InterruptTime0_1ms_Process();
extern void InterruptTime0_5ms_Process();
extern void InterruptTime0_10ms_Process();
extern void InterruptTime0_50ms_Process();
extern void InterruptTime0_100ms_Process();
extern void InterruptTime0_1s_Process();

//extern bool Sys_Event();				/*系统事件处理*/

extern void WOS_Set_InterruptProc(unsigned char pIntIdx,TInterruptProc pIntProc);

#endif

//Begin********External Variable 
//End**********External Variable

//Begin********Internal Variable 
//End**********Internal Variable

