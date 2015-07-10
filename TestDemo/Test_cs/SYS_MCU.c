#include "SYS_MCU.h"
//#include "INTRINS.H"
//#include "WOS_Define.H"
#include "WOS_WTYPE.H"


#include <stdio.h>  

//#include <iostream>  
#include <fcntl.h> 
#include <sys/types.h>  
#include <sys/stat.h> 
#include <unistd.h>  
//using namespace std;  



typedef
  union {
    unsigned char  AsBytes[2];
    unsigned char  AsBool;
    unsigned char  AsByte;
             char  AsChar;
    unsigned short AsWord;
             short AsShort;
	struct {
      byte ByteHi;
      byte ByteLo;
    }AsByteHL;
  } TAddress;

/*
//------PORT--------------------------------------------------------------------
void PortMod(unsigned char pPort,unsigned char pPortBit,unsigned char pMod)
{
	unsigned char aSetBit;

    if (pMod % 2 == 0)
	{
	     aSetBit = ~ LeftShiftBitTable[pPortBit];
		 switch(pPort) 
		 {
		     case 0: P0M0 &= aSetBit; break;
		     case 1: P1M0 &= aSetBit; break;
		     case 2: P2M0 &= aSetBit; break;
		     case 3: P3M0 &= aSetBit; break;
		     case 4: P4M0 &= aSetBit; break;
		     case 5: P5M0 &= aSetBit; break;
		 }

	}else
	{
	     aSetBit = LeftShiftBitTable[pPortBit];
		 switch(pPort) 
		 {
		     case 0: P0M0 |= aSetBit; break;
		     case 1: P1M0 |= aSetBit; break;
		     case 2: P2M0 |= aSetBit; break;
		     case 3: P3M0 |= aSetBit; break;
		     case 4: P4M0 |= aSetBit; break;
		     case 5: P5M0 |= aSetBit; break;
		 }
	} 

    if (pMod / 2 == 0)
	{
	     aSetBit = ~ LeftShiftBitTable[pPortBit];
		 switch(pPort) 
		 {
		     case 0: P0M1 &= aSetBit; break;
		     case 1: P1M1 &= aSetBit; break;
		     case 2: P2M1 &= aSetBit; break;
		     case 3: P3M1 &= aSetBit; break;
		     case 4: P4M1 &= aSetBit; break;
		     case 5: P5M1 &= aSetBit; break;
		 }

	}else
	{
	     aSetBit = LeftShiftBitTable[pPortBit];
		 switch(pPort) 
		 {
		     case 0: P0M1 |= aSetBit; break;
		     case 1: P1M1 |= aSetBit; break;
		     case 2: P2M1 |= aSetBit; break;
		     case 3: P3M1 |= aSetBit; break;
		     case 4: P4M1 |= aSetBit; break;
		     case 5: P5M1 |= aSetBit; break;
		 }

	} 

}

//------Uart--------------------------------------------------------------------
void UART_Baud_Generator_12Clk(void)
{
    AUXR &= 0xFB;	//BRTx12/S2Tx12 = 0
}
void UART_Baud_Generator_1Clk(void)
{
    AUXR |= 0x04;   //BRTx12/S2Tx12 = 1
}
void UART_Baud_Generator_Start(void)
{
    AUXR |= 0x10;	//BRTR = 1
}
void UART_Baud_Generator_Stop(void)
{
    AUXR &= 0xEF;	//BRTR = 0
}

//------Uart1-------------------------------------------------------------------
void UART1_CLK_SetToSpecial(void)
{
    AUXR |= 0x01;	  //S1BRS = 1
}
void UART1_CLK_SetToT1(void)
{
    AUXR &= 0xFE;	  //S1BRS = 0
}

void UART1_Baud_SMODDouble(void)
{
    PCON |= 0x80;
}

void UART1_Baud_SMODNormal(void)
{
    PCON &= 0x7F;
}

void UART1_Init(unsigned char pByteSize,unsigned long pBaud)
{
	//IE &= 0x0EF;
	//IP &= 0x0EF;
	//T2CON &= 0xCF;
	TMOD &= 0x0F;  //使用T1时钟
	TMOD |= 0x20;
	
	if (pByteSize==9)
	{
	    SCON=0xD0;  //0xD0-9位;0x50-8位
	}
	else
	{
	    SCON=0x50;  //0xD0-9位;0x50-8位
	}

	switch (pBaud)
	{
		case  1200:{	TH1=0x0ED;UART1_Baud_SMODNormal(); };break;
		case  2400:{	TH1=0x0F4;UART1_Baud_SMODNormal(); };break;
		case  4800:{	TH1=0x0FA;UART1_Baud_SMODNormal(); };break;
		case  9600:{	TH1=0x0FD;UART1_Baud_SMODNormal(); };break;
		case 14400:{	TH1=0x0FE;UART1_Baud_SMODNormal(); };break;
		case 19200:{	TH1=0x0FD;UART1_Baud_SMODDouble(); };break;
		case 28800:{	TH1=0x0FE;UART1_Baud_SMODDouble(); };break;
		//case 38400:{	TH1=0x0FD;UART1_Baud_SMODDouble(); };break;
		case 57600:{	TH1=0x0FF;UART1_Baud_SMODDouble(); };break;
	}
	TL1 = TH1;
    
	TR1 = 1;
}

void UART1_SendByte(unsigned char pByte)
{
	TI = 0;
	SBUF = pByte;
	while(TI==0);
	TI=0;
}

char UART1_ReadByte(unsigned char *pByte)
{
	if (RI)
	{
	    *pByte = SBUF;
    	RI=0;
		return 0;
	}
	return 1;
}

//------Uart2-------------------------------------------------------------------
//串口中断1
TInterruptProc Interrupt_UART2Rxd=NULL;
TInterruptProc Interrupt_UART2Txd=NULL;

void EnalbeInterrupt_Uart2()
{
    //ES2=1;
	IE2 |= 0x01;
}
void DisalbeInterrupt_Uart2()
{
    //ES2=0;
	IE2 &= 0xFE;
}

void UART2_Interrupt_Process()
{
	//if (RI2==1)
	if ((S2CON & 0x01) == 0x01)
	{
	    if (Interrupt_UART2Rxd != NULL)
		{
		    Interrupt_UART2Rxd();
		    //RI2 = 0;
			S2CON &= 0xFE;
		}
	}
	else
	//if (TI==1)
	if ((S2CON & 0x02) == 0x02)
	{
	    if (Interrupt_UART2Txd != NULL) 
		{
		    Interrupt_UART2Txd();
	        //TI=0;
			S2CON &= 0xFD;
		}
	}   
}

void UART2_Set_InterruptProc(unsigned char pIntIdx,TInterruptProc pIntProc)
{
    switch(pIntIdx)
	{
	     case IntIndex_Uart2Rxd:
		     Interrupt_UART2Rxd = pIntProc;
		     break;
		 case IntIndex_Uart2Txd:
		     Interrupt_UART2Txd = pIntProc;
			 break;
	}
}

void Interrupt_Routine_Uart2() interrupt 8
{
	//ES2 = 0;
	IE2 &= 0xFE;
	UART2_Interrupt_Process();
	//ES2 = 1;
	IE2 |= 0x01;
}


void UART2_PortToP4(void)
{
    AUXR1 |= 0x10;
}

void UART2_PortToP1(void)
{
    AUXR1 &= 0xEF;
}

void UART2_Baud_SMODDouble(void)
{
    AUXR |= 0x08;
}

void UART2_Baud_SMODNormal(void)
{
    AUXR &= 0xF7;
}

void UART2_Init(unsigned char pByteSize,unsigned long pBaud)
{
	if (pByteSize==9)
	{
	    S2CON=0xD0;  //0xD0-9位;0x50-8位
	}
	else
	{
	    S2CON=0x50;  //0xD0-9位;0x50-8位
	}

	switch (pBaud)
	{
		case  1200:{	BRT=0x0ED;UART2_Baud_SMODNormal(); };break;
		case  2400:{	BRT=0x0F4;UART2_Baud_SMODNormal(); };break;
		case  4800:{	BRT=0x0FA;UART2_Baud_SMODNormal(); };break;
		case  9600:{	BRT=0x0FD;UART2_Baud_SMODNormal(); };break;
		case 14400:{	BRT=0x0FE;UART2_Baud_SMODNormal(); };break;
		case 19200:{	BRT=0x0FD;UART2_Baud_SMODDouble(); };break;
		case 28800:{	BRT=0x0FE;UART2_Baud_SMODDouble(); };break;
		//case 38400:{	BRT=0x0FD;UART2_Baud_SMODNormal(); };break;
		case 57600:{	BRT=0x0FF;UART2_Baud_SMODDouble(); };break;
	}
}

void UART2_Start()
{
    AUXR |= 0x10;  //BRTR = 1
}
void UART2_Stop()
{
    AUXR &= 0xEF;  //BRTR = 0
}
void UART2_EnableRxd()
{
    S2CON |= 0x10;  //S2REN = 1
}
void UART2_DisableRxd()
{
    S2CON &= 0xEF;  //S2REN = 0
}
void UART2_SetTB8(unsigned char pBit)
{
		if (pBit)
						S2CON |= 0x08;  //S2TB8 = 1
		else    S2CON &= 0xF7;  //S2TB8 = 0
}
void UART2_SendByte(unsigned char pByte)
{
	S2CON &= 0xFD;
	S2BUF = pByte;
	while((S2CON & 0x02)==0);
	S2CON &= 0xFD;
}

char UART2_ReadByte(unsigned char *pByte)
{
	if ((S2CON & 0x01) != 0)
	{
	    *pByte = S2BUF;
    	S2CON &= 0xFE;
		return 0;
	}
	return 1;
}


//------XRAM-------------------------------------------------------------------
void CHIPXRAM_Open(void)
{
    AUXR &= 0xFD;	  //EXTRAM = 0;
}
void CHIPXRAM_Close(void)
{
    AUXR |= 0x02;	  //EXTRAM = 1;
}


//------ADC---------------------------------------------------------------------
void ADC_Power(unsigned char pBool)
{
	if (pBool)	ADC_CONTR = 0x80; //Open Power
	else ADC_CONTR = 0x00;        //Close Power
	//AUXR1 |= 04;
}

void ADC_Pin(unsigned char pIdx,unsigned char pBool)
{
    unsigned char st;
	st = LeftShiftBitTable[pIdx];
    if (pBool) 
	  P1ASF |= LeftShiftBitTable[pIdx];
	else
	  P1ASF &= ~LeftShiftBitTable[pIdx];
}

char ADC_Get10(unsigned char pIdx,unsigned short *pValue)
{
    unsigned char aStatus;
	unsigned long aTimeOut=0;
	AUXR1 |= 04;
	ADC_CONTR = 0xE0 + pIdx;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	ADC_CONTR |= 0x08;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	do {
	    aStatus = ADC_CONTR & 0x10;
		aTimeOut++; if (aTimeOut>10000) return 1;
	}while (aStatus & 0x10 != 0);

	*pValue = ADC_RESL;
	*pValue += ADC_RES*256;

	return 0;
}

char ADC_Get8(unsigned char pIdx,unsigned char *pValue)
{
    unsigned char aStatus;
	unsigned long aTimeOut=0;
	AUXR1 &= 0xFB;
	ADC_CONTR = 0xE0 + pIdx;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	ADC_CONTR |= 0x08;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	do {
	    aStatus = ADC_CONTR & 0x10;
		aTimeOut++; if (aTimeOut>10000) return 1;
	}while (aStatus & 0x10 != 0);

	*pValue = ADC_RES;

	return 0;
}

//------WatchDog----------------------------------------------------------------
void MPU_WatchDogInit()
{
    //For dog
//    WDI = 0;
//    WDI = 1;
}

void MPU_WatchDogReset()
{
//    WDI =0;
//    WDI =1;
}

void MPU_To_FeedWatchDog()
{
//    To_FeedWatchDog = True;  
}


//------T0,T1------------------------------------------------------------------
void MPU_T0_SetTo_1Clk(void)
{
	AUXR |= 0x80;	  //T0x12 = 1  缺省  
}
void MPU_T0_SetTo_12Clk(void)
{
    AUXR &= 0x7F;     //T0x12 = 0
}

//------SPI------------------------------------------------------------------
void MPU_SPI_WriteByte(unsigned char pByte)
{
    SPDAT = pByte;
}
void MPU_SPI_Interrupt_Enable(void)
{	 
    IE2 |=0x02; //ESPI = 1;
}
void MPU_SPI_Interrupt_Disable(void)
{
    IE2 &=0xFD; //ESPI = 0;
}
void MPU_SPI_Interrupt_Clear(void)
{
    SPSTAT |= 0x80; //SPIF = 1;
}
void MPU_SPI_Set(unsigned char pByte)
{	//主机 SPI使能 MSB先发 上升输出 后时钟沿采样
    SPCTL = pByte;//0xD7;
}

*/


void UART1_Init(unsigned char pByteSize,unsigned long pBaud)
{
}


void UART1_SendByte(unsigned char pByte)
{
    int fd,size,i;
    unsigned char aByte;

    aByte = pByte;
    fd=open("./IOUARTO.BIN",O_WRONLY);
    write(fd,&aByte,1);
    close(fd);
}

void UART2_Init(unsigned char pByteSize,unsigned long pBaud)
{
}

void UART2_Start()
{
//    AUXR |= 0x10;  //BRTR = 1
}
void UART2_Stop()
{
//    AUXR &= 0xEF;  //BRTR = 0
}
void UART2_EnableRxd()
{
//    S2CON |= 0x10;  //S2REN = 1
}

char UART2_ReadByte(unsigned char *pByte)
{
    int fd,size,i;
    unsigned char aByte;

    fd=open("/home/wei/testnew/IOINPUT1.BIN",O_RDONLY);
    lseek(fd,6,SEEK_SET);    
    read(fd,&aByte,1);
    close(fd);

/*
	if ((S2CON & 0x01) != 0)
	{

	    *pByte = S2BUF;
    	S2CON &= 0xFE;
		return 0;

	}
	return 1;

*/
    *pByte = aByte;   
}


