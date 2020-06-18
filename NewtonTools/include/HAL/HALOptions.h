/*
	File:		HALOptions.h

	Contains:	Hardware-specific option definitions.

				Note: These are the same type of option definitions that the communications
				system uses. The options are used in c protocol interfaces that need to have
				flexible parameters passed: e.g., the init routine for a TSerialChip may
				need PCMCIA-related parameters (like a pointer to a TCardSocket) for
				serial chips on cards, or built-in hardware addresses for on-board
				serial chips. Using the option interface with its explicit typing of
				the option structures makes this more robust.

				These options are not typically public, and would not be used via comm
				scripting.

	Copyright:	� 1994-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v16 (9/9/96) internal.

*/



#ifndef	__HALOPTIONS_H
#define __HALOPTIONS_H


#ifndef	__SERIALOPTIONS_H
#include "SerialOptions.h"
#endif

#ifndef	__SERIALCHIPV2_H
#include "SerialChipV2.h"
#endif

#ifndef	__NAMESERVER_H
#include "NameServer.h"
#endif


	// Option labels
	// C++ uses longs
	#define kHMOSerialSCCHardware		'8530'
	#define kHMOSerialPCMCIAHardware	'16x5'
	#define kHMOSerialVoyagerHardware   'vshw'

	#define kHMOSerExtClockDivide		'cdiv'
	#define kHMOHiSpeedClockOption		'hclk'
	#define kHMOSerDebugConfig			'dbgc'
	#define kHMOGeoPortDebugConfig		'dbgg'
	#define kHMOSerIRLinkConfig			'irlk'
	#define kHMOSerTVIRLinkConfig		'tvlk'
	#define kHMOSerialChipLinkStats		'scls'

	// Hardware location id labels
	#define kHWLocExternalSerial		'extr'
	#define kHWLocBuiltInIR				'infr'
	#define kHWLocBuiltInModem			'mdem'
	#define kHWLocPCMCIASlot1			'slt1'
	#define kHWLocPCMCIASlot2			'slt2'
	#define kHWLocPCMCIAAnySlot			'slot'
	#define kHWLocBuiltInExtra			'tblt'



//--------------------------------------------------------------------------------
//	TUConfigServer
//
//		Interface to configuration routines for mapping comm service id's to
//		particular hardware locations.
//
//		Currently a subclass of TUNameServer, but could be incorporated directly
//		into that class (no penalty since no instance variables are needed).
//--------------------------------------------------------------------------------

class TUConfigServer : public TUNameServer
{
	public:
				TUConfigServer() {};
	NewtonErr 	GetDefaultConfig(ULong serviceID, char* configType, ULong* configIDPtr, ULong* flagsPtr = nil);
	NewtonErr 	SetDefaultConfig(ULong serviceID, char* configType, ULong configID, ULong flags = 0);

	NewtonErr 	GetDefaultHWLoc(ULong serviceID, ULong* hwLocIDPtr, ULong* flagsPtr = nil);
	NewtonErr 	SetDefaultHWLoc(ULong serviceID, ULong hwLocID, ULong flags = 0);

	NewtonErr 	RegisterULongName(ULong name, char* type, ULong thing, ULong spec);
	NewtonErr 	UnRegisterULongName(ULong name, char* type);
	NewtonErr 	LookupULongName(ULong name, char* type, ULong* thing, ULong* spec);

	void 		ULongStrToCStr(ULong name, char* nameStr);
};


//--------------------------------------------------------------------------------
//	THMOSerExtClockDivide
//		HAL-level option for finer control over serial chip clocking...
//		SCC specific. Specify this option, and then specify external clock in
//		a speed option...
//--------------------------------------------------------------------------------
#define kSerClk_Default			(0x00)
#define kSerClk_DivideBy_1		(0x80)
#define kSerClk_DivideBy_16		(0x81)
#define kSerClk_DivideBy_32		(0x82)
#define kSerClk_DivideBy_64		(0x83)
#define kSerClk_DivideBy_Mask	(0x03)

class THMOSerExtClockDivide : public TOption
{
	public:
						THMOSerExtClockDivide();

		UByte			fClockDivideOption;		// clock divide rate to set (0x00 to use default)
};

// --------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//	THMOHiSpeedClockOption
//		SCC-level option for setting hi-speed chip clock... used by async driver.
//--------------------------------------------------------------------------------

class THMOHiSpeedClockOption : public TOption
{
	public:
						THMOHiSpeedClockOption();

		Boolean			fUseHiSpeedClock;		// use hi-speed clock if true (default true)
};


//--------------------------------------------------------------------------------
//	THMOSerialChipLinkStats
//		TSerialChip throughput and buffer level stats. Get only. Debug only.
//--------------------------------------------------------------------------------

class THMOSerialChipLinkStats : public TOption
{
	public:

		ULong			fLinkPutByteTotal;
		ULong			fLinkGetByteTotal;
		ULong			fInBufferHighMark;
};


//--------------------------------------------------------------------------------
//	THMOGeoPortDebugConfig
//
//		Option to pass to ProcessOption. Sets up serial chip for debugger use.
//		This
//--------------------------------------------------------------------------------

class THMOGeoPortDebugConfig : public TOption
{
	public:
					THMOGeoPortDebugConfig();

	void*			fDebugObject;				// ptr to debugger object
	Boolean 		fTakeControl;				// true if debugger is taking control, false
};												//  if debugger is relinquishing control

//--------------------------------------------------------------------------------
//	THMOSerDebugConfig
//
//		Option to pass to ProcessOption. Sets up serial chip for debugger use.
//		This
//--------------------------------------------------------------------------------

class THMOSerDebugConfig : public TOption
{
	public:
					THMOSerDebugConfig();

	void*			fDebugObject;				// ptr to debugger object
	SCCChannelInts 	fDebugIntHandlers;			// ptr to debugger interrupt routines
	Boolean 		fInstallOverCurrent;		// true to install over current client
};

//--------------------------------------------------------------------------------
//	THMOSerIRLinkConfig
//
//		Option to pass to ProcessOption. Configures serial hardware for different
//		IR modes.
//--------------------------------------------------------------------------------
typedef UByte SerIRLinkMode;
#define kSerIRLink_Default			(0x00)
#define kSerIRLink_SharpIR			(0x00)
#define kSerIRLink_IRDA_1_6usec		(0x01)
#define kSerIRLink_IRDA_3_16		(0x02)
#define kSerIRLink_IRDA_Any			(0x03)
#define kSerIRLink_LastMode			(0x03)

typedef UByte SerIRLinkConfig;
#define kSerIRLinkCfg_Default		(0x00)
#define kSerIRLinkCfg_AutoRx		(0x01)
#define kSerIRLinkCfg_SetRxSense	(0x02)
#define kSerIRLinkCfg_RelaxedASK	(0x04)	/* allow 410KHz-735KHz signal (default is 461KHz-614KHz) */

typedef UByte SerIRLinkStatus;
#define kSerIRLinkSts_IRDADetect	(0x01)	/* Last mode autodetected: 1 == IRDA, 0 == ASK */

class THMOSerIRLinkConfig : public TOption
{
	public:
					THMOSerIRLinkConfig();

	SerIRLinkMode	fIRLinkMode;			// basic IR mode
	SerIRLinkConfig	fConfigFlags;			// auto-detect is only bit defined so far
	SerIRLinkStatus	fStatus;				// bit 0 is valid after data has been received, if configured for auto-detect
	UByte			fRxSensitivity;			// hmmm.... leave an out for this.
};

//--------------------------------------------------------------------------------
//	THMOSerTVIRLinkConfig
//
//		Option to pass to ProcessOption. Configures serial hardware for TV IR Modes.
//--------------------------------------------------------------------------------
typedef UByte SerTVIRLinkMode;
#define kSerTVIRMode_TVTransmit		(0x00)
#define kSerTVIRMode_TVRxOverSample	(0x01)
#define kSerTVIRMode_TVRxTimedBit	(0x02)
#define kSerTVIRMode_LastMode		(0x02)

typedef UByte SerTVIRLinkConfig;
#define kSerIRLinkCfg_Default		(0x00)
#define kSerIRLinkCfg_SetTimings	(0x01)

class THMOSerTVIRLinkConfig : public TOption
{
	public:
					THMOSerTVIRLinkConfig();

	SerTVIRLinkMode	fIRLinkMode;			// basic IR mode
	SerTVIRLinkConfig fConfigFlags;			//
	UByte			fTVTxTiming;			// bit rate to Hermes needs to be 80% greater than this
	UByte			fTVRxASKModulation;		// typically 38KHz (0x5f)
	UByte			fTVRxASKSensitivity;	// typically 0
	UByte			fTVRxTimingHiBits;		// sample rate timing should be less than
	UByte			fTVRxTimingLoByte;		//  80% of the main serial chip to Hermes bit rate
};


//--------------------------------------------------------------------------------
//	THMOSerialSCCHardware
//
//		Defines the hardware configuration for on-board 8530 Serial Communication
//		 Controller chips.  May be one-or two channel.
//--------------------------------------------------------------------------------

class TSCCChip;

// Config types
#define	kSCCConfigAsync				0		/* default config to async */
#define	kSCCConfigAsyncHalfDuplex	1		/* default to async, but half-duplex */
#define	kSCCConfigSyncSDLC			2		/* default to sdlc */

class THMOSerialSCCHardware : public TOption
{
	public:
				THMOSerialSCCHardware();

	TSCCChip*	fSCCChip;			// ptr to TSCCChip object (must be filled in)
	SCCSide		fSCCSide;			// sideA or sideB (defaults to side A)
	ULong 		fSCCConfigType;		// kSCCConfigAsync (default), kSCCConfigAsyncHalfDuplex, etc.
};


//--------------------------------------------------------------------------------
//	THMOSerialPCMCIAHardware
//
//		Defines the hardware configuration for pcmcia serial chips.
//--------------------------------------------------------------------------------

class TCardSocket;
class TCardHandler;

class THMOSerialPCMCIAHardware : public TOption
{
	public:
				THMOSerialPCMCIAHardware();

	TCardSocket* fCardSocket;		// ptr to TCardSocket object (must be filled in)
	TCardHandler* fCardHandler;		// ptr to TCardHandler object (must be filled in)
	UByte* 		fBaseRegAddr;		// ptr to base address of register array (must be filled in)
	ULong 		fHWLocationID;		// 1336176 kHWLocPCMCIASlot1, kHWLocPCMCIASlot2, etc. (valid if Length() >= 0x1c)
};

#endif	// __HALOPTIONS_H

