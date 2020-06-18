/*
	File:		SerialChipRegistry.h

	Contains:	xxx put contents here xxx

	Copyright:	� 1994-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v3 (1/17/95) internal.

	Typical usage:

		A newly instantiated TSerialChip calls GetSerialChipRegistry()->Register(this, hwLoc)
		to get into the registry (the registry also calls the NameServer to add an entry with
		its SerialChipID and location).

		The serial tool calls GetSerialChipRegistry()->FindByLocation(hwLoc) to find a chip
		meeting its criteria. If found, it can call TSerialChip::InstallChipHandler()/RemoveChipHandler()
		to claim/release the serial chip. This can all be done atomically, to solve the problem
		of the serial chip disappearing after nameserver lookup. The chip should first be claimed
		via the NameServer to force a passive claim to be released...

*/

#ifndef	__SERIALCHIPREGISTRY_H
#define __SERIALCHIPREGISTRY_H

#ifndef	__SERIALCHIPV2_H
#include "SerialChipV2.h"
#endif

#define kRegistryFullError		(kError_RAMTable_Full)
#define kInvalidSerChipID		(kError_Bad_ObjectId)
#define kNilSerChipID			(0)
typedef ULong SerialChipID;

PROTOCOL PSerialChipRegistry : public TProtocol
{
	public:

	static PSerialChipRegistry* New(char*);
	NewtonErr		Init();
	void			Delete();

  // Methods called by TSerialChip instances... typically don't need to know their id's...

	NewtonErr		Register(TSerialChip* theChip, ULong hwLoc); // add chip to registry (atomic)
	NewtonErr		UnRegister(TSerialChip* theChip); 		// remove chip from registry
	NewtonErr		SetDefaultChip(ULong serviceType, ULong* hwLocation, Boolean onlyIfUnset); // set default hwLocation for a service, if unset?

  // Methods called by TSerialChip clients...

	TSerialChip*	GetChipPtr(SerialChipID);				// map id to chip pointer... may return nil!
	ULong			GetChipLocation(SerialChipID);			// map id to chip location ... may return nil!
	SerialChipID	FindByChip(TSerialChip* theChip);		// returns kNilSerChipID if not found
	SerialChipID	FindByOption(TCMOSerialChipSpec* opt);	// returns kNilSerChipID if not found
	SerialChipID	FindByLocation(ULong hwLocation);		// returns kNilSerChipID if not found
	NewtonErr		ClaimSerialChip(SerialChipID, Boolean passive, TObjectId ownerPortId);	// pass ownerPortId==nil to unclaim
	NewtonErr		GetDefaultChip(ULong serviceType, ULong* hwLocation); // get default hwLocation for a service, if registered
};

extern PSerialChipRegistry* gSerialChipRegistry;			// internal HAL use only...
extern PSerialChipRegistry* GetSerialChipRegistry();		// for external use, or lookup ("", "PTheSerialChipRegistry") in NameServer...

#endif // __SERIALCHIPREGISTRY_H
