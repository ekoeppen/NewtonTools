/*
	File:		CommToolProtocolV2.h

	Copyright:	� 1993-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v6 internal.

*/

#ifndef __COMMTOOLPROTOCOLV2_H
#define __COMMTOOLPROTOCOLV2_H

#ifndef __PROTOCOLS_H
#include "Protocols.h"
#endif

#ifndef	__OPTIONARRAY_H
#include "OptionArray.h"
#endif

#ifndef	__COMMTOOL_H
#include "CommTool.h"
#endif

class TServiceInfo;
class TOptionArray;
class TPCommTool;
class TCMService;
PROTOCOL TCommToolProtocol;

NewtonErr StartCommToolProtocol(TOptionArray* options, ULong serviceId, TServiceInfo* serviceInfo, TCMService* service, TCommToolProtocol* ctProtocol);

// 2.0:	New version of StartCommToolProtocol accepts heapSize parameter.
// 		HeapSize is used to set the size of the heap for the TCommToolProtocol implementation.
NewtonErr StartCommToolProtocol(TOptionArray* options, ULong serviceId, TServiceInfo* serviceInfo, TCMService* service, TCommToolProtocol* ctProtocol, Size heapSize);


// Capability key for TCommToolProtocol interface version.
#define kCTInterfaceVersionType			"ctiv"

// If you implement TCommToolProtocol as defined below, you must include a kCTInterfaceVersionType
// with value kCTPInterfaceVersion2Str
// The macro should be used as follows:
//	CAPABILITIES((kCTInterfaceVersionType kCTPInterfaceVersion2Str))

#define	kCTPInterfaceVersion2Str			"2"
const long		kCTPInterfaceVersion2 = 2;

#define kCTInterfaceName		"TCommToolProtocol"

PROTOCOL TCommToolProtocol : public TProtocol
{
	public:

		static	TCommToolProtocol*		New(char*);
				void					Delete();

				NewtonErr				TaskConstructor();
				void					TaskDestructor();

				UChar*					GetToolName();

				void					HandleRequest(TUMsgToken& msgToken, ULong msgType);
				void					HandleReply(ULong userRefCon, ULong msgType);

				void					DoControl(ULong opCode, ULong msgType);
				void					DoKillControl(ULong msgType);
				void					GetCommEvent();
				void					DoKillGetCommEvent();
				NewtonErr				PostCommEvent(TCommToolGetEventReply& theEvent, NewtonErr result);

				NewtonErr				OpenStart(TOptionArray* options);
				NewtonErr				OpenComplete();
				Boolean					Close();
				void					CloseComplete(NewtonErr result);

				void					ConnectStart();
				void					ConnectComplete(NewtonErr result);

				void					ListenStart();
				void					ListenComplete(NewtonErr result);

				void					AcceptStart();
				void					AcceptComplete(NewtonErr result);

				void					DisconnectComplete(NewtonErr result);

				void					ReleaseStart();
				void					ReleaseComplete(NewtonErr result);

				void					Bind();			// Obsolete, leave implementation empty
				void					Unbind();		// Obsolete, leave implementation empty

				void					GetProtAddr();	// Obsolete, leave implementation empty

				ULong					ProcessOption(TOption* theOption, ULong label, ULong opcode);// Obsolete, leave implementation empty
				NewtonErr				AddDefaultOptions(TOptionArray* options);
				NewtonErr				AddCurrentOptions(TOptionArray* options);

				void					PutBytes(CBufferList* clientBuffer);
				void					PutFramedBytes(CBufferList* clientBuffer, Boolean endOfFrame);
				void					PutComplete(NewtonErr result, ULong putBytesCount);

				void					KillPut();
				void					KillPutComplete(NewtonErr result);

				void					GetBytes(CBufferList* clientBuffer);
				void					GetFramedBytes(CBufferList* clientBuffer);
				void					GetComplete(NewtonErr result, Boolean endOfFrame = false, ULong getBytesCount = 0);
				void					GetBytesImmediate(CBufferList* clientBuffer, Size threshold);

				void					KillGet();
				void					KillGetComplete(NewtonErr result);

				void					TerminateConnection();
				void					TerminateComplete();

										// GetNextTermProc is Obsolete, leave implementation empty
				void					GetNextTermProc(ULong terminationPhase,ULong& terminationFlag,TerminateProcPtr& TerminationProc);

				void					SetChannelFilter(int msgType, Boolean enable);


	/*	callbacks for base CommTool behavior, call as "utility" functions or treat as
		inherited calls (i.e. given function X(), inherited::X() would be CTX())
	*/

	NONVIRTUAL	NewtonErr				CTTaskConstructor();
	NONVIRTUAL	void					CTTaskDestructor();

	NONVIRTUAL	NewtonErr				CTGetToolPort(TObjectName toolId, TUPort& port); // private, don't use

	NONVIRTUAL	TObjectName				CTGetToolId();	// private, don't use

	NONVIRTUAL	void					CTCompleteRequest(TUMsgToken& msgToken, NewtonErr result);
	NONVIRTUAL	void					CTCompleteRequest(TUMsgToken& msgToken, NewtonErr result, TCommToolReply& reply);
	NONVIRTUAL	void					CTCompleteRequest(CommToolChannelNumber channel, NewtonErr result);
	NONVIRTUAL	void					CTCompleteRequest(CommToolChannelNumber channel, NewtonErr result, TCommToolReply& reply);

	NONVIRTUAL	void					CTHandleRequest(TUMsgToken& msgToken, ULong msgType);
	NONVIRTUAL	void					CTHandleReply(ULong userRefCon, ULong msgType);

	NONVIRTUAL	void					CTDoControl(ULong opCode, ULong msgType);
	NONVIRTUAL	void					CTDoKillControl(ULong msgType);
	NONVIRTUAL	void					CTGetCommEvent();
	NONVIRTUAL	void					CTDoKillGetCommEvent();
	NONVIRTUAL	NewtonErr				CTPostCommEvent(TCommToolGetEventReply& theEvent, NewtonErr result);

	NONVIRTUAL	void					CTOpenContinue();	// private, don't use

	NONVIRTUAL	NewtonErr				CTOpenStart(TOptionArray* options);
	NONVIRTUAL	NewtonErr				CTOpenComplete();

	NONVIRTUAL	Boolean					CTClose();
	NONVIRTUAL	void					CTCloseComplete(NewtonErr result);

	NONVIRTUAL	void					CTConnectStart();
	NONVIRTUAL	void					CTConnectComplete(NewtonErr result);

	NONVIRTUAL	void					CTListenStart();
	NONVIRTUAL	void					CTListenComplete(NewtonErr result);

	NONVIRTUAL	void					CTAcceptStart();
	NONVIRTUAL	void					CTAcceptComplete(NewtonErr result);

	NONVIRTUAL	void					CTDisconnectComplete(NewtonErr result);

	NONVIRTUAL	void					CTReleaseStart();
	NONVIRTUAL	void					CTReleaseComplete(NewtonErr result);

	NONVIRTUAL	void					CTBind();
	NONVIRTUAL	void					CTUnbind();

	NONVIRTUAL	void					CTGetProtAddr();	// private, don't use

	NONVIRTUAL	ULong					CTProcessOption(TOption* theOption, ULong label, ULong opcode);
	NONVIRTUAL	NewtonErr				CTAddDefaultOptions(TOptionArray* options);
	NONVIRTUAL	NewtonErr				CTAddCurrentOptions(TOptionArray* options);

	NONVIRTUAL	void					CTPutComplete(NewtonErr result, ULong putBytesCount);
	NONVIRTUAL	void					CTKillPutComplete(NewtonErr result);
	NONVIRTUAL	void					CTGetComplete(NewtonErr result, Boolean endOfFrame = false, ULong getBytesCount = 0);
	NONVIRTUAL	void					CTKillGetComplete(NewtonErr result);

	NONVIRTUAL	void					CTKillRequestComplete(CommToolRequestType requestTypeKilled, NewtonErr killResult);

	NONVIRTUAL	void					CTHoldAbort();	// private, don't use
	NONVIRTUAL	void					CTAllowAbort();	// private, don't use

	NONVIRTUAL	NewtonErr				CTStartAbort(NewtonErr abortError);

	NONVIRTUAL	Boolean					CTShouldAbort(ULong stateFlag, NewtonErr result);	// private, don't use

	NONVIRTUAL	void					CTTerminateConnection();
	NONVIRTUAL	void					CTTerminateComplete();

	NONVIRTUAL	NewtonErr				CTInitAsyncRPCMsg(TUAsyncMessage& asyncMsg, ULong refCon);

	NONVIRTUAL	NewtonErr				CTFlushChannel(CommToolRequestType filter, NewtonErr flushResult);

	NONVIRTUAL	void					CTSetChannelFilter(CommToolRequestType msgType, Boolean enable);
	NONVIRTUAL	CommToolChannelNumber	CTRequestTypeToChannelNumber(CommToolRequestType msgType);
	NONVIRTUAL	CommToolRequestType		CTChannelNumberToRequestType(CommToolChannelNumber channelNumber);

	// getters/setters�
	NONVIRTUAL	ULong					CTGetToolConnectState();
	NONVIRTUAL	void					CTSetToolConnectState(ULong state);

	NONVIRTUAL	NewtonErr					CTGetAbortErr();
	NONVIRTUAL	void					CTSetAbortErr(NewtonErr err);

	NONVIRTUAL	ULong					CTGetTerminationEvent();
	NONVIRTUAL	void					CTSetTerminationEvent(ULong event);

	NONVIRTUAL	TCMOCTConnectInfo&		CTGetConnectInfo();
	NONVIRTUAL	void					CTSetConnectInfo(TCMOCTConnectInfo& info);

	NONVIRTUAL	ULong					CTGetRequestSize();
	NONVIRTUAL	UChar*					CTGetRequest();

	NONVIRTUAL	TCommToolMsgContainer	CTGetRequestListItem(UChar item);	// private, don't use
	NONVIRTUAL  ConnectParms&		  	CTGetConnectParms();	// private, don't use

	NONVIRTUAL	TCMOTransportInfo&		CTGetCMOTransportInfo();
	NONVIRTUAL	void					CTSetCMOTransportInfo(TCMOTransportInfo& info);

	NONVIRTUAL 	CommToolRequestType		CTGetRequestsToKill();	// private, don't use
	NONVIRTUAL  void					CTSetRequestsToKill(CommToolRequestType rType);	// private, don't use

	// private, don't use
	NONVIRTUAL	void					ToolInit(TPCommTool* tool);

	// New Methods for 2.0
	// New Getters/setters
	NONVIRTUAL	ULong					CTGetReceiveMessageBufSize();	// 2.0 // returns the size of the buffer used by the commtool to receive rpc messages
																			   // Any message sent to the tool which exceeds this size will be truncated.
	NONVIRTUAL	TUPort*					CTGetToolPort(); // 2.0 // returns a pointer to the tool's port object

	NONVIRTUAL	TCommToolOptionInfo&	CTGetControlOptionsInfo();	// 2.0 // returns the option info for the current control request
	NONVIRTUAL	TCommToolOptionInfo&	CTGetGetBytesOptionsInfo();	// 2.0 // returns the option info for the current get bytes request
	NONVIRTUAL	TCommToolOptionInfo&	CTGetPutBytesOptionsInfo();	// 2.0 // returns the option info for the current put bytes request

	NONVIRTUAL	CBufferList*			CTGetCurPutData();			// 2.0 // returns a pointer to the current put request buffer list
	NONVIRTUAL	Boolean					CTGetCurPutFrameData();		// 2.0 // returns true if current put request is framed
	NONVIRTUAL	Boolean					CTGetCurPutEndOfFrame();	// 2.0 // returns true if current framed put request is end of frame

	NONVIRTUAL	CBufferList*			CTGetCurGetData();			// 2.0 // returns a pointer to the current get request buffer list
	NONVIRTUAL	Boolean					CTGetCurGetFrameData();		// 2.0 // returns true if current get request is framed
	NONVIRTUAL	Boolean					CTGetCurGetNonBlocking();	// 2.0 // returns true if current get request is non blocking (ie has a threshold)
	NONVIRTUAL	Size					CTGetCurGetThreshold();		// 2.0 // returns the value of threshold for the current nonblocking get request

	NONVIRTUAL	Boolean					CTGetPassiveClaim();						// 2.0 // returns true if client asked for passive claim of tool resources
	NONVIRTUAL	void					CTSetPassiveClaim(Boolean passiveClaim);	// 2.0 // Set the value of passive claim

	NONVIRTUAL	Boolean					CTGetPassiveState();						// 2.0 // returns true if in passive state (resources passively claimed, and willing to give up resources)
	NONVIRTUAL	void					CTSetPassiveState(Boolean passiveState);	// 2.0 // Set the value of passive claim

	NONVIRTUAL	Boolean					CTGetWaitingForResNotify();						// 2.0 // returns true if tool has passively claimed resources, and is waiting for notification of resource ownership
	NONVIRTUAL	void					CTSetWaitingForResNotify(Boolean waitingForResNotify);	// 2.0 // Set the value of passive claim

	NONVIRTUAL	ULong					CTGetCurRequestOpCode();	// 2.0 // returns the opcode of the current control request

	// new base class methods
	NONVIRTUAL 	void					CTBindStart();	// 2.0
	NONVIRTUAL 	void					CTBindComplete(NewtonErr result);	// 2.0

	NONVIRTUAL 	void					CTUnbindStart();	// 2.0
	NONVIRTUAL 	void					CTUnbindComplete(NewtonErr result);	// 2.0

	NONVIRTUAL 	ULong					CTProcessOptionStart(TOption* theOption, ULong label, ULong opcode);	// 2.0
	NONVIRTUAL 	void					CTProcessOptionComplete(ULong optResult); 	// 2.0

	NONVIRTUAL 	ULong					CTProcessPutBytesOptionStart(TOption* theOption, ULong label, ULong opcode);	// 2.0
	NONVIRTUAL 	void 					CTProcessPutBytesOptionComplete(ULong optResult);	// 2.0

	NONVIRTUAL 	ULong 					CTProcessGetBytesOptionStart(TOption* theOption, ULong label, ULong opcode);	// 2.0
	NONVIRTUAL 	void 					CTProcessGetBytesOptionComplete(ULong optResult);	// 2.0

	NONVIRTUAL 	void					CTResArbRelease(UChar* resName, UChar* resType);		// 2.0
	NONVIRTUAL 	void					CTResArbReleaseStart(UChar* resName, UChar* resType);	// 2.0
	NONVIRTUAL 	void					CTResArbReleaseComplete(NewtonErr result);				// 2.0

	NONVIRTUAL 	void					CTResArbClaimNotification(UChar* resName, UChar* resType);	// 2.0

	NONVIRTUAL void						CTHandleInternalEvent();	// 2.0

	// new implementation methods
				void					BindStart();	// 2.0
				void					BindComplete(NewtonErr result);	// 2.0

				void					UnbindStart();	// 2.0
				void					UnbindComplete(NewtonErr result);	// 2.0

				ULong					ProcessOptionStart(TOption* theOption, ULong label, ULong opcode);	// 2.0
				void					ProcessOptionComplete(ULong optResult); 	// 2.0

				ULong					ProcessPutBytesOptionStart(TOption* theOption, ULong label, ULong opcode);	// 2.0
				void 					ProcessPutBytesOptionComplete(ULong optResult);	// 2.0

				ULong 					ProcessGetBytesOptionStart(TOption* theOption, ULong label, ULong opcode);	// 2.0
				void 					ProcessGetBytesOptionComplete(ULong optResult);	// 2.0

				void					ResArbRelease(UChar* resName, UChar* resType);		// 2.0
				void					ResArbReleaseStart(UChar* resName, UChar* resType);	// 2.0
				void					ResArbReleaseComplete(NewtonErr result);				// 2.0

				void					ResArbClaimNotification(UChar* resName, UChar* resType);	// 2.0

				TUPort*					ForwardOptions();	// 2.0

				void					HandleInternalEvent();	// 2.0


				TPCommTool*				fCommTool;
};

#endif
