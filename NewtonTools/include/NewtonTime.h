/*
	File:		NewtonTime.h

	Contains:	Timing gear for Newton build system

	Copyright:	� 1992-1995 by Apple Computer, Inc.  All rights reserved.

	Derived from v14 internal.

*/

#ifndef __NEWTONTIME_H
#define __NEWTONTIME_H

#ifndef __NEWTONTYPES_H
#include "NewtonTypes.h"
#endif

#ifndef __COMPMATH_H
#include "CompMath.h"
#endif


enum
{
	kNoTimeout = 0,
	kTimeOutImmediate = -1
};



#define	firstPart	time.lo
#define	secondPart	time.hi


//
// NOTE: the maximum time that can be represented by a TTimeout is 14 minutes.
// If you need to compute a future time that is a greater amount into the future, you
// must use a TTime and apply your own conversion beyond minutes.  For example, if you
// wanted to get the time for one day you would:
// TTime oneDay(1*24*60,kMinutes). (1 day, 24 hours in a day, 60 minutes in an hour)
//

typedef ULong	TTimeout;
typedef ULong   THardwareTimeUnits;


ULong		RealClockSeconds(void);			// gets seconds based realtime clock
ULong		RealClock(void);				// gets minutes based realtime clock

#ifdef forARM

	// our base unit is 200ns
	// if the hardware is different, a conversion must be done

	/*
		Use TimeUnits enumeration to construct relative time values
		These enumerations would be the second argument to the TTime
		constructor that takes amount and units. For example a relative
		TTime object that is 10 seconds in length could be constructed as:

			TTime(10, kSeconds)

		Note that the send delayed call in ports takes an ABSOLUTE TTime
		object. Such an object is created by getting the absolute time
		from GetGlobalTime() + delta.
	*/

	#ifndef hasRunt			/* voyager systems (MP2000, eMate and later) */

		enum TimeUnits {
			kSystemTimeUnits = (1),							// to convert to (amount, units)
			kMicroseconds	= (4),							// clock ticks in a microsecond (3.6864Mhz clk)
			kMilliseconds	= (3686),
			kMacTicks		= (61440),						// for compatibility
			kSeconds		= (3686400),
			kMinutes		= (60*kSeconds)
		};

	#else					/* pre-voyager systems (130 and earlier) */

		enum TimeUnits {
			kSystemTimeUnits = (1),							// to convert to (amount, units)
			kMicroseconds	= (5),							// number of 200ns units in a microsecond
			kMilliseconds	= (1000*kMicroseconds),
			kMacTicks		= (16667*kMicroseconds),		// for compatibility
			kSeconds		= (1000*kMilliseconds),
			kMinutes		= (60*kSeconds)
		};

	#endif

	ULong		Ticks(void);						// gets tick count
	void		SetRealClock(ULong minutes);		// sets realtime clock minutes - since 1/1/04 12:00am
	void		SetRealClockSeconds(ULong seconds);	// sets realtime clock seconds - since 1/1/04 12:00am
	void		SleepTillTicks(ULong);				// sleeps until ticks passes
	void 		Wait(ULong);						// sleep for # ticks (�1/2 tick)

	//////////////////////////////////////////////////////////////////////////////////////
	//
	// 					TTime
	//
	// TTime's are used to represent moments in time.  For instance, if you want to send a
	// message a day from now, you find now and add in one day.
	//

	#ifdef applec
		// avoid bogus MPW CFront warning
		#define BOGUSNESS_FOR_CFRONT(x) (((TTime*)this)->x)
	#else
		#define BOGUSNESS_FOR_CFRONT(x) x
	#endif

	#ifdef __cplusplus

	#define PRESERVE_OLD_PUBLIC_JUMPTABLE_ENTRY_FOR_TTIME_CTOR 1

	class TTime {
		public:
			Int64	time;

			void 	Set(ULong low)					{ time.lo = low; time.hi = 0L; }
			void 	Set(ULong low, SLong high)		{ time.lo = low; time.hi = high; }
			void	Set(ULong amount, TimeUnits units);
				// on most compilers 'fMyTime.Set(x, y)' will be more effcient than
				// fMyTime = TTime(x, y) because the first won't use a temporary

					TTime()							{ }

			#ifndef ARM6C_DOESNT_NEED_THIS_ANYMORE
					TTime(const TTime &x)			{ time = x.time; };
			#endif

					TTime(ULong low)				{ Set(low); }
					TTime(ULong low, ULong high)	{ Set(low, SLong(high)); }
	#if PRESERVE_OLD_PUBLIC_JUMPTABLE_ENTRY_FOR_TTIME_CTOR
					TTime(ULong amount, TimeUnits units);
	#else
					TTime(ULong amount, TimeUnits units) { Set(amount, units); }
	#endif

			operator	ULong()	const				{ return time.lo; }

			TTime 	operator+ (const TTime& b)	{ TTime ret(b); CompAdd(&time, &ret.time); return ret; }
			TTime 	operator- (const TTime& b)	{ TTime ret(*this); CompSub(&b.time, &ret.time); return ret; }

			Boolean	operator<  (const TTime& b)	const	{ return CompCompare(&BOGUSNESS_FOR_CFRONT(time), &b.time) < 0; }
			Boolean	operator== (const TTime& b)	const	{ return CompCompare(&BOGUSNESS_FOR_CFRONT(time), &b.time) == 0; }
			Boolean	operator!= (const TTime& b)	const	{ return CompCompare(&BOGUSNESS_FOR_CFRONT(time), &b.time) != 0; }
			Boolean	operator>  (const TTime& b)	const	{ return CompCompare(&BOGUSNESS_FOR_CFRONT(time), &b.time) > 0; }

			Boolean	operator>=	(const TTime& b) const	{ return CompCompare(&BOGUSNESS_FOR_CFRONT(time), &b.time) >= 0; }
			Boolean	operator<=	(const TTime& b) const	{ return CompCompare(&BOGUSNESS_FOR_CFRONT(time), &b.time) <= 0; }

			ULong	ConvertTo(TimeUnits units);

			void	PrintObject(HammerIORef win, Boolean summary, int indent);
	};

	// GetGlobalTime -
	// returns a TTime moment representing the current time.
	extern "C" TTime	GetGlobalTime(void);

	// GetTaskTime -
	// returns a TTime duration representing the time spent in the specified task.
	extern "C" TTime	GetTaskTime(TObjectId timeForTaskId = 0);

	// TimeFromNow -
	// returns a TTime moment representing a time in the future.
	// NOTE: You can only specify a moment up to 14 minutes into the future
	// using this method.  If you need a longer distance into the future,
	// simply add the future TTime duration to the current time from GetGlobalTime.  For example,
	// TTime distantTime(
	extern "C" TTime	TimeFromNow(TTimeout deltaTime);

	ULong		TTimeToMilliseconds(TTime);

	#endif /* __cplusplus */


#elif defined(forWin32)

	enum TimeUnits {
		/* the base unit of time is a millesecond */
		kMilliseconds	= 1,
		kCentiseconds	= (10*kMilliseconds),
		kSeconds		= (1000*kMilliseconds),
		kMinutes		= (60*kSeconds),
		kHours			= (60*kMinutes),
		kDays			= (24*kHours),
		kFortnights		= (14*kDays)
	};

	#ifdef __cplusplus

	class TTime {
		public:
			Int64	time;

			void 	Set(ULong low)					{ time.lo = low; time.hi = 0L; }
			void 	Set(ULong low, SLong high)		{ time.lo = low; time.hi = high; }
			void	Set(ULong amount, TimeUnits units)	{ CompMul(amount, (ULong) units, &time); }

				// on most compilers 'fMyTime.Set(x, y)' will be more effcient than
				// fMyTime = TTime(x, y) because the first won't use a temporary

					TTime()							{ }
					TTime(ULong low)				{ Set(low); }
					TTime(ULong low, ULong high)	{ Set(low, SLong(high)); }
					TTime(ULong amount, TimeUnits units) { Set(amount, units); }

			operator	ULong()						{ return time.lo; }

			TTime 	operator+ (const TTime& b)	{ TTime ret(b); CompAdd(&time, &ret.time); return ret; }
			TTime 	operator- (const TTime& b)	{ TTime ret(*this); CompSub(&b.time, &ret.time); return ret; }

			Boolean	operator<	(const TTime& b)	{ return CompCompare(&time, &b.time) < 0; }
			Boolean	operator==	(const TTime& b)	{ return CompCompare(&time, &b.time) == 0; }
			Boolean	operator>	(const TTime& b)	{ return CompCompare(&time, &b.time) > 0; }

			Boolean	operator>=	(const TTime& b)	{ return CompCompare(&time, &b.time) >= 0; }
			Boolean	operator<=	(const TTime& b)	{ return CompCompare(&time, &b.time) <= 0; }

			long	Milliseconds(void);
	};

	#endif

	ULong		Ticks(void);
	long 		TickCount(void);
	void 		GetDateTime( unsigned long *secs );


#endif

#endif /* __NEWTONTIME_H */
