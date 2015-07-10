/******************************************************************************/
/*接口说明:
/*----------------------------------------------------------------------------*/
/*TypeDefs:
/*	Byte,Word,DWord
/*	TVarWord,TVarDWord
/*TalbeDefs:
/*	LeftShiftTable
/*	RightShiftTable
/******************************************************************************/
#ifndef _UWOSWTYPESH_
#define _UWOSWTYPESH_

#define code const

#include "WOS_DEFINE.H"

//#define CPU51
#define ARM

#ifdef  CPU51
#define con_data_f xdata
#define con_data_n idata
#define con_data_i data
#define con_data_r register
#endif //end define for CPU51

#ifndef bool
#define bool bit
#endif

#ifndef BOOL
#define BOOL bit
#endif


#define int8   char
#define uint8  unsigned char
#define int16  short
#define uint16 unsigned short
#define int32  long
#define uint32 unsigned long

#define Int8   char
#define Int8U  unsigned char
#define Int16  short
#define Int16U unsigned short
#define Int32  long
#define Int32U unsigned long

#define FPInt8U  (unsigned char*)
#define FPInt16U (unsigned short*)
#define FPInt32U (unsigned long*)

#define BYTE unsigned char
#define Byte unsigned char
#define byte unsigned char
#define WORD unsigned short
#define Word unsigned short
#define word unsigned short
#define DWORD unsigned long
#define DWord unsigned long
#define Dword unsigned long

#define FPVarWord 	(TVarWord*)
#define FPVarDWord	(TVarDWord*)

#define PVarWord 	TVarWord*
#define PVarDWord	TVarDWord*

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
  } TVarWord;

  typedef
  union {
    unsigned char  AsBytes[4];
    unsigned char  AsByte;
             char  AsChar;
    unsigned short AsWords[2];
    unsigned short AsWord;
             short AsShort;
    unsigned long  AsDWord;
             long  AsLong;
	struct {
      unsigned short WordHi;
      unsigned short WordLo;
    }AsWordHL;
	struct {
      TVarWord VarWordHi;
      TVarWord VarWordLo;
    }AsVarWordHL;
  }TVarDWord;

extern Byte code LeftShiftBitTable[8];
extern Byte code RightShiftBitTable[8];
 
typedef void(*TInterruptProc)(void);
typedef void(*TFarProc)(void);
typedef void(*TVoidProc)(void);


#endif
