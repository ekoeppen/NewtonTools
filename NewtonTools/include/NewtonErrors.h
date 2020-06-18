/*
	File:		NewtonErrors.h
	
	Contains:	Error code for Newton C++ Tools

	Written by:	Newton Tools Group

	Copyright:	� 1996 by Apple Computer, Inc., all rights reserved.

*/


#ifndef __NEWTONERRORS_H
#define __NEWTONERRORS_H

#define		kMMErrBase				(-34000)	// Memory errors


#define kMemErrBogusBlockType 				(kMMErrBase	   )	/* e.g. not free, direct or indirect */
#define kMemErrUnalignedPointer				(kMMErrBase - 1)	/* pointer not aligned to 4-byte boundary */
#define kMemErrPointerOutOfHeap				(kMMErrBase - 2)	/* pointer to outside of heap */
#define kMemErrBogusInternalBlockType		(kMMErrBase - 3)	/* Unknown infrastructure type */
#define kMemErrMisplacedFreeBlock			(kMMErrBase - 4)	/* free block where there shouldn't be one */
#define kMemErrBadFreelistPointer			(kMMErrBase - 5)	/* free-list pointer points outside of heap */
#define kMemErrFreelistPointerPointsAtJunk	(kMMErrBase - 6)	/* free-list pointer doesn't point at a free block */
#define kMemErrBadForwardMarch				(kMMErrBase - 7)	/* Invalid block size */
#define kMemErrBogusBlockSize				(kMMErrBase - 8)	/* forbidden bits set in block-size */
#define kMemErrBlockSizeLessThanMinimum		(kMMErrBase - 9)	/* heap blocks have a certain minimum size... */
#define kMemErrPreposterousBlockSize		(kMMErrBase - 10)	/* heap block too large (>2GB) probably don't  */
#define kMemErrBogusFreeCount				(kMMErrBase - 11)	/* total free is bigger than entire heap */
#define kMemErrBadNilPointer				(kMMErrBase - 12)	/* Nil pointer where not allowed  */
#define kMemErrFreeSpaceDisagreement1		(kMMErrBase - 13)	/* tracked -vs- actual free-space is different */
#define kMemErrFreeSpaceDisagreement2		(kMMErrBase - 14)	/* tracked -vs- linked free-space is different */
#define kMemErrBadMasterPointer				(kMMErrBase - 15)	/* master pointer doesn't point back to handle block */
#define kMemErrBadBlockDeltaSize			(kMMErrBase - 16)	/* bad block-size adjustment */
#define kMemErrBadInternalBlockType			(kMMErrBase - 17)	/* possibly mangled internal block */
#define kMemErrHeapCorruptErr				(kMMErrBase - 18)	/* The heap is invalid [apparently whacked?] */
#define	kMemErrExceptionGrokkingHeap		(kMMErrBase - 19)	/* caught an exception checking the heap [this is bad] */
#define	kMemErrBadHeapHeader				(kMMErrBase - 20)	/* Invalid heap header  */



#define kNSErrBase					(-48000)	

#define kNSErrNotAFrameStore		(kNSErrBase - 1)	// The PCMCIA card is not a data storage card
#define kNSErrOldStoreFormat		(kNSErrBase - 2)	// Store format is too old to understand
#define kNSErrNewStoreFormat		(kNSErrBase - 3)	// Store format is too new to understand
#define kNSErrStoreCorrupted		(kNSErrBase - 4)	// Store is corrupted, can't recover
#define kNSErrObjectCorrupted		(kNSErrBase - 5)	// Single object is corrupted, can't recover
#define kNSErrUnknownStreamFormat	(kNSErrBase - 6)	// Object stream has unknown format version
#define kNSErrInvalidFaultBlock		(kNSErrBase - 7)	// Fault block is invalid (probably from a removed store)
#define kNSErrNotAFaultBlock		(kNSErrBase - 8)	// Not a fault block (internal error)
#define kNSErrNotASoupEntry			(kNSErrBase - 9)	// Not a soup entry
#define kNSErrStoreNotRegistered	(kNSErrBase - 10)	// Tried to remove a store that wasn't registered
#define kNSErrUnknownIndexType		(kNSErrBase - 11)	// Soup index has an unknown type
#define kNSErrUnknownKeyStructure	(kNSErrBase - 12)	// Soup index has an unknown key structure
#define kNSErrNoSuchIndex			(kNSErrBase - 13)	// Soup index does not exist
#define kNSErrDuplicateSoupName		(kNSErrBase - 14)	// A soup with this name already exists
#define kNSErrCantCopyToUnionSoup	(kNSErrBase - 15)	// Tried to CopyEntries to a union soup
#define kNSErrInvalidSoup			(kNSErrBase - 16)	// Soup is invalid (probably from a removed store)
#define kNSErrInvalidStore			(kNSErrBase - 17)	// entry is invalid (probably from a removed store)
#define kNSErrInvalidEntry			(kNSErrBase - 18)	// Entry is invalid (probably from a removed store)
#define kNSErrKeyHasWrongType		(kNSErrBase - 19)	// Key does not have the type specified in the index
#define kNSErrStoreIsROM			(kNSErrBase - 20)	// Store is in ROM
#define kNSErrDuplicateIndex		(kNSErrBase - 21)	// Soup already has an index with this path
#define kNSErrInternalError			(kNSErrBase - 22)	// Internal error--something unexpected happened
#define kNSErrCantRemoveUIDIndex	(kNSErrBase - 23)	// Tried to RemoveIndex the _uniqueID index
#define kNSErrInvalidQueryType		(kNSErrBase - 24)	// Query type missing or unknown
#define kNSErrIndexCorrupted		(kNSErrBase - 25)	// Discovered index inconsistency
#define kNSErrInvalidTagsCount		(kNSErrBase - 26)	// max tags count has been reached
#define kNSErrNoTags				(kNSErrBase - 27)	// soup does not have tags (PlainSoupModifyTag, PlainSoupRemoveTags)
#define kNSErrInvalidTagSpec		(kNSErrBase - 28)	// tagSpec frame is invalid
#define	kNSErrWrongStoreVersion		(kNSErrBase - 29)	// Store cannot handle the feature (e.g. large objects)
#define kNSErrInvalidSorting		(kNSErrBase - 30)	// indexDesc requests an unknown sorting table
#define kNSErrInvalidUnion			(kNSErrBase - 31)	// can not UnionSoup (different sorting tables)
#define kNSErrBadIndexDesc			(kNSErrBase - 32)	// Bad index description
#define kNSErrVBOKey				(kNSErrBase - 33)	// Soup entries keys can not be virtual binaries


#define kNSErrObjectPointerOfNonPtr	(kNSErrBase - 200)	// ObjectPtr of non-pointer
#define kNSErrBadMagicPointer		(kNSErrBase - 201)	// Bad magic pointer
#define kNSErrEmptyPath				(kNSErrBase - 202)	// Empty path
#define kNSErrBadSegmentInPath		(kNSErrBase - 203)	// Invalid segment in path expression
#define kNSErrPathFailed			(kNSErrBase - 204)	// Path failed
#define kNSErrOutOfBounds			(kNSErrBase - 205)	// Index out of bounds (string or array)
#define kNSErrObjectsNotDistinct	(kNSErrBase - 206)	// Source and dest must be different objects
#define kNSErrLongOutOfRange		(kNSErrBase - 207)	// Long out of range
#define kNSErrSettingHeapSizeTwice	(kNSErrBase - 208)	// Call SetObjectHeapSize only once, before InitObjects
#define kNSErrGcDuringGc			(kNSErrBase - 209)	// GC during GC...this is bad!
#define kNSErrBadArgs				(kNSErrBase - 210)	// Bad args
#define kNSErrStringTooBig			(kNSErrBase - 211)	// String too big
#define kNSErrTFramesObjectPtrOfNil	(kNSErrBase - 212)	// TFramesObjectPtr of NIL
#define kNSErrUnassignedTFramesObjectPtr	(kNSErrBase - 213)	// unassigned TFramesObjectPtr
#define kNSErrObjectReadOnly		(kNSErrBase - 214)	// Object is read-only
#define kNSErrOutOfObjectMemory		(kNSErrBase - 216)	// Ran out of heap memory
#define kNSErrDerefMagicPointer		(kNSErrBase - 217)	// Magic pointers cannot be dereferenced in Fram
#define kNSErrNegativeLength		(kNSErrBase - 218)	// Negative length
#define kNSErrOutOfRange			(kNSErrBase - 219)	// Value out of range
#define kNSErrCouldntResizeLockedObject	(kNSErrBase - 220)	// Couldn't resize locked object
#define kNSErrBadPackageRef			(kNSErrBase - 221)	// Reference to deactivated package
#define kNSErrBadExceptionName		(kNSErrBase - 222)	// Exception not a subexception of |evt.ex|

#define kNSErrNotAFrame				(kNSErrBase - 400)	// Expected a frame
#define kNSErrNotAnArray			(kNSErrBase - 401)	// Expected an array
#define kNSErrNotAString			(kNSErrBase - 402)	// Expected a string
#define kNSErrNotAPointer			(kNSErrBase - 403)	// Expected a pointer, array, or binary object
#define kNSErrNotANumber			(kNSErrBase - 404)	// Expected a number
#define kNSErrNotAReal				(kNSErrBase - 405)	// Expected a real
#define kNSErrNotAnInteger			(kNSErrBase - 406)	// Expected an integer
#define kNSErrNotACharacter			(kNSErrBase - 407)	// Expected a character
#define kNSErrNotABinaryObject		(kNSErrBase - 408)	// Expected a binary object
#define kNSErrNotAPathExpr			(kNSErrBase - 409)	// Expected a path expression (or a symbol or integer)
#define kNSErrNotASymbol			(kNSErrBase - 410)	// Expected a symbol
#define kNSErrNotAFunction			(kNSErrBase - 411)	// Expected a function
#define kNSErrNotAFrameOrArray		(kNSErrBase - 412)	// Expected a frame or an array
#define kNSErrNotAnArrayOrNil		(kNSErrBase - 413)	// Expected an array or NIL
#define kNSErrNotAStringOrNil		(kNSErrBase - 414)	// Expected a string or NIL
#define kNSErrNotABinaryObjectOrNil	(kNSErrBase - 415)	// Expected a binary object or NIL
#define kNSErrUnexpectedFrame		(kNSErrBase - 416)	// Unexpected frame
#define kNSErrUnexpectedBinaryObject	(kNSErrBase - 417)	// Unexpected binary object
#define kNSErrUnexpectedImmediate	(kNSErrBase - 418)	// Unexpected immediate
#define kNSErrNotAnArrayOrString	(kNSErrBase - 419)	// Expected an array or string
#define kNSErrNotAVBO				(kNSErrBase - 420)	// Expected a vbo
#define kNSErrNotAPackage			(kNSErrBase - 421)	// Expected a package
#define kNSErrNotNil				(kNSErrBase - 422)	// Expected a NIL
#define kNSErrNotASymbolOrNil		(kNSErrBase - 423)  // expected NIL or a Symbol
#define kNSErrNotTrueOrNil			(kNSErrBase - 424)  // expected NIL or True
#define kNSErrNotAnIntegerOrArray	(kNSErrBase - 425)  // expected an integer or an array


#define kNSErrNotInBreakLoop		(kNSErrBase - 800)	// Not in a break loop
#define kNSErrTooManyArgs			(kNSErrBase - 802)	// Too many args for a CFunction
#define kNSErrWrongNumberOfArgs		(kNSErrBase - 803)	// Wrong number of args
#define kNSErrZeroForLoopIncr		(kNSErrBase - 804)	// For loop by expression has value zero
#define kNSErrNoCurrentException	(kNSErrBase - 806)	// No current exception
#define kNSErrUndefinedVariable		(kNSErrBase - 807)	// Undefined variable
#define kNSErrUndefinedGlobalFunction	(kNSErrBase - 808)	// Undefined global function
#define kNSErrUndefinedMethod		(kNSErrBase - 809)	// Undefined method
#define kNSErrMissingProtoForResend	(kNSErrBase - 810)	// No _proto for inherited send
#define kNSErrNilContext			(kNSErrBase - 811)	// Tried to access slot in NIL context
#define kNSErrBadCharForString		(kNSErrBase - 815)	// The operation would make the (rich) string invalid



// ---------------  Common errors�  -------------

#define 	noErr						0
#define 	kNoMemory					(-7000)


#endif // __NEWTONERRORS_H


