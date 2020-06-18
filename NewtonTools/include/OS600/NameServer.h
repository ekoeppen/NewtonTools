/*
	File:		NameServer.h

	Copyright:	� 1992-1994 by Apple Computer, Inc., all rights reserved.

	Derived from v13 internal.

*/

#ifndef	__NAMESERVER_H
#define __NAMESERVER_H


#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef	__NEWTERRORS_H
#include "NewtErrors.h"
#endif

#ifndef	__USERPORTS_H
#include "UserPorts.h"
#endif

#ifndef	__OSERRORS_H
#include "OSErrors.h"
#endif

#ifndef __AEVENTS_H
#include "AEvents.h"
#endif

/*
	Following is a list of types that are registered with the NameServer.
*/
extern const char kTUPort[];

typedef ULong	TObjectName;

class TUNameServer
{
	public:
						TUNameServer();
						~TUNameServer();
		NewtonErr		RegisterName(char* name, char* type, ULong thing, ULong spec);
		NewtonErr		UnRegisterName(char* name, char* type);
		NewtonErr		WaitForRegister(char* name, char* type, ULong* thing, ULong* spec);
		NewtonErr		WaitForUnregister(char* name, char* type);
		NewtonErr		Lookup(char* name, char* type, ULong* thing, ULong* spec);

		NewtonErr		ResourceClaim(char* name, char* type, TObjectId ownerPortId, TObjectId applicationNameId);
		NewtonErr		ResourceUnclaim(char* name, char* type);
		NewtonErr		ResourcePassiveClaim(char* name, char* type, TObjectId ownerPortId, TObjectId applicationNameId);
		NewtonErr		ResourcePassiveUnclaim(char* name, char* type);


	private:
		TUPort			fNameServerPort;
		TUSharedMem*	fMsgName;
		TUSharedMem*	fMsgType;
};



//
// NameServerCommand's
//
typedef ULong NameServerCommand;
typedef ULong SystemEvent;

#define	kRegisterName				1
#define	kUnregisterName				2
#define	kWaitForRegister			3
#define	kWaitForUnregister			4
#define	kLookup						5
#define	k_DEBUGGING_DumpObjectName	6
#define	kRegisterForSystemEvent		7
#define	kUnRegisterForSystemEvent	8
#define	kSendSystemEvent			9
#define	kGestalt					10
#define	kResourceArbitration		11


// Name server message block definitions
//
// NOTE - if you change the size of these messages, verify that
// 		  kNameServerRequestSizeMax is set to the appropriate value!

class TNameServerRequest : public SingleObject
{
	public:
							TNameServerRequest();

		NameServerCommand 	fCommand;			// nameserver/systemEvent command
};


class TNameRequest : public TNameServerRequest
{
	public:
							TNameRequest();

		ULong	 			fThing;				// "thing" to register.  Is returned by lookup
		ULong				fSpec;				// another thing which is registered.  Also returned by lookup
		ULong				fParam1;			// Unused
		ULong				fParam2;			// Unused
		TObjectId			fObjectName;		// shared mem Id of object name C string
		TObjectId			fObjectType;		// shared mem Id of object type C string

};

class TSysEventRequest : public TNameServerRequest
{
	public:
							TSysEventRequest();

		SystemEvent			fTheEvent;
		TObjectId			fSysEventObjId;		// Object Id of port to send sys event to, or object Id of sys event shared mem message
		ULong				fSysEventTimeOut;	// time out used for async send of sys event message
		ULong				fSysEventSendFilter;// filter used for async send of sys event message
};


class TGestaltRequest : public TNameServerRequest
{
	public:
							TGestaltRequest();

		ULong				fSelector;			// indicates type of gestalt request
};


// Resource Arbitration Request types
#define	kResArbitrationClaim			1
#define	kResArbitrationUncliam			2
#define	kResArbitrationPassiveClaim		3
#define kResArbitrationPassiveUnclaim	4

class TResArbitrationRequest : public TNameRequest
{
	public:
							TResArbitrationRequest();

		ULong				fRequestType;		// indicates type of resource arbitration request (e.g. claim, unclaim)
		TObjectId			fOwnerPortId;		// Port Id of owner.  Required when claiming a resource
		TObjectId			fOwnerName;			// optionally shared mem Id of owner application (unicode, will be displayed to user)
};


class TNameServerReply : public SingleObject
{
	public:
							TNameServerReply();

		ULong	 			fThing;
		ULong				fSpec;
		NewtonErr			fResult;
};

#endif
