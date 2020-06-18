/*
	File:		CommAddresses.h

	Contains:	Address formats

	Copyright:	� 1992-1994 by Apple Computer, Inc., all rights reserved.

	Derived from v3 internal of CommAddressesExternal.h.

*/

/* --------------------------------------------------------------------------------------------------------------------
		Addresses

		a complete address is specified by a Title, Type, Discriminator, Kind,
		Route, and Alternate information.

		category		option selector		example				description
		--------		---------------		-------				-----------
		Title:			kCMATitleLabel		"Joe Smith"			as seen by user interface
		Type:			kCMATypeLabel		AppleLink			service type
		Discriminator:	kCMADiscLabel		X.25				specific type of connection
		Kind:			kCMAKindLabel
		Route:			kCMARouteLabel		"J.SMITH"			transport level address
		Alternate:		kCMAltLabel			---					an alternate address, which can
																be a complete address (allowing
																recursive addressing)

		*** currently only transport level ("Route") addresses are defined ***


   -------------------------------------------------------------------------------------------------------------------- */


#ifndef	__COMMADDRESSES_H
#define __COMMADDRESSES_H



#ifndef __OPTIONARRAY_H
	#include "OptionArray.h"
#endif




#ifndef FRAM

	// address types�
	#define kCMATitleLabel				'titl'
	#define kCMATypeLabel				'typa'
	#define kCMADiscLabel				'disc'
	#define kCMAKindLabel				'kind'
	#define kCMARouteLabel				'rout'
	#define kCMAltLabel					'alt '

#endif //notFRAM


// known kCMARouteLabel types�
#define kNamedAppleTalkAddress		1
#define kRawAppleTalkAddress		2
#define kPhoneNumber				3



// AppleTalk address types
#define	kNBPEntityName				1		/* i.e. "Sulu:Laserwriter@NewtVille" */
#define	kNameTypeZone				2		/* i.e. len "Sulu"; len "Laserwriter"; len "NewtVille" */



#ifndef FRAM

//--------------------------------------------------------------------------------
//		All C++ (non-FRAM stuff) goes below here
//--------------------------------------------------------------------------------



typedef FastInt RouteAddrType;

class TCMARouteAddress : public TOption
{
	public:

		RouteAddrType	fType;

	protected:
						TCMARouteAddress(RouteAddrType type);		// can't instantiate directly, use derived class
};


/* --------------------------------------------------------------------------------------------------------------------
		TCMAPhoneNumber

		kCMARouteLabel address option storing complete phone number
		as passed to modem
		e.g. "9,,1-212-555-1212"

   -------------------------------------------------------------------------------------------------------------------- */

class TCMAPhoneNumber : public TCMARouteAddress
{
	public:
						TCMAPhoneNumber(ULong phoneLen);

		ULong			fPhoneLen;
		// phone number follows

};


/* --------------------------------------------------------------------------------------------------------------------
		TCMAAppleTalkAddr

		kCMARouteLabel address option storing complete AppleTalk internet
		address tuple + specific link

   -------------------------------------------------------------------------------------------------------------------- */

// same as Network:Addresses.h�
typedef ULong	TLinkId;				// AppleTalk link identifier
typedef UShort	TNetworkNumber;			// AppleTalk network number
typedef UByte	TNode;					// AppleTalk node number
typedef UByte	TSocketNumber;			// AppleTalk socket number

class TCMAAppleTalkAddr : public TCMARouteAddress
{
	public:
						TCMAAppleTalkAddr();

		TLinkId			fLinkId;
		TNetworkNumber	fNetwork;
		TNode			fNode;
		TSocketNumber	fSocket;
};


/* --------------------------------------------------------------------------------------------------------------------
		TCMANamedAppleTalkAddr

		kCMARouteLabel address option storing complete AppleTalk named
		address of internet entity + specific link

   -------------------------------------------------------------------------------------------------------------------- */

typedef FastInt NamedAddrType;

class TCMANamedAppleTalkAddr : public TCMARouteAddress
{
	public:
						TCMANamedAppleTalkAddr(ULong addrLen, NamedAddrType nameType = kNBPEntityName);

		NamedAddrType	fNamedAddrType;		// kNBPEntityName or kNameTypeZone
		TLinkId			fLinkId;
		ULong			fDataLen;
		// AppleTalk NBP string follows
};


#endif // notFRAM


#endif // __COMMADDRESSES_H
