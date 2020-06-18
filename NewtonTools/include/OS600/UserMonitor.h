/*
	File:		UserMonitor.h

	Contains:	User routines for creating and accessing monitors.

	Copyright:	� 1992-1994 by Apple Computer, Inc., all rights reserved.

	Derived from v8 internal.

*/

#ifndef	__USERMONITOR_H
#define __USERMONITOR_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif	//__NEWTON_H

#ifndef	__USEROBJECTS_H
#include "UserObjects.h"
#endif	//__USEROBJECTS_H

#include "UserSharedMem.h"
#include "UserGlobals.h"
#include "UserTasks.h"


////
//
// Monitors

class TUMonitor : public TUObject
{
	public:
					TUMonitor(TObjectId id = 0);
					~TUMonitor();
		void		operator=(TObjectId id) { CopyObject(id); }
		void		operator=(const TUMonitor& copy) { CopyObject(copy); }
		void		DestroyObject();

		void		CopyObject(TObjectId id);
		void		CopyObject(const TUMonitor& copy);

		void		SetDestroyKernelObject(Boolean newStatus)
						{ fObjectCreatedByUs = newStatus; }

		long		Init(MonitorProcPtr monitorProc, ULong stackSize, void* monitorObject = nil, TObjectId environmentId = 0, Boolean faultMonitor = false, ULong name = 'MNTR', Boolean rebootProtected = false);

		long		InvokeRoutine(long selector, void* userObject)
					{ return MonitorDispatchSWI(fId, selector, userObject); }
	private:
};


#endif /* __NEWTTYPES_H */
