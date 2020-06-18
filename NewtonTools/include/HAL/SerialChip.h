/*
	File:		SerialChip.h

	Contains:	Interface to simple async serial chip (as opposed to full-blown SCC).
				This can be used for support of PCMCIA serial-chip-based modems:
				PCMCIA modem cards typically have a simple serial 16450 chip on them
				for the host interface.

				NOTE: Only one of the protocol files SerialChipV1.h and SerialChipV2.h
				can be built into the ROM. Otherwise routines will be doubly defined!
				For 2.0 ROMs, SerialChipV2.h is built into the ROM, and SerialChipV1.h
				is simply included by the simpler TSerialChip's.

	Copyright:	� 1993-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v2 internal.

*/

#ifndef	__SERIALCHIPV1_H
#define __SERIALCHIPV1_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef __PROTOCOLS_H
#include "Protocols.h"
#endif

#include "SerialOptions.h"

// Implementations
#define kSerialChip16450ID		 	's450'

class TCardHandler;			// card handler protocol..
class TCardSocket;			// card socket protocol..

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

typedef ULong RxErrorStatus;					// mirrors SCC read register 1 bits
#define kSerialRxParityErr		(0x00000010)
#define kSerialRxOverrun		(0x00000020)
#define kSerialRxFramingErr		(0x00000040)

typedef ULong SerialOutputControl;
#define kSerialOutputDTR		(0x00000001)
#define kSerialOutputRTS		(0x00000002)

typedef ULong SerialStatus;						// mirrors SCC read register 0 bits
#define kSerialRxCharAvailable	(0x00000001)
#define kSerialTxBufferEmpty	(0x00000004)
#define kSerialDCDAsserted		(0x00000008)	// note positive logic here
#define kSerialCTSNegated		(0x00000020)	// note negative logic here
#define kSerialBreak			(0x00000080)
#define kSerialChipGone			(0x00000100)	// card pulled out!

// A TSerTool installs SCCIntHandler's to handle the various serial chip interrupts.
typedef void(*SCCIntHandler)(void*);

// There are four interrupts per channel.
struct SCCChannelInts
{
	SCCIntHandler		TxBEmptyIntHandler;
	SCCIntHandler		ExtStsIntHandler;
	SCCIntHandler		RxCAvailIntHandler;
	SCCIntHandler		RxCSpecialIntHandler;
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
	void				ClearSerialOutputs(SerialOutputControl); 	// **
	SerialOutputControl	GetSerialOutputs();

	void				PowerOff();					// turn power off (may not be called)
	void				PowerOn();					// turn power back on and reconfigure
	Boolean				PowerIsOn();				// is serial chip powered?
	void				SetInterruptEnable(Boolean enable); // ** enable/disable interrupts

	void				Reset();					 	// **
	void				SetBreak(Boolean assert); 		// **

	InterfaceSpeed		SetSpeed(BitRate bitsPerSec);
	void				SetIOParms(TCMOSerialIOParms* opt);	// set bit rate, parity, data bits, stop bits
	void				Reconfigure();				// ** reconfigure based on speed, IOParms

	//---------------------------------------------
	// Special methods for PCMCIA card serial chips

	NewtonErr			Init(TCardSocket* theCardSocket, TCardHandler* theCardHandler, UByte* baseRegAddr);
	void				CardRemoved(void);			// async "card gone" call - call with IRQs disabled!

	// ** called with interrupts disabled...
};

#endif __SERIALCHIP_H
