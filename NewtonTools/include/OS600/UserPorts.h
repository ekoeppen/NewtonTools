/*
	File:		UserPorts.h

	Contains:	User glue to port code

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v25 internal.

*/

#ifndef	__USERPORTS_H
#define __USERPORTS_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef __NEWTERRORS_H
#include "NewtErrors.h"
#endif

#ifndef	__USEROBJECTS_H
#include "UserObjects.h"
#endif

#ifndef	__USERSHAREDMEM_H
#include "UserSharedMem.h"
#endif

class TUPort;
class TUAsyncMessage;

//
// TUMsgToken
//
// used for receive to get info about sender
//
class TUMsgToken
{
	public:
					TUMsgToken()							{ fMsgId = 0; fRcvrMsgId = 0; fReplyId = 0; fSignature = 0;}

		long		CashMessageToken(ULong* returnSize, void* content, ULong size, ULong offset = 0, Boolean copyDone = true);
		long		ReplyRPC(void* content, ULong size, long replyResult = noErr);
		long		GetUserRefCon(ULong *refConPtr);

		TObjectId	GetMsgId() const				{ return fMsgId; }
		TObjectId	GetReceiverMsgId() const		{ return fRcvrMsgId; }
		TObjectId	GetReplyId() const				{ return fReplyId; }
		TObjectId	GetSignature() const			{ return fSignature; }

		friend class TUPort;
		friend class TUAsyncMessage;

	private:
		TObjectId	fMsgId;			// message senders id
		TObjectId	fReplyId;		// send reply message here
		ULong		fSignature;		// signature used to sync to message sender
		TObjectId	fRcvrMsgId;		// message receivers id on async receive
};


////
//
// Async Message Parameter Block

class TUAsyncMessage
{
	public:
					TUAsyncMessage();
					TUAsyncMessage(const TUAsyncMessage& copy);
					TUAsyncMessage(TObjectId sMemMsg, TObjectId replyMem);
					~TUAsyncMessage();
		void		operator=(const TUAsyncMessage& copy)			{ fMsg = copy.fMsg; fReplyMem = copy.fReplyMem; }
		void		operator=(const TUMsgToken& copy);
		long		Init(Boolean forSendRPC = true);

		long		SetCollectorPort(TObjectId portId);
		long		SetUserRefCon(ULong refCon)				{ return fMsg.SetUserRefCon(refCon); }
		long		GetUserRefCon(ULong *refConPtr)			{ return fMsg.GetUserRefCon(refConPtr); }
		TObjectId	GetMsgId()								{ return fMsg; }
		TObjectId	GetReplyMemId()							{ return fReplyMem; }
		long		GetResult(TObjectId* sentbyId = nil, TObjectId* replymemId = nil, ULong* msgType = nil, ULong* signature = nil);
		long		BlockTillDone(TObjectId* sentbyId = nil, TObjectId* replymemId = nil, ULong* msgType = nil, ULong* signature = nil);
		long		Abort();
		long		Abort(TUMsgToken* token, ULong* msgType);

	private:
		TUSharedMemMsg	fMsg;
		TUSharedMem		fReplyMem;
};


//
// When a futureTimeToSend is specified in any of the following calls, it represents a moment in time.
// A moment in time is relative to the current time.  So, if I wanted to have a message sent in a day, I
// would:
// TTime futureTime = GetGlobalTime() + TTime(1*24*60,kMinutes). (1 day, 24 hours in a day, 60 minutes in an hour)
// gives me the time in the future to send the message.
//
//
// The timeout option below represents the duration of the call itself, and is represented by a 32 bit number.
// This means that you can have a timeout of no more than 14 minutes in the future (the number of 200ns time units
// that fit in 32 bits).
//
// To set the timeout paramater you can supply a number in any unit up to minutes.  For example, if you want a
// 1 second timeout you could use either:
// 1*kSeconds
// or:
// 1000*kMilliseconds
//

////
//
// Ports

class TUPort : public TUObject
{
	public:
					TUPort() : TUObject(0) {}
					TUPort(TObjectId id);
		void		operator=(TObjectId id) { CopyObject(id); }
		void		operator=(const TUPort& copy) { CopyObject(copy); }
		long		Init();

		long		Send(void* content, ULong size, TTimeout timeout = kNoTimeout, ULong msgType = 0, Boolean urgent = false)
								{ return SendGoo(kBuiltInSMemMsgId, 0, content, size, msgType, 0, urgent, timeout, 0); }
		long		SendRPC(ULong* returnSize, void* content, ULong size, void* replyBuf, ULong replySize, TTimeout timeout = kNoTimeout, ULong msgType = 0, Boolean urgent = false)
								{ return SendRPCGoo(kBuiltInSMemMsgId, kBuiltInSMemId, returnSize, content, size, msgType, 0, urgent, replyBuf, replySize, timeout, nil); }

					// async versions of send...
		long		Send(TUAsyncMessage* async, void* content, ULong size, TTimeout timeout = kNoTimeout, TTime* futureTimeToSend = nil, ULong msgType = 0, Boolean urgent = false)
								{ return SendGoo(async->GetMsgId(), 0, content, size, msgType, kPortFlags_Async, urgent, timeout, futureTimeToSend); }
		long		SendRPC(TUAsyncMessage* async, void* content, ULong size, void* replyBuf, ULong replySize, TTimeout timeout = kNoTimeout, TTime* futureTimeToSend = nil, ULong msgType = 0, Boolean urgent = false)
								{ return SendRPCGoo(async->GetMsgId(), async->GetReplyMemId(), nil, content, size, msgType, kPortFlags_Async, urgent, replyBuf, replySize, timeout, futureTimeToSend); }

		long		Receive(ULong* returnSize, void* content, ULong size, TUMsgToken* token = nil, ULong* returnMsgType = nil, TTimeout timeout = kNoTimeout, ULong msgFilter = kMsgType_MatchAll, Boolean onMsgAvail = false, Boolean tokenOnly = false);
		long		Receive(TUAsyncMessage* async, TTimeout timeout = kNoTimeout, ULong msgFilter = kMsgType_MatchAll, Boolean onMsgAvail = false);

		long		IsMsgAvailable(ULong msgFilter = kMsgType_MatchAll)
								{ return Receive(nil, (TTimeout) kNoTimeout, msgFilter); }

		long		ResetMsgFilter(TUAsyncMessage* async, ULong msgFilter);

		long		Reset(ULong sendersResetFlags, ULong receiversResetFlags);

	private:
		long		SendGoo(TObjectId msgId, TObjectId replyId, void* content, ULong size, ULong msgType, ULong flags, Boolean urgent, TTimeout timeout, TTime* futureTimeToSend);
		long		SendRPCGoo(TObjectId msgId, TObjectId replyId, ULong* returnSize, void* content, ULong size, ULong msgType, ULong flags, Boolean urgent,
								void* replyBuf, ULong replySize, TTimeout timeout, TTime* futureTimeToSend);
		friend void SleepTill(TTime* futureTimeToSend);
		long		SendForSleepTill(TTime* futureTimeToSend)
								{ return SendGoo(kBuiltInSMemMsgId, 0, nil, 0, 0, 0, false, kTimeOutImmediate, futureTimeToSend); }

};


extern long SendForInterrupt(TObjectId portId, TObjectId msgId, TObjectId replyId, void* content, ULong size,
					ULong msgType = kMsgType_FromInterrupt, TTimeout timeout = 0, TTime* futureTimeToSend = nil, Boolean urgent = false);


#endif
