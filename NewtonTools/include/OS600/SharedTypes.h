/*
	File:		SharedTypes.h

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v35 internal.

*/

#ifndef	__SHAREDTYPES_H
#define __SHAREDTYPES_H

#ifndef __KERNELTYPES_H
#include	"KernelTypes.h"
#endif

typedef void (*TaskProcPtr)(void*, ULong, TObjectId);
typedef void (*MonitorProcPtr)(void*, ULong, void*);	// monitorObject, selector, userObject

enum TaskRegisters
{
	// result
	kResultReg					= 0,
	kcTheFrame					= 11,					// frame pointer
	kcTheStack					= 13,
	kcTheLink					= 14,
	kcThePC						= 15,

	// Monitor registers
	kMonMonId					= 0,
	kMonMonRefCon				= 0,
	kMonSelector				= 1,
	kMonUserRefCon				= 2,
	kMonThePC					= 3,
	kReturnParm0				= 0,
	kReturnParm1				= 1,
	kReturnParm2				= 2,
	kReturnParm3				= 3,
	kReturnParm4				= 4,

	// Copy registers
	kCopyToBuf					= 0,
	kCopyFromBuf				= 1,
	kCopySize					= 2
};

enum TaskPriorities {

	kIdleTaskPriority					= 0,
	kUserTaskPriority					= 10,
	kKernelTaskPriority					= 20,
	kPreemptiveSchedulerTaskPriority	= 25,
	kTimerTaskPriority					= 31
};

enum MiscItems
{
	// suspend code for monitors
	kSuspendMonitor				= -1,
	kMonitorFaultSelector		= -2,

	// exception codes for debugger
	kExcpt_SerialDebuggerStop	= 8,

	// built in id's for a task
	kBuiltInSMemMsgId			= 1,
	kBuiltInSMemId,
	// built in id's for a monitor
	kBuiltInSMemMonitorFaultId,					// used in fault monitors to get fault info

	// shared memory privilage flags
	kSMemReadOnly				= 0x01,			// allow only read operations (if not set, read/write)
	kSMemReadWrite				= 0x00,			// allow read/write operations
	kSMemNoSizeChangeOnCopyTo	= 0x02,			// don't allow size to change when copyto takes place (use initial size)

	// message type stuff
	kMsgType_MatchAll			= ~0,			// match any message on receive
	kMsgType_ReservedMask		= 0x00ffffff,	// mask to reserve system msg types
	kMsgType_CollectedReceiver	= 0x01000000,	// system: msg is collected receiver
	kMsgType_CollectedSender	= 0x02000000,	// system: msg is collected sender
	kMsgType_FromInterrupt		= 0x04000000,	// system: msg is from an interrupt
	kMsgType_NoMsgTypeSet		= 0x08000000,	// system: all messages with no message type have this set

	kMsgType_CollectorMask 		= kMsgType_CollectedReceiver | kMsgType_CollectedSender,	// tells us if we have either type of collector

	// port flags stuff
	kPortFlags_Async			= 0x00000001,	// call is async
	kPortFlags_Urgent			= 0x00000002,	// call is urgent
	kPortFlags_ReceiveOnMsgAvail= 0x00000004,	// only do receive if something matches
	kPortFlags_WantDelay		= 0x00000008,	// we want delay
	kPortFlags_WantTimeout		= 0x00000010,	// we want timeout
	kPortFlags_IsMsgAvail		= 0x00000020,	// this is a peek call
	kPortFlags_ReservedMask		= 0x00ffffff,	// mask to reserver system port flags
	kPortFlags_TimerWanted		= 0x01000000,	// system: internal for timer wanted
	kPortFlags_CanRemoveTask	= 0x02000000,	// system: internal for task removal allowed
	kPortFlags_ScheduleOnSend	= 0x04000000,	// we want scheduling to happen on send

	// more port flags (for TUPort::Reset)
	kPortFlags_Abort			= 0x00000001,	// receivers/senders should be aborted
	kPortFlags_Timeout			= 0x00000002,	// receivers/senders should be timedout

	// port send default parameters
	kPortSend_BufferAlreadySet	= -1,

	// shared mem msg flags
	kSMemMsgFlags_Abort			= 0x00000001,	// abort the msg in progress
	kSMemMsgFlags_BlockTillDone	= 0x00000002	// block this task till msg done
};

const int	kTypeBits = 4;
const int	kTypeMask = 0x0f;

// we currently only allow 16 of these
enum KernelTypes {
	kNoType = 0,
	kBaseType,
	kPortType,
	kTaskType,
	kEnvironmentType,
	kDomainType,
	kSemListType,
	kSemGroupType,
	kSharedMemType,
	kSharedMemMsgType,
	kMonitorType,
	kPhysType,
	kExtPhysType
};

#endif
