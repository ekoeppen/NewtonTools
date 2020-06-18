/*
	File:		CommErrors.h

	Contains:	Error #defines for TCommTool's

	Copyright:	� 1993-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v21 (8/30/96) internal.

*/

#ifndef	__COMMERRORS_H
#define __COMMERRORS_H

#ifndef __NEWTERRORS_H
#include "NewtErrors.h"
#endif

// CommToolError�
#define kCommErrIOBusy						(1)						// (when set) request is being processed and is not yet complete
																	// currently used by OpenComplete

// ERRBASE_COMMTOOL = (-16000)
#define kCommErrBase						(ERRBASE_COMMTOOL)
#define kCommErrCommandInProgress			(kCommErrBase - 1)
#define kCommErrBadCommand					(kCommErrBase - 2)
#define kCommErrToolBusy					(kCommErrBase - 3)		// tool already has pending all the requests it can handle
																	// when returned from StartService indicates tool already running
#define kCommErrBufferOverflow				(kCommErrBase - 4)
#define kCommErrRequestCanceled				(kCommErrBase - 5)		// request canceled by kill request
#define kCommErrBadParameter				(kCommErrBase - 6)		// bad parameter in request
#define kCommErrNoConnectionEnd				(kCommErrBase - 7)		// connection end has not been created and must be created before request can be processed
#define kCommErrAlreadyConnected			(kCommErrBase - 8)		// invalid call when connected
#define kCommErrNotConnected				(kCommErrBase - 9)		// invalid call when not connected
#define kCommErrIncompatibleRemote			(kCommErrBase - 10)		// connection negotiation failed because remote end is incompatible with local connection end configuration
#define kCommErrRetransLimitReached			(kCommErrBase - 11)		// connection terminated/failed due to retransmission limit of data/connect packet reached
#define kCommErrNoDataAvailable				(kCommErrBase - 12)		// no data available for TCommToolGetRequest when fNonBlocking is TRUE
#define kCommErrConnectionAborted			(kCommErrBase - 13)		// connection aborted by disconnect
#define kCommErrNotSupported				(kCommErrBase - 14)		// call not supported
#define kCommErrNoRequestPending			(kCommErrBase - 15)		// request not pending
#define kCommErrNoEventPending				(kCommErrBase - 16)		// event not pending
#define	kCommErrListenerTimeOut				(kCommErrBase - 17)		// time out waiting for connection
#define kCommErrAlreadyBound				(kCommErrBase - 18)		// connection end already bound
#define kCommErrNotBound					(kCommErrBase - 19)		// connection end needs to be bound before used
#define	kCommErrReleasingConnection			(kCommErrBase - 20)		// connection end is being released
#define	kCommErrNoPhoneNumber				(kCommErrBase - 21)		// Connect request is missing required phone number option
#define	kCommErrResourceNotAvailable		(kCommErrBase - 22)		// operation failed because some resource was not available...
#define kCommErrOptionNotSupported			(kCommErrBase - 23)		// call failed because passed option is not supported
#define kCommErrMethodNotImplemented		(kCommErrBase - 24)		// this method is not implemented

// SerialErrors�
// ERRBASE_SERIAL = (-18000)
#define kSerResult_EOM						(1000)
#define kSerResult_NoErr					(noErr)
#define kSerErr_Base						(ERRBASE_SERIAL)
#define kSerErr_ChannelInUse				(kSerErr_Base)
#define kSerErr_MemoryError					(kSerErr_Base - 1)
#define kSerErr_NotCurrentOwner				(kSerErr_Base - 2)
#define kSerErr_AsyncError					(kSerErr_Base - 3)		// framing (parity) overrun
#define kSerErr_CRCError					(kSerErr_Base - 4)		// crc error on input framing
#define kSerErr_InternalError				(kSerErr_Base - 5)		// internal error: e.g. illegal state in state machine.
#define kSerErr_PacketSizeError				(kSerErr_Base - 6)		// packet size too large or too small in output request
#define kSerErr_PacketLength				(kSerErr_Base - 7)		// packet unexpected length
#define kSerErr_PacketUnderRun				(kSerErr_Base - 8)		// eof not found...
#define kSerErr_PacketOverRun				(kSerErr_Base - 9)		// overrun bit set.
#define kSerErr_ExcessCollisions 			(kSerErr_Base - 10) 	// too many collisions when trying to send packet
#define kSerErr_ExcessDeferrals 			(kSerErr_Base - 11) 	// too many deferrals when trying to send packet
#define kSerErr_TimedOut 					(kSerErr_Base - 12) 	// timed out waiting for some event...
#define kSerErr_ToolNotReady 				(kSerErr_Base - 13) 	// serial tool has not been turned on.


// MNP errors
// ERRBASE_MNP = (-20000)
#define MNP_ERR_BASE						ERRBASE_MNP				// base for MNP driver errors

#define ERR_MNP_NEGOTIATION_FAILURE			(MNP_ERR_BASE-1)		// Connection parameter negotiation failure
#define ERR_MNP_CONNECT_TIME_OUT			(MNP_ERR_BASE-2)		// Connect request (acceptor mode) timed out
#define ERR_MNP_NOT_CONNECTED				(MNP_ERR_BASE-3)		// Not connected
#define ERR_MNP_ABORTED						(MNP_ERR_BASE-4)		// Request aborted by disconnect request
#define ERR_MNP_ATTENTION_DISABLED			(MNP_ERR_BASE-5)		// Link attention service is not enabled
#define ERR_MNP_CONNECT_RETRY_LIMIT			(MNP_ERR_BASE-6)		// Connect (initiator mode) request retry limit reached.
#define ERR_MNP_COMMAND_IN_PROGRESS			(MNP_ERR_BASE-7)		// Command already in progress.
#define ERR_MNP_ALREADY_CONNECTED			(MNP_ERR_BASE-8)		// Connection already established.
#define ERR_MNP_INCOMPATIBLE_PROT_LVL 		(MNP_ERR_BASE-9)		// Connection failed due to incompatible protocol levels
#define ERR_MNP_HANDSHAKE_FAILURE			(MNP_ERR_BASE-10)		// Connection handshake failed.
#define ERR_MNP_NOT_ALLOCATED				(MNP_ERR_BASE-11)		// Memory for MNP not allocated (option was passed which indicated not to allocate mnp memory)

#define MNP_ERR_END							ERR_MNP_NOT_ALLOCATED	// must be last error!



// FaxToolErrors
// ERRBASE_FAX = (-22000)
#define kFaxToolErrBase						(ERRBASE_FAX)
#define kFaxToolErrNoRemoteSignal			(kFaxToolErrBase - 1)
#define kFaxToolErrIncompatibleRemoteUnit	(kFaxToolErrBase - 2)
#define kFaxToolErrProtocolError			(kFaxToolErrBase - 3)
#define kFaxToolErrCmdRetransLimit			(kFaxToolErrBase - 4)
#define kFaxToolErrTransmissionFailed		(kFaxToolErrBase - 5)
#define kFaxToolErrFailureToTrain			(kFaxToolErrBase - 6)
#define kFaxToolErrNotSendingPage			(kFaxToolErrBase - 7)
#define kFaxToolErrT4DecodeUnderflow		(kFaxToolErrBase - 8)


// ModemErrors�
// ERRBASE_MODEM = (-24000)
#define kModemErrNoResponse					(ERRBASE_MODEM)			// modem not responding
#define kModemErrNoDialTone					(ERRBASE_MODEM - 1)		// No dial tone
#define kModemErrNoCarrier					(ERRBASE_MODEM - 2)		// No carrier.
#define kModemErrLineBusy					(ERRBASE_MODEM - 3)		// Line busy.
#define kModemErrNoAnswer					(ERRBASE_MODEM - 4)		// No answer.
#define kModemErrCommandFailure				(ERRBASE_MODEM - 5)		// modem command failed (invalid modem command/bad CRC) or command too long
#define kModemErrNoFaxCarrier				(ERRBASE_MODEM - 6)		// Fax carrier error
#define kModemErrNotSupported				(ERRBASE_MODEM - 7)		// Modem connected to the serial port does not support requested service
#define kModemErrCellularNotSupported		(ERRBASE_MODEM - 8)		// Modem connected to the serial port does not support cellular connection
#define kModemErrRcvPktFlagsTimeOut			(ERRBASE_MODEM - 9)		// AT+FRH command timed out receiving flags (as opposed to timing out waiting for flags).


// IR Errors�
// ERRBASE_SHARPIR = (-38000)
#define	kIRPending							(1)
#define	kIRErrTimeout						(ERRBASE_SHARPIR - 1)	// protocol time out
#define	kIRErrCancel						(ERRBASE_SHARPIR - 2)	// remote side cancelled operation
#define	kIRErrPacket						(ERRBASE_SHARPIR - 3)	// protocol error
#define	kIRErrCheckSum						(ERRBASE_SHARPIR - 4)	// data checksum failed
#define	kIRErrNAK							(ERRBASE_SHARPIR - 5)	// remote side receive failed
#define	kIRErrRetry							(ERRBASE_SHARPIR - 6)	// retries exceeded
#define	kIRErrSerial						(ERRBASE_SHARPIR - 7)	// SCC data errors on receive
#define	kIRErrGeneric						(ERRBASE_SHARPIR - 8)	// something else happened

// IrDA specific errors (many errors reported via errors above)
// ERRBASE_IRDA = (-38500)
#define	kIrDAErrDiscoveryFailed				(ERRBASE_IRDA - 1)		// Discovery failed
#define	kIrDAErrNoSuchClass					(ERRBASE_IRDA - 2)		// IAS lookup - class not found
#define	kIrDAErrNoSuchAttribute				(ERRBASE_IRDA - 3)		// IAS lookup - attribute not found
#define	kIrDAErrUserRequestedDisconnect		(ERRBASE_IRDA - 4)
#define	kIrDAErrLAPUnexpectedDisconnect		(ERRBASE_IRDA - 5)
#define	kIrDAErrLAPFailedConnection			(ERRBASE_IRDA - 6)
#define	kIrDAErrLAPReset					(ERRBASE_IRDA - 7)
#define	kIrDAErrLMMuxInitiatedDisconnect	(ERRBASE_IRDA - 8)
#define	kIrDAErrDataSentOnDiscLSAPConn		(ERRBASE_IRDA - 9)
#define	kIrDAErrNonResponsiveLMMuxClient	(ERRBASE_IRDA - 10)
#define	kIrDAErrNoAvailableLMMuxClient		(ERRBASE_IRDA - 11)
#define	kIrDAErrHalfOpen					(ERRBASE_IRDA - 12)
#define	kIrDAErrIllegalSourceAddress		(ERRBASE_IRDA - 13)
#define	kIrDAErrConnectionRace				(ERRBASE_IRDA - 14)
#define	kIrDAErrProtocolError				(ERRBASE_IRDA - 15)

// Blackbird Errors�
// ERRBASE_BLACKBIRD = (-46000)
#define	kBBvcInitErr						(ERRBASE_BLACKBIRD - 1)	// Blackbird initialization failed
#define	kBBTimerErr							(ERRBASE_BLACKBIRD - 2)	// Some Timer error occurred
#define	kBBConnectionDenied					(ERRBASE_BLACKBIRD - 3)	// a connection request was denied by the remote
#define	kBBNoFreeConnections				(ERRBASE_BLACKBIRD - 4)	// unable to connect because there are no free endpoints
#define kBBNoServiceSpecified				(ERRBASE_BLACKBIRD - 5)	// A connect request was received but no service name was given

// Wizard Import Errors�
// ERRBASE_WIZARD = (-50000)
#define	kWizErrGeneric						(ERRBASE_WIZARD - 1)	// usual serial error
#define	kWizErrBadApp						(ERRBASE_WIZARD - 2)	// unsupported application
#define	kWizErrTimeout						(ERRBASE_WIZARD - 3)	// time out
#define	kWizErrNoCard						(ERRBASE_WIZARD - 4)	// no card in Wizard
#define	kWizErrCancel						(ERRBASE_WIZARD - 5)	// import cancelled
#define	kWizErrNoTranslator					(ERRBASE_WIZARD - 6)	// no translator loaded

// TAPI Errors�
// ERRBASE_TAPI = (-23000)
#define	kTAPIErrGeneric						(ERRBASE_TAPI - 1)		// something bad happened

#endif
