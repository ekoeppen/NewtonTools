/*
	File:		ConfigOS600.h

	Copyright:	� 1993-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v18 internal.

*/


#ifndef __CONFIGOS600_H
#define __CONFIGOS600_H

#ifndef __CONFIGGLOBAL_H
#include "ConfigGlobal.h"
#endif

#ifdef forNewt
	#define	hasSkiaMemMgr 1
#endif


#ifdef forDebug

#define doTaskSwitchEvents 1
		// #define doTaskSwitchEvents to get task switch tracing.  Builds a THistoryCollector
		// for the task name and time of the switch


#else

#endif // forDebug

//
// Define hasPatchableJumpTable because all platforms support patchable jump tables
#define hasPatchableJumpTable 1

#ifdef hasCirrus
#define hasNewKernelMemoryMap

#define useHALAtomicCode 1

// Define this if you want patching
#define hasPatching 1
#endif

#ifndef __NEWTON_H
#include "Newton.h"
#endif

// OSBUG section
#ifdef OSBUG
// this stuff lives in profile.c
void dbgOSInitializeDebug();
void dbgOSMemoryStats(char* comment);
void dbgOSPrint(char* fmt, ...);
void dbgOSDump();

#define DBGOSINIT()						dbgOSInitializeDebug()
#define DBGOSPRINT(args)				dbgOSPrint args
#define DBGOSMEMORYSTATS(comment)		dbgOSMemoryStats(comment)
#define DBGOSDUMP()						dbgOSDump()

#else

#define DBGOSINIT()
#define DBGOSPRINT(args)
#define DBGOSMEMORYSTATS(comment)
#define DBGOSDUMP()

#endif // OSBUG

#endif
