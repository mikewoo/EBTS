#ifndef UWOS_DEFINEH
#define UWOS_DEFINEH

//测试程序专用
#define _nop_() {}

#define bit bool
#define code const
#define data
#define xdata
#define idata

#ifndef NULL
    //#define NULL    ((void *)0)
    #define NULL    0
#endif

/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/


//#define BYTE           INT8S                     /* Define data types for backward compatibility ...   */
//#define UBYTE          INT8U                     /* ... to uC/OS V1.xx.  Not actually needed for ...   */
//#define WORD           INT16S                    /* ... uC/OS-II.                                      */
//#define UWORD          INT16U
#define LONG           INT32S
#define ULONG          INT32U

//#define BYTE           INT8S                     /* Define data types for backward compatibility ...   */
#define UCHAR          INT8U                     /* ... to uC/OS V1.xx.  Not actually needed for ...   */
//#define WORD           INT16S                    /* ... uC/OS-II.                                      */
//#define UWORD          INT16U
//#define LONG           INT32S
//#define ULONG          INT32U


/* 全局符号定义 */
#define HIGH 1
#define LOW 0
#define FALSE 0
#define TRUE ~FALSE
#define True  TRUE
#define False FALSE
//#define Not   !
//#define not   !
#define BitNot   ~
#define bitnot   ~
#define Yes   
#define yes   
#define function
#define procedure void
#define end_if
#define end_for
#define end_while
#define end_switch

//#define CPU51

#ifdef  CPU51
  #ifndef bool
    #define bool bit
  #endif
#endif

#define ARM
#ifdef  ARM
  #ifndef bool
    #define bool char
  #endif
#endif

#define BOOL bool

#define BYTE unsigned char
#define Byte unsigned char
#define byte unsigned char
#define WORD unsigned short
#define word unsigned short
#undef  DWORD
#define DWORD unsigned long

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */

//#define FPVarWord 	(TVarWord*)
//#define FPVarDWord	(TVarDWord*)

//#define PVarWord 	TVarWord*
//#define PVarDWord	TVarDWord*

 
#endif
