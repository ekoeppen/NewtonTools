/*
	File:		PMuxTool.h

	Contains:	Protocol interface for "Multiplexing" CommTool.  The MuxTool
				supports multiple simultaneous connections per tool.

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v2 (5/11/95) internal.

*/



#ifndef	__PMUXTOOL_H
#define __PMUXTOOL_H

#ifndef __CONFIGCOMMUNICATIONS_H
#include "ConfigCommunications.h"
#endif

#ifndef __PROTOCOLS_H
#include "Protocols.h"
#endif

#ifndef __COMMTOOL_H
#include "CommTool.h"
#endif

#ifndef __COMMERRORS_H
#include "CommErrors.h"
#endif

#ifndef	__OSERRORS_H
#include "OSErrors.h"
#endif

#ifndef __PMUXTOOLCALLBACK_H
#include "PMuxCallBack.h"
#endif

#ifndef __PCONNECTIONEND_H
#include "PConnectionEnd.h"
#endif

//--------------------------------------------------------------------------------
//		PMuxTool
//--------------------------------------------------------------------------------
PROTOCOL PMuxTool : public TProtocol
{
	public:
		static PMuxTool*		New(char*);		// initialize state, return this
		void					Delete();		// clean up

		void					OpenMuxStart(PMuxCallBack* muxCallBack, TCommToolOpenRequest* fRequest);		// Open the MuxTool, when complete call PMuxToolCallBack::OpenComplete
		void					CloseMuxStart();		// Close the MuxTool, when complete call PMuxToolCallBack::CloseComplete

		PConnectionEnd*			NewConnectionEnd();
		void					DisposeConnectionEnd(PConnectionEnd* connectionEndPtr);

		void					HandleTimerTick();	// called every timer period

		void					HandleRequest(UChar* msgBuf, TUMsgToken& msgToken, ULong msgType);
		void					HandleReply(ULong userRefCon, ULong msgType);

								// This is the hook for associated PConnectionEnds.  This may be used, for example, to send a packet
		void					HandleInternalRequest(void* msgBuf);

		void					HandleInternalEvent();	// called each time thru main receive loop, allows for deferred processing
};



#endif /* __PMUXTOOL_H */