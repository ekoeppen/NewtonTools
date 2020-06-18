/*
	File:		PCECallBack.h

	Contains:	Protocol interface for ConnectionEnd callbacks routines.
				Typically, the system will call out to a PConnectionEnd
				for things like PutBytes, etc.  When complete, the
				PConnectionEnd implementation will call PCECallBack::PutBytesComplete.

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v3 (5/24/95) internal.

*/



#ifndef	__PCECALLBACK_H
#define __PCECALLBACK_H

#ifndef __CONFIGCOMMUNICATIONS_H
#include "ConfigCommunications.h"
#endif

#ifndef __PROTOCOLS_H
#include "Protocols.h"
#endif

#ifndef __USERPORTS_H
#include "UserPorts.h"
#endif

#ifndef __COMMTOOL_H
#include "CommTool.h"
#endif

#ifndef	__COMMTOOLOPTIONS_H
#include "CommToolOptions.h"
#endif

class TConnectionEnd;

//--------------------------------------------------------------------------------
//		PCECallBack
//--------------------------------------------------------------------------------
PROTOCOL PCECallBack : public TProtocol
{
	public:
		static	PCECallBack*	New(char*);		// initialize state, return this
		void					Delete();		// clean up

		void					Init(TConnectionEnd* cePtr);


		void					OpenComplete(NewtonErr result);
		void					CloseComplete(NewtonErr result);

		void					BindComplete(NewtonErr result);
		void					UnbindComplete(NewtonErr result);

		void					ConnectComplete(NewtonErr result);
		void					ListenComplete(NewtonErr result);
		void					AcceptComplete(NewtonErr result);

		void					TerminateComplete();

		void					PutComplete(NewtonErr result, ULong putBytesCount);
		void					KillPutComplete(NewtonErr result);

		void					GetComplete(NewtonErr result, Boolean endOfFrame = false, ULong getBytesCount = 0);
		void					KillGetComplete(NewtonErr result);

		void					HandleRequest(UChar* request, ULong requestSize, TUMsgToken& msgToken, ULong msgType);
		void					HandleReply(ULong userRefCon, ULong msgType);

		void					KillControlComplete(NewtonErr result);
		void					KillGetCommEventComplete(NewtonErr result);

		void					GetCommEvent();
		NewtonErr				PostCommEvent(TCommToolGetEventReply& theEvent, NewtonErr result);

		void					ProcessOptionComplete(ULong optResult);
		void 					ProcessPutBytesOptionComplete(ULong optResult);
		void 					ProcessGetBytesOptionComplete(ULong optResult);

		void					ResArbReleaseComplete(NewtonErr result);

		NewtonErr				FlushChannel(ULong filter, NewtonErr flushResult);
		NewtonErr				StartAbort(NewtonErr abortError);
		NewtonErr				GetAbortErr();
		ULong					GetTerminationEvent();
		void					SetTerminationEvent(ULong event);

		NewtonErr				InitAsyncRPCMsg(TUAsyncMessage& asyncMsg, ULong refCon);

		// getters/setters�
		ULong					GetToolConnectState();
		void					SetToolConnectState(ULong state);

		TCMOCTConnectInfo&		GetConnectInfo();
		void					SetConnectInfo(TCMOCTConnectInfo& info);

		TCMOTransportInfo&		GetCMOTransportInfo();
		void					SetCMOTransportInfo(TCMOTransportInfo& info);

		ULong					GetReceiveMessageBufSize();	// returns the size of the buffer used by the commtool to receive rpc messages
																			   // Any message sent to the tool which exceeds this size will be truncated.
		TUPort*					GetConnectionEndPort(); // returns a pointer to the tool's port object

		TCommToolOptionInfo&	GetControlOptionsInfo();	// returns the option info for the current control request
		TCommToolOptionInfo&	GetGetBytesOptionsInfo();	// returns the option info for the current get bytes request
		TCommToolOptionInfo&	GetPutBytesOptionsInfo();	// returns the option info for the current put bytes request

		CBufferList*			GetCurPutData();			// returns a pointer to the current put request buffer list
		Boolean					GetCurPutFrameData();		// returns true if current put request is framed
		Boolean					GetCurPutEndOfFrame();		// returns true if current framed put request is end of frame

		CBufferList*			GetCurGetData();			// returns a pointer to the current get request buffer list
		Boolean					GetCurGetFrameData();		// returns true if current get request is framed
		Boolean					GetCurGetNonBlocking();	// returns true if current get request is non blocking (ie has a threshold)
		Size					GetCurGetThreshold();		// returns the value of threshold for the current nonblocking get request

		Boolean					GetPassiveClaim();						// returns true if client asked for passive claim of tool resources
		void					SetPassiveClaim(Boolean passiveClaim);	// Set the value of passive claim

		Boolean					GetPassiveState();						// returns true if in passive state (resources passively claimed, and willing to give up resources)
		void					SetPassiveState(Boolean passiveState);	// Set the value of passive claim

		Boolean					GetWaitingForResNotify();						// returns true if tool has passively claimed resources, and is waiting for notification of resource ownership
		void					SetWaitingForResNotify(Boolean waitingForResNotify);	// Set the value of passive claim

		ULong					GetCurRequestOpCode();	// returns the opcode of the current control request

};


#endif /* PCECALLBACK_H */

