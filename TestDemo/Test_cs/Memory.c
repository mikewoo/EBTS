#include "Memory.h"
#include "SYS_MCU.h"
//#include <intrins.h>
#include "WOS_DEFINE.H"
#include "PortConfig.h"
#include "Memory.h"

xdata volatile TAppStatus AppStatus={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                           	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
                           };


void Mem_Init()
{
    AppStatus.Sensor_Counter0 = 0;
    AppStatus.Sensor_Counter1 = 0;
}

void Mem_Load()
{
    
}

void Mem_Save()
{
    
}

