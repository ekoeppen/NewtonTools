/*
	File:		List.h

	Contains:	Interface to the CList class

	Copyright:	� 1992-1995 by Apple Computer, Inc.  All rights reserved.

	Derived from v14 internal.

*/

#ifndef __LIST_H
#define __LIST_H

#ifndef __DYNAMICARRAY_H
#include "DynamicArray.h"
#endif

class CItemTester;

//-----------------------------------------------------------------------
//		CList
//-----------------------------------------------------------------------
class CList : public CDynamicArray
{
public:

	static CList* Make();
	static CList* Make(ArrayIndex size);

				CList();
				~CList();

	// get

	void*		At(ArrayIndex index);
	void*		First(void);
	void*		Last(void);

	// insertion

	NewtonErr	Insert(void* item);
	Boolean		InsertUnique(void* item);
	NewtonErr	InsertBefore(ArrayIndex index, void* item);
	NewtonErr	InsertAt(ArrayIndex index, void* item);
	NewtonErr	InsertFirst(void* item);
	NewtonErr	InsertLast(void* item);

	// removal

	NewtonErr	Remove(void* item);
	NewtonErr	RemoveAt(ArrayIndex index);
	NewtonErr	RemoveFirst(void);
	NewtonErr	RemoveLast(void);

	// replacement

	NewtonErr	Replace(void* oldItem, void* newItem);
	NewtonErr	ReplaceAt(ArrayIndex index, void* newItem);
	NewtonErr	ReplaceFirst(void* newItem);
	NewtonErr	ReplaceLast(void* newItem);

	// indexing

	ArrayIndex	GetIdentityIndex(void* item);
	ArrayIndex	GetEqualityIndex(void* item);

	// searching

	void*		Search(CItemTester* test, ArrayIndex& index);
	Boolean	 	Contains(void* item) { return GetIdentityIndex(item) != kEmptyIndex;}

	// old names from TList
	long Count()				{ return fSize; };
	Boolean Empty()				{ return (fSize == 0);};
	Boolean AddUnique(void* add) { return InsertUnique(add);}
	ArrayIndex Index(void* item) { return GetIdentityIndex(item);}
	void* Ith(ArrayIndex index) { return At(index);}

}; // CList


//-----------------------------------------------------------------------
//		CList inlines
//-----------------------------------------------------------------------

inline void* CList::First(void)
	{ return At(0); }

inline void* CList::Last(void)
	{ return At(fSize - 1); }

inline NewtonErr CList::Insert(void* item)
	{ return InsertAt(fSize, item); }

inline NewtonErr CList::InsertBefore(ArrayIndex index, void* item)
	{ return InsertAt(index, item); }

inline NewtonErr CList::InsertFirst(void* item)
	{ return InsertAt(0, item); }

inline NewtonErr CList::InsertLast(void* item)
	{ return InsertAt(fSize, item); }

inline NewtonErr CList::RemoveAt(ArrayIndex index)
	{ return RemoveElementsAt(index, 1); }

inline NewtonErr CList::RemoveFirst()
	{ return RemoveElementsAt(0, 1); }

inline NewtonErr CList::RemoveLast()
	{ return RemoveElementsAt(fSize - 1, 1); }

inline NewtonErr CList::ReplaceFirst(void* newItem)
	{ return ReplaceAt(0, newItem); }

inline NewtonErr CList::ReplaceLast(void* newItem)
	{ return ReplaceAt(fSize - 1, newItem); }

inline ArrayIndex CList::GetEqualityIndex(void* item)
	{ return GetIdentityIndex(item); }


#endif	/*	__LIST_H	*/
