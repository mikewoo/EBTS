#ifndef _USYSMCUH_
#define _USYSMCUH_
//Ver1.00

//#include "REGXX.H"

#include "WOS_DEFINE.H"

//测试程序专用
#define bit bool
#define code const
#define data
#define xdata
#define idata

/*             
//------STC12AXX----------------------------------------------------------------
sfr  AUXR     = 0x8E;

sfr  P0M0     = 0x94;
sfr  P0M1     = 0x93;

sfr  P1M0     = 0x92;
sfr  P1M1     = 0x91;

sfr  P2M0     = 0x96;
sfr  P2M1     = 0x95;

*/
//******Function****************************************************************

//------PORT--------------------------------------------------------------------
extern void PortMod(unsigned char pPort,unsigned char pPortBit,unsigned char pMod);


//------Uart--------------------------------------------------------------------
extern void UART_Baud_Generator_12Clk(void);
extern void UART_Baud_Generator_1Clk(void);
extern void UART_Baud_Generator_Start(void);
extern void UART_Baud_Generator_Stop(void);

//------Uart1-------------------------------------------------------------------
extern void UART1_CLK_SetToSpecial(void);
extern void UART1_CLK_SetToT1(void);
extern void UART1_Baud_SMODDouble(void);
extern void UART1_Baud_SMODNormal(void);
extern void UART1_Init(unsigned char pByteSize,unsigned long pBaud);
extern void UART1_SendByte(unsigned char pByte);
extern char UART1_ReadByte(unsigned char *pByte);
//------Uart2-------------------------------------------------------------------
#define IntIndex_Uart2Rxd 0x81
#define IntIndex_Uart2Txd 0x82

extern void EnalbeInterrupt_Uart2();
extern void DisalbeInterrupt_Uart2();
//extern void UART2_Set_InterruptProc(unsigned char pIntIdx,TInterruptProc pIntProc);
extern void UART2_PortToP4(void);
extern void UART2_PortToP1(void);
extern void UART2_Baud_SMODDouble(void);
extern void UART2_Baud_SMODNormal(void);
extern void UART2_Init(unsigned char pByteSize,unsigned long pBaud);
extern void UART2_Start();
extern void UART2_Stop();
extern void UART2_EnableRxd();
extern void UART2_DisableRxd();
extern void UART2_SetTB8(unsigned char pBit);
extern void UART2_SendByte(unsigned char pByte);
extern char UART2_ReadByte(unsigned char *pByte);

//------XRAM-------------------------------------------------------------------
extern void CHIPXRAM_Open(void);  //缺省为开
extern void CHIPXRAM_Close(void);

//------ADC--------------------------------------------------------------------
extern void ADC_Power(unsigned char pBool);
extern void ADC_Pin(unsigned char pIdx,unsigned char pBool);
extern char ADC_Get10(unsigned char pIdx,unsigned short *pValue);
extern char ADC_Get8(unsigned char pIdx,unsigned char *pValue);

//------WatchDog----------------------------------------------------------------
#define SysDef_WatchDogFeed() { WDI =0, WDI =1; } 

extern void MPU_WatchDogReset();		/*看门狗复位*/
extern void MPU_To_FeedWatchDog();

//------E2PROM------------------------------------------------------------------
extern INT8U MPU_Byte_Read(INT16U add);
extern void MPU_Byte_Program(INT16U add, INT8U ch);
//擦除扇区, 入口:DPTR = 扇区地址
extern void MPU_Sector_Erase(INT16U add);
extern void MPU_IAP_Disable();


//------T0,T1------------------------------------------------------------------
extern void MPU_T0_SetTo_1Clk(void);
extern void MPU_T0_SetTo_12Clk(void);

//------SPI--------------------------------------------------------------------
extern void MPU_SPI_WriteByte(unsigned char pByte);
extern void MPU_SPI_Interrupt_Enable(void);
extern void MPU_SPI_Interrupt_Disable(void);
extern void MPU_SPI_Interrupt_Clear(void);
extern void MPU_SPI_Set(unsigned char pByte);

#endif
