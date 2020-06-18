/*
	File:		TimerQueue.h

	Contains:	Interface to the TTimerQueue class

	Copyright:	� 1994-1995 by Apple Computer, Inc.  All rights reserved.

	Derived from v6 internal.

*/

#ifndef __TIMERQUEUE_H
#define __TIMERQUEUE_H

#ifndef __LONGTIME_H
#include <LongTime.h>
#endif

#ifndef __USERPORTS_H
#include <UserPorts.h>
#endif


class TTimerElement;
class TTimerQueue;


//--------------------------------------------------------------------------------
//		TTimerElement
//--------------------------------------------------------------------------------
class TTimerElement : public SingleObject
{
public:

						TTimerElement(TTimerQueue* q, ULong refCon);
		virtual			~TTimerElement();

				Boolean	IsPrimed(void);

				Boolean	Prime(TTimeout delta);
				Boolean	Cancel(void);

		virtual	void	Timeout(void) = 0;

				ULong	GetRefCon(void)			{ return fRefCon; };
				void	SetRefCon(ULong refCon)	{ fRefCon = refCon; };

#ifdef debugTimers
	void Dump(void);
#endif

private:

		friend class TTimerQueue;

		TTimerQueue*		fQueue;
		TTimerElement*		fNext;
		TTimeout			fDelta;
		ULong				fRefCon;
		Boolean				fPrimed;

}; // TTimerElement


//--------------------------------------------------------------------------------
//		TTimerQueue
//--------------------------------------------------------------------------------
class TTimerQueue : public SingleObject
{
public:

				TTimerQueue();
				~TTimerQueue();

				TTimeout			Check(void);
				Boolean				IsEmpty(void);

				TTimerElement*		Cancel(ULong refCon);

#ifdef debugTimers
	void Dump(void);
#endif

private:

		friend class TTimerElement;

				TTimerElement*		Enqueue(TTimerElement* item);
				TTimerElement*		Dequeue(TTimerElement* item, Boolean adjust);

				void				Calibrate(void);

		TTimerElement*	fHead;
		TTime			fLastCalibrate;
		Boolean			fTimeoutInProgress;

}; // TTimerQueue


//--------------------------------------------------------------------------------
//		TTimerPort
//--------------------------------------------------------------------------------
class TTimerPort : public TUPort
{
public:

				TTimerPort();
				~TTimerPort();

		NewtonErr	Init(void);

		NewtonErr	TimedReceive(	ULong* returnSize,
									void* content,
									ULong size,
									TUMsgToken* token = nil,
									ULong* returnMsgType = nil,
									ULong msgFilter = kMsgType_MatchAll,
									Boolean onMsgAvail = false,
									Boolean tokenOnly = false);

		TTimerQueue*	GetQueue(void);

private:

		TTimerQueue*	fQueue;

}; // TTimerQueue


//--------------------------------------------------------------------------------
//		inlines
//--------------------------------------------------------------------------------

inline Boolean TTimerElement::IsPrimed(void)
	{ return fPrimed; }

inline Boolean TTimerQueue::IsEmpty(void)
	{ return (fHead == nil); }

inline TTimerQueue* TTimerPort::GetQueue(void)
	{ return fQueue; }

#endif	/*	__TIMERQUEUE_H	*/
