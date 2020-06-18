/*
	File:		Newton.h

	Contains:	Newton C++ Tools errors, types, memory, and debug, widgets

	Written by:	The Newton Tools group

	Copyright:	� 1996 by Apple Computer, Inc.  All rights reserved.

*/

#ifndef __NEWTON_H
#define __NEWTON_H

//--------------------------------------------------------------------------------
//		Standard C/C++ includes
//--------------------------------------------------------------------------------

// malloc, free
#ifndef __STDLIB_H
#include "stdlib.h"
#endif

// memcpy, memmove
#ifndef __STRING_H
#include "string.h"
#endif

// __size_t et al.
#ifndef __STDDEF_H
#include "stddef.h"
#endif

//--------------------------------------------------------------------------------
//		Platform includes
//--------------------------------------------------------------------------------

#ifdef forARM
#define hasUnicode 1
#endif

#ifndef __NEWTONTYPES_H
#include "NewtonTypes.h"
#endif

#ifndef __NEWTONWIDGETS_H
#include "NewtonWidgets.h"
#endif

#ifndef __NEWTONMEMORY_H
#include "NewtonMemory.h"
#endif

#ifndef __NEWTONEXCEPTIONS_H
#include "NewtonExceptions.h"
#endif

#ifndef __NEWTONDEBUG_H
#include "NewtonDebug.h"
#endif

#ifndef __NEWTONERRORS_H
#include "NewtonErrors.h"
#endif

#ifndef __NEWTONTIME_H
#include "NewtonTime.h"
#endif

#endif	/* __NEWTON_H */
