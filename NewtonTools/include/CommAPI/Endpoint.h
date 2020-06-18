/*
	File:		Endpoint.h

	Contains:	Protocol Interface for TEndpoint's

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v32 internal.

*/

#ifndef __ENDPOINT_H
#define __ENDPOINT_H

#ifndef	__NEWTON_H
#include "Newton.h"
#endif

#ifndef __PROTOCOLS_H
#include <Protocols.h>
#endif

#ifndef __TRANSPORT_H
#include "Transport.h"
#endif

#ifndef __LONGTIME_H
#include <LongTime.h>
#endif


class TEndpointEventHandler;
class TAEventHandler;
class TAEvent;
class CBufferSegment;
class TUMsgToken;
class TAppWorld;
class TOptionArray;
class CBufferSegment;
class TCMOTransportInfo;


// "which" parm to IsPending()
#define	kSyncCall				(0x01)
#define	kAsyncCall				(0x02)
#define	kEitherCall				(0x03)

//--------------------------------------------------------------------------------
//		TEndpoint
//--------------------------------------------------------------------------------

PROTOCOL TEndpoint : public TProtocol
{

public:

		static		TEndpoint*	New(char*);
					void		Delete(void);

	// delete the endpoint, but leave the tool running
		NONVIRTUAL	TObjectId	DeleteLeavingTool(void);

	// called as part of CMGetEndpoint
		NONVIRTUAL	NewtonErr	InitBaseEndpoint(TEndpointEventHandler* handler);
		NONVIRTUAL	void		SetClientHandler(ULong clientHandler);

	// EventHandler interface

					Boolean		HandleEvent(ULong msgType, TAEvent* event, ULong msgSize);
					Boolean		HandleComplete(TUMsgToken* msgToken, ULong* msgSize, TAEvent* event);

	// For handing endpoints around
	// passed on to TEnpointEventHandler

					NewtonErr	AddToAppWorld(void);				// assumes gAppWorld
					NewtonErr	RemoveFromAppWorld(void);			// assumes gAppWorld

	// Client interface

					NewtonErr	Open(ULong clientHandler = 0);
					NewtonErr	Close(void);
					NewtonErr	Abort(void);

		NONVIRTUAL	NewtonErr	GetInfo(TCMOTransportInfo* info);
		NONVIRTUAL	Long		GetState(void);
		NONVIRTUAL	Boolean		IsSync(void);
		NONVIRTUAL	void		GetAbortParameters(ULong& eventID, ULong& refCon);

		Boolean		SetSync(Boolean sync);

		NewtonErr	GetProtAddr(TOptionArray* bndAddr, TOptionArray* peerAddr, TTimeout timeOut = kNoTimeout);
		NewtonErr	OptMgmt(ULong arrayOpCode, TOptionArray* options, TTimeout timeOut = kNoTimeout);

		NewtonErr	Bind(TOptionArray* addr = nil, Long* qlen = nil, TTimeout timeOut = kNoTimeout);
		NewtonErr	UnBind(TTimeout timeOut = kNoTimeout);

		NewtonErr	Listen(TOptionArray* addr = nil, TOptionArray* opt = nil, CBufferSegment* data = nil,
							Long* seq = nil, TTimeout timeOut = kNoTimeout);

		NewtonErr	Accept(TEndpoint* resfd, TOptionArray* addr = nil, TOptionArray* opt = nil,
							CBufferSegment* data = nil, Long seq = 0, TTimeout timeOut = kNoTimeout);

		NewtonErr	Connect(TOptionArray* addr = nil, TOptionArray* opt = nil, CBufferSegment* data = nil,
							Long* seq = nil, TTimeout timeOut = kNoTimeout);

		NewtonErr	Disconnect(CBufferSegment* data = nil, Long reason = 0, Long seq = 0);
		NewtonErr	Release(TTimeout timeOut = kNoTimeout);

		NewtonErr	Snd(UByte* buf, Size& nBytes, ULong flags, TTimeout timeOut = kNoTimeout);
		NewtonErr	Rcv(UByte* buf, Size& nBytes, Size thresh, ULong* flags, TTimeout timeOut = kNoTimeout);

		// alternate versions of same...
		NewtonErr	Snd(CBufferSegment* buf, ULong flags, TTimeout timeOut = kNoTimeout);
		NewtonErr	Rcv(CBufferSegment* buf, Size thresh, ULong* flags, TTimeout timeOut = kNoTimeout);

		// wait for an expected event to arrive
		NewtonErr	WaitForEvent(TTimeout timeOut = kNoTimeout);

		// convenience functions
		NONVIRTUAL	NewtonErr	EasyOpen(ULong clientHandler = 0);		// calls default Open/Bind/Connect
		NONVIRTUAL	NewtonErr	EasyConnect(ULong clientHandler = 0,
									TOptionArray* options = nil, TTimeout timeOut = kNoTimeout);
		NONVIRTUAL	NewtonErr	EasyClose(void);						// calls default Disconnect/UnBind/Close

	protected:

		NONVIRTUAL	void	DestroyBaseEndpoint(void);		// impl's must call this in ::Delete()

	public:

		// New calls for 2.0

		NewtonErr	nBind(TOptionArray* opt = nil, TTimeout timeOut = kNoTimeout, Boolean sync = true);

		NewtonErr	nListen(TOptionArray* opt = nil, CBufferSegment* data = nil, Long* seq = nil,
							TTimeout timeOut = kNoTimeout, Boolean sync = true);

		NewtonErr	nAccept(TEndpoint* resfd, TOptionArray* opt = nil, CBufferSegment* data = nil,
							Long seq = 0, TTimeout timeOut = kNoTimeout, Boolean sync = true);

		NewtonErr	nConnect(TOptionArray* opt = nil, CBufferSegment* data = nil, Long* seq = nil,
							TTimeout timeOut = kNoTimeout, Boolean sync = true);

		NewtonErr	nRelease(TTimeout timeOut = kNoTimeout, Boolean sync = true);

		NewtonErr	nDisconnect(CBufferSegment* data = nil, Long reason = 0, Long seq = 0,
							TTimeout timeOut = kNoTimeout, Boolean sync = true);

		NewtonErr	nUnBind(TTimeout timeOut = kNoTimeout, Boolean sync = true);

		NewtonErr	nOptMgmt(ULong arrayOpCode, TOptionArray* options, TTimeout timeOut = kNoTimeout,
							Boolean sync = true);

		NewtonErr	nSnd(UByte* buf, Size* count, ULong flags, TTimeout timeOut = kNoTimeout,
							Boolean sync = true, TOptionArray* opt = nil);

		NewtonErr	nRcv(UByte* buf, Size* count, Size thresh, ULong* flags, TTimeout timeOut = kNoTimeout,
							Boolean sync = true, TOptionArray* opt = nil);

		NewtonErr	nSnd(CBufferSegment* buf, ULong flags, TTimeout timeOut = kNoTimeout,
							Boolean sync = true, TOptionArray* opt = nil);

		NewtonErr	nRcv(CBufferSegment* buf, Size thresh, ULong* flags, TTimeout timeOut = kNoTimeout,
							Boolean sync = true, TOptionArray* opt = nil);

		NewtonErr	nAbort(Boolean sync = true);

		NewtonErr	Timeout(ULong refCon);

		Boolean		IsPending(ULong which);

		// So endpoint clients can use forks
		NONVIRTUAL	Boolean	UseForks(Boolean justDoIt);		// returns old state

	protected:

		Long					fState;				// state of this endpoint
		TEndpointEventHandler*	fEventHandler;		// our event handler for talking to transport provider
		ULong					fClientRefCon;		// client event handler for setting up client events
		TCMOTransportInfo*		fInfo;				// information about our transport provider
		Boolean					fSync;				// TRUE if we are currently synchronous
		Boolean					fToolIsRunning;		// TRUE if the tool is up and running

}; // TEndpoint


inline Long TEndpoint::GetState(void)
	{ return fState; }

inline Boolean TEndpoint::IsSync(void)
	{ return fSync; }

#endif /* __ENDPOINT_H */
