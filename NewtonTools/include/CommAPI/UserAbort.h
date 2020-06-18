/*
	File:		UserAbort.h

	Contains:	Interface to the TUserAbortEvent and TUserAbortHandler objects

	Copyright:	� 1993, 1995 by Apple Computer, Inc., all rights reserved.

	Derived from v2 internal.

*/

#ifndef __USERABORT_H
#define __USERABORT_H

#ifndef __AEVENTHANDLER_H
#include <AEventHandler.h>
#endif

// in Newt:Main.c
extern NewtonErr InstallAbortHandler(ULong refCon, ULong eventID, NewtonErr result);
extern NewtonErr RemoveAbortHandler(ULong refCon);

#define kAEAbortID					'abrt'

//--------------------------------------------------------------------------------
//		TUserAbortEvent
//--------------------------------------------------------------------------------

class TUserAbortEvent : public TAEvent
{
public:

	TUserAbortEvent();

	NewtonErr			fResult;		// result code for the abort (usually kError_Call_Aborted)
	ULong				fRefCon;		// client refCon (TUserAbortHandler*)
};



#endif __USERABORT_H
