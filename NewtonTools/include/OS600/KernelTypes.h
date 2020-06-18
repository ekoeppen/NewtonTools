/*
	File:		KernelTypes.h

	Copyright:	� 1992-1994 by Apple Computer, Inc., all rights reserved.

	Derived from v13 internal.

*/

#ifndef	__KERNELTYPES_H
#define __KERNELTYPES_H

#ifndef __CONFIGOS600_H
#include "ConfigOS600.h"
#endif

typedef enum {
	kNoAccess 		= 0,
	kSuperReadWrite = 1,
	kReadOnly 		= 2,
	kReadWrite 		= 3
} Perm;

// special addresses

#define	kIllegalVAddr	(4095L * MByte)			// the last section is "illegal"
#define	kIllegalPAddr	(4095L * MByte)			// the last section is "illegal"

// task types
typedef long	Priority;

enum ObjectTypes
{
	kObjectPort,
	kObjectTask,
	kObjectEnvironment,
	kObjectDomain,
	kObjectSemList,
	kObjectSemGroup,
	kObjectSharedMem,
	kObjectSharedMemMsg,
	kObjectMonitor,
	kObjectPhys
};

enum SemFlags
{
	kWaitOnBlock,				// ok if we need to block
	kNoWaitOnBlock				// don't wait if need to block
};

#define MAKESEMLISTITEM(semNum, operation)	(((semNum) << 16) + ((operation) & 0xffff))

enum GetPortTypes
{
	kGetObjectPort = 0,
	kGetNullPort,
	kGetNameServerPort
};


#endif
