/*
	File:		FixedMath.h

	Contains:	Fixed Math interfaces.

	Copyright:	� 1993-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v9 internal.

*/


#ifndef __FIXEDMATH_H
	#define __FIXEDMATH_H

#ifndef __CONFIGTOOLBOX_H
#include "ConfigToolbox.h"
#endif


	typedef struct {
		Fixed	radius;
		Fixed	angle;
	} polar;

	#define kFix1				((Fixed) 0x00010000)				/* Fixed 1.0 	*/
	#define kFixNeg1			((Fixed) 0xFFFF0000)				/* Fixed -1.0 	*/
	#define kFixHalf			(kFix1 / 2)							/* Fixed 0.5 	*/
	#define kFrac1				((Fract) 0x40000000)				/* Fract 1.0 	*/
	#define kFracHalf			((Fract) 0x20000000)				/* Fract 0.5 */

	#define kShiftBitsLong 			5			/* shift counts */
	#define kShiftBytesLong		2
	#define kShiftBitsWord			4
	#define kShiftBytesWord		1
	#define kShiftBitsByte			3
	#define kShiftBytesPoint		3
	#define kLongSize				32
	#define kLongMask				31			/* for figuring bits outside of complete longs */
	#define kHalfLongSize			16
	#define kFixedPrecision		16
	#define kFractPrecision		30
	#define kShortSize				16
	#define kHalfShortSize			8
	#define kWordSize				16
	#define kWordMask				0x0f
	#define kByteSize				8
	#define kHighByteMask			((unsigned long) 0xff00)
	#define kHighBit				((unsigned long) 0x80000000)
	#define kHighNybble 			((unsigned long) 0xf0000000)
	#define kHighByte 				((unsigned long) 0xff000000)
	#define kPositiveInfinity 		((Fixed) 0x7FFFFFFF)		/* for Fixed and Fract */
	#define kNegativeInfinity 		((Fixed) 0x80000000)	/* for Fixed and Fract */
	#define kShortPositiveInfinity 	((short) 0x7fff)
	#define kShortNegativeInfinity 	((short) 0x8000)
	#define kFixMask				0xffff0000

	#define ff(a)				((Fixed)(a) << 16)					/* int to Fixed 	*/
	#define fl(a)				((Fixed)((float)(a) * kFix1))			/* float to Fixed*/
	#define fi(a) 				((short)(((Fixed)(a) +kFixHalf) >> 16))	/* Fixed to int 	*/

	#define RORL(shift, value) 		(value) = (unsigned long) (value) >> (shift) | (value) << kLongSize - (shift)
	#define ROLL(shift, value) 		(value) = (value) << (shift) | (unsigned long) (value) >> kLongSize - (shift)

	#define sizeBits(count)			((count) + kLongSize - 1 >> kShiftBitsLong << kShiftBytesLong)

	#define LongAmount(a)  		(((a) + sizeof(long) - 1) >> kShiftBytesLong)	/* makes one-relative long count from a byte count */
	#define TruncEqual(a, b)		((((a) ^ (b)) & kFixMask) == 0)

	/*----- fixedMath.c -----*/

#ifdef __cplusplus
extern "C"
{
#endif

	Fixed FixedMultiply(Fixed, Fixed);
	Fixed FractMultiply(Fixed, Fixed);
	Fixed FixedMultiplyDivide(Fixed multiplier, Fixed dividend, Fixed divisor) ;
	Fixed FixedDivide(Fixed, Fixed);
	Fixed FractDivide(Fixed, Fixed);
	Fract FractSquareRoot(Fract);
	Fract FractSineCosine(Fixed degrees, Fract *cosine);
	Fract FractSquareRoot(Fract);

	Fixed FixedAtan2(Fixed x, Fixed y);		/* added by APG	*/


#ifdef __cplusplus
}
#endif

	#define	FixedConst(a,b) 	(((long)(a) << 16L) | (0x0000FFFF & (b)))
	#define FixedRound(a)		fi(a)
	#define Fixed2Fract(a)		((Fract)(a) << 14)
	#define Fixed2Long(a)		((long)fi(a))
	#define Long2Fixed(a)		ff(a)
	#define Fract2Fixed(a)		(((Fixed)(a) + 8192L) >> 14)
	#define FixedSqrt(a)		(((Fixed)FractSquareRoot(a) + 64) >> 7)
	#define FixedTrunc(a)		((short)((Fixed)(a) >> 16))
	#define FixedRatio(a,b)		FixedDivide(ff(a), ff(b))

	#define FixDiv			FixedDivide

#endif	// __FIXEDMATH_H
