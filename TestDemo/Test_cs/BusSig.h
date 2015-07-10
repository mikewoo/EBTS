#ifndef _UBUSSIGH_
#define _UBUSSIGH_

#include "SYS_MCU.h"

#define To_Power_On 		0x11
#define To_Power_Off 		0x10
#define To_Power_PreOff 	0x12

#define To_FMot1_ToP		0x41
#define To_FMot1_ToN 		0x42
#define To_FMot2_ToP		0x43
#define To_FMot2_ToN 		0x44
#define To_FMot3_ToP		0x45
#define To_FMot3_ToN 		0x46
#define To_FMot4_ToP		0x47
#define To_FMot4_ToN 		0x48
#define To_FMot1_AutoInit	0x4F

extern void Enalble_U2_485R(bit pOnOff);
extern void Enalble_U2_485T(bit pOnOff);

#endif

