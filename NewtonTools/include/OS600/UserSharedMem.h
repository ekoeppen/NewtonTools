/*
	File:		UserSharedMem.h

	Contains:	User task interface to shared memory objects

	Copyright:	� 1992-1994 by Apple Computer, Inc., all rights reserved.

	Derived from v13 internal.

*/

#ifndef	__USERSHAREDMEM_H
#define __USERSHAREDMEM_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef	__USEROBJECTS_H
#include "UserObjects.h"
#endif	//__USEROBJECTS_H
#include "SharedTypes.h"
#include "UserGlobals.h"
#include "LongTime.h"

class TUMsgToken;

class TUSharedMem : public TUObject
{
	public:
					TUSharedMem(TObjectId id = 0) : TUObject(id) {};
		void		operator=(TObjectId id) { CopyObject(id); }
		void		operator=(const TUSharedMem& copy) { CopyObject(copy); }
		long		Init();

		long		SetBuffer(void* buffer, ULong size, ULong permissions = kSMemReadOnly);
		long		GetSize(ULong* returnSize, void** returnBuffer = nil);
		long		CopyToShared(void* buffer, ULong size, ULong offset = 0, TUMsgToken* token = nil);
		long		CopyFromShared(ULong* returnSize, void* buffer, ULong size, ULong offset = 0, TUMsgToken* token = nil);
};


class TUSharedMemMsg : public TUSharedMem
{
	public:
					TUSharedMemMsg(TObjectId id = 0) : TUSharedMem(id) {};
		void		operator=(TObjectId id) { CopyObject(id); }
		void		operator=(const TUSharedMemMsg& copy) { CopyObject(copy); }
		long		Init();

		long		SetTimerParms(TTimeout timeout = kNoTimeout, TTime* delay = nil);
		long		SetMsgAvailPort(TObjectId availPortId);
		long		GetSenderTaskId(TObjectId* theSenderTaskId);
		long		GetSize(ULong* returnSize, void** returnBuffer = nil, ULong *refConPtr = nil);
		long		SetUserRefCon(ULong refCon);
		long		GetUserRefCon(ULong *refConPtr);
		long		CheckForDone(ULong flags, TObjectId* sentbyId = nil, TObjectId* replymemId = nil, ULong* msgType = nil, ULong* signature = nil)
						{ return SMemMsgCheckForDoneSWI(fId, flags, sentbyId, replymemId, msgType, signature); }
		long		MsgDone(long result, TObjectId signature)
						{ return SMemMsgMsgDoneSWI(fId, result, signature); }
};


#endif
