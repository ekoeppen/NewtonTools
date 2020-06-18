/*
	File:		SerialOptions.h

	Contains:	Serial tool option definitions.

	Copyright:	� 1992-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v52 internal.

*/



#ifndef	__SERIALOPTIONS_H
#define __SERIALOPTIONS_H

#ifndef FRAM

#ifndef	__COMMSERVICES_H
#include "CommServices.h"
#endif

#ifndef	__OPTIONARRAY_H
#include "OptionArray.h"
#endif

#ifndef	__LongTime_H
#include "LongTime.h"			// for TTimeout
#endif

#endif // notFRAM

//--------------------------------------------------------------------------------
//		This stuff must be FRAM-able!
//--------------------------------------------------------------------------------

//	Standard ASCII Mnemonics

#define	chNUL						0x00
#define	chSOH						0x01	/* Control-A */
#define	chSTX						0x02	/* Control-B */
#define	chETX						0x03	/* Control-C */
#define	chEOT						0x04	/* Control-D */
#define	chENQ						0x05	/* Control-E */
#define	chACK						0x06	/* Control-F */
#define	chBEL						0x07	/* Control-G */
#define	chBS						0x08	/* Control-H */
#define	chHT						0x09	/* Control-I */
#define	chLF						0x0A	/* Control-J */
#define	chVT						0x0B	/* Control-K */
#define	chFF						0x0C	/* Control-L */
#define	chCR						0x0D	/* Control-M */
#define	chSO						0x0E	/* Control-N */
#define	chSI						0x0F	/* Control-O */
#define	chDLE						0x10	/* Control-P */
#define	chDC1						0x11	/* Control-Q */
#define	chDC2						0x12	/* Control-R */
#define	chDC3						0x13	/* Control-S */
#define	chDC4						0x14	/* Control-T */
#define	chNAK						0x15	/* Control-U */
#define	chSYN						0x16	/* Control-V */
#define	chETB						0x17	/* Control-W */
#define	chCAN						0x18	/* Control-X */
#define	chEM						0x19	/* Control-Y */
#define	chSUB						0x1A	/* Control-Z */
#define	chESC						0x1B	/* Control-[ */
#define	chFS						0x1C
#define	chGS						0x1D
#define	chRS						0x1E
#define	chUS						0x1F


#ifdef FRAM
#define	unicodeNUL					$\u0000
#define	unicodeSOH					$\u0001
#define	unicodeSTX					$\u0002
#define	unicodeETX					$\u0003
#define	unicodeEOT					$\u0004
#define	unicodeENQ					$\u0005
#define	unicodeACK					$\u0006
#define	unicodeBEL					$\u0007
#define	unicodeBS					$\u0008
#define	unicodeHT					$\u0009
#define	unicodeLF					$\u000A
#define	unicodeVT					$\u000B
#define	unicodeFF					$\u000C
#define	unicodeCR					$\u000D
#define	unicodeSO					$\u000E
#define	unicodeSI					$\u000F
#define	unicodeDLE					$\u0010
#define	unicodeDC1					$\u0011
#define	unicodeDC2					$\u0012
#define	unicodeDC3					$\u0013
#define	unicodeDC4					$\u0014
#define	unicodeNAK					$\u0015
#define	unicodeSYN					$\u0016
#define	unicodeETB					$\u0017
#define	unicodeCAN					$\u0018
#define	unicodeEM					$\u0019
#define	unicodeSUB					$\u001A
#define	unicodeESC					$\u001B
#define	unicodeFS					$\u001C
#define	unicodeGS					$\u001D
#define	unicodeRS					$\u001E
#define	unicodeUS					$\u001F
#endif


// default flow control
#define	kDefaultXOnChar				chDC1	/* 0x11 */
#define	kDefaultXOffChar			chDC3	/* 0x13 */

// default framing
#define	kDefaultFramingChar			chDLE	/* 0x10 */
#define	kDefaultEOMChar				chETX	/* 0x03 */
#define	kDefaultSOMChar				chSYN	/* 0x16 */
#define	kDefaultSOHChar				chSTX	/* 0x02 */

// SCCSide
#define	kNoChannel					0
#define	kSCCSideA					1
#define	kSCCSideB					2

// SCCService
#define	kSCCServiceNotSpecified		0		/* defaults to SCC1/sideA */
#define	kSCCServiceStandard			1		/* standard serial: defaults to SCC1/sideA */
#define	kSCCServicePtToPtIR			2		/* Point-to-point IR: defaults to SCC1/sideB */
#define	kSCCServiceModem			3		/* modem connection: defaults to MODEM1 if available, SCC1/sideA otherwise */
#define	kSCCServicePrinter			4		/* printer connection: defaults to SCC1/sideA */

// Stop bits
#define k1StopBits					0
#define k1pt5StopBits				1
#define k2StopBits					2

// Parity
#define kNoParity					0
#define kOddParity					1
#define kEvenParity					2

// Data bits
#define k5DataBits					5
#define k6DataBits					6
#define k7DataBits					7
#define k8DataBits					8

// Interface speed (bps)
#define kExternalClock				1
#define	k300bps						300
#define	k600bps						600
#define	k1200bps					1200
#define	k2400bps					2400
#define	k4800bps					4800
#define	k7200bps					7200
#define	k9600bps					9600
#define	k12000bps					12000
#define	k14400bps					14400
#define	k19200bps					19200
#define	k38400bps					38400
#define	k57600bps					57600
#define	k115200bps					115200
#define	k230400bps					230400

// Serial event codes
#define kSerialEventBreakStartedMask		(0x00000001)
#define kSerialEventBreakEndedMask			(0x00000002)
#define kSerialEventDCDNegatedMask			(0x00000004)
#define kSerialEventDCDAssertedMask			(0x00000008)

#define kSerialEventCTSNegatedMask			(0x00000010)
#define kSerialEventCTSAssertedMask			(0x00000020)
#define kSerialEventExtClkDetectEnableMask	(0x00000040)

#define kSerialEventDSRNegatedMask			(0x00000100)
#define kSerialEventDSRAssertedMask			(0x00000200)
#define kSerialEventRINegatedMask			(0x00000400)
#define kSerialEventRIAssertedMask			(0x00000800)

#define kSerialEventAllMask					(0x00000f7f)


// IR option bit definitions

// the high two bits must never be used, otherwise Frames RINTs won't work
#define irDontUseTheseBits			(0xC0000000)

// IR data/protocol type
#define	irUsingNegotiateIR			(0x00)
#define	irUsingSharpIR				(0x01)
#define	irUsingNewtIR				(0x02)
#define	irUsingSeniorIR				(0x04)
#define irUsingIrDA					(0x08)
	// all other bits are reserved, and must be zero

#define	irJ1ProtocolType			(irUsingSharpIR | irUsingNewtIR)
#define	irProtocolType				(irUsingSharpIR | irUsingNewtIR | irUsingSeniorIR)

// IR protocol options
#define	irUsing9600					(0x01)
#define	irUsing19200				(0x02)
#define	irUsing38400				(0x04)
	// all other bits are reserved, and must be zero

#define	irProtocolOptionsBrick1			(irUsing9600)

// 1.3 is capable of all three speeds
#define	irJ1ProtocolOptions			(irUsing9600 | irUsing19200 | irUsing38400)
#define	irProtocolOptions			(irUsing9600 | irUsing19200 | irUsing38400)

// IR Connect options
// high two bits are reserved, so we stay compatible with Frames RINT's
#define	irSymmetricConnect			(0x01)		// set by client for symmetric connect
#define	irActiveConnection			(0x02)		// set by tool to indicate active or passive connection
#define	irIrDACapableConnect		(0x04)		// set by client to include irUsingIrDA in negotiation
#define irNegotiatedConnection		(0x08)		// set by client to indicate already negotiated (typically by IrProbe)
	// all other bits are reserved, and must be zero


//	TCMOSerialMiscConfig
#define kSerDefaultSendForIntDelay		(20 * kMilliseconds)	/* delay for SendForInterrupt on input available */

#ifdef FRAM

	// Option labels
	// FRAM uses strings
	#define kCMOSerialHWChipLoc			"schp"
	#define kCMOSerialHardware			"scc "
	#define kCMOSerialBuffers			"sbuf"
	#define kCMOSerialIOParms			"siop"
	#define kCMOSerialBitRate			"sbps"
	#define kCMOSerialBreak				"sbrk"
	#define kCMOSerialBytesAvailable	"sbav"
	#define kCMOSerialDiscard			"sdsc"
	#define kCMOBreakFraming			"sbkf"
	#define kCMOKeyboardConfig			"kbcf"
	#define kCMOSerialDTRControl		"sdtr"
	#define kCMOPCMCIAModemSound		"msnd"
	#define kCMOSerialMiscConfig		"smsc"
	#define kCMOSerialEventEnables		"sevt"
	#define kCMOSerialIOStats			"sios"
	#define kCMOOutputFlowControlParms	"oflc"
	#define kCMOInputFlowControlParms	"iflc"
	#define kCMOFramingParms			"fram"
	#define kCMOFramedAsyncStats		"frst"
	#define kCMOLocalTalkStats			"ltst"
	#define kCMOLocalTalkNodeID			"ltid"
	#define kCMOLocalTalkMiscConfig		"ltms"
	#define kCMOSlowIRProtocolType		"irpt"
	#define kCMOSlowIRStats				"irst"
	#define kCMOSlowIRSniff				"irsn"
	#define kCMOSlowIRBitBang			"irtv"
	#define kCMOSlowIRConnect			"irco"
	#define kCMOIrDADiscovery			"irdi"
	#define kCMOIrDAReceiveBuffers		"irrb"
	#define kCMOIrDALinkDisconnect		"irld"
	#define kCMOIrDAConnectionInfo		"irci"
	#define kCMOIrDAConnectUserData		"ircd"
	#define kCMOIrDAConnectAttrName		"irca"
	#define kCMOProbeIRDiscovery		"irpk"
	#define kCMOSerialCircuitControl	"sctl"
	#define kCMOSerialChipSpec			"sers"
	#define kCMOSerialHalfDuplex		"1way"


#else

	// Option labels
	// C++ uses longs
	#define kCMOSerialHWChipLoc			'schp'
	#define kCMOSerialHardware			'scc '
	#define kCMOSerialBuffers			'sbuf'
	#define kCMOSerialIOParms			'siop'
	#define kCMOSerialBitRate			'sbps'
	#define kCMOSerialBreak				'sbrk'
	#define kCMOSerialBytesAvailable	'sbav'
	#define kCMOSerialDiscard			'sdsc'
	#define kCMOBreakFraming			'sbkf'
	#define kCMOKeyboardConfig			'kbcf'
	#define kCMOSerialDTRControl		'sdtr'
	#define kCMOPCMCIAModemSound		'msnd'
	#define kCMOSerialMiscConfig		'smsc'
	#define kCMOSerialEventEnables		'sevt'
	#define kCMOSerialIOStats			'sios'
	#define kCMOOutputFlowControlParms	'oflc'
	#define kCMOInputFlowControlParms	'iflc'
	#define kCMOFramingParms			'fram'
	#define kCMOFramedAsyncStats		'frst'
	#define kCMOLocalTalkStats			'ltst'
	#define kCMOLocalTalkNodeID			'ltid'
	#define kCMOLocalTalkMiscConfig		'ltms'
	#define kCMOSlowIRProtocolType		'irpt'
	#define kCMOSlowIRStats				'irst'
	#define kCMOSlowIRSniff				'irsn'
	#define kCMOSlowIRBitBang			'irtv'
	#define kCMOSlowIRConnect			'irco'
	#define kCMOIrDADiscovery			'irdi'
	#define kCMOIrDAReceiveBuffers		'irrb'
	#define kCMOIrDALinkDisconnect		'irld'
	#define kCMOIrDAConnectionInfo		'irci'
	#define kCMOIrDAConnectUserData		'ircd'
	#define kCMOIrDAConnectAttrName		'irca'
	#define kCMOProbeIRDiscovery		'irpk'
	#define kCMOSerialCircuitControl	'sctl'
	#define kCMOSerialChipSpec			'sers'
	#define kCMOSerialHalfDuplex		'1way'

#endif


#ifndef FRAM
//--------------------------------------------------------------------------------
//		All C++ (non-FRAM) stuff goes below here
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//	TCMOSerialHWChipLoc
//		Specifies the TSerialChip to use by location id (see :includes:hal:haloptions
//		for a list of these).
//
//		NOTE: This is a 2.0 option, which should typically be used instead of
//		 	TCMOSerialHardware. The user should be given an interface to allow
//			them to change the value of this option.  If this option is not
//			specified, the default TSerialChip for the service using the TSerialChip
//			will be used. The external serial port will be tbe typical default.
//			If fHWLoc is nil, fServiceID will be used to lookup a default chip
//			location rather than using the service ID of the current tool.
//--------------------------------------------------------------------------------

class TCMOSerialHWChipLoc : public TOption
{
	public:
				TCMOSerialHWChipLoc();

	ULong		fHWLoc;			// defaults to kHWLocExternalSerial
	ULong		fService;		// defaults to nil
};


//--------------------------------------------------------------------------------
//	TCMOSerialChipSpec
//		Option to return/specify generic information about tbe current serial chip.
//		This can be used to select chip to bind to (superset of TCMOSerialHWChipLoc).
//--------------------------------------------------------------------------------

/* Parity, Stop/Data Bit support: same as PCMCIA Serial Port Interface Extension Tuple UART capabilities field */
#define kSerCap_Parity_Space	(0x00000001)
#define kSerCap_Parity_Mark		(0x00000002)
#define kSerCap_Parity_Odd		(0x00000004)
#define kSerCap_Parity_Even		(0x00000008)

#define kSerCap_DataBits_5		(0x00000001)
#define kSerCap_DataBits_6		(0x00000002)
#define kSerCap_DataBits_7		(0x00000004)
#define kSerCap_DataBits_8		(0x00000008)
#define kSerCap_StopBits_1		(0x00000010)
#define kSerCap_StopBits_1_5	(0x00000020)
#define kSerCap_StopBits_2		(0x00000040)
#define kSerCap_StopBits_All	(0x00000070)
#define kSerCap_DataBits_All	(0x0000000f)

// serial chip types (0-2 follow PCMCIA standard)
#define	kSerialChipUnknown			0xff	/* unknown type of uart */
#define	kSerialChip8250				0x00	/* 8250 uart */
#define	kSerialChip16450			0x01	/* 16450 uart */
#define	kSerialChip16550			0x02	/* 16550 uart */
#define	kSerialChip8530				0x20	/* SCC */
#define	kSerialChip6850				0x21	/* Brick Modem port uart */
#define	kSerialChip6402				0x22	/* Brick IR port uart */
#define	kSerialChipVoyager			0x23	/* Cirrus uart */

class TCMOSerialChipSpec : public TOption
{
	public:
						TCMOSerialChipSpec();

		ULong			fHWLoc;				// chip location (i.e., kHWLocExternalSerial) (must match if not nil)
		ULong 			fSerFeatures;		// features supported by this chip (set feature bits must be supported)

		UByte			fSerOutSupported;	// output signals supported by current chip (SerOutCircuits) (set bits must be supported)
		UByte			fSerInSupported;	// input signals supported by current chip (SerInCircuits) (set bits must be supported)
		UByte			fParitySupport;		// (set bits must be supported)
		UByte			fDataStopBitSupport; // (set bits must be supported)

		UByte			fUARTType;			// (not used to match)
		Boolean			fChipNotInUse;		// (must match if set)
		UByte			fReserved2;
		UByte			fReserved3;

		// following are pcmcia only...
		UShort			fCIS_ManFID;		// CIS manufacturer ID, PCMCIA serial only (must match if not nil)
		UShort			fCIS_ManFIDInfo;	// CIS manufacturer ID info, PCMCIA serial only (must match if not nil)
};


//--------------------------------------------------------------------------------
//	TCMOSerialCircuitControl
//		Option for finer control of RS-232 defined control lines...
//--------------------------------------------------------------------------------

typedef UByte SerOutCircuits;
#define kSerOutDTR			(0x01)
#define kSerOutRTS			(0x02)		/* Macintosh HSKo */

typedef UByte SerInCircuits;
#define kSerInDSR			(0x02)
#define kSerInDCD			(0x08)		/* Macintosh GPi */
#define kSerInRI			(0x10)		/* Macintosh GPi */
#define kSerInCTS			(0x20)		/* Macintosh HSKi */
#define kSerInBreak			(0x80)

class TCMOSerialCircuitControl : public TOption
{
	public:
						TCMOSerialCircuitControl();

		SerOutCircuits	fSerOutToSet;		// output circuits to assert. defaults to 0.
		SerOutCircuits	fSerOutToClear;		// output circuits to negate. defaults to 0.
		SerOutCircuits	fSerOutState;		// current output circuit state (after set/clear).
		SerInCircuits	fSerInState;		// current input circuit state
};


//--------------------------------------------------------------------------------
//	TCMOSerialHardware
//		Defines the hardware configuration for all SCC-related serial services.
//		This defaults to using the din-8 serial port.
//--------------------------------------------------------------------------------

typedef char * SCCChip;
extern const SCCChip SCC1;
extern const SCCChip SCC2;
extern const SCCChip MODEM1;
extern const SCCChip PCMCIA1;

typedef FastInt SCCService;

enum SCCSide {
	noChannel = kNoChannel,				// use default for the specified type of service
	sideA = kSCCSideA,					// J1 din-8 serial port (default)
	sideB = kSCCSideB					// J1 slow IR serial port
};

// If you specify SCCService, the system can make some intelligent guess about
// which physical connection is desired. Either the SCCService should be specified,
// or the SCCSide/SCCChip, or neither.


class TCMOSerialHardware : public TOption
{
	public:
				TCMOSerialHardware();

	SCCSide		fSCCSide;		// sideA or sideB
	SCCChip		fSCCChip;		// SCC1, SCC2, PCMCIA1, PCMCIA2, etc.
	FastInt 	fSCCService;	// kSCCServiceStandard, kSCCServicePtToPtIR, etc.
	// default is SCC1/sideA, kSCCServiceStandard
};


//--------------------------------------------------------------------------------
//	TCMOSerialBuffers
//		Defines the buffer sizes for the (async) serial tool.
//--------------------------------------------------------------------------------


class TCMOSerialBuffers : public TOption
{
	public:
				TCMOSerialBuffers();

	ULong		fSendSize;		// size of send buffer; defaults to 256 bytes
	ULong		fRecvSize;		// size of recv buffer; defaults to 256 bytes
	ULong		fRecvMarkers;	// number of error markers/messages for recv buffer; defaults to 8
};


//--------------------------------------------------------------------------------
//	TCMOSerialIOParms
//		bps rate, stop bits, data bits, parity
//--------------------------------------------------------------------------------

typedef ULong BitRate;
typedef ULong InterfaceSpeed;
typedef FastInt StopBits;
typedef FastInt ParityType;
typedef FastInt DataBits;

class TCMOSerialIOParms : public TOption
{
	public:
						TCMOSerialIOParms();

		FastInt			fStopBits;		// default 1 stop bit
		FastInt			fParity;		// default no parity
		FastInt			fDataBits;		// default 8 data bits
		BitRate			fSpeed;			// default 9600 bps
};


//--------------------------------------------------------------------------------
//	TCMOSerialBitRate
//		bit rate, used for changing speed after the tool is open
//--------------------------------------------------------------------------------

class TCMOSerialBitRate : public TOption
{
	public:
						TCMOSerialBitRate();

		BitRate			fBitsPerSecond;	// default 9600 bps
};


//--------------------------------------------------------------------------------
//	TCMOSerialBreak
//		break send option. no synchronization is currently done with output.
//--------------------------------------------------------------------------------

class TCMOSerialBreak : public TOption
{
	public:
						TCMOSerialBreak();

		TTimeout		fBreakTime;			// default 75 milliseconds
};


//--------------------------------------------------------------------------------
//	TCMOSerialBytesAvailable
//		number of bytes waiting to be read
//--------------------------------------------------------------------------------

class TCMOSerialBytesAvailable : public TOption
{
	public:
						TCMOSerialBytesAvailable();

		ULong			fBytesAvailable;
};


//--------------------------------------------------------------------------------
//	TCMOSerialDiscard
//		discard bytes in input/output buffers
//--------------------------------------------------------------------------------

class TCMOSerialDiscard : public TOption
{
	public:
						TCMOSerialDiscard();

		Boolean			discardInput;		// defaults to TRUE
		Boolean			discardOutput;		// defaults to FALSE
};


//--------------------------------------------------------------------------------
//	TCMOBreakFraming
//		break framing option for async serial driver; special support for LaserWriter LS
//--------------------------------------------------------------------------------

class TCMOBreakFraming : public TOption
{
	public:
						TCMOBreakFraming();

		TTimeout		fBreakOnTime;		// break time before send: default 0 usec
		TTimeout		fBreakOffTime;		// marking time before send: default 0 usec
		Boolean			fUseHighSpeedClock; // defaults to FALSE.
		ULong			fRepeatCount;		// defaults to zero. Set to non-zero to repeat a send
											//  multiple times (only small data amounts).
};

//--------------------------------------------------------------------------------
//	TCMOSerialDTRControl
//		Set the state of DTR. Will return opFailure if you are using hardware input flow control.
//--------------------------------------------------------------------------------

class TCMOSerialDTRControl : public TOption
{
	public:
						TCMOSerialDTRControl();

		Boolean			fAssertDTR;			// defaults to TRUE. Set FALSE to negate DTR.
};


//--------------------------------------------------------------------------------
//	TCMOPCMCIAModemSound
//		Enable sound from pcmcia card modems. The modem comm tool will pass this
// 		to the TSerialChip to ask that the modem sound be routed to the speaker.
//	    This option will be ignored by TSerialChip's other than the TSerialChip16450.
// 		By default, the TSerialChip will NOT enable sound (it doens't know if this
//	 	serial chip is talking to a modem, a plain serial card, a pager card, etc.).
//
//		The TSerialChip will automatically turn off the sound channel when the
//		comm tool unbinds from it, so it is not necessary to pass this option again
//		when you hang up.
//--------------------------------------------------------------------------------

class TCMOPCMCIAModemSound : public TOption
{
	public:
						TCMOPCMCIAModemSound();

		Boolean			fEnableModemSound;
};

//--------------------------------------------------------------------------------
//	TCMOSerialHalfDuplex
//		Force half-duplex connection. Only valid at connect time and later.
//		The TSerialChip sets the default for this at bind time. If the
//		TSerialChip supports the ConfigureForOutput call, it will be notified
//		when output is starting, and when it is stopping, so it can switch between
//		transmit and receive modes.
//--------------------------------------------------------------------------------

class TCMOSerialHalfDuplex : public TOption
{
	public:
						TCMOSerialHalfDuplex();

		Boolean			fHalfDuplex;		// defaults to FALSE.
};


//--------------------------------------------------------------------------------
//	TCMOSerialMiscConfig
//		Miscellaneous configuration for async driver. These are probably only
//		useful for strange cases. Use at your own risk.
//--------------------------------------------------------------------------------

class TCMOSerialMiscConfig : public TOption
{
	public:
						TCMOSerialMiscConfig();

		TTimeout		inputDelay;			// defaults to kSerDefaultSendForIntDelay, 20 ms. delay for SendForInterrupt on input available.
		Boolean			disableInputDMA;	// defaults to FALSE.
		Boolean			disableOutputDMA;	// defaults to FALSE.
		Boolean			txdOffUntilSend; 	// defaults to FALSE. If set, transceiver is not enabled
											//  until the first send occurs. This is useful for
											//  clients that want to listen first.
		Boolean			txdOnIfGPiOn; 		// defaults to FALSE. This modifies txdOffUntilSend to
											//  work only if GPi is not asserted at open.
		Boolean			txdOnIfHSKiOn; 		// defaults to FALSE. This modifies txdOffUntilSend to
											//  work only if HSKi is not asserted at open.
};

//--------------------------------------------------------------------------------
//	TCMOSerialEventEnables
//		Enable the serial driver to interrupt the TEndPoint on particular state changes.
//--------------------------------------------------------------------------------

class TCMOSerialEventEnables : public TOption
{
	public:
						TCMOSerialEventEnables();

		ULong			serEventEnables;	// defaults to 0.
		TTimeout		carrierDetectDownTime;	// amount of dcd needs to be negated before
											//  reporting event: default 0 usec
};

//--------------------------------------------------------------------------------
//	TCMOSerialIOStats
//		parity framing, overrun error; total bytes putten/gotten
//      read-only. .
//--------------------------------------------------------------------------------

class TCMOSerialIOStats : public TOption
{
	public:
						TCMOSerialIOStats();

		ULong			parityErrCount;	// reset when read
		ULong			framingErrCount; // reset when read
		ULong			softOverrunCount;	// reset when read
		ULong			hardOverrunCount;	// reset when read

		UByte			fGPiState;		// current state of GPi (0 == negated, 1 == asserted)
		UByte			fHSKiState;		// current state of GPi (0 == negated, 1 == asserted)
		Boolean			fExternalClockDetect; // true if external clock has been detected...

};


//--------------------------------------------------------------------------------
//	TCMOInputFlowControlParms
//		software and hardware input flow control
//--------------------------------------------------------------------------------

class TCMOFlowControlParms : public TOption
{
	public:

		UChar			xonChar;			// default chDC1
		UChar			xoffChar;			// default chDC3
		Boolean			useSoftFlowControl;	// default FALSE
		Boolean			useHardFlowControl;	// default FALSE
		Boolean			hardFlowBlocked;	// default FALSE; TRUE if hardware flow blocked
		Boolean			softFlowBlocked;	// default FALSE; TRUE if software flow blocked

	protected:
						TCMOFlowControlParms();

	// NOTE: No one should instantiate this object directly;
	// use TCMOInputFlowControlParms or TCMOOutputFlowControlParms below
};

class TCMOInputFlowControlParms : public TCMOFlowControlParms
{
	public:
						TCMOInputFlowControlParms();
};

class TCMOOutputFlowControlParms : public TCMOFlowControlParms
{
	public:
						TCMOOutputFlowControlParms();
};


//--------------------------------------------------------------------------------
//	TCMOFramingParms
//		data framing options
//--------------------------------------------------------------------------------

class TCMOFramingParms : public TOption
{
	public:
						TCMOFramingParms();

		UChar			escapeChar;			// default chDLE; escape character
		UChar			eomChar;			// default chETX; eom character
		Boolean			doHeader;			// default TRUE; syn/dle/stx header
		Boolean			doOutFCS;			// default TRUE; compute and send 2-byte FCS at end
		Boolean			doInFCS;			// default TRUE; compute and check 2-byte FCS at end
};


//--------------------------------------------------------------------------------
//	TCMOFramedAsyncStats
//		Framed Async statistics
//--------------------------------------------------------------------------------

class TCMOFramedAsyncStats : public TOption
{
	public:
						TCMOFramedAsyncStats();

		ULong			preHeaderByteCnt;	// number of bytes discarded looking for valid header
};


//--------------------------------------------------------------------------------
//	TCMOKeyboardConfig
//		Misc keyboard comm tool configuration....
//--------------------------------------------------------------------------------

class TCMOKeyboardConfig : public TOption
{
	public:
						TCMOKeyboardConfig();

		// Keyboard options. fSCPAtPowerOn is always set true for 130-style keyboards, false
		//  for the Shay-style keyboards.
		Boolean			fPowerOffClose;		// defaults to TRUE. Close driver at power off (e.g., rely on SCP to restart).
		Boolean			fGPiDuringSCP;		// defaults to TRUE. Ignore data while GPi asserted.
		Boolean			fSCPAtPowerOn;		// defaults to TRUE. Ignore SCP data at power on.
		Boolean			fHSKiLoopedToHSKo;	// defaults to TRUE. Close driver if HSKi drops.

		// Shay-style keyboard specific options...
		Boolean			fPowerOnCheck;		// defaults to FALSE. Close driver if not detected at power on.

};


//--------------------------------------------------------------------------------
//	TCMOLocalTalkStats
//		LocalTalk statistics
//--------------------------------------------------------------------------------

class TCMOLocalTalkStats : public TOption
{
	public:
						TCMOLocalTalkStats();

		UByte	overrunErrCount;			// all of these default to zero (0)
		UByte	lengthErrCount;
		UByte	crcErrCount;
		UByte	underrunErrCount;
		UByte	randomCTSCount;
		UByte	collisionCount;
		UByte	deferCount;
		UByte	abortsDetected;
		UByte	abortsMissed;
		UByte	randomACKCount;
		UByte	noRoomForPacketCount;
};


//--------------------------------------------------------------------------------
//	TCMOLocalTalkNodeID
//		LocalTalk node id
//--------------------------------------------------------------------------------

class TCMOLocalTalkNodeID : public TOption
{
	public:
						TCMOLocalTalkNodeID();

		UByte	nodeID;						// default to zero (0) since node id of 0 is invalid...
};


//--------------------------------------------------------------------------------
//	TCMOLocalTalkMiscConfig
//		Miscellaneous configuration for localtalk driver. These are probably only
//		useful for strange cases. Use at your own risk.
//--------------------------------------------------------------------------------

class TCMOLocalTalkMiscConfig : public TOption
{
	public:
					TCMOLocalTalkMiscConfig();

		Boolean		peekMode;				// just listen to packets.
		Boolean		readControlPackets;		// listen to control packets as well as data packets.
		Boolean		saveErrPackets;			// save all packets, even those w. overruns and crc errors.
		UByte		nodeID;					// set to zero to listen to all packets.
};


//--------------------------------------------------------------------------------
//	TCMOSlowIRProtocolType
//		Slow IR protocol
//--------------------------------------------------------------------------------

class TCMOSlowIRProtocolType : public TOption
{
	public:
						TCMOSlowIRProtocolType();

		ULong protocol;			// defaults to irUsingNegotiateIR
		ULong options;			// defaults to irUsing9600

	// note that even though the values above are defined as
	// bitfields, only one of the values will be set in this option
	// high two bits of each are reserved for compatibility with Frames RINTs
};


//--------------------------------------------------------------------------------
//	TCMOSlowIRStats
//		Slow IR statistics
//--------------------------------------------------------------------------------

class TCMOSlowIRStats : public TOption
{
	public:
					TCMOSlowIRStats();

	ULong			dataPacketsIn;		// count of data packets received and ACKed
	ULong			checkSumErrs;		// count of checksum errors

	ULong			dataPacketsOut;		// count of data packets sent and ACKed
	ULong			dataRetries;		// count of data send retries

	ULong			falseStarts;		// count of times we thought we had a packet but were wrong
	ULong			serialErrs;			// count of SCC errors
	ULong			protocolErrs;		// count of poorly-formed packets received
};

//--------------------------------------------------------------------------------
//	TCMOSlowIRSniff
//		Slow IR sniffing
//--------------------------------------------------------------------------------

class TCMOSlowIRSniff : public TOption
{
	public:
						TCMOSlowIRSniff();

		Boolean			sniffEnable;	// TRUE if sniffing should be enabled during Open
};

//--------------------------------------------------------------------------------
//	TCMOSlowIRBitBang
//
//		Option for configuring direct IR banging for remote controls.
//		In this mode, sniffing and slow IR are disabled. Output byte 1's and 0's are
//      interpreted as values for the direct IR bit banging, based on the bit rate
//      configured below.
//
// 		With bit-banged IR, all the output has to fit into our buffer, the rest is just
//		not sent. Otherwise, there would be big gaps in the output where we depleted the
//		'dma' buffer, and had to refill from the user's buffer. We could get around this
//		in the future with double-buffering.
//
//--------------------------------------------------------------------------------

class TCMOSlowIRBitBang : public TOption
{
	public:
						TCMOSlowIRBitBang();

		ULong			bitTime;			// bit timing in microseconds
		Long			count;				// repeat count for code (defaults to 1)
		Boolean			enableBitBangIR;	// defaults to TRUE (May be ignored in 2.0)
};

//--------------------------------------------------------------------------------
//	TCMOSlowIRConnect
//		Slow IR connection options
//--------------------------------------------------------------------------------

class TCMOSlowIRConnect : public TOption
{
	public:
						TCMOSlowIRConnect();

		ULong			connectOptions;		// connect-time options, defaults to 0
};

//--------------------------------------------------------------------------------
//	TCMOIrDADiscovery
//		IrDA discovery options
//--------------------------------------------------------------------------------

class TCMOIrDADiscovery : public TOption
{
	public:
						TCMOIrDADiscovery();

		ULong			fProbeSlots;		// number of slots, defaults to 8 (valid are 1, 6, 8, 16)
		ULong			fMyServiceHints;	// my service hints, defaults to kDevInfoHintPDA
		ULong			fPeerServiceHints;	// set: service hint mask, defaults to 0xFFFFFFFF (match any), get: actual peer device service hints
		ULong			fPeerDevAddr;		// device addr we connected to, defaults to 0
		ULong			fMediaBusyCheck;	// check 600ms for other traffic before sending discovery, defaults to true
};

//--------------------------------------------------------------------------------
//	TCMOIrDAReceiveBuffers
//		IrDA receive buffer(s) options
//--------------------------------------------------------------------------------

class TCMOIrDAReceiveBuffers : public TOption
{
	public:
						TCMOIrDAReceiveBuffers();

		ULong			fSize;				// size of each receive buffer, defaults to 512
		ULong			fCount;				// number of receive buffers, defaults to 1
};

//--------------------------------------------------------------------------------
//	TCMOIrDALinkDisconnect
//		IrDA link disconnect options
//--------------------------------------------------------------------------------

class TCMOIrDALinkDisconnect : public TOption
{
	public:
						TCMOIrDALinkDisconnect();

		ULong			fTimeout;			// link w/no activity drops after this many secs, defaults to 40
};

//--------------------------------------------------------------------------------
//	TCMOIrDAConnectionInfo
//		IrDA lsap connection info options
//--------------------------------------------------------------------------------

class TCMOIrDAConnectionInfo : public TOption
{
	public:
						TCMOIrDAConnectionInfo();

		ULong			fMyLSAPId;			// Newton's lsapId (if fixed id is desired, else use 0 for dynamic), defaults to 0
		ULong			fPeerLSAPId;		// Peer device's lsapId (if known, else use 0 for lookup), defaults to 0
		ULong			fMyNameLength;		// length of Newton's IAS class name string, defaults to 1
		ULong			fPeerNameLength;	// length of peer device's IAS class name string, defaults to 1
		UChar			fClassNames[61];	// my class name (null terminated) followed by peer's class name, defaults to "X"/"X"
};

//--------------------------------------------------------------------------------
//	TCMOIrDAConnectUserData
//		IrDA lsap connection class name options
//--------------------------------------------------------------------------------

class TCMOIrDAConnectUserData : public TOption
{
	public:
						TCMOIrDAConnectUserData();

		ULong			fDataLength;		// length of data that follows
		UChar			fData[60];			// data passed w/connect and/or accept received w/listen
};

//--------------------------------------------------------------------------------
//	TCMOIrDAConnectAttrName
//		IrDA lsap connection attribute name option
//		Used by comm tools that implement higher levels of the IrDA stack and
//		want to register their LSAP ids with a different attribute name.
//--------------------------------------------------------------------------------

class TCMOIrDAConnectAttrName : public TOption
{
	public:
						TCMOIrDAConnectAttrName();

		ULong			fNameLength;		// length of attr name that follows
		UChar			fName[60];			// attr name (defaults to "IrDA:IrLMP:LsapSel")
};

#endif // notFRAM

#endif //	__SERIALOPTIONS_H

