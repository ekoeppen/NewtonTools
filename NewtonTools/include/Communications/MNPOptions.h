/*
	File:		MNPOptions.h

	Contains:	Options for the MNPTool

	Copyright:	� 1992-1993, 1995 by Apple Computer, Inc., all rights reserved.

	Derived from v11 internal.

*/



#ifndef __MNPOPTIONS_H
#define __MNPOPTIONS_H

#ifndef FRAM

#ifndef	__COMMSERVICES_H
#include "CommServices.h"
#endif

#ifndef __SERIALOPTIONS_H
#include "SerialOptions.h"
#endif

#ifndef	__OPTIONARRAY_H
#include "OptionArray.h"
#endif

// MNP Option Labels
#define kCMOMNPAllocate 		'mnpa'			/* MNP Allocate */
#define kCMOMNPCompression		'mnpc'			/* MNP Compression */
#define kCMOMNPDataRate			'eter'			/* End To End Rate */
#define kCMOMNPSpeedNegotiation	'mnpn'			/* MNP speed Negotiation */
#define kCMOMNPStatistics		'mnps'			/* MNP Statistics */

#else

// for FRAM
// MNP Option Labels
#define kCMOMNPAllocate 		"mnpa"			/* MNP Allocate */
#define kCMOMNPCompression		"mnpc"			/* MNP Compression */
#define kCMOMNPDataRate			"eter"			/* end to end rate */
#define kCMOMNPSpeedNegotiation	"mnpn"			/* MNP speed Negotiation */
#define kCMOMNPStatistics		"mnps"			/* MNP Statistics */

#endif not FRAM





//--------------------------------------------------------------------------------
//	TCMOMNPAllocate
//		Specifies if MNP should allocate it's memory to be ready for connection.
//		Only valid at open time.
//--------------------------------------------------------------------------------
#ifndef FRAM

class TCMOMNPAllocate : public TOption
{
	public:
					TCMOMNPAllocate();

		Boolean		fMNPAlloc;		// if true, mnp driver allocates it's memory and
									// is available for connection

	// default is true
};


//	NOTE:	The compression type precedence will be (in decending order):
//			V42bis, MNP7, MNP5, none
//
//--------------------------------------------------------------------------------
//	TCMOMNPCompression
//		Defines the compression type for MNP connections.
//		This option is required for MNP services
//--------------------------------------------------------------------------------

typedef FastInt MNPCompressionType;
#endif not FRAM

#define	kMNPCompressionNone		0x00000001		// connect with no compression
#define	kMNPCompressionMNP5		0x00000002		// connect with MNP 5 compression
#define	kMNPCompressionMNP7		0x00000004		// connect with MNP 7 compression	NOT YET SUPPORTED
#define	kMNPCompressionV42bis	0x00000008		// connect with V42bis compression


#ifndef FRAM
class TCMOMNPCompression : public TOption
{
	public:
								TCMOMNPCompression();

		MNPCompressionType		fCompressionType;

	// default is V.42bis, MNP5, and None
};


//--------------------------------------------------------------------------------
//	TCMOMNPDataRate
//		Data rate, in bits per second, for MNP connection.  All MNP timers are based on this rate.
//		The data rate must reflect the MNP to MNP connection data rate (end to end).
//		Not the serial interface speed which may or may not be the same.
//		This is a required address option for MNP services
//--------------------------------------------------------------------------------

class TCMOMNPDataRate : public TOption
{
	public:
					TCMOMNPDataRate();

		ULong		fDataRate;

	// default is 2400
};


//--------------------------------------------------------------------------------
//	TCMOMNPSpeedNegotiation
//		This option controls the MNP speed negotiation.  When this option is
//		used prior to or when connecting, MNP will negotiate with the remote
//		end to change speed to the negotiated level.  This feature is implemented
//		as an Apple specific parameter in the Link Request packet.  This
//		Apple specific option is not part of the standard MNP implementation.
//		If the remote end does not support this feature, the LR parameter is
//		ignored.
//
//		NOTE:  The MNP Link Request packets are sent at the original connect
//		speed (set using kCMOSerialIOParms or kCMOSerialBitRate).  When this
// 		option is used, it is assumed speed negotiated is the MNP Data Rate, and
//		the serial port speed will be set to this value.
//
//		The resulting connection speed can be determined by getting the current
//		value of the kCMOMNPDataRate option after connecting.
//
//--------------------------------------------------------------------------------

class TCMOMNPSpeedNegotiation : public TOption
{
	public:
					TCMOMNPSpeedNegotiation();

		BitRate		fRequestedSpeed;			// default 57600 bps, speed rate to set serial
};


//--------------------------------------------------------------------------------
//	TCMOMNPStatistics
//		MNP Connection Statistics.  Read/Write option.  Read to get current values,
//		write to reset the values.
//
//--------------------------------------------------------------------------------

class TCMOMNPStatistics : public TOption
{
	public:
					TCMOMNPStatistics();

		ULong		fAdaptValue;				// default 196, max data packet size, adaptive
		ULong		fLTRetransCount;			// default 0, retransmission count for current LT
		ULong		fLRRetransCount;			// default 0, retransmission count for current LR
		ULong		fRetransTotal;				// default 0, total number of frame retransmissions
		ULong		fRcvBrokenTotal;			// default 0, total number of broken frames received
		ULong		fForceAckTotal;				// default 0, total number of forced Acks
		ULong		fRcvAsyncErrTotal;			// default 0, total number of serial driver async errors
		ULong		fFramesRcvd;				// default 0, total number of frames received
		ULong		fFramesXmited;				// default 0, total number of frames transmitted
		ULong		fBytesRcvd;					// default 0, total number of data bytes received
		ULong		fBytesXmited;				// default 0, total number of data bytes transmitted
		ULong		fWriteBytesIn;				// default 0, user data write byte count before compression
		ULong		fWriteBytesOut;				// default 0, user data write byte count after compression
		ULong		fReadBytesIn;				// default 0, user data read byte count before decompression
		ULong		fReadBytesOut;				// default 0, user data read byte count after decompression
		ULong		fWriteFlushCount;			// default 0, Number of flush calls to compressor
};
#endif not FRAM

//
// Connect options used for testing.
//

#ifndef FRAM

#define kCMOMNPDebugConnect 'mdct'			/* MNP Debug Connect options */

#else

#define kCMOMNPDebugConnect "mdct"			/* MNP Debug Connect options */

#endif not FRAM

#ifndef FRAM
class TCMOMNPDebugConnect : public TOption
{
	public:
					TCMOMNPDebugConnect();

		Boolean		fARACompatibleMode;			// default false, switch on ARA compatibility
		Boolean		fClass4;					// default true, enable class 4
		Boolean		fStreamModeMax;				// default true, enable class 4 max data
		UChar		fMaxCredit;					// default 8, size of flow control window
		ULong		fMaxDataSize;				// default 64, size of max data pkt

};
#endif not FRAM



#endif  __MNPOPTIONS_H

