/*
	File:		ItemTester.h

	Contains:	Interface to the CItemTester class

	Copyright:	� 1992, 1994 by Apple Computer, Inc.  All rights reserved.

	Derived from v6 internal.

*/

#ifndef __ITEMTESTER_H
#define __ITEMTESTER_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

enum CompareResult {
	kItemLessThanCriteria = -1,
	kItemEqualCriteria = 0,
	kItemGreaterThanCriteria = 1
};

//--------------------------------------------------------------------------------
//		CItemTester
//--------------------------------------------------------------------------------
class CItemTester : public SingleObject
{

public:

	virtual CompareResult TestItem(const void* testItem) const;

}; // CItemTester


#endif	/*	__ITEMTESTER_H	*/
