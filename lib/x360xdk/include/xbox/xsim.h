//--------------------------------------------------------------------------------------
// XSim.h
// 
// C-Style API for XSim
// 
// Microsoft Game Studios Tools and Technology Group
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once

#ifndef _XSIM_H_
#define _XSIM_H_

// Putting these here so that XSim clients only need to include XSim.h

#ifndef XSIM_INTERNAL
#include <xbdm.h>
#endif
#include "XSimError.h"

#ifdef __cplusplus
extern "C" {
#endif

const DWORD DEFAULT_COMPONENT_FRAMERATE = 60;
const DWORD DM_AUTOMATION_INPUTQUEUE_LENGTH = 100;
const DWORD IO_BUFFER_SIZE = 16384; // Buffer size is one Xbox HD sector.

//------------------------------------------------------------------------------
// Handle definition
//------------------------------------------------------------------------------
typedef HANDLE XSIMHANDLE;

//------------------------------------------------------------------------------
// General component status
//------------------------------------------------------------------------------
typedef enum _XSIM_COMPONENTSTATUS {
    XSIM_COMPONENTSTATUS_IDLE,
    XSIM_COMPONENTSTATUS_RUNNING
} XSIM_COMPONENTSTATUS;

//------------------------------------------------------------------------------
// Synchronization mode used by TextSequencePlayer
//------------------------------------------------------------------------------
typedef enum _XSIM_SYNCHMODE {
    XSIM_SYNCHMODE_FRAME  = 0x00000001,
    XSIM_SYNCHMODE_TIME   = 0x00000002
} XSIM_SYNCHMODE;

//------------------------------------------------------------------------------
// Structs used for Random Input Player button press timings
//------------------------------------------------------------------------------
typedef struct _XSIM_BUTTONPRESSATTRIBUTES {
      DWORD dwIntervalMinMs;
      DWORD dwIntervalMaxMs;
      DWORD dwHoldTimeMinMs; 
      DWORD dwHoldTimeMaxMs;
} XSIM_BUTTONPRESSATTRIBUTES;

typedef struct _XSIM_CONTROLLERPRESSATTRIBUTES {
      XSIM_BUTTONPRESSATTRIBUTES DpadUp;
      XSIM_BUTTONPRESSATTRIBUTES DpadDown;
      XSIM_BUTTONPRESSATTRIBUTES DpadLeft;
      XSIM_BUTTONPRESSATTRIBUTES DpadRight;
      XSIM_BUTTONPRESSATTRIBUTES Start;
      XSIM_BUTTONPRESSATTRIBUTES Back;
      XSIM_BUTTONPRESSATTRIBUTES LeftThumb;
      XSIM_BUTTONPRESSATTRIBUTES RightThumb;
      XSIM_BUTTONPRESSATTRIBUTES LeftShoulder;
      XSIM_BUTTONPRESSATTRIBUTES RightShoulder;
      XSIM_BUTTONPRESSATTRIBUTES A;
      XSIM_BUTTONPRESSATTRIBUTES B;
      XSIM_BUTTONPRESSATTRIBUTES X;
      XSIM_BUTTONPRESSATTRIBUTES Y;
	  XSIM_BUTTONPRESSATTRIBUTES XBox360Button;
      XSIM_BUTTONPRESSATTRIBUTES RightTrigger;
      XSIM_BUTTONPRESSATTRIBUTES LeftTrigger;
      XSIM_BUTTONPRESSATTRIBUTES ThumbLX;
      XSIM_BUTTONPRESSATTRIBUTES ThumbLY;
      XSIM_BUTTONPRESSATTRIBUTES ThumbRX;
      XSIM_BUTTONPRESSATTRIBUTES ThumbRY;
} XSIM_CONTROLLERPRESSATTRIBUTES;

//------------------------------------------------------------------------------
// User index bits used for building user index masks
//------------------------------------------------------------------------------
typedef enum _XSIM_USERINDEXMASK {
	XSIM_USERINDEXMASK_0   = 0x00000001,
	XSIM_USERINDEXMASK_1   = 0x00000002,
	XSIM_USERINDEXMASK_2   = 0x00000004,
	XSIM_USERINDEXMASK_3   = 0x00000008,
	XSIM_USERINDEXMASK_ALL = 0x0000000F,
} XSIM_USERINDEXMASK;

//------------------------------------------------------------------------------
// XSim Functions
//------------------------------------------------------------------------------
// Initialize/Uninitialize
HRESULT WINAPI XSimInitialize(DWORD dwComponentFrameRate);
HRESULT WINAPI XSimUninitialize();

// Take/Return control from/to the physical controller
HRESULT WINAPI XSimAcquireControl(IN DWORD dwUserIndexMask);
HRESULT WINAPI XSimReturnControl(IN DWORD dwUserIndexMask);

// Player creation
HRESULT WINAPI XSimCreateRandomInputPlayer(OUT XSIMHANDLE* phXSimHandle);
HRESULT WINAPI XSimCreateRandomStatePlayer(IN LPCSTR lpFileName, OUT XSIMHANDLE* phXSimHandle);
HRESULT WINAPI XSimCreateFilePlayer(IN LPCSTR lpFileName, IN XSIM_SYNCHMODE eSynchMode, OUT XSIMHANDLE* phXSimHandle);
HRESULT WINAPI XSimCreateTextSequencePlayer(IN LPCSTR lpPlaybackString, IN XSIM_SYNCHMODE eSynchMode, IN DWORD dwDefaultPlaybackRate, 
											OUT XSIMHANDLE* phXSimHandle);
// Recorder creation
HRESULT WINAPI XSimCreateFileRecorder(IN LPCSTR lpFileName, OUT XSIMHANDLE* phXSimHandle);

// Handle releasing
HRESULT WINAPI XSimCloseHandle(IN XSIMHANDLE hXSimHandle);

// Start/Stop player(s)
HRESULT WINAPI XSimStartPlayer(IN XSIMHANDLE hXSimHandle, IN DWORD dwUserIndex);
HRESULT WINAPI XSimStopPlayer(IN DWORD dwUserIndex);

// Start/Stop recorder(s)
HRESULT WINAPI XSimStartRecorder(IN XSIMHANDLE hXSimHandle, IN DWORD dwUserIndex);
HRESULT WINAPI XSimStopRecorder(IN DWORD dwUserIndex);

// Player/Recorder status
HRESULT WINAPI XSimGetPortPlayerStatus(IN DWORD dwUserIndex, OUT XSIM_COMPONENTSTATUS* pStatus);
HRESULT WINAPI XSimGetPortRecorderStatus(IN DWORD dwUserIndex, OUT XSIM_COMPONENTSTATUS* pStatus);

// Random Input Player settings
HRESULT WINAPI XSimSetRandomInputPlayerConnectAttributes(IN XSIMHANDLE hXSimHandle, IN BOOL bStartConnected,
  														 IN DWORD dwDisconnectIntervalMin, IN DWORD dwDisconnectIntervalMax,
  														 IN DWORD dwReconnectIntervalMin,  IN DWORD dwReconnectIntervalMax);
HRESULT WINAPI XSimGetRandomInputPlayerPressAttributes(IN XSIMHANDLE hXSimHandle, OUT XSIM_CONTROLLERPRESSATTRIBUTES* pPressAttributes);
HRESULT WINAPI XSimSetRandomInputPlayerPressAttributes(IN XSIMHANDLE hXSimHandle, IN XSIM_CONTROLLERPRESSATTRIBUTES* pPressAttributes);

// Random State Player state control
HRESULT WINAPI XSimGetRandomStatePlayerState(IN XSIMHANDLE hXSimHandle, IN DWORD dwBufferSize, OUT LPSTR lpStateName);
HRESULT WINAPI XSimSetRandomStatePlayerState(IN XSIMHANDLE hXSimHandle, IN LPCSTR lpStateName);

#ifdef __cplusplus
}
#endif


#endif 
