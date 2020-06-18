/*
	File:		ListIterator.h

	Contains:	Interface to the CListIterator class

	Copyright:	� 1992, 1994 by Apple Computer, Inc.  All rights reserved.

	Derived from v5 internal.

*/

#ifndef __LISTITERATOR_H
#define __LISTITERATOR_H

#ifndef __ARRAYITERATOR_H
#include "ArrayIterator.h"
#endif


//--------------------------------------------------------------------------------
//		CListIterator
//--------------------------------------------------------------------------------
class CListIterator : public CArrayIterator
{

public:

				CListIterator();
				CListIterator(CDynamicArray* itsList);
				CListIterator(CDynamicArray* itsList, Boolean itsForward);
				CListIterator(CDynamicArray* itsList, ArrayIndex itsLowBound,
					ArrayIndex itsHighBound, Boolean itsForward);

	void*		CurrentItem(void);
	void*		FirstItem(void);
	void*		NextItem(void);

}; // CListIterator


#endif	/*	__LISTITERATOR_H	*/
