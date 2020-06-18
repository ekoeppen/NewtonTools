/*
	File:		LongTime.h

	Copyright:	� 1992-1994 by Apple Computer, Inc., all rights reserved.

	Derived from v30 internal.

*/

#ifndef	__LONGTIME_H
#define	__LONGTIME_H
#define	__LongTime_H	/* obsolete */

#ifndef	__NEWTON_H
#include "Newton.h"
#endif

typedef long(*InterruptHandler)(void*);

// the public interface for the real time clock

class TURealTimeAlarm
{
	public:
		// this routine initalizes the TURealTimeAlarm object for a unique "channel" specified by the
		// "name" argument. This call reserves a slot in the timer table for the caller.
		static long	CheckIn(ULong name);

		// this routine is called when the caller is finished using the real time clock
		static long	CheckOut(ULong name);

		// this routine sets the alarm on a channel. If an alarm already exists on this channel,
		// it will be discarded
		static long	SetAlarm(ULong name, TTime time, TObjectId port, TObjectId message, void* obj, long sizeOfObj, ULong type);

		// this routine sets the alarm on a channel. If an alarm already exists on this channel,
		// it will be discarded. It fires off an interrupt handler when the alarm fires,
		// rather than a message
		static long	SetAlarm(ULong name, TTime time, InterruptHandler DirectHandler, void* obj, ULong WakeUp=true, ULong IsRelative=false);

		// this routine clears any pending alarm on a channel
		static long	ClearAlarm(ULong name);

		// this routine provides status on a channel. It indicates if it is active, and if so
		// when it is scheduled to go off. If it is not active, "error" indicates the last
		// error value. Error is initialized to noErr and is cleared by ClearAlarm and SetAlarm
		static long	AlarmStatus(ULong name, Boolean* active, TTime* alarmTime, long* error);

		// This static routine returns the current real time clock value.
		static TTime	Time();

		// this routine sets the real time clock
		static void		SetTime(TTime time);

		// this routine returns a new alarm name, and registers it
		static long	NewName(ULong* name);
};

#endif
