/*
	File:		CardDefines.h

	Copyright:	� 1992-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v5 internal (10/23/96).

*/


#ifndef __CARDDEFINES_H
#define __CARDDEFINES_H


//
//	Card version definitions
//

#define kCardVersion2p0					0x00020000		// Version for 2.0
#define kCardVersionVoyager				0x00020200		// Version for Voyager


#ifndef __CONFIGPCMCIA_H
#include "ConfigPCMCIA.h"
#endif

#ifndef __OSERRORS__
#include "OSErrors.h"
#endif

#ifndef __NEWTON_H
#include "Newton.h"
#endif



//
//	types
//

typedef	ULong	TNanoAmp;								// nano amp
typedef	ULong	TMicroVolt;								// micro volt
typedef	ULong	TNanoSecond;							// nano second



//
//	constants
//

#define	kCapability_Voyager				'voyg'			// Protocol (card handlers, drivers) is Voyager compatible

#define	kCardNameNumberOfChars			32				// card names passed around have a fixed small number of chars

enum TCardStatus
{
	kBatteryStatus						=	0x0003,		// Battery status (11:ok, 01:low, X0:bad)
	kWriteProtected						=	0x0004, 	// Write protected
	kCardBusy							=	0x0008 		// Busy (incertion of Ready/busy)
};



//
//	card types
//

#define	kSRAMCard						'sram'			// SRAM card
#define	kROMCard						'rom '			// ROM card
#define	kFlashCard						'flsh'			// Flash card
#define	kPagedStoreCard					'pgts'			// ATA card
#define	kSerialCard						'comm'			// Serial I/O card
#define	kVideoCard						'vga1'			// video card



//
//	Card endian address conversion
//

inline ULong ToLittleEndianAddr(ULong addr)
{
	return (addr ^ 0x00000003);
}

inline void* ToLittleEndianAddr(void* addr)
{
	return (void*) ToLittleEndianAddr((ULong)addr);
}



//
//	Card access delay
//

void CardAttrMemReadDelay();							// Read attribute memory delay (for some io cards)
void CardAttrMemWriteDelay();							// Write attribute memory delay (for EEPROM memory)

UChar CardAttrMemReadByte(void* addr);
void CardAttrMemWriteByte(void* addr, UChar data);



//
//	Struct for configuration registers
//

struct TCardConfigRegs									// ***** Adjusted for big endian
{
	UChar	fOdd3;
	UChar	fConfigAndStatusReg;						// Configuration and status reg
	UChar	fOdd1;
	UChar	fConfigOptionReg;							// Configuration oprion reg
	UChar	fOdd7;
	UChar	fSocketAndCopyReg;							// Socket and copy reg
	UChar	fOdd5;
	UChar	fPinReplacementReg;							// Pin replacement reg
};

enum kCardConfigOptionRegMasks
{
	kCardConfigOptionSReset			=	0x80,			// Soft reset
	kCardConfigOptionLevlREQ		=	0x40,			// Level mode IREQ
	kCardConfigOptionConfIndex		=	0x3f			// Configuration index
};

enum kCardConfigAndStatusRegMasks
{
	kCardConfigStatusChanged		=	0x80,
	kCardConfigStatusSigChg			=	0x40,
	kCardConfigStatusIOis8			=	0x20,
	kCardConfigStatusRsvd0			=	0x10,
	kCardConfigStatusAudio			=	0x08,
	kCardConfigStatusPwrDwn			=	0x04,
	kCardConfigStatusIntr			=	0x02,
	kCardConfigStatusRsvd1			=	0x01
};

enum kCardPinReplacementRegMasks
{
	kCardPinReplaceCBVD1			=	0x80,
	kCardPinReplaceCBVD2			=	0x40,
	kCardPinReplaceCRdyBsy			=	0x20,
	kCardPinReplaceCWProt			=	0x10,
	kCardPinReplaceRBVD1			=	0x08,
	kCardPinReplaceRBVD2			=	0x04,
	kCardPinReplaceRRdyBsy			=	0x02,
	kCardPinReplaceRWProt			=	0x01
};

enum kCardfSocketAndCopyRegMasks
{
	kCardSocketAndCopyReserved		=	0x80,
	kCardSocketAndCopyCopyNumber	=	0x70,
	kCardSocketAndCopySocketNumber	=	0x0f
};



#endif
