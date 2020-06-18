/*
	File:		BufferSegment.h

	Contains:	External interface to the Newton ROM buffer segment class

	Copyright:	� 1992-1995 by Apple Computer, Inc.  All rights reserved.

	NOTE:  This external file was created from version <14> of the internal file 

*/

#ifndef __BUFFERSEGMENT_H
#define __BUFFERSEGMENT_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

class CMinBuffer;
class CBuffer;

//--------------------------------------------------------------------------------
//		CBufferSegment
//--------------------------------------------------------------------------------
class CBufferSegment
{
public:

	static CBufferSegment *New(void);
	void Delete();

	// initialization

	NewtonErr	Init(Size len);
	NewtonErr	Init(void* data,
					 Size len,
					 Boolean freeBuffer = false,
					 Size validOff = 0,
					 Long validCount = -1);

	// get primitives

	int		Peek(void);
	int		Next(void);
	int		Skip(void);
	int		Get(void);
	Size	Getn(UByte* p, Size n);
	int		CopyOut(UByte* p, Size& n);

	// put primitives

	int		Put(int dataByte);
	Size	Putn(const UByte* p, Size n);
	int		CopyIn(const UByte* p, Size& n);

	// misc

	void	Reset(void);

	// position and size

	Long	Hide(Long count, int dir);
	Size	Seek(Long off, int dir);
	Size	Position(void) const;
	Size	GetSize(void) const;
	Boolean	AtEOF(void) const;

private:

	// these member functions are intentionally declared private
	// to prevent external code from knowing the size of the object

	CBufferSegment();
	~CBufferSegment();
	CBufferSegment(const CBufferSegment&);
	CBufferSegment& operator=(const CBufferSegment&);
	CBufferSegment* operator&();
	const CBufferSegment* operator&() const;

}; // CBufferSegment


//--------------------------------------------------------------------------------
//		ROM Glue
//--------------------------------------------------------------------------------

inline CBufferSegment* CBufferSegment::New()
	{ return new CBufferSegment; }
	
inline void CBufferSegment::Delete()
	{ delete this; }

#endif	/*	__BUFFERSEGMENT_H	*/
