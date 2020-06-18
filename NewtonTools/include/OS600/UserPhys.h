/*
	File:		UserPhys.h

	Copyright:	� 1993-1994 by Apple Computer, Inc., all rights reserved.

	Derived from v7 internal.

*/

#ifndef	__USERPHYS_H
#define __USERPHYS_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef	__SHAREDTYPES_H
#include "sharedTypes.h"
#endif //__SHAREDTYPES_H

#ifndef	__USEROBJECTS_H
#include "UserObjects.h"
#endif	//__USEROBJECTS_H

#ifndef __USERPORTS_h
#include "UserPorts.h"
#endif

typedef enum {kMakeRangeInvalid, kMakeRangeInaccessible, kMakeRangeAccessible} EPhysChangeType;

class TUPhys : public TUObject {
	public:
					TUPhys(TObjectId id = 0) : TUObject(id) {};
		void		operator=(TObjectId id) { CopyObject(id); }
		void		operator=(const TUPhys& copy) { CopyObject(copy); }
		long		Init(PAddr base, ULong size, Boolean readOnly=false, Boolean cache=true);

		// change any mappings associated with this phys
		long		Invalidate();			// to invalid
		long		MakeInaccessible();		// to inaccessible
		long		MakeAccessible();		// to accessible

		// change the mapping associated with the provided virtual address of this phys.
		// this routine is not for the faint of heart.  It cannot cause a page allocation
		// so if the virtual address and range don't match the pagetable entries exactly it
		// will return an error.  In other words the specified range better match exactly a
		// previously mapped physical range in size and base.
		long		ChangeVirtualMapping(VAddr va, ULong vsize, EPhysChangeType access);

		// mode info
		long		ReadOnly(Boolean& ro);

		long		Size(ULong& sz);			// the size of this phys
		long		Align(ULong& al);			// the alignment of this phys
		long		Base(PAddr& paddr);			// the physical address of the base of this phys
};

#endif __USERPHYS_H