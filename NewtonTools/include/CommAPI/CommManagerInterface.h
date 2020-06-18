/*
	File:		CommManagerInterface.h

	Contains:	CommManager interface

	Copyright:	� 1992-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v3 internal of CommManagerInterfaceExternal.h.

*/

#ifndef	__COMMMANAGERINTERFACE_H
#define __COMMMANAGERINTERFACE_H



#ifndef __NEWTERRORS_H
	#include "NewtErrors.h"
#endif

#ifndef FRAM

	#ifndef __AEVENTS_H
		#include "AEvents.h"
	#endif

	#ifndef	__SYSTEMEVENTSH
		#include "SystemEvents.h"
	#endif

	#ifndef	__NEWTON_H
		#include "Newton.h"
	#endif

	#ifndef	__KERNELTYPES_H
		#include "KernelTypes.h"
	#endif

	#ifndef __OPTIONARRAY_H
		#include "OptionArray.h"
	#endif

	#ifndef	__COMMOPTIONS_H
		#include "CommOptions.h"
	#endif


	#ifndef __COMMSERVICES_H
		#include "CommServices.h"
	#endif

	class TOptionArray;
	class TEndpoint;

#endif // notFRAM



#define kCMErrorBase					(ERRBASE_COMMMGR)

#define kCMErr_AlreadyInitialized		(kCMErrorBase)
#define kCMErr_NoSuchCommand			(kCMErrorBase - 1)
#define kCMErr_UnknownService			(kCMErrorBase - 2)
#define kCMErr_ServiceExists			(kCMErrorBase - 3)
#define kCMErr_NoServiceSpecified		(kCMErrorBase - 4)		// no service specified in the TOptionArray
#define kCMErr_ServiceNotFound			(kCMErrorBase - 5)		// no service registered of the type specified in the TOptionArray
#define kCMErr_NoEndPointExists			(kCMErrorBase - 6)		// usually returned when CMStartService should have been called
#define kCMErr_NoPublicPortExists		(kCMErrorBase - 7)		// usually returned when CMGetEndPoint should have been called
#define kCMErr_NoKnownLastDevice		(kCMErrorBase - 8)		// no known last connected device
#define kCMErr_TupleNotDeviceId			(kCMErrorBase - 9)		// tuple received, but not device id tuple
#define kCMErr_ExpectedServiceInfoRsp	(kCMErrorBase - 10)		// service info response tuple expected
#define kCMErr_UnsupportedService		(kCMErrorBase - 11)		// unsupported service, can only load packages
#define kCMErr_SCPLoadInProgress		(kCMErrorBase - 12)		// SCP load is in progress, cannot issue another
#define kCMErr_SCPLoadNotAvailable		(kCMErrorBase - 13)		// SCP load call is not supported on this machine
#define kCMErr_BadSpeedResponseTuple	(kCMErrorBase - 14)		// can process this speed
#define kCMErr_NoKnownLastPackageLoaded	(kCMErrorBase - 15)		// no package was previously loaded through SCPLoader



#ifndef FRAM

/* --------------------------------------------------------------------------------------------------------------------
	TConnectedDevice

	object describing last known connected device
	use CMGetLastDevice to return this structure

   -------------------------------------------------------------------------------------------------------------------- */

#define kConnectedToSCC			(1)
#define kConnectedToPCMCIA		(2)

class TConnectedDevice
{
	public:

		TTime		fLastConnectTime;	// when device was last known to be connected
		ULong		fConnectedTo;		// physical object device is connected to
		ULong		fDeviceType;		// device type
		ULong		fManufacturer;		// manufacturer
		ULong		fVersion;			// version
};


/* --------------------------------------------------------------------------------------------------------------------
					TDeviceIdNotification
   -------------------------------------------------------------------------------------------------------------------- */

class TDeviceIdNotification : public TAESystemEvent
{
	public:
		TConnectedDevice	fConnectedDevice;
};


/* --------------------------------------------------------------------------------------------------------------------
	TServiceInfo

	information about how to talk to a particular service, returned from
	CMStartService (see below).

   -------------------------------------------------------------------------------------------------------------------- */

#define kServiceByPort				(0x01)

class TServiceInfo
{
	public:

		TObjectId	GetPortId()			{ return fPortId; }
		ULong		GetServiceId()		{ return fServiceId; }

		void		SetPortId(TObjectId portId);
		void		SetServiceId(ULong serviceId);

	private:

		UByte		fFlags;			// what service is returning
		TObjectId	fPortId;		// port of service
		ULong		fServiceId;		// service Id
};


/* --------------------------------------------------------------------------------------------------------------------

	InitializeCommManager
	initialize the CommManager, called once by the OS at boot time

	CMStartService(TOptionArray* options, TServiceInfo* serviceInfo):

		start the service described in the TOptionArray,
		return the TObjectId of the port associated with
		the service.

	CMGetEndPoint(TOptionArray* options, TEndpoint** endPoint, Boolean handleAborts);

		start the service described in the TOptionArray,
		return the TEndpoint representing the interface
		to the service.  If handleAborts is TRUE, a user
		abort handler is automatically installed

	CMStartServiceInternal(TOptionArray* options, TServiceInfo* serviceInfo)

		same as CMStartService, however used internally
		by tools to start other tools

	CMGetLastDevice(TConnectedDevice* lastDevice)

		returns a TConnectedDevice object, describing the last
		known connected device and the time it was connected
		returns kCMErr_NoKnownLastDevice when no connected device
		is known

	CMSetLastDevice(TConnectedDevice* lastDevice)

		sets last connected device to the one specified
		in lastDevice.  not necessary to set fLastConnectTime
		in lastDevice, call sets it

	CMSCPLoad(ULong waitPeriod, ULong tries = 1, ULong filter = kAnySCPDevice)

		tweak the serial line looking for a SCP aware device.
		the waitPeriod parameter is the number of milliseconds
		to wait on the device.
		tries is the number of times to wait on device, applying
		waitPeriod millisecond wait for each try.
		if filter is set to kSCPJustIdentify,
		just try to identify the device (a subsequent
		call to CMGetLastDevice will tell you what device
		has been identified).  if filter is set to
		kSCPLoadAnyDevice, attempt to load a package from
		any device connected and at least provide identification
		information if device supports it.  if filter is set
		to any other id, attempt to load a package only if
		that device matches the id

	NewtonErr CMGetServiceVersion(ULong serviceId, ULong* version)

		given a service identifier, return the version
		if no such service exists, the error kCMErr_UnknownService
		is returned
		version must be seeded:
		-set to kFindNewestVersion to return newest version
		-set to specific version to find that specific version
		-set to 0 to find any version (normally used just to see
		if some service exists)

   -------------------------------------------------------------------------------------------------------------------- */


// client calls�
NewtonErr CMStartService(TOptionArray* options, TServiceInfo* serviceInfo);
NewtonErr CMGetEndpoint(TOptionArray* options, TEndpoint** endPoint, Boolean handleAborts = false);
NewtonErr CMGetLastDevice(TConnectedDevice* lastDevice);
NewtonErr CMSetLastDevice(TConnectedDevice* lastDevice);

#define kFindNewestVersion		(0xFFFFFFFF)

NewtonErr CMGetServiceVersion(ULong serviceId, ULong* version);

#define kSCPJustIdentifiy		(0)				// just try to identify device
#define kSCPLoadAnyDevice		'****'			// wildcard, attempt to load any device

NewtonErr CMSCPLoad(ULong waitPeriod, ULong tries = 1, ULong filter = kSCPLoadAnyDevice);

// internal tool calls�
NewtonErr CMStartServiceInternal(TOptionArray* options, TServiceInfo* serviceInfo);


#endif // FRAM



#endif  //__COMMMANAGERINTERFACE_H
