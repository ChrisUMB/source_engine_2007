//===========================================================================
// Filename:	XMassiveAdClient.h
//
// Declaration file for the Massive AdClient. (External)
//
// Copyright (c) Microsoft Corp. All rights reserved.
//
//===========================================================================

#ifndef __MASSIVECLIENTCORE_H__
#define __MASSIVECLIENTCORE_H__

#include "XMassiveAdClientMediaTypes.h"

#ifdef __cplusplus

namespace MassiveAdClient3
{

// Forward Declaration
class CMassiveZoneManager;
class CRequestObject;

//===========================================================================
// XMassiveAdClient Class

class XMassiveAdClient
{
public:

	// Initialization and Instance Retriveal
	static XMassiveAdClient *Instance();
	static XMassiveAdClient *Initialize(IN const MAD_MASSIVE_INIT_STRUCT *initStruct);
	static DWORD Shutdown(IN OPTIONAL BOOL bWaitForResponse=true, IN OPTIONAL UINT uTimeout=0);
	static DWORD AbortShutdown();

	// Accessors
	static const DWORD GetLastError();
	static const MAD_STATE GetState();
	static const char *GetVersion();

	// Logging
	void static Log(IN MASSIVE_ENUM_LOG_LEVEL uLogLevel, IN const char *szObjectName, IN const char *szFormatedString, IN OPTIONAL ...);

	// Client Action Functions
	static DWORD Update(IN OPTIONAL BOOL bForceTick = false);
	static DWORD SuspendAll();
	static DWORD ResumeAll();
	static DWORD FlushImpressions();
		   
	static DWORD EnterZone(IN const char *szZoneName);
	static DWORD ExitZone(IN const char *szZoneName);

	// NetworkManager Accessors/Mutators
	static void SetMaxSendRate(IN SHORT uMaxSendRate);
	static void SetMaxReceiveRate(IN SHORT uMaxReceiveRate);

	// MultiPlayer
	static char *MPSessionCreate();
	static DWORD MPSessionJoin(IN const char *pszGUID);
	static DWORD MPSessionLeave(void);
	
	// Memory
	static void SetCustomMemoryFunctions(IN massiveMalloc m, IN massiveFree f);
	static DWORD SetCustomMemoryBuffer(IN BYTE *pbBuffer, IN INT ibufferSize);
	static DWORD ReleaseCustomMemoryBuffer();
};

}	//namespace MassiveAdClient3

#else
// C Interface

typedef struct _XMassiveAdClient XMassiveAdClient;  

XMassiveAdClient * APIENTRY XMassiveAdClientCreate(const MAD_MASSIVE_INIT_STRUCT *pInit);

DWORD APIENTRY XMassiveAdClientShutdown(BOOL bWaitForResponse, UINT uTimeout);
DWORD APIENTRY XMassiveAdClientAbortShutdown();

// Accessors
const DWORD APIENTRY XMassiveAdClientGetLastError();
const MAD_STATE APIENTRY XMassiveAdClientGetState();
const char * APIENTRY XMassiveAdClientGetVersion();

// Logging
void APIENTRY XMassiveAdClientLog(MASSIVE_ENUM_LOG_LEVEL eLevel, const char *szName, const char *szText);

// Client Action Functions
int APIENTRY XMassiveAdClientUpdate(BOOL bForceUpdate);

DWORD APIENTRY XMassiveAdClientSuspendAll();
DWORD APIENTRY XMassiveAdClientResumeAll();
DWORD APIENTRY XMassiveAdClientFlushImpressions();
	   
DWORD APIENTRY XMassiveAdClientEnterZone(const char *szZoneName);
DWORD APIENTRY XMassiveAdClientExitZone(const char *szZoneName);

// NetworkManager Accessors/Mutators
void APIENTRY XMassiveAdClientSetMaxSendRate(SHORT uMaxSendRate);
void APIENTRY XMassiveAdClientSetMaxReceiveRate(SHORT uMaxReceiveRate);

// MultiPlayer
char * APIENTRY XMassiveAdClientMPSessionCreate();
DWORD APIENTRY XMassiveAdClientMPSessionJoin(const char *pszGUID);
DWORD APIENTRY XMassiveAdClientMPSessionLeave();

// Memory
void APIENTRY XMassiveAdClientSetCustomMemoryFunctions(massiveMalloc m, massiveFree f);
DWORD APIENTRY XMassiveAdClientSetCustomMemoryBuffer(signed char *p_memoryBuffer, UINT i32_bufferSize);
DWORD APIENTRY XMassiveAdClientReleaseCustomMemoryBuffer();


#endif


#endif	// __MASSIVECLIENTCORE_H__
