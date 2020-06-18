/*
	File:		SingleQ.h

	Contains:	Support for singly linked lists.

	Copyright:	� 1993 by Apple Computer, Inc., all rights reserved.

	Derived from original internal (no number).

*/

#ifndef		__SINGLEQ_H
#define		__SINGLEQ_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

class TSingleQItem
{
	public:
		void	Init();

		TSingleQItem*	fLink;
};


//
// this is the container class for TSingleQItems, you specify the
// offset into the Class that has the TSingleQItem within it
// so we can return the Outer Level class item, not the
// address of the TSingleQItem to the caller. 
//
class TSingleQContainer
{
	public:
				TSingleQContainer();
				TSingleQContainer(ULong offsetToSingleQItem);
		void	Init(ULong offsetToSingleQItem);

		void	Add(void* item);
		void*	Remove();
		void*	Peek();
		void*	GetNext(void* item);

	private:
		TSingleQItem*	fHead;
		ULong			fOffsetToSingleQItem;
};

#endif
