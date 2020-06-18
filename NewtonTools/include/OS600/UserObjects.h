/*
	File:		UserObjects.h

	Copyright:	� 1992-1994 by Apple Computer, Inc., all rights reserved.

	Derived from v14 internal.

*/

#ifndef	__USEROBJECTS_H
#define __USEROBJECTS_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef	__KERNELTYPES_H
#include "KernelTypes.h"
#endif


#ifndef	__SHAREDTYPES_H
#include "SharedTypes.h"
#endif


class 	TUMonitor;
struct 	ObjectMessage;


// We have to explicitly declare this here, before we can tell TUObject that it's a friend
extern "C" void MonitorExitAction(TObjectId monitorId, ULong action);

// user objects are derived from this class, this is the interface to
// the object manager.
// All objects consist fundamentally of an object Id.  This Id is given
// to the kernel on all calls related to that Id.  If you want to pass
// a given object around, the correct thing to do is to ask for the Id
// by assigning this object to something of the type TObjectId.
class TUObject : public SingleObject
{
	public:
					TUObject(TObjectId id = 0)	{ fObjectCreatedByUs = false; fId = id; }
					TUObject(TUObject& copy)	{ fObjectCreatedByUs = false; fId = copy.fId; }
					operator	TObjectId()		{ return fId; }
		void		DestroyObject();
					~TUObject();

		void		CopyObject(const TObjectId id);
		void		CopyObject(const TUObject& copy)	{ CopyObject(copy.fId); }
		long		MakeObject(ObjectTypes objectType, ObjectMessage* msg, ULong msgSize);
		void		DenyOwnership()				{ fObjectCreatedByUs = false; }

		Boolean		IsExtPage()					{ return (fId & kTypeMask) == kExtPhysType; }

		TObjectId	fId;

	protected:
		friend		void MonitorExitAction(TObjectId monitorId, ULong action);
		friend		class TUMonitor;
		Boolean		fObjectCreatedByUs;
};


extern long	TaskGiveObject(TObjectId id, TObjectId assignToTaskId);
extern long	TaskAcceptObject(TObjectId id);

#endif
