/*
	File:		New.h

	Contains:	new operator for Newton C++ Tools

	Written by:	

	Copyright:	� 1992 by Apple Computer, Inc., all rights reserved.
	
*/

#ifndef __NEW_H
#define __NEW_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif


#ifdef __cplusplus
/*	----------------------------------------------------------------
**
**	In-place operator new.
**
**		Use it to call a constructor for a hunk of bytes that you
**		have alllocated, like this:
**
**			void * hunk_of_memory = malloc(42);
**
**			TFoo * foo = new(hunk_of_memory) TFoo(...constructor args...);
**
*/
void * operator new ( size_t, void * );
#endif

#endif /* __NEW_H */
