/*
	File:		NewtonScript.h

	Contains:	NewtonScript interface for Newton C++ Tools

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

*/

#ifndef	__NEWTONSCRIPT_H
#define	__NEWTONSCRIPT_H

#ifndef __OBJECTS_H
#include <objects.h>
#endif

// ---------------------------------------------------------------------------
// NewtonScript
// 
// Callbacks to NewtonScript functions from C/C++
// ---------------------------------------------------------------------------


extern Ref NSCall(RefArg fcn);
extern Ref NSCall(RefArg fcn, RefArg arg0);
extern Ref NSCall(RefArg fcn, RefArg arg0, RefArg arg1);
extern Ref NSCall(RefArg fcn, RefArg arg0, RefArg arg1, RefArg arg2);
extern Ref NSCall(RefArg fcn, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3);
extern Ref NSCall(RefArg fcn, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4);
extern Ref NSCall(RefArg fcn, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4, RefArg arg5);
extern Ref NSCallWithArgArray(RefArg fn, RefArg args);

extern Ref NSCallGlobalFn(RefArg sym);
extern Ref NSCallGlobalFn(RefArg sym, RefArg arg0);
extern Ref NSCallGlobalFn(RefArg sym, RefArg arg0, RefArg arg1);
extern Ref NSCallGlobalFn(RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2);
extern Ref NSCallGlobalFn(RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3);
extern Ref NSCallGlobalFn(RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4);
extern Ref NSCallGlobalFn(RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4, RefArg arg5);
extern Ref NSCallGlobalFnWithArgArray(RefArg sym, RefArg args);

extern Ref NSSend(RefArg receiver, RefArg sym);
extern Ref NSSend(RefArg receiver, RefArg sym, RefArg arg0);
extern Ref NSSend(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1);
extern Ref NSSend(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2);
extern Ref NSSend(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3);
extern Ref NSSend(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4);
extern Ref NSSend(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4, RefArg arg5);
extern Ref NSSendWithArgArray(RefArg receiver, RefArg sym, RefArg args);

extern Ref NSSendIfDefined(RefArg receiver, RefArg sym);
extern Ref NSSendIfDefined(RefArg receiver, RefArg sym, RefArg arg0);
extern Ref NSSendIfDefined(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1);
extern Ref NSSendIfDefined(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2);
extern Ref NSSendIfDefined(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3);
extern Ref NSSendIfDefined(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4);
extern Ref NSSendIfDefined(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4, RefArg arg5);
extern Ref NSSendIfDefinedWithArgArray(RefArg receiver, RefArg sym, RefArg args);

extern Ref NSSendProto(RefArg receiver, RefArg sym);
extern Ref NSSendProto(RefArg receiver, RefArg sym, RefArg arg0);
extern Ref NSSendProto(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1);
extern Ref NSSendProto(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2);
extern Ref NSSendProto(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3);
extern Ref NSSendProto(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4);
extern Ref NSSendProto(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4, RefArg arg5);
extern Ref NSSendProtoWithArgArray(RefArg receiver, RefArg sym, RefArg args);

extern Ref NSSendProtoIfDefined(RefArg receiver, RefArg sym);
extern Ref NSSendProtoIfDefined(RefArg receiver, RefArg sym, RefArg arg0);
extern Ref NSSendProtoIfDefined(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1);
extern Ref NSSendProtoIfDefined(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2);
extern Ref NSSendProtoIfDefined(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3);
extern Ref NSSendProtoIfDefined(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4);
extern Ref NSSendProtoIfDefined(RefArg receiver, RefArg sym, RefArg arg0, RefArg arg1, RefArg arg2, RefArg arg3, RefArg arg4, RefArg arg5);
extern Ref NSSendProtoIfDefinedWithArgArray(RefArg receiver, RefArg sym, RefArg args);

extern Ref	GetVariable(RefArg contextFrame, RefArg varName, long* found = 0, int isArgFrame = 0);
extern void	SetVariable(RefArg contextFrame, RefArg varName, RefArg value);

#endif /* __NEWTONSCRIPT_H */

