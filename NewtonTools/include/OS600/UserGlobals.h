/*
	File:		UserGlobals.h

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v29 internal.

*/

#ifndef	__USERGLOBALS_H
#define	__USERGLOBALS_H
#define __UserGlobals__	// obsolete

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef	__KERNELTYPES_H
#ifndef	__KERNELTYPES__	// obsolete
#include 	"KernelTypes.h"
#endif
#endif

#ifndef	__LONGTIME_H
#ifndef	__LongTime__	// obsolete
#include	"LongTime.h"
#endif
#endif

#ifndef __NEWTCONFIG_H
#include	"NewtConfig.h"	// because they used to be defined in this file
#endif

class TUPort;
class TULockStack;
class TUMonitor;

// extern globals
extern TUMonitor*		gUObjectMgrMonitor;	// use this to talk to the object manager
extern TUPort*			gUNullPort;			// this is a special null port (never receives) used to create things like sleep
extern TObjectId		gCurrentTaskId;		// id of currently running task
extern TObjectId		gCurrentMonitorId;	// monitor that a task is in if any
extern void*			gCurrentGlobals;	// pointer to per task globals

extern "C" ULong GetPortSWI(ULong what);
extern "C" long GenericSWI(...);
extern "C" long GenericWithReturnSWI(ULong p1, ULong p2, ULong p3, ULong p4, ULong* rp1, ULong* rp2, ULong* rp3);
extern "C" long SemaphoreOpGlue(ULong ObjectId, ULong OpListId, ULong flags);
extern "C" long PortSendSWI(ULong ObjectId, ULong msgId, ULong replyId, ULong msgType, ULong flags);
extern "C" long PortReceiveSWI(ULong ObjectId, ULong msgId, ULong msgFilter, ULong flags, ULong* senderMsgId, ULong* replyMemId, ULong* returnMsgType, ULong* signature);
extern "C" long PortResetFilterSWI(ULong ObjectId, ULong msgId, ULong msgFilter);

extern "C" long SMemSetBufferSWI(ULong ObjectId, void* buffer, ULong size, ULong permissions);
extern "C" long SMemGetSizeSWI(ULong ObjectId, ULong* returnSize, void** returnBuffer, ULong* refConPtr);
extern "C" long SMemCopyToSharedSWI(ULong ObjectId, void* buffer, ULong size, ULong offset, ULong sendersMsgId, ULong signature);
extern "C" long SMemCopyFromSharedSWI(ULong ObjectId, void* buffer, ULong size, ULong offset, ULong sendersMsgId, ULong signature, ULong* returnSize);
extern "C" long MonitorDispatchSWI(ULong ObjectId, long selector, void* userObject);
extern "C" long MonitorExitSWI(long monitorResult, void* continuationPC);
extern "C" long MonitorThrowSWI(char *, void *, void *);
extern "C" long MonitorFlushSWI(ULong ObjectId);
extern "C" long SMemMsgSetTimerParmsSWI(ULong ObjectId, ULong timeout, ULong timeLow, ULong timeHigh);
extern "C" long SMemMsgSetMsgAvailPortSWI(ULong ObjectId, ULong availPort);
extern "C" long SMemMsgGetSenderTaskIdSWI(ULong ObjectId, void* senderTaskId);
extern "C" long SMemMsgSetUserRefConSWI(ULong ObjectId, ULong refCon);
extern "C" long SMemMsgGetUserRefConSWI(ULong ObjectId, ULong* refConPtr);
extern "C" long SMemMsgMsgDoneSWI(ULong ObjectId, long result, ULong signature);
extern "C" long SMemMsgCheckForDoneSWI(ULong ObjectId, ULong flags, ULong* sentById, ULong* replymemId, ULong* msgType, ULong* signature);

extern "C" long ResetRebootReason(void);

#ifdef forARM
// Hardware status goop
// read and write volatile
inline UChar ReadVByte(const volatile void* ptr) { return *(const volatile unsigned char*)ptr; }
inline ULong ReadVLong(const volatile void* ptr) { return *(const volatile unsigned long*)ptr; }
inline void WriteVByte(volatile void* ptr, UChar ch) { *(volatile unsigned char*)ptr = ch; }
inline void WriteVLong(volatile void* ptr, ULong l) { *(volatile unsigned long*)ptr = l; }
#endif

// The following is an atomic and stack safe routine that will
// allow you to read a location in memory, or in setBits, and
// clear out the clearBits, then write the new value back out
// in one operation.
extern "C" void SetAndClearBitsAtomic(void* ptr, ULong setBits, ULong clearBits);

class TProcessorState;
extern "C" TProcessorState * GetProcessorFaultState();

// call-off to page manager to see how much is/could be freed
extern "C" ULong SystemFreePageCount();

#endif
