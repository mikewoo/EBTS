#ifndef _UMEMORYH_
#define _UMEMORYH_

#include "SYS_MCU.h"

typedef
  	struct {
		//Input
		Byte Power_ToInit;
		Byte Power_ToPreOff;
		Byte Power_ToOn;
		Byte Power_ToOff;

		Byte Mot1_ToAutoInit;
		
		Byte Mot1_ToP;
		Byte Mot1_ToN;
		Byte Mot2_ToP;
		Byte Mot2_ToN;
		Byte Mot3_ToP;
		Byte Mot3_ToN;		//System
		//Input
		Byte Sensor1_P;
		Byte Sensor1_N;
		Byte Sensor2_P;
		Byte Sensor2_N;

		//Input
		Byte Sensor_Counter0;
		Byte Sensor_Counter1;

        //OutPut
		Byte Mot1_Running;
		Byte Mot2_Running;
		Byte Mot3_Running;
		
		Byte Mot1_Phase;
		Byte Mot2_Phase;
		Byte Mot3_Phase;

		Byte Mot1_Counter;
		Byte Mot2_Counter;
		Byte Mot3_Counter;

    }TAppStatus;

extern xdata volatile TAppStatus AppStatus;

extern void Mem_Init();

#endif
