/*	----------------------------------------------------------------
**
**	Protocols.h  --  Protocols, monitors, protocol meta-information, protocol registry
**
**		class TProtocol;				// Base class for protocols
**		class TClassInfo;				// Meta-information for protocols
**		MONITOR TClassInfoRegistry;		// Clearing house for implementations of protocols
**
**	Copyright � 1992-1994, Apple Computer, Inc.   All Rights Reserved.
**
**	----------------------------------------------------------------
**
**	Derived from v31 internal.
**
*/

#ifndef __PROTOCOLS_H
#define __PROTOCOLS_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif


/*
**	Redefine some ProtocolGen keywords when we're really
**	going through CFront
*/

#ifndef PROTOCOLGEN
#define PROTOCOL			class
#define MONITOR				class
#define	PSEUDOSTATIC		/*nothing*/
#define	NONVIRTUAL			/*nothing*/
#define	INVISIBLE			/*nothing*/
#define PROTOCOLVERSION(x)	/*nothing*/
#define MONITORVERSION(x)	/*nothing*/
#define CAPABILITIES(x)		/*nothing*/
#endif

/*
**	If no protocols, define VIRTUAL/ENDVIRTUAL
**	so we can compile protocols as classes on Mac etc.
**	(that is, VIRTUAL functions become pure virtual).
*/

#ifdef hasNoProtocols
#define VIRTUAL				virtual
#define ENDVIRTUAL			= 0
#else
#define VIRTUAL				/*nothing*/
#define ENDVIRTUAL			/*nothing*/
#endif

#define	PROTOCOLGEN_WORKING_DELETES				/* Delete() methods work now */

class TProtocol;
class TClassInfo;
MONITOR TClassInfoRegistry;


/*	----------------------------------------------------------------
**
**	CodeProcPtr  --  Pass control to the first byte of a hunk-O-code
**						with a selector as the first argument.
**
*/
typedef void* (*CodeProcPtr)(int selector, ...);


/*	----------------------------------------------------------------
**
**	TProtocol  --  Base class for protocols and protocol monitors
**
*/
class TProtocol
{
public:
	void			Become(const TProtocol*);			// forward to an instance
	void			Become(TObjectId);					// forward to a monitor (via kernel id)
	const TClassInfo*	ClassInfo() const;				// ==> info about the protocol (doesn't work for monitors)
	TObjectId		GetMonitorId() const;				// ==> monitor id, or zero
	operator		TObjectId();						// ==> monitor id, or zero
	void			SetType(const TClassInfo*);			// set this instance's type

	long			StartMonitor						// start object up as a monitor
						(
							unsigned long	stackSize,
							TObjectId		environment = 0,
							ULong			name = 0x6D6E7472,		// Hardcode 'mntr' for Win compilers
							Boolean			rebootProtected = false
						);

	long			DestroyMonitor();					// destroy the monitor

private:
	/*
	**	Never change these
	**	 (generated glue depends on this layout)
	**
	*/
	void*			fRuntime;				// runtime usage (e.g. Throw() cleanup of autos for exceptions)
	const TProtocol*	fRealThis;			// -> true "this" for auto instances
	const void**	fBTable;				// -> dispatch table
	TObjectId		fMonitorId;				// for monitors, the monitor id

	friend class ClassInfo;					// allow (e.g.) TClassInfo::MakeAt to diddle our innards
	friend void PrivateClassInfoMakeAt(const TClassInfo*, const void* proto);	// for pre jump table use
};

inline TProtocol :: operator TObjectId()
{
	return fMonitorId;
}

/*
**	Put one of these inside the '{...}' of your protocol implementations.
**	Follow it with a semicolon.  It declares some magic stuff you're probably
**	better off not puzzling over.
**
**	That is:
**
**		PROTOCOL TFooImpl : public TFoo
**		{
**		public:
**			PROTOCOL_IMPL_HEADER_MACRO(TFooImpl);
**			<your methods>
**		};
**
**	ProtocolGen makes one of these for you if you generate source code
**	via '-ServerHeader'.
**
*/
#if defined(forARM)  ||  defined(PROTOCOLGEN)
#define	PROTOCOL_IMPL_HEADER_MACRO(name) \
	static size_t Sizeof(); \
	static const TClassInfo* ClassInfo(void)
#else
/* we need something (*anything*) to precede the semicolon */
#define	PROTOCOL_IMPL_HEADER_MACRO(name) \
	enum { __totally_bogus_enum }
#endif /*forARM*/

/*
**	For each of your protocol implementations, put one of these in your
**	".c" or ".cp" files.  You can follow it with a semicolon or not, depending
**	on how lax CFront is about extra semicolons today.
**
**		#include	"FooImpl.h"
**
**		PROTOCOL_IMPL_SOURCE_MACRO(TFooImpl)
**
**	ProtocolGen makes one of these for you if you generate source
**	code via '-ServerCFile'.
**
*/
#if forARM
#define	PROTOCOL_IMPL_SOURCE_MACRO(name) \
	size_t name :: Sizeof() { return sizeof(name); }
#else
#define	PROTOCOL_IMPL_SOURCE_MACRO(name)
#endif /*forARM*/

/*	----------------------------------------------------------------
**
**	TClassInfo  --  Meta-information for protocols
**
*/
class TClassInfo
{
public:
	const char *	ImplementationName()	const;	// implementation name
	const char *	InterfaceName()			const;	// name of public interface
	const char *	Signature()				const;	// signature (actually, capability list)
	size_t			Size()					const;	// instance size
	void			MakeAt(const void*)		const;	// construct an instance at the address
	const void *	EntryProc()				const;	// return address of monitor entry proc
	const void *	AllocProc()				const;	// return address of OperatorNew() proc, or nil
	const void *	FreeProc()				const;	// return address of OperatorDelete() proc, or nil
	unsigned long	Version()				const;	// implementation version
	unsigned long	Flags()					const;	// various flags (see below)
	long			Register()				const;	// register with protocol-server
	long			DeRegister()			const;	// de-register with protocol-server
	TProtocol *		New()					const;	// make an instance
	void			Destroy(TProtocol *)	const;	// destroy an instance at the address
	CodeProcPtr		Selector()				const;	// return address of selector proc
	const char *	GetCapability(const char*)	const;	// test if protocol has a specific capability, return it
	const char *	GetCapability(long)	const;		// test if protocol has a specific capability, return it
	Boolean			HasInstances(long *count) const; 	// return true is instances of this protocol exist, count = number of them



private:
	friend class TProtocol;
	friend size_t PrivateClassInfoSize(const TClassInfo*);	// for pre jump table use
	friend void PrivateClassInfoMakeAt(const TClassInfo*, const void* proto);
	friend const char * PrivateClassInfoInterfaceName(const TClassInfo*);
	friend const char * PrivateClassInfoImplementationName(const TClassInfo*);

	/*
	**	Never change these
	**	 (generated glue depends on this layout, and if you change
	**	  anything here you will definitely wish you hadn't)
	**
	**	This structure is relocatable.  Please keep it that way.
	**
	*/
	long			fReserved1;				// (reserved for future use, zero for now)
	long			fNameDelta;				// SRO (Self-Relative-Offset) to asciz implementation name
	long			fInterfaceDelta;		// SRO to asciz protocol name
	long			fSignatureDelta;		// SRO to asciz signature
	long			fBTableDelta;			// SRO to dispatch table
	long			fEntryProcDelta;		// SRO to monitor entry (valid only for monitors)
	unsigned long	fSizeofBranch;			// ARM branch to sizeof-code
	unsigned long	fAllocBranch;			// ARM branch to alloc-code, or zero
	unsigned long	fFreeBranch;			// ARM branch to OperatorDelete code, or zero
	unsigned long	fDefaultNewBranch;		// ARM branch to New(void), or MOV PC,LK
	unsigned long	fDefaultDeleteBranch;	// ARM branch to Delete(void), or MOV PC,LK
	unsigned long	fVersion;				// this implementation's version
	unsigned long	fFlags;					// various flags (see below)
	long			fSelectorBranch;		// ARM branch to bail-out function (that returns nil now)
	long			fReserved2;				// (reserved for future use, zero for now)
};


enum
{
	 kci_IsMonitor		= 0x00000001		// bit 0 ==> is monitor
};


/*	----------------------------------------------------------------
**
**	TClassInfoRegistry  --  A registry of protocols
**
*/
MONITOR TClassInfoRegistry : public TProtocol
{
public:

	static TClassInfoRegistry* New(const char*);
	void			Delete();

	NewtonErr		Register(const TClassInfo*, ULong refCon=0);
	NewtonErr		DeRegister(const TClassInfo*, Boolean specific=false);
	Boolean			IsRegistered(const TClassInfo*, Boolean specific=false) const;
	const TClassInfo* Satisfy(const char* intf, const char* impl, ULong version) const;
	long			Seed() const;
	const TClassInfo*	First(long seed, ULong* pRefCon=0) const;
	const TClassInfo*	Next(long seed, const TClassInfo* from, ULong* pRefCon=0) const;
	const TClassInfo*	Find(const char* intf, const char* impl, int skipCount, ULong* pRefCon=0) const;

	//	2.0 calls
	const TClassInfo*	Satisfy(const char* intf, const char* impl, const char* capability) const;
	const TClassInfo*	Satisfy(const char* intf, const char* impl, const char* capability, const char* capabilityValue) const;
	const TClassInfo*	Satisfy(const char* intf, const char* impl, const long capability, const long capabilityValue = 0) const;

	void				UpdateInstanceCount(const TClassInfo* classinfo, long adjustment);
	long 				GetInstanceCount(const TClassInfo* classinfo);
};

extern TClassInfoRegistry*		gProtocolRegistry;
extern TProtocol*				NewByName(const char * abstract, const char * implementation);
extern TProtocol*				NewByName(const char * abstract, const char * implementation, ULong version);	// ask for version
extern TProtocol*				NewByName(const char * abstract, const char * implementation, const char * capability);
extern const TClassInfo*		ClassInfoByName(const char * abstract, const char * implementation, ULong version = 0);
extern TProtocol*				AllocInstanceByName(const char * abstract, const char * implementation);
extern void						FreeInstance(TProtocol*);
extern void						StartupProtocolRegistry(void);
extern TClassInfoRegistry*		GetProtocolRegistry(void);


/*	----------------------------------------------------------------
**
**	Standard selectors for hunks-of-code
**
*/
enum {
	 kCodeInit			= 0			// int (*code)(kCodeInit);	// initialization, returns zero on success
	,kCodeVersion		= 1			// int (*code)(kCode);		// version, zero for now
	,kCodeInfo			= 2			// int (*code)(kCode);		// any number you like
	,kCodeClassCount	= 3			// int (*code)(kCode);		// ==> # classes
	,kCodeClassAt		= 4			// const TClassInfo* (*code)(kCode, int Nth);	// class-info-proc for Nth class
	,kCodeReserved5		= 5			// reserved
	,kCodeReserved6		= 6			// reserved
	,kCodeReserved7		= 7			// reserved

	// First generally available selector is 8
};


/*	----------------------------------------------------------------
**
**	Functions for working with hunks-of-code
**
*/
extern const TClassInfo*	ClassInfoFromHunkByName(void * hunk, const char * abstract, const char * implementation);
extern TProtocol*		NewFromHunkByName(void * hunk, const char * abstract, const char * implementation);


/*	----------------------------------------------------------------
**
**	SAFELY_CAST  --  safely cast an instance of a protocol to some
**					 expected implementation
**
**		o	result is zero if the implementation isn't the exact
**			expected one
**
*/
#define	SAFELY_CAST(instance, to) \
	instance->ClassInfo() == to::ClassInfo() ? (to*)instance : 0

#endif /* __PROTOCOLS_H */
