/*
	File:		NewtonMemory.h

	Contains:	Memory interface for Newton DDK build system

	Written by:	The Newton Tools group

	Copyright:	� 1992-1995 by Apple Computer, Inc.  All rights reserved.

*/

#ifndef __NEWTONMEMORY_H
#define __NEWTONMEMORY_H

#ifndef __NEWTONTYPES_H
#include "NewtonTypes.h"
#endif


//----------------------------------------------------------------------
//		Newton PDA-specific stuff
//----------------------------------------------------------------------

typedef long Size;			

/*
**	Opaque memory manager types
**
*/
typedef void *	Heap;


/* The following define switches the default initiliazer �= 0� on/off
 * for C++ vs C for function defintions later in this header file
 * IT IS NOT INTENDED FOR USE IN YOUR C++/C CODE except in �extern "C"� 
 * function declarations like those below that need to work for both C and C++
*/
#ifdef __cplusplus
	#define DEFAULT_NIL = 0
#else
	#define	DEFAULT_NIL
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*	----------------------------------------------------------------
**
**	General operations
**
*/
NewtonErr		MemError(void);						/* per-task result of last memory mgr call */


/*	----------------------------------------------------------------
**
**	"Ptr" operations
**
**		Note that 'SetPtrSize' does not exist -- it is gone from the
**		Macintosh suite (use ReallocPtr instead, which can move the Ptr
**		block and is MUCH more effective than the Mac's SetPtrSize).
**
*/
#define		DisposePtr(p) DisposPtr(p)

void			DisposPtr(Ptr p);
Size			GetPtrSize(Ptr p);
Ptr				NewPtr(Size size);
Ptr				NewPtrClear(Size byteCount);
Heap			PtrToHeap(Ptr);
Ptr				ReallocPtr(Ptr, Size);			/* like realloc */


/*	----------------------------------------------------------------
**
**	Naming heap blocks
**
*/
ULong			GetPtrName(Ptr);
Ptr				NewNamedPtr(Size size, ULong name);
void			SetPtrName(Ptr, ULong);


Size			TotalFreeInHeap(Heap DEFAULT_NIL);
Size			LargestFreeInHeap(Heap DEFAULT_NIL);
unsigned long	CountFreeBlocks(Heap DEFAULT_NIL);
Size			TotalUsedInHeap(Heap DEFAULT_NIL);
Size			MaxHeapSize(Heap DEFAULT_NIL);


/*	----------------------------------------------------------------
**
**	System memory availability information
**
**		SystemRAMSize
**
**			e.g. 512K for J1
**
*/
Size			SystemRAMSize(void);


/*	----------------------------------------------------------------
**
**	Memory operations
**
**		If you are in doubt as to what to call to shuffle large amounts
**		of memory around, use BlockMove (which is...
**		...).  DON'T invent your own memory-moving
**		routines.
**
*/
void BlockMove(const void * srcPtr, void * destPtr, Size byteCount);
int  EqualBytes(const void *, const void *, Size);
void FillBytes(void *, Size length, UChar pattern);
void FillLongs(void *, Size length, ULong pattern);
void ZeroBytes(void *, Size length);
void XORBytes(const void * src1, const void * src2, void * dest, Size size);


#ifdef __cplusplus
}
#endif

#endif /* __NEWTONMEMORY_H */
