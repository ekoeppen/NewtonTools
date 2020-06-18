/*
	File:		SerialChipV2.h

	Contains:	Interface to serial chips, version 2.

	Copyright:	� 1993-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v9 (8/2/96) internal.

	Notes on Implementing a TSerialChip:

		For simple async serial chips, the old version 1 TSerialChip interface may be
		used. The newer version is more complex, and supports a wider range of serial
		communication, from simple serial, to localtalk, to IR. It has support for
		a number of unusual communication modes used to communicate with devices such
		as the LaserWriter LS, and IR devices such as TVs and VCRs.

		Implementing a TSerialChip has different challenges than using one. If the
		serial chip is on a PCMCIA card, this is relatively easy, and copying the
		TSerialChip16450 implementation example and changing that should be fairly
		straightforward.

	Notes on Using a TSerialChip:

		These are typically used only by low-level serial comm tools in the Newton ROM since
		they are tricky to use. The serial tool calls into the TSerialChip protocol; some
		of these calls have to be done with all interrupts excluded. The TSerialChip has
		four callbacks into the serial tool, all done at interrupt time. Therefore, the
		comm tool will have some interrupt-level routines, and will have to be very
		careful about synchronizing access to the TSerialChip between these interrupt
		level routines and higher-level methods that also want to access the chip.

		The easiest way to use a TSerialChip is indirectly: use the TAsyncSerTool,
		TFramedAsyncSerTool, or TLocalTalkTool comm tools instead, and let them
		do the difficult work of interfacing to the TSerialChip.

		Still not convinced? Also note that the TSerialChip may disappear at interrupt time
		(if it's on a PCMCIA card that is being yanked), and that the version of the
		TSerialChip interface may be version 1, version 2, or a later version. Good luck!
		(And make sure you lock down your stack since you'll have to call EnterFIQAtomic
		before invoking some of the TSerialChip methods).

*/

#ifndef	__SERIALCHIPV2_H
#define __SERIALCHIPV2_H

#ifndef __NEWTTYPES_H
#include "NewtTypes.h"
#endif

#ifndef __PROTOCOLS_H
#include "Protocols.h"
#endif

#ifndef __SERIALOPTIONS_H
#include "SerialOptions.h"
#endif

#ifndef	__SYSTEMEVENTS_H
#include "SystemEvents.h"		// for power on wakeups...
#endif


// Implementations
#define kSerialChip16450ID		 	's450'

class TCardHandler;			// card handler protocol..
class TCardSocket;			// card socket protocol..
class TCircleBuf;			// circular buffer, usable for dma
class TOutDMACircleBuf;
class TOption;				// standard option class

/*	----------------------------------------------------------------
**
**	Various standard capabilities
**
*/

#define	kCapability_Version_2	'v2.0'	/* chip can handle extended 2.0 calls  */


/* --------------------------------------------------------------------------------
	TSerialChip

	A non-SCC connected modem (or other serial device) should have a TSerialChip
	implementation. This may be in-ROM, or loaded off a PCMCIA card. The
	on-board TAsyncSerTool will look for a TSerialChip registered with the
	NameServer if given the appropriate option.

	The object should be locked in memory when allocated, since it will be
	accessed at interrupt time.

   -------------------------------------------------------------------------------- */


// There are four interrupts the serial chip can generate. The TAsyncSerTool object
//  will register handlers for these with the TSerialChip device via the InstallHandlers
//  method. A PCMCIA-based device will take the single I/O card interrupt and
//  invoke the appropriate handler based on other serial chip information.

typedef ULong RxErrorStatus;					/* mirrors SCC read register 1 bits			*/
#define kSerialRxParityErr		(0x00000010)
#define kSerialRxOverrun		(0x00000020)
#define kSerialRxFramingErr		(0x00000040)
#define kSerialRxEOF			(0x00000080)
#define kSerialRxSoftOverrun	(0x00000100)	/* software detected errors */
#define kSerialRxTimeout		(0x00000200)
#define kSerialRxUnderrun		(0x00000400)

typedef ULong SerialOutputControl;
#define kSerialOutputDTR		(0x00000001)
#define kSerialOutputRTS		(0x00000002)

typedef ULong SerialStatus;						/* mirrors SCC read register 0 bits			*/
#define kSerialRxCharAvailable	(0x00000001)
#define kSerialDSRAsserted		(0x00000002)	/* 2.0 CHANGE!!					*/
#define kSerialTxBufferEmpty	(0x00000004)
#define kSerialDCDAsserted		(0x00000008)	/* note positive logic here					*/
#define kSerialRIAsserted		(0x00000010)	/* 2.0 CHANGE!!					*/
#define kSerialCTSAsserted		(0x00000020)	/* 2.0 CHANGE!!					*/
#define kSerialTxUnderrun		(0x00000040)
#define kSerialBreak			(0x00000080)
#define kSerialAbort			(0x00000080)
#define kSerialChipGone			(0x00000100)	/* card pulled out!							*/

typedef ULong SerialFeatures; 					/* features supported by this chip (v2.0)	*/
#define kSerFeatureNone			(0x00000000)
#define kSerFeatureDefaults		(0x00000001)	/* default capabilities (used for v1.0 chips) */
#define kSerFeatureVersion2		(0x00000002)	/* supports version 2.0 interface calls		*/
#define kSerFeatureTriStateTxD	(0x00000004)	/* can tristate TxD							*/
#define kSerFeatureHiSpeedClk	(0x00000008)	/* can switch to high-speed clock...(?)		*/
#define kSerFeatureCTSClock		(0x00000010)	/* CTS may be used for clocking
													(enables auto-clock detect feature)		*/
#define kSerFeatureAllSent		(0x00000020)	/* All sent call is supported				*/
#define kSerFeatureTxConfigNeeded (0x00000040)	/* output config needed: half duplex...		*/
#define kSerFeatureTVRemote		(0x00000080)	/* supports TV remote mode					*/
#define kSerFeatureGetErrByte	(0x00000100)	/* supports GetErrorByte call				*/
#define kSerFeatureSDLCMode		(0x00000200)	/* supports sdlc sync calls					*/
#define kSerFeatureLocalTalk 	(0x00000400)	/* supports localtalk calls					*/
#define kSerFeatureAsyncRxDMA 	(0x00001000)	/* supports input dma for async				*/
#define kSerFeatureAsyncTxDMA 	(0x00002000)	/* supports output dma for async			*/
#define kSerFeatureSyncRxDMA 	(0x00004000)	/* supports input dma for sync				*/
#define kSerFeatureSyncTxDMA 	(0x00008000)	/* supports output dma for sync				*/
#define kSerFeatureWireAsyncRxDMABuf (0x00010000)	/* async input dma requires wired buffer	*/
#define kSerFeatureWireAsyncTxDMABuf (0x00020000)	/* async output dma requires wired buffer	*/
#define kSerFeatureWaitForAllSent (0x00100000)	/* WaitForAllSent call available?	*/

typedef ULong SerialIntSource;					/* matches Voyager interrupt mask reg bits */
#define kSerIntSrcAbort			(0x00000001)	/* break or abort */
#define kSerIntSrcHunt			(0x00000002)
#define kSerIntSrcUnderRun		(0x00000004)
#define kSerIntSrcCTS			(0x00000008)
#define kSerIntSrcDCD			(0x00000010)
#define kSerIntSrcRxSpecial 	(0x00000020)
#define kSerIntSrcRxOnAllChars  (0x00000040)
#define kSerIntSrcTxBufEmpty  	(0x00000080)
#define kSerIntSrcRxOnFirstChar (0x00000100)	/* may go away  */

typedef ULong SerialMode;
#define kSerModeAsync			(0x00000000)	/* async serial mode */
#define kSerModeSync			(0x00000001)	/* set sdlc mode	*/
#define kSerModeLocalTalk		(0x00000002)	/* localtalk mode	*/
#define kSerModeMask 			(0x00000003)	/* async/sync/localtalk mask		*/
#define kSerModeHalfDuplex		(0x00000004)	/* input and output are exclusive	*/
#define kSerModePolled			(0x00000008)	/* polled mode: interrupts are off initially */

typedef UByte DMAControl;
#define kDMANoOp				(0x00)			/* no change */
#define kDMAStart				(0x01)			/* start dma interface */
#define kDMAStop				(0x02)			/* stop dma interface */
#define kDMASuspend				(0x03)			/* suspend? */
#define kDMASync				(0x04)			/* move any bytes into client buffer */
#define kDMAFlush				(0x05)			/* flush any bytes currently in buffer */
#define kDMACommandMask			(0x0f)			/* use to isolate command */
#define kDMANotifyOnNext		(0x10)			/* set notify on next */

// A TSerTool installs SCCIntHandler's to handle the various SCC channel interrupts.
typedef void(*SCCIntHandler)(void*);
typedef void(*RxDMAIntHandler)(void*, RxErrorStatus);
typedef void(*TxDMAIntHandler)(void*);

// There are four interrupts per channel.
struct SCCChannelInts
{
	SCCIntHandler		TxBEmptyIntHandler;
	SCCIntHandler		ExtStsIntHandler;
	SCCIntHandler		RxCAvailIntHandler;
	SCCIntHandler		RxCSpecialIntHandler;
};

struct SCCDMARegPtrs
{
	ULong *				controlReg;			// Control register address
	ULong *				baseReg;			// Base register address
	ULong *				pointerReg;			// Pointer register address
	ULong *				sizeReg;			// Size register address
	ULong *				countReg;			// Count register address
	ULong *				wordReg;			// Word register address
	ULong *				compareReg;			// Compare register address
	ULong				theInt;				// Interrupt selector
};


PROTOCOL TSerialChip : public TProtocol
{
	public:

	static TSerialChip* New(char*);
	void				Delete();

	NewtonErr 			InstallChipHandler(void* serialTool, SCCChannelInts* intHandlers);
	NewtonErr 			RemoveChipHandler(void* serialTool);

	void				PutByte(UByte nextChar);	// ** only called if TxBufEmpty() or TxBE int
	void				ResetTxBEmpty();			// ** called if TxBE int and no more to write
	UByte				GetByte();					// ** only called if RxBufFull() or RxBF int
	Boolean				TxBufEmpty();				// ** is transmitter ready for another byte?
	Boolean				RxBufFull();				// ** does receiver have a byte available?
	RxErrorStatus		GetRxErrorStatus();			// ** return receive error status indications for current
													//  byte available - this resets the status
	SerialStatus		GetSerialStatus();			// get status bits
	void				ResetSerialStatus();		// reset latched status bits
	void				SetSerialOutputs(SerialOutputControl); 		// **
	void				ClearSerialOutputs(SerialOutputControl);	// **
	SerialOutputControl	GetSerialOutputs();

	void				PowerOff();					// turn power off (may not be called)
	void				PowerOn();					// turn power back on and reconfigure
	Boolean				PowerIsOn();				// is serial chip powered?
	void				SetInterruptEnable(Boolean enable); // ** enable/disable interrupts

	void				Reset();					// **
	void				SetBreak(Boolean assert);	// **

	InterfaceSpeed		SetSpeed(BitRate bitsPerSec);
	void				SetIOParms(TCMOSerialIOParms* opt);	// set bit rate, parity, data bits, stop bits
	void				Reconfigure();				// ** reconfigure based on speed, IOParms

	//---------------------------------------------
	// Special methods for PCMCIA card serial chips

	NewtonErr			Init(TCardSocket* theCardSocket, TCardHandler* theCardHandler, UByte* baseRegAddr);
	void				CardRemoved(void);			// async "card gone" call - call with IRQs disabled!

	//	----------------------------------------------------------------
	//
	//	2.0 calls
	//
	SerialFeatures		GetFeatures();				// return features vector of this chip
	NewtonErr			InitByOption(TOption* initOpt); // used instead of Init for 2.0 interfaces.
	NewtonErr 			ProcessOption(TOption* opt); // process option from client
	NewtonErr			SetSerialMode(SerialMode mode); // call after binding

	void				SysEventNotify(ULong event); // called when serial tool gets a power on/off event
													// event is generally kSysEvent_PowerOn or kSysEvent_PowerOff
													// called after comm tool for power-off, and before for power-on

	void				SetTxDTransceiverEnable(Boolean enable); // **
	RxErrorStatus		GetByteAndStatus(UByte* nextCharPtr); // ** NOTE: GetRxErrorStatus not called if this is available

	NewtonErr			SetIntSourceEnable(SerialIntSource src, Boolean enable);
													// enable/disable specific ints. Returns error
													//  if that particular source cannot be controlled?
													//  Only used currently to shut off CTS ints on auto-clock detect.
	Boolean				AllSent();					// ** have all transmit characters left chip?
	void 				ConfigureForOutput(Boolean start);	// only called if kSerFeatureTxConfigNeeded = 1

	//  ------------------------------------------
	//  Methods for DMA control ...

	NewtonErr			InitTxDMA(TCircleBuf* buf, SCCIntHandler txDMAIntHandler);
	NewtonErr			InitRxDMA(TCircleBuf* buf, ULong notifyLevel, RxDMAIntHandler intHandler);	// int handler takes flags param!
	NewtonErr			TxDMAControl(DMAControl ctl); 	// start, stop, reset, etc.
	NewtonErr			RxDMAControl(DMAControl ctl); 	// start, stop, reset, suspend, etc.

	//  ------------------------------------------
	//  Special methods for Synchronous serial...

	void 				SetSDLCAddress(UByte nodeID); // **
	void				ReEnableReceiver(Boolean reset); // ** reenable receiver for another packet

	//---------------------------------
	// Special methods for LocalTalk...

	Boolean 			LinkIsFree(Boolean resetClks);
	Boolean 			SendControlPacket(UByte pType, UByte dest, Boolean syncPulse); // sync send control packet
	void				WaitForPacket(TTimeout delay); 	// sync wait for a control packet in...
														//  call RxDMAIntHandler if one comes in.
														//  NOTE: may turn async if data packet comes in...

	//	----------------------------------------------------------------
	//
	//	3.0 calls
	//
	NewtonErr			WaitForAllSent(); 			// delay until all bytes have been sent

	// ** called with interrupts disabled...
};

#endif /*__SERIALCHIPV2_H*/
