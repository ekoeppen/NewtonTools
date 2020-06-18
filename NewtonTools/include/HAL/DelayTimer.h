/*
	File:		DelayTimer.h

	Contains:	DelayTimer implements a fast timer polling service based on the timer0
				free-running timer. Also includes a useful global routine for
				one-shot delays...

	Copyright:	� 1992-1997 by Apple Computer, Inc., all rights reserved.
	
	Derived from v2 (11/18/94) internal

	Notes:

				UNLESS YOU ARE IN THE ROM, use ConvertToHardwareTime() to generate values
				to pass to the delay routines. This will ensure that you continue to
				work on future platforms (like Voyager-based Newton's) where the hardware
				time base is different.

				Use only for short delays (remember, no polling!).

				Polled timer handling routines. 2 varieties of timer routines are provided:

				1. Busy wait a specified time: call ShortTimerDelay.

				2. Busy wait while looking for some event (e.g., waiting for some SCC register bit to
				   change. Call ResetTimeOut at the start, then call TimedOut as needed to see if the
				   time has expired. Right now this kind of call can't be nested: it would be easy to
				   support nested calls: the caller would simply be responsible for remembering the start
				   time and delay, and passing these to the routine (could be an object).

				The timeout routines are typically called with interrupts disabled! Timing will be less
					exact, otherwise...

*/


#ifndef __DELAYTIMER_H
#define	__DELAYTIMER_H



typedef signed long	FastBoolean;
extern void ShortTimerDelay(THardwareTimeUnits delay);	// pass delay in HardwareTimeUnits


class TDelayTimer : private SingleObject {

public:
						TDelayTimer();

	// 	Conversion routines between TTimeout's and THardwareTimeUnits's. This class
	//   uses THardwareTimeUnits to be fast; the client can use ConvertToHardwareTime
	//   in an initialization routine to create various hardware time value constants
	//	 to be used later. Conversely, if GetHardwareTime() is used in a time-critical
	//   situation (e.g., performance monitors), ConvertFromHardwareTime can be
	//   used later to translate into platform-independent times. These routines can
	//   also be used to generate factors to do your own conversion: e.g.,
	//	 (1*kMilliseconds)/ConvertToHardwareTime(1*kMilliseconds) is the factor to multiply
	//   THardwareTimeUnits's by to get TTimeout's.
	//
	THardwareTimeUnits 	ConvertToHardwareTime(TTimeout time);
	TTimeout 			ConvertFromHardwareTime(THardwareTimeUnits time);
	THardwareTimeUnits 	GetHardwareTime();

	//  ShortTimerDelay is the same as ShortTimerDelay above...

	void 				ShortTimerDelay(THardwareTimeUnits delay); // delay in busy wait loop. Try to avoid this!

	//  ResetTimeOut is used in conjunction with ShortTimerDelayUntil and TimedOut,  to implement
	//	short wait loops on the order of 100 usec or so (e.g., waiting for the serial transmit
	//	register to empty). For short absolute delays (not waiting on something), use ShortTimerDelay above.

	void 				ResetTimeOut(THardwareTimeUnits delay);

	void 				ShortTimerDelayUntil(THardwareTimeUnits delay);
	FastBoolean			TimedOut(THardwareTimeUnits delay);
	FastBoolean			TimedOut();

private:

	// polling timer data...
	THardwareTimeUnits	fTimeOutStart;				// used for ResetTimeOut/TimedOut timer
	THardwareTimeUnits	fTimeOutDelay;				// used for ResetTimeOut/TimedOut timer
	volatile ULong * 	fTimerCounterReg;			// cache pointer to timer0 for faster response

};

#endif
