/*****************************************************************************************************
* GP32 SDK Version 1.1 header file : gpdef.h                                                         *
*		The latest patch : 22,May,2001                                                             *
*		SDK Developer : Jstar, Achi                                                                *
*		related library : all library file                                                         *
*		COPYRIGHT DESCRIPTION														 *
*			The copyright of the source is reserved by GAMEPARK,Inc!!!                            *
*****************************************************************************************************/

#ifndef __GPDEF_H__
#define __GPDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "gpos_def.h"

#ifndef NULL
#define NULL 	0
#endif

#ifndef TRUE
#define TRUE	1
#else
#undef TRUE
#define TRUE	1
#endif

#ifndef	FALSE
#define FALSE	0
#else
#undef	FALSE
#define FALSE	0
#endif

#ifndef __size_t
#define __size_t 1
   typedef unsigned int size_t;
#endif

#undef byte
#define byte	char

#undef ubyte
#define ubyte	unsigned char

#undef uchar
#define uchar unsigned char

#undef word
#define word	short

#undef uword
#define uword	unsigned short

#undef ushort
#define ushort unsigned short

#undef dword
#define dword	long

#undef udword
#define udword	unsigned long

#undef ulong
#define ulong unsigned long

/*==============================================*/
//key definition
#define	GPC_VK_NONE		0x00
#define	GPC_VK_LEFT		0x01
#define	GPC_VK_UP		0x08	
#define	GPC_VK_RIGHT	0x04
#define	GPC_VK_DOWN		0x02

#define GPC_VK_F1		0x80	//AT OLD, VK_ENTER
#define GPC_VK_F2		0x10	//AT OLD, VK_F3
#define GPC_VK_F3		0x20	//AT OLD, VK_F2
#define GPC_VK_ENTER	0x40	//AT OLD, VK_F1

#define GPC_VK_START	0x100
#define GPC_VK_SELECT	0x200

#define GPC_VK_FA		GPC_VK_ENTER
#define GPC_VK_FB		GPC_VK_F3
#define GPC_VK_FL		GPC_VK_F2
#define GPC_VK_FR		GPC_VK_F1

/*==============================================*/
//LCD Definition
#define	GPC_LCD_WIDTH	320
#define	GPC_LCD_HEIGHT	240
#define GPC_LCD_PHYSICAL_W	240
#define GPC_LCD_PHYSICAL_H	320

/*etc===========================================*/
typedef struct tagGPRECT{
	int left;
	int top;
	int right;
	int bottom;
}GPRECT;

typedef struct tagGPPOINT{
	int X;
	int Y;
}GPPOINT;

/* file system*/
#define MAX_PATH_NAME_LEN	256

#ifdef __cplusplus
}
#endif

#endif /*__GPDEF_H__*/
