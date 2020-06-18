/*
	File:		CardPower.h

	Copyright:	� 1993-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v1 (4/25/96) internal.

*/

#ifndef __CARDPOWER_H
#define __CARDPOWER_H

#ifndef __LONGTIME_H
#include "LongTime.h"
#endif

#ifndef __NEWTON_H
#include "Newton.h"
#endif


/*	----------------------------------------------------------------
**
**	+5v management
**
*/
Boolean VccOn(int socket, Boolean fail_if_not_on=false);
void VccOff(int socket);
void VccOff(int socket, TTimeout delay);

/*	----------------------------------------------------------------
**
**	+12v management
**
*/
Boolean VppOn(int socket, Boolean fail_if_not_on=false);
void VppOff(int socket);
void VppOff(int socket, TTimeout delay);


/*	----------------------------------------------------------------
**
**	internal +12v management
**
*/
void InternalVppOn();
void InternalVppOff();


/*	----------------------------------------------------------------
**
**	Internal (Not for developers)
**
*/
NewtonErr InitVppManager();
NewtonErr RestoreVppState();						// also restores Vcc state
NewtonErr RestoreCardPower(ULong socket);			// Rename from RestoreVppState
Boolean VccIdleOff(Boolean force_off=false);
Boolean VppIdleOff(Boolean force_off=false);
Boolean InternalVppIdleOff(Boolean force_off=false);
Boolean VccIdleOff(ULong socket);
Boolean VppIdleOff(ULong socket);

#define	kResetTimeOut	(~4)						// 1318976 To reset Vcc and Vpp internal state

typedef void (*VccOffNotifyFuncPtr)(void* refcon);

void RegisterVccOffNotify(int socket, VccOffNotifyFuncPtr func, void* refCon);
void UnregisterVccOffNotify(int socket);
Boolean IsVccOffNotifyRegistered(int socket);


TTimeout GetVccTimeout(int socket);
void SetVccTimeout(int socket, TTimeout timeout); //0==> default


#endif /*__VPP_H*/
