/***
*direct.h - function declarations for directory handling/creation
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This include file contains the function declarations for the library
*       functions related to directory handling and creation.
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _INC_DIRECT
#define _INC_DIRECT

#include <crtdefs.h>

#ifdef  _MSC_VER
/*
 * Currently, all MS C compilers for Win32 platforms default to 8 byte
 * alignment.
 */
#pragma pack(push,_CRT_PACKING)
#endif  /* _MSC_VER */

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef _XBSTRICT

/* _getdiskfree structure for _getdiskfree() */
#ifndef _DISKFREE_T_DEFINED

struct _diskfree_t {
        unsigned total_clusters;
        unsigned avail_clusters;
        unsigned sectors_per_cluster;
        unsigned bytes_per_sector;
        };

#define _DISKFREE_T_DEFINED
#endif

/* function prototypes */

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_getcwd")
#pragma push_macro("_getdcwd")
#pragma push_macro("_getdcwd_nolock")
#undef _getcwd
#undef _getdcwd
#undef _getdcwd_nolock
#endif

_XBOX_CRT_UNSUPPORTED(_getcwd)
_CRTIMP __checkReturn __out_z_opt char * __cdecl _getcwd(__out_ecount_opt(_SizeInBytes) char * _DstBuf, __in int _SizeInBytes);
_XBOX_CRT_UNSUPPORTED(_getdcwd)
_CRTIMP __checkReturn __out_z_opt char * __cdecl _getdcwd(__in int _Drive, __out_ecount_opt(_SizeInBytes) char * _DstBuf, __in int _SizeInBytes);
_XBOX_CRT_UNSUPPORTED(_getdcwd_nolock)
__checkReturn __out_z_opt char * __cdecl _getdcwd_nolock(__in int _Drive, __out_ecount_opt(_SizeInBytes) char * _DstBuf, __in int _SizeInBytes);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_getcwd")
#pragma pop_macro("_getdcwd")
#pragma pop_macro("_getdcwd_nolock")
#endif

_XBOX_CRT_UNSUPPORTED(_chdir)
_CRTIMP __checkReturn int __cdecl _chdir(__in_z const char * _Path);
#endif // !_XBSTRICT
_CRTIMP __checkReturn int __cdecl _mkdir(__in_z const char * _Path);
_CRTIMP __checkReturn int __cdecl _rmdir(__in_z const char * _Path);

#ifndef _XBSTRICT
_XBOX_CRT_UNSUPPORTED(_chdrive)
_CRTIMP __checkReturn int __cdecl _chdrive(__in int _Drive);
_XBOX_CRT_UNSUPPORTED(_getdrive)
_CRTIMP __checkReturn int __cdecl _getdrive(void);
_XBOX_CRT_UNSUPPORTED(_getdrives)
_CRTIMP __checkReturn unsigned long __cdecl _getdrives(void);

#ifndef _GETDISKFREE_DEFINED
_XBOX_CRT_UNSUPPORTED(_getdiskfree)
_CRTIMP __checkReturn unsigned __cdecl _getdiskfree(__in unsigned _Drive, __out struct _diskfree_t * _DiskFree);
#define _GETDISKFREE_DEFINED
#endif

#endif // !_XBSTRICT


#ifndef _WDIRECT_DEFINED

#ifndef _XBSTRICT

/* wide function prototypes, also declared in wchar.h  */

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_wgetcwd")
#pragma push_macro("_wgetdcwd")
#pragma push_macro("_wgetdcwd_nolock")
#undef _wgetcwd
#undef _wgetdcwd
#undef _wgetdcwd_nolock
#endif

_XBOX_CRT_UNSUPPORTED(_wgetcwd)
_CRTIMP __checkReturn __out_z_opt wchar_t * __cdecl _wgetcwd(__out_ecount_opt(_SizeInWords) wchar_t * _DstBuf, __in int _SizeInWords);
_XBOX_CRT_UNSUPPORTED(_wgetdcwd)
_CRTIMP __checkReturn __out_z_opt wchar_t * __cdecl _wgetdcwd(__in int _Drive, __out_ecount_opt(_SizeInWords) wchar_t * _DstBuf, __in int _SizeInWords);
_XBOX_CRT_UNSUPPORTED(_wgetdcwd_nolock)
__checkReturn __out_z_opt wchar_t * __cdecl _wgetdcwd_nolock(__in int _Drive, __out_ecount_opt(_SizeInWords) wchar_t * _DstBuf, __in int _SizeInWords);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_wgetcwd")
#pragma pop_macro("_wgetdcwd")
#pragma pop_macro("_wgetdcwd_nolock")
#endif

_XBOX_CRT_UNSUPPORTED(_wchdir)
_CRTIMP __checkReturn int __cdecl _wchdir(__in_z const wchar_t * _Path);
#endif // !_XBSTRICT
_CRTIMP __checkReturn int __cdecl _wmkdir(__in_z const wchar_t * _Path);
_CRTIMP __checkReturn int __cdecl _wrmdir(__in_z const wchar_t * _Path);

#define _WDIRECT_DEFINED
#endif

#if     !__STDC__

#ifndef _XBSTRICT

/* Non-ANSI names for compatibility */
#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("getcwd")
#undef getcwd
#endif

_XBOX_CRT_UNSUPPORTED_NONSTDC(getcwd, _getcwd)
_CRTIMP __checkReturn __out_z_opt char * __cdecl getcwd(__out_ecount_opt(_SizeInBytes) char * _DstBuf, __in int _SizeInBytes);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("getcwd")
#endif

_XBOX_CRT_UNSUPPORTED_NONSTDC(chdir, _chdir)
_CRTIMP __checkReturn int __cdecl chdir(__in_z const char * _Path);
#endif // !_XBSTRICT
_CRT_NONSTDC_DEPRECATE(_mkdir) _CRTIMP __checkReturn int __cdecl mkdir(__in_z const char * _Path);
_CRT_NONSTDC_DEPRECATE(_rmdir) _CRTIMP __checkReturn int __cdecl rmdir(__in_z const char * _Path);

#ifndef _XBSTRICT
#define diskfree_t  _diskfree_t
#endif // !_XBSTRICT

#endif  /* __STDC__ */

#ifdef  __cplusplus
}
#endif

#ifdef  _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_DIRECT */
