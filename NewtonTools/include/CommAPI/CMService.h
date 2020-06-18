/*
	File:		CMService.h

	Copyright:	� 1992, 1994-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v9 internal.

*/


#ifndef	__CMSERVICE_H
#define __CMSERVICE_H

#ifndef	__NEWTON_H
#include "Newton.h"
#endif

#ifndef __AEVENTS_H
#include "AEvents.h"
#endif

#ifndef __PROTOCOLS_H
#include "Protocols.h"
#endif

#ifndef	__USERPORTS_H
#include "UserPorts.h"
#endif

#ifndef	__COMMMANAGERINTERFACE_H
#include "CommManagerInterface.h"
#endif

#ifndef __OPTIONARRAY_H
#include "OptionArray.h"
#endif

#define kServiceInterfaceName		"TCMService"

class TCMService;
class TUMsgToken;
class TServiceInfo;

extern NewtonErr ServiceToPort(ULong serviceId, TUPort* port);		// DON'T USE; old style, won't work
extern NewtonErr ServiceToPort(ULong serviceId, TUPort* port, TObjectId taskId);	// task Id of service



/* --------------------------------------------------------------------------------
		TAsyncServiceMessage
  -------------------------------------------------------------------------------- */

class TAsyncServiceMessage
{
	public:
						TAsyncServiceMessage();
						~TAsyncServiceMessage();

		TCMService*		Service();

		NewtonErr		Init(TCMService* service);
		NewtonErr		Send(TUPort* destination, void* message, ULong messageSize, void* reply, ULong replySize, ULong messageType = 0);

		Boolean			Match(TUMsgToken* token);		// used internally

	// *** private:

		TCMService*		fService;
		TUAsyncMessage	fAsyncMessage;
		void*			fMessage;
		void*			fReply;
};

inline TCMService* TAsyncServiceMessage::Service()
{
	return fService;
} // Service


/* --------------------------------------------------------------------------------
		TCMService

	Each communications/network service should have a TCMService implementation.

	each service should implement:

	Start:			to start the associated service; returns
					noErr:  			completed immediately with noErr
					kCall_In_Progress:	in process, DoneStarting will be called
					or some error:		failed immediately because of reported error

	DoneStarting:	called when Start has completed

	** possible additions **
	Terminate:		to terminate the associated service
	Message:		when the system needs to inform the service of some system event
	SetOptions:		to set "configuration" options
	GetOptions: 	to get the current set of configuration options

   -------------------------------------------------------------------------------- */



PROTOCOL TCMService : public TProtocol
{
	public:

	static	TCMService*	New(char*);
			void		Delete();

			NewtonErr	Start(TOptionArray* options, ULong serviceId, TServiceInfo* serviceInfo);		// start the service
			NewtonErr	DoneStarting(TAEvent* event, ULong size, TServiceInfo* serviceInfo);			// called back when done starting

};

#endif /* __CMSERVICE_H */
