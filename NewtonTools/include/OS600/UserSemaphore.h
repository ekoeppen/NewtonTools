/*
	File:		UserSemaphore.h

	Contains:	xxx put contents here xxx

	Copyright:	� 1992-1994 by Apple Computer, Inc., all rights reserved.

*/

#ifndef	__USERSEMAPHORE_H
#define __USERSEMAPHORE_H

#include "NewtTypes.h"

#ifndef	__USEROBJECTS_H
#include "UserObjects.h"
#endif	//__USEROBJECTS_H

// semaphore operator list
class TUSemaphoreOpList : public TUObject
{
	public:
					TUSemaphoreOpList(TObjectId id = 0) : TUObject(id) {}
		void		operator=(TObjectId id) { CopyObject(id); }
		void		operator=(const TUSemaphoreOpList& copy) { CopyObject(copy); }
		long		Init(ULong numInList, ...);
};

// SempahoreGroup class
class TUSemaphoreGroup : public TUObject
{
	public:
					TUSemaphoreGroup(TObjectId id = 0) : TUObject(id) {}
		void		operator=(TObjectId id) { CopyObject(id); }
		void		operator=(const TUSemaphoreGroup& copy) { CopyObject(copy); }
		long		Init(ULong num = 1);

		long		SemOp(TObjectId semListId, SemFlags flags = kWaitOnBlock);
		long		SemOp(TUSemaphoreOpList* semListObj, SemFlags flags = kWaitOnBlock);
		long		SetRefCon(void* refCon);
		long		GetRefCon(void** pRefCon);
};

// User Semaphore Class
class TULockingSemaphore : public TUSemaphoreGroup
{
	public:
					TULockingSemaphore(TObjectId id = 0) : TUSemaphoreGroup(id) { GetRefCon(&fSem); }
					~TULockingSemaphore();
		void		operator=(TObjectId id) { CopyObject(id); }
		void		operator=(const TULockingSemaphore& copy) { CopyObject(copy.fId); }
		void		CopyObject(TObjectId id);
		long		Init();

		long		Acquire(SemFlags flags = kWaitOnBlock);
		long		Release();

	private:
		friend void UserBoot();
		static long StaticInit();	// should only be called by UserBoot at init time

		static TUSemaphoreOpList	faquireOP;
		static TUSemaphoreOpList	freleaseOP;
		ULong*		fSem;			// a pointer to the user semaphore
};

// User Semaphore Class
class TURdWrSemaphore : public TUSemaphoreGroup
{
	public:
					TURdWrSemaphore(TObjectId id = 0) : TUSemaphoreGroup(id) {};
		void		operator=(TObjectId id) { CopyObject(id); }
		void		operator=(const TURdWrSemaphore& copy) { CopyObject(copy); }
		long		Init();

		long		AcquireWr(SemFlags flags = kWaitOnBlock);
		long		ReleaseWr();
		long		AcquireRd(SemFlags flags = kWaitOnBlock);
		long		ReleaseRd();

	private:
		friend void UserBoot();
		static long StaticInit();	// should only be called by UserBoot at init time

		static TUSemaphoreOpList	faquireWrOP;
		static TUSemaphoreOpList	freleaseWrOP;
		static TUSemaphoreOpList	faquireRdOP;
		static TUSemaphoreOpList	freleaseRdOP;
};

#endif
