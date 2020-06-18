/*
	File:		CardPCMCIA.h

	Copyright:	� 1992-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v11 internal (9/14/96).

*/

#ifndef __CARDPCMCIA_H
#define __CARDPCMCIA_H


#ifndef __CONFIGPCMCIA_H
#include "ConfigPCMCIA.h"
#endif


#ifdef	hasPCMCIA

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef __CARDDEFINES_H
#include "CardDefines.h"
#endif

#ifndef __LIST_H
#include "List.h"
#endif

#ifndef __LISTITERATOR_H
#include "ListIterator.h"
#endif




////////////////////////////////
//
// Definitions
//

// Device type values

enum kTPDI_DTypes
{
	kTPDI_DType_Null					=	0,					// per PCMCIA 2.0 spec pg 5-13
	kTPDI_DType_ROM						=	1,
	kTPDI_DType_OTPROM					=	2,
	kTPDI_DType_EPROM					=	3,
	kTPDI_DType_EEPROM					=	4,
	kTPDI_DType_FLASH					=	5,
	kTPDI_DType_SRAM					=	6,
	kTPDI_DType_DRAM					=	7,
	kTPDI_DType_IO						=	0xD,
	kTPDI_DType_EXTEND					=	0XE
};


// Function id type values

enum kTPLFID_Functions
{
	kTPLFID_Function_MultiFunc				=	0,
	kTPLFID_Function_Memory					=	1,
	kTPLFID_Function_Serial					=	2,
	kTPLFID_Function_Parallel				=	3,
	kTPLFID_Function_FixedDisk				=	4,
	kTPLFID_Function_Video					=	5,
	kTPLFID_Function_LAN					=	6,
	kTPLFID_Function_AIMS					=	7
};



// bit definitions for power descriptors, also field definitions

enum PowerDescriptionFieldNames										// per PCMCIA 2.0 spec pg 5-24
{
	kVNominal = 0,
	kVMin,
	kVMax,
	kIStatic,
	kIAvg,
	kIPeak,
	kIPDwn,
	kPowerDescrValues												// total power description fields
};


// constants

const TMicroVolt k12p0Volts 				=	12000000;
const TMicroVolt k5p0Volts 					=	5000000;
const TMicroVolt k3p3Volts					=	3300000;
const TMicroVolt kXpXVolts					=	2200000;
const TMicroVolt kYpYVolts					=	1100000;

const UChar kPinReplacementRegisterOffset	=	0x04;				// per PCMCIA 2.0 spec pg 4-32
const UChar kStatusRegisterPresentBit		=	0x04;				// per PCMCIA 2.0 spec pg 4-32
const UChar kLevelInterrupt					=	0x20;				// per PCMCIA 2.0 spec pg 4-32

extern const char* kNewtOSString;									// NewtOS string
extern const char* kArmCPU610String;								// Arm 610 string

char* SetString(char* &desStr, const char* srcStr);
char* SetStringsBlock(char*& desBlock, const char* srcBlock, const ULong maxSize);

////////////////////////////////
//
// TClassLongLink objects are used to hold information about a subsequent CIS chain to be processed after the current
//   chain (and any chains indicated by previously-encountered longlink tuples) is (are) completed. See pages
//   5-7 and 5-8 for how this works.
//

class TCardLongLink : public SingleObject
{
	public:
						TCardLongLink();
						~TCardLongLink();

		void			Clear();

		UChar*			fLinkAddress;								// CISTPL_LONGLINK_A, CISTPL_LONGLINK_C - address of LinkTarget tuple in either attribute or common memory
		int 			fInAttributeMemory : 1;						// location of next chain - true if created from CISTPL_LONGLINK_A, false if from CISTPL_LONGLINK_C
		int  			fPrimaryList : 1;							// true only while processing the first chain
		int 	 		fLongLinkTupleSeen : 1;						// true if we have encounted a long-link tuple in processing this chain
		int 	 		fNoLongLinkTupleSeen : 1;					// true if we have encounted a no-link tuple in processing this chain
};

////////////////////////////////
//
// A Card Configuration (pg 5-17 thru 5-31) consists of
// a Configuration tuple CISTPL_CONF (5-18) and zero or more configuration entries (CISTPL__CE, ppg 5-21 thru 5-31).
// THERE MAY BE ONLY one configuration tuple in the entire CIS.
// We build a TCardConfiguration object in the TCardPCMCIA for each configuration entry.
//
// NOTE - WHAT THE CONFIGURATION SAYS ABOUT THE CARD'S BEHAVIOR IS ONLY TRUE IF THE CARD IS
//  PUT INTO THAT CONFIGURATION BY WRITING THE CONFIGURATION NUMBER TO THE CONFIGURATION REGISTER.
//

const UChar kNumMemoryBlocks				= 8;					// our limits on how many of these we will deal with
const UChar kNumIOBlocks					= 8;					// our limits on how many of these we will deal with

class TCardConfiguration : public SingleObject
{
	public:
						TCardConfiguration();
						~TCardConfiguration();

		void			Clear();

		TCardConfiguration& operator= (const TCardConfiguration& rhs);

		TMicroVolt		fVcc[kPowerDescrValues];					// TPCE_PD - array of common mem values for Vcc - Vnom, VMin, Vmax, Istatic, Iavg, Ipeak, Ipwrdown
		TMicroVolt		fVpp1[kPowerDescrValues];					// TPCE_PD - array of common mem values for Vpp1 - Vnom, VMin, Vmax, Istatic, Iavg, Ipeak, Ipwrdown
		TMicroVolt		fVpp2[kPowerDescrValues];					// TPCE_PD - array of common mem values for Vpp2 - Vnom, VMin, Vmax, Istatic, Iavg, Ipeak, Ipwrdown
		ULong			fVccAttr[kPowerDescrValues];				// TPCE_PD - array of attr mem values for Vcc - Vnom, VMin, Vmax, Istatic, Iavg, Ipeak, Ipwrdown
		ULong			fVpp1Attr[kPowerDescrValues];				// TPCE_PD - array of attr mem values for Vcc - Vnom, VMin, Vmax, Istatic, Iavg, Ipeak, Ipwrdown
		ULong			fVpp2Attr[kPowerDescrValues];				// TPCE_PD - array of attr mem values for Vcc - Vnom, VMin, Vmax, Istatic, Iavg, Ipeak, Ipwrdown
		ULong			fIoAddresses[kNumIOBlocks];					// TPCE_IO - base address to which card will respond (io)
		ULong			fIoLengths[kNumIOBlocks];					// TPCE_IO - length of addresses, corresponding to previous, to which the card will respond
		ULong			fMemAddresses[kNumMemoryBlocks];			// TPCE_MS - base address of card (memory)
		ULong			fMemLengths[kNumMemoryBlocks];				// TPCE_MS - length of addresses, corresponding to previous, to which the card will respond
		ULong			fHostAddresses[kNumMemoryBlocks];			// TPCE_MS - host mapping for above block, if required to be at fixed location
		TNanoSecond	 	fWaitTimeNSecs;								// TPCE_IF - wait time in in
		TNanoSecond		fRdyBsyTimeNSecs;							// TPCE_IF - max busy time on ready/busy line
		UChar			fFeatureSelection;							// TPCE_FS
		UChar			fNumOfIOSpace;								// TPCE_IO (derived) - number of IO spaces actually specified by the card in this configuration
		UChar			fIoAddrLines;								// TPCE_IO - number of IO address lines used by card to determine when it is selected
		UChar			fIo8BitOK;									// TPCE_IO - 8 bit IO is okay
		UChar			fIo16BitOK;									// TPCE_IO - if true, 16 bit IO is okay
		UChar			fConfigurationNumber;						// number of this configuration
		UChar			fInterfaceType;								// TPCE_IF - 0 - mem, 1 = io, 4-7 custom
		UChar			fActiveBits;								// TPCE_IF - bit field which stores part of TPCE_IF value - see following comments
																	// 	bit 0 = BVDs active
																	//	bit 1 = WP active,
																	//	bit 2 = RD/Bsy active
																	//	bit 3 = Mwait req'd / active (contradictory ???)
		UChar			fInterruptInfo;								// TPCE_IR - bit field which stores TPCE_IR value - see following comments
																	//	 bit fields for interrupt info
																	//	 if bit 4 = 0, bits 0-3 indicate which interrupt
																	//	 if bit 4 = 1, then:
																	//	 	bit 0 = can be NMI
																	//	 	bit 1 = can be IOCK
																	//	 	bit 2 = can be BERR
																	//	 	bit 3 = Vendor-specific
																	//	 bit 5 = can leave interrupt request pin low while servicing interrupt
																	//	 bit 6 = interrupt pin can be pulsed low to request interrupt
																	//	 bit 7 = card contains interrupt-sharing logic
		Boolean 		fInterruptShare;							// TPCE_IR - interrupts can be shared by multiple cards
		UChar			fNumOfMemMap;								// TPCE_IO (derived) - number of memory spaces actually specified by the card in this configuration
		UChar			fMiscBits;									// TPCE_MI - the exact contents of the byte, uninterpreted. Have at it, if you care.
};

enum kTPCE_IF_InterfaceTypes
{
	kTPCE_IF_InterfType_Memory		=	0,
	kTPCE_IF_InterfType_IO
};

enum kTPCE_IF_ActiveBits											// 1336187
{
	kTPCE_IF_BVDs_Active			=	0x01,
	kTPCE_IF_WP_Active				=	0x02,
	kTPCE_IF_READY_Active			=	0x04,
	kTPCE_IF_MWait_Required			=	0x08
};


////////////////////////////////
//
// Card Devices correspond to part of layer 1 of the metaformat specification (ppg 5-11 thru 5-16)
// Consituent Tuples:
//		CISTPL_DEVICE
//		CISTPL_DEVICE_A
//		CISTPL_DEVICE_OA
//		CISTPL_DEVICE_OC
//		CISTPL_JEDEC_A
//		CISTPL_JEDEC_C
//

class TCardDevice : public SingleObject
{
	public:
						TCardDevice();								// make a blank one
						TCardDevice(TNanoSecond nsecSpeed, ULong Size,
									TMicroVolt Vcc, Boolean Mwait,
									Boolean AttributeMemoryDescr,
									Boolean WPS,
									UChar DeviceType,
									ULong startOffset);
						~TCardDevice();

		ULong	 		fStartOffset;								// 	we calculate this one as we parse - offset to start of device in relevant mem space
		ULong			fSize;										// 	CISTPL_DEVICE, CISTPL_DEVICE_A, CISTPL_DEVICE_OA, CISTPL_DEVICE_OC - in bytes
		TNanoSecond	 	fnsecSpeed;									// 	CISTPL_DEVICE, CISTPL_DEVICE_A, CISTPL_DEVICE_OA, CISTPL_DEVICE_OC - access time of device in ns
		TMicroVolt	 	fVcc;										//  if OC or OA device, can be 3.3V, otherwise 5V
		int		 		fMwait : 1;									// 	if OC or OA device, can be true - indicates that mwait line will be used to indicate memory wait
		int 			fAttributeMemoryDescr : 1;					// 	true if the device describes attribute space
		int 			fWPS : 1;									//  true if the write protect switch controls this device
		UChar		 	fDeviceType;								//  see codes on page 5-13. 0 null, 1 ROM, 2 OTP, 3 EPROM, 4 EEPROM, 5 FLASH, 6 SRAM, 7 DRAM, oxD IO, oxE extended
		UChar			fJedecMfr;									//  jedec manufacturer code
		UChar			fJedecMfrInfo;								//  manufacturer-specific information
		UChar			fBusSize;									// CISTPL_DEVICE_GEO - bits on bus
		UChar			fEraseBlockSize;							// CISTPL_DEVICE_GEO - bits on bus
		UChar			fReadBlockSize;								// CISTPL_DEVICE_GEO - bits on bus
		UChar			fWriteBlockSize;							// CISTPL_DEVICE_GEO - bits on bus
		UChar			fPart;										// CISTPL_DEVICE_GEO - bits on bus
		UChar			fInterleave;								// CISTPL_DEVICE_GEO - bits on bus
};


////////////////////////////////
//
// Card packages is embedded in Apple vendor unique tuple (0x8E), MFR (C8) and CODE (0x2000)
//
//		CISTPL_VENDOR
//

class TCardPackage : public SingleObject
{
	public:

						TCardPackage();
						~TCardPackage();

		char*			SetName(char* srcStr);						// Set name
		const char*		GetName() const;							// Get name
		char*			SetCPUType(char* srcStr);					// Set CPU type
		const char*		GetCPUType() const;							// Get CPU type
		char*			SetOSType(char* srcStr);					// Set OS type
		const char*		GetOSType() const;							// Get OS type

		ULong			fAddress;									// Address
		ULong			fLength;									// Length
		ULong			fVersion;									// Version
		UChar			fType;										// Type
		UChar			fAttribute;									// Attribute
		UChar			fReserved0;									// Reserved 0
		UChar			fReserved1;									// Reserved 1

		char*			fName;										// nil or Name
		char*			fCPUType;									// nil or CPU type
		char*			fOSType;									// nil or OS type
};


////////////////////////////////
//
// Card function	Include function id, function extension, function config reg base addr, etc.
//
//		CISTPL_VENDOR
//
struct TCardFuncExt;

class TCardFunction : public SingleObject							// 1384004
{
	public:

						TCardFunction();
						~TCardFunction();

		ULong			GetNumOfFuncExts();							// Get the number of function extensions
		TCardFuncExt*	GetFuncExt(const ULong functExtNumber);		// Get a function extension data
		NewtonErr		AddFuncExt(const ULong dataSize, const UChar* data);	// Add a new copy of function extension data

		UChar			fFuncId;									// Function id
		UChar			fFuncIdSysInits;							// Function id system init
		UChar			fConfigEntryNumberStart;					// Possible configuration entries starting number
		UChar			fConfigEntryNumberEnd;						// Possible configuration entries ending number
		ULong			fRegisterBaseAddress;						// Configuration register base address

		CList			fFunctExts;									// Function extension list of TCardFuncExt
};

//	NOTE: The fConfigEntryNumberStart/End indicate the possible starting and ending config entry numbers.
//	Some MFC cards may the function id's and config entries in a very funnuy way. These numbers may be confused.

struct TCardFuncExt : public SingleObject							// 1384004
{
		UChar			fFuncExtDataSize;							// Function extension data size
		UChar			fFuncExtData[1];							// Function extension data
};



////////////////////////////////
//
// TCardPCMCIA objects are used to hold tuples which we get from CIS
//

const UChar kNumFuncExtTuples				= 2;					// our limits on how many of these we will deal with
const UChar kFuncExtSize					= 4;					// our limits on how many of these we will deal with

class TCardPCMCIA : public SingleObject
{
	public:
						TCardPCMCIA();
						~TCardPCMCIA();

		NewtonErr		Clear();									// 1336176 Clear current copy of cis

		char*			SetCardManufacturer(char* srcStr);
		const char*		GetCardManufacturer() const;
		char*			SetCardProduct(char* srcStr);
		const char*		GetCardProduct() const;
		char*			SetCardV1String3(char* srcStr);
		const char*		GetCardV1String3() const;
		char*			SetCardV1String4(char* srcStr);
		const char*		GetCardV1String4() const;
		char*			SetCardV2Vendor(char* srcStr);
		const char*		GetCardV2Vendor() const;
		char*			SetCardV2Info(char* srcStr);
		const char*		GetCardV2Info() const;

		TCardDevice*	GetCardDevice(const ULong deviceNumber);
		TCardDevice*	AddCardDevice(TCardDevice *device);
		TCardPackage*	GetCardPackage(const ULong packageNumber);
		TCardPackage*	AddCardPackage(TCardPackage *package);
		TCardConfiguration*  GetCardConfiguration(const ULong configNumber);
		TCardConfiguration*  AddCardConfiguration(TCardConfiguration *configuration);

		int				fNoAttrMem : 1;								// No attribute memory on the card
		int				fBadCIS : 1;								// Bad CIS on the card
		int				fAttrMemWrable : 1;							// Attribute memory is writable
		int				fTooManyUnknownTuples : 1;					// Too many unknown tuples on the card
		int				fFunctionIdAvail : 1;						// Too many unknown tuples on the card
		int				f16BitOnlyCard : 1;							// 16-bit only card						1113615 lww
		int				f8BitOnlyCard : 1;							// 8-bit only card						1113615 lww

		//	New for Voyager (kCardVersionVoyager)
		int				fNoCIS : 1;									// No CIS on card									//	New for Voyager (kCardVersionVoyager)
		int				fGlobalCIS : 1;								// this TCardPCMCIA is from a global CIS			//	New for Voyager (kCardVersionVoyager)
		int				fFuncSpecificCIS : 1;						// this TCardPCMCIA is from a function specific CIS	//	New for Voyager (kCardVersionVoyager)

		ULong			fSocketNumber;								// we fill in - it represents the current socket for this parse
		ULong		 	fTotalDeviceSize;							// Total common device size
		ULong			fFirstDataByteAddress;						// CISTPL_VERS_2 - < 64k, allows reserving part of common memory for CIS or other uses
		ULong			fRegisterBaseAddress;						// CISTPL_CONF - base address of registers in attribute space	(��� kCardVersionVoyager: use new TCardFunction)
		ULong		 	fRegistersPresent;							// CISTPL_CONF - bit array showing registers that should be there
		UShort			fManufactureId;								// CISTPL_MANFID
		UShort			fManufactureIdInfo;							// CISTPL_MANFID
		UChar			fFunctionId;								// CISTPL_FUNCID									(��� kCardVersionVoyager: use new TCardFunction)
		UChar			fFunctionSysInit;							// CISTPL_FUNCSYSINIT								(��� kCardVersionVoyager: use new TCardFunction)
		UChar			fFuncExt[kNumFuncExtTuples][kFuncExtSize];	// CISTPL_FUNCE 									(��� kCardVersionVoyager: use new TCardFunction)
		UChar			fNumOfFuncExt;								// number of function extension tuples in fFuncExt  (��� kCardVersionVoyager: use new TCardFunction)
		UChar			fNumOfDevice;								// number of devices
		UChar			fNumOfConfigEntry;							// number of configuration entries
		UChar			fNumOfPackage;								// number of packages
		UChar			fNumOfUnknownTuples;						// number of unknown tuples we saw during parse
		UChar			fConfigurationLastEntryNumber;				// CISTPL_CONF - number of configuration-entries that should be there
		UChar			fVendorSpecificV2Bytes[2];					// CISTPL_VERS2 - vendor-specific short

		char*			fManufacturerName;							// CISTPL_VERS_1 - nil or manufacture string
		char*			fProductName;								// CISTPL_VERS_1 - nil or product string
		char*			fV1String3;									// CISTPL_VERS_1 - nil or v1 string 3
		char*			fV1String4;									// CISTPL_VERS_1 - nil or v1 string 4
		char*			fV2Vendor;									// CISTPL_VERS_2 - nil or vendor that formatted card
		char*			fV2Info;									// CISTPL_VERS_2 - nil or info about card

		CList			fPackages;									// packages
		CList			fDevices;									// devices
		CList			fConfigurations;							// configurations (really configuration-entries)


		//	New for 2.0 (kCardVersion2p0 returned from Version())

		ULong			Version();


		//	New for Voyager (kCardVersionVoyager returned from Version())
		//
		//		1. Multiple-function CIS support
		//		2. Other condition devices support
		//		3. Multiple function ids and extension support

//		int				fNoCIS : 1;									// No CIS on card (defined above)
//		int				fGlobalCIS : 1;								// This TCardPCMCIA is from a global CIS (defined above)
//		int				fFuncSpecificCIS : 1;						// This TCardPCMCIA is from a function specific CIS (defined above)

		ULong			GetNumOfCISs();								// Get the number of CISs
		TCardPCMCIA*	GetCardCIS(const ULong cisNumber);			// Get a TCardPCMCIA*
		NewtonErr		AddFuncSpecificCIS();						// Add a new copy of function specific TCardPCMCIA to fCISs list

		ULong			GetNumOfCardOtherCondDeviceLists(const ULong forAttrMemory);						// Get the number of Device_OC or Device_OA list
		ULong			GetNumOfCardOtherCondDevice(const ULong forAttrMemory, const ULong listNumber);		// Get the number of device in a Device_OC or Device_OA list
		TCardDevice*	GetCardOtherCondDevice(const ULong forAttrMemory, const ULong listNumber, const ULong deviceNumber);	// Get a device from a Device_OC or Device_OA list
		Long			AddCardOtherCondDeviceList(const ULong forAttrMemory);								// Add a list to the Device_OC or Device_OA list and return the new list number (<0 error)
		NewtonErr		AddCardOtherCondDevice(const ULong forAttrMemory, const ULong listNumber, TCardDevice *device);			// Add device to a Device_OC or Device_OA list

		ULong			GetNumOfCardFunctions();					// 1384004 Get the number of card function
		TCardFunction*	GetCardFunction(const ULong funcNumber);	// 1384004 Get a card function
		TCardFunction*	AddCardFunction(TCardFunction* cardFunction);// 1384004 Add a new card function

		CList*			fCISs;										// CIS list: first one points to the global CIS 'this TCardPCMCIA itself' or a nil for not multiple-CIS.
		CList			fDeviceOCs;									// Device_OC list of lists
		CList			fDeviceOAs;									// Device_OA list of lists
		CList			fCardFunctions;								// 1384004 Card function list

		UChar			fCurrentCISNumber;							// Current CIS number
		UChar			fV1Major;									// 1323871 TPLLV1_MAJOR
		UChar			fV1Minor;									// 1323871 TPLLV1_MINOR

	private:

		NewtonErr		ClearFields();
		NewtonErr		RemoveFields();
};

#endif

#endif
