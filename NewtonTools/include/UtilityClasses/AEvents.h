/*
	File:		AEvents.h

	Contains:	implementation of main interface calls

	Copyright:	� 1992-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v26 internal.

*/

#ifndef __AEVENTS_H
#define	__AEVENTS_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef __ITEMCOMPARER_H
#include "ItemComparer.h"
#endif


typedef unsigned long AEEventClass;
typedef unsigned long AEEventID;

#define kTypeWildCard 				'****'



#define kMAXEVENTSIZE	(256)

/* -------------------------------------------------------------------------------------------------------------------- */

//			NEWTON specific follows...


// ADD YOUR TYPES HERE  (please use all lower case)

#define kNewtEventClass				'newt'
#define kAESystemEventID			'sysm'
#define kAETimerEventID				'timr'

//  System Message id�
#define kAESystemMessageID			'sysm'

//  Debugger�
#define kAEDebuggerID				'dbug'

//  AppleTalk ids�
#define kAEAppleTalkID				'atlk'
#define kAEAppleTalkPAPID			'pap '
#define kAEAppleTalkATPID			'atp '
#define kAEAppleTalkADSPID			'adsp'
#define kAEAppleTalkDDPID			'ddp '
#define kAEAppleTalkLAPID			'lap '
#define kAEAppleTalkRTMPID			'rtmp'
#define kAEAppleTalkAEPID			'aep '
#define kAEAppleTalkNBPID			'nbp '

//  Communications Manager�
#define kAECommManagerID			'comg'

//  TCommTool's
#define kAECommToolID				'comt'

//	inker event
#define	kInkerEventID				'inkr'

//  card server event
#define kAECardServerID				'cdsv'
#define kAECardServerClientID		'cdcl'
#define kAECardServerUIID			'cdui'

// sound server event
#define kSndEventId 				'snde'

// kAEEndpointId  event
#define kAEEndpointID				'endp'

// package manager ID
#define kPackageEventId			 	'pckm'


/* -------------------------------------------------------------------------------------------------------------------- */




/* --------------------------------------------------------------------------------------------------------------------
					TAEvent

		Base event type in the Newt system from which all others are
		derived.  All events (messages) should be subclassed from
		TAEvent.  (No virtuals allowed).

   -------------------------------------------------------------------------------------------------------------------- */

class TAEvent : public SingleObject
{
	public:
						TAEvent();

		AEEventClass 	fAEventClass;
		AEEventID 		fAEventID;
};


/* --------------------------------------------------------------------------------------------------------------------
					TAESystemEvent
   -------------------------------------------------------------------------------------------------------------------- */

class TAESystemEvent : public TAEvent
{
	public:

						TAESystemEvent();
						TAESystemEvent(ULong type);

		ULong 			fSysEventType;

};


/* --------------------------------------------------------------------------------------------------------------------
					TPowerEvent
   -------------------------------------------------------------------------------------------------------------------- */

class TPowerEvent : public TAESystemEvent
{
	public:

						TPowerEvent();
						TPowerEvent(ULong type, ULong reason);

		ULong			fReason;
};



/* --------------------------------------------------------------------------------------------------------------------
					TAETimerEvent

		Event type for idle handlers.  Private to the idler implementation-
		do not subclass

   -------------------------------------------------------------------------------------------------------------------- */

class TAETimerEvent : public TAEvent
{
	public:
		ULong			fTimerID;
		ULong			fTimerRefCon;
};



//----------------------------------------------------------------------------------------
// TAEventComparer - compares TAEvent with a TAEventHandler.
//----------------------------------------------------------------------------------------

class TAEventComparer : public CItemComparer
{
	public:
							TAEventComparer();
	virtual CompareResult	TestItem(const void* testItem) const;
};



#endif /* __AEVENTS_H */
