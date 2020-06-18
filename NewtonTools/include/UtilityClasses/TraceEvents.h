/*
	File:		TraceEvents.h

	Copyright:	� 1994-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v8 internal.

*/

#ifndef __TRACEEVENTS_H
#define __TRACEEVENTS_H

#ifndef __PROTOCOLS_H
#include "Protocols.h"
#endif

#define kTHistoryCollector	"THistoryCollector"

extern "C"	{
	void AsmTraceAddAddrEvent(char* eventLoc);			// saves cur time and link reg at *eventLoc (8 bytes)
}

const size_t kDefaultNumberOfEntries = 50;

typedef enum {eDontCollect = 0, eResetCollect = 1, eDoCollect = 2} EEventCollectorControl;
typedef enum {eNormalBuffer, eLockedBuffer, eWiredBuffer}  EBufferResidence; // 1275136

// The following structure is for associating a descriptive string
// for the event types.  If an array is provided then the first field
// in the event buffer will be used to find a matching entry in the array
// and the corresponding string will be displayed instead of the number.
// The values of cause provided should be monotonically increasing but do
// not need to be sequential.

typedef struct EventTraceCauseDesc {
	unsigned long cause;
	char* description;
}EventTraceCauseDesc;


typedef struct EventTraceDescInfo {
	EventTraceCauseDesc* desc;
	long descCount;
}EventTraceDescInfo;

const int kEventTraceDescMax = 5;


// think of the below as a private TEventCollector class struct definition

typedef struct TEventCollectorDebuggerInfo {
		EEventCollectorControl fDoCollect;
		char* fEventBuffer;
		char* fCurrentPos;
		unsigned long fBufferSize;
		size_t fEntrySize;
		unsigned long fNumberOfEntries;
		char * fDataFormat;
		char * fName;
		long fActualDescCount;
		EventTraceDescInfo fDescInfo[kEventTraceDescMax];
} TEventCollectorDebuggerInfo;


//������������������ TEventCollector Protocol Interface ����������������������������
typedef ULong TEventCollectorTimeValue;

PROTOCOL TEventCollector : public TProtocol	{
public:


	static 	TEventCollector*	New (char *);		// constructor
			void		Delete ();			// destructor
						// must be overridden and subclassers should provide a delete function that
						// provides cleanup, release buffers, deregisters, etc.

			void		Init (	size_t	entrySizeInBytes,
								char* 	printableFormat,
								char*	collectionName,
								int number = kDefaultNumberOfEntries,
								int residence = eNormalBuffer
							);
						// must be overridden and should setup the
						// buffers and data structures and fill in the
						// TEventCollectorDebuggerInfo information.

						// The printableFormat should allow the debugger to interpret
						// the data and format it for output.
						// Data describing format, fashioned after c formatting but substituting
						// for the size modifier the following :
						// unspecified - data is int (actually the same as c)
						// b - data is a byte (different from c)
						// l - data is a long (actually the same as c)
						// h - data is a short (actually the same as c)

						// collectionName is a name that can be used by the debugger
						// to identify the type of collection for a user friendly interface

						// The residence indicates any special residence requirements for
						// buffer.  Normal indicates the buffer can be paged, locked
						// means that it can't be paged but that the physical pages may
						// change and wired means that it can't be paged or its physical pages
						// changed.  Buffers that are to be accessed by interrupt routines
						// need to be locked (IRQ routines) or wired (FIQ routines).

			Boolean		AddDescriptions (EventTraceCauseDesc *list, int count);
						// list is for associating a descriptive string
						// for the event types.  If an array is provided then
						// the first field in the event buffer will be used to
						// find a matching entry in the array and the corresponding
						// string will be displayed instead of the number.
						// The values of cause provided should be monotonically
						// increasing but do not need to be sequential.
						// count is the number of entries in the array. If a
						// descriptive list isn't provided the fist field is printed
						// uninterpreted.  For space reasons a pointer to the array is
						// kept rather than the array and string data being copied.
						// The protocol object should be deleted before list is
						// deallocated.  Return true if the descriptions were added,
						// false if not [current limit is 5 sets of descriptions].


	// Newton side methods for event tracing
	// methods to add the event data to the buffer
			void		Add (unsigned char byteEventValue);
			void		Add (unsigned long longEventValue);
						// raises an exception if the event entry size is less
						// than sizeof (long)
			void		Add (const void * event);
						// copies entrySizeInBytes from event into the buffer
			void		AddAddress (void);
						// adds time and return address to the buffer...

			void		CollectionControl (int control);

protected:

	// Methods that provide behavior (allow "inherited" code)
	NONVIRTUAL void		Register ();
						// method that registers the event collector with
						// the debugger
	NONVIRTUAL void		Deregister ();
						// method that deregisters the event collector with
						// the debugger
	NONVIRTUAL void		AddTime ();
						// Add the time to the event

	TEventCollectorDebuggerInfo fData;	// used locally and to communicate with the
										// debugger.  The debugger can activate/deactivate
										// collecting by collection name and display the
										// buffer contents by using the data format to
										// interpret the buffer data
	char *fBufferLimit;
	int fResidence;
};

TEventCollector* MakeNewTHistoryCollector();

#endif // __TRACEEVENTS_H

