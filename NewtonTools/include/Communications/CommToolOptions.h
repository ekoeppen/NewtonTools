/*
	File:		CommToolOptions.h

	Contains:	Options common to TCommTool's.

	Copyright:	� 1992-1994 by Apple Computer, Inc., all rights reserved.

	Derived from v6 internal.

*/

#ifndef __COMMTOOLOPTIONS_H
#define __COMMTOOLOPTIONS_H


#ifndef	__COMMSERVICES_H
#include "CommServices.h"
#endif

#ifndef	__OPTIONARRAY_H
#include "OptionArray.h"
#endif


#ifdef FRAM
	#define kCMOIdleTimer			"citr"
	#define kCMOListenTimer			"cltr"
	#define kCMOCTConnectInfo		"ctci"
	#define kCMOToolSpecificOptions	"ctso"
	#define kCMOPassiveClaim		"cpcm"
	#define kCMOPassiveState		"cpst"

#else
	#define kCMOIdleTimer			'citr'			/* CommTool Idle Timer */
	#define kCMOListenTimer			'cltr'			/* CommTool Listen Timer */
	#define kCMOCTConnectInfo		'ctci'			/* CommTool Connect Info */
	#define kCMOToolSpecificOptions	'ctso'			/* CommTool Specific Options */
	#define kCMOPassiveClaim		'cpcm'			/* CommTool Passive Claim option */
	#define kCMOPassiveState		'cpst'			/* CommTool Passive State option */
#endif


#ifndef FRAM
//--------------------------------------------------------------------------------
//	TCMOIdleTimer
//		If a connection is "idle" for specified amount of time, tear down connection
//--------------------------------------------------------------------------------

class TCMOIdleTimer : public TOption
{
	public:
					TCMOIdleTimer();

		ULong		fValue;			// timer value in seconds, default is 120
									// timer is disabled if value is 0
};


//--------------------------------------------------------------------------------
//	TCMOListenTimer
//		Amount of time to wait for a connection while "listening"
//--------------------------------------------------------------------------------

class TCMOListenTimer : public TOption
{
	public:
					TCMOListenTimer();

		ULong		fValue;			// timer value in seconds, default is 120
									// timer is disabled if value is 0
};


//--------------------------------------------------------------------------------
//	TCMOCTConnectInfo
//		Information describing the comm tool connection
//--------------------------------------------------------------------------------

class TCMOCTConnectInfo : public TOption
{
	public:
					TCMOCTConnectInfo();

		Boolean		fErrorFree;					// connection guarantees in order, reliable delivery of data
		Boolean		fSupportsCallBack;			// the connect supports call back
		Boolean		fViaAppleTalk;				// connection is using AppleTalk (e.g. net modem)

		ULong		fAppleTalkAddr;				// AppleTalk address of entity used for connection, only valid if fViaAppleTalk is true
		ULong		fConnectBitsPerSecond;		// Approximate throughput of the connection

};


//--------------------------------------------------------------------------------
//	TCMOToolSpecificOptions
//		CommTool specific options.  Allows application software to direct an
//		option request to a specific level of a endpoint which uses a
//		stack of CommTools.  All options following this option in the array
//		will only be processed by the specified service type
//--------------------------------------------------------------------------------

class TCMOToolSpecificOptions : public TOption
{
	public:
					TCMOToolSpecificOptions();

		ULong		fTargetServiceIdentifier;	// Service Identifier for which options are targeted
};


//--------------------------------------------------------------------------------
//	TCMOPassiveClaim
//		CommTool specific options.  Allows application software to direct an
//		option request to a specific level of a endpoint which uses a
//		stack of CommTools.  All options following this option in the array
//		will only be processed by the specified service type
//--------------------------------------------------------------------------------

class TCMOPassiveClaim : public TOption
{
	public:
					TCMOPassiveClaim();

		Boolean		fPassiveClaim;		// If set, indicates resources should be claimed in passive mode
};

//--------------------------------------------------------------------------------
//	TCMOPassiveState
//		CommTool specific options.  Allows application software to direct an
//		option request to a specific level of a endpoint which uses a
//		stack of CommTools.  All options following this option in the array
//		will only be processed by the specified service type
//--------------------------------------------------------------------------------

class TCMOPassiveState : public TOption
{
	public:
					TCMOPassiveState();

		Boolean		fPassiveState;		// If set, indicates resource useage state is passive (in passive state, they can be given up)
};

#endif // notFRAM

#endif // __COMMTOOLOPTIONS_H
