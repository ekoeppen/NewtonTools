/*
	File:		CommServices.h

	Contains:	Comm Service Identifiers

	Copyright:	� 1992-1994, 1996 by Apple Computer, Inc., all rights reserved.

	Derived from v6 internal of CommServicesExternal.h.

*/


#ifndef	__COMMSERVICES_H
#define __COMMSERVICES_H


/* --------------------------------------------------------------------------------------------------------------------

		Communications and Networking services in MP Junior ROM

		all other services (loaded) are named by owner
		Apple services are lower- and mixed-case
		3rd party services are all uppercase and registered with Apple

	-------------------------------------------------------------------------------------------------------------------- */

#ifndef FRAM

	#define kCMS_CapabilityType_ServiceId				'serv'			// "string" used as TCMService PROTOCOL serviceId capability type
	#define kCMS_CapabilityType_Version					'vern'			// "string" used as TCMService PROTOCOL version capability type
	#define kCMS_UnknownVersion							'zzzz'			// used as value for kCMS_CapabilityType_Version capability when version is undefined or unknown

	#define kCMSAppleTalkID					'atlk'
	#define kCMSFaxID						'faxs'
	#define kCMSModemID						'mods'
	#define	kCMSIrDA						'irda'
	#define	kCMSSlowIR						'slir'
	#define	kCMSSniffIR						'snif'
	#define	kCMSProbeIR						'pkir'
	#define	kCMSTVRemoteIR					'tvir'
	#define kCMSMNPID						'mnps'
	#define	kCMSBasicSerial					'ser '
	#define	kCMSAsyncSerial					'aser'
	#define	kCMSFramedAsyncSerial			'fser'
	#define kCMSLocalTalkID					'ltlk'

#endif //not FRAM


#define kCMSVAppleTalk					2
#define kCMSVMinorAppleTalk				0

#define kCMSVFax						2
#define kCMSVMinorFax					0

#define kCMSVModem						2
#define kCMSVMinorModem					0

#define	kCMSVIrDA						2
#define	kCMSVMinorIrDA					0

#define	kCMSVSlowIR						2
#define	kCMSVMinorSlowIR				0

#define	kCMSVSniffIR					2
#define	kCMSVMinorSniffIR				0

#define	kCMSVProbeIR					2
#define	kCMSVMinorProbeIR				0

#define	kCMSVTVRemoteIR					2
#define	kCMSVMinorTVRemoteIR			0

#define kCMSVMNP						2
#define kCMSVMinorMNP					0

#define	kCMSVBasicSerial				2
#define	kCMSVMinorBasicSerial			0

#define	kCMSVAsyncSerial				2
#define	kCMSVMinorAsyncSerial			0

#define	kCMSVFramedAsyncSerial			2
#define	kCMSVMinorFramedAsyncSerial		0

#define kCMSVLocalTalk					2
#define kCMSVMinorLocalTalk				0



#endif  //__COMMSERVICES_H

