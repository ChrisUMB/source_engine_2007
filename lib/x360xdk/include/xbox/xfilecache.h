/*++

Copyright (c) 1990-2005  Microsoft Corporation

Module Name:    XFileCache.h

Abstract:

    Game Disc Caching API

--*/

#ifndef XFILECACHE_H
#define XFILECACHE_H

#define XFILECACHEAPI   /*nothing*/

#ifdef __cplusplus
extern "C" {
#endif


DWORD
XFILECACHEAPI
XFileCacheInit(
   IN DWORD      Flags,                                 /* (see XFILECACHE_INIT_xxx below) */
   IN ULONGLONG  MaxCacheSize,                          /* maximum bytes to cache */
   IN DWORD      HardwareThread,                        /* where worker thread should execute */
   IN DWORD      ScratchBufferSize,                     /* working storage (zero=default, or at least 192K) */
   IN DWORD      AppVersion                             /* version for application (cache will wipe if no match) */
   );

#define XFILECACHE_MAX_SIZE                     (0xffffffffffffffffui64)
#define XFILECACHE_DEFAULT_THREAD               5           /* default hardware thread to use */

#define XFILECACHE_PRESERVE                     0           /* preserve existing files */
#define XFILECACHE_CLEAR_STARTUP                0x80000000  /* clear "startup" cache area */
#define XFILECACHE_CLEAR_NORMAL                 0x40000000  /* clear "normal" cache area */
#define XFILECACHE_CLEAR_ALL                    0xc0000000  /* clear everything */
#define XFILECACHE_OPPORTUNISTIC_ON             0x00000010  /* allow opportunistic caching (via CreateFile) */
#define XFILECACHE_OPPORTUNISTIC_OFF            0x00000020  /* forbid opportunistic caching */

VOID
XFILECACHEAPI
XFileCacheShutdown();

DWORD
XFILECACHEAPI
XFileCacheControl(
   IN DWORD CacheMode
   );

#define XFILECACHE_BACKGROUND_OFF               (1)     /* caching off */
#define XFILECACHE_BACKGROUND_ON                (2)     /* caching on */
#define XFILECACHE_STARTUP_FILES                (4)     /* flag newly cached files as 'startup' */
#define XFILECACHE_NORMAL_FILES                 (8)     /* flag newly cached files as 'normal' */

DWORD
XFILECACHEAPI
XFileCachePreload(
   IN DWORD Flags,                                      /* type of files (startup / normal / etc.) */
   IN LPCSTR pszFileName                                /* file or pattern to preload */
   );

DWORD
XFILECACHEAPI
XFileCachePreloadFiles(
   IN DWORD Flags,                                      /* type of files (startup / normal / etc.) */
   IN LPCSTR* ppszFileNames,                            /* vector of files to preload */
   IN DWORD FileNameCount                               /* number of files */
   );

DWORD
XFILECACHEAPI
XFileCacheRemove(
    IN LPCSTR pszFileName                               /* possibly wildcarded filename */
    );

DWORD
XFILECACHEAPI
XFileCacheRemoveFiles(
    IN LPCSTR* ppszFileNames,                           /* vector of filenames (possibly wildcarded) */
    IN DWORD FileNameCount                              /* number of files */
    );

DWORD
XFILECACHEAPI
XFileCacheControlFiles(
   IN DWORD Flags,                                      /* control flags (see below) */
   IN LPCSTR* ppszFileNames,                            /* vector of files */
   IN DWORD FileNameCount                               /* number of files */
   );

//
//  valid Flags for XFileCacheControlFiles
//

#define XFILECACHE_DONTCACHE                    1       /* don't cache directory or leaf pattern */


typedef DWORD (*XFILECACHE_READFILEADVISORY_CALLBACK)(
    PVOID Context,
    const char* Path,
    PLARGE_INTEGER pFileOffset,
    DWORD nNumberOfBytesToRead
);

VOID
XFILECACHEAPI
XFileCacheSetFileIoCallbacks
    ( XFILECACHE_READFILEADVISORY_CALLBACK ReadFileAdvisoryCallback,
      PVOID Context
    );

#define XFILECACHE_READFILEADVISORY_DEFER_MASK      0x80000000
#define XFILECACHE_READFILEADVISORY_HOLDOFF(MS)     (XFILECACHE_READFILEADVISORY_DEFER_MASK | (MS))
#define XFILECACHE_READFILEADVISORY_ALLOW(MS)       (MS)
#define XFILECACHE_READFILEADVISORY_OK              0


//
//  XFileCacheCreateFileA is just like CreateFile, with an additional flags parameter to
//  control caching behavior (e.g., "don't cache")
//

WINBASEAPI
HANDLE
WINAPI
XFileCacheCreateUncachedFileA(
    IN LPCSTR lpFileName,
    IN DWORD dwDesiredAccess,
    IN DWORD dwShareMode,
    IN LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    IN DWORD dwCreationDisposition,
    IN DWORD dwFlagsAndAttributes,
    IN HANDLE hTemplateFile
   );
#define XFileCacheCreateUncachedFile XFileCacheCreateUncachedFileA


/* ---------------------------------------------------------------- */


#pragma pack(push, 4)
typedef struct _XFILECACHESTATS XFILECACHESTATS, *PXFILECACHESTATS;
struct _XFILECACHESTATS
{
    ULONGLONG           CachedTotal;
    DWORD               FileCount;

    DWORD               CacheHitOpens;
    DWORD               CacheMissOpens;
    DWORD               CacheHitReads;
    DWORD               CacheMissReads;
    LARGE_INTEGER       CacheHitBytesRequested;
    LARGE_INTEGER       CacheMissBytesRequested;
    LARGE_INTEGER       CacheCopyBytes;
    LARGE_INTEGER       CacheEvictBytes;
};
#pragma pack(pop)

DWORD
XFILECACHEAPI
XFileCacheGetStats(
   OUT PXFILECACHESTATS lpFileCacheStats
   );


#if defined(_DEBUG)

typedef struct _XFILECACHE_FIND_DATA XFILECACHE_FIND_DATA, *PXFILECACHE_FIND_DATA;
struct _XFILECACHE_FIND_DATA
{
    DWORD dwFileAttributes;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwMediaId;
    char cFileName[MAX_PATH];
};

HANDLE
XFILECACHEAPI
XFileCacheFindFirstFile(
    IN LPCSTR lpFileName,
    OUT PXFILECACHE_FIND_DATA pFindFileData
    );

BOOL
XFILECACHEAPI
XFileCacheFindNextFile(
   IN HANDLE hFindFile,
   OUT PXFILECACHE_FIND_DATA pFindFileData
   );

BOOL
XFILECACHEAPI
XFileCacheFindClose(
   IN HANDLE hFindFile
   );

#endif // _DEBUG



#ifdef __cplusplus
}
#endif

#endif // XFILECACHE_H
