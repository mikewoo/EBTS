#ifndef USYSTEMH
#define USYSTEMH

//#include "INTRINS.H"
#include "WOS_DEFINE.H"
#include "SYS_MCU.h"
#include "WOS_WTYPE.H"

extern bool _IsTimer10ms;
extern bool _IsTimer1ms;
extern bool _IsTimer1s;
extern long _Systemtick;

extern void SysInit(void);
extern void LedOnOff(unsigned char pBits); //bit1-4->Led1-4 1:On 0:Off

extern void WOS_SetDalayWatchDogProc(TFarProc pWatchDogProc);
extern void WOS_DelayN100us(Word N);
extern void WOS_DelayNms(Word N);


#endif

