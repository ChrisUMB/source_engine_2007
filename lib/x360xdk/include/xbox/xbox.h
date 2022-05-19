/************************************************************************
*                                                                       *
*   Xbox.h -- This module defines the Xbox APIs                         *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/
#pragma once

#ifndef _XBOX_H_
#define _XBOX_H_


//
// Define API decoration for direct importing of DLL references.
//

#define XBOXAPI

#ifdef __cplusplus
extern "C" {
#endif

#include <xconfig.h>
#include <xinputdefs.h>

#define XUSER_NAME_SIZE                 16
#define XUSER_MAX_NAME_LENGTH           (XUSER_NAME_SIZE - 1)

typedef ULONGLONG                       XUID;
typedef XUID                            *PXUID;

#define INVALID_XUID                    ((XUID) 0)

XBOXAPI
FORCEINLINE
BOOL
WINAPI
IsEqualXUID(
    IN      XUID                        xuid1,
    IN      XUID                        xuid2
    )
{
    return (xuid1 == xuid2);
}

XBOXAPI
FORCEINLINE
BOOL
WINAPI
IsTeamXUID(
    XUID xuid
    )
{
    return (xuid & 0xFF00000000000000) == 0xFE00000000000000;
}


#ifndef _NTOS_
#define XGetLanguage    XTLGetLanguage
#endif

XBOXAPI
DWORD
WINAPI
XGetLanguage(
    VOID
    );

XBOXAPI
DWORD
WINAPI
XGetLocale(
    VOID
    );


typedef struct _XVIDEO_MODE {
    DWORD                               dwDisplayWidth;
    DWORD                               dwDisplayHeight;
    BOOL                                fIsInterlaced;
    BOOL                                fIsWideScreen;
    BOOL                                fIsHiDef;
    float                               RefreshRate;
    DWORD                               VideoStandard;
    DWORD                               Reserved[5];
} XVIDEO_MODE, *PXVIDEO_MODE;

#define XC_VIDEO_STANDARD_NTSC_M        1
#define XC_VIDEO_STANDARD_NTSC_J        2
#define XC_VIDEO_STANDARD_PAL_I         3

XBOXAPI
VOID
WINAPI
XGetVideoMode(
    OUT     PXVIDEO_MODE                pVideoMode
    );

#define XC_VIDEO_FLAGS_WIDESCREEN       0x00000001
#define XC_VIDEO_FLAGS_HDTV_720p        0x00000002
#define XC_VIDEO_FLAGS_HDTV_480p        0x00000008
#define XC_VIDEO_FLAGS_HDTV_1080i       0x00000004

#define XC_CONSOLE_REGION_NA            0x00
#define XC_CONSOLE_REGION_ASIA          0x01
#define XC_CONSOLE_REGION_EUROPE        0x02
#define XC_CONSOLE_REGION_RESTOFWORLD   0x03
#define XC_CONSOLE_REGION_MAXIMUM       0x04
#define XC_CONSOLE_REGION_DEVKIT        0x7F

#define XC_GAME_REGION(region, subregion) \
    ((XC_CONSOLE_REGION_##region << 8) | (subregion))

#define XC_GAME_REGION_NA_ALL           XC_GAME_REGION(NA, 0xFF)
#define XC_GAME_REGION_ASIA_ALL         XC_GAME_REGION(ASIA, 0xFF)
#define XC_GAME_REGION_ASIA_JAPAN       XC_GAME_REGION(ASIA, 0x01)
#define XC_GAME_REGION_ASIA_CHINA       XC_GAME_REGION(ASIA, 0x04)
#define XC_GAME_REGION_ASIA_REST        XC_GAME_REGION(ASIA, 0xF8)
#define XC_GAME_REGION_EUROPE_ALL       XC_GAME_REGION(EUROPE, 0xFF)
#define XC_GAME_REGION_EUROPE_AUNZ      XC_GAME_REGION(EUROPE, 0x01)
#define XC_GAME_REGION_EUROPE_REST      XC_GAME_REGION(EUROPE, 0xFE)
#define XC_GAME_REGION_RESTOFWORLD_ALL  XC_GAME_REGION(RESTOFWORLD, 0xFF)
#define XC_GAME_REGION_DEVKIT_ALL       XC_GAME_REGION(DEVKIT, 0xFF)
#define XC_GAME_REGION_MANUFACTURING    0x8000
#define XC_GAME_REGION_UNRESTRICTED     0xFFFF

#define XC_GAME_REGION_REGION(region) \
    (((region) & 0xFF00) >> 8)

XBOXAPI
DWORD
WINAPI
XGetGameRegion(
    VOID
    );

XBOXAPI
DWORD
WINAPI
XInputGetState(
    IN      DWORD                       dwUserIndex,
    OUT     PXINPUT_STATE               pState
    );

XBOXAPI
DWORD
WINAPI
XInputGetCapabilities(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,
    OUT     PXINPUT_CAPABILITIES        pCapabilities
    );

XBOXAPI
DWORD
WINAPI
XInputSetState(
    IN      DWORD                       dwUserIndex,
    IN      PXINPUT_VIBRATION           pVibration
    );


XBOXAPI
DWORD
WINAPI
XInputGetKeyboardState(
    IN      DWORD                       dwUserIndex,
    OUT     PXINPUT_KEYBOARDSTATE       pKeyboardState
    );


#define XINPUT_LANGUAGE_ENGLISH         1
#define XINPUT_LANGUAGE_ENGLISH_UK      2
#define XINPUT_LANGUAGE_JAPANESE        3
#define XINPUT_LANGUAGE_GERMAN          4
#define XINPUT_LANGUAGE_FRENCH          5
#define XINPUT_LANGUAGE_FRENCH_CANADA   6
#define XINPUT_LANGUAGE_ITALIAN         7
#define XINPUT_LANGUAGE_SPANISH         8
#define XINPUT_LANGUAGE_CHINESE_BOPOMOFO    9
#define XINPUT_LANGUAGE_CHINESE_CHAJEI      10
#define XINPUT_LANGUAGE_KOREAN          11
#define XINPUT_LANGUAGE_SWEDISH         12
#define XINPUT_LANGUAGE_PORTUGUESE_PT   13
#define XINPUT_LANGUAGE_PORTUGUESE_BR   14



XBOXAPI
DWORD
WINAPI
XInputGetKeyboardLanguage(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
DWORD
WINAPI
XInputGetKeystroke(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,
    OUT     PXINPUT_KEYSTROKE           pKeystroke
    );

XBOXAPI
DWORD
WINAPI
XInputGetKeystrokeEx(
    IN OUT  PDWORD                      pdwUserIndex,
    IN      DWORD                       dwFlags,
    OUT     PXINPUT_KEYSTROKE           pKeystroke
    );

#if _DEBUG
XBOXAPI
VOID
WINAPI
XInputEnableAutobind(
    IN      BOOL                        fEnable
    );
#else   // _DEBUG
#define XInputEnableAutobind(f)
#endif  // !_DEBUG


XBOXAPI
DWORD
WINAPI
XMountUtilityDrive(
    IN      BOOL                        fFormatClean,
    IN      DWORD                       dwBytesPerCluster,
    IN      SIZE_T                      dwFileCacheSize
    );

#define XMOUNTUTILITYDRIVE_FORMAT0      0x00000001
#define XMOUNTUTILITYDRIVE_FORMAT1      0x00000002
#define XMOUNTUTILITYDRIVE_FORMAT_ALL   0x0000000f

XBOXAPI
DWORD
WINAPI
XMountUtilityDriveEx(
    IN      DWORD                       dwFlags,
    IN      DWORD                       dwBytesPerCluster,
    IN      SIZE_T                      dwFileCacheSize
    );

XBOXAPI
DWORD
WINAPI
XFlushUtilityDrive(
    VOID
    );

XBOXAPI
DWORD
WINAPI
XUnmountUtilityDrive(
    VOID
    );


#define MAX_LAUNCH_DATA_SIZE            1020
#define XLDEMO_RUNMODE_KIOSKMODE        0x01
#define XLDEMO_RUNMODE_USERSELECTED     0x02

typedef struct _LD_DEMO  // Required for launching into demos
{
    DWORD dwID;
    DWORD dwRunmode;
    DWORD dwTimeout;
    CHAR  szLauncherXEX[128];
    CHAR  szLaunchedXEX[128];
} LD_DEMO, *PLD_DEMO;

// value of LD_DEMO.dwID
#define LAUNCH_DATA_DEMO_ID 'CDX1'




XBOXAPI
DWORD
WINAPI
XSetLaunchData(
    IN      PVOID                       pLaunchData,
    IN      DWORD                       dwLaunchDataSize
    );

XBOXAPI
DWORD
WINAPI
XGetLaunchDataSize(
    OUT     LPDWORD                     pdwLaunchDataSize
    );

XBOXAPI
DWORD
WINAPI
XGetLaunchData(
    OUT     PVOID                       pBuffer,
    IN      DWORD                       dwBufferSize
    );

DECLSPEC_NORETURN
XBOXAPI
VOID
WINAPI
XLaunchNewImage(
    IN      LPCSTR                      szImagePath,
    IN      DWORD                       dwFlags
    );


#define XLAUNCH_KEYWORD_DASH            NULL
#define XLAUNCH_KEYWORD_DEFAULT_APP     ""
#define XLAUNCH_KEYWORD_DASH_ARCADE     "XLNI_DASH_ARCADE"
#define XLAUNCH_FLAG_MATCH_MIN_VERSION  0x00010000

XBOXAPI
HMODULE
WINAPI
XLoadLibrary(
    IN      LPCSTR                      szLibFileName,
    IN      DWORD                       dwMinVersion
    );


typedef struct _XSWAPDISC_ERROR_TEXT {
    LPCWSTR wszTitle;
    LPCWSTR wszText;
    LPCWSTR wszButton;
} XSWAPDISC_ERROR_TEXT, *PXSWAPDISC_ERROR_TEXT;

XBOXAPI
DWORD
WINAPI
XSwapDisc(
    IN      UCHAR                       bDiscNum,
    IN      HANDLE                      hComplete,
    IN      CONST XSWAPDISC_ERROR_TEXT* pErrorStrings
    );

XBOXAPI
BOOL
WINAPI
XSwapCancel(
    VOID
    );


typedef struct _XOVERLAPPED             XOVERLAPPED, *PXOVERLAPPED;


XBOXAPI
BOOL
WINAPI
XGetModuleSection(
    IN      HANDLE                      ModuleHandle,
    IN      LPCSTR                      szSectionName,
    OUT     PVOID                       *pSectionData,
    OUT     ULONG                       *pSectionSize
    );


XBOXAPI
DWORD
WINAPI
XSetThreadProcessor(
    IN      HANDLE                      hThread,
    IN      DWORD                       dwHardwareThread
    );

typedef VOID (WINAPI *XTHREAD_NOTIFY_PROC)(BOOL fCreate);
typedef struct _XTHREAD_NOTIFICATION {
    LIST_ENTRY                          ListEntry;
    XTHREAD_NOTIFY_PROC                 pfnNotifyRoutine;
} XTHREAD_NOTIFICATION, *PXTHREAD_NOTIFICATION;

XBOXAPI
VOID
WINAPI
XRegisterThreadNotifyRoutine(
    IN OUT  PXTHREAD_NOTIFICATION       pThreadNotification,
    IN      BOOL                        fRegister
    );

XBOXAPI
VOID
WINAPI
XSetProcessQuantumLength(
    IN      DWORD                       dwMilliseconds
    );

XBOXAPI
DWORD
WINAPI
XGetProcessQuantumLength(
    VOID
    );

XBOXAPI
BOOL
WINAPI
XSetFileCacheSize(
    IN      SIZE_T                      dwCacheSize
    );

XBOXAPI
SIZE_T
WINAPI
XGetFileCacheSize(
    VOID
    );

XBOXAPI
DWORD
WINAPI
XGetFilePhysicalSortKey(
    IN      HANDLE                      hFile
    );


XBOXAPI
VOID
WINAPI
XSaveFloatingPointStateForDpc(
    VOID
    );

XBOXAPI
VOID
WINAPI
XRestoreFloatingPointStateForDpc(
    VOID
    );

#define XLOCKL2_INDEX_XPS                       0
#define XLOCKL2_INDEX_TITLE                     1

#define XLOCKL2_LOCK_SIZE_1_WAY                 (128*1024)
#define XLOCKL2_LOCK_SIZE_2_WAYS                (256*1024)

#define XLOCKL2_FLAG_SUSPEND_REPLACEMENT        0x00000001
#define XLOCKL2_FLAG_NONEXCLUSIVE_REPLACEMENT   0X00000002

XBOXAPI
BOOL
WINAPI
XLockL2(
    IN      DWORD                       dwIndex,
    IN      CONST PVOID                 pRangeStart,
    IN      DWORD                       dwRangeSize,
    IN      DWORD                       dwLockSize,
    IN      DWORD                       dwFlags
    );

VOID
WINAPI
XUnlockL2(
    IN      DWORD                       dwIndex
    );

XBOXAPI
LPVOID
WINAPI
XPhysicalAlloc(
    IN      SIZE_T                      dwSize,
    IN      ULONG_PTR                   ulPhysicalAddress,
    IN      ULONG_PTR                   ulAlignment,
    IN      DWORD                       flProtect
    );

XBOXAPI
LPVOID
WINAPI
XPhysicalAllocEx(
    IN      SIZE_T                      dwSize,
    IN      ULONG_PTR                   ulLowestAcceptableAddress,
    IN      ULONG_PTR                   ulHighestAcceptableAddress,
    IN      ULONG_PTR                   ulAlignment,
    IN      DWORD                       flProtect
    );

XBOXAPI
SIZE_T
WINAPI
XPhysicalSize(
    IN      LPVOID                      lpAddress
    );

XBOXAPI
VOID
WINAPI
XPhysicalProtect(
    IN      LPVOID                      lpAddress,
    IN      SIZE_T                      dwSize,
    IN      DWORD                       flNewProtect
    );

XBOXAPI
VOID
WINAPI
XPhysicalFree(
    IN      LPVOID                      lpAddress
    );

XBOXAPI
DWORD
WINAPI
XQueryMemoryProtect(
    IN      LPVOID                      lpAddress
    );

XBOXAPI
VOID
WINAPI
XEnableSmallPagesOverride(
    IN      BOOL                        fEnable
    );

XBOXAPI
BOOL
WINAPI
XGetSmallPagesOverride(
    );

XBOXAPI
LPVOID
WINAPI
XEncryptedAlloc(
    IN      SIZE_T                      dwSize
    );

XBOXAPI
VOID
WINAPI
XEncryptedFree(
    IN      LPVOID                      lpAddress
    );



// allocation attribute definitions for XMemAlloc and XMemFree APIs

#define XALLOC_MEMTYPE_HEAP                         0
#define XALLOC_MEMTYPE_PHYSICAL                     1

#define XALLOC_MEMPROTECT_WRITECOMBINE_LARGE_PAGES  0
#define XALLOC_MEMPROTECT_NOCACHE                   1
#define XALLOC_MEMPROTECT_READWRITE                 2
#define XALLOC_MEMPROTECT_WRITECOMBINE              3

#define XALLOC_ALIGNMENT_DEFAULT                    0x0
#define XALLOC_ALIGNMENT_4                          0x1
#define XALLOC_ALIGNMENT_8                          0x2
#define XALLOC_ALIGNMENT_16                         0x4

#define XALLOC_PHYSICAL_ALIGNMENT_DEFAULT           0x0 // Default is 4K alignment
#define XALLOC_PHYSICAL_ALIGNMENT_4                 0x2
#define XALLOC_PHYSICAL_ALIGNMENT_8                 0x3
#define XALLOC_PHYSICAL_ALIGNMENT_16                0x4
#define XALLOC_PHYSICAL_ALIGNMENT_32                0x5
#define XALLOC_PHYSICAL_ALIGNMENT_64                0x6
#define XALLOC_PHYSICAL_ALIGNMENT_128               0x7
#define XALLOC_PHYSICAL_ALIGNMENT_256               0x8
#define XALLOC_PHYSICAL_ALIGNMENT_512               0x9
#define XALLOC_PHYSICAL_ALIGNMENT_1K                0xA
#define XALLOC_PHYSICAL_ALIGNMENT_2K                0xB
#define XALLOC_PHYSICAL_ALIGNMENT_4K                0xC
#define XALLOC_PHYSICAL_ALIGNMENT_8K                0xD
#define XALLOC_PHYSICAL_ALIGNMENT_16K               0xE
#define XALLOC_PHYSICAL_ALIGNMENT_32K               0xF

typedef enum _XALLOC_ALLOCATOR_IDS {
    eXALLOCAllocatorId_GameMin                  = 0,
    eXALLOCAllocatorId_GameMax                  = 127,
    eXALLOCAllocatorId_MsReservedMin            = 128,
    eXALLOCAllocatorId_D3D                      = 128,
    eXALLOCAllocatorId_D3DX,
    eXALLOCAllocatorId_XAUDIO,
    eXALLOCAllocatorId_XAPI,
    eXALLOCAllocatorId_XACT,
    eXALLOCAllocatorId_XBOXKERNEL,
    eXALLOCAllocatorId_XBDM,
    eXALLOCAllocatorId_XGRAPHICS,
    eXALLOCAllocatorId_XONLINE,
    eXALLOCAllocatorId_XVOICE,
    eXALLOCAllocatorId_XHV,
    eXALLOCAllocatorId_USB,
    eXALLOCAllocatorId_XMV,
    eXALLOCAllocatorId_SHADERCOMPILER,
    eXALLOCAllocatorId_XUI,
    eXALLOCAllocatorId_XASYNC,
    eXALLOCAllocatorId_XCAM,
    eXALLOCAllocatorId_XVIS,
    eXALLOCAllocatorId_XIME,
    eXALLOCAllocatorId_XFILECACHE,
    eXALLOCAllocatorId_XRN,
    eXALLOCAllocatorID_XMCORE,
    eXALLOCAllocatorID_XMASSIVE,
    eXALLOCAllocatorId_MsReservedMax            = 191,
    eXALLOCAllocatorId_MiddlewareReservedMin    = 192,
    eXALLOCAllocatorId_MiddlewareReservedMax    = 255
} XALLOC_ALLOCATOR_IDS;

// The PPC compiler defines bitfields to be ordered from the MSB to the LSB,
// which is opposite the convention on the X86 platform.  Use the 'bitfield_order'
// pragma to switch the ordering.  This does not affect endianness in any way.

#if defined(_M_PPCBE)
#pragma bitfield_order(push)
#pragma bitfield_order(lsb_to_msb)
#endif

typedef struct _XALLOC_ATTRIBUTES {
    DWORD                               dwObjectType:13;
    DWORD                               dwHeapTracksAttributes:1;
    DWORD                               dwMustSucceed:1;
    DWORD                               dwFixedSize:1;
    DWORD                               dwAllocatorId:8;
    DWORD                               dwAlignment:4;
    DWORD                               dwMemoryProtect:2;
    DWORD                               dwZeroInitialize:1;
    DWORD                               dwMemoryType:1;
} XALLOC_ATTRIBUTES, *PXALLOC_ATTRIBUTES;

#if defined(_M_PPCBE)
#pragma bitfield_order(pop)
#endif

#define MAKE_XALLOC_ATTRIBUTES(ObjectType,\
                               HeapTracksAttributes,\
                               MustSucceed,\
                               FixedSize,\
                               AllocatorId,\
                               Alignment,\
                               MemoryProtect,\
                               ZeroInitialize,\
                               MemoryType)\
    ((DWORD)( ObjectType | \
             (HeapTracksAttributes << 13) | \
             (MustSucceed << 14) | \
             (FixedSize << 15) | \
             (AllocatorId << 16) | \
             (Alignment << 24) | \
             (MemoryProtect << 28) | \
             (ZeroInitialize << 30) | \
             (MemoryType << 31)))

#define XALLOC_IS_PHYSICAL(Attributes)  ((BOOL)(Attributes & 0x80000000)!=0)

XBOXAPI
LPVOID
WINAPI
XMemAlloc(
    IN      SIZE_T                      dwSize,
    IN      DWORD                       dwAllocAttributes
    );

XBOXAPI
LPVOID
WINAPI
XMemAllocDefault(
    IN      SIZE_T                      dwSize,
    IN      DWORD                       dwAllocAttributes
    );

XBOXAPI
VOID
WINAPI
XMemFree(
    IN OUT  PVOID                       pAddress,
    IN      DWORD                       dwAllocAttributes
    );

XBOXAPI
VOID
WINAPI
XMemFreeDefault(
    IN OUT  PVOID                       pAddress,
    IN      DWORD                       dwAllocAttributes
    );

XBOXAPI
SIZE_T
WINAPI
XMemSize(
    IN      PVOID                       pAddress,
    IN      DWORD                       dwAllocAttributes
    );

XBOXAPI
SIZE_T
WINAPI
XMemSizeDefault(
    IN      PVOID                       pAddress,
    IN      DWORD                       dwAllocAttributes
    );

XBOXAPI
VOID
WINAPI
XSetAttributesOnHeapAlloc(
    IN      PVOID                       pBaseAddress,
    IN      DWORD                       dwAllocAttributes
    );

XBOXAPI
DWORD
WINAPI
XGetAttributesOnHeapAlloc(
    IN      PVOID                       pBaseAddress
    );

XBOXAPI
PVOID
WINAPI
XMemSet128(
    OUT     PVOID                       pDest,
    IN      INT                         c,
    IN      SIZE_T                      count
    );

XBOXAPI
PVOID
WINAPI
XMemSet(
    OUT     PVOID                       pDest,
    IN      INT                         c,
    IN      SIZE_T                      count
    );

XBOXAPI
PVOID
WINAPI
XMemCpy128(
    OUT     PVOID                       pDest,
    IN      CONST VOID*                 pSrc,
    IN      SIZE_T                      count
    );

XBOXAPI
PVOID
WINAPI
XMemCpy(
    OUT     PVOID                       pDest,
    IN      CONST VOID*                 pSrc,
    IN      SIZE_T                      count
    );

XBOXAPI
PVOID
WINAPI
XMemCpyStreaming(
    OUT     PVOID                       pDest,
    IN      CONST VOID*                 pSrc,
    IN      SIZE_T                      count
    );

XBOXAPI
PVOID
WINAPI
XMemCpyStreaming_Cached(
    OUT     PVOID                       pDest,
    IN      CONST VOID*                 pSrc,
    IN      SIZE_T                      count
    );

XBOXAPI
PVOID
WINAPI
XMemCpyStreaming_WriteCombined(
    OUT     PVOID                       pDest,
    IN      CONST VOID*                 pSrc,
    IN      SIZE_T                      count
    );

XBOXAPI
DWORD
WINAPI
XMemGetPageSize(
    const VOID* address
    );

// XMemCompress/XMemDecompress:

#include <xcompress.h>

#define XVER_DEVKIT                     1
#define XVER_RETAIL                     2

#ifdef _DEBUG

XBOXAPI
DWORD
WINAPI
XDebugGetSystemVersionA(
    OUT     LPSTR                       szVersionString,
    IN      UINT                        cchVersionString
    );
#define XDebugGetSystemVersion          XDebugGetSystemVersionA

XBOXAPI
DWORD
WINAPI
XDebugGetXTLVersionA(
    OUT     LPSTR                       szVersionString,
    IN      UINT                        cchVersionString
    );
#define XDebugGetXTLVersion             XDebugGetXTLVersionA

#endif  // _DEBUG


// Xbox-specific Overlapped

typedef
VOID
(WINAPI *PXOVERLAPPED_COMPLETION_ROUTINE)(
    IN      DWORD                       dwErrorCode,
    IN      DWORD                       dwNumberOfBytesTransfered,
    IN OUT  PXOVERLAPPED                pOverlapped
    );


typedef struct _XOVERLAPPED {
    ULONG_PTR                           InternalLow;
    ULONG_PTR                           InternalHigh;
    ULONG_PTR                           InternalContext;
    HANDLE                              hEvent;
    PXOVERLAPPED_COMPLETION_ROUTINE     pCompletionRoutine;
    DWORD_PTR                           dwCompletionContext;
    DWORD                               dwExtendedError;
} XOVERLAPPED, *PXOVERLAPPED;

#define XHasOverlappedIoCompleted(lpOverlapped) \
    (*((volatile ULONG_PTR*)(&(lpOverlapped)->InternalLow)) != ERROR_IO_PENDING)

XBOXAPI
DWORD
WINAPI
XGetOverlappedResult(
    IN      PXOVERLAPPED                pOverlapped,
    OUT     LPDWORD                     pdwResult           OPTIONAL,
    IN      BOOL                        bWait
    );

XBOXAPI
DWORD
WINAPI
XGetOverlappedExtendedError(
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XCancelOverlapped(
    IN      PXOVERLAPPED                pOverlapped
    );

// XContent

// Content types
//  Content type ranges
#define XCONTENTTYPE_SAVEDGAME                      0x00000001
#define XCONTENTTYPE_MARKETPLACE                    0x00000002
#define XCONTENTTYPE_PUBLISHER                      0x00000003

//  Content creation/open flags
#define XCONTENTFLAG_NONE                           0x00000000
#define XCONTENTFLAG_CREATENEW                      CREATE_NEW
#define XCONTENTFLAG_CREATEALWAYS                   CREATE_ALWAYS
#define XCONTENTFLAG_OPENEXISTING                   OPEN_EXISTING
#define XCONTENTFLAG_OPENALWAYS                     OPEN_ALWAYS
#define XCONTENTFLAG_TRUNCATEEXISTING               TRUNCATE_EXISTING

//  Content attributes
#define XCONTENTFLAG_NOPROFILE_TRANSFER             0x00000010
#define XCONTENTFLAG_NODEVICE_TRANSFER              0x00000020
#define XCONTENTFLAG_STRONG_SIGNED                  0x00000040
#define XCONTENTFLAG_ALLOWPROFILE_TRANSFER          0x00000080
#define XCONTENTFLAG_MOVEONLY_TRANSFER              0x00000800

//  Device selector flags
#define XCONTENTFLAG_MANAGESTORAGE                  0x00000100
#define XCONTENTFLAG_FORCE_SHOW_UI                  0x00000200

//  Enumeration scoping
#define XCONTENTFLAG_ENUM_EXCLUDECOMMON             0x00001000


#define XCONTENT_MAX_DISPLAYNAME_LENGTH 128
#define XCONTENT_MAX_FILENAME_LENGTH    42
#define XCONTENTDEVICE_MAX_NAME_LENGTH  27

typedef DWORD                           XCONTENTDEVICEID, *PXCONTENTDEVICEID;

#define XCONTENTDEVICE_ANY              ((XCONTENTDEVICEID)0)

typedef struct _XCONTENT_DATA
{
    XCONTENTDEVICEID                    DeviceID;
    DWORD                               dwContentType;
    WCHAR                               szDisplayName[XCONTENT_MAX_DISPLAYNAME_LENGTH];
    CHAR                                szFileName[XCONTENT_MAX_FILENAME_LENGTH];
} XCONTENT_DATA, *PXCONTENT_DATA;


typedef DWORD                           XCONTENTDEVICETYPE, *PXCONTENTDEVICETYPE;

// Device types
#define XCONTENTDEVICETYPE_HDD          ((XCONTENTDEVICETYPE)1)
#define XCONTENTDEVICETYPE_MU           ((XCONTENTDEVICETYPE)2)

typedef struct _XDEVICE_DATA
{
    XCONTENTDEVICEID                    DeviceID;
    XCONTENTDEVICETYPE                  DeviceType;
    ULONGLONG                           ulDeviceBytes;
    ULONGLONG                           ulDeviceFreeBytes;
    WCHAR                               wszFriendlyName[XCONTENTDEVICE_MAX_NAME_LENGTH];
} XDEVICE_DATA, *PXDEVICE_DATA;


#define XCONTENT_NONE                   0x00000000
#define XCONTENT_CREATED_NEW            0x00000001
#define XCONTENT_OPENED_EXISTING        0x00000002

XBOXAPI
DWORD
WINAPI
XContentCreate(
    IN      DWORD                       dwUserIndex,
    IN      LPCSTR                      szRootName,
    IN      CONST XCONTENT_DATA*        pContentData,
    IN      DWORD                       dwContentFlags,
    OUT     PDWORD                      pdwDisposition      OPTIONAL,
    OUT     PDWORD                      pdwLicenseMask      OPTIONAL,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XContentCreateEx(
    IN      DWORD                       dwUserIndex,
    IN      LPCSTR                      szRootName,
    IN      CONST XCONTENT_DATA*        pContentData,
    IN      DWORD                       dwContentFlags,
    OUT     PDWORD                      pdwDisposition      OPTIONAL,
    OUT     PDWORD                      pdwLicenseMask      OPTIONAL,
    IN      SIZE_T                      dwFileCacheSize,
    IN      ULARGE_INTEGER              uliContentSize,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XContentDelete(
    IN      DWORD                       dwUserIndex         OPTIONAL,
    IN      CONST XCONTENT_DATA*        pContentData,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XContentInstall(
    IN      DWORD                       dwUserIndex,
    IN      XCONTENTDEVICEID            DeviceID,
    IN      LPCSTR                      pszFileName,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XContentClose(
    IN      LPCSTR                      szRootName,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XContentFlush(
    IN      LPCSTR                      szRootName,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XContentSetThumbnail(
    IN      DWORD                       dwUserIndex,
    IN      CONST XCONTENT_DATA*        pContentData,
    IN      CONST BYTE*                 pbThumbnail,
    IN      DWORD                       cbThumbnail,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XContentGetThumbnail(
    IN      DWORD                       dwUserIndex,
    IN      CONST XCONTENT_DATA*        pContentData,
    OUT     PBYTE                       pbThumbnail,        OPTIONAL
    IN OUT  PDWORD                      pcbThumbnail,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XContentGetCreator(
    IN      DWORD                       dwUserIndex,
    IN      CONST XCONTENT_DATA*        pContentData,
    OUT     PBOOL                       pfUserIsCreator,
    OUT     PXUID                       pxuid,              OPTIONAL
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XContentGetLicenseMask(
    OUT     PDWORD                      pdwLicenseMask,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XContentLaunchImage(
    IN      DWORD                       dwUserIndex,
    IN      CONST XCONTENT_DATA*        pContentData,
    IN      LPCSTR                      szImagePath
    );

XBOXAPI
ULONGLONG
WINAPI
XContentCalculateSize(
    IN      ULONGLONG                   cbData,
    IN      DWORD                       cDirectories
    );

XBOXAPI
DWORD
WINAPI
XContentGetDeviceState(
    IN      XCONTENTDEVICEID            DeviceID,
    IN OUT  PXOVERLAPPED                pOverlapped
    );

XBOXAPI
DWORD
WINAPI
XContentGetDeviceStateByHandle(
    IN      CONST XCONTENT_DATA*        pContentData,
    IN OUT  PXOVERLAPPED                pOverlapped
    );

XBOXAPI
DWORD
WINAPI
XContentOpenPackage(
    IN      DWORD                       dwUserIndex,
    IN      CONST XCONTENT_DATA*        pContentData,
    OUT     HANDLE *                    phPackageFile
    );

XBOXAPI
DWORD
WINAPI
XContentCreatePackage(
    IN      DWORD                       dwUserIndex,
    IN      CONST XCONTENT_DATA*        pContentData,
    IN      BOOL                        fFailIfExists,
    OUT     HANDLE*                     phPackageFile
    );

XBOXAPI
DWORD
WINAPI
XContentGetDeviceData(
    IN      XCONTENTDEVICEID            DeviceID,
    OUT     PXDEVICE_DATA               pDeviceData
    );

XBOXAPI
DWORD
WINAPI
XContentGetDeviceName(
    IN      XCONTENTDEVICEID            DeviceID,
    OUT     LPWSTR                      wszName,
    IN      DWORD                       cchName
    );


XBOXAPI
DWORD
WINAPI
XContentCreateEnumerator(
    IN      DWORD                       dwUserIndex,
    IN      XCONTENTDEVICEID            DeviceID,
    IN      DWORD                       dwContentType,
    IN      DWORD                       dwContentFlags,
    IN      DWORD                       cItem,
    OUT     PDWORD                      pcbBuffer           OPTIONAL,
    OUT     PHANDLE                     phEnum
    );

typedef struct _XOFFERING_CONTENTAVAILABLE_RESULT
{
    DWORD                               dwNewOffers;
    DWORD                               dwTotalOffers;
} XOFFERING_CONTENTAVAILABLE_RESULT;

XBOXAPI
DWORD
WINAPI
XContentGetMarketplaceCounts(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwContentCategories,
    IN      DWORD                       cbResults,
    IN OUT  XOFFERING_CONTENTAVAILABLE_RESULT   *pResults,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XEnumerate(
    IN      HANDLE                      hEnum,
    IN OUT  PVOID                       pvBuffer,
    IN      DWORD                       cbBuffer,
    OUT     PDWORD                      pcItemsReturned     OPTIONAL,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XEnumerateBack(
    IN      HANDLE                      hEnum,
    IN OUT  PVOID                       pvBuffer,
    IN      DWORD                       cbBuffer,
    OUT     PDWORD                      pcItemsReturned     OPTIONAL,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );


//-----------------------------------------------------------------------------
// Game instrumentation errors              = 0x8056F0XX
//-----------------------------------------------------------------------------

#define SPA_E_CORRUPT_FILE          _HRESULT_TYPEDEF_(0x8056F001)
#define SPA_E_NOT_LOADED            _HRESULT_TYPEDEF_(0x8056F002)
#define SPA_E_BAD_TITLEID           _HRESULT_TYPEDEF_(0x8056F003)


// User/Profile/Account APIs

typedef enum _XUSER_SIGNIN_STATE
{
    eXUserSigninState_NotSignedIn,
    eXUserSigninState_SignedInLocally,
    eXUserSigninState_SignedInToLive
} XUSER_SIGNIN_STATE;

XBOXAPI
DWORD
WINAPI
XUserGetXUID(
    IN      DWORD                       dwUserIndex,
    OUT     PXUID                       pxuid
    );

XBOXAPI
DWORD
WINAPI
XUserGetName(
    IN      DWORD                       dwUserIndex,
    OUT     LPSTR                       szUserName,
    IN      DWORD                       cchUserName
    );

XBOXAPI
XUSER_SIGNIN_STATE
WINAPI
XUserGetSigninState(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
FLOAT
WINAPI
XUserGetReputationStars(
    IN      FLOAT                       fGamerRating
    );

#define XUSER_INFO_FLAG_LIVE_ENABLED    0x00000001
#define XUSER_INFO_FLAG_GUEST           0x00000002

typedef struct _XUSER_SIGNIN_INFO
{
   XUID                 xuid;
   DWORD                dwInfoFlags;
   XUSER_SIGNIN_STATE   UserSigninState;
   DWORD                dwGuestNumber;
   DWORD                dwSponsorUserIndex;
   CHAR                 szUserName[XUSER_NAME_SIZE];
} XUSER_SIGNIN_INFO, * PXUSER_SIGNIN_INFO;

#define XUSER_GET_SIGNIN_INFO_ONLINE_XUID_ONLY      0x00000001
#define XUSER_GET_SIGNIN_INFO_OFFLINE_XUID_ONLY     0x00000002

XBOXAPI
DWORD
WINAPI
XUserGetSigninInfo(
    IN     DWORD                        dwUserIndex,
    IN     DWORD                        dwFlags          OPTIONAL,
    OUT    PXUSER_SIGNIN_INFO           pSigninInfo
    );


typedef enum _XPRIVILEGE_TYPE
{
    XPRIVILEGE_MULTIPLAYER_SESSIONS              = 254, // on|off

    XPRIVILEGE_COMMUNICATIONS                    = 252, // on (communicate w/everyone) | off (check _FO)
    XPRIVILEGE_COMMUNICATIONS_FRIENDS_ONLY       = 251, // on (communicate w/friends only) | off (blocked)

    XPRIVILEGE_PROFILE_VIEWING                   = 249, // on (viewing allowed) | off (check _FO)
    XPRIVILEGE_PROFILE_VIEWING_FRIENDS_ONLY      = 248, // on (view friend’s only) | off (no details)

    XPRIVILEGE_USER_CREATED_CONTENT              = 247, // on (allow viewing of UCC) | off (check _FO)
    XPRIVILEGE_USER_CREATED_CONTENT_FRIENDS_ONLY = 246, // on (view UCC from friends only) | off (blocked)

    XPRIVILEGE_PURCHASE_CONTENT                  = 245, // on (allow purchase) | off (blocked)

    XPRIVILEGE_PRESENCE                          = 244, // on (share presence info) | off (check _FO)
    XPRIVILEGE_PRESENCE_FRIENDS_ONLY             = 243, // on (share w/friends only | off (don’t share)

    XPRIVILEGE_TRADE_CONTENT                     = 238, // on (allow trading) | off (blocked)

    XPRIVILEGE_VIDEO_COMMUNICATIONS              = 235, // on (communicate w/everyone) | off (check _FO)
    XPRIVILEGE_VIDEO_COMMUNICATIONS_FRIENDS_ONLY = 234, // on (communicate w/friends only) | off (blocked)
} XPRIVILEGE_TYPE;


XBOXAPI
DWORD
WINAPI
XUserAreUsersFriends(
    IN      DWORD                       dwUserIndex,
    IN      PXUID                       pXuids,
    IN      DWORD                       dwXuidCount,
    OUT     PBOOL                       pfResult            OPTIONAL,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XUserCheckPrivilege(
    IN      DWORD                       dwUserIndex,
    IN      XPRIVILEGE_TYPE             PrivilegeType,
    OUT     PBOOL                       pfResult
    );

// Context and Property definitions

typedef struct _XUSER_DATA
{
    BYTE                                type;

    union
    {
        LONG                            nData;     // XUSER_DATA_TYPE_INT32
        LONGLONG                        i64Data;   // XUSER_DATA_TYPE_INT64
        double                          dblData;   // XUSER_DATA_TYPE_DOUBLE
        struct                                     // XUSER_DATA_TYPE_UNICODE
        {
            DWORD                       cbData;    // Includes null-terminator
            LPWSTR                      pwszData;
        } string;
        FLOAT                           fData;     // XUSER_DATA_TYPE_FLOAT
        struct                                     // XUSER_DATA_TYPE_BINARY
        {
            DWORD                       cbData;
            PBYTE                       pbData;
        } binary;
        FILETIME                        ftData;    // XUSER_DATA_TYPE_DATETIME
    };
} XUSER_DATA, *PXUSER_DATA;

typedef struct _XUSER_PROPERTY
{
    DWORD                               dwPropertyId;
    XUSER_DATA                          value;
} XUSER_PROPERTY, *PXUSER_PROPERTY;

typedef struct _XUSER_CONTEXT
{
    DWORD                               dwContextId;
    DWORD                               dwValue;
} XUSER_CONTEXT, *PXUSER_CONTEXT;

// Context and Property APIs

XBOXAPI
DWORD
WINAPI
XUserGetContext(
    IN      DWORD               dwUserIndex,
    IN OUT  XUSER_CONTEXT*      pContext,
    IN OUT  PXOVERLAPPED        pOverlapped         OPTIONAL
    );

XBOXAPI
VOID
WINAPI
XUserSetContext(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwContextId,
    IN      DWORD                       dwContextValue
    );

XBOXAPI
DWORD
WINAPI
XUserSetContextEx(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwContextId,
    IN      DWORD                       dwContextValue,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XUserGetProperty(
    IN      DWORD                       dwUserIndex,
    IN OUT  DWORD*                      pcbActual,
    IN OUT  XUSER_PROPERTY*             pProperty,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
VOID
WINAPI
XUserSetProperty(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwPropertyId,
    IN      DWORD                       cbValue,
    IN      CONST VOID*                 pvValue
    );

XBOXAPI
DWORD
WINAPI
XUserSetPropertyEx(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwPropertyId,
    IN      DWORD                       cbValue,
    IN      CONST VOID*                 pvValue,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

// System-defined contexts and properties

#define X_PROPERTY_TYPE_MASK            0xF0000000
#define X_PROPERTY_SCOPE_MASK           0x00008000
#define X_PROPERTY_ID_MASK              0x00007FFF


#define XPROPERTYID(global, type, id)   ((global ? X_PROPERTY_SCOPE_MASK : 0) | ((type << 28) & X_PROPERTY_TYPE_MASK) | (id & X_PROPERTY_ID_MASK))
#define XCONTEXTID(global, id)          XPROPERTYID(global, XUSER_DATA_TYPE_CONTEXT, id)
#define XPROPERTYTYPEFROMID(id)         ((id >> 28) & 0xf)
#define XISSYSTEMPROPERTY(id)           (id & X_PROPERTY_SCOPE_MASK)

// Predefined contexts
#define X_CONTEXT_PRESENCE              XCONTEXTID(1, 0x1)
#define X_CONTEXT_GAME_TYPE             XCONTEXTID(1, 0xA)
#define X_CONTEXT_GAME_MODE             XCONTEXTID(1, 0xB)

#define X_PROPERTY_RANK                 XPROPERTYID(1, XUSER_DATA_TYPE_INT32,   0x1)
#define X_PROPERTY_GAMERNAME            XPROPERTYID(1, XUSER_DATA_TYPE_UNICODE, 0x2)
#define X_PROPERTY_SESSION_ID           XPROPERTYID(1, XUSER_DATA_TYPE_INT64,   0x3)

// System attributes used in matchmaking queries
#define X_PROPERTY_GAMER_ZONE           XPROPERTYID(1, XUSER_DATA_TYPE_INT32,   0x101)
#define X_PROPERTY_GAMER_COUNTRY        XPROPERTYID(1, XUSER_DATA_TYPE_INT32,   0x102)
#define X_PROPERTY_GAMER_LANGUAGE       XPROPERTYID(1, XUSER_DATA_TYPE_INT32,   0x103)
#define X_PROPERTY_GAMER_RATING         XPROPERTYID(1, XUSER_DATA_TYPE_FLOAT,   0x104)
#define X_PROPERTY_GAMER_MU             XPROPERTYID(1, XUSER_DATA_TYPE_DOUBLE,  0x105)
#define X_PROPERTY_GAMER_SIGMA          XPROPERTYID(1, XUSER_DATA_TYPE_DOUBLE,  0x106)
#define X_PROPERTY_GAMER_PUID           XPROPERTYID(1, XUSER_DATA_TYPE_INT64,   0x107)
#define X_PROPERTY_AFFILIATE_SCORE      XPROPERTYID(1, XUSER_DATA_TYPE_INT64,   0x108)
#define X_PROPERTY_GAMER_HOSTNAME       XPROPERTYID(1, XUSER_DATA_TYPE_UNICODE, 0x109)

// Properties used to write to skill leaderboards
#define X_PROPERTY_RELATIVE_SCORE                   XPROPERTYID(1, XUSER_DATA_TYPE_INT32,   0xA)
#define X_PROPERTY_SESSION_TEAM                     XPROPERTYID(1, XUSER_DATA_TYPE_INT32,   0xB)

// Properties written at the session level to override TrueSkill parameters
#define X_PROPERTY_PLAYER_PARTIAL_PLAY_PERCENTAGE   XPROPERTYID(1, XUSER_DATA_TYPE_INT32,   0xC)
#define X_PROPERTY_PLAYER_SKILL_UPDATE_WEIGHTING_FACTOR XPROPERTYID(1, XUSER_DATA_TYPE_INT32,   0xD)
#define X_PROPERTY_SESSION_SKILL_BETA               XPROPERTYID(1, XUSER_DATA_TYPE_DOUBLE,  0xE)
#define X_PROPERTY_SESSION_SKILL_TAU                XPROPERTYID(1, XUSER_DATA_TYPE_DOUBLE,  0xF)
#define X_PROPERTY_SESSION_SKILL_DRAW_PROBABILITY   XPROPERTYID(1, XUSER_DATA_TYPE_INT32,   0x10)

// Attachment size is written to a leaderboard when the entry qualifies for
// a gamerclip.  The rating can be retrieved via XUserEstimateRankForRating.
#define X_PROPERTY_ATTACHMENT_SIZE                  XPROPERTYID(1, XUSER_DATA_TYPE_INT32,   0x11)


// Values for X_CONTEXT_GAME_TYPE
#define X_CONTEXT_GAME_TYPE_RANKED      0
#define X_CONTEXT_GAME_TYPE_STANDARD    1

// Achievement APIs

typedef struct
{
    DWORD                               dwUserIndex;
    DWORD                               dwAchievementId;
} XUSER_ACHIEVEMENT, *PXUSER_ACHIEVEMENT;

XBOXAPI
DWORD
WINAPI
XUserWriteAchievements(
    IN      DWORD                       dwNumAchievements,
    IN      CONST XUSER_ACHIEVEMENT*    pAchievements,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

typedef struct
{
    DWORD                               dwId;
    LPWSTR                              pwszLabel;
    LPWSTR                              pwszDescription;
    LPWSTR                              pwszUnachieved;
    DWORD                               dwImageId;
    DWORD                               dwCred;
    FILETIME                            ftAchieved;
    DWORD                               dwFlags;
} XACHIEVEMENT_DETAILS, *PXACHIEVEMENT_DETAILS;

// These lengths include the NULL-terminator
#define XACHIEVEMENT_MAX_LABEL_LENGTH   32
#define XACHIEVEMENT_MAX_DESC_LENGTH    100
#define XACHIEVEMENT_MAX_UNACH_LENGTH   100

#define XACHIEVEMENT_SIZE_BASE          (sizeof(XACHIEVEMENT_DETAILS))
#define XACHIEVEMENT_SIZE_STRINGS       (sizeof(WCHAR) * (XACHIEVEMENT_MAX_LABEL_LENGTH  + XACHIEVEMENT_MAX_DESC_LENGTH + XACHIEVEMENT_MAX_UNACH_LENGTH))
#define XACHIEVEMENT_SIZE_FULL          (XACHIEVEMENT_SIZE_BASE + XACHIEVEMENT_SIZE_STRINGS)

#define XACHIEVEMENT_INVALID_ID         ((DWORD)0xFFFFFFFF)

// XACHIEVEMENT_DETAILS::dwFlags can be manipulated with these defines and macros
#define XACHIEVEMENT_DETAILS_MASK_TYPE          0x00000007
#define XACHIEVEMENT_DETAILS_SHOWUNACHIEVED     0x00000008
#define XACHIEVEMENT_DETAILS_ACHIEVED_ONLINE    0x00010000
#define XACHIEVEMENT_DETAILS_ACHIEVED           0x00020000


#define AchievementType(dwFlags)           (dwFlags & XACHIEVEMENT_DETAILS_MASK_TYPE)
#define AchievementShowUnachieved(dwFlags) (dwFlags & XACHIEVEMENT_DETAILS_SHOWUNACHIEVED ? TRUE : FALSE)
#define AchievementEarnedOnline(dwFlags)   (dwFlags & XACHIEVEMENT_DETAILS_ACHIEVED_ONLINE ? TRUE : FALSE)
#define AchievementEarned(dwFlags)         (dwFlags & XACHIEVEMENT_DETAILS_ACHIEVED ? TRUE : FALSE)

// Types returned from AchievementType macro

#define XACHIEVEMENT_TYPE_COMPLETION            1
#define XACHIEVEMENT_TYPE_LEVELING              2
#define XACHIEVEMENT_TYPE_UNLOCK                3
#define XACHIEVEMENT_TYPE_EVENT                 4
#define XACHIEVEMENT_TYPE_TOURNAMENT            5
#define XACHIEVEMENT_TYPE_CHECKPOINT            6
#define XACHIEVEMENT_TYPE_OTHER                 7

#define XACHIEVEMENT_DETAILS_ALL                0xFFFFFFFF
#define XACHIEVEMENT_DETAILS_LABEL              0x00000001
#define XACHIEVEMENT_DETAILS_DESCRIPTION        0x00000002
#define XACHIEVEMENT_DETAILS_UNACHIEVED         0x00000004
#define XACHIEVEMENT_DETAILS_TFC                0x00000020

XBOXAPI
DWORD
WINAPI
XUserCreateAchievementEnumerator(
    IN      DWORD                       dwTitleId,
    IN      DWORD                       dwUserIndex,
    IN      XUID                        xuid,
    IN      DWORD                       dwDetailFlags,
    IN      DWORD                       dwStartingIndex,
    IN      DWORD                       cItem,
    OUT     PDWORD                      pcbBuffer,
    OUT     PHANDLE                     ph
    );

//
// Pictures
//

XBOXAPI
DWORD
WINAPI
XUserReadAchievementPicture(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwTitleId,
    IN      DWORD                       dwImageId,
    IN OUT  PBYTE                       pbTextureBuffer,
    IN      DWORD                       dwPitch,
    IN      DWORD                       dwHeight,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );



XBOXAPI
DWORD
WINAPI
XUserReadGamerPicture(
    IN      DWORD                       dwUserIndex,
    IN      BOOL                        fSmall,
    IN OUT  PBYTE                       pbTextureBuffer,
    IN      DWORD                       dwPitch,
    IN      DWORD                       dwHeight,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XUserReadGamerPictureByKey(
    IN      CONST PXUSER_DATA           pGamercardPictureKey,
    IN      BOOL                        fSmall,
    IN OUT  PBYTE                       pbTextureBuffer,
    IN      DWORD                       dwPitch,
    IN      DWORD                       dwHeight,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XUserAwardGamerPicture(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwPictureId,
    IN      DWORD                       dwReserved,
    IN OUT  PXOVERLAPPED                pXOverlapped        OPTIONAL
    );


// Stats APIs

#define XUSER_STATS_ATTRS_IN_SPEC       64

typedef struct _XUSER_STATS_COLUMN
{
    WORD                                wColumnId;
    XUSER_DATA                          Value;
} XUSER_STATS_COLUMN, *PXUSER_STATS_COLUMN;

typedef struct _XUSER_STATS_ROW
{
    XUID                                xuid;
    DWORD                               dwRank;
    LONGLONG                            i64Rating;
    CHAR                                szGamertag[XUSER_NAME_SIZE];
    DWORD                               dwNumColumns;
    PXUSER_STATS_COLUMN                 pColumns;
} XUSER_STATS_ROW, *PXUSER_STATS_ROW;

typedef struct _XUSER_STATS_VIEW
{
    DWORD                               dwViewId;
    DWORD                               dwTotalViewRows;
    DWORD                               dwNumRows;
    PXUSER_STATS_ROW                    pRows;
} XUSER_STATS_VIEW, *PXUSER_STATS_VIEW;

typedef struct _XUSER_STATS_READ_RESULTS
{
    DWORD                               dwNumViews;
    PXUSER_STATS_VIEW                   pViews;
} XUSER_STATS_READ_RESULTS, *PXUSER_STATS_READ_RESULTS;

typedef struct _XUSER_STATS_SPEC
{
    DWORD                               dwViewId;
    DWORD                               dwNumColumnIds;
    WORD                                rgwColumnIds[XUSER_STATS_ATTRS_IN_SPEC];
} XUSER_STATS_SPEC, *PXUSER_STATS_SPEC;

XBOXAPI
DWORD
WINAPI
XUserResetStatsView(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwViewId,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XUserResetStatsViewAllUsers(
    IN      DWORD                       dwViewId,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XUserReadStats(
    IN      DWORD                       dwTitleId,
    IN      DWORD                       dwNumXuids,
    IN      CONST XUID*                 pXuids,
    IN      DWORD                       dwNumStatsSpecs,
    IN      CONST XUSER_STATS_SPEC*     pSpecs,
    IN OUT  PDWORD                      pcbResults,
    OUT     PXUSER_STATS_READ_RESULTS   pResults,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XUserCreateStatsEnumeratorByRank(
    IN      DWORD                       dwTitleId,
    IN      DWORD                       dwRankStart,
    IN      DWORD                       dwNumRows,
    IN      DWORD                       dwNumStatsSpecs,
    IN      CONST XUSER_STATS_SPEC*     pSpecs,
    OUT     PDWORD                      pcbBuffer,
    OUT     PHANDLE                     ph
    );

XBOXAPI
DWORD
WINAPI
XUserCreateStatsEnumeratorByXuid(
    IN      DWORD                       dwTitleId,
    IN      XUID                        XuidPivot,
    IN      DWORD                       dwNumRows,
    IN      DWORD                       dwNumStatsSpecs,
    IN      CONST XUSER_STATS_SPEC*     pSpecs,
    OUT     PDWORD                      pcbBuffer,
    OUT     PHANDLE                     ph
    );


XBOXAPI
DWORD
WINAPI
XUserCreateStatsEnumeratorByRating(
    IN      DWORD                       dwTitleId,
    IN      LONGLONG                    i64Rating,
    IN      DWORD                       dwNumRows,
    IN      DWORD                       dwNumStatsSpecs,
    IN      CONST XUSER_STATS_SPEC*     pSpecs,
    OUT     PDWORD                      pcbBuffer,
    OUT     PHANDLE                     ph
    );


// System defined leaderboard columns
#define X_STATS_COLUMN_ATTACHMENT_SIZE          ((WORD)0xFFFA)

// Column ids for skill leaderboards (STATS_VIEW_SKILL_* views)
#define X_STATS_COLUMN_SKILL_SKILL              61
#define X_STATS_COLUMN_SKILL_GAMESPLAYED        62
#define X_STATS_COLUMN_SKILL_MU                 63
#define X_STATS_COLUMN_SKILL_SIGMA              64

#define X_STATS_SKILL_SKILL_DEFAULT             1
#define X_STATS_SKILL_MU_DEFAULT                3.0
#define X_STATS_SKILL_SIGMA_DEFAULT             1.0


// Signin UI API

// XShowSiginUI flags.
#define XSSUI_FLAGS_LOCALSIGNINONLY                 0x00000001
#define XSSUI_FLAGS_SHOWONLYONLINEENABLED           0x00000002
#define XSSUI_FLAGS_CONVERTOFFLINETOGUEST           0x00400000


XBOXAPI
DWORD
WINAPI
XEnableGuestSignin(
    IN      BOOL                        fEnable
    );

XBOXAPI
DWORD
WINAPI
XShowSigninUI(
    IN      DWORD                       cPanes,
    IN      DWORD                       dwFlags
    );


XBOXAPI
DWORD
WINAPI
XShowFriendsUI(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
DWORD
WINAPI
XShowPlayersUI(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
DWORD
WINAPI
XShowMessagesUI(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
DWORD
WINAPI
XShowMessageComposeUI(
    IN      DWORD                       dwUserIndex,
    IN      CONST XUID*                 pXuidRecipients     OPTIONAL,
    IN      DWORD                       cRecipients,
    IN      LPCWSTR                     wszText             OPTIONAL
    );

// Deprecated. Use XCUSTOMACTION_FLAG_CLOSES_GUIDE instead.
#define CUSTOMACTION_FLAG_CLOSESUI      1

typedef enum
{
    XMSG_FLAG_DISABLE_EDIT_RECIPIENTS   = 0x00000001
} XMSG_FLAGS;

#define XMSG_MAX_CUSTOM_IMAGE_SIZE      (36*1024)

typedef enum
{
    XCUSTOMACTION_FLAG_CLOSES_GUIDE     = 0x00000001,
    XCUSTOMACTION_FLAG_DELETES_MESSAGE  = 0x00000002
} XCUSTOMACTION_FLAGS;

#define XMSG_MAX_CUSTOMACTION_TRANSLATIONS      11


typedef struct
{
    DWORD                               dwActionId;
    WCHAR                               wszEnActionText[23];
    WORD                                wReserved;
    DWORD                               dwFlags;
    struct
    {
        DWORD                           dwLanguageId;
        WCHAR                           wszActionText[23];
        WORD                            wReserved;
    } rgTranslations[XMSG_MAX_CUSTOMACTION_TRANSLATIONS];
} XMSG_CUSTOMACTION;

#define XCUSTOMACTION_MAX_PAYLOAD_SIZE  1024

XBOXAPI
DWORD
WINAPI
XShowCustomMessageComposeUI(
    IN      DWORD                       dwUserIndex,
    IN      CONST XUID*                 pXuidRecipients     OPTIONAL,
    IN      DWORD                       cRecipients,
    IN      DWORD                       dwFlags,
    IN      LPCWSTR                     wszTitle,
    IN      LPCWSTR                     wszGameMessage,
    IN      LPCWSTR                     wszPlayerMessage    OPTIONAL,
    IN      CONST BYTE*                 pbImage             OPTIONAL,
    IN      DWORD                       cbImage,
    IN      CONST XMSG_CUSTOMACTION*    pCustomActions,
    IN      DWORD                       cCustomActions,
    IN      CONST BYTE*                 pbCustomPayload     OPTIONAL,
    IN      DWORD                       cbCustomPayload,
    IN      DWORD                       dwExpireMinutes     OPTIONAL,
    IN OUT  XOVERLAPPED*                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XShowGameInviteUI(
    IN      DWORD                       dwUserIndex,
    IN      CONST XUID*                 pXuidRecipients     OPTIONAL,
    IN      DWORD                       cRecipients,
    IN      LPCWSTR                     wszUnused           OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XShowFriendRequestUI(
    IN      DWORD                       dwUserIndex,
    IN      XUID                        xuidUser
    );

#define XPLAYERLIST_CUSTOMTEXT_MAX_LENGTH   31
#define XPLAYERLIST_TITLE_MAX_LENGTH        36
#define XPLAYERLIST_DESCRIPTION_MAX_LENGTH  83
#define XPLAYERLIST_IMAGE_MAX_SIZE          36864
#define XPLAYERLIST_MAX_PLAYERS             100
#define XPLAYERLIST_BUTTONTEXT_MAX_LENGTH   23

typedef struct
{
    XUID        xuid;
    WCHAR       wszCustomText[XPLAYERLIST_CUSTOMTEXT_MAX_LENGTH];
} XPLAYERLIST_USER;

typedef struct
{
    XUID        xuidSelected;
    DWORD       dwKeyCode;
} XPLAYERLIST_RESULT;

typedef enum
{
    XPLAYERLIST_BUTTON_TYPE_TITLECUSTOM          = 0,
    XPLAYERLIST_BUTTON_TYPE_PLAYERREVIEW,
    XPLAYERLIST_BUTTON_TYPE_GAMEINVITE,
    XPLAYERLIST_BUTTON_TYPE_MESSAGE,
    XPLAYERLIST_BUTTON_TYPE_FRIENDREQUEST,
} XPLAYERLIST_BUTTON_TYPE;

typedef struct
{
    DWORD dwType;
    WCHAR wszCustomText[XPLAYERLIST_BUTTONTEXT_MAX_LENGTH];
} XPLAYERLIST_BUTTON;


typedef enum
{
    XPLAYERLIST_FLAG_CUSTOMTEXT             = 0x00000001,
} XPLAYERLIST_FLAGS;


XBOXAPI
DWORD
WINAPI
XShowCustomPlayerListUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,
    IN      LPCWSTR                     pszTitle,
    IN      LPCWSTR                     pszDescription,
    IN      CONST BYTE*                 pbImage             OPTIONAL,
    IN      DWORD                       cbImage,
    IN      CONST XPLAYERLIST_USER*     rgPlayers,
    IN      DWORD                       cPlayers,
    IN      CONST XPLAYERLIST_BUTTON*   pXButton            OPTIONAL,
    IN      CONST XPLAYERLIST_BUTTON*   pYButton            OPTIONAL,
    OUT     XPLAYERLIST_RESULT*         pResult             OPTIONAL,
    IN OUT  XOVERLAPPED*                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XShowKeyboardUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,
    IN      LPCWSTR                     wseDefaultText,
    IN      LPCWSTR                     wszTitleText,
    IN      LPCWSTR                     wszDescriptionText,
    OUT     LPWSTR                      wszResultText,
    IN      DWORD                       cchResultText,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XShowGamerCardUI(
    IN      DWORD                       dwUserIndex,
    IN      XUID                        XuidPlayer
    );

XBOXAPI
DWORD
WINAPI
XShowAchievementsUI(
    IN      DWORD                       dwUserIndex
    );

typedef enum _XSHOWMARKETPLACEUI_ENTRYPOINTS {
    XSHOWMARKETPLACEUI_ENTRYPOINT_CONTENTLIST,
    XSHOWMARKETPLACEUI_ENTRYPOINT_CONTENTITEM,
    XSHOWMARKETPLACEUI_ENTRYPOINT_MEMBERSHIPLIST,
    XSHOWMARKETPLACEUI_ENTRYPOINT_MEMBERSHIPITEM,
    XSHOWMARKETPLACEUI_ENTRYPOINT_MAX
} XSHOWMARKETPLACEUI_ENTRYPOINTS;


XBOXAPI
DWORD
WINAPI
XShowMarketplaceUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwEntryPoint,
    IN      ULONGLONG                   qwOfferID               OPTIONAL,
    IN      DWORD                       dwContentCategories
    );

//-----------------------------------------------------------------------------
// XShowMarketplaceDownloadItemsUI Result errors = 0x8057F0XX
//-----------------------------------------------------------------------------

#define MPDI_E_CANCELLED            _HRESULT_TYPEDEF_(0x8057F001)
#define MPDI_E_INVALIDARG           _HRESULT_TYPEDEF_(0x8057F002)
#define MPDI_E_OPERATION_FAILED     _HRESULT_TYPEDEF_(0x8057F003)

typedef enum _XSHOWMARKETPLACEDOWNLOADITEMSUI_ENTRYPOINTS {
    XSHOWMARKETPLACEDOWNLOADITEMS_ENTRYPOINT_FREEITEMS=1000,
    XSHOWMARKETPLACEDOWNLOADITEMS_ENTRYPOINT_PAIDITEMS,
    XSHOWMARKETPLACEDOWNLOADITEMS_ENTRYPOINT_MAX
} XSHOWMARKETPLACEDOWNLOADITEMSUI_ENTRYPOINTS;

XBOXAPI
DWORD
WINAPI
XShowMarketplaceDownloadItemsUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwEntryPoint,
    IN      CONST ULONGLONG*            pOfferIDs,
    IN      DWORD                       dwOfferIdCount,
    OUT     HRESULT*                    phrResult,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

#define XMARKETPLACE_IMAGE_URL_MINIMUM_WCHARCOUNT   55
#define XMARKETPLACE_MAX_OFFERIDS                   6

XBOXAPI
VOID
APIENTRY
XMarketplaceGetImageUrl(
  IN     DWORD     dwTitleID,
  IN     ULONGLONG qwOfferID,
  IN     DWORD     cchStringBuffer,
  IN OUT WCHAR*    pwszStringBuffer
  );

XBOXAPI
DWORD
APIENTRY
XMarketplaceGetDownloadStatus(
  IN    DWORD       dwUserIndex,
  IN    ULONGLONG   qwOfferID,
  OUT   LPDWORD     pdwResult
  );

XBOXAPI
BOOL
APIENTRY
XMarketplaceDoesContentIdMatch(
    IN  CONST BYTE*             pbContentId,
    IN  CONST XCONTENT_DATA*    pContentData
    );

XBOXAPI
DWORD
WINAPI
XShowDeviceSelectorUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwContentType,
    IN      DWORD                       dwContentFlags,
    IN      ULARGE_INTEGER              uliBytesRequested,
    OUT     PXCONTENTDEVICEID           pDeviceID,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DECLSPEC_NORETURN
XBOXAPI
VOID
WINAPI
XShowDirtyDiscErrorUI(
    IN      DWORD                       dwUserIndex
    );

// API to show error and informational messages
#define XMB_NOICON                      0x00000000
#define XMB_ERRORICON                   0x00000001
#define XMB_WARNINGICON                 0x00000002
#define XMB_ALERTICON                   0x00000003
#define XMB_PASSCODEMODE                0x00010000
#define XMB_VERIFYPASSCODEMODE          0x00020000

#define XMB_MAXBUTTONS                  3
#define XMB_CANCELID                    -1

typedef struct _MESSAGEBOX_RESULT
{
    union
    {
        DWORD                           dwButtonPressed;
        WORD                            rgwPasscode[4];
    };
} MESSAGEBOX_RESULT, *PMESSAGEBOX_RESULT;

XBOXAPI
DWORD
WINAPI
XShowMessageBoxUI(
    IN      DWORD                       dwUserIndex,
    IN      LPCWSTR                     wszTitle,
    IN      LPCWSTR                     wszText,
    IN      DWORD                       cButtons,
    IN      LPCWSTR*                    pwszButtons,
    IN      DWORD                       dwFocusButton,
    IN      DWORD                       dwFlags,
    OUT     PMESSAGEBOX_RESULT          pResult,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XShowPlayerReviewUI(
    IN      DWORD                       dwUserIndex,
    IN      XUID                        XuidFeedbackTarget
    );


//  UI Extensibility API
#define GAMEBANNER_WIDTH                384
#define GAMEBANNER_HEIGHT               128

XBOXAPI
DWORD
WINAPI
XCustomSetBannerImage(
    IN      PVOID                       pvTexture,
    IN      DWORD                       dwFlags
    );

XBOXAPI
VOID
WINAPI
XCustomSetAction(
    IN      DWORD                       dwActionIndex,
    IN      LPCWSTR                     szActionText,
    IN      DWORD                       dwFlags
    );

typedef struct
{
    WORD                                wActionId;
    WCHAR                               wszActionText[23];
    DWORD                               dwFlags;
} XCUSTOMACTION;

XBOXAPI
VOID
WINAPI
XCustomRegisterDynamicActions(
    VOID
    );

XBOXAPI
VOID
WINAPI
XCustomUnregisterDynamicActions(
    VOID
    );

XBOXAPI
BOOL
WINAPI
XCustomGetCurrentGamercard(
    OUT DWORD*              pdwUserIndex,
    OUT XUID*               pXuid
    );

XBOXAPI
DWORD
WINAPI
XCustomSetDynamicActions(
    DWORD                   dwUserIndex,
    XUID                    xuid,
    CONST XCUSTOMACTION*    pCustomActions,
    WORD                    cCustomActions
    );

XBOXAPI
BOOL
WINAPI
XCustomGetLastActionPress(
    OUT     DWORD*                      pdwUserIndex,
    OUT     DWORD*                      pdwActionIndex,
    OUT     XUID*                       pXuid
    );

XBOXAPI
DWORD
WINAPI
XCustomGetLastActionPressEx(
    OUT     DWORD*                      pdwUserIndex,
    OUT     DWORD*                      pdwActionId,
    OUT     XUID*                       pXuid,
    OUT     BYTE*                       pbPayload       OPTIONAL,
    IN OUT  WORD*                       pcbPayload      OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XEnableScreenSaver(
    IN      BOOL                        fEnable
    );



typedef struct _XHASH_STATE {
    BYTE Internal[88];
} XHASH_STATE, *PXHASH_STATE;

#define XHASHMEMORY_DIGEST_SIZE (20)

XBOXAPI
VOID
WINAPI
XHashMemoryBegin(
    OUT     XHASH_STATE*                pState
    );

XBOXAPI
VOID
WINAPI
XHashMemoryUpdate(
    IN OUT  XHASH_STATE*                pState,
    IN      CONST VOID*                 pvMemory,
    IN      DWORD                       dwSize
    );

XBOXAPI
VOID
WINAPI
XHashMemoryEnd(
    IN      CONST XHASH_STATE*          pState,
    OUT     BYTE*                       pbDigest
    );

XBOXAPI
BOOL
WINAPI
XCloseHandle(
    IN      HANDLE                      hObject
    );



//-----------------------------------------------------------------------------
// Security Status. 
//-----------------------------------------------------------------------------

typedef enum _XSECURITY_STATUS_CHECKS {
    XSECURITY_STATUS_ANY,
    XSECURITY_STATUS_VERSION_CHECK,
    XSECURITY_STATUS_MAXIMUM
} XSECURITY_STATUS_CHECK;

//
// Returns:
//   ERROR_INVALID_PARAMETER - unknown security check
//   ERROR_ACCESS_DENIED - security check failed
//   ERROR_SUCCESS - security check succeeded.
XBOXAPI
DWORD
WINAPI
XGetSecurityStatus(
    IN  DWORD dwSecurityCheck
    );

XBOXAPI
DWORD
WINAPI
XSetSecurityStatus(
    IN  DWORD dwSecurityCheck,
    IN  DWORD dwStatus
    );


#ifdef __cplusplus
}
#endif


#endif // _XBOX_H_

