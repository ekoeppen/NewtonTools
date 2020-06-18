/*
	File:		ROMExtension.h

	Contains:	Structure for ROM extension blocks

	Copyright:	� 1994-1996 by Apple Computer, Inc.  All rights reserved.

	Derived from v16 internal.

*/

#ifndef __ROMEXTENSION_H
#define __ROMEXTENSION_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef __MEMORYLANES_H
#include "MemoryLanes.h"
#endif

#ifndef PROTOCOLGEN
//----------------------------------------------------------------------
//		Manifest Constants
//----------------------------------------------------------------------

const ULong kMaxROMExtensions = 4;		// we support four extension blocks
const Long kBaseROMId = -1;				// used by patch table code to tell base from REx

const ULong kRExHeaderVersion = 1;		// gotta start somewhere
const ULong kUndefined = 0xFFFFFFFF;	// no entry

const ULong kRExSignatureA = (ULong) 'RExB';
const ULong kRExSignatureB = (ULong) 'lock';

// config entry tags

const ULong kRAMConfigTag = (ULong) 'ram ';
const ULong kRAMAllocationTag = (ULong) 'ralc';
const ULong kDiagnosticsTag = (ULong) 'diag';
const ULong kCPatchTableTag = (ULong) 'jump';
const ULong kFrameExportTableTag = (ULong) 'fexp';
const ULong kFrameImportTableTag = (ULong) 'fimp';
const ULong kPackageListTag = (ULong) 'pkgl';
const ULong kPadBlockTag = (ULong) 'pad ';
const ULong kPatchTablePageTableTag = (ULong) 'ptpt';
const ULong kGelatoPageTableTag = (ULong) 'glpt';
const ULong kROMTimingConfigTag = (ULong) 'romt';
const ULong kFlashTimingConfigTag = (ULong) 'fsht';
const ULong kFlashTimingBankTag = (ULong) 'fshb';
const ULong kFlashDriverConfigTag = (ULong) 'fshd';
const ULong	kFlashDriverEntryTag	=	ULong ( 'fdrv' );
const ULong	kFlashAddressTag		=	ULong ( 'flsa' );

// magic well-known ROM extension physical locations
// one immediately after the base image (long-word aligned)
// one at phys 8 MB

# if !defined ( OMHACK )
# define	OMHACK	1
# endif
# ifdef OMHACK
extern const unsigned long ROM$$Size;
# endif
#define kRExPAddr0 ((PAddr)&ROM$$Size)

const PAddr kRExPAddr1 = (8 * MByte);

#endif /* PROTOCOLGEN */

//----------------------------------------------------------------------
//		RExHeader
//----------------------------------------------------------------------

struct ConfigEntry {
	ULong tag;
	ULong offset;
	ULong length;
};

struct RExHeader
{
	ULong signatureA;		// signature so we can scan for them
	ULong signatureB;
	ULong checksum;			// checksum of this block, or kUndefined
	ULong headerVersion;
	ULong manufacturer;		// for id'ing patches
	Fixed version;			// for id'ing patches
	ULong length;			// size of the rom extension block (including header)
	ULong id;				// extension ID (0..kMaxROMExtensions-1)
	VAddr start;			// virtual address of the top of this block
	ULong count;			// number of config entries
	ConfigEntry table[1];	// table of config entries, will be more than one
};


//----------------------------------------------------------------------
//		RAMAllocTable
//----------------------------------------------------------------------

// this table is used to partition RAM among various system resources
// "system" RAM is equal to total RAM minus user store RAM

enum RAMAllocSelector {
	kSystemRAMAlloc = -1,
	kRAMStoreAlloc,
	kFramesHeapAlloc,
	kRDMCacheAlloc
};

const ULong kRAMAllocTableVersion = 1;

struct RAMAllocEntry {
	ULong	min;		// in bytes, 0 means "no limit"
	ULong	max;		// in bytes, 0 means "no limit"
	ULong	pct;		// ratio of 1024, e.g. 256 = 25%, 512 = 50% etc.
};

struct RAMAllocTable {
	ULong version;				// version of this table format
	ULong count;				// count of entries in the table
	RAMAllocEntry table[3];		// actually could be more, but first three are required
};


//----------------------------------------------------------------------
//		RAMConfigTable
//----------------------------------------------------------------------

const ULong kRAMConfigTableVersion = 1;

struct RAMConfigEntry {
// From Includes:OS600:MemoryLanes.h
	ULong	ramPhysStart;			// physical start of Ram Bank
	ULong	ramSize;				// number of bytes of RAM in bank
	ULong	tag;					// tag of owner
	ULong	laneSize;				// size of a lane (e.g. 128K)
	ULong	laneCount;				// number of lanes (4 if entirely normal RAM)
};

struct RAMConfigTable {
	ULong version;				// version of this table format
	ULong count;				// count of entries in the table
	RAMConfigEntry	table[1];
};


//----------------------------------------------------------------------
//		ROMTimingConfigTable
//----------------------------------------------------------------------

const ULong kROMTimingConfigTableVersion = 1;

struct ROMTimingConfigTable {
	ULong version;
	Boolean enableBurst;
	UChar pageHitAccessTime;
	UChar addressSetupTime;
	UChar cycleTime;
};


//----------------------------------------------------------------------
//		FlashBankTimingConfigTable
//----------------------------------------------------------------------

const ULong kFlashBankTimingConfigTableVersion = 1;

struct FlashBankTimingConfigTable {
	ULong version;
	UChar tWR;
	UChar tAS;
	UChar tCS;
	UChar tAC;
	UChar tCYC;
};
//----------------------------------------------------------------------
//		FlashDriverConfigTable
//----------------------------------------------------------------------
# if defined(hasCirrus) || defined(hasVoyager)
class	TClassInfo;
struct SFlashDriverEntry
	{
	enum
		{
		kVersion			=	0x1
		};

	ULong					fVersion;				// version of this table format
	TClassInfo*				fDriverClassInfo;		// pointer to the class info for flash driver
	};
/*----------------------------------------------------------------------------*/
# else
const ULong kFlashDriverConfigTableVersion = 1;

struct FlashDriverConfigTable {
	ULong version;				// version of this table format

};
# endif // defined(hasCirrus) || defined(hasVoyager)


//----------------------------------------------------------------------
//		FlashBankConfigTable
//----------------------------------------------------------------------

const ULong kFlashBankConfigTableVersion = 1;

struct FlashBankConfigTable {
	ULong version;				// version of this table format
	ULong count;				// count of entries in the table
	PAddr table[1];				// starting physical address of flash chip
};


#endif
