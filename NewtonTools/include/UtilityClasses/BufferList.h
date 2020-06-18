/*
	File:		BufferList.h

	Contains:	Interface to the CBufferList class

	Copyright:	� 1992-1995 by Apple Computer, Inc.  All rights reserved.

	NOTE:  This external file was created from version <10> of the internal file 

*/


#ifndef __BUFFERLIST_H
#define __BUFFERLIST_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

class CMinBuffer;
class CBuffer;
class CList;

class CListIterator;


//--------------------------------------------------------------------------------
//		CBufferList
//--------------------------------------------------------------------------------
class CBufferList
{
public:

		static CBufferList	*New(void);
		void		Delete();
	
		NewtonErr	Init(Boolean deleteSegments = true);
		NewtonErr	Init(CList* bufList, Boolean deleteSegments = true);

	// Buffer methods

			int		Peek(void);
			int		Next(void);
			int		Skip(void);
			int		Get(void);
			Size	Getn(UByte* p, Size n);
			int		CopyOut(UByte* p, Size& n);

			int		Put(int dataByte);
			Size	Putn(const UByte* p, Size n);
			int		CopyIn(const UByte* p, Size& n);

			void	Reset(void);
			void	ResetMark(void);

			Long	Hide(Long count, int dir);
			 Size	Seek(Long off, int dir);
			 Size	Position(void) const;
			 Size	GetSize(void) const;
			 Boolean	AtEOF(void) const;

	// List methods

		CBuffer*	At(ArrayIndex index);
		CBuffer*	First(void);
		CBuffer*	Last(void);

		NewtonErr	Insert(CBuffer* item);
		NewtonErr	InsertBefore(ArrayIndex index, CBuffer* item);
		NewtonErr	InsertAt(ArrayIndex index, CBuffer* item);
		NewtonErr	InsertFirst(CBuffer* item);
		NewtonErr	InsertLast(CBuffer* item);

		NewtonErr	Remove(CBuffer* item);
		NewtonErr	RemoveAt(ArrayIndex index);
		NewtonErr	RemoveFirst(void);
		NewtonErr	RemoveLast(void);
		NewtonErr	RemoveAll(void);

		NewtonErr	Delete(CBuffer* item);
		NewtonErr	DeleteAt(ArrayIndex index);
		NewtonErr	DeleteFirst(void);
		NewtonErr	DeleteLast(void);
		NewtonErr	DeleteAll(void);

	ArrayIndex		GetIndex(CBuffer* item);

private:

		Boolean		NextSegment(void);
		void		SelectSegment(ArrayIndex index);

	// the constructor and destructor methods are intentionally declared private
	// to prevent external code from knowing the size of the object
					CBufferList();
					~CBufferList();

}; // CBufferList


//--------------------------------------------------------------------------------
//		ROM Glue
//--------------------------------------------------------------------------------

inline CBufferList *CBufferList::New(void)
	{ return new CBufferList; }

inline void CBufferList::Delete(void)
	{ delete this; }

#endif //__BUFFERLIST_H
