/*
	File:		HammerIO.h

	Contains:	Interfaces for hammer io.

	Copyright:	� 1993-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v10 internal.

*/

#ifndef __HAMMERIO_H
#define __HAMMERIO_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#include "stdio.h"

#ifndef __KERNELTYPES_H
#include "KernelTypes.h"
#endif

// do a printf to hammer during a break (useful for object browsing)
extern void dfprintf(HammerIORef ref, char* fmt, ...);

#ifdef __cplusplus
extern "C" {
#endif

void ObjectBrowser(HammerIORef win, char* browseStr);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C" {
#endif

void SWITraceCaptureStart(ULong r0, ULong swiNum);
void SWITraceCaptureEnd();

#ifdef __cplusplus
}
#endif

long SWITraceInit(ULong maxNum);
long SWITraceParse(HammerIORef ref, char* line);

void RegisterPackageWithDebugger(void* virtAddr, ULong key);
/*
			Makes Hammer, if present, know about the package identified by the key.
*/

void RegisterLoadedCodeWithDebugger(void* virtAddr, const char* name, ULong key);
/*
			This call will do nothing unless a debugger is present.  Hammer will use the
			name to load the symbols and then resume the image (unless the CapsLock key is
			down).  The virtAddr must be the virtual address of the first byte of the
			image produced by the linker.  For protocols the name is the implementation name
			for frame (or raw?) parts the name is the part info.  The name must be faulted in.
			The key is used to remove the symbols.  Multiple calls to RegisterPackageCodeWithDebugger
			may use the same key.
*/

void DeregisterLoadedCodeWithDebugger( ULong key);
/*
			Makes Hammer, if present, forget about the package symbols that were
			registered with key.
*/

void InformDebuggerMemoryReloaded(void* virtAddr, ULong size);

/*
			Lets Hammer, if present, reinstall breakpoints in the memory range given.
*/


#endif
