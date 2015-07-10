#include "Input.h"
#include "SYS_MCU.h"
//#include <intrins.h>
#include "WOS_DEFINE.H"
#include "PortConfig.h"
#include "Memory.h"
#include "BusSig.h"

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include  <unistd.h>

void IN_Comm()
{	
	static idata byte aByte;
	//static idata byte aBuf[10];

/*	
	if (!UART1_ReadByte(&aByte))
	{
//		if (aByte == To_FMot_ToP) AppStatus.Mot_ToP=1;
//		if (aByte == To_FMot_ToN) AppStatus.Mot_ToN=1;
		
		AppStatus.Sig_TimeOut =0;
		if ((aByte & 0xFF) == To_HotX_Off)
		{
			AppStatus.Hot1Time =   0;
			AppStatus.Hot2Time =   0;
			AppStatus.Hot3Time =   0;
			AppStatus.Hot4Time =   0;
		}
	}
*/	
	aByte = 0x00;
	if (!UART2_ReadByte(&aByte))
	{
		if (aByte == To_FMot1_AutoInit) 
			AppStatus.Mot1_ToAutoInit = 1;

		if (aByte == To_FMot1_ToP) AppStatus.Mot1_ToP=1;
		if (aByte == To_FMot1_ToN) AppStatus.Mot1_ToN=1;
		if (aByte == To_FMot2_ToP) AppStatus.Mot2_ToP=1;
		if (aByte == To_FMot2_ToN) AppStatus.Mot2_ToN=1;
		if (aByte == To_FMot3_ToP) AppStatus.Mot3_ToP=1;
		if (aByte == To_FMot3_ToN) AppStatus.Mot3_ToN=1;
	}
}

void IN_Sensor()
{
    bit aBit;
    //static byte aByte,i;
    int fd,size,i;
    char buffer[80],aByte,aBytes[4];

    fd=open("/home/wei/Test_c/IOINPUT1.BIN",O_RDONLY);
    lseek(fd,7,SEEK_SET);
    read(fd,aBytes,4);
    close(fd);

        aBit = aBytes[0] & 0x01;
//	aBit = MotLim_11;
	AppStatus.Sensor1_P = aBit;
        
        aBit = aBytes[1] & 0x02;
//	aBit = MotLim_12;
	AppStatus.Sensor1_N = aBit;

        aBit = aBytes[2] & 0x04;
//	aBit = MotLim_21;
	AppStatus.Sensor2_P = aBit;

        aBit = aBytes[3] & 0x08;
//	aBit = MotLim_22;
	AppStatus.Sensor2_N = aBit;
}
/*
void IN_Counter0()
{
	if (AppStatus.Sensor_Counter0<100) 
		AppStatus.Sensor_Counter0++;
}
void IN_Counter1()
{
	if (AppStatus.Sensor_Counter1<100) 
		AppStatus.Sensor_Counter1++;
}
*/
