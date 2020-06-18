/*
	File:		PMuxCallBack.h

	Contains:	Protocol interface for TMuxTool callbacks routines.
				Typically, the system will call out to the PMuxTool
				for things like OpenMux, etc.  When complete, the
				PMuxTool implementation will call PMuxCallBack::OpenMuxComplete.

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v3 (4/13/95) internal.

*/



#ifndef	__PMUXCALLBACK_H
#define __PMUXCALLBACK_H

#ifndef __CONFIGCOMMUNICATIONS_H
#include "ConfigCommunications.h"
#endif

#ifndef __NEWTONTIME_H
#include "NewtonTime.h"
#endif

#ifndef __PROTOCOLS_H
#include "Protocols.h"
#endif

#ifndef __PCONNECTIONEND_H
#include "PConnectionEnd.h"
#endif

#ifndef	__USERPORTS_H
#include "UserPorts.h"
#endif

#ifndef __COMMERRORS_H
#include "CommErrors.h"
#endif

#ifndef	__OSERRORS_H
#include "OSErrors.h"
#endif

class TMuxTool;

//--------------------------------------------------------------------------------
//		PMuxCallBack
//--------------------------------------------------------------------------------
PROTOCOL PMuxCallBack : public TProtocol
{
	public:
		static	PMuxCallBack*		New(char*);		// initialize state, return this
		void						Delete();		// clean up

		void						Init(TMuxTool* muxToolPtr);

		void						OpenMuxComplete(NewtonErr result);	// if result == noErr, the MuxTool moves to the open state
		void						CloseMuxComplete(NewtonErr result);	// If result == kCommErrToolBusy then leave the mux tool open

		void						HandleRequest(UChar* msgBuf, TUMsgToken& msgToken, ULong msgType);
		void						HandleReply(ULong userRefCon, ULong msgType);

		TUPort*						GetMuxPort();	// returns a pointer to the MuxToolPort

		NewtonErr					InitAsyncRPCMsg(TUAsyncMessage& asyncMsg, ULong refCon);	// Initialize a TUAsyncMessage for async RPC

		TTimeout					GetTimerPeriod(); // returns period used by "tick" timer.  NOTE: One timer is shared by the MuxTool and all connection ends
		void						SetTimerPeriod(TTimeout timerPeriod);
};


#endif /* __PMUXCALLBACK_H */