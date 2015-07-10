#include "TMAIN.h"

#include "WOS_DEFINE.H"
#include "SYS_MCU.h"
#include "System.h"
#include "PortConfig.h"
#include "Memory.h"
#include "Input.h"
#include "Output.h"
#include "Process.h"
#include "UI.h"
#include "BusSig.h"


#include <fcntl.h>
#include <stdio.h>  
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

void sigroutine(int signo)
{
    switch (signo) {
        case SIGALRM:
             _IsTimer1s = TRUE; 
            //printf("---Time1s signal -- SIGALRM\n");
            break;
        case SIGVTALRM:
            _IsTimer1ms = TRUE;
            //printf("---Timer1ms signal -- SIGVTALRM\n");
            break;
    }
}

//void sigroutine1(int signo)
//{
//    _IsTimer1ms = TRUE;
//}

void _TimerSet(void)
{
    struct itimerval value,ovalue,value2;
    //sec = 5;
    printf("process id is %d\n",getpid());
    signal(SIGALRM, sigroutine);
    signal(SIGVTALRM, sigroutine);

    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 100000;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 100000;
    setitimer(ITIMER_REAL, &value, &ovalue);
    value2.it_value.tv_sec = 0;
    value2.it_value.tv_usec = 100000;
    value2.it_interval.tv_sec = 0;
    value2.it_interval.tv_usec = 100000;
    setitimer(ITIMER_VIRTUAL, &value2, &ovalue);
}


void Device_Init(void);

int main()
{
	unsigned char i;

	idata unsigned short j;
	BYTE aDir=0;
        unsigned long _RunTicks = 0;

	idata BYTE aKey;
	idata byte aByte,bByte;

//	aKey = UI_KeyGet();

        _TimerSet();
	Mem_Init();
	SysInit();
	for (j=0;j<100;j++);

	UART1_Init(8,57600);
	UART1_SendByte(0x55);
	UART2_Init(8,9600);
	UART2_Start();
	UART2_EnableRxd();
	
	Device_Init();
	
	while (1)
	{  		
		//Timer 1ms Signal
		if (_IsTimer1ms)
		{   _IsTimer1ms = FALSE;
			//for(j=2000;j>0;j--);
			//读Key 
                        aKey = UI_KeyGet();
			Event_Keyboard(aKey);
			
			//读通信
			IN_Comm();
			Event_Comm();

			//自动工作
			Event_Auto();
			
			//传感器 
			//IN_Sensor();
			//电机保护
			Mot_RunProtect() ;
			
			//计数器
			if (AppStatus.Sensor_Counter1>=1)
			{AppStatus.Sensor_Counter1=0;
				
				if (bByte==0)
				{bByte=1;
					Led_OnOff(1,1);
				}else
				{bByte=0;
					Led_OnOff(1,0);
				}
			}
		}//if10ms
		//Timer 1s Signal
		if (_IsTimer1s)
		{  _IsTimer1s = FALSE;

                    _RunTicks++;
                    printf("---Time %ld passed.\n",_RunTicks);
                    if ( _RunTicks>=2){ _RunTicks=0; break;}
			//Led_OnOff(2,0);

			if (aByte==0)
			{aByte=1;
				Led_OnOff(1,1);
				////Mot_OnOff(3,0,1);
			}else
			{aByte=0;
				Led_OnOff(1,0);
				////Mot_OnOff(3,1,0);
			}
		}

		
		//Timer Signal end
	} //while(1)
        printf("Process Ended-->\n");
	sleep(2000);
        return 0;
}

void Device_Init()
{
	AppStatus.Mot1_ToP = 0;
	AppStatus.Mot1_ToN = 0;
	AppStatus.Mot2_ToP = 0;
	AppStatus.Mot2_ToN = 0;
	AppStatus.Mot3_ToP = 0;
	AppStatus.Mot3_ToN = 0;

	AppStatus.Mot1_Running = 0;
	AppStatus.Mot2_Running = 0;
	AppStatus.Mot3_Running = 0;
	
	AppStatus.Mot1_Phase = 0;
	AppStatus.Mot2_Phase = 0;
	AppStatus.Mot3_Phase = 0;
	
	AppStatus.Mot1_Counter = 0;
	AppStatus.Mot2_Counter = 0;
	AppStatus.Mot3_Counter = 0;
		
	AppStatus.Mot1_ToAutoInit = 0;
	
	Enalble_U2_485R(1);
	Enalble_U2_485T(0);
	
	Mot_OnOff(1,0,0);
	Mot_OnOff(2,0,0);
	Mot_OnOff(3,0,0);
	
	Led_OnOff(1,0);
	Led_OnOff(2,0);
}

