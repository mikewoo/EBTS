#include "Output.h"
#include "SYS_MCU.h"
//#include "INTRINS.h"
#include "WOS_DEFINE.H"
#include "PortConfig.h"
#include "Memory.h"

#include "System.h"
#include "Input.h"

#include <stdio.h>  

//#include <iostream>  
#include <fcntl.h> 
#include <sys/types.h>  
#include <sys/stat.h> 
#include <unistd.h>  
//using namespace std;  



void Mot_OnOff(unsigned char pID,bit pOnOff,bit pDir)
{  
    FILE *fp;
    unsigned char aOutByte;

	switch(pID)
	{
		case 1:{
			AppStatus.Mot1_Phase 	= pDir;
			AppStatus.Mot1_Running 	= pOnOff;
			if (AppStatus.Mot1_Running == 1) 
			{
				AppStatus.Mot1_Counter = 0;
			};
		};break;
		case 2:{
			AppStatus.Mot2_Phase 	= pDir;
			AppStatus.Mot2_Running 	= pOnOff;
			if (AppStatus.Mot2_Running == 1) 
			{
				AppStatus.Mot2_Counter = 0;
			};
		};break;
		case 3:{
			AppStatus.Mot3_Phase 	= pDir;
			AppStatus.Mot3_Running 	= pOnOff;
			if (AppStatus.Mot3_Running == 1) 
			{
				AppStatus.Mot3_Counter = 0;
			};
		};break;
	}
	
	Mot_RunProtect();//20130110电机启动前防撞
	
//	EMot1 = !AppStatus.Mot1_Running;
//	PMot1 = AppStatus.Mot1_Phase;

//	EMot2 = !AppStatus.Mot2_Running;
//	PMot2 = AppStatus.Mot2_Phase;

//	EMot3 = !AppStatus.Mot3_Running;
//	PMot3 = AppStatus.Mot3_Phase;

    if (AppStatus.Mot1_Running==0) aOutByte |= 0x01;
    else                           aOutByte &= 0xFE; 
    if (AppStatus.Mot1_Phase==1) aOutByte |= 0x02;
    else                         aOutByte &= 0xFD;

    if (AppStatus.Mot2_Running==0) aOutByte |= 0x04;
    else                           aOutByte &= 0xFB; 
    if (AppStatus.Mot2_Phase==1) aOutByte |= 0x08;
    else                         aOutByte &= 0xF7;

    if (AppStatus.Mot3_Running==0) aOutByte |= 0x10;
    else                           aOutByte &= 0xEF;
    if (AppStatus.Mot3_Phase==1) aOutByte |= 0x20;
    else                         aOutByte &= 0xDF;

    fp = fopen("./IOOUTM.BIN", "w");
    fwrite(&aOutByte,1,1,fp);
    fclose(fp);
}

void Mot_RunProtect()
{
    FILE *fp;
    unsigned char aOutByte;
	
	if (AppStatus.Mot1_Running)
	{
		AppStatus.Mot1_Counter++;
		if (AppStatus.Mot1_Counter > 100) 
		{
			AppStatus.Mot1_Running=0;
		};
		if (AppStatus.Mot1_Phase == 0)
			if (AppStatus.Sensor1_P != 1)
			{	AppStatus.Mot1_Running=0; AppStatus.Mot1_ToAutoInit = 0;//自动初始化结束
			}
		if (AppStatus.Mot1_Phase == 1)
			if (AppStatus.Sensor1_N != 1)
			{	AppStatus.Mot1_Running=0; AppStatus.Mot1_ToAutoInit = 0;//自动初始化结束
			}
//		EMot1 = !AppStatus.Mot1_Running;
                if (AppStatus.Mot1_Running==0) aOutByte |= 0x01;
                else                           aOutByte &= 0xFE;  
	}
	
	if (AppStatus.Mot2_Running)
	{
		AppStatus.Mot2_Counter++;
		if (AppStatus.Mot2_Counter > 100) 
		{
			AppStatus.Mot2_Running=0;
		};
		if (AppStatus.Mot2_Phase == 0)
			if (AppStatus.Sensor2_P != 1)	AppStatus.Mot2_Running=0;
		if (AppStatus.Mot2_Phase == 1)
			if (AppStatus.Sensor2_N != 1)	AppStatus.Mot2_Running=0;
//		EMot2 = !AppStatus.Mot2_Running;
               if (AppStatus.Mot2_Running==0) aOutByte |= 0x04;
               else                           aOutByte &= 0xFB;  
	}

	if (AppStatus.Mot3_Running)
	{
		AppStatus.Mot3_Counter++;
		if (AppStatus.Mot3_Counter > 100) 
		{
			AppStatus.Mot3_Running=0;
		};
		//if (AppStatus.Mot3_Phase == 0)
		//	if (AppStatus.Sensor3_P != 1)	AppStatus.Mot3_Running=0;
		//if (AppStatus.Mot3_Phase == 1)
		//	if (AppStatus.Sensor3_N != 1)	AppStatus.Mot3_Running=0;
//		EMot3 = !AppStatus.Mot3_Running;
               if (AppStatus.Mot3_Running==0) aOutByte |= 0x10;
               else                           aOutByte &= 0xEF;  
	}

    fp = fopen("./IOOUTM.BIN", "w");
    fwrite(&aOutByte,1,1,fp);
    fclose(fp);
}

