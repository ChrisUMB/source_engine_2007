
/************************************************************************
*                                                                       *
*   XCam.h -- This module defines the Xbox Camera APIs                  *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/

#pragma once
#ifndef __XCAM_H__
#define __XCAM_H__

#include <xonline.h>
#include <xaudio.h>

#if (!defined __XHV_H__ && !defined __XHVPV_H__)
#include <xhv.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


//------------------------------------------------------------------------------
// XCam Interfaces
//------------------------------------------------------------------------------
typedef struct IXCamVideo          *PIXCAMVIDEO;
typedef struct IXCamStreamEngine   *PIXCAMSTREAMENGINE;
typedef struct IXCamMotionEngine   *PIXCAMMOTIONENGINE;
struct __declspec(deprecated) IXCamRecordEngine;
struct __declspec(deprecated) IXCamPlaybackEngine;
typedef struct IXCamRecordEngine   *PIXCAMRECORDENGINE;
typedef struct IXCamPlaybackEngine *PIXCAMPLAYBACKENGINE;

//------------------------------------------------------------------------------
// XCam Enum Typedefs
//------------------------------------------------------------------------------
typedef enum _XCAMDEVICESTATE {
    XCAMDEVICESTATE_DISCONNECTED    = 0,
    XCAMDEVICESTATE_CONNECTED       = 1,
    XCAMDEVICESTATE_INITIALIZED     = 2,
    XCAMDEVICESTATE_IN_ERROR        = 3,
    XCAMDEVICESTATE_ERROR_FULLSPEED = 4,
    XCAMDEVICESTATE_FORCE_DWORD  = 0x7fffffff
} XCAMDEVICESTATE;

typedef enum _XCAMRESOLUTION {
    XCAMRESOLUTION_160x120      = 0x00A00078,
    XCAMRESOLUTION_176x144      = 0x00B00090,
    XCAMRESOLUTION_320x240      = 0x014000F0,
    XCAMRESOLUTION_352x288      = 0x01600120,
    XCAMRESOLUTION_640x480      = 0x028001E0,
    XCAMRESOLUTION_960x720      = 0x03C002D0,
    XCAMRESOLUTION_1280x960     = 0x050003C0,
    XCAMRESOLUTION_FORCE_DWORD  = 0x7fffffff
} XCAMRESOLUTION;

typedef enum _XCAMFRAMERATE {
    XCAMFRAMERATE_FASTEST       = 0,
    XCAMFRAMERATE_5             = 5,
    XCAMFRAMERATE_10            = 10,
    XCAMFRAMERATE_15            = 15,
    XCAMFRAMERATE_20            = 20,
    XCAMFRAMERATE_25            = 25,
    XCAMFRAMERATE_30            = 30,
    XCAMFRAMERATE_60            = 60,
    XCAMFRAMERATE_FORCE_DWORD   = 0x7fffffff
} XCAMFRAMERATE;

typedef enum _XCAMCONFIGIDS {
    XCAMCONFIGID_AE_MODE         = 2,
    XCAMCONFIGID_AE_PRIORITY     = 3,
    XCAMCONFIGID_EXPOSURE_TIME   = 4,
    XCAMCONFIGID_BACKLIGHT_COMP  = 101,
    XCAMCONFIGID_BRIGHTNESS      = 102,
    XCAMCONFIGID_CONTRAST        = 103,
    XCAMCONFIGID_GAIN            = 104,
    XCAMCONFIGID_FLICKER         = 105,
    XCAMCONFIGID_HUE             = 106,
    XCAMCONFIGID_SATURATION      = 107,
    XCAMCONFIGID_SHARPNESS       = 108,
    XCAMCONFIGID_GAMMA           = 109,
    XCAMCONFIGID_WHITE_BALANCE   = 110,
    XCAMCONFIGID_AUTO_WHITE_BAL  = 111,
    XCAMCONFIGID_LOWLIGHT        = 202,
    XCAMCONFIGID_LIGHTSOURCE     = 204,
    XCAMCONFIGID_COMP_ROOM_LIGHT = 300,
    XCAMCONFIGID_COMP_CORRECTED_LIGHTSOURCE = 301,
    XCAMCONFIGCONTROLID_FORCE_DWORD  = 0x7fffffff
} XCAMCONFIGCONTROLID;

typedef enum _XCAMZOOMFACTOR {
    XCAMZOOMFACTOR_1X            = 1,
    XCAMZOOMFACTOR_2X            = 2,
    XCAMZOOMFACTOR_4X            = 4,
    XCAMZOOMFACTOR_FORCE_DWORD   = 0x7fffffff
} XCAMZOOMFACTOR;


static const LONG XCAMCONFIG_LIGHTSOURCE_INCANDESCENT = 0;
static const LONG XCAMCONFIG_LIGHTSOURCE_FLOURESCENT = 1;
static const LONG XCAMCONFIG_LIGHTSOURCE_DAYLIGHT = 2;

//------------------------------------------------------------------------------
// Flags for use in AudioDestinationFlags of XCAM_PLAYBACK_ENGINE_INIT_PARAMS
//------------------------------------------------------------------------------
#define XCAM_PLAYBACK_AUDIO_DEST_USER_1      0x01
#define XCAM_PLAYBACK_AUDIO_DEST_USER_2      0x02
#define XCAM_PLAYBACK_AUDIO_DEST_USER_3      0x04
#define XCAM_PLAYBACK_AUDIO_DEST_USER_4      0x08
#define XCAM_PLAYBACK_AUDIO_DEST_ALL_USERS   0x0F

#define XCAM_PLAYBACK_AUDIO_DEST_DEFAULT_TV  0x10
#define XCAM_PLAYBACK_AUDIO_DEST_CUSTOM      0x20


//------------------------------------------------------------------------------
// XCam Callback Functions
//------------------------------------------------------------------------------
typedef VOID (*PFNCAMERADATAREADY)(DWORD UserData, PBYTE pVideoFrame, DWORD dwSize);

//------------------------------------------------------------------------------
// XCam Structures
//------------------------------------------------------------------------------
typedef struct _XCAM_STREAM_ENGINE_INIT_PARAMS {
    XCAMRESOLUTION                 VideoResolution;
    DWORD                          MaximumBitrate;
    DWORD                          MinimumBitrate;
    DWORD                          InitialTargetBitrate;
    XCAMFRAMERATE                  InitialTargetFramerate;
    DWORD                          MaxRemoteConsoles;
    DWORD                          NetworkDataPacketSize;
    DWORD                          ThreadProcessorID;
    BOOL                           GenerateLocalPreview;
    BOOL                           GetDataDirectFromCamera;
    PFNCAMERADATAREADY             CameraDataReadyCallback;
    DWORD                          CameraDataReadyCallbackUserdata;
    IDirect3DDevice9              *pD3DDevice;
} XCAM_STREAM_ENGINE_INIT_PARAMS, *PXCAM_STREAM_ENGINE_INIT_PARAMS;

typedef struct _XCAM_MOTION_ENGINE_INIT_PARAMS {
  DWORD                             ThreadProcessorID;
  XCAMRESOLUTION                    VideoResolution;
  IDirect3DDevice9*                 pD3DDevice;
  BOOL                              GetDataDirectFromCamera;
  FLOAT                             PersistenceValue;
  BYTE                              MovementThreshold;
} XCAM_MOTION_ENGINE_INIT_PARAMS, *PXCAM_MOTION_ENGINE_INIT_PARAMS;

typedef struct _XCAM_RECORD_ENGINE_INIT_PARAMS {
    XCAMRESOLUTION                 VideoResolution;
    XCAMFRAMERATE                  Framerate;
    DWORD                          TargetBitrate;
    DWORD                          AudioSourceUserIndex;
    DWORD                          ThreadProcessorID;
    BOOL                           GenerateLocalPreview;
    BOOL                           GetDataDirectFromCamera;
    PFNCAMERADATAREADY             CameraDataReadyCallback;
    DWORD                          CameraDataReadyCallbackUserdata;
    PIXHVENGINE                    pXHVEngine;
    IDirect3DDevice9              *pD3DDevice;
} XCAM_RECORD_ENGINE_INIT_PARAMS, *PXCAM_RECORD_ENGINE_INIT_PARAMS;

typedef struct _XCAM_PLAYBACK_ENGINE_INIT_PARAMS {
    XCAMRESOLUTION                 VideoResolution;
    XCAMFRAMERATE                  Framerate;
    DWORD                          TargetBitrate;
    DWORD                          AudioDestinationFlags;
    LPXAUDIOSUBMIXVOICE            CustomAudioDestination;
    DWORD                          ThreadProcessorID;
    PIXHVENGINE                    pXHVEngine;
    IDirect3DDevice9              *pD3DDevice;
} XCAM_PLAYBACK_ENGINE_INIT_PARAMS, *PXCAM_PLAYBACK_ENGINE_INIT_PARAMS;


//------------------------------------------------------------------------------
// XCam Initialization and Shutdown APIs
//------------------------------------------------------------------------------

XBOXAPI
DWORD
WINAPI
XCamInitialize();

XBOXAPI
VOID
WINAPI
XCamShutdown();


//------------------------------------------------------------------------------
// XCam Basic Camera Access API's
//------------------------------------------------------------------------------


XBOXAPI
XCAMDEVICESTATE
WINAPI
XCamGetStatus();

XBOXAPI
DWORD
WINAPI
XCamGetConfig(
    IN     XCAMCONFIGCONTROLID     ControlID,
    OUT    LONG                   *pValue,
    IN OUT PXOVERLAPPED            pOverlapped OPTIONAL);

XBOXAPI
DWORD
WINAPI
XCamSetConfig(
    IN     XCAMCONFIGCONTROLID     ControlID,
    IN     LONG                    Value,
    IN OUT PXOVERLAPPED            pOverlapped OPTIONAL);

XBOXAPI
DWORD
WINAPI
XCamSetView(
    IN     XCAMZOOMFACTOR          ZoomFactor, 
    IN     LONG                    XCenter,
    IN     LONG                    YCenter,
    IN OUT PXOVERLAPPED            pOverlapped OPTIONAL);

XBOXAPI
DWORD
WINAPI
XCamGetView(
    OUT XCAMZOOMFACTOR            *pZoomFactor OPTIONAL, 
    OUT LONG                      *pXCenter OPTIONAL,
    OUT LONG                      *pYCenter OPTIONAL);

XBOXAPI
DWORD
WINAPI
XCamSnapshot(
    IN       XCAMRESOLUTION        Resolution,
    IN OUT   D3DLOCKED_RECT       *pBuffer,
    IN OUT   PXOVERLAPPED          pOverlapped);



//------------------------------------------------------------------------------
// XCam Interface Creation Functions
//------------------------------------------------------------------------------
XBOXAPI
DWORD
WINAPI
XCamCreateVideo(
    OUT      PIXCAMVIDEO                    *ppVideo
    );

XBOXAPI
DWORD
WINAPI
XCamCreateStreamEngine(
    IN CONST XCAM_STREAM_ENGINE_INIT_PARAMS *pParams,
    OUT      PIXCAMSTREAMENGINE             *ppEngine
    );

XBOXAPI
DWORD
WINAPI
XCamCreateMotionEngine(
    IN CONST XCAM_MOTION_ENGINE_INIT_PARAMS *pParams,
    OUT      PIXCAMMOTIONENGINE             *ppEngine
    );

__declspec(deprecated)
XBOXAPI
DWORD
WINAPI
XCamCreateRecordEngine(
    IN CONST XCAM_RECORD_ENGINE_INIT_PARAMS *pParams,
    OUT      PIXCAMRECORDENGINE             *ppEngine
    );

__declspec(deprecated)
XBOXAPI
DWORD
WINAPI
XCamCreatePlaybackEngine(
    IN CONST XCAM_PLAYBACK_ENGINE_INIT_PARAMS *pParams,
    OUT      PIXCAMPLAYBACKENGINE             *ppEngine
    );


//------------------------------------------------------------------------------
// IXCamVideo Interface
//------------------------------------------------------------------------------

#undef  INTERFACE
#define INTERFACE   IXCamVideo

DECLARE_INTERFACE(IXCamVideo)
{
    STDMETHOD_(ULONG, AddRef)( IN THIS ) PURE;
    STDMETHOD_(ULONG, Release)( IN THIS ) PURE;

    STDMETHOD_(DWORD, SetCaptureMode)(
        IN                          THIS_
        IN     XCAMRESOLUTION       Resolution,
        IN     XCAMFRAMERATE        Framerate,
        IN OUT PXOVERLAPPED         pOverlapped OPTIONAL
        ) PURE;

    STDMETHOD_(DWORD, ReadFrame)(
        IN                         THIS_
        IN OUT D3DLOCKED_RECT     *pBuffer,
        IN OUT PXOVERLAPPED        pOverlapped
        ) PURE;
};


//------------------------------------------------------------------------------
// IXCamStreamEngine Interface
//------------------------------------------------------------------------------

#undef  INTERFACE
#define INTERFACE   IXCamStreamEngine

DECLARE_INTERFACE(IXCamStreamEngine)
{
    STDMETHOD_(ULONG, AddRef)( IN THIS ) PURE;
    STDMETHOD_(ULONG, Release)( IN THIS ) PURE;

    //
    // Finds a free remote console object and registers it with the specified XNADDR.
    // Use the "SendVideoToConsole" and "ReceiveVideoFromConsole" flags to specify
    // whether video data should flow in a single direction or bi-directionally
    // between the local machine and the remote machine.  Subsequent calls to
    // this function with the same XNADDR can be used to enable or disable
    // sending/receiving of video data, and/or update the list of XUIDs signed
    // on to that remote machine.
    //
    // If, because of parental control privileges, a video connection cannot be
    // established with this RemoteConsole, this function will return an error code.
    //
    // NOTE: At least one of the two flags must be TRUE - you cannot register a
    // remote console and neither send video to nor receive video from them!
    //
    STDMETHOD_(DWORD, RegisterRemoteConsole)(
        IN                         THIS_
        IN  XNADDR                 RemoteAddress,
        IN  CONST XUID            *RemoteXUIDList,
        IN  DWORD                  RemoteXUIDListLength,
        IN  BOOL                   SendVideoToConsole,
        IN  BOOL                   ReceiveVideoFromConsole
        ) PURE;

    //
    // De-registers a previously registered remote XNADDR.  This will terminate
    // the outgoing/incoming video stream(s) for that XNADDR.
    //
    STDMETHOD_(DWORD, UnregisterRemoteConsole)(
        IN                         THIS_
        IN  XNADDR                 RemoteAddress
        ) PURE;

    //
    // Retrieve the current list of registered remote consoles.
    //
    STDMETHOD_(VOID, GetRemoteConsoles)(
        IN                         THIS_
        OUT    XNADDR              *pRemoteAddresses,
        IN OUT PDWORD              pNumAddresses
        ) PURE;

    //
    // Check to see whether the video streams to and from the specified remote
    // console are disabled as a result of family settings. After calling 
    // RegisterRemoteConsole(), this function should be used to check and see
    // whether the console is in a disabled state. Similarly, following a local
    // user sign-in event, this function should be called for each registered
    // RemoteConsole to check and see if any of them have become disabled (or
    // potentially re-enabled). Internally, as soon as the sign-in has occurred,
    // the XCamStreamEngine will re-examine the parental control privileges and
    // determine if video communication with each RemoteConsole can continue.
    // RemoteConsoles that are disabled as a result of family settings will not
    // produce any new outbound video packets, nor will they generate new frames
    // of video.
    //
    STDMETHOD_(BOOL, IsRemoteConsoleDisallowed)(
        IN                         THIS_
        IN     XNADDR              RemoteAddress
        ) PURE;

    //
    // Get the address of the RemoteConsole which is having the hardest time
    // receiving and processing the stream that we are sending.  This is the
    // console that is forcing the bitrate of the local encoder to drop the 
    // farthest.  By terminating the video feed to this console, the engine
    // should be able to raise the encoder bitrate up somewhat (assuming that
    // the other RemoteConsoles are not having an equally hard time receiving
    // and processing the stream we are sending).  If you want to try and
    // improve the video experience for all other recipients (ie: if the actual
    // bitrate has fallen lower than you find acceptable), then use this
    // function to determine which RemoteConsole you should stop sending the
    // local video stream to.
    //
    STDMETHOD_(DWORD, GetSlowestConnection)(
        IN                         THIS_
        OUT XNADDR                *pRemoteAddress
        ) PURE;

    //
    // Push a frame of video into the "encode queue".  XOVERLAPPED is signaled once
    // the encode is complete
    //
    STDMETHOD_(DWORD, SubmitLocalVideoFrame)(
        IN                         THIS_
        IN  PBYTE                  pVideoFrame,
        IN  PXOVERLAPPED           pOverlapped
        ) PURE;

    //
    // Retrieves a chunk of data to be sent to the specified XNADDR (which was
    // previously registered via "RegisterRemoteConsole").  This blob can contain
    // both encoded video data, as well as QOS data and necessary feedback 
    // communication related to an incoming video stream.  This should be called
    // for _ALL_ registered remote consoles, regardless of whether they are sending
    // video, receiving video, or both.
    //
    STDMETHOD_(DWORD, GetNetworkData)(
        IN                         THIS_
        IN     XNADDR              RemoteAddress,
        OUT    PBYTE               pBuffer,
        IN OUT PDWORD              pBufferSize
        ) PURE;

    //
    // Submits a chunk of data that has been received on the network from the 
    // specified XNADDR (which was previously registered via "RegisterRemoteConsole").
    // See "GetNetworkData" for more information.
    //
    STDMETHOD_(DWORD, SubmitNetworkData)(
        IN                         THIS_
        IN  XNADDR                 RemoteAddress,
        IN  PBYTE                  pBuffer,
        IN  DWORD                  BufferSize,
        IN  PXOVERLAPPED           pOverlapped
        ) PURE;

    //
    // Specifies the screenspace rectangle in which the incoming video stream
    // corresponding with the RemoteAddress should be rendered.  This function should
    // be used in conjunction with the "RenderRemoteConsole" function.
    //
    STDMETHOD_(DWORD, SetRemoteConsoleRect)(
        IN                         THIS_
        IN       XNADDR            RemoteAddress,
        IN CONST D3DRECT          *pRect
        ) PURE;

    //
    // Specifies the default texture that should be used as the "fallback" texture for
    // this remote console during calls to "RenderRemoteConsole".  If no new frames have
    // been decoded in the last 5 seconds, the engine will switch over to rendering this
    // fallback texture (if one has been provided).  To get rid of a previously set
    // default texture, simply calls this function and pass in NULL for the
    // pDefaultTexture.  This fallback texture has no effect on the data returned by 
    // "GetNextRemoteConsoleFrame", and should only be used in conjunction with the
    // "RenderRemoteConsole" function.
    //
    STDMETHOD_(DWORD, SetRemoteConsoleDefaultTexture)(
        IN                         THIS_
        IN  XNADDR                 RemoteAddress,
        IN  D3DTexture            *pDefaultTexture
        ) PURE;

    //
    // Renders the current frame of the incoming video stream corresponding
    // with the specified RemoteAddress in the screenspace rectangle previously
    // specified in "SetRemoteConsoleRect".
    //
    STDMETHOD_(DWORD, RenderRemoteConsole)(
        IN                         THIS_
        IN  XNADDR                 RemoteAddress
        ) PURE;

    //
    // Obtains the next frame of video for the specified RemoteAddress. Use
    // this function if you want to handle displaying the incoming stream
    // yourself, rather than use the "RenderRemoteConsole" function. If no
    // new frames are available, this will return ERROR_IO_PENDING.
    //
    STDMETHOD_(DWORD, GetNextRemoteConsoleFrame)(
        IN                         THIS_
        IN     XNADDR              RemoteAddress,
        IN OUT D3DLOCKED_RECT     *pYBuffer,
        IN OUT D3DLOCKED_RECT     *pUBuffer,
        IN OUT D3DLOCKED_RECT     *pVBuffer
        ) PURE;

    //
    // Obtains the next frame of video for the specified RemoteAddress, and
    // converts it to D3DFMT_LIN_X8R8G8B8 directly within this function using
    // the CPU.  This function is _MUCH_ more CPU intensive than 
    // GetNextRemoteConsoleFrame(), and should only be used if you actually want
    // the color conversion to occur on the CPU instead of the GPU. If no new
    // frames are available, this will return ERROR_IO_PENDING.
    //
    STDMETHOD_(DWORD, GetNextRemoteConsoleFrameRGB)(
        IN                         THIS_
        IN     XNADDR              RemoteAddress,
        IN OUT D3DLOCKED_RECT     *pBuffer
        ) PURE;


    //
    // Does for the local preview video what "SetRemoteConsoleRect"
    // does for a remote console's incoming video stream.
    //
    STDMETHOD_(VOID, SetLocalPreviewRect)(
        IN                         THIS_
        IN CONST D3DRECT          *pRect
        ) PURE;

    //
    // Does for the local preview video what "RenderRemoteConsole" does
    // for a remote console's incoming video stream.
    //
    STDMETHOD_(VOID, RenderLocalPreview)(
        IN                         THIS
        ) PURE;

    //
    // Does for the local preview video what "GetNextRemoteConsoleFrame" does
    // for a remote console's incoming video stream.
    //
    STDMETHOD_(DWORD, GetNextLocalPreviewFrame)(
        IN                         THIS_
        IN OUT D3DLOCKED_RECT     *pBuffer
        ) PURE;

    //
    // Does for the local preview video what "GetNextRemoteConsoleFrameRGB"
    // does for a remote console's incoming video stream
    //
    STDMETHOD_(DWORD, GetNextLocalPreviewFrameRGB)(
        IN                         THIS_
        IN OUT D3DLOCKED_RECT     *pBuffer
        ) PURE;

    //
    // Encoder bitrate and framerate controls
    //
    STDMETHOD_(VOID, SetEncoderTargetBitrate)(
        IN                         THIS_
        IN  DWORD                  TargetBitrate
        ) PURE;

    STDMETHOD_(DWORD, GetEncoderTargetBitrate)(
        IN                         THIS
        ) PURE;

    STDMETHOD_(DWORD, GetEncoderActualBitrate)(
        IN                         THIS
        ) PURE;

    STDMETHOD_(VOID, SetEncoderTargetFramerate)(
        IN                         THIS_
        IN  XCAMFRAMERATE          TargetFramerate
        ) PURE;

    STDMETHOD_(XCAMFRAMERATE, GetEncoderTargetFramerate)(
        IN                         THIS
        ) PURE;

    STDMETHOD_(XCAMFRAMERATE, GetEncoderActualFramerate)(
        IN                         THIS
        ) PURE;

};


//------------------------------------------------------------------------------
// IXCamMotionEngine Interface
//------------------------------------------------------------------------------

#undef  INTERFACE
#define INTERFACE   IXCamMotionEngine

DECLARE_INTERFACE(IXCamMotionEngine)
{
    STDMETHOD_(ULONG, AddRef)( IN THIS ) PURE;
    STDMETHOD_(ULONG, Release)( IN THIS ) PURE;

    //
    // Main worker function. Generates motion map by differencing the current
    // and previous frames.
    //
    STDMETHOD_(VOID, GenerateMotionMap)(
        IN                         THIS_
        IN OUT D3DLOCKED_RECT*     pBufferA, 
        IN OUT D3DLOCKED_RECT*     pBufferB
        ) PURE;

    //
    // Returns the motion map in a D3DFMT_LIN_L8 locked texture.
    //
    STDMETHOD_(VOID, GetMotionMapData)(
        IN                         THIS_
        IN OUT D3DLOCKED_RECT*     pBuffer
        ) PURE;
  
    //
    // Tests motion against a filled rectangle. Returns TRUE if motion
    // was detected.
    //
    STDMETHOD_(BOOL, RectFilledTouch)(
        IN                         THIS_
        IN OUT D3DRECT*            pRect
        ) PURE;

    //
    // Tests motion against a filled rectangle, returning a percentage
    // of motion inside the rectangle (0..1).
    //
    STDMETHOD_(FLOAT, RectFilledTouchPercent)(
        IN                         THIS_
        IN OUT D3DRECT*            pRect
        ) PURE;

    //
    // Tests motion against a rectange outline. Returns TRUE if motion
    // was detected.
    //
    STDMETHOD_(BOOL, RectOutlineTouch)(
        IN                         THIS_
        IN OUT D3DRECT*            pRect
        ) PURE;

    //
    // Tests motion against an ellipse outline. Returns TRUE if motion
    // was detected. If the pvecDirection vector is not NULL, on
    // return it will contain the direction of motion.
    //
    STDMETHOD_(BOOL, EllipseOutlineTouch)(
        IN                         THIS_
        IN INT                     nCenterX,
        IN INT                     nCenterY, 
        IN FLOAT                   fRadiusX,
        IN FLOAT                   fRadiusY, 
        IN OUT D3DVECTOR*          pvecDirection
        ) PURE;

    //
    // Tests motion against a filled ellipse. Returns TRUE if motion
    // was detected. If the pvecDirection vector is not NULL, on
    // return it will contain the direction of motion.
    //
    STDMETHOD_(BOOL, EllipseFilledTouch)(
        IN                         THIS_
        IN INT                     nCenterX,
        IN INT                     nCenterY, 
        IN FLOAT                   fRadiusX,
        IN FLOAT                   fRadiusY, 
        IN OUT D3DVECTOR*          pvecDirection
        ) PURE;

    //
    // Tests motion against a filled ellipse. Returns a percentage of
    // motion inside the ellipse (0..1). If the pvecDirection vector 
    // is not NULL, on return it will contain the direction of motion.
    //
    STDMETHOD_(FLOAT, EllipseFilledTouchPercent)(
        IN                         THIS_
        IN INT                     nCenterX,
        IN INT                     nCenterY, 
        IN FLOAT                   fRadiusX,
        IN FLOAT                   fRadiusY, 
        IN OUT D3DVECTOR*          pvecDirection
        ) PURE;

    //
    // Tests motion against an aribtrary bitmap. The bitmap must be a texture
    // in the D3DFMT_LIN_L8 format that represents a touch region. Pixels
    // with value of 255 represent areas to be tested. Returns TRUE if motion
    // detected.
    //
    STDMETHOD_(BOOL, RegionFilledTouch)(
        IN                         THIS_
        IN OUT BYTE*               pbyRegionMap,
        IN OUT D3DRECT*            prectRegion
        ) PURE;

    //
    // Tests motion against an aribtrary bitmap. The bitmap must be a texture
    // in the D3DFMT_LIN_L8 format that represents a touch region. Pixels
    // with value of 255 represent areas to be tested. Returns a percentage
    // of motion inside tested areas (0..1).
    //
    STDMETHOD_(FLOAT, RegionFilledTouchPercent)(
        IN                         THIS_
        IN OUT BYTE*               pbyRegionMap,
        IN OUT D3DRECT*            prectRegion
        ) PURE;

    //
    // Sets motion threshold (0..255). The lower the threshold the more motion
    // and potentially noise is detected.
    //
    STDMETHOD_(VOID, SetThreshold)(
        IN                         THIS_
        IN BYTE                    byThreshold
        ) PURE;

    //
    // Returns motion threshold
    //
    STDMETHOD_(BYTE, GetThreshold)(
        IN                         THIS
        ) PURE;

    //
    // Gets the frame retreived from the camera in D3DFMT_LE_LIN_YUY2 format.
    //
    STDMETHOD_(DWORD, GetNextLocalPreviewFrame)(
        IN                         THIS_
        IN OUT D3DLOCKED_RECT*     pBuffer
        ) PURE;

    //
    // Sets rectangle where live video will be rendered.
    //
    STDMETHOD_(VOID, SetLocalPreviewRect)(
        IN                         THIS_
        IN OUT D3DRECT*            pRect
        ) PURE;

    //
    // Render live video in local preview rectangle.
    //
    STDMETHOD_(VOID, RenderLocalPreview)(
        IN                         THIS
        ) PURE;


};

//------------------------------------------------------------------------------
// IXCamRecordEngine Interface
//------------------------------------------------------------------------------

#undef  INTERFACE
#define INTERFACE   IXCamRecordEngine

DECLARE_INTERFACE (IXCamRecordEngine)
{
    STDMETHOD_(ULONG, AddRef)( IN THIS ) PURE;
    STDMETHOD_(ULONG, Release)( IN THIS ) PURE;

    //
    // Calculates the estimated buffer size required to hold a video message
    // of the specified length in seconds.
    //
    STDMETHOD_(DWORD, EstimateRequiredBufferSize)(
        IN                         THIS_
        IN  DWORD                  MessageLengthInSeconds
        ) PURE;

    //
    // Begin recording into the supplied buffer.  Recording will complete when
    // the buffer is full and there is no longer enough space left to hold more
    // frames, or when the specified message length has been reached.  The
    // actual amount of data written to the buffer will be returned in the
    // XOVERLAPPED structure.
    //
    STDMETHOD_(DWORD, StartRecording)(
        IN                         THIS_
        IN  PVOID                  pBuffer,
        IN  DWORD                  BufferSize,
        IN  DWORD                  MessageLengthInSeconds,
        IN  PXOVERLAPPED           pOverlapped
        ) PURE;

    //
    // Stop the recording.
    //
    STDMETHOD_(VOID, StopRecord)(
        IN                         THIS
        ) PURE;

    //
    // Push a frame of video into the "encode queue".  XOVERLAPPED is signaled once
    // the encode is complete.  Only use this if the engine is not getting its data
    // direct from the camera
    //
    STDMETHOD_(DWORD, SubmitLocalVideoFrame)(
        IN                         THIS_
        IN  PBYTE                  pVideoFrame,
        IN  PXOVERLAPPED           pOverlapped
        ) PURE;

    //
    // Specifies the screenspace rectangle in which the local preview of the
    // video capture should be rendered.  This function should be used in
    // conjunction with the "RenderLocalPreview" function.
    //
    STDMETHOD_(VOID, SetLocalPreviewRect)(
        IN                         THIS_
        IN CONST D3DRECT          *pRect
        ) PURE;

    //
    // Renders the current frame of the local preview in the screenspace
    // rectangle previously specified in "SetLocalPreviewRect".
    //
    STDMETHOD_(VOID, RenderLocalPreview)(
        IN                         THIS
        ) PURE;

    //
    // Obtains the next frame of video from the local preview. Use this
    // function if you want to handle displaying the incoming stream yourself,
    // rather than use the "RenderLocalPreview" function. If no new frames are
    // available, this will return ERROR_IO_PENDING.
    //
    STDMETHOD_(DWORD, GetNextLocalPreviewFrame)(
        IN                         THIS_
        IN OUT D3DLOCKED_RECT     *pBuffer
        ) PURE;
};


//------------------------------------------------------------------------------
// IXCamPlaybackEngine Interface
//------------------------------------------------------------------------------

#undef  INTERFACE
#define INTERFACE   IXCamPlaybackEngine

DECLARE_INTERFACE (IXCamPlaybackEngine)
{
    STDMETHOD_(ULONG, AddRef)( IN THIS ) PURE;
    STDMETHOD_(ULONG, Release)( IN THIS ) PURE;

    //
    // Begin playback from the supplied buffer.  The XOVERLAPPED supplied here
    // will be signaled once playback is complete.
    //
    STDMETHOD_(DWORD, StartPlayback)(
        IN                         THIS_
        IN  PVOID                  pBuffer,
        IN  DWORD                  BufferSize,
        IN  PXOVERLAPPED           pOverlapped
        ) PURE;

    //
    // Pause the playback.
    //
    STDMETHOD_(VOID, Pause)(
        IN                         THIS
        ) PURE;

    //
    // Pause the playback.
    //
    STDMETHOD_(VOID, Resume)(
        IN                         THIS
        ) PURE;

    //
    // Stop the playback.
    //
    STDMETHOD_(VOID, Stop)(
        IN                         THIS
        ) PURE;

    //
    // Specifies the screenspace rectangle in which the video playback should
    // be rendered.  This function should be used in conjunction with the 
    // "Render" function.
    //
    STDMETHOD_(VOID, SetRect)(
        IN                         THIS_
        IN CONST D3DRECT          *pRect
        ) PURE;

    //
    // Renders the current frame of video in the screenspace rectangle
    // previously specified in "SetRect".
    //
    STDMETHOD_(VOID, Render)(
        IN                         THIS
        ) PURE;

    //
    // Obtains the next frame of video. Use this function if you want to handle
    // displaying the incoming stream yourself, rather than use the "Render"
    // function. If no new frames are available, this will return
    // ERROR_IO_PENDING.
    //
    STDMETHOD_(DWORD, GetNextFrame)(
        IN                         THIS_
        IN OUT D3DLOCKED_RECT     *pYBuffer,
        IN OUT D3DLOCKED_RECT     *pUBuffer,
        IN OUT D3DLOCKED_RECT     *pVBuffer
        ) PURE;
};


//------------------------------------------------------------------------------
// C Function Wrappers for XCAM Interfaces
//------------------------------------------------------------------------------

#pragma push_macro("VTBL")
#pragma push_macro("THIS")
#pragma push_macro("THIS_")

#undef  VTBL
#undef  THIS
#undef  THIS_

#if defined(__cplusplus) && !defined(CINTERFACE)
#define VTBL(p) (p)
#define THIS
#define THIS_
#else // defined(__cplusplus) && !defined(CINTERFACE)
#define VTBL(p) ((p)->lpVtbl)
#define THIS    pThis
#define THIS_   pThis,
#endif // defined(__cplusplus) && !defined(CINTERFACE)

FORCEINLINE
STDMETHODIMP_(ULONG)
IXCamVideo_AddRef(
    IN  PIXCAMVIDEO                pThis
    )
{
    return VTBL(pThis)->AddRef(THIS);
}

FORCEINLINE
STDMETHODIMP_(ULONG)
IXCamVideo_Release(
    IN  PIXCAMVIDEO                pThis
    )
{
    return VTBL(pThis)->Release(THIS);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamVideo_SetCaptureMode(
    IN  PIXCAMVIDEO                pThis,
    IN  XCAMRESOLUTION             Resolution,
    IN  XCAMFRAMERATE              Framerate,
    IN  PXOVERLAPPED               pOverlapped
    )
{
    return VTBL(pThis)->SetCaptureMode(THIS_ Resolution, Framerate, pOverlapped);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamVideo_ReadFrame(
    IN  PIXCAMVIDEO                pThis,
    IN OUT D3DLOCKED_RECT         *pBuffer,
    IN  PXOVERLAPPED               pOverlapped
    )
{
    return VTBL(pThis)->ReadFrame(THIS_ pBuffer, pOverlapped);
}




FORCEINLINE
STDMETHODIMP_(ULONG)
IXCamStreamEngine_AddRef(
    IN  PIXCAMSTREAMENGINE         pThis
    )
{
    return VTBL(pThis)->AddRef(THIS);
}

FORCEINLINE
STDMETHODIMP_(ULONG)
IXCamStreamEngine_Release(
    IN  PIXCAMSTREAMENGINE         pThis
    )
{
    return VTBL(pThis)->Release(THIS);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_RegisterRemoteConsole(
    IN  PIXCAMSTREAMENGINE         pThis,
    IN  XNADDR                     RemoteAddress,
    IN  CONST XUID                *RemoteXUIDList,
    IN  DWORD                      RemoteXUIDListLength,
    IN  BOOL                       SendVideoToConsole,
    IN  BOOL                       ReceiveVideoFromConsole
    )
{
    return VTBL(pThis)->RegisterRemoteConsole(THIS_ RemoteAddress, RemoteXUIDList, RemoteXUIDListLength, SendVideoToConsole, ReceiveVideoFromConsole);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_UnregisterRemoteConsole(
    IN  PIXCAMSTREAMENGINE         pThis,
    IN  XNADDR                     RemoteAddress
    )
{
    return VTBL(pThis)->UnregisterRemoteConsole(THIS_ RemoteAddress);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamStreamEngine_GetRemoteConsoles(
    IN     PIXCAMSTREAMENGINE      pThis,
    IN     XNADDR                 *pRemoteAddresses,
    IN OUT PDWORD                  pNumAddresses
    )
{
    return VTBL(pThis)->GetRemoteConsoles(THIS_ pRemoteAddresses, pNumAddresses);
}

FORCEINLINE
STDMETHODIMP_(BOOL)
IXCamStreamEngine_IsRemoteConsoleDisallowed(
    IN     PIXCAMSTREAMENGINE      pThis,
    IN     XNADDR                  RemoteAddress
    )
{
    return VTBL(pThis)->IsRemoteConsoleDisallowed(THIS_ RemoteAddress);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_GetSlowestConnection(
    IN  PIXCAMSTREAMENGINE         pThis,
    IN  XNADDR                    *pRemoteAddress
    )
{
    return VTBL(pThis)->GetSlowestConnection(THIS_ pRemoteAddress);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_SubmitLocalVideoFrame(
    IN  PIXCAMSTREAMENGINE         pThis,
    IN  PBYTE                      pVideoFrame,
    IN  PXOVERLAPPED               pOverlapped
    )
{
    return VTBL(pThis)->SubmitLocalVideoFrame(THIS_ pVideoFrame, pOverlapped);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_GetNetworkData(
    IN     PIXCAMSTREAMENGINE      pThis,
    IN     XNADDR                  RemoteAddress,
    OUT    PBYTE                   pBuffer,
    IN OUT PDWORD                  pBufferSize
    )
{
    return VTBL(pThis)->GetNetworkData(THIS_ RemoteAddress, pBuffer, pBufferSize);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_SubmitNetworkData(
    IN  PIXCAMSTREAMENGINE         pThis,
    IN  XNADDR                     RemoteAddress,
    IN  PBYTE                      pBuffer,
    IN  DWORD                      BufferSize,
    IN  PXOVERLAPPED               pOverlapped
    )
{
    return VTBL(pThis)->SubmitNetworkData(THIS_ RemoteAddress, pBuffer, BufferSize, pOverlapped);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_SetRemoteConsoleRect(
    IN       PIXCAMSTREAMENGINE    pThis,
    IN       XNADDR                RemoteAddress,
    IN CONST D3DRECT              *pRect
    )
{
    return VTBL(pThis)->SetRemoteConsoleRect(THIS_ RemoteAddress, pRect);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_SetRemoteConsoleDefaultTexture(
    IN  PIXCAMSTREAMENGINE         pThis,
    IN  XNADDR                     RemoteAddress,
    IN  D3DTexture                *pDefaultTexture
    )
{
    return VTBL(pThis)->SetRemoteConsoleDefaultTexture(THIS_ RemoteAddress, pDefaultTexture);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_RenderRemoteConsole(
    IN  PIXCAMSTREAMENGINE         pThis,
    IN  XNADDR                     RemoteAddress
    )
{
    return VTBL(pThis)->RenderRemoteConsole(THIS_ RemoteAddress);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_GetNextRemoteConsoleFrame(
    IN     PIXCAMSTREAMENGINE      pThis,
    IN     XNADDR                  RemoteAddress,
    IN OUT D3DLOCKED_RECT         *pYBuffer,
    IN OUT D3DLOCKED_RECT         *pUBuffer,
    IN OUT D3DLOCKED_RECT         *pVBuffer
    )
{
    return VTBL(pThis)->GetNextRemoteConsoleFrame(THIS_ RemoteAddress, pYBuffer, pUBuffer, pVBuffer);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_GetNextRemoteConsoleFrameRGB(
    IN     PIXCAMSTREAMENGINE      pThis,
    IN     XNADDR                  RemoteAddress,
    IN OUT D3DLOCKED_RECT         *pBuffer
    )
{
    return VTBL(pThis)->GetNextRemoteConsoleFrameRGB(THIS_ RemoteAddress, pBuffer);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamStreamEngine_SetLocalPreviewRect(
    IN       PIXCAMSTREAMENGINE    pThis,
    IN CONST D3DRECT              *pRect
    )
{
    return VTBL(pThis)->SetLocalPreviewRect(THIS_ pRect);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamStreamEngine_RenderLocalPreview(
    IN  PIXCAMSTREAMENGINE         pThis
    )
{
    return VTBL(pThis)->RenderLocalPreview(THIS);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_GetNextLocalPreviewFrame(
    IN     PIXCAMSTREAMENGINE      pThis,
    IN OUT D3DLOCKED_RECT         *pBuffer
    )
{
    return VTBL(pThis)->GetNextLocalPreviewFrame(THIS_ pBuffer);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_GetNextLocalPreviewFrameRGB(
    IN     PIXCAMSTREAMENGINE      pThis,
    IN OUT D3DLOCKED_RECT         *pBuffer
    )
{
    return VTBL(pThis)->GetNextLocalPreviewFrameRGB(THIS_ pBuffer);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamStreamEngine_SetEncoderTargetBitrate(
    IN  PIXCAMSTREAMENGINE         pThis,
    IN  DWORD                      TargetBitrate
    )
{
    return VTBL(pThis)->SetEncoderTargetBitrate(THIS_ TargetBitrate);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_GetEncoderTargetBitrate(
    IN  PIXCAMSTREAMENGINE         pThis
    )
{
    return VTBL(pThis)->GetEncoderTargetBitrate(THIS);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamStreamEngine_GetEncoderActualBitrate(
    IN  PIXCAMSTREAMENGINE         pThis
    )
{
    return VTBL(pThis)->GetEncoderActualBitrate(THIS);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamStreamEngine_SetEncoderTargetFramerate(
    IN  PIXCAMSTREAMENGINE         pThis,
    IN  XCAMFRAMERATE              TargetFramerate
    )
{
    return VTBL(pThis)->SetEncoderTargetFramerate(THIS_ TargetFramerate);
}

FORCEINLINE
STDMETHODIMP_(XCAMFRAMERATE)
IXCamStreamEngine_GetEncoderTargetFramerate(
    IN  PIXCAMSTREAMENGINE         pThis
    )
{
    return VTBL(pThis)->GetEncoderTargetFramerate(THIS);
}

FORCEINLINE
STDMETHODIMP_(XCAMFRAMERATE)
IXCamStreamEngine_GetEncoderActualFramerate(
    IN  PIXCAMSTREAMENGINE         pThis
    )
{
    return VTBL(pThis)->GetEncoderActualFramerate(THIS);
}


FORCEINLINE
STDMETHODIMP_(ULONG)
IXCamMotionEngine_AddRef( 
    IN PIXCAMMOTIONENGINE       pThis
    )
{
    return VTBL(pThis)->AddRef(THIS);
}

FORCEINLINE
STDMETHODIMP_(ULONG)
IXCamMotionEngine_Release(
    IN PIXCAMMOTIONENGINE       pThis
    )
{
    return VTBL(pThis)->Release(THIS);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamMotionEngine_GenerateMotionMap(
    IN PIXCAMMOTIONENGINE      pThis,
    IN OUT D3DLOCKED_RECT*     pBufferA, 
    IN OUT D3DLOCKED_RECT*     pBufferB
    )
{
    return VTBL(pThis)->GenerateMotionMap(THIS_ pBufferA, pBufferB);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamMotionEngine_GetMotionMapData(
    IN PIXCAMMOTIONENGINE      pThis,
    IN OUT D3DLOCKED_RECT*     pBuffer
    )
{
    return VTBL(pThis)->GetMotionMapData(THIS_ pBuffer);
}

FORCEINLINE
STDMETHODIMP_(BOOL)
IXCamMotionEngine_RectFilledTouch(
    IN PIXCAMMOTIONENGINE      pThis,
    IN OUT D3DRECT*            pRect
    )
{
    return VTBL(pThis)->RectFilledTouch(THIS_ pRect);
}

FORCEINLINE
STDMETHODIMP_(FLOAT)
IXCamMotionEngine_RectFilledTouchPercent(
    IN PIXCAMMOTIONENGINE      pThis,
    IN OUT D3DRECT*            pRect
    )
{
    return VTBL(pThis)->RectFilledTouchPercent(THIS_ pRect);
}

FORCEINLINE
STDMETHODIMP_(BOOL)
IXCamMotionEngine_RectOutlineTouch(
    IN PIXCAMMOTIONENGINE      pThis,
    IN OUT D3DRECT*            pRect
    )
{
    return VTBL(pThis)->RectOutlineTouch(THIS_ pRect);
}

FORCEINLINE
STDMETHODIMP_(BOOL)
IXCamMotionEngine_EllipseOutlineTouch(
    IN PIXCAMMOTIONENGINE      pThis,
    IN INT                     nCenterX,
    IN INT                     nCenterY, 
    IN FLOAT                   fRadiusX,
    IN FLOAT                   fRadiusY, 
    IN OUT D3DVECTOR*          pvecDirection
    )
{
    return VTBL(pThis)->EllipseOutlineTouch(THIS_ nCenterX, nCenterY, fRadiusX, fRadiusY, pvecDirection);
}

FORCEINLINE
STDMETHODIMP_(BOOL)
IXCamMotionEngine_EllipseFilledTouch(
    IN PIXCAMMOTIONENGINE      pThis,
    IN INT                     nCenterX,
    IN INT                     nCenterY, 
    IN FLOAT                   fRadiusX,
    IN FLOAT                   fRadiusY, 
    IN OUT D3DVECTOR*          pvecDirection
    )
{
    return VTBL(pThis)->EllipseFilledTouch(THIS_ nCenterX, nCenterY, fRadiusX, fRadiusY, pvecDirection);
}

FORCEINLINE
STDMETHODIMP_(FLOAT)
IXCamMotionEngine_EllipseFilledTouchPercent(
    IN PIXCAMMOTIONENGINE      pThis,
    IN INT                     nCenterX,
    IN INT                     nCenterY, 
    IN FLOAT                   fRadiusX,
    IN FLOAT                   fRadiusY, 
    IN OUT D3DVECTOR*          pvecDirection
    )
{
    return VTBL(pThis)->EllipseFilledTouchPercent(THIS_ nCenterX, nCenterY, fRadiusX, fRadiusY, pvecDirection);
}

FORCEINLINE
STDMETHODIMP_(BOOL)
IXCamMotionEngine_RegionFilledTouch(
    IN PIXCAMMOTIONENGINE      pThis,
    IN OUT BYTE*               pbyRegionMap,
    IN OUT D3DRECT*            prectRegion
    )
{
    return VTBL(pThis)->RegionFilledTouch(THIS_ pbyRegionMap, prectRegion);
}

FORCEINLINE
STDMETHODIMP_(FLOAT)
IXCamMotionEngine_RegionFilledTouchPercent(
    IN PIXCAMMOTIONENGINE      pThis,
    IN OUT BYTE*               pbyRegionMap,
    IN OUT D3DRECT*            prectRegion
    )
{
    return VTBL(pThis)->RegionFilledTouchPercent(THIS_ pbyRegionMap, prectRegion);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamMotionEngine_SetThreshold(
    IN PIXCAMMOTIONENGINE      pThis,
    IN BYTE                    byThreshold
    )
{
    return VTBL(pThis)->SetThreshold(THIS_ byThreshold);
}

FORCEINLINE
STDMETHODIMP_(BYTE)
IXCamMotionEngine_GetThreshold(
    IN PIXCAMMOTIONENGINE      pThis
    )
{
    return VTBL(pThis)->GetThreshold(THIS);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamMotionEngine_GetNextLocalPreviewFrame(
    IN PIXCAMMOTIONENGINE      pThis,
    IN OUT D3DLOCKED_RECT*     pBuffer
    )
{
    return VTBL(pThis)->GetNextLocalPreviewFrame(THIS_ pBuffer);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamMotionEngine_SetLocalPreviewRect(
    IN PIXCAMMOTIONENGINE      pThis,
    IN OUT D3DRECT*            pRect
    )
{
    return VTBL(pThis)->SetLocalPreviewRect(THIS_ pRect);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamMotionEngine_RenderLocalPreview(
    IN PIXCAMMOTIONENGINE      pThis
    )
{
    return VTBL(pThis)->RenderLocalPreview(THIS);
}



FORCEINLINE
STDMETHODIMP_(ULONG)
IXCamRecordEngine_AddRef(
    IN  PIXCAMRECORDENGINE         pThis
    )
{
    return VTBL(pThis)->AddRef(THIS);
}

FORCEINLINE
STDMETHODIMP_(ULONG)
IXCamRecordEngine_Release(
    IN  PIXCAMRECORDENGINE         pThis
    )
{
    return VTBL(pThis)->Release(THIS);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamRecordEngine_EstimateRequiredBufferSize(
    IN  PIXCAMRECORDENGINE         pThis,
    IN  DWORD                      MessageLengthInSeconds
    )
{
    return VTBL(pThis)->EstimateRequiredBufferSize(THIS_ MessageLengthInSeconds);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamRecordEngine_StartRecording(
    IN  PIXCAMRECORDENGINE         pThis,
    IN  PVOID                      pBuffer,
    IN  DWORD                      BufferSize,
    IN  DWORD                      MessageLengthInSeconds,
    IN  PXOVERLAPPED               pOverlapped
    )
{
    return VTBL(pThis)->StartRecording(THIS_ pBuffer, BufferSize, MessageLengthInSeconds, pOverlapped);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamRecordEngine_StopRecord(
    IN  PIXCAMRECORDENGINE         pThis
    )
{
    return VTBL(pThis)->StopRecord(THIS);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamRecordEngine_SubmitLocalVideoFrame(
    IN  PIXCAMRECORDENGINE         pThis,
    IN  PBYTE                      pVideoFrame,
    IN  PXOVERLAPPED               pOverlapped
    )
{
    return VTBL(pThis)->SubmitLocalVideoFrame(THIS_ pVideoFrame, pOverlapped);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamRecordEngine_SetLocalPreviewRect(
    IN  PIXCAMRECORDENGINE         pThis,
    IN  CONST D3DRECT             *pRect
    )
{
    return VTBL(pThis)->SetLocalPreviewRect(THIS_ pRect);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamRecordEngine_RenderLocalPreview(
    IN  PIXCAMRECORDENGINE         pThis
    )
{
    return VTBL(pThis)->RenderLocalPreview(THIS);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamRecordEngine_GetNextLocalPreviewFrame(
    IN     PIXCAMRECORDENGINE      pThis,
    IN OUT D3DLOCKED_RECT         *pBuffer
    )
{
    return VTBL(pThis)->GetNextLocalPreviewFrame(THIS_ pBuffer);
}



FORCEINLINE
STDMETHODIMP_(ULONG)
IXCamPlaybackEngine_AddRef(
    IN  PIXCAMPLAYBACKENGINE       pThis
    )
{
    return VTBL(pThis)->AddRef(THIS);
}

FORCEINLINE
STDMETHODIMP_(ULONG)
IXCamPlaybackEngine_Release(
    IN  PIXCAMPLAYBACKENGINE       pThis
    )
{
    return VTBL(pThis)->Release(THIS);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamPlaybackEngine_StartPlayback(
    IN  PIXCAMPLAYBACKENGINE       pThis,
    IN  PVOID                      pBuffer,
    IN  DWORD                      BufferSize,
    IN  PXOVERLAPPED               pOverlapped
    )
{
    return VTBL(pThis)->StartPlayback(THIS_ pBuffer, BufferSize, pOverlapped);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamPlaybackEngine_Pause(
    IN  PIXCAMPLAYBACKENGINE       pThis
    )
{
    return VTBL(pThis)->Pause(THIS);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamPlaybackEngine_Resume(
    IN  PIXCAMPLAYBACKENGINE       pThis
    )
{
    return VTBL(pThis)->Resume(THIS);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamPlaybackEngine_Stop(
    IN  PIXCAMPLAYBACKENGINE       pThis
    )
{
    return VTBL(pThis)->Stop(THIS);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamPlaybackEngine_SetRect(
    IN  PIXCAMPLAYBACKENGINE       pThis,
    IN CONST D3DRECT              *pRect
    )
{
    return VTBL(pThis)->SetRect(THIS_ pRect);
}

FORCEINLINE
STDMETHODIMP_(VOID)
IXCamPlaybackEngine_Render(
    IN  PIXCAMPLAYBACKENGINE       pThis
    )
{
    return VTBL(pThis)->Render(THIS);
}

FORCEINLINE
STDMETHODIMP_(DWORD)
IXCamPlaybackEngine_GetNextFrame(
    IN     PIXCAMPLAYBACKENGINE    pThis,
    IN OUT D3DLOCKED_RECT         *pYBuffer,
    IN OUT D3DLOCKED_RECT         *pUBuffer,
    IN OUT D3DLOCKED_RECT         *pVBuffer
    )
{
    return VTBL(pThis)->GetNextFrame(THIS_ pYBuffer, pUBuffer, pVBuffer);
}


#pragma pop_macro("VTBL")
#pragma pop_macro("THIS")
#pragma pop_macro("THIS_")

#ifdef __cplusplus
}
#endif

#endif // __XCAM_H__
