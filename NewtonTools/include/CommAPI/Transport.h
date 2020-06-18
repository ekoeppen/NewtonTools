/*
	File:		Transport.h

	Contains:	Transport interface for communications

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v6 internal of TransportExternal.h.

*/

#ifndef __TRANSPORT_H
#define __TRANSPORT_H

#ifndef __NEWTERRORS_H
	#include "NewtErrors.h"
#endif


//--------------------------------------------------------------------------------
//	This file is based on the X/Open Transport Interface
//	January, 1992
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//	The following errors can be reported directly to the user.
//	Not all errors are used.
//
//--------------------------------------------------------------------------------

#define TNOERR				(noErr)							// no error
#define TBADADDR			(ERRBASE_TRANSPORT - 1)			// incorrect address format
#define TBADOPT				(ERRBASE_TRANSPORT - 2)			// incorrect option format
#define TACCESS				(ERRBASE_TRANSPORT - 3)			// incorrect permissions
#define TBADF				(ERRBASE_TRANSPORT - 4)			// illegal transport fd
#define TNOADDR				(ERRBASE_TRANSPORT - 5)			// couldn't allocate addr
#define TOUTSTATE			(ERRBASE_TRANSPORT - 6)			// out of State
#define TBADSEQ				(ERRBASE_TRANSPORT - 7)			// bad call sequence number
#define TSYSERR				(ERRBASE_TRANSPORT - 8)			// system error
#define TLOOK				(ERRBASE_TRANSPORT - 9)			// event requires attention
#define TBADDATA			(ERRBASE_TRANSPORT - 10)		// illegal amount of data
#define TBUFOVFLW			(ERRBASE_TRANSPORT - 11)		// buffer not large enough
#define TFLOW				(ERRBASE_TRANSPORT - 12)		// flow control
#define TNODATA				(ERRBASE_TRANSPORT - 13)		// no data
#define TNODIS				(ERRBASE_TRANSPORT - 14)		// discon_ind not found on queue
#define TNOUDERR			(ERRBASE_TRANSPORT - 15)		// unitdata error not found
#define TBADFLAG			(ERRBASE_TRANSPORT - 16)		// bad flags
#define TNOREL				(ERRBASE_TRANSPORT - 17)		// no ord rel found on queue
#define TNOTSUPPORT			(ERRBASE_TRANSPORT - 18)		// primitive not supported
#define TSTATECHNG			(ERRBASE_TRANSPORT - 19)		// state is in process of changing
#define TNOSTRUCTYPE		(ERRBASE_TRANSPORT - 20)		// unsupported struct-type requested
#define TBADNAME			(ERRBASE_TRANSPORT - 21)		// invalid transport provider name
#define TBADQLEN			(ERRBASE_TRANSPORT - 22)		// qlen is zero
#define TADDRBUSY			(ERRBASE_TRANSPORT - 23)		// address in use
#define TINDOUT				(ERRBASE_TRANSPORT - 24)		// outstanding connection indications
#define TPROVMISMATCH		(ERRBASE_TRANSPORT - 25)		// transport provider mismatch
#define TRESQLEN			(ERRBASE_TRANSPORT - 26)		// resfd specified to accept w/qlen>0
#define TRESADDR			(ERRBASE_TRANSPORT - 27)		// resfd not bound to same addr as fd
#define TQFULL				(ERRBASE_TRANSPORT - 28)		// incoming connection queue full
#define TPROTO				(ERRBASE_TRANSPORT - 29)		// XTI protocol error
#define TALRDYSYNC			(ERRBASE_TRANSPORT - 30)		// Already in sync call


//--------------------------------------------------------------------------------
//	The following error codes are reserved for service-specific errors
//	Each service can redefine these errors to mean whatever they please
//--------------------------------------------------------------------------------

#define	TRESERVEDTOP		(ERRBASE_TRANSPORT - 501)		// top of the reserved range
#define	TRESERVEDBOTTOM		(ERRBASE_TRANSPORT - 999)		// bottom of the reserved range

//--------------------------------------------------------------------------------
//	The following are events codes sent to the Client event handler
//	For more information, see EndpointEvent.h
//--------------------------------------------------------------------------------

	// the following are events (i.e. arrive unsolicited)

#define	T_SPECEVT				(1)			// transport-specific event
#define	T_DISCONNECT			(2)			// remote disconnect received
#define	T_ORDREL				(3)			// remote orderly release indication
#define T_IDLEEVT				(4)			// idle timer expired
#define T_LISTENEVT				(5)			// listen timer expired
#define T_PROGRESSEVT			(6)			// progress event posted
#define T_TAPIEVT				(7)			// TAPI event



	// the following are completion notifications (i.e. arrive upon completion of async calls)

#define	T_RCVCOMPL				(-1)		// Snd complete event
#define	T_SNDCOMPL				(-2)		// Rcv complete event
#define	T_GETPROTADDRCOMPL		(-3)		// GetProtocolAddress complete
#define	T_OPTMGMTCOMPL			(-4)		// OptionManagement complete event
#define	T_LISTENCOMPL			(-5)		// Listen complete
#define	T_ACCEPTCOMPL			(-6)		// Accept complete
#define	T_CONNECTCOMPL			(-7)		// Connect complete
#define	T_RELEASECOMPL			(-8)		// Release complete event
#define	T_DISCONNECTCOMPL		(-9)		// Disconnect complete event
#define	T_BINDCOMPL				(-10)		// Bind complete event
#define	T_UNBINDCOMPL			(-11)		// UnBind complete event
#define	T_ABORTCOMPL			(-12)		// Abort complete event


//--------------------------------------------------------------------------------
//	The following are the flag definitions needed by the
//	user level library routines
//--------------------------------------------------------------------------------

	// TCMOEndpointInfo flags (see CommOptions.h)

#define	T_NOFLAG				(0x00000000)		// no flags
#define	T_CANSENDZERO			(0x00000001)		// supports 0-length TSDUs
#define	T_CANEOM				(0x00000002)		// preserves client end-of-message boundaries
#define	T_EXPCHANNEL			(0x00000004)		// supports expedited data
#define	T_RELIABLE				(0x00000008)		// link is reliable
#define	T_CANBIND				(0x00000010)		// supports Bind()
#define	T_CANLISTEN				(0x00000011)		// supports Listen() / Accept()
#define	T_CANCONNECT			(0x00000012)		// supports Connect()
#define	T_CANRELEASE			(0x00000014)		// supports Release()
#define	T_FRAMING				(0x00000018)		// transport supports packet framing
#define	T_FLOWCONTROL			(0x00000020)		// transport supports flow control

	// Snd and Rcv flags

#define	T_EOP					(0x00000000)		// set end-of-message (nop)
#define	T_MORE					(0x00000001)		// set no end-of-message
#define T_PACKET				(0x00000002)		// packetize the data (use framing)
#define	T_EXP					(0x00000004)		// expedited data

#define	T_FRAME					T_PACKET			// OBSOLETE - old-style constant

//--------------------------------------------------------------------------------
//	Service type defines.
//--------------------------------------------------------------------------------

#define	T_COTS					(1)				// connection-oriented transport service
#define	T_COTS_ORD				(2)				// connection-oriented with orderly release
#define	T_CLTS					(3)				// connectionless transport service


#define	T_TRANS					(5)				// connection-oriented transaction service
#define	T_TRANS_ORD				(6)				// connection-oriented transaction with orderly release
#define	T_TRANS_CLTS			(7)				// connectionless transaction service

//--------------------------------------------------------------------------------
//	The following are states as seen by the user
//--------------------------------------------------------------------------------

#define	T_UNINIT				(0)				// unitialized
#define	T_UNBND					(1)				// unbound
#define	T_IDLE					(2)				// idle
#define	T_OUTCON				(3)				// outgoing connection pending
#define	T_INCON					(4)				// incoming connection pending
#define	T_DATAXFER				(5)				// data transfer
#define	T_OUTREL				(6)				// outgoing release pending
#define	T_INREL					(7)				// incoming release pending
#define	T_INFLUX				(8)				// state is changing
#define	T_OUTLSTN				(9)				// listen pending

//--------------------------------------------------------------------------------
//	General purpose defines
//--------------------------------------------------------------------------------

#define	T_YES					(1)
#define	T_NO					(0)
#define	T_UNUSED				(-1)
#define	T_NULL					(0)
#define	T_ABSREQ				(0x00008000)

#define	T_INFINITE				(-1)			// used in TCMOEndpointInfo (see CommOptions.h)
#define	T_INVALID				(-2)			// used in TCMOEndpointInfo (see CommOptions.h)



#endif // __TRANSPORT_H
