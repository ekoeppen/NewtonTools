/*
	File:		HammerConfigBits.h

	Contains:	definitions of bits for Hammer�s Config and Tests menus

	Copyright:	� 1995 by Apple Computer, Inc., all rights reserved.

	Derived from v1 internal.

*/

#ifndef __HAMMERCONFIGBITS_H
#define __HAMMERCONFIGBITS_H

#ifndef __CONFIGGLOBAL_H
#include "ConfigGlobal.h"
#endif

#ifdef forProtected
	ULong GetHammerConfigBits(void);
#endif

#ifdef forPrivate
	extern ULong gNewtConfig;

	const ULong kCrippleMemory			= 0x00000001;		// bit 0
	const ULong kEnableListener			= 0x00000002;		// bit 1
	const ULong kDisableSCP				= 0x00000004;		// bit 2
	const ULong kConfigBit3				= 0x00000008;		// bit 3
	const ULong kStopOnAborts			= 0x00000010;		// bit 4
	const ULong kStopOnThrows			= 0x00000020;		// bit 5
	const ULong kHeapChecking			= 0x00000040;		// bit 6
	const ULong kStackThrashing			= 0x00000080;		// bit 7
	const ULong kOSProfiling			= 0x00000100;		// bit 8
	const ULong kDefaultStdioOn			= 0x00000200;		// bit 9
	const ULong kDiagnostics			= 0x00000400;		// bit 10
	const ULong kConfigBit11			= 0x00000800;		// bit 11
	const ULong kLCDContrastAdjust		= 0x00001000;		// bit 12
	const ULong kDontPauseCPU			= 0x00002000;		// bit 13
	const ULong kFakeBatteryLevel		= 0x00004000;		// bit 14
	const ULong kEnableStdout			= 0x00008000;		// bit 15
	const ULong kEnablePackageSymbols	= 0x00010000;		// bit 16
	const ULong kEnablePCSpy			= 0x00020000;		// bit 17
	const ULong kEraseInternalStore		= 0x00040000;		// bit 18
	const ULong kConfigBit19			= 0x00080000;		// bit 19
#endif

#ifdef forProtected
	const ULong kLicenseeConfig0		= 0x00100000;		// bit 20 -- reserved for licensees
	const ULong kLicenseeConfig1		= 0x00200000;		// bit 21 -- reserved for licensees
	const ULong kLicenseeConfig2		= 0x00400000;		// bit 22 -- reserved for licensees
	const ULong kLicenseeConfig3		= 0x00800000;		// bit 23 -- reserved for licensees
#endif

#ifdef forPrivate
	const ULong kConfigBit24			= 0x01000000;		// bit 24
	const ULong kConfigBit25			= 0x02000000;		// bit 25
	const ULong kConfigBit26			= 0x04000000;		// bit 26
	const ULong kConfigBit27			= 0x08000000;		// bit 27
	const ULong kConfigBit28			= 0x10000000;		// bit 28
	const ULong kConfigBit29			= 0x20000000;		// bit 29
	const ULong kConfigBit30			= 0x40000000;		// bit 30
	const ULong kConfigBit31			= 0x80000000;		// bit 31
#endif


#ifdef forProtected
	ULong GetHammerTestBits(void);
#endif

#ifdef forPrivate
	extern ULong gNewtTests;

	const ULong kTestNetwork			= 0x00000001;		// bit 0
	const ULong kTestCommunications		= 0x00000002;		// bit 1
	const ULong kTestOS600				= 0x00000004;		// bit 2
	const ULong kTestNewtHardware		= 0x00000008;		// bit 3
	const ULong kTestPCMCIA				= 0x00000010;		// bit 4
	const ULong kTestTestUtilities		= 0x00000020;		// bit 5
	const ULong kTestBlackBird			= 0x00000040;		// bit 6
	const ULong kTestFlash				= 0x00000080;		// bit 7
	const ULong kTestRomDomainManager	= 0x00000100;		// bit 8
	const ULong kTestPackageManager		= 0x00000200;		// bit 9
	const ULong kTestSound				= 0x00000400;		// bit 10
	const ULong kTestAgent				= 0x00000800;		// bit 11
	const ULong kAvailDaemon			= 0x00001000;		// bit 12
	const ULong kTestHAL				= 0x00002000;		// bit 13
	const ULong kTestUtilityClasses		= 0x00004000;		// bit 14
	const ULong kTestBit15				= 0x00008000;		// bit 15
	const ULong kTestBit16				= 0x00010000;		// bit 16
	const ULong kTestBit17				= 0x00020000;		// bit 17
	const ULong kTestBit18				= 0x00040000;		// bit 18
	const ULong kTestBit19				= 0x00080000;		// bit 19
#endif

#ifdef forProtected
	const ULong kLicenseeTest0			= 0x00100000;		// bit 20 -- reserved for licensees
	const ULong kLicenseeTest1			= 0x00200000;		// bit 21 -- reserved for licensees
	const ULong kLicenseeTest2			= 0x00400000;		// bit 22 -- reserved for licensees
	const ULong kLicenseeTest3			= 0x00800000;		// bit 23 -- reserved for licensees
#endif

#ifdef forPrivate
	const ULong kTestBit24				= 0x01000000;		// bit 24
	const ULong kTestBit25				= 0x02000000;		// bit 25
	const ULong kTestBit26				= 0x04000000;		// bit 26
	const ULong kTestBit27				= 0x08000000;		// bit 27
	const ULong kTestBit28				= 0x10000000;		// bit 28
	const ULong kTestBit29				= 0x20000000;		// bit 29
	const ULong kTestBit30				= 0x40000000;		// bit 30
	const ULong kTestBit31				= 0x80000000;		// bit 31
#endif

#endif  /* __HAMMERCONFIGBITS_H */
