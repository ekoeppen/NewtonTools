/*
	File:		ctype.h

	Contains:	Newton C++ Tools ctype.h subset

	Written by:	xxx put writers here xxx

	Copyright:	� 1993 by Apple Computer, Inc., all rights reserved.

*/

#pragma force_top_level
#pragma include_only_once

/*
 * ctype.h declares two functions useful for converting ascii character strings
 */

#ifndef __CTYPE_H
#define __CTYPE_H

#ifdef __cplusplus

extern "C" int tolower(int c);
extern "C" int toupper(int c);

#else

extern int tolower(int c);
    /* if c is an ASCII (0-127) upper-case letter then return the corresponding */
    /* ASCII(0-127) lower-case letter, otherwise return c.                     */

extern int toupper(int c);
    /* if c is an ASCII (0-127) lower-case letter then return the corresponding */
    /* ASCII (0-127) upper-case letter, otherwise return c.                     */

#endif

#endif

/* end of ctype.h */
