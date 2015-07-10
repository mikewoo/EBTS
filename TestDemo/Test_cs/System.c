//#include <intrins.h>

#include "WOS_DEFINE.H"
#include "WOS_KERNEL.H"
#include "SYS_MCU.h"
//#include "KeyBoard.h"
#include "PortConfig.h"
//#include "Action.h"


void LedOnOff(unsigned char pBits); //bit1-4->Led1-4 1:On 0:Off

void SysInit(void)
{
    WOS_InitReg();
    //Timer,Series Port Set=T0,T1
 //   TMOD=0x11;  //T0,T1

   // TH0=0xFF;
    //TL0=0x0;

    //TCON=0x00;
    //T2CON=0x00;

    //IT0 = 1;
    //IT1 = 1;
    //IP  = 0x30;  //0010 0000b  IPT2 = 1  IPUART=1
    //IE  = 0x82;  //1000 0010b  EA,ET0 =1
    //EnalbeInterrupt_T0();
    //EnalbeInterrupt_All();
 
    //PCON=0x80;   //SMod=1	  ±¶Æµ

    /*------------------------------------------------
    Setup the serial port for 19200 baud at 11.0592MHz.
    ------------------------------------------------*/

    //TR0 = 1; // Open Interrupt T0

//	MPU_T0_SetTo_1Clk();  //T0 x12 Clk

    //for Input-Counter1
//	EX0 = 1;
//	EX1 = 1;
}
