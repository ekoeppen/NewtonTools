/*
	File:		AEventHandler.h

	Contains:	TAEventHandler definition

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v18 internal.

*/

#ifndef __AEVENTHANDLER_H
#define	__AEVENTHANDLER_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef __ITEMCOMPARER_H
#include "ItemComparer.h"
#endif

#ifndef __AEVENTS_H
#include "AEvents.h"
#endif

#ifndef __TIMERQUEUE_H
#include "TimerQueue.h"
#endif

#ifndef __USERPORTS_H
#include "UserPorts.h"
#endif

class TAEventHandler;


/* --------------------------------------------------------------------------------------------------------------------
					TAEHandlerComparer
   -------------------------------------------------------------------------------------------------------------------- */

class TAEHandlerComparer : public CItemComparer
{
	public:
						TAEHandlerComparer();
		CompareResult	TestItem(const void* testItem) const;
};


typedef CItemComparer TAETimerComparer;


/* --------------------------------------------------------------------------------------------------------------------
					TAEIdleTimer
   -------------------------------------------------------------------------------------------------------------------- */

class TAEIdleTimer : public TTimerElement
{
	public:
						TAEIdleTimer(TTimerQueue* q, ULong refCon, TAEventHandler* handler, TTimeout idle);

		Boolean			Start(void);
		Boolean			Stop(void);
		Boolean			Reset(void);
		Boolean			Reset(TTimeout idle);

		void			Timeout(void);

private:

	TAEventHandler*		fHandler;
	TTimeout			fIdleTime;
};

inline Boolean TAEIdleTimer::Start()
	{ return Prime(fIdleTime); }

inline Boolean TAEIdleTimer::Stop()
	{ return Cancel(); }

inline Boolean TAEIdleTimer::Reset()
	{ return Cancel() && Prime(fIdleTime); }

inline Boolean TAEIdleTimer::Reset(TTimeout idle)
	{ fIdleTime = idle;  return Cancel() && Prime(idle); }


/* --------------------------------------------------------------------------------------------------------------------
					TAEventHandler
   -------------------------------------------------------------------------------------------------------------------- */

class TAEventHandler : public SingleObject
{
	public:
						TAEventHandler();
		virtual			~TAEventHandler();

		/*	initializes handler to specified eventID
			will now call AEHandlerProc for all events of this type
		*/
		NewtonErr		Init(AEEventID eventID, AEEventClass eventClass = kNewtEventClass);

		AEEventClass	GetEventClass(void) { return fEventClass; };
		AEEventID		GetEventID(void) { return fEventID; };

		void			DeferReply(void);											// Defer reply to message we just received.
		NewtonErr		ReplyImmed(void);											// Do an immediate reply.
		void			SetReply(ULong size, TAEvent* event);						// Set reply size and reply
		void			SetReply(TUMsgToken* token);								// Set reply message token
		void			SetReply(TUMsgToken* token, ULong size, TAEvent* event);	// Set all the reply parameters

		virtual	Boolean	AETestEvent(TAEvent* event);		// User supplied test of event - true if event is for this handler

		// User supplied handler routines

		virtual	void	AEHandlerProc(TUMsgToken* token, ULong* size, TAEvent* event);
		virtual	void	AECompletionProc(TUMsgToken* token, ULong* size, TAEvent* event);
		virtual	void	IdleProc(TUMsgToken* token, ULong* size, TAEvent* event);

		/* 	initializes idler for time specified
			will now call IdleProc
		*/
		NewtonErr		InitIdler(TTimeout idle, ULong refCon = 0,  Boolean start = true);
		NewtonErr		InitIdler(ULong idleAmount, TimeUnits idleUnits, ULong refCon = 0,  Boolean start = true);

		NewtonErr		StartIdle(void);			// start the timer
		NewtonErr		StopIdle(void);				// stop the timer
		NewtonErr		ResetIdle(void);							// stop the timer if running, start again, using original delay value
		NewtonErr		ResetIdle(ULong amount, TimeUnits units);	// stop the timer if running, and setup new values, start again
		NewtonErr		ResetIdle(TTimeout idle);					// stop the timer if running, and setup new values, start again

	private:

		friend class	TAEHandlerComparer;
		friend class	TAEventComparer;
		friend class	TAEHandlerIterator;
		friend class	TAppWorld;

		TAEventHandler*		AddHandler(TAEventHandler* headOfChain);
		// Adds SELF from the chain of handlers starting at headOfChain.

		TAEventHandler*		RemoveHandler(TAEventHandler* headOfChain);
		// Removes SELF from the chain of handlers starting at headOfChain. Returns the
        // new head of chain (if self was the head then there _must_ be a new head.

		NewtonErr			AEDoEvent(TUMsgToken* token, ULong* size, TAEvent* event);
		// Execute the event if it belongs to this handler
		// else pass it a long to the next handler

		void 				AEDoComplete(TUMsgToken* token, ULong* size, TAEvent* event);
		// Execute the event if it belongs to this handler
		// else pass it a long to the next handler

		TAEventHandler*		GetNextHandler(void);
		// Return the next handler in the chain

		TAEventHandler*		fNext;
		AEEventClass 		fEventClass;
		AEEventID 			fEventID;
		TAEIdleTimer*		fIdler;
};


/* --------------------------------------------------------------------------------------------------------------------
					TSystemEventHandler
   -------------------------------------------------------------------------------------------------------------------- */

class TSystemEventHandler : public TAEventHandler
{
	public:
						TSystemEventHandler();

		// call Init for each type of system event you're interested in�
		NewtonErr		Init(ULong systemEvent, ULong sendFilter = 0);

		// override to get all system events�
		virtual void	AnySystemEvents(TAEvent* event);

		// override to receive system events of their respective types�
		virtual void	PowerOn(TAEvent* event);
		virtual void	PowerOff(TAEvent* event);
		virtual void	NewCard(TAEvent* event);
		virtual void	AppAlive(TAEvent* event);
		virtual void	DeviceNotification(TAEvent* event);
		virtual void	PowerOffPending(TAEvent* event);

	private:

		void			AEHandlerProc(TUMsgToken* token, ULong*, TAEvent* event);
		Boolean			fInited;

};



/* --------------------------------------------------------------------------------------------------------------------
					TAEHandlerIterator
   -------------------------------------------------------------------------------------------------------------------- */

class TAEHandlerIterator : public SingleObject
{
public:
	TAEHandlerIterator(TAEventHandler* chainHead);

	Boolean More(void);
	// Returns TRUE if there are more elements to iterate over

	void Reset(void);
	// Resets the iterator to begin again

	TAEventHandler* CurrentHandler(void);
	// returns the current handler in the handler chain

	TAEventHandler* FirstHandler(void);
	// Resets the iterator to begin again and returns the first handler in the handler chain

	TAEventHandler* NextHandler(void);
	// returns the next handler in the handler chain

private:
	void Advance(void);
	// Advances the iteration

	TAEventHandler*	fFirstHandler;
	TAEventHandler*	fCurrentHandler;
	TAEventHandler*	fNextHandler;
};

//----------------------------------------------------------------------------------------
// CHandlerIterator: Inline method definitions.
//----------------------------------------------------------------------------------------

inline Boolean TAEHandlerIterator::More(void)
{
	return (fCurrentHandler != nil);
}

inline TAEventHandler* TAEHandlerIterator::CurrentHandler(void)
{
	return fCurrentHandler;
}

inline TAEventHandler* TAEHandlerIterator::FirstHandler(void)
{
	this->Reset();
	return fFirstHandler;
}

inline TAEventHandler* TAEHandlerIterator::NextHandler(void)
{
	this->Advance();
	return fCurrentHandler;
}


#endif // __AEVENTHANDLER_H
