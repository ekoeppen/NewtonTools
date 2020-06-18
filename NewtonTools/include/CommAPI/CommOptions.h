/*
	File:		CommOptions.h

	Contains:	Options defintions for CommManagerInterface

	Copyright:	� 1992-1994 by Apple Computer, Inc., all rights reserved.

	Derived from v3 internal of CommOptionsExternal.h.

*/

#ifndef	__COMMOPTIONS_H
#define __COMMOPTIONS_H



#ifndef FRAM

	#ifndef	__NEWTON_H
		#include "Newton.h"
	#endif

	#ifndef __OPTIONARRAY_H
		#include "OptionArray.h"
	#endif

	#define SETOPTIONLENGTH(oClass)		this->SetLength(sizeof(oClass) - sizeof(TOption));

#endif // notFRAM


/* --------------------------------------------------------------------------------------------------------------------

	Option definitions and selectors for Newton

	NOTE:  naming conventions

	kCMOxxxx	CommManager option, published in this file
	kCMSxxxx	CommManager service, published in CommServices.h
	kCMAxxxx	CommManager address, published in CommServices.h
	kCMCxxxx	CommManager configuration

	EXAMPLE:

	#define kCMOExampleOption		'exap'

	class TCMOExampleOption : public TOption
	{
		public:
					TCMOExampleOption();

			ULong	fSpeed;				// speed of interface
			Boolean	fFast;				// fast or slow
	};


	TCMOExampleOption::TCMOExampleOption() : TOption(kOptionType)
	{
		SetLabel(kCMOExampleOption);
		SETOPTIONLENGTH(TCMOExampleOption);
	}

   -------------------------------------------------------------------------------------------------------------------- */

#ifndef FRAM

	#define kCMOAppleTalkATP		'atp '
	#define kCMOAppleTalkNBP		'nbp '
	#define kCMOAppleTalkADSP		'adsp'
	#define kCMOAppleTalkPAP		'pap '

	#define kCMOEndpointName		'endp'
	#define kCMOTransportInfo		'tinf'

	#define	kCMOServiceIdentifier	'sid '

#endif // notFRAM


#ifndef FRAM

	//--------------------------------------------------------------------------------
	//	TCMOEndpointName
	//		NewByName string for the TEndpoint object
	//--------------------------------------------------------------------------------

	class TCMOEndpointName : public TOption
	{
		public:
							TCMOEndpointName();

			char			fClassName[64];
	};


	//--------------------------------------------------------------------------------
	//	TCMOTransportInfo
	//		info used by endpoint's and endpoint clients
	//--------------------------------------------------------------------------------

	class TCMOTransportInfo : public TOption
	{
		public:
					TCMOTransportInfo();

		ULong		serviceType;		// one of TransportServices (see Transport.h)
		ULong		flags;				// one of TransportFlags (see Transport.h)

		// the following are maximum sizes for various data buffers
		// could be T_INFINITE or T_INVALID
		// see XTI documentation for interpretation of values

		Long		tdsu;				// maximum data size transport can send/receive
		Long		etdsu;				// maximum expedited data size transport can send/receive
		Long		connect;			// max connect data
		Long		discon;				// max disconnect data
		Long		addr;				// max addr size
		Long		opt;				// max option size
	};

	//--------------------------------------------------------------------------------
	//	TCMOServiceIdentifier
	//		info used by endpoint's and endpoint clients
	//--------------------------------------------------------------------------------

	class TCMOServiceIdentifier : public TOption
	{
		public:
						TCMOServiceIdentifier();

			ULong		fServiceId;			// service type identifier
			TObjectId	fPortId;			// Id of service port (if non-zero, port is used instead of starting service)

	};

#endif // notFRAM


#endif  // __COMMOPTIONS_H

