/*****************************************************************************
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       xmedia.h
 *  Content:    The definitions for XMedia public APIs.
 *
 ****************************************************************************/

#ifndef __XMEDIA_INCLUDED__
#define __XMEDIA_INCLUDED__

#pragma once

#include <xtl.h>
#include <xaudio.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma warning(push)
#pragma warning(disable:4201)

//
// Miscellaneous defines.
//

#define XMEDIA_INLINE                   __inline
#define XMEDIA_SAFE_RELEASE(p)          {if (p) {(p)->Release(); (p) = NULL;}}

//
// Callback used with IXMediaXmvPlayer::SetCallback() API.
//

typedef
VOID
(*XMEDIA_XMV_CALLBACK)(
    IN OPTIONAL PVOID pvContext
    );

//
// Callbacks used with user I/O routines.
//

typedef
HRESULT
(*XMEDIA_USER_STREAM_READ_CALLBACK)(
    IN OPTIONAL PVOID pvContext,
    IN ULONGLONG ullOffset,
    IN PVOID pvBuffer,
    IN DWORD dwBytesToRead,
    OUT DWORD* pdwBytesRead
    );

typedef
HRESULT
(*XMEDIA_USER_STREAM_WRITE_CALLBACK)(
    IN OPTIONAL PVOID pvContext,
    IN ULONGLONG ullOffset,
    IN PVOID pvBuffer,
    IN DWORD dwBytesToWrite,
    OUT DWORD* pdwBytesWritten
    );

//
// HRESULTs returned by IXMediaXmvPlayer::GetNextFrame() API.
//

#define XMEDIA_WARNING                  0x10000000
#define XMEDIA_FACILITY                 0x06660000
#define XMEDIA_W_EOF                    _HRESULT_TYPEDEF_(XMEDIA_WARNING | XMEDIA_FACILITY | ERROR_HANDLE_EOF)
#define XMEDIA_W_NO_DATA                _HRESULT_TYPEDEF_(XMEDIA_WARNING | XMEDIA_FACILITY | ERROR_NO_DATA)

//
// Flags used with Create method.
//

#define XMEDIA_CREATE_BACKGROUND_MUSIC  0x00000001
#define XMEDIA_CREATE_CPU_AFFINITY      0x00000002
#define XMEDIA_CREATE_SHARE_IO_CACHE    0x00000004
#define XMEDIA_CREATE_FOR_LOOP          0x00000008

//
// Flags used with Play, GetNextFrame, and RenderNextFrame methods.
//

#define XMEDIA_PLAY_DISABLE_AV_SYNC     0x00000001
#define XMEDIA_PLAY_LOOP                0x00000002
#define XMEDIA_PLAY_REPEAT_FRAME        0x00000004

//
// Flags used with Stop method.
//

#define XMEDIA_STOP_IMMEDIATE           0x00000000
#define XMEDIA_STOP_LOOP                0x00000001

//
// XMedia player status.
//

typedef enum
{
    XMEDIA_PLAYER_IDLE = 1,
    XMEDIA_PLAYER_BUFFERING,
    XMEDIA_PLAYER_PLAYING,
    XMEDIA_PLAYER_PAUSING,
    XMEDIA_PLAYER_PAUSED,
    XMEDIA_PLAYER_STOPPING,
    XMEDIA_PLAYER_STOPPED,
    XMEDIA_PLAYER_TERMINATING
} XMEDIA_PLAYER_STATUS, *PXMEDIA_PLAYER_STATUS;

//
// XMedia callback notification types.
//

typedef enum
{
    XMEDIA_NOTIFY_END_OF_FRAME = 1,
    XMEDIA_NOTIFY_STATE_CHANGE,
    XMEDIA_NOTIFY_BEGIN_SCENE,
    XMEDIA_NOTIFY_END_SCENE
} XMEDIA_CALLBACK_TYPE, *PXMEDIA_CALLBACK_TYPE;

//
// XMedia player creation types.
//

typedef enum
{
    XMEDIA_CREATE_FROM_FILE = 1,
    XMEDIA_CREATE_FROM_HANDLE,
    XMEDIA_CREATE_FROM_MEMORY,
    XMEDIA_CREATE_FROM_USER_IO
} XMEDIA_CREATE_TYPE, *PXMEDIA_CREATE_TYPE;

//
// XMedia video formats.
//

typedef enum
{
    XMEDIA_VIDEO_FORMAT_I420 = 1,
} XMEDIA_VIDEO_FORMAT, *PXMEDIA_VIDEO_FORMAT;

//
// XMedia player A/V stream numbers.
//

typedef enum
{
    XMEDIA_STREAM_ID_USE_DEFAULT = 0,
    XMEDIA_STREAM_ID_DONT_USE = 0xffffffff
} XMEDIA_STREAM_ID, *PXMEDIA_STREAM_ID;

//
// Audio and video descriptors.
//

typedef struct _XMEDIA_AUDIO_DESCRIPTOR
{
    DWORD dwNumberOfChannels;
    DWORD dwSampleRate;
    DWORD dwBitsPerSample;
    DWORD dwClipDuration;
} XMEDIA_AUDIO_DESCRIPTOR, *PXMEDIA_AUDIO_DESCRIPTOR;

typedef struct _XMEDIA_VIDEO_DESCRIPTOR
{
    DWORD dwWidth;
    DWORD dwHeight;
    FLOAT fFrameRate;
    DWORD dwClipDuration;
} XMEDIA_VIDEO_DESCRIPTOR, *PXMEDIA_VIDEO_DESCRIPTOR;

//
// Media playback status.
//

typedef struct _XMEDIA_PLAYBACK_STATUS
{
    XMEDIA_PLAYER_STATUS Status;
    LONG lDuration;
} XMEDIA_PLAYBACK_STATUS, *PXMEDIA_PLAYBACK_STATUS;

//
// Video screen (video playback surface) vertex definitions.
//

typedef struct _XMEDIA_VIDEO_SCREEN_VERTEX
{
    FLOAT fX, fY, fZ, fTu, fTv;
} XMEDIA_VIDEO_SCREEN_VERTEX, *PXMEDIA_VIDEO_SCREEN_VERTEX;

typedef union _XMEDIA_VIDEO_SCREEN
{
    struct
    {
        XMEDIA_VIDEO_SCREEN_VERTEX upperLeft;
        XMEDIA_VIDEO_SCREEN_VERTEX upperRight;
        XMEDIA_VIDEO_SCREEN_VERTEX lowerLeft;
        XMEDIA_VIDEO_SCREEN_VERTEX lowerRight;
    };
    XMEDIA_VIDEO_SCREEN_VERTEX aVertices[4];
} XMEDIA_VIDEO_SCREEN, *PXMEDIA_VIDEO_SCREEN;

//
// Video frame used with GetNextFrame method.
//

typedef struct _XMEDIA_VIDEO_FRAME
{
    XMEDIA_VIDEO_FORMAT videoFormat;
    DWORD dwFlags;
    LONG lTimeToPresent;

    union
    {    
        struct
        {
            PVOID pvYBuffer;
            PVOID pvUBuffer;
            PVOID pvVBuffer;
            DWORD dwYBufferSize;
            DWORD dwUBufferSize;
            DWORD dwVBufferSize;
            DWORD dwYPitch;
            DWORD dwUPitch;
            DWORD dwVPitch;
        } i420;

    };
} XMEDIA_VIDEO_FRAME, *PXMEDIA_VIDEO_FRAME;

//
// Paramters used with XMV player Create method.
//

typedef struct _XMEDIA_XMV_CREATE_PARAMETERS
{
    XMEDIA_CREATE_TYPE createType;
    DWORD dwFlags;
    DWORD dwAudioDecoderCpu;
    DWORD dwVideoDecoderCpu;
    DWORD dwAudioRendererCpu;
    DWORD dwVideoRendererCpu;
    DWORD dwAudioStreamId;
    DWORD dwVideoStreamId;

    union
    {    
        struct
        {
            LPCSTR szFileName;
            DWORD dwIoBlockSize;
            DWORD dwIoBlockCount;
            DWORD dwIoBlockJitter;
        } createFromFile;

        struct
        {
            HANDLE handle;
            ULONGLONG ullOffset;
            ULONGLONG ullLength;
            DWORD dwIoBlockSize;
            DWORD dwIoBlockCount;
            DWORD dwIoBlockJitter;
        } createFromHandle;

        struct
        {
            PVOID pvBuffer;
            DWORD dwBufferSize;
        } createFromMemory;

        struct
        {
            XMEDIA_USER_STREAM_READ_CALLBACK pfnAudioStreamReadCallback;
            XMEDIA_USER_STREAM_READ_CALLBACK pfnVideoStreamReadCallback;
            PVOID pvAudioStreamContext;
            PVOID pvVideoStreamContext;
        } createFromUserIo;
    };
} XMEDIA_XMV_CREATE_PARAMETERS, *PXMEDIA_XMV_CREATE_PARAMETERS;

//
// IXMediaXmvPlayer interface.
//

typedef struct IXMediaXmvPlayer IXMediaXmvPlayer;

#ifdef __cplusplus

//
// IXMediaXmvPlayer C++ interface definition.
//

struct IXMediaXmvPlayer
{
    DWORD
    WINAPI
    AddRef();

    DWORD
    WINAPI
    Release();

    HRESULT
    WINAPI
    GetNextFrame(
        IN OUT PXMEDIA_VIDEO_FRAME pVideoFrame
        );

    HRESULT
    WINAPI
    RenderNextFrame(
        IN DWORD dwFlags,
        OUT OPTIONAL PLONG plTimeToPresent
        );

    HRESULT
    WINAPI
    SetRectangle(
        IN PRECT pRect
        );

    HRESULT
    WINAPI
    GetRectangle(
        IN OUT PRECT pRect
        );

    HRESULT
    WINAPI
    SetVideoScreen(
        IN PXMEDIA_VIDEO_SCREEN pScreen
        );

    HRESULT
    WINAPI
    GetVideoScreen(
        IN OUT PXMEDIA_VIDEO_SCREEN pScreen
        );

    HRESULT
    WINAPI
    GetAudioDescriptor(
        IN OUT PXMEDIA_AUDIO_DESCRIPTOR pAudioDescriptor
        );

    HRESULT
    WINAPI
    GetVideoDescriptor(
        IN OUT PXMEDIA_VIDEO_DESCRIPTOR pVideoDescriptor
        );

    HRESULT
    WINAPI
    Play(
        IN DWORD dwFlags,
        IN OPTIONAL PXOVERLAPPED pOverlapped
        );

    HRESULT
    WINAPI
    Pause();

    HRESULT
    WINAPI
    Resume();

    HRESULT
    WINAPI
    Stop(
        IN DWORD dwFlags
        );

    HRESULT
    WINAPI
    Seek(
        IN DWORD dwSeekOffset,
        OUT OPTIONAL DWORD* pdwSetOffset
        );

    HRESULT
    WINAPI
    SetPlaySpeed(
	IN FLOAT fPlaySpeed
	);

    HRESULT
    WINAPI
    GetStatus(
        IN OUT PXMEDIA_PLAYBACK_STATUS pStatus
        );

    HRESULT
    WINAPI
    GetSourceVoice(
        OUT IXAudioSourceVoice** ppSourceVoice
        );

    HRESULT
    WINAPI
    SetCallback(
        IN XMEDIA_CALLBACK_TYPE Type,
        IN XMEDIA_XMV_CALLBACK pfnCallback,
        IN OPTIONAL PVOID pvContext
        );
};

#endif // __cplusplus

//
// IXMediaXmvPlayer interface create methods.
//

HRESULT
WINAPI
XMediaCreateXmvPlayer(
    IN IDirect3DDevice9* pD3dDevice,
    IN PXMEDIA_XMV_CREATE_PARAMETERS pCreateParameters,
    OUT IXMediaXmvPlayer** ppPlayer
    );

HRESULT
WINAPI
XMediaCreateXmvPlayerFromFile(
    IN IDirect3DDevice9* pD3dDevice,
    IN LPCSTR szFileName,
    OUT IXMediaXmvPlayer** ppPlayer
    );

HRESULT
WINAPI
XMediaCreateXmvPlayerFromHandle(
    IN IDirect3DDevice9* pD3dDevice,
    IN HANDLE handle,
    IN ULONGLONG ullOffset,
    IN ULONGLONG ullLength,
    OUT IXMediaXmvPlayer** ppPlayer
    );

HRESULT
WINAPI
XMediaCreateXmvPlayerFromMemory(
    IN IDirect3DDevice9* pD3dDevice,
    IN PVOID pvBuffer,
    IN DWORD dwBufferSize,
    OUT IXMediaXmvPlayer** ppPlayer
    );

HRESULT
WINAPI
XMediaCreateXmvPlayerFromUserIo(
    IN IDirect3DDevice9* pD3dDevice,
    IN XMEDIA_USER_STREAM_READ_CALLBACK pfnAudioStreamReadCallback,
    IN XMEDIA_USER_STREAM_READ_CALLBACK pfnVideoStreamReadCallback,
    IN OPTIONAL PVOID pvAudioStreamContext,
    IN OPTIONAL PVOID pvVideoStreamContext,
    OUT IXMediaXmvPlayer** ppPlayer
    );

//
// IXMediaXmvPlayer C interface definition.
//

DWORD
WINAPI
IXMediaXmvPlayer_AddRef(
    IN IXMediaXmvPlayer* pPlayer
    );

DWORD
WINAPI
IXMediaXmvPlayer_Release(
    IN IXMediaXmvPlayer* pPlayer
    );

HRESULT
WINAPI
IXMediaXmvPlayer_GetNextFrame(
    IN IXMediaXmvPlayer* pPlayer,
    IN OUT PXMEDIA_VIDEO_FRAME pVideoFrame
    );

HRESULT
WINAPI
IXMediaXmvPlayer_RenderNextFrame(
    IN IXMediaXmvPlayer* pPlayer,
    IN DWORD dwFlags,
    OUT OPTIONAL PLONG plTimeToPresent
    );

HRESULT
WINAPI
IXMediaXmvPlayer_SetRectangle(
    IN IXMediaXmvPlayer* pPlayer,
    IN PRECT pRect
    );

HRESULT
WINAPI
IXMediaXmvPlayer_GetRectangle(
    IN IXMediaXmvPlayer* pPlayer,
    IN OUT PRECT pRect
    );

HRESULT
WINAPI
IXMediaXmvPlayer_SetVideoScreen(
    IN IXMediaXmvPlayer* pPlayer,
    IN PXMEDIA_VIDEO_SCREEN pScreen
    );

HRESULT
WINAPI
IXMediaXmvPlayer_GetVideoScreen(
    IN IXMediaXmvPlayer* pPlayer,
    IN OUT PXMEDIA_VIDEO_SCREEN pScreen
    );

HRESULT
WINAPI
IXMediaXmvPlayer_GetAudioDescriptor(
    IN IXMediaXmvPlayer* pPlayer,
    IN OUT PXMEDIA_AUDIO_DESCRIPTOR pAudioDescriptor
    );

HRESULT
WINAPI
IXMediaXmvPlayer_GetVideoDescriptor(
    IN IXMediaXmvPlayer* pPlayer,
    IN OUT PXMEDIA_VIDEO_DESCRIPTOR pVideoDescriptor
    );

HRESULT
WINAPI
IXMediaXmvPlayer_Play(
    IN IXMediaXmvPlayer* pPlayer,
    IN DWORD dwFlags,
    IN OPTIONAL PXOVERLAPPED pOverlapped
    );

HRESULT
WINAPI
IXMediaXmvPlayer_Pause(
    IN IXMediaXmvPlayer* pPlayer
    );

HRESULT
WINAPI
IXMediaXmvPlayer_Resume(
    IN IXMediaXmvPlayer* pPlayer
    );

HRESULT
WINAPI
IXMediaXmvPlayer_Stop(
    IN IXMediaXmvPlayer* pPlayer,
    IN DWORD dwFlags
    );

HRESULT
WINAPI
IXMediaXmvPlayer_Seek(
    IN IXMediaXmvPlayer* pPlayer,
    IN DWORD dwSeekOffset,
    OUT OPTIONAL DWORD* pdwSetOffset
    );

HRESULT
WINAPI
IXMediaXmvPlayer_SetPlaySpeed(
    IN IXMediaXmvPlayer* pPlayer,
    IN FLOAT fPlaySpeed
    );

HRESULT
WINAPI
IXMediaXmvPlayer_GetStatus(
    IN IXMediaXmvPlayer* pPlayer,
    IN OUT PXMEDIA_PLAYBACK_STATUS pStatus
    );

HRESULT
WINAPI
IXMediaXmvPlayer_GetSourceVoice(
    IN IXMediaXmvPlayer* pPlayer,
    OUT IXAudioSourceVoice** ppSourceVoice
    );

HRESULT
WINAPI
IXMediaXmvPlayer_SetCallback(
    IN IXMediaXmvPlayer* pPlayer,
    IN XMEDIA_CALLBACK_TYPE Type,
    IN XMEDIA_XMV_CALLBACK pfnCallback,
    IN OPTIONAL PVOID pvContext
    );

//
// XLaunchDvdPlayer API definition.
//

VOID
WINAPI
XLaunchDvdPlayer();

#ifdef __cplusplus

//
// IXMediaXmvPlayer C++ interface definition.
//

XMEDIA_INLINE
DWORD
WINAPI
IXMediaXmvPlayer::AddRef()
{
    return IXMediaXmvPlayer_AddRef(this);
}

XMEDIA_INLINE
DWORD
WINAPI
IXMediaXmvPlayer::Release()
{
    return IXMediaXmvPlayer_Release(this);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::GetNextFrame(
    IN OUT PXMEDIA_VIDEO_FRAME pVideoFrame
    )
{
    return IXMediaXmvPlayer_GetNextFrame(this, pVideoFrame);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::RenderNextFrame(
    IN DWORD dwFlags,
    OUT OPTIONAL PLONG plTimeToPresent
    )
{
    return IXMediaXmvPlayer_RenderNextFrame(this, dwFlags, plTimeToPresent);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::SetRectangle(
    IN PRECT pRect
    )
{
    return IXMediaXmvPlayer_SetRectangle(this, pRect);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::GetRectangle(
    IN OUT PRECT pRect
    )
{
    return IXMediaXmvPlayer_GetRectangle(this, pRect);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::SetVideoScreen(
    IN PXMEDIA_VIDEO_SCREEN pScreen
    )
{
    return IXMediaXmvPlayer_SetVideoScreen(this, pScreen);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::GetVideoScreen(
    IN OUT PXMEDIA_VIDEO_SCREEN pScreen
    )
{
    return IXMediaXmvPlayer_GetVideoScreen(this, pScreen);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::GetAudioDescriptor(
    IN OUT PXMEDIA_AUDIO_DESCRIPTOR pAudioDescriptor
    )
{
    return IXMediaXmvPlayer_GetAudioDescriptor(this, pAudioDescriptor);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::GetVideoDescriptor(
    IN OUT PXMEDIA_VIDEO_DESCRIPTOR pVideoDescriptor
    )
{
    return IXMediaXmvPlayer_GetVideoDescriptor(this, pVideoDescriptor);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::Play(
    IN DWORD dwFlags,
    IN OPTIONAL PXOVERLAPPED pOverlapped
    )
{
    return IXMediaXmvPlayer_Play(this, dwFlags, pOverlapped);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::Pause()
{
    return IXMediaXmvPlayer_Pause(this);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::Resume()
{
    return IXMediaXmvPlayer_Resume(this);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::Stop(
    IN DWORD dwFlags
    )
{
    return IXMediaXmvPlayer_Stop(this, dwFlags);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::Seek(
    IN DWORD dwSeekOffset,
    OUT OPTIONAL DWORD* pdwSetOffset
    )
{
    return IXMediaXmvPlayer_Seek(this, dwSeekOffset, pdwSetOffset);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::SetPlaySpeed(
    IN FLOAT fPlaySpeed
    )
{
    return IXMediaXmvPlayer_SetPlaySpeed(this, fPlaySpeed);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::GetStatus(
    IN OUT PXMEDIA_PLAYBACK_STATUS pStatus
    )
{
    return IXMediaXmvPlayer_GetStatus(this, pStatus);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::GetSourceVoice(
    OUT IXAudioSourceVoice** ppSourceVoice
    )
{
    return IXMediaXmvPlayer_GetSourceVoice(this, ppSourceVoice);
}

XMEDIA_INLINE
HRESULT
WINAPI
IXMediaXmvPlayer::SetCallback(
    IN XMEDIA_CALLBACK_TYPE Type,
    IN XMEDIA_XMV_CALLBACK pfnCallback,
    IN OPTIONAL PVOID pvContext
    )
{
    return IXMediaXmvPlayer_SetCallback(this, Type, pfnCallback, pvContext);
}


#endif // __cplusplus

#pragma warning(pop)

#ifdef __cplusplus
}
#endif

#endif // __XMEDIA_INCLUDED__

