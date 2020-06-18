/*
	File:		ItemComparer.h

	Contains:	Interface to the CItemComparer class

	Copyright:	� 1992-1995 by Apple Computer, Inc.  All rights reserved.

	Derived from v11 internal.

*/

#ifndef __ITEMCOMPARER_H
#define __ITEMCOMPARER_H

#ifndef __ITEMTESTER_H
#include "ItemTester.h"
#endif

//	NOTE
//	CItemComparer::TestItem should return
//		kItemLessThanCriteria if (fItem < criteria)
//		kItemGreaterThanCriteria for (fItem > criteria)
//		kItemEqualCriteria for (fItem == criteria)
//	this will keep the CSortedList sorted in ascending order

//	Change the value of itsForward in CArrayIterator::CArrayIterator
//	to FALSE to view a list in descending order.


//--------------------------------------------------------------------------------
//		CItemComparer
//--------------------------------------------------------------------------------
class CItemComparer : public CItemTester
{

public:

							CItemComparer();
							CItemComparer(const void* testItem, const void* keyValue = nil);
			void			SetTestItem(const void* testItem);
			void			SetKeyValue(const void* keyValue);

	// functions that wrap inline methods so they can be used by external callers
			void 			FXUSetTestItem(const void* testItem);
			void 			FXUSetKeyValue(const void* keyValue);

	virtual CompareResult	TestItem(const void* criteria) const;

protected:

	const void*		fItem;
	const void*		fKey;

private:

}; // CItemComparer

//--------------------------------------------------------------------------------
//		CItemComparer inlines
//--------------------------------------------------------------------------------

inline void CItemComparer::SetTestItem(const void* testItem)
	{ fItem = testItem; }

inline void CItemComparer::SetKeyValue(const void* keyValue)
	{ fKey = keyValue; }

#endif	/*	__ITEMCOMPARER_H	*/
