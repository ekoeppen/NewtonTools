/*
	File:		CompMath.h

	Contains:	Header file for composite math routines.

	Copyright:	� 1991-1995 by Apple Computer, Inc., all rights reserved.

    Derived from v6 internal.

*/

#ifndef	__COMPMATH_H
#define	__COMPMATH_H

#ifndef __CONFIGTOOLBOX_H
#include "ConfigToolbox.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

void	CompAdd(const Int64* src, Int64* dst);
void	CompSub(const Int64* src, Int64* dst);
void	CompNeg(Int64* srcdst);
void	CompShift(Int64* srcdst, long shift);
void	CompMul(long src1, long src2, Int64* dst);
long	CompDiv(const Int64* numerator, long denominator, long* remainder);
void	CompFixMul(const Int64* compSrc, Fixed fixSrc, Int64* compDst);
long	CompCompare(const Int64* a,const Int64* minusb);
unsigned long CompSquareRoot(const Int64* src);

#ifdef __cplusplus
}
#endif


#endif
