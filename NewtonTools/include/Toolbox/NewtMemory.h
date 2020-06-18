/*
	File:		NewtMemory.h

	Contains:	Basic Newton memory manager calls

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v38 internal.

		WARNING:	this file is a global errors file and must be
					FRAMable.  please use caution when adding
					anything other than new errors!
*/

#ifndef __NEWTMEMORY_H
#define __NEWTMEMORY_H

#ifndef __CONFIGTOOLBOX_H
#include "ConfigToolbox.h"
#endif

#ifndef __NEWTERRORS_H
#include "NewtErrors.h"
#endif

/*	----------------------------------------------------------------
**
**	Things that can go wrong with heaps
**	 (certainly NOT exhaustive, but all of the ones returned by CheckHeap())
*/

#define kMM_BogusBlockType 					(ERRBASE_MEMORY	   )	/* e.g. not free, direct or indirect */
#define kMM_UnalignedPointer				(ERRBASE_MEMORY - 1)	/* pointer not aligned to 4-byte boundary */
#define kMM_PointerOutOfHeap				(ERRBASE_MEMORY - 2)	/* pointer to outside of heap */
#define kMM_BogusInternalBlockType			(ERRBASE_MEMORY - 3)	/* not an infrastructure type we know of */
#define kMM_MisplacedFreeBlock				(ERRBASE_MEMORY - 4)	/* free block where there shouldn't be one */
#define kMM_BadFreelistPointer				(ERRBASE_MEMORY - 5)	/* free-list pointer points outside of heap */
#define kMM_FreelistPointerPointsAtJunk		(ERRBASE_MEMORY - 6)	/* free-list pointer doesn't point at a free block */
#define kMM_BadForwardMarch					(ERRBASE_MEMORY - 7)	/* bogus block size, and we can't go forward */
#define kMM_BogusBlockSize					(ERRBASE_MEMORY - 8)	/* forbidden bits set in block-size */
#define kMM_BlockSizeLessThanMinimum		(ERRBASE_MEMORY - 9)	/* heap blocks have a certain minimum size... */
#define kMM_PreposterousBlockSize			(ERRBASE_MEMORY - 10)	/* truly huge (>2GB) blocks probably don't work at all */
#define kMM_BogusFreeCount					(ERRBASE_MEMORY - 11)	/* total free is bigger than entire heap */
#define kMM_BadNilPointer					(ERRBASE_MEMORY - 12)	/* pointer is nil (but is not allowed to be) */
#define kMM_FreeSpaceDisagreement1			(ERRBASE_MEMORY - 13)	/* tracked -vs- actual free-space is different */
#define kMM_FreeSpaceDisagreement2			(ERRBASE_MEMORY - 14)	/* tracked -vs- linked free-space is different */
#define kMM_BadMasterPointer				(ERRBASE_MEMORY - 15)	/* master pointer doesn't point back to handle block */
#define kMM_BadBlockDeltaSize				(ERRBASE_MEMORY - 16)	/* bad block-size adjustment */
#define kMM_BadInternalBlockType			(ERRBASE_MEMORY - 17)	/* possibly mangled internal block */
#define kHeapCorruptErr						(ERRBASE_MEMORY - 18)	/* heap's been whacked */
#define	kMM_ExceptionGrokkingHeap			(ERRBASE_MEMORY - 19)	/* caught an exception checking the heap [this is bad] */
#define	kMM_BadHeapHeader					(ERRBASE_MEMORY - 20)	/* noticably bad heap header */

#define memFullErr							(-108)					/* Not enough room in heap zone [traditional] */

#endif	/* __NEWTMEMORY_H	*/
