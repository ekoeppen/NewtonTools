/*
	File:		NewtonTypes.h

	Contains:	Global types for Newton build system

	Copyright:	� 1992-1996 by Apple Computer, Inc.  All rights reserved.

	Derived from v17 internal.

*/

#ifndef __NEWTONTYPES_H
#define __NEWTONTYPES_H

#ifndef __CONFIGGLOBAL_H
#include "ConfigGlobal.h"
#endif

#if defined(__cplusplus) && defined(applec)
	// MPW CFront has a bug
	#define CALLVIRTUALDESTRUCTOR(obj, cl) (((cl*)obj)->cl::~cl())
#else
	#define CALLVIRTUALDESTRUCTOR(obj, cl) (((cl*)obj)->~cl())
#endif

#if defined(__cplusplus) && !defined(SINGLEOBJECT)

	#if defined(__SC__) || !defined(applec)

		/* non-MPW CFront compilers (e.g. DOS) need this so our classes will compile */
		class SingleObject {};

		#define SINGLEOBJECT /* nothing */

	#else

		#define SINGLEOBJECT : public SingleObject

	#endif

#endif


/* If we haven't already done so, pull in stddef.h for size_t */

#ifndef __stddef_h
#include "stddef.h"
#endif


/* Base types */

#ifndef __boolean_defined__
	typedef unsigned char	Boolean;
#endif

typedef char			Char;			/* In ARM6 C compiler char is unsigned char */
typedef signed char		SChar;
typedef unsigned char 	UChar;

#ifndef __byte_defined__
	typedef signed char		Byte;
#endif

typedef signed char		SByte;
typedef unsigned char	UByte;

typedef short			Short;			/* In ANSI C short is signed short */
typedef signed short	SShort;
typedef unsigned short	UShort;

typedef long			Long;			/* In ANSI C long is signed long */
typedef signed long		SLong;
typedef unsigned long	ULong;

typedef signed long		FastInt;

#define FASTINT_MIN		(~0x7fffffff)	/* -2147483648 and 0x80000000 are unsigned */
    									/* minimum value for an object of type FastInt */
#define	FASTINT_MAX		0x7FFFFFFF		/* maximum value for an object of type FastInt */

#ifndef __unichar_defined__
	typedef unsigned short	UniChar;
#endif


typedef UniChar			Character;


/* Pointer types */
#ifndef __ptr_defined__
	typedef char*			Ptr;
#endif

#ifndef __handle_defined__
	typedef Ptr*			Handle;
#endif

#ifndef __procptr_defined__
	typedef long			(*ProcPtr)();
#endif


typedef long NewtonErr;		/* needs to hold error codes less than -32767 */


/* Math types */

typedef struct Int64
{
	SLong	hi;
	ULong	lo;
} Int64;


#ifndef __fixed_defined__
	typedef long Fixed;
#endif

#ifndef __fract_defined__
	typedef long Fract;
#endif


/* Graphics types */

#ifndef __point_defined__
	struct Point
	{
		short 	v;
		short 	h;
	};
	typedef struct Point Point;
#endif

#ifndef __rect_defined__
	struct Rect
	{
		short	top;
		short	left;
		short	bottom;
		short	right;
	};
	typedef struct Rect Rect;
#endif


struct FPoint
{
	Fixed 	x;
	Fixed	y;
};
typedef struct FPoint FPoint;


struct FRect
{
	Fixed	left;
	Fixed	top;
	Fixed	right;
	Fixed	bottom;
};
typedef struct FRect FRect;


/* Constants */

#ifndef nil
	#define nil		NULL
#endif


#ifndef __boolean_defined__
 #if !defined(__arm) || !defined(__cplusplus) /* false and true are now C++ keywords */
 	#if defined(__arm) /* ARM C compiler warns about using the tokens 'false' and 'true' so hide them */
 		#define false false_
 		#define true true_
	#endif
	enum { false, true };
 #endif
#endif


/* Newton memory architecture types */
typedef ULong	VAddr;
typedef ULong	PAddr;
typedef ULong	LAddr;

/* Newton OS types */
typedef ULong	TObjectId;
typedef ULong	HammerIORef;

#endif /* __NEWTONTYPES_H */
