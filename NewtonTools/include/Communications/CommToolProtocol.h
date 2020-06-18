/*
	File:		CommToolProtocol.h

	Copyright:	� 1993-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v5 internal.

*/

#ifndef __COMMTOOLPROTOCOL_H
#define __COMMTOOLPROTOCOL_H

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

				void					Bind();
				void					Unbind();

				void					GetProtAddr();

				ULong					ProcessOption(TOption* theOption, ULong label, ULong opcode);
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
				void					GetNextTermProc(ULong terminationPhase,ULong& terminationFlag,TerminateProcPtr& TerminationProc);

				void					SetChannelFilter(int msgType, Boolean enable);

	/*	callbacks for base CommTool behavior, call as "utility" functions or treat as
		inherited calls (i.e. given function X(), inherited::X() would be CTX())
	*/

	NONVIRTUAL	NewtonErr				CTTaskConstructor();
	NONVIRTUAL	void					CTTaskDestructor();
	NONVIRTUAL	NewtonErr				CTGetToolPort(TObjectName toolId, TUPort& port);
	NONVIRTUAL	TObjectName				CTGetToolId();

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

	NONVIRTUAL	void					CTOpenContinue();
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

	NONVIRTUAL	void					CTGetProtAddr();

	NONVIRTUAL	ULong					CTProcessOption(TOption* theOption, ULong label, ULong opcode);
	NONVIRTUAL	NewtonErr				CTAddDefaultOptions(TOptionArray* options);
	NONVIRTUAL	NewtonErr				CTAddCurrentOptions(TOptionArray* options);

	NONVIRTUAL	void					CTPutComplete(NewtonErr result, ULong putBytesCount);
	NONVIRTUAL	void					CTKillPutComplete(NewtonErr result);
	NONVIRTUAL	void					CTGetComplete(NewtonErr result, Boolean endOfFrame = false, ULong getBytesCount = 0);
	NONVIRTUAL	void					CTKillGetComplete(NewtonErr result);

	NONVIRTUAL	void					CTKillRequestComplete(CommToolRequestType requestTypeKilled, NewtonErr killResult);

	NONVIRTUAL	void					CTHoldAbort();
	NONVIRTUAL	void					CTAllowAbort();
	NONVIRTUAL	NewtonErr				CTStartAbort(NewtonErr abortError);
	NONVIRTUAL	Boolean					CTShouldAbort(ULong stateFlag, NewtonErr result);

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

	NONVIRTUAL	NewtonErr				CTGetAbortErr();
	NONVIRTUAL	void					CTSetAbortErr(NewtonErr err);

	NONVIRTUAL	ULong					CTGetTerminationEvent();
	NONVIRTUAL	void					CTSetTerminationEvent(ULong event);

	NONVIRTUAL	TCMOCTConnectInfo&		CTGetConnectInfo();
	NONVIRTUAL	void					CTSetConnectInfo(TCMOCTConnectInfo& info);

	NONVIRTUAL	ULong					CTGetRequestSize();
	NONVIRTUAL	UChar*					CTGetRequest();

	NONVIRTUAL	TCommToolMsgContainer	CTGetRequestListItem(UChar item);
	NONVIRTUAL  ConnectParms&		  	CTGetConnectParms();

	NONVIRTUAL	TCMOTransportInfo&		CTGetCMOTransportInfo();
	NONVIRTUAL	void					CTSetCMOTransportInfo(TCMOTransportInfo& info);

	NONVIRTUAL 	CommToolRequestType		CTGetRequestsToKill();
	NONVIRTUAL  void					CTSetRequestsToKill(CommToolRequestType rType);

	// private, don't use
	NONVIRTUAL	void					ToolInit(TPCommTool* tool);

	//private:

				TPCommTool*				fCommTool;
};

#endif
