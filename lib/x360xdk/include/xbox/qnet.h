
/*
 * Copyright (c) Microsoft Corporation
 *
 * Defines the interface to the Quick Network library
 */

#ifndef __QNET_H__
#define __QNET_H__



#ifndef __cplusplus
#error "QNet requires C++!"
#endif // end if not defined __cplusplus


#ifdef _XBOX
#include <xcam.h>
#endif


#define QNET_S_OK                       S_OK
#define QNET_S_ALREADY_SET              S_FALSE
#define QNET_E_ABORTED                  HRESULT_FROM_WIN32(ERROR_REQUEST_ABORTED)
#define QNET_E_ALREADY_EXISTS           HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS)
#define QNET_E_BUFFER_TOO_SMALL         HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER)
#define QNET_E_DOES_NOT_EXIST           HRESULT_FROM_WIN32(ERROR_NOT_FOUND)
#define QNET_E_INVALID_ARG              E_INVALIDARG
#define QNET_E_INVALID_SESSION_TYPE     HRESULT_FROM_WIN32(ERROR_INVALID_CATEGORY)
#define QNET_E_INVALID_STATE            HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE_STATE)
#define QNET_E_NOT_HOST                 HRESULT_FROM_WIN32(ERROR_PRIVILEGE_NOT_HELD)
#define QNET_E_NOT_IMPLEMENTED          E_NOTIMPL
#define QNET_E_NOT_SIGNED_IN            HRESULT_FROM_WIN32(ERROR_NOT_LOGGED_ON)
#define QNET_E_OUT_OF_MEMORY            E_OUTOFMEMORY
#define QNET_E_PENDING                  HRESULT_FROM_WIN32(ERROR_IO_PENDING)
#define QNET_E_REMOVED                  HRESULT_FROM_WIN32(ERROR_DEVICE_REMOVED)
#define QNET_E_SERVER_ERROR             XONLINE_E_SERVER_ERROR
#define QNET_E_SESSION_FULL             XONLINE_E_SESSION_FULL
#define QNET_E_SESSION_ENDED_BY_HOST    HRESULT_FROM_WIN32(ERROR_GRACEFUL_DISCONNECT)
#define QNET_E_TASK_BUSY                HRESULT_FROM_WIN32(ERROR_BUSY)
#define QNET_E_VERSION_MISMATCH         HRESULT_FROM_WIN32(ERROR_REVISION_MISMATCH)


#define QNET_MAX_NUM_PLAYERS            31

#define QNET_USER_MASK_USER0            0x1
#define QNET_USER_MASK_USER1            0x2
#define QNET_USER_MASK_USER2            0x4
#define QNET_USER_MASK_USER3            0x8

#define QNET_SENDDATA_RELIABLE          0x00000001 // ensure that the data arrives or else the connection is lost
#define QNET_SENDDATA_SEQUENTIAL        0x00000002 // require all previous QNET_SENDDATA_SEQUENTIAL sends to be received before this one
#define QNET_SENDDATA_VIA_HOST          0x00000004 // sends data through host rather than directly to target(s)

#define QNET_COMMFILTER_ALLOW_ALL       0xFFFFFFFF
#define QNET_COMMFILTER_ALLOW_NONE      0x00000000


typedef enum _QNET_SEARCHSTATE
{
    QNET_SEARCHSTATE_RETRIEVING_LIST, // the list of available sessions is being retrieved
    QNET_SEARCHSTATE_TESTING_QOS,     // QoS lookups are being performed on the available sessions
    QNET_SEARCHSTATE_DONE             // the search has completed
} QNET_SEARCHSTATE, * PQNET_SEARCHSTATE;

typedef enum _QNET_SESSIONTYPE
{
    QNET_SESSIONTYPE_LOCAL,             // local multiplayer only
    QNET_SESSIONTYPE_SYSTEMLINK,        // System Link multiplayer
    QNET_SESSIONTYPE_XBOXLIVE_STANDARD, // Xbox Live multiplayer using standard matchmaking
    QNET_SESSIONTYPE_XBOXLIVE_RANKED    // Xbox Live multiplayer using ranked matchmaking and arbitration
} QNET_SESSIONTYPE, * PQNET_SESSIONTYPE;

typedef enum _QNET_STATE
{
    QNET_STATE_IDLE,
    QNET_STATE_SESSION_HOSTING,
    QNET_STATE_SESSION_JOINING,
    QNET_STATE_GAME_LOBBY,
    QNET_STATE_SESSION_REGISTERING,
    QNET_STATE_SESSION_STARTING,
    QNET_STATE_GAME_PLAY,
    QNET_STATE_SESSION_ENDING,
    QNET_STATE_SESSION_LEAVING,
    QNET_STATE_SESSION_DELETING
} QNET_STATE, * PQNET_STATE;

typedef enum _QNET_CAMERA_STREAMS
{
    QNET_CAMERA_STREAMS_NONE,
    QNET_CAMERA_STREAMS_SEND,
    QNET_CAMERA_STREAMS_RECV,
    QNET_CAMERA_STREAMS_BOTH
} QNET_CAMERA_STREAMS, * PQNET_CAMERA_STREAMS;

typedef enum _QNET_PRESENCE_JOIN_MODE
{
    QNET_PRESENCE_JOIN_MODE_NOT_ALLOWED,
    QNET_PRESENCE_JOIN_MODE_EVERYONE,
    QNET_PRESENCE_JOIN_MODE_FRIENDS_ONLY,
} QNET_PRESENCE_JOIN_MODE, * PQNET_PRESENCE_JOIN_MODE;

typedef enum _QNET_OPTION_TYPE
{
    QNET_OPTION_TYPE_NOTIFY_LISTENER            = 0x00000000,
    QNET_OPTION_TYPE_TOTAL_PUBLIC_SLOTS         = 0x00000001,
    QNET_OPTION_TYPE_TOTAL_PRIVATE_SLOTS        = 0x00000002,
    QNET_OPTION_TYPE_FILLED_PUBLIC_SLOTS        = 0x00000003,
    QNET_OPTION_TYPE_FILLED_PRIVATE_SLOTS       = 0x00000004,
    QNET_OPTION_TYPE_XSESSION_HANDLE            = 0x00000005,
    QNET_OPTION_TYPE_SESSIONTYPE                = 0x00000006,
    QNET_OPTION_TYPE_JOIN_IN_PROGRESS_ALLOWED   = 0x00000007,
    QNET_OPTION_TYPE_INVITES_ALLOWED            = 0x00000008,
    QNET_OPTION_TYPE_PRESENCE_JOIN_MODE         = 0x00000009,
    QNET_OPTION_TYPE_CALLBACK_INTERFACE         = 0x0000000A,
    QNET_OPTION_TYPE_QOS_DATA_BUFFER            = 0x0000000B,
    QNET_OPTION_TYPE_XHVENGINE_INTERFACE        = 0x0000000C,
    QNET_OPTION_TYPE_XCAMSTREAMENGINE_INTERFACE = 0x0000000D,
    QNET_OPTION_TYPE_IMMEDIATE_SENDS_ALLOWED    = 0x0000000E,
    QNET_OPTION_TYPE_NEVER_DROP_CONNECTIONS     = 0x0000000F,
} QNET_OPTION_TYPE, * PQNET_OPTION_TYPE;


//
// IQNetPlayer interface definition
//
class IQNetPlayer
{
public:
    virtual
    XUID
    GetXuid(
        ) = 0;

    virtual
    DWORD
    GetUserIndex(
        ) = 0;

    virtual
    DWORD
    GetSessionIndex(
        ) = 0;

    virtual
    ULONG_PTR
    GetCustomDataValue(
        ) = 0;

    virtual
    VOID
    SetCustomDataValue(
        IN ULONG_PTR                        ulpCustomDataValue
        ) = 0;

    virtual
    LPCWSTR
    GetGamertag(
        ) = 0;

    virtual
    XONLINE_NAT_TYPE
    GetNatType(
        ) = 0;

    virtual
    HRESULT
    GetXnaddr(
        OUT XNADDR *                        pxnaddr
        ) = 0;

    virtual
    DWORD
    GetCurrentRtt(
        ) = 0;

    virtual
    BOOL
    IsLocal(
        ) = 0;

    virtual
    BOOL
    IsHost(
        ) = 0;

    virtual
    BOOL
    IsPrivateSlot(
        ) = 0;

    virtual
    BOOL
    HasVoice(
        ) = 0;

    virtual
    BOOL
    HasCamera(
        ) = 0;

    virtual
    BOOL
    IsTalking(
        ) = 0;

    virtual
    BOOL
    IsReady(
        ) = 0;

    virtual
    BOOL
    IsMutedByLocalUser(
        IN DWORD                            dwUserIndex
        ) = 0;

    virtual
    BOOL
    IsSameSystem(
        IN IQNetPlayer *                    pPlayerOther
        ) = 0;

    virtual
    HRESULT
    SetReady(
        IN BOOL                             bReady
        ) = 0;

    virtual
    HRESULT
    SendData(
        IN IQNetPlayer *                    pPlayerTarget     OPTIONAL,
        IN const void *                     pvData,
        IN DWORD                            dwDataSize,
        IN DWORD                            dwFlags
        ) = 0;

    virtual
    HRESULT
    RemoveSystemFromGame(
        ) = 0;

    virtual
    IQNetPlayer *
    GetPlayerOnSameSystem(
        IN DWORD                            dwUserIndex
        ) = 0;

    virtual
    HRESULT
    WriteStats(
        IN DWORD                            dwNumViews,
        IN CONST XSESSION_VIEW_PROPERTIES * pViews
        ) = 0;

    virtual
    VOID
    GetCommFilter(
        OUT DWORD *                         pdwVoiceSendMask  OPTIONAL,
        OUT DWORD *                         pdwVoiceRecvMask  OPTIONAL,
        OUT DWORD *                         pdwCameraSendMask OPTIONAL,
        OUT DWORD *                         pdwCameraRecvMask OPTIONAL
        ) = 0;

    virtual
    HRESULT
    SetCommFilter(
        IN DWORD                            dwVoiceSendMask,
        IN DWORD                            dwVoiceRecvMask,
        IN DWORD                            dwCameraSendMask,
        IN DWORD                            dwCameraRecvMask
        ) = 0;

};


#ifdef _XBOX
//
// IQNetCameraManager interface definition
//
class IQNetCameraManager
{
public:
    virtual
    VOID
    Destroy(
        ) = 0;

    virtual
    VOID
    SetCameraStreams(
        IN QNET_CAMERA_STREAMS              CameraStreams
        ) = 0;

    virtual
    VOID
    SetCameraView(
        IN XCAMZOOMFACTOR                   ZoomFactor,
        IN int                              xCenter,
        IN int                              yCenter
        ) = 0;

    virtual
    BOOL
    IsSetCameraViewPending(
        ) = 0;

    virtual
    HRESULT
    SetRenderRectForSystem(
        IN IQNetPlayer *                    pPlayerOnSystem OPTIONAL,
        IN CONST D3DRECT *                  pRect
        ) = 0;

    virtual
    HRESULT
    SetRemoteSystemDefaultTexture(
        IN IQNetPlayer *                    pPlayerOnSystem,
        IN D3DTexture *                     pDefaultTexture OPTIONAL
        ) = 0;

    virtual
    HRESULT
    RenderSystem(
        IN IQNetPlayer *                    pPlayerOnSystem OPTIONAL
        ) = 0;

    virtual
    HRESULT
    GetNextFrameForRemoteSystem(
        IN IQNetPlayer *                    pPlayerOnSystem,
        IN OUT D3DLOCKED_RECT *             pYBuffer,
        IN OUT D3DLOCKED_RECT *             pUBuffer,
        IN OUT D3DLOCKED_RECT *             pVBuffer
        ) = 0;

    virtual
    HRESULT
    GetNextLocalPreviewFrame(
        IN OUT D3DLOCKED_RECT *             pBuffer
        ) = 0;

    virtual
    HRESULT
    GetNextFrameForSystemRGB(
        IN IQNetPlayer *                    pPlayerOnSystem OPTIONAL,
        IN OUT D3DLOCKED_RECT *             pBuffer
        ) = 0;
};
#endif


//
// IQNetGameSearch interface definition
//
class IQNetGameSearch
{
public:
    virtual
    VOID
    Destroy(
        ) = 0;

    virtual
    QNET_SEARCHSTATE
    GetState(
        ) = 0;

    virtual
    BOOL
    IsComplete(
        ) = 0;

    virtual
    HRESULT
    GetResultCode(
        ) = 0;

    virtual
    VOID
    Abort(
        ) = 0;

    virtual
    DWORD
    GetNumResults(
        ) = 0;

    virtual
    const XSESSION_SEARCHRESULT *
    GetSearchResultAtIndex(
        IN DWORD                            dwIndex
        ) = 0;

    virtual
    const XNQOSINFO *
    GetQosInfoAtIndex(
        IN DWORD                            dwIndex
        ) = 0;
};


//
// IQNetCallbacks interface definition
//
class IQNetCallbacks
{
public:
    virtual
    VOID
    NotifyStateChanged(
        IN QNET_STATE               OldState,
        IN QNET_STATE               NewState,
        IN HRESULT                  hrInfo
        ) = 0;

    virtual
    VOID
    NotifyPlayerJoined(
        IN IQNetPlayer *            pPlayer
        ) = 0;

    virtual
    VOID
    NotifyPlayerLeaving(
        IN IQNetPlayer *            pPlayer
        ) = 0;

    virtual
    VOID
    NotifyNewHost(
        IN IQNetPlayer *            pPlayer
        ) = 0;

    virtual
    VOID
    NotifyDataReceived(
        IN IQNetPlayer *            pPlayerFrom,
        IN DWORD                    dwNumPlayersTo,
        IN IQNetPlayer **           apPlayersTo,
        IN const BYTE *             pbData,
        IN DWORD                    dwDataSize
        ) = 0;

    virtual
    VOID
    NotifyWriteStats(
        IN IQNetPlayer *            pPlayer
        ) = 0;

    virtual
    VOID
    NotifyReadinessChanged(
        IN IQNetPlayer *            pPlayer,
        IN BOOL                     bReady
        ) = 0;

    virtual
    VOID
    NotifyCommSettingsChanged(
        IN IQNetPlayer *            pPlayer
        ) = 0;

    virtual
    VOID
    NotifyGameSearchComplete(
        IN IQNetGameSearch *        pGameSearch,
        IN HRESULT                  hrComplete,
        IN DWORD                    dwNumResults
        ) = 0;

    virtual
    VOID
    NotifyGameInvite(
        IN DWORD                    dwUserIndex,
        IN const XINVITE_INFO *     pInviteInfo
        ) = 0;

    virtual
    VOID
    NotifyContextChanged(
        IN const XUSER_CONTEXT *    pContext
        ) = 0;

    virtual
    VOID
    NotifyPropertyChanged(
        IN const XUSER_PROPERTY *   pProperty
        ) = 0;
};


//
// IQNet interface definition
//
class IQNet
{
public:
    virtual
    VOID
    Destroy(
        ) = 0;

    virtual
    VOID
    DoWork(
        ) = 0;

    virtual
    HRESULT
    HostGame(
        IN DWORD                            dwUserIndexHost,
        IN DWORD                            dwUserMask,
        IN DWORD                            dwPublicSlots,
        IN DWORD                            dwPrivateSlots,
        IN DWORD                            cProperties          OPTIONAL,
        IN const XUSER_PROPERTY *           pProperties          OPTIONAL,
        IN DWORD                            cContexts,
        IN const XUSER_CONTEXT *            pContexts
        ) = 0;

    virtual
    HRESULT
    JoinGameFromSearchResult(
        IN DWORD                            dwUserIndex,
        IN DWORD                            dwUserMask,
        IN const XSESSION_SEARCHRESULT *    pSearchResult
        ) = 0;

    virtual
    HRESULT
    JoinGameFromInviteInfo(
        IN DWORD                            dwUserIndex,
        IN DWORD                            dwUserMask,
        IN const XINVITE_INFO *             pInviteInfo
        ) = 0;

    virtual
    HRESULT
    LeaveGame(
        IN BOOL                             bMigrateHost
        ) = 0;

    virtual
    HRESULT
    StartGame(
        ) = 0;

    virtual
    HRESULT
    EndGame(
        ) = 0;

#ifdef _XBOX
    virtual
    HRESULT
    CreateCameraManager(
        IN XCAMRESOLUTION                   Resolution, 
        IN XCAMFRAMERATE                    Framerate, 
        IN DWORD                            dwBitRate,
        IN IDirect3DDevice9 *               pd3dDevice           OPTIONAL,
        OUT IQNetCameraManager **           ppIQNetCameraManager
        ) = 0;
#else
    virtual
    HRESULT
    CreateCameraManager(
        IN DWORD                            dwReserved1          OPTIONAL, 
        IN DWORD                            dwReserved2          OPTIONAL, 
        IN DWORD                            dwReserved3          OPTIONAL,
        IN void *                           pvReserved4          OPTIONAL,
        OUT void **                         ppvReserved5         OPTIONAL 
        ) = 0;
#endif

    virtual
    HRESULT
    CreateGameSearch(
        IN DWORD                            dwUserIndex,
        IN DWORD                            dwUserMask,
        IN DWORD                            dwMatchQueryIndex,
        IN DWORD                            dwMaxResults,
        IN DWORD                            cProperties          OPTIONAL,
        IN const XUSER_PROPERTY *           pProperties          OPTIONAL,
        IN DWORD                            cContexts,
        IN const XUSER_CONTEXT *            pContexts,
        OUT IQNetGameSearch **              ppGameSearch
        ) = 0;

    virtual
    HRESULT
    CreateGameSearchById(
        IN DWORD                            dwUserIndex,
        IN XNKID                            xnkidSessionId,
        OUT IQNetGameSearch **              ppGameSearch
        ) = 0;

    virtual
    BOOL
    IsHost(
        ) = 0;

    virtual
    IQNetPlayer *
    GetHostPlayer(
        ) = 0;

    virtual
    DWORD
    GetPlayerCount(
        ) = 0;

    virtual
    IQNetPlayer *
    GetPlayerByIndex(
        IN DWORD                            dwPlayerIndex
        ) = 0;

    virtual
    IQNetPlayer *
    GetPlayerByXuid(
        IN XUID                             xuid
        ) = 0;

    virtual
    IQNetPlayer *
    GetLocalPlayerByUserIndex(
        IN DWORD                            dwUserIndex
        ) = 0;

    virtual
    HRESULT
    AddLocalPlayerByUserIndex(
        IN DWORD                            dwUserIndex
        ) = 0;

    virtual
    HRESULT
    RemoveLocalPlayerByUserIndex(
        IN DWORD                            dwUserIndex
        ) = 0;

    virtual
    HRESULT
    ResetReady(
        ) = 0;

    virtual
    BOOL
    IsEveryoneReady(
        ) = 0;

    virtual
    HRESULT
    SetGameContext(
        IN const XUSER_CONTEXT *            pContext
        ) = 0;

    virtual
    const XUSER_CONTEXT *
    GetGameContext(
        IN DWORD                            dwContextId
        ) = 0;

    virtual
    HRESULT
    SetGameProperty(
        IN const XUSER_PROPERTY *           pProperty
        ) = 0;

    virtual
    const XUSER_PROPERTY *
    GetGameProperty(
        IN DWORD                            dwPropertyId
        ) = 0;

    virtual
    HRESULT
    FlushStats(
        IN OUT XOVERLAPPED *                pXOverlapped         OPTIONAL
        ) = 0;

    virtual
    QNET_STATE
    GetState(
        ) = 0;

    virtual
    HRESULT
    GetLastStateResult(
        ) = 0;

    virtual
    HRESULT
    Notify(
        IN DWORD                            dwID,
        IN ULONG_PTR                        Param
        ) = 0;

    virtual
    HRESULT
    GetOpt(
        IN QNET_OPTION_TYPE                 OptionType,
        IN OUT void *                       pvOptionData,
        IN OUT DWORD *                      pdwOptionDataSize
        ) = 0;

    virtual
    HRESULT
    SetOpt(
        IN QNET_OPTION_TYPE                 OptionType,
        IN void *                           pvOptionData,
        IN DWORD                            dwOptionDataSize
        ) = 0;
};



HRESULT
WINAPI
QNetCreate(
    IN QNET_SESSIONTYPE     SessionType,
    IN IQNetCallbacks *     pIQNetCallbacks,
    OUT IQNet **            ppIQNet
    );


#endif // end if not defined __QNET_H__
