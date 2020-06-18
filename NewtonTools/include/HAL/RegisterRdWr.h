/*
	File:		RegisterRdWr.h

	Copyright:	� 1992-1993, 1996 by Apple Computer, Inc., all rights reserved.

	Derived from v1 (1/8/96) internal.

*/


#ifndef __REGISTERRDWR_H
#define __REGISTERRDWR_H


#ifndef __NEWTTYPES_H
#include "NewtTypes.h"
#endif

#ifndef __USERGLOBALS_H
#include "UserGlobals.h"
#endif




inline
ULong ReadReg(ULong addr)									//	Read a ULong from addr
{
	return ReadVLong((void*)addr);
}

inline
UChar ReadRegB(ULong addr)									//	Read a UChar from addr
{
	return ReadVByte((void*)addr);
}


inline
void WriteReg(ULong addr, ULong data)						//	Write a ULong to addr
{
	WriteVLong((void*)addr, data);
}

inline
void WriteRegB(ULong addr, ULong data)						//	Write a UChar to addr
{
	WriteVByte((void*)addr, (UChar)data);
}


inline
ULong GetRegBits(ULong addr, ULong bits)					//	Get bits from a ULong at addr
{
	return ReadVLong((void*)addr) & bits;
}

inline
UChar GetRegBitsB(ULong addr, ULong bits)					//	Get bits from a UChar at addr
{
	return ReadVByte((void*)addr) & (UChar)bits;
}


inline
void ClearRegBits(ULong addr, ULong bits)					//	Clear bits in a ULong at addr
{
	*(volatile ULong*)addr &= ~bits;
}

inline
void ClearRegBitsB(ULong addr, ULong bits)					//	Clear bits in a UChar at addr
{
	*(volatile UChar*)addr &= (UChar)~bits;
}


inline
void SetRegBits(ULong addr, ULong bit)						//	Set bits in a ULong at addr
{
	*(volatile ULong*)addr = (*((volatile ULong*)addr)) | bit;
}

inline
void SetRegBitsB(ULong addr, ULong bit)						//	Set bits in a UChar at addr
{
	*(volatile UChar*)addr = (*((volatile UChar*)addr)) | (UChar)bit;
}


inline
void ClearNSetRegBits(ULong addr, ULong bits, ULong data)	//	Clear bits and set data in a ULong at addr
{
	*(volatile ULong*)addr = (*((volatile ULong*)addr) & ~bits) | data;
}

inline
void ClearNSetRegBitsB(ULong addr, ULong bits, ULong data)	//	Clear bits and set data in a UChar at addr
{
	*(volatile UChar*)addr = (*((volatile UChar*)addr) & (UChar)~bits) | (UChar)data;
}





#endif
