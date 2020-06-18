/*
	File:		NewtonWidgets.h

	Contains:	Interface to Classroom widgets

	Written by:	The Newton Tools group

	Copyright:	� 1992-1995 by Apple Computer, Inc.  All rights reserved.

*/

#ifndef __NEWTONWIDGETS_H
#define __NEWTONWIDGETS_H

#ifndef __NEWTONTYPES_H
#include "NewtonTypes.h"
#endif

#ifndef EOF
#define EOF (-1)
#endif

#ifndef EOM
#define EOM (-2)
#endif

#ifndef UNUSED_PARAM
#define UNUSED_PARAM(x) (1 ? (void) 0 : (void) x)
#endif

#ifdef __cplusplus
	enum PositionMode 
	{
		kPosBeg = -1,
		kPosCur = 0,
		kPosEnd = 1
	};
#endif


#if !defined(qMacApp) || defined(forDockerSubSystem)

	typedef Long ArrayIndex;
	enum IndexValues { kEmptyIndex = -1 };

#endif

//--------------------------------------------------------------------------------
//		Byte swapping
//--------------------------------------------------------------------------------

#define BYTE_SWAP_CHAR(n) (n)
#define BYTE_SWAP_SHORT(n) (((UShort) n >> 8) + ((UShort) n << 8))
#define BYTE_SWAP_LONG(n) (((n << 24) & 0xFF000000) | ((n <<  8) & 0x00FF0000) | ((n >>  8) & 0x0000FF00) | ((n >> 24) & 0x000000FF))

// the following macros are for code with static data that
// assumes ordering different from native ordering

#ifdef hasByteSwapping

	#define CANONICAL_LONG BYTE_SWAP_LONG
	#define CANONICAL_SHORT BYTE_SWAP_SHORT
	#define	CANONICAL_CHAR BYTE_SWAP_CHAR

#else

	#define CANONICAL_LONG(n) (n)
	#define CANONICAL_SHORT(n) (n)
	#define CANONICAL_CHAR(n) (n)

#endif

void ByteSwap (void* p, long count, long swapSize);	// always available
	// implementation of ByteSwap is in UtilityClasses:Widgets.c


//--------------------------------------------------------------------------------
//		Comparison Macros
//--------------------------------------------------------------------------------

#define ABS(a)    ( ((a) < 0) ? -(a) : (a) )
#define MAX(a, b) ( ((a) > (b)) ? (a) : (b) )
#define MIN(a, b) ( ((a) < (b)) ? (a) : (b) )
#define MINMAX(min, expr, max) ( MIN(MAX(min, expr), max) )
#define ODD(x)    ( (x) & 1 )
#define EVEN(x)   ( !((x) & 1) )

#ifdef __cplusplus
	inline Boolean Odd(ULong x)						{ return (Boolean) (x & 1); }
	inline Boolean Even(ULong x)					{ return (Boolean) !(x & 1); }
	inline Long Abs(Long a)							{ return (a < 0) ? -a : a; }
#if !defined(qMacApp) || defined(forDockerSubSystem)
	inline Long Max(Long a, Long b)					{ return (a > b) ? a : b; }
	inline Long Min(Long a, Long b)					{ return (a < b) ? a : b; }
	inline Long MinMax(Long l, Long x, Long h)		{ return Min(Max(l, x), h); }
#endif
	inline ULong UMax(ULong a, ULong b)				{ return (a > b) ? a : b; }
	inline ULong UMin(ULong a, ULong b)				{ return (a < b) ? a : b; }
	inline ULong UMinMax(ULong l, ULong x, ULong h)	{ return UMin(UMax(l, x), h); }
#endif

//--------------------------------------------------------------------------------
//		Bitwiddling Macros
//--------------------------------------------------------------------------------

//	BIT(N)		the Nth bit set
//	BITS(N,M)	bits N through M set, inclusive.  N > M  (e.g. "BITS(31,0)").

#define BIT(N)		(1<<(N))						/* bit N				*/
#define BITS(N,M)	((BIT((M)-(N)+1)-1)<<(N))		/* bits N..M inclusive	*/

#define MASKTEST(data, mask)   ( (data) & (mask) )
#define MASKSET(data, mask)    ( (data) | (mask) )
#define MASKCLEAR(data, mask)  ( (data) & (~(mask)) )
#define MASKTOGGLE(data, mask) ( ((data) & (mask)) ? ((data) & (~(mask))) : ((data) | (mask)) )

#ifdef __cplusplus
	inline ULong MaskTest(ULong data, ULong mask)	{ return data & mask; }
	inline ULong MaskSet(ULong data, ULong mask)	{ return data | mask; }
	inline ULong MaskClear(ULong data,ULong  mask)	{ return data & (~mask); }
	inline ULong MaskToggle(ULong data, ULong mask)	{ return (data & mask) ? (data & (~mask)) : (data | mask); }
#endif

//--------------------------------------------------------------------------------
//		Alignment Macros
//--------------------------------------------------------------------------------

// some useful sizes

#define	KByte					(1024)
#define	MByte					(1024*1024)


//	ALIGN(amount, boundary)		round 'amount' up to nearest 'boundary' (which
//									must be a power of two)
//
//	WORDALIGN(amount)			round 'amount' up to a multiple of two
//
//	LONGALIGN(amount)			round 'amount' up to a multiple of four
//
//	PAGEALIGN(amount)			ditto, for 4K and 1K (ARM)
//	SUBPAGEALIGN(amount)

#define		ALIGN(N,B)			((((ULong)(N))+(B)-1)&~(B-1))
#define		WORDALIGN(n)		ALIGN((n),2)
#define		LONGALIGN(n)		ALIGN((n),4)
#define		PAGEALIGN(n)		ALIGN((n),kPageSize)
#define		SUBPAGEALIGN(n)		ALIGN((n),kSubPageSize)
#define		ALIGNED(n,B)		(((ULong)(n)) == ALIGN(((ULong)(n)),B))
#define		TRUNC(N,B)			(((ULong)(N)) & ~((B)-1))

//--------------------------------------------------------------------------------
//		TProtocol support
//--------------------------------------------------------------------------------

#ifdef hasNoProtocols
	#define NEWPROTOCOL(var, type, name) 	{ var = (type*) new name; var->New(); }
	#define DELETEPROTOCOL(var)				{ var->Delete(); delete var;}
#else
	#define NEWPROTOCOL(var, type, name)	{ var = (type*) NewByName(#type, #name); }
	#define DELETEPROTOCOL(var)				{ var->Delete(); }
#endif

#endif	/* __NEWTONWIDGETS_H */
