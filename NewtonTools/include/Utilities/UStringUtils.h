/*
	File:		UStringUtils.h

	Contains:	Unicode-friendly version of some common string
				utility functions.

	Written by:	Newton Tools team

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.


*/

#ifndef __USTRINGUTILS_H
#define __USTRINGUTILS_H

#ifndef __NEWTON_H
#include "Newton.h"
#endif


//------------------------------------------------------------------------
//	standard string utilities

#ifdef __cplusplus
extern "C" {
#endif

Character* 	Ustrcpy( Character* destStr, const Character* sourceStr );
Character*	Ustrncpy( Character* destStr, const Character* sourceStr, ULong n );
Character*	Ustrcat( Character* destStr, const Character* sourceStr );
Character*	Ustrncat( Character* destStr, const Character* sourceStr, ULong n );
ULong		Ustrlen( const Character* str );
Character*	Ustrchr( const Character *str, Character ch );
FastInt		Ustrcmp( const Character* str1, const Character* str2 );
void*		Umemset(void* str, Character ch, ULong numChars);

ULong		Umbstrlen( const Character* str, FastInt destEncoding );
ULong		Umbstrnlen( const Character* str, FastInt destEncoding, ULong n );

#ifdef __cplusplus
}	// extern "C"
#endif

Boolean 	HasChars(Character* c);
Boolean 	HasDigits(Character* c);
Boolean 	HasSpaces(Character* c);

Boolean		IsPunctSymbol(Character *word, FastInt index);
void		StripPunctSymbols(Character *word);

// unicode wrappers for char-by-char conversions
void 		ConvertUnicodeCharacters(Character* array, Ptr buffer, FastInt conversionType, long len);
long 		ConvertUnicodeChar(Character* c, Ptr b, FastInt conversionType);

#endif	/* __USTRINGUTILS_H */
