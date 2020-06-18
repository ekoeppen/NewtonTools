/*
	File:		UserTasks.h

	Contains:	User level interface to task class.

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v34 internal.

*/

#ifndef	__USERTASKS_H
#define __USERTASKS_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef	__SHAREDTYPES_H
#include "sharedTypes.h"
#endif //__SHAREDTYPES_H

#ifndef	__USEROBJECTS_H
#include "UserObjects.h"
#endif	//__USEROBJECTS_H

#ifndef	__LongTime_H
#include "LongTime.h"
#endif	//__LongTime_H

#ifndef __USERGLOBALS_H
#include "UserGlobals.h"
#endif /*__USERGLOBALS_H*/

#include "UserPorts.h"

const int kSleepForever = 0xffffffff;		// will cause sleep to never return

extern void Sleep(TTimeout timeout);
extern void SleepTill(TTime* futureTime);

// Get a pointer to the object you passed to the task (which constitutes
// the "task global space".

extern "C" void*	GetGlobals(void);

struct SKernelParams
{
	ULong					fParams[12];			// arguments and return values
};


/*	----------------------------------------------------------------
**
**	STaskSwitchedGlobals  --  Switched task globals
**
**		The OS "switches" these writable globals.
**
*/
struct STaskSwitchedGlobals
{
	SKernelParams			fKernelParams;			// parameters for kernel calls
	int						fErrNo;					// slot for errors from stdio
	TObjectId				fDefaultHeapDomainId;	//
	void*					fStackTop;				// byte beyond top of stack we are running on
	void*					fStackBottom;			// last usable byte in this stack
	TObjectId				fTaskId;				// current task id
	void *					fCurrentHeap;			// -> current heap
	NewtonErr				fMemErr;				// current task's MemError() status
	ULong					fTaskName;				// task name, from Init call

	/*
	**	Exceptions currently assume that fExceptionGlobals appears LAST
	**
	*/
	ExceptionGlobals		fExceptionGlobals;		// globals for try/catch/Throw
};


inline STaskSwitchedGlobals * TaskSwitchedGlobals()
{
	return ((STaskSwitchedGlobals*)gCurrentGlobals) - 1;
}


enum
{
	kSpawnedTaskStackSize	= 6000,
	kSpawnedTaskAckTimeout	= 15000,
	kSpawnedTaskAckMsgType	= 0x00800000
};



class TUTask : public TUObject
{
	public:
					TUTask(TObjectId id = 0) : TUObject(id) {};
		void		operator=(TObjectId id) { CopyObject(id); }
		void		operator=(const TUTask& copy) { CopyObject(copy); }

		long		Init(TaskProcPtr pc, ULong stackSize, ULong objectSize, void* theObject, ULong priority, ULong taskName, TObjectId environment);

		long		Init(TaskProcPtr pc, ULong stackSize, ULong objectSize, void* theObject, ULong priority = kUserTaskPriority, ULong taskName = 'UNAM');

		long		Start();
		long		Suspend();
		long		GetRegister(ULong reg, ULong* value);
		long		SetRegister(ULong reg, ULong value);
};



// this is the task spawner class
// it will spawn a task that represents
// itself and continue as that task

class TUTaskWorld : public SingleObject
{
	public:
						TUTaskWorld();
		virtual			~TUTaskWorld();

		long			StartTask(Boolean wantResultFromChild, Boolean wantOwnerShip, TTimeout startTimeout, ULong stackSize, ULong priority, ULong taskName, TObjectId environment);	// make a new task and object
		long			StartTask(Boolean wantResultFromChild = true, Boolean wantOwnerShip = false, TTimeout startTimeout = kNoTimeout, ULong stackSize = kSpawnedTaskStackSize, ULong priority = kUserTaskPriority, ULong taskName = 'UNAM');	// make a new task and object
		TObjectId		GetChildTaskId() { return fChildTask; }

	protected:
		virtual	ULong	GetSizeOf() = 0;			// object must return its own size
		virtual	long	TaskConstructor();			// spawned task called here to construct itself
		virtual	void	TaskDestructor();			// spawned task called here to destroy itself
		virtual	void	TaskMain() = 0;				// spawned task called here to begin running

		void			TaskEntry(ULong, TObjectId taskId);	// low level entry for spawned task (only in base class)

		// these instance vars are used by the task creator (the parent)
		Boolean			fIsSpawned;					// this indicates if this object is running a new task
		Boolean			fIsOwnedByParent;			// true if parent owns child, false if child independent
		Boolean			fWantResult;				// true if result should be passed back from child
		TUPort			fMotherPort;				// port used to talk between object in pre and post task state
		TUTask			fChildTask;					// created task
};


struct TULockStack
{
	VAddr	start;
	VAddr	end;
};

extern long ResetAccountTime();
extern long GetNextTaskId(TObjectId lastId, TObjectId* returnId);
extern long Yield(TObjectId taskId);


// Reboot -
//
// This function will reboot the machine in
// one of two states, 1) Warmboot: we will try
// to preserve the persistent areas.
// 2) Coldboot: all data will be lost.
//
// The error parameter is saved so that the
// main user application, upon reboot, can display
// an appropriate error dialog.
//
// The safe flag indicates whether we should
// wait for any protected monitors to finish
// or not.  True means wait.
//
// Pass kRebootMagicNumber for the rebootType
// if you want a cold boot, zero will do a warm
// boot.
//
long Reboot(NewtonErr error = noErr, ULong rebootType = 0, Boolean safe = false);


// SetEnvironment -
//
// Sets the current tasks environment and gets the previous one
// and returns it.
//
long SetEnvironment(TObjectId newEnvId, TObjectId* oldEnvId = nil);

// GetEnvironment -
//
// Return the id of the current task's environment
//
long GetEnvironment(TObjectId* pEnvID);

//	Environment Add/Remove/Test glue (eventually calls GenericSWI)
//
long EnvironmentHasDomain(TObjectId env_id, TObjectId domain_id, Boolean * pHasDomain, Boolean * pIsManager);
long AddDomainToEnvironment(TObjectId env_id, TObjectId dom_id, ULong flags);
long RemoveDomainFromEnvironment(TObjectId env_id, TObjectId dom_id);

// arrange for current task's objs to go to 'to' when the task exits
//
long SetBequeathId(TObjectId to);

#endif
