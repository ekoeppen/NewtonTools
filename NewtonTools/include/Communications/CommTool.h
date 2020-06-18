/*
	File:		CommTool.h

	Contains:	Base class for communications tools.

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	NOTE:  This external file was merged from v80 and v77 of the internal files.

*/



#ifndef	__COMMTOOL_H
#define __COMMTOOL_H

#ifndef __CONFIGCOMMUNICATIONS_H
#include "ConfigCommunications.h"
#endif

#include "CommErrors.h"

#ifndef	__OSERRORS_H
#include "OSErrors.h"
#endif

#ifndef	__USERPORTS_H
#include "UserPorts.h"
#endif

#ifndef	__USERTASKS_H
#include "UserTasks.h"
#endif

#ifndef	__NAMESERVER_H
#include "NameServer.h"
#endif

#ifndef	__BUFFERLIST_H
#include "BufferList.h"
#endif

#ifndef	__BUFFERSEGMENT_H
#include "BufferSegment.h"
#endif

#ifndef	__AEVENTS_H
#include "AEvents.h"
#endif

#ifndef	__OPTIONARRAY_H
#include "OptionArray.h"
#endif

#ifndef	__COMMOPTIONS_H
#include "CommOptions.h"
#endif

#ifndef	__COMMTOOLOPTIONS_H
#include "CommToolOptions.h"
#endif

#ifndef	__COMMADDRESSES_H
#include "CommAddresses.h"
#endif

#ifndef	__TRANSPORT_H
#include "Transport.h"
#endif

#ifndef __TRACEEVENTS_H
#include "TraceEvents.h"
#endif


//--------------------------------------------------------------------------------
//		CommTool Tracing
//--------------------------------------------------------------------------------

// All comm tools descend from TCommTool, so we define a trace buffer that all
// subclasses can use. It is defined if hasBasicCommTracing is true.
// Macros for using this buffer are defined here as well.
//
// If hasBasicCommTracing is defined, the COMM_BASIC_ADDR_TRACE and COMM_BASIC_TRACE_EVENT
// generate code. If hasFullCommTracing is defined, COMM_TRACE_EVENT and COMM_ADDR_TRACE
// are also active.
//
// NOTE: Subclass tools should use their own "traceXXXTool" to control tracing in that
// tool by defining away any of these macros used as follows:
//
// #if defined(traceXXXTool)
//  	#if defined(hasFullCommTracing)
//		EventTraceCauseDesc XXXToolTraceEvents[] = {
//		etc...
//		};
//  	#endif // hasFullCommTracing
// #else
// 		#define	COMM_BASIC_ADDR_TRACE()
//		#define	COMM_BASIC_TRACE_EVENT(x, y)
//		#define	COMM_ADDR_TRACE()
//		#define	COMM_TRACE_EVENT(x, y)
// #endif // traceXXXTool
//
// ... and later in the constructor:
//
//	#if defined(traceXXXTool) && defined(hasFullCommTracing)
//	fEventBuffer->AddDescriptions (XXXToolTraceEvents, sizeof (XXXToolTraceEvents)/ sizeof (EventTraceCauseDesc));
//	#endif
//
// Direct subclasses can add event buffer descriptors (AddDescriptions) for events
// defined starting at kLastCommTraceEvent...

#ifdef hasBasicCommTracing
#define	COMM_BASIC_ADDR_TRACE() fEventBuffer->AddAddress ()
#define	COMM_BASIC_TRACE_EVENT(x, y) fEventBuffer->Add ((unsigned long)(((unsigned long)((x) & 0xFF) << 24) + ((unsigned long)((y) & 0xFF) << 16) + (unsigned long)((y) & 0xFFFF)))
#define	COMM_BASIC_TRACE_EVENT2(x, y, z) fEventBuffer->Add ((unsigned long)(((unsigned long)((x) & 0xFF) << 24) + ((unsigned long)((y) & 0xFF) << 16) + (unsigned long)((z) & 0xFFFF)))
#else
#define	COMM_BASIC_ADDR_TRACE()
#define	COMM_BASIC_TRACE_EVENT(x, y)
#define	COMM_BASIC_TRACE_EVENT2(x, y, z)
#endif

#ifdef hasFullCommTracing
#define	COMM_ADDR_TRACE() fEventBuffer->AddAddress ()
#define	COMM_TRACE_EVENT(x, y) fEventBuffer->Add ((unsigned long)(((unsigned long)((x) & 0xFF) << 24) + ((unsigned long)((y) & 0xFF) << 16) + (unsigned long)((y) & 0xFFFF)))
#define	COMM_TRACE_EVENT2(x, y, z) fEventBuffer->Add ((unsigned long)(((unsigned long)((x) & 0xFF) << 24) + ((unsigned long)((y) & 0xFF) << 16) + (unsigned long)((z) & 0xFFFF)))
#else
#define	COMM_ADDR_TRACE()
#define	COMM_TRACE_EVENT(x, y)
#define	COMM_TRACE_EVENT2(x, y, z)
#endif

#define kLastCommTraceEvent (96)

extern NewtonErr InitCommTools();


// Tool types
const ULong				kConnectionCommTool = 'cnct';
const ULong				kTranslationCommTool = 'trsl';

// Tool sub-types
const ULong				kSessionCnctCommTool = 'sson';
const ULong				kSessionlessCnctCommTool = 'sson';
const ULong				kBitMapTrslCommTool = 'bitm';

const ULong				kCommToolStackSize = 6000;
const ULong				kCommToolMaxRequestSize = 64;

const Size				kCommToolDefaultHeapSize = 50000;


//--------------------------------------------------------------------------------
//		CommToolOpCodes
//--------------------------------------------------------------------------------

// the standard CommToolOpCodes correspond to standard Comm Tool control calls
// these opcodes, as well as the message types define the interface for sending
// events FROM THE CLIENT TO THE TOOL

enum CommToolOpCodes
{
	kCommToolOpen = 1,				// open comm tool (create instance variables)
	kCommToolClose,					// dispose connection end instance variables
	kCommToolConnect,				// for tools that support connection, initiate connection (active)
	kCommToolListen,				// for tools that support connection, listen for connection (passive)
	kCommToolAccept,				// for tools that support connection, accept connection request (passive)
	kCommToolDisconnect,			// terminate current connection (aborting current data) (active),  or reject conn. request (passive)
	kCommToolRelease,				// orderly connection shut down
	kCommToolBind,					// bind tool connection end to address (passive)
	kCommToolUnbind,				// unbind tool connection end to address (passive)
	kCommToolOptionMgmt,			// option management
	kCommToolGetProtAddr,			// get local and remote protocol address of connection
	kCommToolCreateConnectionEnd,	// create a connection end
	kCommToolDisposeConnectionEnd,	// destroy a connection end
	kCommToolOpenMux				// Open a multiplexting commTool (aka MuxTool)
};

// NOTE - Control call OpCodes are shared by TCommTool as well as tool implementations.
// Tool implementation begin defining their opcodes at kCommToolCmdMax.
// So if TCommTool ever needs more than 256 commands, this will effect all
// tool implementations which define their own control call opcodes.
#define kCommToolCmdMax		(256)				// must be last command



enum CommToolStatusOpCodes
{
	kCommToolGetConnectState = 1,			// returns current tool connect state
	kCommToolDumpState,						// for testing/debug, returns more than you ever wanted to know
	kCommToolStatusMax
};


enum CommToolResArbOpCodes
{
	kCommToolResArbRelease = 1,			// request to release resource
	kCommToolResArbClaimNotification	// notification of active ownership of passive resource
};


//--------------------------------------------------------------------------------
//		CommToolEvents
//--------------------------------------------------------------------------------

enum CommToolEvents
{
	kCommToolEventDisconnected = T_DISCONNECT,		// current connection gone, this event can be returned after a connect call has completed successfully

	kCommToolEventSerialEvent = T_SPECEVT,			// serial tool event, e.g., DCD change, break rcvd., etc.

	kCommToolEventProgressEvent = T_PROGRESSEVT		// progress event, e.g., N fax lines have been received.

	// Motorola Radio Tool:  32000 to 32999
};

//--------------------------------------------------------------------------------
//		CommToolRequestType
//--------------------------------------------------------------------------------

enum CommToolRequestType
{
	kCommToolRequestTypeGet				= 0x00000001,		// get requests use this channel
	kCommToolRequestTypePut				= 0x00000002,		// put requests use this channel
	kCommToolRequestTypeControl			= 0x00000004,		// control calls use this channel
	kCommToolRequestTypeGetEvent		= 0x00000008,		// Get Comm Event requests use this channel
	kCommToolRequestTypeKill			= 0x00000010,		// kill request
	kCommToolRequestTypeStatus			= 0x00000020,		// status calls use this channel
	kCommToolRequestTypeResArb			= 0x00000040,		// resource arbitration requests use this channel

	kCommToolRequestTypeMask			= 0x000000ff		// mask for CommTool requests
};

//--------------------------------------------------------------------------------
//		CommToolChannelNumber
//--------------------------------------------------------------------------------

enum CommToolChannelNumber
{
	kCommToolGetChannel				= 0,
	kCommToolPutChannel,
	kCommToolControlChannel,
	kCommToolGetEventChannel,
	kCommToolKillChannel,
	kCommToolStatusChannel,
	kCommToolResArbChannel,
	kCommToolNumChannels
};


// CommTool reserved TUAsyncMessage refCon's
//
enum
{
	kToolMsgForwardOpt				= 20000
};



//--------------------------------------------------------------------------------
//		CommToolConnectInfo
//--------------------------------------------------------------------------------

enum CommToolConnectInfo
{
	kCommConnectionSupportsCallBack	=	0x00000001,			// set if the connection supports call back security
	kCommConnectionViaAppleTalk		= 	0x00000002,			// set if the connection is over AppleTalk
	kCommConnectionReliable			=	0x00000004			// set if the connection is reliable (guaranteed in order delivery)
};

enum
{
	kToolStateConnecting			= 0x00000001,			// tool is trying to establish a connection
	kToolStateConnected				= 0x00000002,			// tool is connected
	kToolStateWantAbort				= 0x00000004,			// aborting or waiting to abort task
	kToolStateRelease				= 0x00000008,			// orderly connection shut down.
	kToolStateClosing				= 0x00000010,			// set when tool is closing down
	kToolStateDisconnectReq			= 0x00000020,			// set when disconnect request is pending
	kToolStateListenMode			= 0x00000040,
	kToolStateTerminating			= 0x00000080,			// set when connection is being terminated
	kToolStateBound					= 0x00000100			// set when the endpoint is in bound state
};


// fOptionsState
enum
{
	kOptionsInProgress				=	0x00000001,			// set if option array is being processed
	kOptionsNotProcessed			=	0x00000002,			// set when an option is not processed, attempt to forward request
	kOptionsArrayAllocated			=	0x00000004,			// set when option array is allocated for an "outside" request
	kOptionsForwardReqActive		=	0x00000008,			// set when option request has been forwarded, and RPC is in progress
	kOptionsForwardMsgAllocated		=	0x00000010,			// set when message blocks for options forward request have been allocated
	kOptionsOutside					=	0x00000020			// set when options request is outside (i.e. uses shared memory object for option array)
};



//--------------------------------------------------------------------------------
//		CommTool Trace Events
//--------------------------------------------------------------------------------

// First subclass can add events starting at kLastCommTraceEvent constant below...


//--------------------------------------------------------------------------------
//		TCommToolAEvent
//--------------------------------------------------------------------------------

class TCommToolAEvent : public TAEvent
{
	public:
							TCommToolAEvent();
};



//--------------------------------------------------------------------------------
//		TCommToolControlRequest
//--------------------------------------------------------------------------------
class TCommToolControlRequest : public TCommToolAEvent
{
	public:
							TCommToolControlRequest();

		ULong				fOpCode;					// Request operation code, used to differentiate control calls
};


//--------------------------------------------------------------------------------
//		TCommToolReply
//--------------------------------------------------------------------------------

// for most CommTool RPC requests, the reply is a long indicating the result
// of the request.  Other requests, such as Get, return more information

class TCommToolReply : public TCommToolAEvent
{
	public:
							TCommToolReply();

		NewtonErr			fResult;					// indicates result of request

		ULong				fSize;						// Size of this reply
};


//--------------------------------------------------------------------------------
//		TCommToolPutRequest
//--------------------------------------------------------------------------------
class TCommToolPutRequest : public TCommToolAEvent
{
	public:

		TCommToolPutRequest();

		CBufferList*	fData;				// data list, or shared memory TObjectId

		// these fields are for clients outside our domain

		Long			fValidCount;		// count of valid bytes in fData; -1 == "all"
											// data is assumed to start at offset 0
		Boolean			fOutside;			// TRUE, fData is a shared memory object id

		// these fields are for clients using framing
		Boolean			fFrameData;			// TRUE, use framing
		Boolean			fEndOfFrame;		// TRUE, close the frame

		// Optional options for Put request
		TOptionArray*	fOptions;			// 2.0 // TOptionArray
		ULong			fOptionCount;		// 2.0 // number of options specified in the request option array, only used if outside
};


//--------------------------------------------------------------------------------
//		TCommToolPutReply
//--------------------------------------------------------------------------------
class TCommToolPutReply : public TCommToolReply
{
	public:
							TCommToolPutReply();

		ULong				fPutBytesCount;				// number of bytes put
};


//--------------------------------------------------------------------------------
//		TCommToolGetRequest
//--------------------------------------------------------------------------------
class TCommToolGetRequest : public TCommToolAEvent
{
	public:

		TCommToolGetRequest();

		CBufferList*	fData;				// data list, or shared memory TObjectId
		Size			fThreshold;			// for fNonBlocking TRUE, do not complete until
											// at least this many bytes have arrived
											// if zero, then complete immediately
		Boolean			fNonBlocking;		// TRUE, return as soon as fThreshold is satisfied
		Boolean			fFrameData;			// TRUE, deframe the data as it arrives
		Boolean			fOutside;			// TRUE, fData is a shared memory object id
		TOptionArray*	fOptions;			// 2.0 // TOptionArray
		ULong			fOptionCount;		// 2.0 // number of options specified in the request option array, only used if outside
};


//--------------------------------------------------------------------------------
//		TCommToolGetReply
//--------------------------------------------------------------------------------
class TCommToolGetReply : public TCommToolReply
{
	public:
							TCommToolGetReply();

		Boolean				fEndOfFrame;
		ULong				fGetBytesCount;				// number of bytes got
};


//--------------------------------------------------------------------------------
//		TCommToolOpenRequest
//--------------------------------------------------------------------------------
class TCommToolOpenRequest : public TCommToolControlRequest
{
	public:
							TCommToolOpenRequest();

		TOptionArray*		fOptions;					// open options array
		ULong				fOptionCount;				// number of options specified in the option array

		Boolean				fOutside;					// fOptionArray is actually a sharedId
};


//--------------------------------------------------------------------------------
//		TCommToolOpenReply
//--------------------------------------------------------------------------------
class TCommToolOpenReply : public TCommToolReply

{
	public:
							TCommToolOpenReply();

		TObjectId			fPortId;					// Id of port for tool or connection end
};


//--------------------------------------------------------------------------------
//		TCommToolConnectRequest
//--------------------------------------------------------------------------------

//	used for listen, accept, and connect

class TCommToolConnectRequest : public TCommToolControlRequest
{
	public:
						TCommToolConnectRequest();

		ULong				fReserved1;				// reserved, don't use
		ULong				fReserved2;				// reserved, don't use
		TOptionArray*		fOptions;				// TOptionArray
		ULong				fOptionCount;			// number of options specified in the request option array
		CBufferSegment*		fData;					// CBufferSegment
		ULong				fSequence;				// from TCommToolListenReply

		Boolean				fOutside;				// if TRUE, the above are TObjectId's
};


//--------------------------------------------------------------------------------
//		TCommToolConnectReply
//--------------------------------------------------------------------------------
class TCommToolConnectReply : public TCommToolReply

//	used for listen, accept, and connect

{
	public:
							TCommToolConnectReply();

		ULong				fSequence;
};


//--------------------------------------------------------------------------------
//		TCommToolDisconnectRequest
//--------------------------------------------------------------------------------
class TCommToolDisconnectRequest : public TCommToolControlRequest
{
	public:
						TCommToolDisconnectRequest();

		CBufferSegment*		fDisconnectData;			// CBufferSegment
		ULong				fSequence;					// from TCommToolListenReply, zero otherwise
		ULong				fReason;					// reason code

		Boolean				fOutside;					// if TRUE, the above *'s are TObjectId's
};


//--------------------------------------------------------------------------------
//		TCommToolBindRequest
//--------------------------------------------------------------------------------
class TCommToolBindRequest : public TCommToolControlRequest
{
	public:
						TCommToolBindRequest();

		ULong				fReserved1;					// reserved, don't use
		ULong				fReserved2;					// reserved, don't use

		Boolean				fOutside;					// if TRUE, the above *'s are TObjectId's
		Boolean				fCopyBack;					// if TRUE and fOutside TRUE, copy back the data on reply

		TOptionArray*		fOptions;					// used as both a request and reply parameter
		ULong				fOptionCount;				// number of options specified in the request option array

};


//--------------------------------------------------------------------------------
//		TCommToolBindReply
//--------------------------------------------------------------------------------
class TCommToolBindReply : public TCommToolReply
{
	public:
							TCommToolBindReply();

		ULong				fWastedULong;
};



//--------------------------------------------------------------------------------
//		TCommToolOptionMgmtRequest
//--------------------------------------------------------------------------------
class TCommToolOptionMgmtRequest : public TCommToolControlRequest
{
	public:
						TCommToolOptionMgmtRequest();

		TOptionArray*		fOptions;				// used as both a request and reply parameter
		ULong				fOptionCount;			// number of options specified in the request option array
		ULong				fRequestOpCode;

		Boolean				fOutside;				// if TRUE, the above *'s are TObjectId's
		Boolean				fCopyBack;				// if TRUE and fOutside TRUE, copy back the data on reply
};


//--------------------------------------------------------------------------------
//		TCommToolGetProtAddrRequest
//--------------------------------------------------------------------------------
class TCommToolGetProtAddrRequest : public TCommToolControlRequest
{
	public:
						TCommToolGetProtAddrRequest();

		// NOTE: these fields are used as return values,
		// and are valid only after the GetProtAddr request has completed

		TOptionArray*		fBoundAddr;
		TOptionArray*		fPeerAddr;

		Boolean				fOutside;					// if TRUE, the above *'s are TObjectId's
};


//--------------------------------------------------------------------------------
//		TCommToolGetEventReply
//--------------------------------------------------------------------------------

class TCommToolGetEventReply : public TCommToolReply
{
	public:
							TCommToolGetEventReply();

		ULong				fEventCode;					// the event
		TTime				fEventTime;					// global time event occurred
		ULong				fEventData;					// event data
		ULong				fServiceId;					// Service Id of tool which originated the event
};


//--------------------------------------------------------------------------------
//		TCommToolKillRequest
//--------------------------------------------------------------------------------
class TCommToolKillRequest : public TCommToolAEvent
{
	public:
						TCommToolKillRequest();

														// defaults to all channels
		CommToolRequestType	fRequestsToKill;			// bit map of request types to kill
		// NOTE:  kill is not valid on status or timer or kill channel
};


//--------------------------------------------------------------------------------
//		TCommToolStatusRequest
//--------------------------------------------------------------------------------
class TCommToolStatusRequest : public TCommToolControlRequest
{
	public:
						TCommToolStatusRequest();

		TObjectId		fStatusInfoId;			// shared memory id of container for status info
};


//--------------------------------------------------------------------------------
//		TCommToolResArbRequest
//--------------------------------------------------------------------------------
class TCommToolResArbRequest : public TCommToolControlRequest
{
	public:
						TCommToolResArbRequest();

		UChar*			fResNamePtr;			// pointer to resource name "C" string
		UChar*			fResTypePtr;			// pointer to resource type "C" string
};


//--------------------------------------------------------------------------------
//		TCommToolMsgContainer
//--------------------------------------------------------------------------------
class TCommToolMsgContainer : public SingleObject
{
	public:
							TCommToolMsgContainer();

		Boolean				fRequestPending;
		ULong				fRequestMsgSize;
		TUMsgToken			fMsgToken;
};


//--------------------------------------------------------------------------------
//		TCommOptionInfo
//--------------------------------------------------------------------------------
class TCommToolOptionInfo : public SingleObject
{
	public:
							TCommToolOptionInfo();

		ULong					fOptionsState;
		CommToolChannelNumber	fChannelNum;			// channel number of options request
		ULong					fOptionCount;			// used for outside requests only, indicates number of options in option array
		TOptionArray* 			fOptions;				// pointer to request options
		TOption*				fCurOptPtr;				// pointer to current option
		TOptionIterator*		fOptionsIterator;		// pointer to option array iterator for current options request
};


typedef Boolean (*TerminateProcPtr)(void* refPtr);


//--------------------------------------------------------------------------------
//		ConnectParms
//--------------------------------------------------------------------------------
struct ConnectParms
{
	CBuffer*		udata;
	ULong			sequence;
	Boolean			outside;
};

typedef struct ConnectParms ConnectParms, *ConnectParmsPtr;



#endif /* __COMMTOOL_H */
