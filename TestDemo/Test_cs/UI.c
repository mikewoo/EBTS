#include "UI.h"
#include "SYS_MCU.h"
//#include "INTRINS.H"
#include "WOS_DEFINE.H"
#include "WOS_WTYPE.H"
#include "PortConfig.h"
//#include "Memory.h"

//#include "System.h"
//#include "Input.h"


#define data

#include <stdio.h>  

//#include <iostream>  
#include <fcntl.h> 
#include <sys/types.h>  
#include <sys/stat.h> 
#include <unistd.h>  
//using namespace std;  



data unsigned char _KeyCode=0xFF,_KeyOld=0xFF,_KeyOld1=0xFF,_KeyNow;
data unsigned char _Last_KeyCode = 0xFF, KeyPressIng=0;
unsigned char _KeyInBuf[2],_KeyRowP=0;
data unsigned char _Keyi,_KeyaByte;


unsigned char UI_KeyGet()
{
	static unsigned char iKeyCode = 0xFF; 
	static unsigned char iKeyLast = 0xFF;	
        static char kByte[6]; 
	
	unsigned char aKeyBuff=0;
	

     int  fd1 = open("/home/wei/Test_c/IOINPUT1.BIN", O_RDONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);

    read(fd1, kByte, 6);
	close(fd1);
	
	if (kByte[0]==0x01) { aKeyBuff |= 0x01; }
	if (kByte[1]==0x02) { aKeyBuff |= 0x02; }
	if (kByte[2]==0x04) { aKeyBuff |= 0x04; }
	if (kByte[3]==0x08) { aKeyBuff |= 0x08; }
	if (kByte[4]==0x10) { aKeyBuff |= 0x10; }
	if (kByte[5]==0x20) { aKeyBuff |= 0x20; }

	if (aKeyBuff != iKeyLast)
	{
		iKeyLast = aKeyBuff;
		return 0xFF;
	}
	else
	{
		iKeyCode = iKeyLast;
		iKeyLast = 0xFF;
	};
	return iKeyCode;
}

void Led_OnOff(unsigned char pID,bit pOnOff) //ID-Led1-2 OnOff-1:On 0:Off
{  
    FILE *fp;
    unsigned char aOutByte;

    switch(pID)
	{
		case 1:{
//			eLed1 = (pOnOff==1)?0:1; 
			aOutByte &= 0xFE;
			aOutByte |= 0x01;
		};break;
		case 2:{
//			eLed2 = (pOnOff==1)?0:1; 
			aOutByte &= 0xFD;
			aOutByte |= 0x02;
		};break;
	}

    fp = fopen("./IOOUTLED.BIN", "w");
    fwrite(&aOutByte,1,1,fp);
    fclose(fp);

}

