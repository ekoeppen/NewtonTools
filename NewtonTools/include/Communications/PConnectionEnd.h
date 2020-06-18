/*
	File:		PConnectionEnd.h

	Contains:	Definition of a PConnectionEnd.  A connection end is created
				each time a MuxTool receives an open request (e.g. NS endpoint
				instantiate).

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v2 (5/11/95) internal.

*/



#ifndef	__PCONNECTIONEND_H
#define __PCONNECTIONEND_H

#ifndef __CONFIGCOMMUNICATIONS_H
#include "ConfigCommunications.h"
#endif

#ifndef __PROTOCOLS_H
#include "Protocols.h"
#endif

#ifndef __COMMTOOL_H
#include "CommTool.h"
#endif

// Forward declaration of PMuxTool so it can be used as a parameter for PConnectionEnd::Init()
PROTOCOL PMuxTool;

class PCECallBack;

// PConnectionEnd
//	Each open call to the MuxTool creates a new PConnectionEnd.
//	PConnectionEnd has evolved from TCommTool.  TCommTool has been
//	split between TMuxTool and PConnectionEnd.  The methods for dealing
//	with connection state and managing a connection are contained in
//	PConnectionEnd, while the methods related to receiving OS messages and
//	managing the OS task are part of TMuxTool


// NOTE:  This should just be a protocol and the developer will provide
// the implementation.  To replace all the "CT" functions from TCommToolProtocol,
// define a new protocol and the implementation which call back into this ROM
// based functionality.


PROTOCOL PConnectionEnd : public TProtocol
{
	public:
		static PConnectionEnd*	New(char*);		// initialize state, return this
		void					Delete();		// clean up

								// Allocate and intialize variables and do whatever else is necessary to be ready to handle requests
		NewtonErr				Init(PMuxTool* pmuxToolPtr, PCECallBack* ceCallBack, ULong ceNumber);

								// This is the hook for associated PMuxTools.
								// This may be used, for example, when a packet arrives for this connection end
		void					HandleInternalRequest(void* msgBuf);

								// This method is called after returning from a request dispatch (e.g. putBytes).
								// If the connection end needs to perform some operation but it can't be nested,
								// you can set a flag and initiate the operation when HandleInternalEvent is called
		void					HandleInternalEvent();

		void					OpenStart();
		void					CloseStart();

		void					BindStart();
		void					UnbindStart();

		void					ConnectStart();
		void					ListenStart();
		void					AcceptStart();

		void					ReleaseStart();

		void					TerminateStart();

		void					PutBytesStart(CBufferList* clientBuffer);
		void					PutFramedBytesStart(CBufferList* clientBuffer, Boolean endOfFrame);
		void					KillPutStart();

		void					GetBytesStart(CBufferList* clientBuffer);
		void					GetFramedBytesStart(CBufferList* clientBuffer);
		void					GetBytesImmediateStart(CBufferList* clientBuffer, Size threshold);
		void					KillGetStart();

		void					HandleTimerTick();

		void					HandleRequest(UChar* request, ULong requestSize, TUMsgToken& msgToken, ULong msgType);
		void					HandleReply(ULong userRefCon, ULong msgType);

		void					KillControlStart();

		void					KillGetCommEventStart();

		void					GetCommEvent();

		ULong					ProcessOptionStart(TOption* theOption, ULong label, ULong opcode);	// 2.0
		ULong					ProcessPutBytesOptionStart(TOption* theOption, ULong label, ULong opcode);	// 2.0
		ULong 					ProcessGetBytesOptionStart(TOption* theOption, ULong label, ULong opcode);	// 2.0

		void					ResArbReleaseStart(UChar* resName, UChar* resType);	// 2.0
		void					ResArbClaimNotification(UChar* resName, UChar* resType);	// 2.0

		TUPort*					ForwardOptions();	// 2.0


};

#endif /* PCONNECTIONEND_H */