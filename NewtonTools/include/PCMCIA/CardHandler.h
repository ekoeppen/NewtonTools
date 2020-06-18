/*
	File:		CardHandler.h

	Contains:	Original CardHandler header for PCMCIA  cards.

	Copyright:	� 1992-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v6 internal (3/19/97).

*/



#ifndef __CARDHANDLER_H
#define __CARDHANDLER_H


#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef __PROTOCOLS__H
#include "Protocols.h"
#endif

#ifndef __CARDDEFINES_H
#include "CardDefines.h"
#endif


class TCardSocket;
class TCardPCMCIA;

//
//	class TCardHandler
//

PROTOCOL TCardHandler : public TProtocol
{
	public:
		static	TCardHandler*	New(char*);									// PROTOCOL constructor
		void					Delete();									// PROTOCOL destructor

		NewtonErr		RecognizeCard(TCardSocket* socket, TCardPCMCIA* card);			// Recognize card
		NewtonErr		ParseUnrecognizedCard(TCardSocket* socket, TCardPCMCIA* card);	// Recognized unparsed card (do your own parsing)

		NewtonErr		InstallServices(TCardSocket* socket, TCardPCMCIA* card, ULong configNumber=0);
		NewtonErr		RemoveServices(void);								// Install/Remove services

		NewtonErr		SuspendServices(void);								// Suspend/Resume services
		NewtonErr		ResumeServices(TCardSocket* socket, TCardPCMCIA* card, ULong configNumber=0);
		NewtonErr		EmergencyShutdown(void);							// EmergencyShutdown when card is away (from interrupt handler)

		NewtonErr		FormatCIS(TCardSocket* socket, TCardPCMCIA* card);	// Format CIS
		char*			CardIdString(TCardPCMCIA* card);					// Card identification string
		ULong			CardStatus(void);									// In CardDefines.h TCardStatus

		ULong			GetNumberOfDevice(void);
		void			GetDeviceInfo(ULong deviceNumber, ULong* cardType, TObjectId* cardPhys, void** cardDriverInfo, ULong* deviceOffset, ULong* deviceSize);

		void			SetCardServerPort(TObjectId port);					// Set card server port
		void			SetRemovableHandler(Boolean removable);				// Removable means the card handler
		Boolean			GetRemovableHandler(void);							//	will be removed when card removed

		long			CardSpecific(ULong selector, void* ptr=0, ULong something=0);	// selectors 0-0xffff are reserved by Apple
};



//	CardSpecific should return kError_Call_Not_Implemented if the selector is not
//  supported, to help with compatibility issues...

enum kCardSpecificSelectors										// From 0x00 to 0xff reserved for Apple
{
	kCardSpecificProcessOption				=	0,				// first param = TOption*, second param = TSerialChip* or TXXXDriver*, returns option processing results
	kCardSpecificPowerOn					=	1,				// first param = nil, second param = TSerialChip* or TXXXDriver*
	kCardSpecificPowerOff					=	2,				// first param = nil, second param = TSerialChip* or TXXXDriver*

	kCardSpecificATASetPartitionInfo		=	3,				// Set partition info
	kCardSpecificATAGetBootParamBlock		=	4,				// Get parameter block
	kCardSpecificATAGetStoreProtocolInfo	=	5,				// Get store protocol info

	kCardSpecificGetDeviceHWLocationId		=	9,				// first param = ULong* to "device hw location id 'slt?'", second param = device number		1384004

	kCardSpecificRegIREQintHandler			=	10,				// first param = InterruptHandler, second param = TSerialChip* or TXXXDriver*
	kCardSpecificDeRegIREQintHandler		=	11,				// first param = nil, second param = TSerialChip* or TXXXDriver*
	kCardSpecificSetIREQIntEnable			=	12				// first param = 1 for enable, 0 for disable, second param = TSerialChip* or TXXXDriver*
	// 128..255 reserved by lantern
};


#endif
