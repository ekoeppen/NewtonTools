/*
	File:		UCErrors.h

	Copyright:	� 1993-1994 by Apple Computer, Inc., all rights reserved.

	Derived from v4 internal.

		WARNING:	this file is a global errors file and must be
					FRAMable.  please use caution when adding
					anything other than new errors!
*/

#ifndef	__UCERRORS_H
#define __UCERRORS_H

#ifndef __NEWTERRORS_H
#include "NewtErrors.h"
#endif


#define	UtilityErrorBase		(ERRBASE_UTILITYCLASSES)
#define AEventErrorBase			(ERRBASE_UTILITYCLASSES - 100)

// general utility class errors�
#define eNoError 				(noErr)
#define eNotImplemented			(UtilityErrorBase -1)
#define eNoMemory 				(UtilityErrorBase -2)
#define eBadPositionMode 		(UtilityErrorBase -3)
#define eAlreadyInited 			(UtilityErrorBase -4)
#define eBadSize 				(UtilityErrorBase -5)
#define eOverflow 				(UtilityErrorBase -6)
#define eUnderflow 				(UtilityErrorBase -7)
#define eRangeCheck 			(UtilityErrorBase -8)
#define eElementSizeMismatch 	(UtilityErrorBase -9)
#define eNotInitialized 		(UtilityErrorBase -10)
#define eNilPtr					(UtilityErrorBase -11)

// TAppWorld errors�
#define eNoHandler				(AEventErrorBase)


#endif
