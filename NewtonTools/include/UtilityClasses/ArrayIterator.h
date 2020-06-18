/*
	File:		ArrayIterator.h

	Contains:	Interface to the CArrayIterator class

	Copyright:	� 1992-1994, 1996 by Apple Computer, Inc.  All rights reserved.

	Derived from v14 internal.

*/

#ifndef __ARRAYITERATOR_H
#define __ARRAYITERATOR_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

// when building with the CW IDE, these are already defined in MacApp headers
#ifndef qMacApp
enum IterateDirection { kIterateBackward = 0, kIterateForward = 1 };
#endif

#if defined(forDocker)
#define CArrayIterator CDockerIterator
#endif

class CList;
class CSortedList;
class CDynamicArray;


//--------------------------------------------------------------------------------
//		CArrayIterator
//--------------------------------------------------------------------------------
class CArrayIterator : public SingleObject
{

public:

					CArrayIterator();
					CArrayIterator(CDynamicArray* itsDynamicArray);
					CArrayIterator(CDynamicArray* itsDynamicArray,
						Boolean itsForward);
					CArrayIterator(CDynamicArray* itsDynamicArray,
						ArrayIndex itsLowBound, ArrayIndex itsHighBound,
						Boolean itsForward);

					~CArrayIterator();

		void		Init(void);
		void		Init(CDynamicArray* itsDynamicArray, ArrayIndex itsLowBound,
						ArrayIndex itsHighBound, Boolean itsForward);

		void		InitBounds(ArrayIndex itsLowBound, ArrayIndex itsHighBound,
						Boolean itsForward);
		void		Reset(void);
		void		ResetBounds(Boolean goForward = true);

		void		SwitchArray(CDynamicArray* newArray, Boolean itsForward = kIterateForward);

		ArrayIndex	FirstIndex(void);
		ArrayIndex	NextIndex(void);
		ArrayIndex	CurrentIndex(void);

		void		RemoveElementsAt(ArrayIndex theIndex, ArrayIndex theCount);
		void		InsertElementsBefore(ArrayIndex theIndex, ArrayIndex theCount);
		void		DeleteArray(void);

		Boolean		More(void);

protected:

		void		Advance(void);

		CDynamicArray*		fDynamicArray;			// the associated dynamic array

		ArrayIndex			fCurrentIndex;			// current index of this iteration
		ArrayIndex			fLowBound;				// lower bound of iteration in progress
		ArrayIndex			fHighBound;				// upper bound of iteration in progress
		Boolean				fIterateForward;		// if iteration is forward or backward

private:

friend class CDynamicArray;
friend class CList;
friend class CSortedList;

		CArrayIterator*		AppendToList(CArrayIterator* toList);
		CArrayIterator*		RemoveFromList(void);

		CArrayIterator*		fPreviousLink;			// link to previous iterator
		CArrayIterator*		fNextLink;				// link to next iterator

}; // CArrayIterator


#endif	/*	__ARRAYITERATOR_H	*/
