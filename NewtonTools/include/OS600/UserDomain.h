/*
	File:		UserDomain.h

	Copyright:	� 1992, 1994 by Apple Computer, Inc., all rights reserved.

	Derived from v6 internal.

*/

#ifndef	__USERDOMAIN_H
#define __USERDOMAIN_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif	//__NEWTON_H

#ifndef	__SHAREDTYPES_H
#include "sharedTypes.h"
#endif //__SHAREDTYPES_H

#ifndef	__USEROBJECTS_H
#include "UserObjects.h"
#endif	//__USEROBJECTS_H

#include "UserMonitor.h"

class TUDomain: public TUObject
{
	public:
					TUDomain() : TUObject((TObjectId) 0) {};
					TUDomain(TObjectId id) : TUObject(id) {};
		void		operator=(TObjectId id) { CopyObject(id); }
		void		operator=(const TUDomain& copy) { CopyObject(copy); }

		// initalization of a domain
		long		Init(TObjectId monitor, VAddr base, ULong size);
		long		SetFaultMonitor(TObjectId monitor);

		long		Base(VAddr& base);
		long		Size(ULong& size);
};

#endif __USERDOMAIN__