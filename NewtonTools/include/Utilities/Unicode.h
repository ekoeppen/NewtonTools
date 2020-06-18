/*
	File:		Unicode.h

	Contains:	Public header for Unicode.

	Written by:	Newton Tools Team

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

*/

#ifndef __UNICODE_H
#define __UNICODE_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif

// ---------------------------------------------------------------------------
// constants

#define kUnsupportedEncoding	-1

#ifndef __OBJECTS_H
#include "objects.h"
#endif

typedef enum {
	kUnicode = 0,				// not implemented
	kMacRomanEncoding,			// Macintosh Roman
	kASCIIEncoding,				// 7-bit ASCII
	kPCRomanEncoding,			// not implemented
	kWizardEncoding,			// for English Wizard's
	kShiftJISEncoding,			// for Japanese PV-F1, PI-3000, etc.
	kMacKanjiEncoding			// ShiftJIS for Macintosh KanjiTalk 7	// 114... 115...
} TCharEncoding;


const UChar		kNoTranslationChar = 0x1A;	// the Substitue character in ASCII
const UChar		kEndOfCharString = 0;
const UniChar	kEndOfUnicodeString = 0;


// define character size neutral definition for end of string

#ifdef hasUnicode
const UniChar kEndOfString = kEndOfUnicodeString;
const FastInt kSystemEncoding = kUnicode;
#endif


// kDefaultEncoding represents the character set of the current desktop platorm
#ifdef usePCRomanEncoding
const FastInt kDefaultEncoding = kPCRomanEncoding;
#elif defined(JapaneseVersion)
const FastInt kDefaultEncoding = kShiftJISEncoding;
#else
const FastInt kDefaultEncoding = kMacRomanEncoding;
#endif


// ---------------------------------------------------------------------------
// conversion calls

void		ConvertFromUnicode(
					const Character* source, void* dest,
					FastInt destEncoding = kDefaultEncoding, long length = 0x7FFFFFFF);

void		ConvertToUnicode(
					const void* source, Character* dest,
					FastInt srcEncoding = kDefaultEncoding, long length = 0x7FFFFFFF);


#endif	/* __UNICODE_H */
