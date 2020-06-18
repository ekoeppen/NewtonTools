/*
	File:		SystemEvents.h

	Copyright:	� 1993-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v11 internal.

*/

#ifndef	__SYSTEMEVENTS_H
#define __SYSTEMEVENTS_H

#ifndef 	__NEWTON_H
#include 	"Newton.h"
#endif
#ifndef		__KERNELTYPES_H
#include	"KernelTypes.h"
#endif
#ifndef		__NAMESERVER_H
#include	"NameServer.h"
#endif
#ifndef		__USERPORTS_H
#include	"UserPorts.h"
#endif

// SystemEvent's
#define kSysEvent_PowerOn				'pwon'
#define kSysEvent_PowerOff				'pwof'
#define kSysEvent_AppAlive				'aliv'
#define kSysEvent_NewICCard				'card'
#define kSysEvent_DeviceNotification	'dnot'
#define kSysEvent_PowerOffPending		'ppen'


class TSystemEvent
{
//	friend	TSendSystemEvent;

	public:
				TSystemEvent(SystemEvent event = 0);

		void	SetEvent(SystemEvent event);

		NewtonErr	RegisterForSystemEvent(TObjectId portId, ULong sendFilter = 0, TTimeout timeout = kNoTimeout);
		NewtonErr	UnRegisterForSystemEvent(TObjectId portId);

	private:
		TUPort				fNameServerPort;
		SystemEvent			fEvent;
};

class TSendSystemEvent : public TSystemEvent
{
	public:
				TSendSystemEvent(SystemEvent event = 0) : TSystemEvent(event){};
		NewtonErr	Init();

		NewtonErr	SendSystemEvent(void* message, ULong messageSize);
		NewtonErr	SendSystemEvent(TUAsyncMessage* asyncMessage, void* message, ULong messageSize, void* reply, ULong replySize);

	private:
		TUSharedMemMsg		fMsgToSend;
		TSysEventRequest	fMsgToNameServer;
};

#endif
