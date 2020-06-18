/*
	File:		OptionArray.h

	Contains:	Interface to CommAPI config/options

	Copyright:	� 1992-1996 by Apple Computer, Inc., all rights reserved.

	Derived from v6 internal of OptionArrayExternal.h.

*/

#ifndef __OPTIONARRAY_H
#define __OPTIONARRAY_H


#ifndef FRAM

	#ifndef __NEWTMEMORY_H
		#include "NewtMemory.h"
	#endif


	#ifndef __USERSHAREDMEM_H
		#include "UserSharedMem.h"
	#endif

#endif //notFRAM


// TOption status bit masks�
#define kProcessedFlagMask		(0x80000000)
#define kExtendedFormatMask		(0x40000000)	// not the same as TOptionExtended!

// TOption element types�
#define	kServiceSpecificType	(0x02000000)	// used for TOptionExtended
#define kServiceType			(0x04000000)
#define kAddressType			(0x08000000)
#define kOptionType				(0x0C000000)
#define	kConfigType				(0x10000000)
#define	kTypeMask				(0x3F000000)


// TOption OpCode mask
#define	kOpCodeMask				(0x0000ff00)
#define	kOpCodeResultMask		(0x000000ff)


// TOption (individual) opCodes
#define	opInvalid				(0x0000)			//    0: invalid opCode (the default)
#define	opSetNegotiate			(0x0100)			//  256: set, may not be what we expected
#define	opSetRequired			(0x0200)			//  512: set, fail if unable
#define	opGetDefault			(0x0300)			//  768: get default option value
#define	opGetCurrent			(0x0400)			// 1024: get current option value

// TOptionArray (aggregate) opCodes [used in TEndpoint::OptMgmt]
#define	opProcess				(0x0500)			// 1280: process each option (use option opCode)

#ifdef FRAM

// TOption (individual) result codes
#define opInProgress			1			// operation is in progress, and not yet complete
#define	opSuccess				0			// operation completed successfully
#define	opFailure				-1			// operation failed
#define	opPartSuccess			-2			// (set) but actual value different from requested value (opSetNegotiate only)
#define	opReadOnly				-3			// set attempted on read-only option
#define	opNotSupported			-4			// option not supported
#define	opBadOpCode				-5			// opCode is invalid

// TOptionArray (aggregate) result codes
#define	opNotFound				-6			// option not found
#define	opTruncated				-7			// one or more requested options are missing
#define	opPadded				-8			// option was padded with garbage

#endif // FRAM

#ifndef FRAM

// TOption (individual) result codes
#define opInProgress			((ULong)1)			// operation is in progress, and not yet complete
#define	opSuccess				((ULong)0)			// operation completed successfully
#define	opFailure				((ULong)-1)			// operation failed
#define	opPartSuccess			((ULong)-2)			// (set) but actual value different from requested value (opSetNegotiate only)
#define	opReadOnly				((ULong)-3)			// set attempted on read-only option
#define	opNotSupported			((ULong)-4)			// option not supported
#define	opBadOpCode				((ULong)-5)			// opCode is invalid

// TOptionArray (aggregate) result codes
#define	opNotFound				((ULong)-6)			// option not found
#define	opTruncated				((ULong)-7)			// one or more requested options are missing
#define	opPadded				((ULong)-8)			// option was padded with garbage

class TOption;
class TOptionArray;
class TOptionIterator;
class TSubArrayOption;

typedef FastInt OptionOpCodes;
typedef FastInt OptionOpCodesResult;


//--------------------------------------------------------------------------------
//		TOption
//--------------------------------------------------------------------------------

class TOption
{
public:
				TOption(ULong type = kOptionType);

	Boolean		IsProcessed();	// has this option been processed?
	Boolean		IsExtended();	// is this option in extended format?
	Boolean		IsService();	// is this TOption a service type?
	Boolean		IsAddress();	// is this TOption an address type?
	Boolean		IsOption();		// is this TOption a option type?
	Boolean		IsConfig();		// is this TOption a config type?
	Boolean		IsServiceSpecific();		// is this TOption matched for a particular service?

	void		Reset();

	Size		Length();		// return length
	ULong		Label();		// return label

	void		SetOpCode(ULong opCode);			// set the option opCode
	void		SetOpCodeResult(ULong opCode);		// set the option opCode result
	ULong		GetOpCode();						// return the option opCode
	ULong		GetOpCodeResults();					// return the option opCode results

	void		SetLabel(ULong label);
	void		SetLength(Size length);

	void		SetProcessed();	// set as processed
	void		SetAsService(ULong serviceId);		// Set fLabel to the serviceId and call SetAsService()
	void		SetAsService();						// Set the service flag
	void		SetAsOption(ULong optionId);
	void		SetAsConfig(ULong configId);
	void		SetAsAddress(ULong addrId);

	NewtonErr	CopyDataFrom(TOption* source);
	TOption*	Clone(void);

private:

//	friend TOptionIterator;
//	friend TOptionArray;
//	friend TOptionExtended;

	ULong		fLabel;			// option label
	Size		fLength;		// length of data, excluding header (i.e., fLabel, fLength, fFlags)
	ULong		fFlags;			// flag bits

	// variable amount of data follows, derived classes specify
};


//--------------------------------------------------------------------------------
//		TOptionExtended
//--------------------------------------------------------------------------------

class TOptionExtended : public TOption
{
	public:
					TOptionExtended(ULong type = kOptionType);

		void		SetAsServiceSpecific(ULong service);
		ULong		ServiceLabel();
		void		SetExtendedResult(NewtonErr result);
		NewtonErr	GetExtendedResult();

	private:

		ULong		fServiceLabel;
		NewtonErr	fExtendedResult;
};


//--------------------------------------------------------------------------------
//		TOptionArray
//--------------------------------------------------------------------------------

class TOptionArray : SingleObject
{

public:

					TOptionArray();
					~TOptionArray();

		NewtonErr	Init(void);
		NewtonErr	Init(ULong initialSize);
		NewtonErr	Init(TObjectId sharedId, ULong optionCount);
		NewtonErr	Init(TSubArrayOption* array);

		void		Reset();

	// array manipulation primitives

		TOption*	OptionAt(ArrayIndex index);
		NewtonErr	CopyOptionAt(ArrayIndex index, TOption* copy);

		NewtonErr	AppendOption(TOption* opt);
		NewtonErr	AppendVarOption(TOption* opt, void* varData, ULong varLen);
		NewtonErr	AppendSubArray(TOptionArray* subArray);

		NewtonErr	InsertOptionAt(ArrayIndex index, TOption* opt);
		NewtonErr	InsertVarOptionAt(ArrayIndex index, TOption* opt, void* varData, ULong varLen);
		NewtonErr	InsertSubArrayAt(ArrayIndex index, TOptionArray* subArray);

		NewtonErr	RemoveOptionAt(ArrayIndex index);
		NewtonErr	RemoveAllOptions(void);

	// miscellaneous functions

		ULong		GetSize();				// how many bytes array contains
		ArrayIndex	GetArrayCount();		// how many TOption elements on array

		NewtonErr	Merge(TOptionArray* optionArray);
		Boolean		IsEmpty(void);


	// shared memory access

		Boolean		IsShared();
		TObjectId	GetSharedId();
		NewtonErr	MakeShared(ULong permissions = kSMemReadOnly);
		NewtonErr	UnShare();

		NewtonErr	CopyFromShared(TObjectId sharedId, ULong count);
		NewtonErr	CopyToShared(TObjectId sharedId);
		NewtonErr	ShadowCopyBack(void);

private:

		friend class TOptionIterator;

		ArrayIndex			fCount;				// elements in array
		Ptr					fArrayBlock;		// element storage
		TOptionIterator*	fIterator;			// linked list of iterators active on this array
		TUSharedMem			fSharedMemoryObject;
		Boolean				fIsShared;			// TRUE if we have been shared
		Boolean				fShadow;			// TRUE if were created from a shared memory object

#ifdef DebugOptionArrayAtomicity
		Boolean				fNeedSemaphore;
#endif

}; // TOptionArray


//--------------------------------------------------------------------------------
//		TOptionIterator
//--------------------------------------------------------------------------------
class TOptionIterator : SingleObject
{

public:

					TOptionIterator();
					TOptionIterator(TOptionArray* itsOptionArray);
					TOptionIterator(TOptionArray* itsOptionArray,
						ArrayIndex itsLowBound, ArrayIndex itsHighBound);

					~TOptionIterator();

		void		Init(TOptionArray* itsOptionArray, ArrayIndex itsLowBound,
						ArrayIndex itsHighBound);
		void		InitBounds(ArrayIndex itsLowBound, ArrayIndex itsHighBound);

		void		Reset(void);
		void		ResetBounds(void);

		ArrayIndex	FirstIndex(void);
		ArrayIndex	NextIndex(void);
		ArrayIndex	CurrentIndex(void);

		TOption*	FirstOption(void);
		TOption*	NextOption(void);
		TOption*	CurrentOption(void);

		TOption*	FindOption(ULong label);

		Boolean		More(void);

protected:

		void		Advance(void);

		TOptionArray*		fOptionArray;			// the associated option array

		ArrayIndex			fCurrentIndex;			// current index of this iteration
		ArrayIndex			fLowBound;				// lower bound of iteration in progress
		ArrayIndex			fHighBound;				// upper bound of iteration in progress
		TOption*			fCurrentOption;

private:

friend class TOptionArray;

		void					RemoveOptionAt(ArrayIndex theIndex);
		void					InsertOptionAt(ArrayIndex theIndex);
		void					DeleteArray(void);

		TOptionIterator*		AppendToList(TOptionIterator* toList);
		TOptionIterator*		RemoveFromList(void);

		TOptionIterator*		fPreviousLink;			// link to previous iterator
		TOptionIterator*		fNextLink;				// link to next iterator

// private and not implemented to prevent copying and assignment

					TOptionIterator(const TOptionIterator&);
		TOptionIterator& operator=(const TOptionIterator&);

}; // TOptionIterator


//--------------------------------------------------------------------------------
//		TOption inline functions
//--------------------------------------------------------------------------------

inline Boolean TOption::IsProcessed()
	{ return ( (fFlags & kProcessedFlagMask) == kProcessedFlagMask ); }

inline Boolean TOption::IsExtended()
	{ return ( (fFlags & kExtendedFormatMask) == kExtendedFormatMask ); }

inline Boolean TOption::IsService()
	{ return ( (fFlags & kTypeMask) == kServiceType ); }

inline Boolean TOption::IsAddress()
	{ return ( (fFlags & kTypeMask) == kAddressType ); }

inline Boolean TOption::IsOption()
	{ return ( (fFlags & kTypeMask) == kOptionType ); }

inline Boolean TOption::IsConfig()
	{ return ( (fFlags & kTypeMask) == kConfigType ); }

inline Boolean TOption::IsServiceSpecific()
	{ return ( (fFlags & kTypeMask) == kServiceSpecificType ); }

inline Size TOption::Length()
	{ return fLength; }

inline ULong TOption::Label()
	{ return fLabel; }

inline void TOption::SetLabel(ULong label)
	{ fLabel = label; }

inline void TOption::SetLength(Size length)
	{ fLength = length; }

inline void TOption::SetProcessed()
	{ fFlags |= kProcessedFlagMask; }

inline void TOption::SetOpCode(ULong opCode)
	{ fFlags = (fFlags & ~kOpCodeMask) | (opCode & kOpCodeMask); }

inline void TOption::SetOpCodeResult(ULong opCode)
	{ fFlags = (fFlags & ~kOpCodeResultMask) | (opCode & kOpCodeResultMask); }

inline ULong TOption::GetOpCode()
	{ return (fFlags & kOpCodeMask); }

inline ULong TOption::GetOpCodeResults()
	{ return ((Long) ((SByte)(fFlags & kOpCodeResultMask))); }
	// we want the low eight bits to be sign extended before returning as ULong

inline ULong TOptionArray::GetSize()
	{ return GetPtrSize(fArrayBlock); }

inline ULong TOptionExtended::ServiceLabel()
	{ return fServiceLabel; }

inline void TOptionExtended::SetExtendedResult(NewtonErr result)
	{ fExtendedResult = result; }

inline NewtonErr TOptionExtended::GetExtendedResult()
	{ return fExtendedResult; }

//--------------------------------------------------------------------------------
//		TOptionArray inline functions
//--------------------------------------------------------------------------------

inline ArrayIndex TOptionArray::GetArrayCount()
	{ return fCount; }

inline NewtonErr TOptionArray::AppendOption(TOption* opt)
	{ return InsertOptionAt(fCount, opt); }

inline NewtonErr TOptionArray::AppendVarOption(TOption* opt, void* varData, ULong varLen)
	{ return InsertVarOptionAt(fCount, opt, varData, varLen); }

inline NewtonErr TOptionArray::AppendSubArray(TOptionArray* subArray)
	{ return InsertSubArrayAt(fCount, subArray); }

inline Boolean TOptionArray::IsEmpty()
	{ return (fCount == 0); }

inline Boolean TOptionArray::IsShared()
	{ return fIsShared; }

inline TObjectId TOptionArray::GetSharedId()
	{ return (TObjectId)fSharedMemoryObject; }


#endif // notFRAM


#endif //__OPTIONARRAY_H
