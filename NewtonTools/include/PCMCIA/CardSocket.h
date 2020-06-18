/*
	File:		CardSocket.h

	Copyright:	� 1992-1997 by Apple Computer, Inc., all rights reserved.

	Derived from v16 (5/16/97) internal.

*/




#ifndef	__CARDSOCKET_H
#define __CARDSOCKET_H

#ifndef __CONFIGPCMCIA_H
#include "ConfigPCMCIA.h"
#endif


#ifdef	hasPCMCIA


#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef	__USERDOMAIN__
#include "UserDomain.h"
#endif

#ifndef	__USERPHYS__
#include "UserPhys.h"
#endif

#ifndef __KERNELTYPES__
#include "KernelTypes.h"
#endif

#ifndef	__USERPORTS__
#include "UserPorts.h"
#endif

#ifndef	__CARDDEFINES_H
#include "CardDefines.h"
#endif





class TCardSocket;
class TCardDMAEngine;
struct InterruptObject;
struct GPIOIntObject;



//
//	Interrupt definitions
//

typedef	NewtonErr (*IntProcPtr)(void *object, TCardSocket* socket);		// Interrupt proc ptr

enum TSocketInt											// Socket interrupt types
{
	kSocketBusyInt				=	0,					// Memory card busy interrupt
	kSocketStatusChangedInt		=	1,					// IO card status changed interrupt#
	kSocketCardDetectedInt		=	2,					// Card detected interrupt		(*** For internal use ***)
	kSocketCardLockInt			=	3,					// Card unlock/remove interupt	(*** For internal use ***)
	kSocketCardIREQInt			=	4,					// IO card IREQ interrupt

	// Brick only

	kSocketCardInsertInt		=	5,					// Card inserted interrupt#		(*** For internal use ***)

	// Voyager only

	kSocketSpeakerInt			=	6,					// Speaker interrupt#
	kSocketDREQInt				=	7,					// DMA REQ interrupt
	kSocketWPInt				=	8,					// WP interrupt

	kSocketReadFailureInt		=	9,					// Read failure interrupt		(*** For internal use ***)
	kSocketWriteFailureInt		=	10,					// Write failure interrupt		(*** For internal use ***)
	kSocketWrFIFOEmptyInt		=	11,					// Write FIFO empty interrupt
	kSocketWrFIFOThreshldInt	=	12,					// Write FIFO threshold met (2 or 4 entries interrupt)

	kSocketIntCount,									// Interrupt type count

	kSocketOkToEnableInt		=	0xFFFFFFFF			// 1347661 Ok to enable interrupt now (FOR INTERNAL USE)
};

enum TSocketIntFlags
{
	kSocketIntEnableRising		=	0x0001,				// Enable rising edge interrupt
	kSocketIntEnableFalling		=	0x0002,				// Enable falling edge interrupt
	kSocketIntPromoteFIQ		=	0x0004,				// Promote interrupt to FIQ
	kSocketIntWakeup			=	0x0008				// Wakeup when interrupted
};


enum TSocketPowerLevels									// Used in RequestPower() and ReleasePower()
{
	kSocketPowerLevelVcc		=	0x00,				// Vcc
	kSocketPowerLevelVcc5V,								// 5 V Vcc
	kSocketPowerLevelVcc12V,							// 12 V Vcc
	kSocketPowerLevelVcc3p3V,							// 3.3 V Vcc
	kSocketPowerLevelVccXpXV,							// X.X V Vcc
	kSocketPowerLevelVccYpYV,							// Y.Y V Vcc
	kSocketPowerLevelVcc0V,								// 0 V Vcc
	kSocketPowerLevelVpp		=	0x10,				// Vpp
	kSocketPowerLevelVpp5V,								// 5 V Vpp
	kSocketPowerLevelVpp12V,							// 12 V Vpp
	kSocketPowerLevelVpp3p3V,							// 3.3 V Vpp
	kSocketPowerLevelVppXpXV,							// X.X V Vpp
	kSocketPowerLevelVppYpYV,							// Y.Y V Vpp
	kSocketPowerLevelVpp0V								// 0 V Vpp
};

#define kAllCurrent				(-1)					// All power using by the socket



//
//	Voltage definitions
//

#ifndef __kPCMCIAVoltageAvailibilities					// ���� Also defined in PlatformDriver.h
#define __kPCMCIAVoltageAvailibilities
enum kPCMCIAVoltageAvailibilities
{
	kPCMCIA5VAvailable			=	0x0001,				// 5.0 V available
	kPCMCIA12VAvailable			=	0x0002,				// 12.0 V available
	kPCMCIA3p3VAvailable		=	0x0004,				// 3.3 V available
	kPCMCIAXpXVAvailable		=	0x0008,				// X.X V available
	kPCMCIAYpYVAvailable		=	0x0010,				// Y.Y V available
	kPCMCIA0VAvailable			=	0x0020				// 0 V available (for example: 0 V Vpp)
};
#endif



//
//	TCardSocket definitions
//

class TCardSocket : public SingleObject
{
	public:

		TCardSocket(ULong socketNumber=0);				// Constructor with socket number
		~TCardSocket(void);								// Destructor

		//	Socket infomation

		TObjectId	SocketDomain(void);					// Get socket domain
		TObjectId	SocketPhysResource(void);			// Get socket physical resource
		ULong		SocketNumber(void);					// Get socket number

		ULong		AttributeMemBaseAddr(void);			// Get attribute memory base address
		ULong		CommonMemBaseAddr(void);			// Get common memory base address
		ULong		IOBaseAddr(void);					// Get IO base address

		NewtonErr	CreateSocketPhys(TUPhys* phys, ULong cardOffset, ULong size, Boolean readOnly=false);	// Create socket physical resource

		TCardDMAEngine*	DMAEngine(void);				// Get DMA engine

		//	Interrutpt handler

		NewtonErr	RegisterSocketInterrupt(TSocketInt intType, IntProcPtr intProc, void *intProcObj);		// Register ready/IRQ interrupt proc
		void		DeregisterSocketInterrupt(TSocketInt intType);	// Deregister interrupt
		void		EnableSocketInterrupt(TSocketInt intType);		// Enable interrupt
		void		DisableSocketInterrupt(TSocketInt intType);		// Disable interrupt
		void		ClearSocketInterrupt(TSocketInt intType);		// Clear interrupt

		//	Socket controls

		void		SetControl(ULong control);			// Set control

		//	Socket status

		Boolean		IsIOInteface(void);					// Is PCMCIA IO interface selected
		Boolean		IsPCMCIABusEnable(void);			// Is PCMCIA bus enabled

		ULong		GetControl(void);					// Get control
		ULong		GetPCPins(void);					// Get pin states

		Boolean		IsCardDetected(void);				// Is card deteced
		Boolean		IsReady(void);						// Is ready				(memory interface only)
		Boolean		IsIRQ(void);						// Is IRQ high			(io interface only)
		Boolean		IsStatusChanged(void);				// Is status changed	(io interface only)
		Boolean		IsWriteProtected(void);				// Is write protected	(memory interface only)

		TNanoAmp	VccMaxCurrent(void);				// Vcc max current supply
		TNanoAmp	VppMaxCurrent(void);				// Vpp (Vpp1 + Vpp2) max current supply
		TNanoAmp	Vpp1MaxCurrent(void);				// Vpp 1 max current supply
		TNanoAmp	Vpp2MaxCurrent(void);				// Vpp 2 max current supply
		TMicroVolt	VccMaxVoltage(void);				// Vcc max voltage supply (use VccVoltageSpec() in 2.0)
		TMicroVolt	VccMinVoltage(void);				// Vcc min voltage supply (use VccVoltageSpec() in 2.0)
		TMicroVolt	VppMaxVoltage(void);				// Vpp max voltage supply (use VppVoltageSpec() in 2.0)
		TMicroVolt	VppMinVoltage(void);				// Vpp min voltage supply (use VppVoltageSpec() in 2.0)

		TNanoSecond	VccRisingTime(void);				// Vcc rising time
		TNanoSecond	VppRisingTime(void);				// Vpp rising time


		//	Socket setup

		void		PCMCIAReset(void);					// PCMCIA bus reset

		void		SelectMemoryInterface(void);		// Select PCMCIA memory interface
		void		SelectIOInterface(void);			// Select PCMCIA IO interface

		void		SetDefaultSpeeds(void);						// Set default speeds and timeouts
		void		SetAttributeMemSpeed(TNanoSecond speed);	// Set attribute memory wait speed
		void		SetCommonMemSpeed(TNanoSecond speed);		// Set common memory wait speed
		void		SetIOSpeed(TNanoSecond speed);				// Set IO wait speed
		void		SetWatchTimer(TNanoSecond time);			// Set system to card watch dog timer
		void		SetDMAWatchTimer(TNanoSecond time);			// Set DMA to card watch dog timer
		void		SetBusTimer(TNanoSecond time);				// Set bus timer
		TNanoSecond	GetCommonMemSpeed(void);					// Get common memory wait speed


		//	New for 2.0

		ULong		Version(void);						// TCardSocket version

		ULong		VccVoltageSpec(void);				// Vcc power specs (return kPCMCIAVoltageSpecs)
		ULong		VppVoltageSpec(void);				// Vpp power specs (return kPCMCIAVoltageSpecs)

		NewtonErr	SelectVoltageLevel(TSocketPowerLevels powerLevel);


		//	New for Voyager (kCardVersionVoyager)

		// ���� Voyager only, others return a "(ULong)kError_Call_Not_Implemented"

		ULong		GetSocketASICId();					// Get socket ASIC Id (0:non Voyager ASIC)

		ULong		SocketBaseAddr(void);				// Get socket base address

		NewtonErr	SetSocketInterruptFlags(TSocketInt intType, TSocketIntFlags flags);			// Set interrupt flags

		ULong		GetVPCPins();						// Get Voyager PCPins (Direct read, no conversion)

		void		SetRdWrQueueControl(ULong control);	// Set read/write prefetch/queue control
		ULong		GetRdWrQueueControl(void);			// Get read/write prefetch/queue control
		ULong		GetRdWrQueueStatus(void);			// Get read/write prefetch/queue status

		void		SetPullupControl(ULong control);	// Set pullups control
		ULong		GetPullupControl(void);				// Get pullups control

		void		Do16BitWrite(ULong addr, ULong data);	// Write 16 bit data (data at low 16-bit)
		ULong		Do16BitRead(ULong addr);				// Do 16-bit read (data returns at low 16-bit)


	private:		//	���� for internal use only

};




//
//	Bits in Control reg		(in SetControl())
//
														// Internal HW definitions
const ULong kCardByteAccess		=	0x00000010;			// kCARD_BYTE_ACCESS
const ULong kCareAutoIncAddress	=	0x00000008;			// kCARD_AUTOINC_ADDRESS
const ULong kCardPortAccess		=	0x00000004;			// kCARD_PORT_ACCESS
const ULong kCardAssembly32		=	0x00000002;			// kCARD_ASSEMB_32

const ULong kDefaultPC32Control	=	kCareAutoIncAddress + kCardAssembly32;
const ULong kDefaultPC16Control	=	0;

//	Voyager definitions																				

const ULong kCardDynamicSwap	=	0x00000800;			// Enable dynamic swapping	(0 for us)		
const ULong kCardSwapSize		=	0x00000400;			// Enable swapping size		(0 for us)		
const ULong kCardHandshakeReady	=	0x00000080;			// Handshake with ready pin					
const ULong kCardAutoIOIs16		=	0x00000040;			// Dynamic bus size with IOIs16
const ULong kCardNoEndianConvert=	0x00000020;			// Disable endian conversion(0 for us)		

const ULong kCardDisableResetOut=	0x00020000;			// Disable reset output 		(for both memory and IO)	
const ULong kCardSWWriteProtect	=	0x00010000;			// Sottware write protect card  (for both memory and IO)	

const ULong kCardVS2Dir			=	0x00008000;			// VS2 direction (1: output)				
const ULong kCardVS1Dir			=	0x00004000;			// VS1 direction (1: output)				
const ULong kCardVS2Out			=	0x00002000;			// VS2 output data							
const ULong kCardVS1Out			=	0x00001000;			// VS1 output data							


//
//	Bits in Read/Write Queue Control reg	(in SetRdWrQueueControl() and GetRdWrQueueControl())
//

//	Voyager definitions																				

const ULong kCardWrFIFOEnable	=	0x00000010;			// Write FIFO enable
const ULong kCardWrFIFOIntCntl	=	0x00000008;			// Write FIFO threshold control interrupt on 2/4 entries (0/1)
const ULong kCardWrFIFOFlush	=	0x00000004;			// Write FIFO flush
const ULong kCardRdPrefectch	=	0x00000002;			// Read prefetch enable
const ULong kCardRdIOPrefectch	=	0x00000001;			// Read IO prefetch enable

//	Bits in Read/Write Queue Control reg	(in GetRdWrQueueStatus())

//	Voyager definitions																				

//const ULong kCardWrFIFOEmpty	=	0x00001000;			// Write FIFO empty
//const ULong kCardWrFIFOThreshld=	0x00000800;			// Write FIFO threshold met (2 or 4 entries interrupt)


//
//	Bits in PCPins reg		(in GetPCPins())
//

//	Voyager definitions

const ULong kCardReadFailure	=	0x00004000;			// Read failure
const ULong kCardWriteFailure	=	0x00002000;			// Write failure
const ULong kCardWrFIFOEmpty	=	0x00001000;			// Write FIFO empty
const ULong kCardWrFIFOThreshld	=	0x00000800;			// Write FIFO threshold met (2 or 4 entries interrupt)
const ULong kCardVS2			=	0x00000400;			// Voltage sense 2
const ULong kCardVS1			=	0x00000200;			// Voltage sense 1
const ULong kCardEjectSwitchUp	=	0x00000080;			// Eject switch state

//	New definitions	(Mem/IO are same const)

const ULong kCardWPIOIs16		=	0x00000020;			// Memory/IO: write protected/IO is 16#
const ULong kCareBVD2Spkr		=	0x00000010;			// Memory/IO: BVD2/Speaker#
const ULong kCardBVD1Stschg		=	0x00000008;			// Memory/IO: BVD1/Status changed#
const ULong kCardReadyIREQ		=	0x00000004;			// Memory/IO: Ready/IREQ#

const ULong kCardCD1			=	0x00000002;			// Card detected 1
const ULong kCardCD2			=	0x00000001;			// Card detected 2

//	Old definitions	(Mem/IO are seperated const)

const ULong kCardMemProtected	=	0x00000020;			// Memory: write protected
const ULong kCareMemBVD2		=	0x00000010;			// Memory: BVD2
const ULong kCardMemBVD1		=	0x00000008;			// Memory: BVD1
const ULong kCardMemReady		=	0x00000004;			// Memory: Ready
const ULong kCardIOis16			=	0x00000020;			// IO: IO is 16#
const ULong kCareIOSpkr			=	0x00000010;			// IO: Speaker#
const ULong kCardIOStsChg		=	0x00000008;			// IO: Status changed#
const ULong kCardIOIRQ			=	0x00000004;			// IO: IREQ#

//	CIS voltage senses

const ULong kCardCis5VOnly		=	kCardVS2+kCardVS1;	// CIS "5 V only"
const ULong kCardCis3p3Maybe5V	=	kCardVS2;			// CIS "3.3 V only" or "3.3 and 5 V"
const ULong kCardCisXpXVOnly	=	kCardVS1;			// CIS "X.X V" only
const ULong kCardCisXpX3p3Maybe5V	=	0;				// CIS "X.X and 3.3 V" or "X.X, 3.3 and 5 V"


//
//	Bits in Voyager PCPins reg	(in GetVPCPins())		����� Voyager only
//

const ULong kCardVReadFailure	=	0x00004000;			// Voyager Read failure
const ULong kCardVWriteFailure	=	0x00002000;			// Voyager Write failure
const ULong kCardVWrFIFOEmpty	=	0x00001000;			// Voyager Write FIFO empty
const ULong kCardVWrFIFOThreshld =	0x00000800;			// Voyager Write FIFO threshold met (2 or 4 entries interrupt)
const ULong kCardVReadyIREQ		=	0x00000400;			// Voyager (Memory/IO:) Ready/IREQ#
const ULong kCardVWPIOIs16		=	0x00000200;			// Voyager (Memory/IO:) write protected/IO is 16#
const ULong kCardVPCTL2			=	0x00000100;			// Voyager PCTL2 (reserved)
const ULong kCardVPCTL1			=	0x00000080;			// Voyager PCTL1 (reserved)
const ULong kCardVDREQ			=	0x00000040;			// Voyager DMA REG
const ULong kCardVVS2			=	0x00000020;			// Voyager Voltage sense 2
const ULong kCardVVS1			=	0x00000010;			// Voyager Voltage sense 1
const ULong kCardVCD2			=	0x00000008;			// Voyager Card detected 2
const ULong kCardVCD1			=	0x00000004;			// Voyager Card detected 1
const ULong kCareVBVD2Spkr		=	0x00000002;			// Voyager (Memory/IO:) BVD2/Speaker#
const ULong kCardVBVD1Stschg	=	0x00000001;			// Voyager (Memory/IO:) BVD1/Status changed#

//	Voyager CIS voltage senses

const ULong kCardVCis5VOnly		=	kCardVVS2+kCardVVS1; // Voyager CIS "5 V only"
const ULong kCardVCis3p3Maybe5V	=	kCardVVS2;			 // Voyager CIS "3.3 V only" or "3.3 and 5 V"
const ULong kCardVCisXpXVOnly	=	kCardVVS1;			 // Voyager CIS "X.X V" only
const ULong kCardVCisXpX3p3Maybe5V	=	0;				 // Voyager CIS "X.X and 3.3 V" or "X.X, 3.3 and 5 V"


//
//	Bits in Pullup Control reg	(in SetPullupControl() and GetPullupControl())
//

//	Voyager definitions																										

const ULong kCardRdyWaitPullupEn	=	0x4000;			// Enable strong pullups for Ready and Wait lines
const ULong kCardDisProtBVD1		=	0x2000;			// Disable Protection for PCM_BVD[1] input during card power off
const ULong kCardInputPullupEn		=	0x1000;			// Input Pull-Up Enable
const ULong kCardCDPullupControl1	=	0x0800;			// Card detected pullup control
const ULong kCardCDPullupControl0	=	0x0400;			// (11: weak pullup always on, 10: weak pullup except sleep)




#endif	//	hasPCMCIA

#endif	//	__CARDSOCKET_H

