/*
	File:		DynamicArray.h

	Contains:	Interface to the CDynamicArray class

	Copyright:	� 1992-1995 by Apple Computer, Inc.  All rights reserved.

	Derived from v18 internal.

*/

#ifndef __DYNAMICARRAY_H
#define __DYNAMICARRAY_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#if defined(forDocker)
#define CArrayIterator CDockerIterator
#endif

//--------------------------------------------------------------------------------
//		Forward and external class declarations
//--------------------------------------------------------------------------------

class CArrayIterator;
	// CArrayIterator knows how to traverse a CDynamicArray.
	// In particular, it will bend indices to account for on-the-fly
	// element insertion and deletion.


//--------------------------------------------------------------------------------
//		CDynamicArray
//--------------------------------------------------------------------------------

class CDynamicArray : public SingleObject
{

public:

	enum Parameters {
		kDefaultElementSize = 4,
		kDefaultChunkSize = 4
	};

						CDynamicArray();
						CDynamicArray(Size elementSize, ArrayIndex chunkSize);

						~CDynamicArray();

	// array manipulation primitives

			ArrayIndex	GetArraySize(void);
			NewtonErr	SetArraySize(ArrayIndex theSize);
			NewtonErr	SetElementCount(ArrayIndex theSize);		// like SetArraySize, but sets logical size, too

			void*		ElementPtrAt(ArrayIndex index);
			void*		SafeElementPtrAt(ArrayIndex index);
			NewtonErr	GetElementsAt(ArrayIndex index, void* elemPtr, ArrayIndex count);
			NewtonErr	InsertElementsBefore(ArrayIndex startHere, void* elemPtr, ArrayIndex count);
			NewtonErr	ReplaceElementsAt(ArrayIndex index, void* elemPtr, ArrayIndex count);
			NewtonErr	RemoveElementsAt(ArrayIndex index, ArrayIndex count);
			NewtonErr	RemoveAll(void);

	// miscellaneous functions

			Boolean		IsEmpty(void);

			NewtonErr	Merge(CDynamicArray* aDynamicArray);

	// don't call this unless you know what you are doing.  Just say NO!

			void		NukeIterator(void);		// Dangerous

protected:

		Size			ComputeByteCount(ArrayIndex count);

		ArrayIndex		fSize;			// logical size of array

private:

		friend class CArrayIterator;

		Size			fElementSize;	// size of a single element
		ArrayIndex		fChunkSize;		// grow/shrink array by this many elements
		ArrayIndex		fAllocatedSize;	// physical size of array
		void*			fArrayBlock;	// element storage
		CArrayIterator*	fIterator;		// linked list of iterators active on this array

}; // CDynamicArray


//--------------------------------------------------------------------------------
//		inline functions
//--------------------------------------------------------------------------------

inline ArrayIndex CDynamicArray::GetArraySize()
	{ return fSize; }

inline Boolean CDynamicArray::IsEmpty()
	{ return (fSize == 0); }

inline void* CDynamicArray::ElementPtrAt(ArrayIndex index)
	{ return (void*)((long)fArrayBlock + (fElementSize * index)); }

inline Size CDynamicArray::ComputeByteCount(ArrayIndex count)
	{ return (fElementSize * count); }

inline NewtonErr CDynamicArray::RemoveAll()
	{ return RemoveElementsAt(0, fSize); }

inline void CDynamicArray::NukeIterator()
	{ fIterator = nil; }

#endif	/*	__DYNAMICARRAY_H	*/
