/*
	File:		ConfigCommunications.h

	Contains:	Configuration control of the Communications subsystem. This
				controls which tools are built, and the level of debugging
				code used in building those tools.

				This include file should only be included by Communications
				subsytem files. It is in the global includes since the
				configuration of the subsytem is public (e.g., it makes sense to
				build LocalTalk only if you're also building AppleTalk).

				[Currently HAL files include this as well...]

	Copyright:	� 1993-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v14 internal.

*/


#ifndef __CONFIGCOMMUNICATIONS_H
#define __CONFIGCOMMUNICATIONS_H

#ifndef __CONFIGGLOBAL_H
#include "ConfigGlobal.h"
#endif

#ifndef	__NEWTON_H
#include "Newton.h"
#endif

//--------------------------------------------------------------------------------
//	Tracing Control
//
//  Do some basic level of tracing for debug builds, but try not to use more
//  than 5K or so of ROM, and 1K of RAM. To keep it small, we turn off
//	tracing for less-used tools, and do only basic tracing in the tools
// 	we do trace. Turning on full tracing will add tracing for all tools, and do
//	more complete tracing in each tool; this is turned on by default if you define
// 	"hasTracing" in your build environment (MyNewtCOptions).
//
//	If hasFullCommTracing is defined, hasBasicCommTracing should also be defined!
//
//	NOTE: Tracing for comm tools typically depends upon traceCommTool being defined
//		since the TCommTool superclass (superclass of all comm tools) defines the
//		trace buffer used by subclasses. See "CommTool.h" for more info on tracing
//		in comm tools.
//--------------------------------------------------------------------------------

#if defined(forDebug)
	// for now, in debug builds, turn on basic tacing
	#define hasBasicCommTracing		(1)
#endif

#if defined(forDebug) && defined(hasTracing)
	#define hasFullCommTracing		(1)
	// if hasFullCommTracing is defined, hasBasicCommTracing must be defined
	#define hasBasicCommTracing		(1)
	// doCommEventTracing should go away, replaced by "traceXXXXTool, hasBasicCommTracing
	// and hasFullCommTracing
	#define doCommEventTracing		(1)		/* obsolete */
#endif // defined(hasTracing)


#if defined(hasBasicCommTracing)
	#define traceCommTool 			(1)
	#define traceSerialTool 		(1)
	#define traceModemTool			(1)
	#define traceFaxTool			(1)
	#define traceMNPTool			(1)
#endif

#if defined(hasFullCommTracing)
	#define traceLocalTalkTool 		(1)
	#define traceKeyboardTool 		(1)
	#define traceSharpIRTool 		(1)
	#define traceSniffIRTool 		(1)
	#define traceTVRemoteIRTool 	(1)
	#define traceMNPTool			(1)
	#define traceIrDATool			(1)
	#define traceIrProbeTool		(1)
#endif


//--------------------------------------------------------------------------------
// 	Define availability of tools...
//
//	Note that some tools will imply other tools. E.g., the MNPTool requires the
//  AsyncSerTool (as do many others)... This dependency should be shown here...
//
//--------------------------------------------------------------------------------

#if defined(hasRunt) || defined(hasBrick) || defined(hasVoyager)
	#define hasLocalTalk 			(1)
	#define hasTVRemoteIRTool		(1)
	#define hasTSharpIRTool			(1)
	#define hasTSniffIRTool			(1)
	#define hasTIrProbeTool			(1)
	#define hasTKeyboardTool		(1)
#endif

#if defined(hasRunt) || defined(hasBrick)
  // If IrDA is already specified (for debugging on bunwarmers), compile them to use external IR port
  #if defined(hasTIrDATool)
	#define useExternalPortForIR	(1)
  #endif
#else
	// Include IrDA for systems with IR that supports it.
	#define hasTIrDATool			(1)
#endif

/* If useSmallV42CompressBuffers is defined, the V.42bis compression
** buffer decreases from 28k to 14k
*/
#define useSmallV42CompressBuffers		(1)


#endif
