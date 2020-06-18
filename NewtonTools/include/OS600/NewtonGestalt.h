/*
	File:		NewtonGestalt.h

	Copyright:	� 1993-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v7 internal.

*/

#ifndef __NEWTONGESTALT_H
#define __NEWTONGESTALT_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#if !(defined(FRAM) || defined(forNTK) || defined(forDocker))
#ifndef __USERPORTS_H
#include "UserPorts.h"
#endif

typedef ULong GestaltSelector;
#endif	/* FRAM */


/*	----------------------------------------------------------------------------------
**
**		Global gestalt selectors...
**
*/

#define kGestalt_Base					0x01000001
#define kGestalt_Version				(kGestalt_Base + 1)
#define kGestalt_SystemInfo				(kGestalt_Base + 2)
#define kGestalt_RebootInfo				(kGestalt_Base + 3)
#define kGestalt_NewtonScriptVersion	(kGestalt_Base + 4)
#define	kGestalt_PatchInfo				(kGestalt_Base + 5)
#define	kGestalt_SoundInfo				(kGestalt_Base + 6)
#define	kGestalt_PCMCIAInfo				(kGestalt_Base + 7)
#define kGestalt_RexInfo				(kGestalt_Base + 8)

#define kGestalt_Extended_Base			0x02000001
#define kGestalt_SoftContrast			(kGestalt_Extended_Base + 2)
#define kGestalt_Ext_KMEAsicRegs	 	(kGestalt_Extended_Base + 3)
#define kGestalt_Ext_KMEAsicAddr	 	(kGestalt_Extended_Base + 4)
#define kGestalt_Ext_KMEPlatform	 	(kGestalt_Extended_Base + 5)
#define kGestalt_Ext_Backlight		 	(kGestalt_Extended_Base + 6)
#define kGestalt_Ext_ParaGraphRecognizer	(kGestalt_Extended_Base + 7)
#define kGestalt_Ext_VolumeInfo			(kGestalt_Extended_Base + 8)
#define kGestalt_Ext_SoundHWInfo		(kGestalt_Extended_Base + 9)


/*	----------------------------------------------------------------------------------
**
**		Global gestalt parameters...
**
*/

/*	TGestaltSystemInfo */

#define kGestalt_Manufacturer_Apple			0x01000000
#define kGestalt_Manufacturer_Sharp 		0x10000100

#define kGestalt_MachineType_MessagePad		0x10001000
#define kGestalt_MachineType_Lindy			0x00726377
#define kGestalt_MachineType_Bic			0x10002000


#if !(defined(FRAM) || defined(forNTK) || defined(forDocker))

extern ULong gHardwareType;

/*	----------------------------------------------------------------------------------
**
**		Gestalt parameter blocks...
**
*/

class TGestaltVersion
{
	public:
		ULong		fVersion;
};

class TGestaltSystemInfo
{
	public:
		ULong		fManufacturer;
		ULong		fMachineType;
		ULong		fROMVersion;
		ULong		fROMStage;
		ULong		fRAMSize;
		ULong		fScreenWidth;
		ULong		fScreenHeight;
		ULong		fPatchVersion;
		Point		fScreenResolution;
		ULong		fScreenDepth;
		Fixed		fTabletResX;
		Fixed		fTabletResY;
		ULong		fCpuType;
		Fixed		fCpuSpeed;
};

class TGestaltRebootInfo
{
	public:
		ULong		fRebootReason;
		ULong		fRebootCount;
};

class TGestaltNewtonScriptVersion
{
	public:
		ULong		fVersion;
};


class TGestaltPCMCIAInfo								// kGestalt_PCMCIAInfo
{
	public:
		ULong		fServicesAvailibility;				// PCMCIA services abvailibity
		ULong		fReserverd0;						// Reserved (0)
		ULong		fReserverd1;						// Reserved (0)
		ULong		fReserverd2;						// Reserved (0)
		ULong		fReserverd3;						// Reserved (0)
		ULong		fReserverd4;						// Reserved (0)
		ULong		fReserverd5;						// Reserved (0)
		ULong		fReserverd6;						// Reserved (0)
};

enum kPCMCIAServicesAvailibility						// TGestaltPCMCIAInfo.fServicesAvailibility
{														// (Undefind bits are 0)
	kPCMCIACISParserAvail		=	0x00000001,			// CIS parser available
	kPCMCIACISIteratorAvailable	=	0x00000002,			// CIS iterator available
	kPCMCIAExtendedTCardPCMCIA	=	0x00000004,			// Extended TCardPCMCIA class
	kPCMCIAExtendedTCardSocket	=	0x00000008			// Extended TCardSocket class
};


class TGestaltSoftContrast
{
	public:
		Boolean				fHasSoftContrast;			// true = has software contrast control
														// false = hardware contrast control
		long				fMinContrast;
		long				fMaxContrast;
};


class TGestaltBacklight
{
	public:
		Boolean				fHasBacklight;				// true = has backlight
														// false = no backlight
};


class TGestaltParaGraphRecognizer
{
	public:
		Boolean		fHasParaGraphRecognizer;			// true = has recognizer
														// false = no recognizer
};


class TGestaltPatchInfo
{
	public:

	ULong			fTotalPatchPageCount;
	struct
	{
		ULong		fPatchCheckSum;
		ULong		fPatchVersion;
		ULong		fPatchPageCount;
		ULong		fPatchFirstPageIndex;
	} fPatch[5];
};

class TGestaltRexInfo
{
	public:

struct
	{
		ULong	signatureA;
		ULong	signatureB;
		ULong	checksum;
		ULong	headerVersion;
		ULong	manufacturer;
		ULong	version;
		ULong	length;
		ULong	id;
		ULong	start;
		ULong	count;
	} fRex[4];
};

/*	----------------------------------------------------------------------------------
**
**		User object to return Gestalt parameter blocks...
**
*/

class TUGestalt
{
	public:
						TUGestalt();
		NewtonErr			Gestalt(GestaltSelector selector, void* paramBlock, ULong paramSize);
		NewtonErr			Gestalt(GestaltSelector selector, void* paramBlock, ULong* paramSize);
		NewtonErr			RegisterGestalt(GestaltSelector selector, void* paramBlock, ULong paramSize);
		NewtonErr			ReplaceGestalt(GestaltSelector selector, void* paramBlock, ULong paramSize);

	private:
		TUPort			fGestaltPort;
};


#endif	/* FRAM */
#endif	/* __NEWTONGESTALT_H */
