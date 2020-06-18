/*
	File:		NewtonDebug.h

	Contains:	Debug gear for Newton DDK build system

	Written by:	The Newton Tools group

	Copyright:	� 1992-1995 by Apple Computer, Inc.  All rights reserved.

*/

// NOTE:  This external file was created from version <13> of the internal file 

#ifndef __NEWTONDEBUG_H
#define __NEWTONDEBUG_H

#ifndef __NEWTONTYPES_H
#include "NewtonTypes.h"
#endif

#ifndef __NEWTONEXCEPTIONS_H
#include "NewtonExceptions.h"
#endif

#ifndef __NEWTONMEMORY_H
#include "NewtonMemory.h"
#endif

#ifndef __STDIO_H
#include "stdio.h"
#endif



/*
	... could ... for "standard" C/C++ support

	#ifdef NDEBUG
	#undef forDebug
	#endif

	#ifdef DEBUG
	#define forDebug 1
	#endif
*/

#undef Debugger
#undef DebugStr
#undef DebugCStr


#ifdef forDebug

	#ifdef __cplusplus
	extern "C" {
	#endif

	extern void Debugger(void);
	extern void DebugStr(const char*);
	#define DebugCStr(s) DebugStr(s)
		
	extern int printf(const char* format,...);
	
	/* PRINTF arguments must be passed inside ( ) 		*/
	/* for example PRINTF(("formatstring",...));    	*/
	
	#define PRINTF(args) printf(args)	

	#ifdef __cplusplus
	}
	#endif

#else

	#define Debugger() ((void) 0)
	#define DebugStr(msg) ((void) 0)
	#define DebugCStr(msg) ((void) 0)
	#define PRINTF(args) { }

#endif


//--------------------------------------------------------------------------------
//		Exception Macros
//--------------------------------------------------------------------------------

#define	THROWIF(result, exception)			do { if (result) Throw((exception), (void*) (result)); } while (0)
#define	THROWNOT(expr, exception, result)	do { if (!(expr)) Throw((exception), (void*) (result)); } while (0)

/*
	...
	
	The flag "debugLevel" is always defined by this file.
	Your code can use "#if" or even "if" instead of "#ifdef"

	debugLevel controls how much debugging gear is enabled:
		debugLevel = 0: no gear is enabled
		debugLevel = 1: minimum gear is enabled
		...

	debugLevel's value is set based on whether forDebug is defined.
	If forDebug is not defined, debugLevel is defined to be 0 (none)
	If forDebug is defined, debugLevel is defined to be 1 (minimum)

	You can override the default settings for debugLevel by defining
	debugLevel before including this file, or in your local compiler
	option line.
*/

#ifndef debugLevel
	#ifdef forDebug
		#define debugLevel 1
	#else
		#define debugLevel 0
	#endif
#endif

// ok to use #if, since debugLevel is always defined

#if debugLevel == 0

//--------------------------------------------------------------------------------
//		No Debugging Gear
//--------------------------------------------------------------------------------

	#define XSETPTRNAME(p,n)		((void)0)
	#define XSETHANDLENAME(h,n)		((void)0)

	#define XDEBUGSTR(msg)			((void)0)
	#define XBLOCKDEBUGPRINT(args)	{ }
	#define XDEBUGPRINT(args)		((void)0)

	#define XBLOCKPRINT(args)		{ }
	#define XPRINT(args)			((void)0)
	#define XPRINTIF(expr, args)	((void)0)

	#define XBLOCKFPRINT(args)		{ }
	#define XFPRINT(args)			((void)0)
	#define XFPRINTIF(expr, args)	((void)0)

	#define XBLOCKASSERTPRINT(expr, args)	((void) 0)
	#define XASSERTPRINT(expr, args)		((void) 0)

	#define XASSERT(expr)			((void)0)
	#define XASSERTNOT(expr)		((void)0)

	#define ASSERTMSG(expr, msg)	((void) 0)
	#define ASSERTTHROW(expr)		((void) 0)

	#define XREQUIRE(expr, label)		do { if (!(expr)) goto label; } while (0)
	#define XREQUIRENOT(expr, label)	do { if (expr) goto label; } while (0)

	#define XREQUIRE_ACTION(expr, label, action)		do { if (!(expr)) { { action } goto label; } } while (0)
	#define XREQUIRENOT_ACTION(expr, label, action)		do { if (expr) { { action } goto label; } } while (0)

	#define	THROWERROR(result, msg)				THROWIF(result, exNewtException)
	#define	THROWNIL(expr, result, msg)			do { if (!(expr)) Throw(exNewtException, (void*) (result)); } while (0)

#elif debugLevel == 1

//--------------------------------------------------------------------------------
//		Minimum Debugging Gear
//--------------------------------------------------------------------------------

	// globals ...
	// defined ...



#ifdef forARM
	#define XSETPTRNAME(p,n)		SetPtrName((Ptr) (p), (ULong) (n))
#endif

	#define	XDEBUGSTR(msg)			Debugger()
	#define XBLOCKDEBUGPRINT(args)	{ }
	#define XDEBUGPRINT(args)		Debugger()

	#define XBLOCKPRINT(args)		{ }
	#define XPRINT(args)			((void)0)
	#define XPRINTIF(expr, args)	((void)0)

	#define XBLOCKFPRINT(args)		{ }
	#define XFPRINT(args)			((void)0)
	#define XFPRINTIF(expr, args)	((void)0)

	#define XBLOCKASSERTPRINT(expr, args)	do { if (!(expr)) DebugCStr("ASSERTPRINT(" #expr ") failed"); } while (0)
	#define XASSERTPRINT(expr, args)		do { if (!(expr)) DebugCStr("ASSERTPRINT(" #expr ") failed"); } while (0)

	#define XASSERT(expr)			do { if (!(expr)) DebugCStr("XASSERT(" #expr ") failed"); } while (0)
	#define XASSERTNOT(expr)		do { if (expr) DebugCStr("XASSERTNOT(" #expr ") failed"); } while (0)

	#define ASSERTMSG(expr, msg)	do { if (!(expr)) ThrowMsg("ASSERTMSG(" #expr ") failed"); } while (0)
	#define	ASSERTTHROW(expr)		do { if (!(expr)) ThrowMsg("ASSERTMSG(" #expr ") failed"); } while (0)


	#define XREQUIRE(expr, label) \
				do { \
					if (!(expr)) { \
						DebugCStr("XREQUIRE(" #expr ", " #label ") failed"); \
						goto label; \
					} \
				} while (0)

	#define XREQUIRENOT(expr, label) \
				do { \
					if (expr) { \
						DebugCStr("XREQUIRENOT(" #expr ", " #label ") failed"); \
						goto label; \
					} \
				} while (0)

	#define XREQUIRE_ACTION(expr, label, action) \
				do { \
					if (!(expr)) { \
						DebugCStr("XREQUIRE_ACTION(" #expr ", " #label ", " #action ") failed"); \
						{ action } \
						goto label; \
					} \
				} while (0)

	#define XREQUIRENOT_ACTION(expr, label, action) \
				do { \
					if (expr) { \
						DebugCStr("XREQUIRENOT_ACTION(" #expr ", " #label ", " #action ") failed"); \
						{ action } \
						goto label; \
					} \
				} while (0)

	#define	THROWERROR(result, msg)				THROWIF(result, exNewtException)
	#define	THROWNIL(expr, result, msg)			do { if (!(expr)) Throw(exNewtException, (void*) (result)); } while (0)

#endif /* debugLevel */

//--------------------------------------------------------------------------------
//		Variants of XREQUIRE et al.
//--------------------------------------------------------------------------------

/************************************************
 *	OSErr f()
 *	{
 *		OSErr err = noErr;
 *
 *		XTRY
 *		{
 *			err = g();
 *			XFAIL(err);
 *
 *			int y = g();
 *			XFAILIF( y, err = kError; );
 *
 *			char* x = malloc(64);
 *			XFAILNOT( x, err = MemError(); );
 *		}
 *		XENDTRY;
 *
 *		XDOFAIL(err)
 *		{
 *			// failure cleanup
 *		}
 *		XENDFAIL;
 *
 *		return err;
 *	}
 ************************************************
 */

#define XTRY							do
#define XENDTRY  						while(0)

#define XDOFAIL(expr)					if (expr) do
#define XENDFAIL						while(0)

#define XFAIL(expr)						{ if (expr) { break; } }
#define XFAILIF(expr, action)			{ if (expr) { { action } break; } }
#define XFAILNOT(expr, action)			{ if (!(expr)) { { action } break; } }

//--------------------------------------------------------------------------------
//		Equivalent expressions for compatibility
//--------------------------------------------------------------------------------

#define	PRINT XPRINT
#define	ASSERTPRINT XASSERTPRINT
#define DEBUGPTRNAME XSETPTRNAME
#define DEBUGHANDLENAME XSETHANDLENAME
#define	ASSERTNOERROR XASSERTNOT
#define	XASSERTNIL XASSERTNOT
#define	XREQUIRENIL XREQUIRENOT
#define CHECK ASSERTMSG
#define DebugString DebugCStr
#define	BLOCKASSERT XASSERT
#define	assert XASSERT
#define	DASSERT XASSERT
#define	DPRINT XPRINT
#define	PRINTIF XPRINTIF
#define	DBGASSERT XASSERT
#define	XDEBUGGER XDEBUGSTR
#define	DEBUGGER XDEBUGSTR

#define ASSERT XASSERT

#endif /* __NEWTONDEBUG_H */

