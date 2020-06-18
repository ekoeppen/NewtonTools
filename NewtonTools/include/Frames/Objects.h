/*
	File:		objects.h

	Contains:	Newton object system
				Basic object interface

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	<01>		06/25/95	first created for Newton C++ Tools
*/

#ifndef __OBJECTS_H
#define __OBJECTS_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef kError_No_Memory
#define kError_No_Memory -10007
#endif

typedef long Ref;

// constant values for comparison with a Ref
const Ref	NILREF = 0x02;
const Ref	TRUEREF = 0x1A;
const Ref	FALSEREF = NILREF;	

class TObjectIterator;
class RefVar;
typedef const RefVar& RefArg;

typedef Ref (*MapSlotsFunction)(RefArg tag, RefArg value, ULong anything);


extern Ref 	MakeInt(long i);
extern Ref 	MakeChar(unsigned char c);
extern Ref	MakeBoolean(int val);

extern Boolean IsInt(RefArg r);	
extern Boolean IsChar(RefArg r);	
extern Boolean IsPtr(RefArg r);		
extern Boolean IsMagicPtr(RefArg r);    
extern Boolean IsRealPtr(RefArg r);   
					
extern long 	RefToInt(RefArg r);			
extern UniChar RefToUniChar(RefArg r);		

#define	ISNIL(r)	(((Ref) (r)) == NILREF)
#define	NOTNIL(r)	(((Ref) (r)) != NILREF)
#define	ISFALSE(r)	(((Ref) (r)) == FALSEREF)
#define	ISTRUE(r)	(((Ref) (r)) != FALSEREF)

#ifdef USEOLDFRAMESMACROS
/* WARNING: these obsolete macros will be removed in the next release of this header file */

#define	MAKEINT(i)		(MakeInt(i))
#define	MAKECHAR(c)     (MakeChar(c))
#define	MAKEBOOLEAN(b)	(b ? TRUEREF : FALSEREF)
#define ISINT(r)		IsInt(r)
#define ISPTR(r)		IsPtr(r)
#define ISCHAR(r)		IsChar(r)
#define	ISBOOLEAN(r)	( r == TRUEREF || r == FALSEREF)
#define RINT(r)			RefToInt(r)
#define RCHAR(r)		RefToUniChar(r)

#endif

//____________________________________________________________________
// Array Functions

extern	void	AddArraySlot(RefArg obj, RefArg value);
extern	Ref		AllocateArray(RefArg theClass, long length);
extern	void	ArrayMunger(RefArg a1, long a1start, long a1count,
						RefArg a2, long a2start, long a2count);
extern	long	ArrayPosition(RefArg array, RefArg item, long start, RefArg test);
extern	Boolean ArrayRemove(RefArg array, RefArg element);
extern	void 	ArrayRemoveCount(RefArg array, FastInt start, FastInt removeCount);
extern	Ref		GetArraySlot(RefArg obj, long slot);
extern	void	SetArraySlot(RefArg obj, long slot, RefArg value);

// Sorts an array
// test = '|<|, '|>|, '|str<|, '|str>|, or any function object returning -1,0,1 (as strcmp)
// key = NILREF (use the element directly), or a path, or any function object
extern	void	SortArray(RefArg array, RefArg test, RefArg key);		

//____________________________________________________________________
// General Object Functions

extern	Ref		AllocateBinary(RefArg theClass, long length);
extern	Ref		Clone(RefArg obj);
extern	Ref		DeepClone(RefArg obj);
extern	Ref		EnsureInternal(RefArg obj);
extern	int		EQ(RefArg a, RefArg b);
extern	void	ReplaceObject(RefArg target, RefArg replacement);
extern	Ref		TotalClone(RefArg obj);

//____________________________________________________________________
// Garbage Collection Functions

extern	void	GC();
extern	void	Statistics(ULong* freeSpace, ULong* largestFreeBlock);	

//____________________________________________________________________
// Object Class Functions

extern	Ref		ClassOf(RefArg obj);
extern	Boolean IsArray(RefArg ref);
extern	Boolean IsBinary(RefArg ref);
extern	Boolean IsFrame(RefArg ref);
extern	Boolean IsFunction(RefArg ref);								
extern	Boolean	IsInstance(RefArg obj, RefArg super);

extern	Boolean IsNumber(RefArg ref);
extern	Boolean IsReadOnly(RefArg obj);
extern	Boolean	IsReal(RefArg ref);
extern	Boolean	IsString(RefArg ref);
extern	Boolean	IsSymbol(RefArg obj);
extern	Boolean	IsSubclass(RefArg sub, RefArg super);

extern	void	SetClass(RefArg obj, RefArg theClass);

//____________________________________________________________________
// Symbol Functions

extern	Ref		MakeSymbol(char* name);		

#define	SYM(name)	MakeSymbol(#name)

extern	int		SymbolCompareLex(RefArg sym1, RefArg sym2);
extern	ULong	SymbolHash(RefArg sym);		// Return a symbol's hash value
extern	int		symcmp(char* s1, char* s2);	// Case-insensitive comparison

//____________________________________________________________________
// Frame & Slot Functions

extern	Ref		AllocateFrame(void);
extern	Boolean	FrameHasPath(RefArg obj, RefArg thePath);
extern	Boolean	FrameHasSlot(RefArg obj, RefArg slot);
extern	Ref		GetFramePath(RefArg obj, RefArg thePath);
extern	Ref		GetFrameSlot(RefArg obj, RefArg slot);
extern	long	Length(RefArg obj);		// Length in bytes or slots
extern	void	MapSlots(RefArg obj, MapSlotsFunction func, ULong anything);

//---------------------------------------------------------------------
extern	TObjectIterator*	NewTObjectIterator(RefArg obj);
extern	void				DeleteTObjectIterator(TObjectIterator* iter);

extern	void	RemoveSlot(RefArg frame, RefArg tag);
extern	void	SetFramePath(RefArg obj, RefArg thePath, RefArg value);		
extern	void	SetFrameSlot(RefArg obj, RefArg slot, RefArg value);
extern	void	SetLength(RefArg obj, long length);


//____________________________________________________________________
// String Manipulation Functions

extern	Ref		ASCIIString(RefArg str);
extern	void	BinaryMunger(RefArg a1, long a1start, long a1count,
					 RefArg a2, long a2start, long a2count);
extern	Ref		MakeString(const char* str);
extern	Ref		MakeString(const UniChar* str);		// Unicode version
extern	int		StrBeginsWith(RefArg str, RefArg prefix);
extern	void	StrCapitalize(RefArg str);
extern	void	StrCapitalizeWords(RefArg str);
extern	void	StrDowncase(RefArg str);
extern	int		StrEndsWith(RefArg str, RefArg suffix);
extern	void	StrMunger(RefArg s1, long s1start, long s1count,
				  RefArg s2, long s2start, long s2count);
extern	long	StrPosition(RefArg str, RefArg substr, long startPos);
extern	long	StrReplace(RefArg str, RefArg substr, RefArg replacement, long count);
extern	void	StrUpcase(RefArg str);
extern	Ref		Substring(RefArg str, long start, long count);
extern	void	TrimString(RefArg str);

//____________________________________________________________________
// Numeric Conversion Functions

extern	long	CoerceToInt(RefArg r);
extern	double	CoerceToDouble(RefArg r);
extern	Ref		MakeReal(double d);

//____________________________________________________________________
// Exception Handling Functions

extern	void	ThrowRefException(ExceptionName name, RefArg data);
extern	void	ThrowBadTypeWithFrameData(NewtonErr errorCode, RefArg value);

// DON'T USE THESE DIRECTLY!!!!
// MUST USE with macros WITH_LOCKED_BINARY and END_WITH_LOCKED_BINARY see below
extern Ptr		LockedBinaryPtr(RefArg obj);
extern void		UnlockRefArg(RefArg obj);


// C++ stuff to keep Ref usage simple

class RefVar {
  private:
 	long* _;

  public:
	RefVar();
	~RefVar();
	RefVar(const RefVar& o);
	RefVar(const Ref r);

	RefVar&	operator=(const RefVar& o);
	RefVar&	operator=(const Ref r);
	operator long() const;
};



class RefStruct : public RefVar {
  public:
	RefStruct();
	~RefStruct(); 	
	RefStruct(const RefStruct& o);
	RefStruct(const RefVar& o);
	RefStruct(const Ref r);
	RefStruct&	operator=(const RefVar& o);
	RefStruct&	operator=(const RefStruct& o) { return (RefStruct&)operator=((RefVar&)o); }
	RefStruct&	operator=(const Ref r);	
	operator long() const;	
};


class TObjectIterator : public SingleObject 
{ private:
  	TObjectIterator();
  public:
	void		Reset(RefArg newObj);
	int			Next(void);
	int			Done(void);
	Ref			Tag(void);
	Ref			Value(void);
};

#define FOREACH(obj, value_var) \
        {       \
        TObjectIterator* _iter = NewTObjectIterator(obj);   \
        if (!_iter) OutOfMemory();  \
        RefVar value_var;       \
        unwind_protect {        \
            while (!_iter->Done()) {    \
                value_var = _iter->Value();

#define FOREACH_WITH_TAG(obj, tag_var, value_var) \
        {       \
        TObjectIterator* _iter = NewTObjectIterator(obj);   \
        if (!_iter) OutOfMemory();  \
        RefVar tag_var;       \
        RefVar value_var;       \
        unwind_protect {        \
            while (!_iter->Done()) {    \
                tag_var = _iter->Tag(); \
                value_var = _iter->Value();

#define END_FOREACH     \
 			_iter->Next();	\
           }   \
        }       \
        on_unwind {     \
            DeleteTObjectIterator(_iter);       \
        }       \
        end_unwind;     \
        }

/* This is used like

        RefVar obj;
        ...
        FOREACH(obj, value)
            ...
            DoSomething(value);
            ...
        END_FOREACH
        ...
		
		or 
		
        RefVar obj;
        ...
        FOREACH_WITH_TAG(obj, tag, value)
            ...
			if (tag == kSomethin)
            	DoSomething(value);
            ...
        END_FOREACH
        ...
*/ 



#define WITH_LOCKED_BINARY(obj, ptr_var)        \
        unwind_protect {        \
            void* ptr_var = LockedBinaryPtr(obj);

#define END_WITH_LOCKED_BINARY(obj)  \
        }       \
        on_unwind {				\
            UnlockRefArg(obj);     \
        }       \
        end_unwind;

DeclareException(exOutOfMemory,exRootException);	// evt.ex.outofmem

// exOutOfMemory has a numeric error code 
inline void OutOfMemory(char* = 0)		{ Throw(exOutOfMemory, (void*) kError_No_Memory); }
	

#endif // __OBJECTS_H
