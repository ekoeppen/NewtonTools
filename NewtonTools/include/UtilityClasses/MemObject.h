/*
	File:		MemObject.h

	Contains:	Interface to CMemObject

	Copyright:	� 1992, 1995 by Apple Computer, Inc.  All rights reserved.

	Derived from v5 internal.

*/

#ifndef	__MEMOBJECT_H
#define __MEMOBJECT_H

#ifndef	__USERSHAREDMEM_H
#include "UserSharedMem.h"
#endif

#ifndef	__USERPORTS_H
#include "UserPorts.h"
#endif

/*
	Class CMemObject

	Basic memory object.  A CMemObject is either Private or Shared.
	A private CMemObject contains the raw pointer and size of the block,
	which is memory owned by the task using it (usually created via malloc).

	A shared CMemObject contains a shared memory object reference to the block.

	Basic operations on a CMemObject:

		IsPrivate			return true if internal object, false otherwise

		IsShared			returns true if the memory is set to be shared,
							false otherwise

		GetId				if the object is shared, returns the shared memory
							id.  useful when you need to pass the id to an
							external task world.

		GetSize				returns the size of the object in bytes

		CopyTo				copies data to the object, you supply the ptr to the data
							to copy, the size of the data, and an optional offset.

		CopyFrom			copies data from the object, you supply a ptr to a buffer
							to copy to, along with a size and optional offset.

		Destroy				disposes of any memory associated with the memory object,
							only has an effect on internal objects

	Operations valid on Private blocks:

		Init(ULong size, Ptr buffer, Boolean makeShared = false, ULong permissions = kSMemReadOnly)

							intializes a CMemObject to the buffer supplied, you must
							also pass in the size.  if you intend to "share" this memory
							with another task, set makeShared and determine the permissions

							use kSMemReadOnly if you want the external client to only have
							read access, use kSMemReadWrite to give full read/write permission

		Init(ULong size, Boolean makeShared = false, ULong permissions = kSMemReadOnly)

							basically same as Init above, however all you need to supply
							is the size, the allocation will be done automatically


		MakeShared(ULong permissions = kSMemReadOnly)

							makes the internal object into a shared memory object.  you
							can supply the permissions.  before passing the id of the
							object to another task, you must make the object shared.

		GetBase			returns a raw pointer to the data, 0 if the object is
							external


	Operations valid on Shared blocks:

		Make(TObjectId sharedObjectId, TUMsgToken* msgToken = nil)

							given a memory object id, Make will intialize the CMemObject
							to its memory reference.  useful when you have received an id
							from the owner task and want to make a CMemObject out of it.

*/


struct MemObjectFlags
{
	unsigned int	internal:			1;		// set if internal object
	unsigned int	createdMemory:		1;		// set if memory object created the memory, valid only if internal set
	unsigned int	shared:				1;		// set if memory object is shared
	unsigned int	useToken:			1;		// set if memory object should use TUMsgToken in copies
	unsigned int	unused1:			1;
	unsigned int	unused2:			1;
	unsigned int	unused3:			1;
	unsigned int	unused4:			1;
};


class CMemObject : public SingleObject
{
	public:
							CMemObject();
							~CMemObject();

		NewtonErr			Init(ULong size, void* buffer, Boolean makeShared = false, ULong permissions = kSMemReadOnly);
		NewtonErr			Init(ULong size, Boolean makeShared = false, ULong permissions = kSMemReadOnly);
		long				Make(TObjectId sharedObjectId, TUMsgToken* msgToken = nil);
		NewtonErr			MakeShared(ULong permissions = kSMemReadOnly);
		void				Destroy(void);

		Boolean				IsInternal(void)			{ return fFlags.internal; }
		Boolean				IsShared(void)				{ return fFlags.shared; }
		TObjectId			GetId(void);				// returns id if type is external, 0 otherwise

		NewtonErr			CopyTo(void* buffer, ULong size, ULong offset = 0);
		NewtonErr			CopyFrom(ULong* returnSize, void* buffer, ULong size, ULong offset = 0);
		ULong				GetSize(void)				{ return fSize; }

		// internal only calls�
		void*				GetBase(void);			// returns fBuffer if type is internal

	private:

		MemObjectFlags		fFlags;					// object flags
		TUSharedMem			fSharedMemoryObject;	// shared memory object if type external
		TUMsgToken			fSharedMemoryToken;		// validation token for shared memory object
		ULong				fSize;					// size if internal, cache of size if type external
		void*				fBuffer;				// ptr to memory if type internal
};



#endif __MEMOBJECT_H
