/***
*tchar.h - definitions for generic international text functions
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Definitions for generic international functions, mostly defines
*       which map string/formatted-io/ctype functions to char, wchar_t, or
*       MBCS versions.  To be used for compatibility between single-byte,
*       multi-byte and Unicode text models.
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif

#include <crtdefs.h>

#ifndef _INC_TCHAR
#define _INC_TCHAR

#ifdef _STRSAFE_H_INCLUDED_
#error Need to include strsafe.h after tchar.h
#endif

#ifdef  _MSC_VER
#pragma warning(disable:4514)       /* disable unwanted C++ /W4 warning */
/* #pragma warning(default:4514) */ /* use this to reenable, if necessary */
#endif  /* _MSC_VER */

/* Notes */

/* There is no:
 *      _tcscat_l
 *      _tcscpy_l
 * because mbscat and mbscpy just behave like strcat and strcpy,
 * so no special locale-specific behavior is needed.
 */

/* Functions like:
 *      _strncat_l
 *      _strncat_s_l
 * are only available if ANSI is defined (i.e. no _UNICODE nor _MBCS),
 * because these functions are only accessible through the _tcs macros.
 */

#ifdef  __cplusplus
extern "C" {
#endif

#if !defined (_XBOX_CRT_DEPRECATE_FAR_MAPPINGS) && !defined (_CRT_FAR_MAPPINGS_NO_DEPRECATE)
#define _CRT_FAR_MAPPINGS_NO_DEPRECATE
#endif

#ifndef _CRT_FAR_MAPPINGS_NO_DEPRECATE
/*
Long ago, these f prefix text functions referred to handling of text in segmented architectures. Ever since the move
to Win32 they have been obsolete names, but we kept them around as aliases. Now that we have a deprecation 
mechanism we can warn about them. You should switch to the identical function without the f prefix.
*/
#pragma deprecated("_ftcscat")
#pragma deprecated("_ftcschr")
#pragma deprecated("_ftcscpy")
#pragma deprecated("_ftcscspn")
#pragma deprecated("_ftcslen")
#pragma deprecated("_ftcsncat")
#pragma deprecated("_ftcsncpy")
#pragma deprecated("_ftcspbrk")
#pragma deprecated("_ftcsrchr")
#pragma deprecated("_ftcsspn")
#pragma deprecated("_ftcsstr")
#pragma deprecated("_ftcstok")
#pragma deprecated("_ftcsdup")
#pragma deprecated("_ftcsnset")
#pragma deprecated("_ftcsrev")
#pragma deprecated("_ftcsset")
#pragma deprecated("_ftcscmp")
#pragma deprecated("_ftcsicmp")
#pragma deprecated("_ftcsnccmp")
#pragma deprecated("_ftcsncmp")
#pragma deprecated("_ftcsncicmp")
#pragma deprecated("_ftcsnicmp")
#pragma deprecated("_ftcscoll")
#pragma deprecated("_ftcsicoll")
#pragma deprecated("_ftcsnccoll")
#pragma deprecated("_ftcsncoll")
#pragma deprecated("_ftcsncicoll")
#pragma deprecated("_ftcsnicoll")
#pragma deprecated("_ftcsclen")
#pragma deprecated("_ftcsnccat")
#pragma deprecated("_ftcsnccpy")
#pragma deprecated("_ftcsncset")
#pragma deprecated("_ftcsdec")
#pragma deprecated("_ftcsinc")
#pragma deprecated("_ftcsnbcnt")
#pragma deprecated("_ftcsnccnt")
#pragma deprecated("_ftcsnextc")
#pragma deprecated("_ftcsninc")
#pragma deprecated("_ftcsspnp")
#pragma deprecated("_ftcslwr")
#pragma deprecated("_ftcsupr")
#pragma deprecated("_ftclen")
#pragma deprecated("_ftccpy")
#pragma deprecated("_ftccmp")
#endif /* ndef _CRT_FAR_MAPPINGS_NO_DEPRECATE */

#define _ftcscat    _tcscat
#define _ftcschr    _tcschr
#define _ftcscpy    _tcscpy
#define _ftcscspn   _tcscspn
#define _ftcslen    _tcslen
#define _ftcsncat   _tcsncat
#define _ftcsncpy   _tcsncpy
#define _ftcspbrk   _tcspbrk
#define _ftcsrchr   _tcsrchr
#define _ftcsspn    _tcsspn
#define _ftcsstr    _tcsstr
#define _ftcstok    _tcstok

#define _ftcsdup    _tcsdup
#define _ftcsnset   _tcsnset
#define _ftcsrev    _tcsrev
#define _ftcsset    _tcsset

#define _ftcscmp      _tcscmp
#define _ftcsicmp     _tcsicmp
#define _ftcsnccmp    _tcsnccmp
#define _ftcsncmp     _tcsncmp
#define _ftcsncicmp   _tcsncicmp
#define _ftcsnicmp    _tcsnicmp

#define _ftcscoll     _tcscoll
#define _ftcsicoll    _tcsicoll
#define _ftcsnccoll   _tcsnccoll
#define _ftcsncoll    _tcsncoll
#define _ftcsncicoll  _tcsncicoll
#define _ftcsnicoll   _tcsnicoll

/* Redundant "logical-character" mappings */

#define _ftcsclen   _tcsclen
#define _ftcsnccat  _tcsnccat
#define _ftcsnccpy  _tcsnccpy
#define _ftcsncset  _tcsncset

#define _ftcsdec    _tcsdec
#define _ftcsinc    _tcsinc
#define _ftcsnbcnt  _tcsnbcnt
#define _ftcsnccnt  _tcsnccnt
#define _ftcsnextc  _tcsnextc
#define _ftcsninc   _tcsninc
#define _ftcsspnp   _tcsspnp

#define _ftcslwr    _tcslwr
#define _ftcsupr    _tcsupr

#define _ftclen     _tclen
#define _ftccpy     _tccpy
#define _ftccmp     _tccmp

#ifndef _CONST_RETURN
#ifdef  __cplusplus
#define _CONST_RETURN  const
#define _CRT_CONST_CORRECT_OVERLOADS
#else
#define _CONST_RETURN
#endif
#endif

/* For backwards compatibility */
#define _WConst_return _CONST_RETURN

#ifdef  _UNICODE

#ifdef  __cplusplus
}   /* ... extern "C" */
#endif

/* ++++++++++++++++++++ UNICODE ++++++++++++++++++++ */

#include <wchar.h>

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef _WCTYPE_T_DEFINED
typedef unsigned short wint_t;
typedef unsigned short wctype_t;
#define _WCTYPE_T_DEFINED
#endif

#ifndef __TCHAR_DEFINED
typedef wchar_t     _TCHAR;
typedef wchar_t     _TSCHAR;
typedef wchar_t     _TUCHAR;
typedef wchar_t     _TXCHAR;
typedef wint_t      _TINT;
#define __TCHAR_DEFINED
#endif

#ifndef _TCHAR_DEFINED
#if     !__STDC__
typedef wchar_t     TCHAR;
#endif
#define _TCHAR_DEFINED
#endif

#define _TEOF       WEOF

#define __T(x)      L ## x


/* Program */

#define _tmain      wmain

/* Formatted i/o */

#define _tprintf        wprintf
#define _tprintf_l      _wprintf_l
#define _tprintf_s      wprintf_s
#define _tprintf_s_l    _wprintf_s_l
#define _tprintf_p      _wprintf_p
#define _tprintf_p_l    _wprintf_p_l
#define _tcprintf       _cwprintf
#define _tcprintf_l     _cwprintf_l
#define _tcprintf_s     _cwprintf_s
#define _tcprintf_s_l   _cwprintf_s_l
#define _tcprintf_p     _cwprintf_p
#define _tcprintf_p_l   _cwprintf_p_l
#define _vtcprintf      _vcwprintf
#define _vtcprintf_l    _vcwprintf_l
#define _vtcprintf_s    _vcwprintf_s
#define _vtcprintf_s_l  _vcwprintf_s_l
#define _vtcprintf_p    _vcwprintf_p
#define _vtcprintf_p_l  _vcwprintf_p_l
#define _ftprintf       fwprintf
#define _ftprintf_l     _fwprintf_l
#define _ftprintf_s     fwprintf_s
#define _ftprintf_s_l   _fwprintf_s_l
#define _ftprintf_p     _fwprintf_p
#define _ftprintf_p_l   _fwprintf_p_l
#define _stprintf       _swprintf
#define _stprintf_l     __swprintf_l
#define _stprintf_s     swprintf_s
#define _stprintf_s_l   _swprintf_s_l
#define _stprintf_p     _swprintf_p
#define _stprintf_p_l   _swprintf_p_l
#define _sctprintf      _scwprintf
#define _sctprintf_l    _scwprintf_l
#define _sctprintf_p    _scwprintf_p
#define _sctprintf_p_l  _scwprintf_p_l
#define _sntprintf      _snwprintf
#define _sntprintf_l    _snwprintf_l
#define _sntprintf_s    _snwprintf_s
#define _sntprintf_s_l  _snwprintf_s_l
#define _vtprintf       vwprintf
#define _vtprintf_l     _vwprintf_l
#define _vtprintf_s     vwprintf_s
#define _vtprintf_s_l   _vwprintf_s_l
#define _vtprintf_p     _vwprintf_p
#define _vtprintf_p_l   _vwprintf_p_l
#define _vftprintf      vfwprintf
#define _vftprintf_l    _vfwprintf_l
#define _vftprintf_s    vfwprintf_s
#define _vftprintf_s_l  _vfwprintf_s_l
#define _vftprintf_p    _vfwprintf_p
#define _vftprintf_p_l  _vfwprintf_p_l
#define _vstprintf      _vswprintf
#define _vstprintf_l    _vswprintf_l
#define _vstprintf_s    vswprintf_s
#define _vstprintf_s_l  _vswprintf_s_l
#define _vstprintf_p    _vswprintf_p
#define _vstprintf_p_l  _vswprintf_p_l
#define _vsctprintf     _vscwprintf
#define _vsctprintf_l   _vscwprintf_l
#define _vsctprintf_p   _vscwprintf_p
#define _vsctprintf_p_l _vscwprintf_p_l
#define _vsntprintf     _vsnwprintf
#define _vsntprintf_l   _vsnwprintf_l
#define _vsntprintf_s   _vsnwprintf_s
#define _vsntprintf_s_l _vsnwprintf_s_l

#define _tscanf         wscanf
#define _tscanf_l       _wscanf_l
#define _tscanf_s       wscanf_s
#define _tscanf_s_l     _wscanf_s_l
#define _tcscanf        _cwscanf
#define _tcscanf_l      _cwscanf_l
#define _tcscanf_s      _cwscanf_s
#define _tcscanf_s_l    _cwscanf_s_l
#define _ftscanf        fwscanf
#define _ftscanf_l      _fwscanf_l
#define _ftscanf_s      fwscanf_s
#define _ftscanf_s_l    _fwscanf_s_l
#define _stscanf        swscanf
#define _stscanf_l      _swscanf_l
#define _stscanf_s      swscanf_s
#define _stscanf_s_l    _swscanf_s_l
#define _sntscanf       _snwscanf
#define _sntscanf_l     _snwscanf_l
#define _sntscanf_s     _snwscanf_s
#define _sntscanf_s_l   _snwscanf_s_l


/* Unformatted i/o */

#define _fgettc         fgetwc
#define _fgettc_nolock  _fgetwc_nolock
#define _fgettchar      _fgetwchar
#define _fgetts         fgetws
#define _fputtc         fputwc
#define _fputtc_nolock  _fputwc_nolock
#define _fputtchar      _fputwchar
#define _fputts         fputws
#define _cputts         _cputws
#define _cgetts         _cgetws
#define _cgetts_s       _cgetws_s
#define _gettc          getwc
#define _gettc_nolock   _getwc_nolock
#define _gettch         _getwch
#define _gettch_nolock  _getwch_nolock
#define _gettche        _getwche
#define _gettche_nolock _getwche_nolock
#define _gettchar       getwchar
#define _gettchar_nolock _getwchar_nolock
#define _getts          _getws
#define _getts_s        _getws_s
#define _puttc          putwc
#define _puttc_nolock   _putwc_nolock
#define _puttchar       putwchar
#define _puttchar_nolock _putwchar_nolock
#define _puttch         _putwch
#define _puttch_nolock  _putwch_nolock
#define _putts          _putws
#define _ungettc        ungetwc
#define _ungettc_nolock _ungetwc_nolock
#define _ungettch       _ungetwch
#define _ungettch_nolock _ungetwch_nolock


/* String conversion functions */

#define _tcstod     wcstod
#define _tcstol     wcstol
#define _tcstoul    wcstoul
#define _tcstoi64   _wcstoi64
#define _tcstoui64  _wcstoui64
#define _tstof      _wtof
#define _tstol      _wtol
#define _tstoi      _wtoi
#define _tstoi64    _wtoi64
#define _tcstod_l     _wcstod_l
#define _tcstol_l     _wcstol_l
#define _tcstoul_l    _wcstoul_l
#define _tcstoi64_l   _wcstoi64_l
#define _tcstoui64_l  _wcstoui64_l
#define _tstof_l      _wtof_l
#define _tstol_l      _wtol_l
#define _tstoi_l      _wtoi_l
#define _tstoi64_l    _wtoi64_l

#define _itot_s     _itow_s
#define _ltot_s     _ltow_s
#define _ultot_s    _ultow_s
#define _itot       _itow
#define _ltot       _ltow
#define _ultot      _ultow
#define _ttoi       _wtoi
#define _ttol       _wtol

#define _ttoi64     _wtoi64
#define _i64tot_s   _i64tow_s
#define _ui64tot_s  _ui64tow_s
#define _i64tot     _i64tow
#define _ui64tot    _ui64tow

/* String functions */

#define _tcscat         wcscat
#define _tcscat_s       wcscat_s
#define _tcschr         wcschr
#define _tcscpy         wcscpy
#define _tcscpy_s       wcscpy_s
#define _tcscspn        wcscspn
#define _tcslen         wcslen
#define _tcsnlen        wcsnlen
#define _tcsncat        wcsncat
#define _tcsncat_s      wcsncat_s
#define _tcsncat_l      _wcsncat_l
#define _tcsncat_s_l    _wcsncat_s_l
#define _tcsncpy        wcsncpy
#define _tcsncpy_s      wcsncpy_s
#define _tcsncpy_l      _wcsncpy_l
#define _tcsncpy_s_l    _wcsncpy_s_l
#define _tcspbrk        wcspbrk
#define _tcsrchr        wcsrchr
#define _tcsspn         wcsspn
#define _tcsstr         wcsstr
#define _tcstok         wcstok
#define _tcstok_s       wcstok_s
#define _tcstok_l       _wcstok_l
#define _tcstok_s_l     _wcstok_s_l
#define _tcserror       _wcserror
#define _tcserror_s     _wcserror_s
#define __tcserror      __wcserror
#define __tcserror_s    __wcserror_s

#define _tcsdup         _wcsdup
#define _tcsnset        _wcsnset
#define _tcsnset_s      _wcsnset_s
#define _tcsnset_l      _wcsnset_l
#define _tcsnset_s_l    _wcsnset_s_l
#define _tcsrev         _wcsrev
#define _tcsset         _wcsset
#define _tcsset_s       _wcsset_s
#define _tcsset_l       _wcsset_l
#define _tcsset_s_l     _wcsset_s_l

#define _tcscmp         wcscmp
#define _tcsicmp        _wcsicmp
#define _tcsicmp_l      _wcsicmp_l
#define _tcsnccmp       wcsncmp
#define _tcsncmp        wcsncmp
#define _tcsncicmp      _wcsnicmp
#define _tcsncicmp_l    _wcsnicmp_l
#define _tcsnicmp       _wcsnicmp
#define _tcsnicmp_l     _wcsnicmp_l

#define _tcscoll        wcscoll
#define _tcscoll_l      _wcscoll_l
#define _tcsicoll       _wcsicoll
#define _tcsicoll_l     _wcsicoll_l
#define _tcsnccoll      _wcsncoll
#define _tcsnccoll_l    _wcsncoll_l
#define _tcsncoll       _wcsncoll
#define _tcsncoll_l     _wcsncoll_l
#define _tcsncicoll     _wcsnicoll
#define _tcsncicoll_l   _wcsnicoll_l
#define _tcsnicoll      _wcsnicoll
#define _tcsnicoll_l    _wcsnicoll_l

#ifdef _DEBUG
#define _tcsdup_dbg _wcsdup_dbg
#endif

/* Execute functions */

#define _texecl     _wexecl
#define _texecle    _wexecle
#define _texeclp    _wexeclp
#define _texeclpe   _wexeclpe
#define _texecv     _wexecv
#define _texecve    _wexecve
#define _texecvp    _wexecvp
#define _texecvpe   _wexecvpe

#define _tspawnl    _wspawnl
#define _tspawnle   _wspawnle
#define _tspawnlp   _wspawnlp
#define _tspawnlpe  _wspawnlpe
#define _tspawnv    _wspawnv
#define _tspawnve   _wspawnve
#define _tspawnvp   _wspawnvp
#define _tspawnvp   _wspawnvp
#define _tspawnvpe  _wspawnvpe

#define _tsystem    _wsystem


/* Time functions */

#define _tasctime   _wasctime
#define _tctime     _wctime
#define _tctime32   _wctime32
#define _tctime64   _wctime64
#define _tstrdate   _wstrdate
#define _tstrtime   _wstrtime
#define _tutime     _wutime
#define _tutime32   _wutime32
#define _tutime64   _wutime64
#define _tcsftime   wcsftime
#define _tcsftime_l _wcsftime_l

#define _tasctime_s   _wasctime_s
#define _tctime_s     _wctime_s
#define _tctime32_s   _wctime32_s
#define _tctime64_s   _wctime64_s
#define _tstrdate_s   _wstrdate_s
#define _tstrtime_s   _wstrtime_s

/* Directory functions */

#define _tchdir             _wchdir
#define _tgetcwd            _wgetcwd
#define _tgetdcwd           _wgetdcwd
#define _tgetdcwd_nolock    _wgetdcwd_nolock
#define _tmkdir             _wmkdir
#define _trmdir             _wrmdir

#ifdef _DEBUG
#define _tgetcwd_dbg        _wgetcwd_dbg
#define _tgetdcwd_dbg       _wgetdcwd_dbg
#define _tgetdcwd_lk_dbg    _wgetdcwd_lk_dbg
#endif

/* Environment/Path functions */

#define _tfullpath      _wfullpath
#define _tgetenv        _wgetenv
#define _tgetenv_s      _wgetenv_s
#define _tdupenv_s      _wdupenv_s
#define _tmakepath      _wmakepath
#define _tmakepath_s    _wmakepath_s
#define _tpgmptr        _wpgmptr
#define _get_tpgmptr    _get_wpgmptr
#define _tputenv        _wputenv
#define _tputenv_s      _wputenv_s
#define _tsearchenv     _wsearchenv
#define _tsearchenv_s   _wsearchenv_s
#define _tsplitpath     _wsplitpath
#define _tsplitpath_s   _wsplitpath_s

#ifdef _DEBUG
#define _tfullpath_dbg  _wfullpath_dbg
#define _tdupenv_s_dbg  _wdupenv_s_dbg
#endif

/* Stdio functions */

#define _tfdopen    _wfdopen
#define _tfsopen    _wfsopen
#define _tfopen     _wfopen
#define _tfopen_s   _wfopen_s
#define _tfreopen   _wfreopen
#define _tfreopen_s _wfreopen_s
#define _tperror    _wperror
#define _tpopen     _wpopen
#define _ttempnam   _wtempnam
#define _ttmpnam    _wtmpnam
#define _ttmpnam_s  _wtmpnam_s

#ifdef _DEBUG
#define _ttempnam_dbg   _wtempnam_dbg
#endif


/* Io functions */

#define _taccess    _waccess
#define _taccess_s  _waccess_s
#define _tchmod     _wchmod
#define _tcreat     _wcreat
#define _tfindfirst       _wfindfirst
#define _tfindfirst32     _wfindfirst32
#define _tfindfirst64     _wfindfirst64
#define _tfindfirsti64    _wfindfirsti64
#define _tfindfirst32i64  _wfindfirst32i64
#define _tfindfirst64i32  _wfindfirst64i32
#define _tfindnext        _wfindnext
#define _tfindnext32      _wfindnext32
#define _tfindnext64      _wfindnext64
#define _tfindnexti64     _wfindnexti64
#define _tfindnext32i64   _wfindnext32i64
#define _tfindnext64i32   _wfindnext64i32
#define _tmktemp    _wmktemp
#define _tmktemp_s  _wmktemp_s
#define _topen      _wopen
#define _tremove    _wremove
#define _trename    _wrename
#define _tsopen     _wsopen
#define _tsopen_s   _wsopen_s
#define _tunlink    _wunlink

#define _tfinddata_t      _wfinddata_t
#define _tfinddata32_t    _wfinddata32_t
#define _tfinddata64_t    _wfinddata64_t
#define _tfinddatai64_t   _wfinddatai64_t
#define _tfinddata32i64_t _wfinddata32i64_t
#define _tfinddata64i32_t _wfinddata64i32_t


/* Stat functions */

#define _tstat      _wstat
#define _tstat32    _wstat32
#define _tstat32i64 _wstat32i64
#define _tstat64    _wstat64
#define _tstat64i32 _wstat64i32
#define _tstati64   _wstati64


/* Setlocale functions */

#define _tsetlocale _wsetlocale


/* Redundant "logical-character" mappings */

#define _tcsclen        wcslen
#define _tcscnlen       wcsnlen
#define _tcsclen_l(_String, _Locale) wcslen(_String)
#define _tcscnlen_l(_String, _Max_count, _Locale) wcsnlen((_String), (_Max_count))
#define _tcsnccat       wcsncat
#define _tcsnccat_s     wcsncat_s
#define _tcsnccat_l     _wcsncat_l
#define _tcsnccat_s_l   _wcsncat_s_l
#define _tcsnccpy       wcsncpy
#define _tcsnccpy_s     wcsncpy_s
#define _tcsnccpy_l     _wcsncpy_l
#define _tcsnccpy_s_l   _wcsncpy_s_l
#define _tcsncset       _wcsnset
#define _tcsncset_s     _wcsnset_s
#define _tcsncset_l     _wcsnset_l
#define _tcsncset_s_l   _wcsnset_s_l

#define _tcsdec     _wcsdec
#define _tcsinc     _wcsinc
#define _tcsnbcnt   _wcsncnt
#define _tcsnccnt   _wcsncnt
#define _tcsnextc   _wcsnextc
#define _tcsninc    _wcsninc
#define _tcsspnp    _wcsspnp

#define _tcslwr     _wcslwr
#define _tcslwr_l   _wcslwr_l
#define _tcslwr_s   _wcslwr_s
#define _tcslwr_s_l _wcslwr_s_l
#define _tcsupr     _wcsupr
#define _tcsupr_l   _wcsupr_l
#define _tcsupr_s   _wcsupr_s
#define _tcsupr_s_l _wcsupr_s_l
#define _tcsxfrm    wcsxfrm
#define _tcsxfrm_l  _wcsxfrm_l


#if     __STDC__ || defined(_NO_INLINING)
#define _tclen(_pc) (1)
#define _tccpy(_pc1,_cpc2) ((*(_pc1) = *(_cpc2)))
#define _tccpy_l(_pc1,_cpc2,_locale) _tccpy((_pc1),(_cpc2))
#define _tccmp(_cpc1,_cpc2) ((*(_cpc1))-(*(_cpc2)))
#else   /* __STDC__ */
__inline __checkReturn size_t __CRTDECL _tclen(__in_z const wchar_t *_Cpc)
{ 
    /* avoid compiler warning */
    (void *)_Cpc;
    return 1;
}
__inline void __CRTDECL _tccpy(__out wchar_t *_Pc1, __in_z const wchar_t *_Cpc2) { *_Pc1 = (wchar_t)*_Cpc2; }
__inline void __CRTDECL _tccpy_l(__out wchar_t *_Pc1, __in_z const wchar_t *_Cpc2, __in_opt _locale_t _Locale)
{
    _CRT_UNUSED(_Locale);
    _tccpy(_Pc1, _Cpc2);
}
__inline __checkReturn int __CRTDECL _tccmp(__in_z const wchar_t *_Cpc1, __in_z const wchar_t *_Cpc2) { return (int) ((*_Cpc1)-(*_Cpc2)); }
#endif  /* __STDC__ */

/* ctype functions */

#define _istalnum   iswalnum
#define _istalnum_l   _iswalnum_l
#define _istalpha   iswalpha
#define _istalpha_l   _iswalpha_l
#define _istascii   iswascii
#define _istcntrl   iswcntrl
#define _istcntrl_l   _iswcntrl_l
#define _istdigit   iswdigit
#define _istdigit_l   _iswdigit_l
#define _istgraph   iswgraph
#define _istgraph_l   _iswgraph_l
#define _istlower   iswlower
#define _istlower_l   _iswlower_l
#define _istprint   iswprint
#define _istprint_l   _iswprint_l
#define _istpunct   iswpunct
#define _istpunct_l   _iswpunct_l
#define _istspace   iswspace
#define _istspace_l   _iswspace_l
#define _istupper   iswupper
#define _istupper_l   _iswupper_l
#define _istxdigit  iswxdigit
#define _istxdigit_l  _iswxdigit_l

#define _totupper   towupper
#define _totupper_l   _towupper_l
#define _totlower   towlower
#define _totlower_l   _towlower_l

#define _istlegal(_Char)                (1)
#define _istlead(_Char)                 (0)
#define _istleadbyte(_Char)             (0)
#define _istleadbyte_l(_Char, _Locale)  (0)


#if     __STDC__ || defined(_NO_INLINING)
#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? NULL : (_cpc2)-1)
#define _wcsinc(_pc)    ((_pc)+1)
#define _wcsnextc(_cpc) ((unsigned int) *(_cpc))
#define _wcsninc(_pc, _sz) (((_pc)+(_sz)))
_CRTIMP __checkReturn size_t __cdecl __wcsncnt(__in_ecount_z(_MaxCount) const wchar_t * _Str, __in size_t _MaxCount);
#define _wcsncnt(_cpc, _sz) (__wcsncnt(_cpc,_sz))
#define _wcsspnp(_cpc1, _cpc2)                                                          (_cpc1==NULL ? NULL : ((*((_cpc1)+wcsspn(_cpc1,_cpc2))) ? ((_cpc1)+wcsspn(_cpc1,_cpc2)) : NULL))
#define _wcsncpy_l(_Destination, _Source, _Count, _Locale)                              (wcsncpy(_Destination, _Source, _Count))
#if __STDC_WANT_SECURE_LIB__
#define _wcsncpy_s_l(_Destination, _Destination_size_chars, _Source, _Count, _Locale)   (wcsncpy_s(_Destination, _Destination_size_chars, _Source, _Count))
#endif
#define _wcsncat_l(_Destination, _Source, _Count, _Locale)                              (wcsncat(_Destination, _Source, _Count))
#if __STDC_WANT_SECURE_LIB__
#define _wcsncat_s_l(_Destination, _Destination_size_chars, _Source, _Count, _Locale)   (wcsncat_s(_Destination, _Destination_size_chars, _Source, _Count))
#endif
#define _wcstok_l(_String, _Delimiters, _Locale)                                        (wcstok(_String, _Delimiters))
#define _wcstok_s_l(_String, _Delimiters, _Current_position, _Locale)                   (wcstok_s(_String, _Delimiters, _Current_position))
#define _wcsnset_l(_Destination, _Value, _Count, _Locale)                               (_wcsnset(_Destination, _Value, _Count))
#define _wcsnset_s_l(_Destination, _Destination_size_chars, _Value, _Count, _Locale)    (_wcsnset_s(_Destination, _Destination_size_chars, _Value, _Count))
#define _wcsset_l(_Destination, _Value, _Locale)                                        (_wcsset(_Destination, _Value))
#define _wcsset_s_l(_Destination, _Destination_size_chars, _Value, _Locale)             (_wcsset_s(_Destination, _Destination_size_chars, _Value))
#else   /* __STDC__ */
__inline __checkReturn wchar_t * __CRTDECL _wcsdec(__in_z const wchar_t * _Cpc1, __in_z const wchar_t * _Cpc2) { return (wchar_t *)((_Cpc1)>=(_Cpc2) ? NULL : ((_Cpc2)-1)); }
__inline __checkReturn wchar_t * __CRTDECL _wcsinc(__in_z const wchar_t * _Pc) { return (wchar_t *)(_Pc+1); }
__inline __checkReturn unsigned int __CRTDECL _wcsnextc(__in_z const wchar_t * _Cpc) { return (unsigned int)*_Cpc; }
__inline __checkReturn wchar_t * __CRTDECL _wcsninc(__in_z const wchar_t * _Pc, __in size_t _Sz) { return (wchar_t *)(_Pc+_Sz); }
__inline __checkReturn size_t __CRTDECL _wcsncnt( __in_ecount_z(_Cnt) const wchar_t * _String, __in size_t _Cnt) 
{ 
        size_t n = _Cnt; 
        wchar_t *cp = (wchar_t *)_String; 
        while (n-- && *cp) 
                cp++; 
        return _Cnt - n - 1; 
}
__inline __checkReturn wchar_t * __CRTDECL _wcsspnp
( 
    __in_z const wchar_t * _Cpc1, 
    __in_z const wchar_t * _Cpc2
)
{
    return _Cpc1==NULL ? NULL : ((*(_Cpc1 += wcsspn(_Cpc1,_Cpc2))!='\0') ? (wchar_t*)_Cpc1 : NULL); 
}

#if __STDC_WANT_SECURE_LIB__
__inline __checkReturn_wat errno_t __CRTDECL _wcsncpy_s_l(__out_ecount_z(_Destination_size_chars) wchar_t *_Destination, __in size_t _Destination_size_chars, __in_z const wchar_t *_Source, __in size_t _Count, __in_opt _locale_t _Locale)
{
    _CRT_UNUSED(_Locale);
    return wcsncpy_s(_Destination, _Destination_size_chars, _Source, _Count);
}
#endif

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(errno_t, _wcsncpy_s_l, __out_ecount(_Size) wchar_t, _Dest, __in_z const wchar_t *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(wchar_t *, __RETURN_POLICY_DST, _wcsncpy_l, _wcsncpy_s_l, __out_ecount_z(_Size) wchar_t, __out_ecount(_Count) wchar_t, _Dst, __in_z const wchar_t *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)
{
    _CRT_UNUSED(_Locale);
#pragma warning( push )
#pragma warning( disable : 4996 6054)
    return wcsncpy(_Dst, _Source, _Count);
#pragma warning( pop )
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(wchar_t *, __RETURN_POLICY_DST, _wcsncpy_l, _wcsncpy_s_l, __out_ecount_z(_Size) wchar_t, __out_ecount(_Count) wchar_t, _Dst, __in_z const wchar_t *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

#if __STDC_WANT_SECURE_LIB__
__inline __checkReturn_wat errno_t __CRTDECL _wcsncat_s_l(__inout_ecount_z(_Destination_size_chars) wchar_t *_Destination, __in size_t _Destination_size_chars, __in_z const wchar_t *_Source, __in size_t _Count, __in_opt _locale_t _Locale)
{
    _CRT_UNUSED(_Locale);
    return wcsncat_s(_Destination, _Destination_size_chars, _Source, _Count);
}
#endif

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(errno_t, _wcsncat_s_l, __inout_ecount(_Size) wchar_t, _Dest, __in_z const wchar_t *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(wchar_t *, __RETURN_POLICY_DST, _wcsncat_l, _wcsncat_s_l, __inout_ecount_z(_Size) wchar_t, __inout_z wchar_t, _Dst, __in_z const wchar_t *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)
{
    _CRT_UNUSED(_Locale);
#pragma warning( push )
#pragma warning( disable : 4996 6054 6059)
/* prefast noise VSW 489802 */
    return wcsncat(_Dst, _Source, _Count);
#pragma warning( pop )
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(wchar_t *, __RETURN_POLICY_DST, _wcsncat_l, _wcsncat_s_l, __inout_ecount_z(_Size) wchar_t, __inout_z wchar_t, _Dst, __in_z const wchar_t *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

_CRT_INSECURE_DEPRECATE(_wcstok_s_l) __inline wchar_t * _wcstok_l(__inout_z_opt wchar_t * _String, __in_z const wchar_t * _Delimiters, __in_opt _locale_t _Locale) 
{
    _CRT_UNUSED(_Locale);
#pragma warning(push)
#pragma warning(disable:4996)
	return wcstok(_String,_Delimiters);
#pragma warning(pop)
}

__inline wchar_t * _wcstok_s_l(__inout_z_opt wchar_t * _String, __in_z const wchar_t * _Delimiters, __deref_inout_z_opt wchar_t **_Current_position, __in_opt _locale_t _Locale) 
{
    _CRT_UNUSED(_Locale);
    return wcstok_s(_String, _Delimiters, _Current_position);
}

__inline __checkReturn_wat errno_t _wcsnset_s_l(__inout_ecount_z(_Destination_size_chars) wchar_t * _Destination, __in size_t _Destination_size_chars, __in_z wchar_t _Value, __in size_t _Count, __in_opt _locale_t _Locale)
{
    _CRT_UNUSED(_Locale);
    return _wcsnset_s(_Destination, _Destination_size_chars, _Value, _Count);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(errno_t, _wcsnset_s_l, __inout_ecount_z(_Size) wchar_t, _Dest, __in_z wchar_t, _Value, __in size_t, _Count, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(wchar_t *, __RETURN_POLICY_DST, _wcsnset_l, _wcsnset_s_l, __inout_ecount_z(_Size) wchar_t, __inout_ecount_z(_MaxCount) wchar_t, _Dst, __in_z wchar_t, _Value, __in size_t, _MaxCount, __in_opt _locale_t, _Locale)
{
    _CRT_UNUSED(_Locale);
#pragma warning( push )
#pragma warning( disable : 4996 )
    return _wcsnset(_Dst, _Value, _MaxCount);
#pragma warning( pop )
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(wchar_t *, __RETURN_POLICY_DST, _wcsnset_l, _wcsnset_s_l, __inout_ecount_z(_Size) wchar_t, __inout_ecount_z(_MaxCount) wchar_t, _Dst, __in_z wchar_t, _Value, __in size_t, _MaxCount, __in_opt _locale_t, _Locale)

__inline __checkReturn_wat errno_t _wcsset_s_l(__inout_ecount_z(_Destination_size_chars) wchar_t * _Destination, __in size_t _Destination_size_chars, __in_z wchar_t _Value, __in_opt _locale_t _Locale) 
{
    _CRT_UNUSED(_Locale);
    return _wcsset_s(_Destination, _Destination_size_chars, _Value);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _wcsset_s_l, __inout_ecount_z(_Size) wchar_t, _Dest, __in_z wchar_t, _Value, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(wchar_t *, __RETURN_POLICY_DST, _wcsset_l, _wcsset_s_l, __inout_ecount_z(_Size) wchar_t, __inout_z wchar_t, _Dst, __in_z wchar_t, _Value, __in_opt _locale_t, _Locale)
{
    _CRT_UNUSED(_Locale);
#pragma warning( push )
#pragma warning( disable : 4996 )
    return _wcsset(_Dst, _Value);
#pragma warning( pop )
}

__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(wchar_t *, __RETURN_POLICY_DST, _wcsset_l, _wcsset_s_l, __inout_ecount_z(_Size) wchar_t, __inout_z wchar_t, _Dst, __in_z wchar_t, _Value, __in_opt _locale_t, _Locale)

#endif  /* __STDC__ */


#else   /* ndef _UNICODE */

/* ++++++++++++++++++++ SBCS and MBCS ++++++++++++++++++++ */

#ifdef  __cplusplus
}   /* ... extern "C" */
#endif

#include <string.h>

#ifdef  __cplusplus
extern "C" {
#endif


#define _TEOF       EOF

#define __T(x)      x


/* Program */

#define _tmain      main


/* Formatted i/o */

#define _tprintf        printf
#define _tprintf_l      _printf_l
#define _tprintf_s      printf_s
#define _tprintf_s_l    _printf_s_l
#define _tprintf_p      _printf_p
#define _tprintf_p_l    _printf_p_l
#define _tcprintf       _cprintf
#define _tcprintf_l     _cprintf_l
#define _tcprintf_s     _cprintf_s
#define _tcprintf_s_l   _cprintf_s_l
#define _tcprintf_p     _cprintf_p
#define _tcprintf_p_l   _cprintf_p_l
#define _vtcprintf      _vcprintf
#define _vtcprintf_l    _vcprintf_l
#define _vtcprintf_s    _vcprintf_s
#define _vtcprintf_s_l  _vcprintf_s_l
#define _vtcprintf_p    _vcprintf_p
#define _vtcprintf_p_l  _vcprintf_p_l
#define _ftprintf       fprintf
#define _ftprintf_l     _fprintf_l
#define _ftprintf_s     fprintf_s
#define _ftprintf_s_l   _fprintf_s_l
#define _ftprintf_p     _fprintf_p
#define _ftprintf_p_l   _fprintf_p_l
#define _stprintf       sprintf
#define _stprintf_l     _sprintf_l
#define _stprintf_s     sprintf_s
#define _stprintf_s_l   _sprintf_s_l
#define _stprintf_p     _sprintf_p
#define _stprintf_p_l   _sprintf_p_l
#define _sctprintf      _scprintf
#define _sctprintf_l    _scprintf_l
#define _sctprintf_p    _scprintf_p
#define _sctprintf_p_l  _scprintf_p_l
#define _sntprintf      _snprintf
#define _sntprintf_l    _snprintf_l
#define _sntprintf_s    _snprintf_s
#define _sntprintf_s_l  _snprintf_s_l
#define _vtprintf       vprintf
#define _vtprintf_l     _vprintf_l
#define _vtprintf_s     vprintf_s
#define _vtprintf_s_l   _vprintf_s_l
#define _vtprintf_p     _vprintf_p
#define _vtprintf_p_l   _vprintf_p_l
#define _vftprintf      vfprintf
#define _vftprintf_l    _vfprintf_l
#define _vftprintf_s    vfprintf_s
#define _vftprintf_s_l  _vfprintf_s_l
#define _vftprintf_p    _vfprintf_p
#define _vftprintf_p_l  _vfprintf_p_l
#define _vstprintf      vsprintf
#define _vstprintf_l    _vsprintf_l
#define _vstprintf_s    vsprintf_s
#define _vstprintf_s_l  _vsprintf_s_l
#define _vstprintf_p    _vsprintf_p
#define _vstprintf_p_l  _vsprintf_p_l
#define _vsctprintf     _vscprintf
#define _vsctprintf_l   _vscprintf_l
#define _vsctprintf_p   _vscprintf_p
#define _vsctprintf_p_l _vscprintf_p_l
#define _vsntprintf     _vsnprintf
#define _vsntprintf_l   _vsnprintf_l
#define _vsntprintf_s   _vsnprintf_s
#define _vsntprintf_s_l _vsnprintf_s_l

#define _tscanf         scanf
#define _tscanf_l       _scanf_l
#define _tscanf_s       scanf_s
#define _tscanf_s_l     _scanf_s_l
#define _tcscanf        _cscanf
#define _tcscanf_l      _cscanf_l
#define _tcscanf_s      _cscanf_s
#define _tcscanf_s_l    _cscanf_s_l
#define _ftscanf        fscanf
#define _ftscanf_l      _fscanf_l
#define _ftscanf_s      fscanf_s
#define _ftscanf_s_l    _fscanf_s_l
#define _stscanf        sscanf
#define _stscanf_l      _sscanf_l
#define _stscanf_s      sscanf_s
#define _stscanf_s_l    _sscanf_s_l
#define _sntscanf       _snscanf
#define _sntscanf_l     _snscanf_l
#define _sntscanf_s     _snscanf_s
#define _sntscanf_s_l   _snscanf_s_l


/* Unformatted i/o */

#define _fgettc         fgetc
#define _fgettc_nolock  _fgetc_nolock
#define _fgettchar      _fgetchar
#define _fgetts         fgets
#define _fputtc         fputc
#define _fputtc_nolock  _fputc_nolock
#define _fputtchar      _fputchar
#define _fputts         fputs
#define _cputts         _cputs
#define _gettc          getc
#define _gettc_nolock   _getc_nolock
#define _gettch         _getch
#define _gettch_nolock  _getch_nolock
#define _gettche        _getche
#define _gettche_nolock _getche_nolock
#define _gettchar       getchar
#define _gettchar_nolock _getchar_nolock
#define _getts          gets
#define _getts_s        gets_s
#define _cgetts         _cgets
#define _cgetts_s       _cgets_s
#define _puttc          putc
#define _puttc_nolock   _putc_nolock
#define _puttchar       putchar
#define _puttchar_nolock _putchar_nolock
#define _puttch         _putch
#define _puttch_nolock  _putch_nolock
#define _putts          puts
#define _ungettc        ungetc
#define _ungettc_nolock _ungetc_nolock
#define _ungettch       _ungetch
#define _ungettch_nolock _ungetch_nolock

/* String conversion functions */

#define _tcstod     strtod
#define _tcstol     strtol
#define _tcstoul    strtoul
#define _tstof      atof
#define _tstol      atol
#define _tstoi      atoi
#define _tstoi64    _atoi64
#define _tcstod_l     _strtod_l
#define _tcstol_l     _strtol_l
#define _tcstoul_l    _strtoul_l
#define _tstof_l      _atof_l
#define _tstol_l      _atol_l
#define _tstoi_l      _atoi_l
#define _tstoi64_l    _atoi64_l

#define _itot_s     _itoa_s
#define _ltot_s     _ltoa_s
#define _ultot_s    _ultoa_s
#define _itot       _itoa
#define _ltot       _ltoa
#define _ultot      _ultoa
#define _ttoi       atoi
#define _ttol       atol

#define _ttoi64     _atoi64
#define _tcstoi64   _strtoi64
#define _tcstoi64_l   _strtoi64_l
#define _tcstoui64  _strtoui64
#define _tcstoui64_l  _strtoui64_l
#define _i64tot_s   _i64toa_s
#define _ui64tot_s  _ui64toa_s
#define _i64tot     _i64toa
#define _ui64tot    _ui64toa

/* String functions */

/* Note that _mbscat, _mbscpy and _mbsdup are functionally equivalent to 
   strcat, strcpy and strdup, respectively. */

#define _tcscat     strcat
#define _tcscat_s   strcat_s
#define _tcscpy     strcpy
#define _tcscpy_s   strcpy_s
#define _tcsdup     _strdup
#define _tcslen     strlen
#define _tcsnlen    strnlen
#define _tcsxfrm    strxfrm
#define _tcsxfrm_l    _strxfrm_l
#define _tcserror   strerror
#define _tcserror_s   strerror_s
#define __tcserror  _strerror
#define __tcserror_s  _strerror_s

#ifdef _DEBUG
#define _tcsdup_dbg _strdup_dbg
#endif

/* Execute functions */

#define _texecl     _execl
#define _texecle    _execle
#define _texeclp    _execlp
#define _texeclpe   _execlpe
#define _texecv     _execv
#define _texecve    _execve
#define _texecvp    _execvp
#define _texecvpe   _execvpe

#define _tspawnl    _spawnl
#define _tspawnle   _spawnle
#define _tspawnlp   _spawnlp
#define _tspawnlpe  _spawnlpe
#define _tspawnv    _spawnv
#define _tspawnve   _spawnve
#define _tspawnvp   _spawnvp
#define _tspawnvpe  _spawnvpe

#define _tsystem    system


/* Time functions */

#define _tasctime   asctime
#define _tctime     ctime
#define _tctime32   _ctime32
#define _tctime64   _ctime64
#define _tstrdate   _strdate
#define _tstrtime   _strtime
#define _tutime     _utime
#define _tutime32   _utime32
#define _tutime64   _utime64
#define _tcsftime   strftime
#define _tcsftime_l _strftime_l

#define _tasctime_s   asctime_s
#define _tctime_s     ctime_s
#define _tctime32_s   _ctime32_s
#define _tctime64_s   _ctime64_s
#define _tstrdate_s   _strdate_s
#define _tstrtime_s   _strtime_s

/* Directory functions */

#define _tchdir             _chdir
#define _tgetcwd            _getcwd
#define _tgetdcwd           _getdcwd
#define _tgetdcwd_nolock    _getdcwd_nolock
#define _tmkdir             _mkdir
#define _trmdir             _rmdir

#ifdef _DEBUG
#define _tgetcwd_dbg        _getcwd_dbg
#define _tgetdcwd_dbg       _getdcwd_dbg
#define _tgetdcwd_lk_dbg    _getdcwd_lk_dbg
#endif

/* Environment/Path functions */

#define _tfullpath      _fullpath
#define _tgetenv        getenv
#define _tgetenv_s      getenv_s
#define _tdupenv_s      _dupenv_s
#define _tmakepath      _makepath
#define _tmakepath_s    _makepath_s
#define _tpgmptr        _pgmptr
#define _get_tpgmptr    _get_pgmptr
#define _tputenv        _putenv
#define _tputenv_s      _putenv_s
#define _tsearchenv     _searchenv
#define _tsearchenv_s   _searchenv_s
#define _tsplitpath     _splitpath
#define _tsplitpath_s   _splitpath_s

#ifdef _DEBUG
#define _tfullpath_dbg  _fullpath_dbg
#define _tdupenv_s_dbg  _dupenv_s_dbg
#endif

/* Stdio functions */

#define _tfdopen    _fdopen
#define _tfsopen    _fsopen
#define _tfopen     fopen
#define _tfopen_s   fopen_s
#define _tfreopen   freopen
#define _tfreopen_s freopen_s
#define _tperror    perror
#define _tpopen     _popen
#define _ttempnam   _tempnam
#define _ttmpnam    tmpnam
#define _ttmpnam_s  tmpnam_s

#ifdef _DEBUG
#define _ttempnam_dbg   _tempnam_dbg
#endif


/* Io functions */

#define _tchmod     _chmod
#define _tcreat     _creat
#define _tfindfirst      _findfirst
#define _tfindfirst32    _findfirst32
#define _tfindfirst64    _findfirst64
#define _tfindfirsti64   _findfirsti64
#define _tfindfirst32i64 _findfirst32i64
#define _tfindfirst64i32 _findfirst64i32
#define _tfindnext       _findnext
#define _tfindnext32     _findnext32
#define _tfindnext64     _findnext64
#define _tfindnexti64    _findnexti64
#define _tfindnext32i64  _findnext32i64
#define _tfindnext64i32  _findnext64i32
#define _tmktemp            _mktemp
#define _tmktemp_s          _mktemp_s

#define _topen      _open
#define _taccess    _access
#define _taccess_s  _access_s

#define _tremove    remove
#define _trename    rename
#define _tsopen     _sopen
#define _tsopen_s   _sopen_s
#define _tunlink    _unlink

#define _tfinddata_t      _finddata_t
#define _tfinddata32_t    _finddata32_t
#define _tfinddata64_t    __finddata64_t
#define _tfinddatai64_t   _finddatai64_t
#define _tfinddata32i64_t _finddata32i64_t
#define _tfinddata64i32_t _finddata64i32_t

/* ctype functions */
#define _istascii       __isascii
#define _istcntrl       iscntrl
#define _istcntrl_l     _iscntrl_l
#define _istxdigit      isxdigit
#define _istxdigit_l    _isxdigit_l

/* Stat functions */
#define _tstat      _stat
#define _tstat32    _stat32
#define _tstat32i64 _stat32i64
#define _tstat64    _stat64
#define _tstat64i32 _stat64i32
#define _tstati64   _stati64


/* Setlocale functions */

#define _tsetlocale setlocale



/* ++++++++++++++++++++ MBCS ++++++++++++++++++++ */

#ifdef  __cplusplus
}   /* ... extern "C" */
#endif

#include <mbstring.h>

#ifdef  __cplusplus
extern "C" {
#endif


#ifndef __TCHAR_DEFINED
typedef char            _TCHAR;
typedef signed char     _TSCHAR;
typedef unsigned char   _TUCHAR;
typedef unsigned char   _TXCHAR;
typedef unsigned int    _TINT;
#define __TCHAR_DEFINED
#endif

#ifndef _TCHAR_DEFINED
#if     !__STDC__
typedef char            TCHAR;
#endif
#define _TCHAR_DEFINED
#endif


#ifdef  _MB_MAP_DIRECT

/* use mb functions directly - types must match */

/* String functions */

#define _tcschr         _mbschr
#define _tcscspn        _mbscspn
#define _tcsncat        _mbsnbcat
#define _tcsncat_s      _mbsnbcat_s
#define _tcsncat_l      _mbsnbcat_l
#define _tcsncat_s_l    _mbsnbcat_s_l
#define _tcsncpy        _mbsnbcpy
#define _tcsncpy_s      _mbsnbcpy_s
#define _tcsncpy_l      _mbsnbcpy_l
#define _tcsncpy_s_l    _mbsnbcpy_s_l
#define _tcspbrk        _mbspbrk
#define _tcsrchr        _mbsrchr
#define _tcsspn         _mbsspn
#define _tcsstr         _mbsstr
#define _tcstok         _mbstok
#define _tcstok_s       _mbstok_s
#define _tcstok_l       _mbstok_l
#define _tcstok_s_l     _mbstok_s_l

#define _tcsnset        _mbsnbset
#define _tcsnset_l      _mbsnbset_l
#define _tcsnset_s      _mbsnbset_s
#define _tcsnset_s_l    _mbsnbset_s_l
#define _tcsrev         _mbsrev
#define _tcsset         _mbsset
#define _tcsset_s       _mbsset_s
#define _tcsset_l       _mbsset_l
#define _tcsset_s_l     _mbsset_s_l

#define _tcscmp         _mbscmp
#define _tcsicmp        _mbsicmp
#define _tcsicmp_l      _mbsicmp_l
#define _tcsnccmp       _mbsncmp
#define _tcsncmp        _mbsnbcmp
#define _tcsncicmp      _mbsnicmp
#define _tcsncicmp_l    _mbsnicmp_l
#define _tcsnicmp       _mbsnbicmp
#define _tcsnicmp_l     _mbsnbicmp_l

#define _tcscoll        _mbscoll
#define _tcscoll_l      _mbscoll_l
#define _tcsicoll       _mbsicoll
#define _tcsicoll_l     _mbsicoll_l
#define _tcsnccoll      _mbsncoll
#define _tcsnccoll_l    _mbsncoll_l
#define _tcsncoll       _mbsnbcoll
#define _tcsncoll_l     _mbsnbcoll_l
#define _tcsncicoll     _mbsnicoll
#define _tcsncicoll_l   _mbsnicoll_l
#define _tcsnicoll      _mbsnbicoll
#define _tcsnicoll_l    _mbsnbicoll_l

/* "logical-character" mappings */

#define _tcsclen        _mbslen
#define _tcscnlen       _mbsnlen
#define _tcsclen_l      _mbslen_l
#define _tcscnlen_l     _mbsnlen_l
#define _tcsnccat       _mbsncat
#define _tcsnccat_s     _mbsncat_s
#define _tcsnccat_l     _mbsncat_l
#define _tcsnccat_s_l   _mbsncat_s_l
#define _tcsnccpy       _mbsncpy
#define _tcsnccpy_s     _mbsncpy_s
#define _tcsnccpy_l     _mbsncpy_l
#define _tcsnccpy_s_l   _mbsncpy_s_l
#define _tcsncset       _mbsnset
#define _tcsncset_s     _mbsnset_s
#define _tcsncset_l     _mbsnset_l
#define _tcsncset_s_l   _mbsnset_s_l

/* MBCS-specific mappings */

#define _tcsdec     _mbsdec
#define _tcsinc     _mbsinc
#define _tcsnbcnt   _mbsnbcnt
#define _tcsnccnt   _mbsnccnt
#define _tcsnextc   _mbsnextc
#define _tcsninc    _mbsninc
#define _tcsspnp    _mbsspnp

#define _tcslwr     _mbslwr
#define _tcslwr_l   _mbslwr_l
#define _tcslwr_s   _mbslwr_s
#define _tcslwr_s_l _mbslwr_s_l
#define _tcsupr     _mbsupr
#define _tcsupr_l   _mbsupr_l
#define _tcsupr_s   _mbsupr_s
#define _tcsupr_s_l _mbsupr_s_l

#define _tclen      _mbclen
#define _tccpy      _mbccpy
#define _tccpy_l    _mbccpy_l
#define _tccpy_s    _mbccpy_s
#define _tccpy_s_l  _mbccpy_s_l

#else /* _MB_MAP_DIRECT */

#if     __STDC__ || defined(_NO_INLINING)

/* use type-safe linked-in function thunks */

/* String functions */

_CRTIMP __checkReturn _CONST_RETURN char * __cdecl _tcschr(__in_z const char * _Str, __in unsigned int _Val);
_CRTIMP __checkReturn size_t __cdecl _tcscspn(__in_z const char * _Str, __in_z const char * _Control);
_CRT_INSECURE_DEPRECATE(_tcsncat_s) _CRTIMP char * __cdecl _tcsncat(__in_z __out_ecount(_MaxCount) char *_Dst, __in_z const char *_Src, __in size_t _MaxCount);
_CRTIMP char * __cdecl _tcsncat_s(__inout_ecount(_DstSizeInChars) char *_Dst, __in size_t _DstSizeInChars, __in_z const char *_Src, size_t _MaxCount);
_CRT_INSECURE_DEPRECATE(_tcsncat_s_l) _CRTIMP char * __cdecl _tcsncat_l(__in_z __out_ecount(_MaxCount) char *_Dst, __in_z const char *_Src, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP char * __cdecl _tcsncat_s_l(__inout_ecount(_DstSizeInChars) char *_Dst, __in size_t _DstSizeInChars, __in_z const char *_Src, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRT_INSECURE_DEPRECATE(_tcsncpy_s) _CRTIMP char * __cdecl _tcsncpy(__out_ecount(_MaxCount) char *_Dst, __in_z const char *_Src, size_t _MaxCount);
_CRTIMP char * __cdecl _tcsncpy_s(__out_ecount(_DstSizeInChars) char *_Dst, __in size_t _DstSizeInChars, __in_z const char *_Src, size_t _MaxCount);
_CRT_INSECURE_DEPRECATE(_tcsncpy_s_l) _CRTIMP char * __cdecl _tcsncpy_l(__out_ecount(_MaxCount) char *_Dst, __in_z const char *_Src, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP char * __cdecl _tcsncpy_s_l(__out_ecount(_DstSizeInChars) char *_Dst, __in size_t _DstSizeInChars, __in_z const char *_Src, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn _CONST_RETURN char * __cdecl _tcspbrk(__in_z const char * _Str, __in_z const char * _Control);
_CRTIMP __checkReturn _CONST_RETURN char * __cdecl _tcsrchr(__in_z const char * _Str, __in unsigned int _Ch);
_CRTIMP __checkReturn size_t __cdecl _tcsspn(__in_z const char * _Str, __in_z const char * _Control);
_CRTIMP __checkReturn _CONST_RETURN char * __cdecl _tcsstr(__in_z const char * _Str, __in_z const char * _Substr);
_CRT_INSECURE_DEPRECATE(_tcstok_s) _CRTIMP __checkReturn char * __cdecl _tcstok(__inout_opt char *_Str, __in_z const char *_Delim);
_CRTIMP __checkReturn char * __cdecl _tcstok_s(__inout_opt char *_Str, __in_z const char *_Delim, __deref_inout_z_opt char **_Context);
_CRT_INSECURE_DEPRECATE(_tcstok_s_l) _CRTIMP __checkReturn char * __cdecl _tcstok_l(__inout_opt char *_Str, __in_z const char *_Delim, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn char * __cdecl _tcstok_s_l(__inout_opt char *_Str, __in_z const char *_Delim, __deref_inout_z_opt char **_Context, __in_opt _locale_t _Locale);

_CRT_INSECURE_DEPRECATE(_tcsnset_s) _CRTIMP char * __cdecl _tcsnset(__inout_z char * _Str, __in unsigned int _Val, __in size_t _MaxCount);
_CRTIMP __checkReturn_wat errno_t _tcsnset_s(__inout_bcount_z(_SizeInChars) char * _Str, __in size_t _SizeInChars, __in unsigned int _Val , __in size_t _MaxCount);
_CRT_INSECURE_DEPRECATE(_tcsnset_s_l) _CRTIMP char * __cdecl _tcsnset_l(__inout_z char * _Str, __in unsigned int _Val, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn_wat errno_t _tcsnset_s_l(__inout_bcount_z(_SizeInChars) char * _Str, __in size_t _SizeInChars, __in unsigned int _Val , __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP char * __cdecl _tcsrev(__inout_z char * _Str);
_CRT_INSECURE_DEPRECATE(_tcsset_s) _CRTIMP char * __cdecl _tcsset(__inout_z char * _Str, __in unsigned int _Val);
_CRT_INSECURE_DEPRECATE(_tcsset_s_l) _CRTIMP char * __cdecl _tcsset_l(__inout_z char * _Str, __in unsigned int _Val, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn_wat errno_t __cdecl _tcsset_s(__inout_ecount_z(_SizeInChars) char * _Str, __in size_t _SizeInChars, __in unsigned int _Val);
_CRTIMP __checkReturn_wat errno_t __cdecl _tcsset_s_l(__inout_ecount_z(_SizeInChars) char * _Str, __in size_t _SizeInChars, __in unsigned int, __in_opt _locale_t _Locale);

_CRTIMP __checkReturn int __cdecl _tcscmp(__in_z const char *_Str1, __in_z const char * _Str);
_CRTIMP __checkReturn int __cdecl _tcsicmp(__in_z const char *_Str1, __in_z const char *_Str2);
_CRTIMP __checkReturn int __cdecl _tcsicmp_l(__in_z const char *_Str1, __in_z const char *_Str2, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn int __cdecl _tcsnccmp(__in_z const char * _Str1, __in_z const char * _Str2, __in size_t _MaxCount);
_CRTIMP __checkReturn int __cdecl _tcsncmp(__in_z const char * _Str1, __in_z const char * _Str2, __in size_t _MaxCount);
_CRTIMP __checkReturn int __cdecl _tcsncicmp(__in_z const char * _Str1, __in_z const char * _Str2, __in size_t _MaxCount);
_CRTIMP __checkReturn int __cdecl _tcsncicmp_l(__in_z const char *_Str1, __in_z const char *_Str2, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn int __cdecl _tcsnicmp(__in_z const char * _Str1, __in_z const char * _Str2, __in size_t _MaxCount);
_CRTIMP __checkReturn int __cdecl _tcsnicmp_l(__in_z const char *_Str1, __in_z const char *_Str2, size_t _MaxCount, __in_opt _locale_t _Locale);

_CRTIMP __checkReturn int __cdecl _tcscoll(__in_z const char * _Str1, __in_z const char * _Str2);
_CRTIMP __checkReturn int __cdecl _tcscoll_l(__in_z const char *_Str1, __in_z const char *_Str2, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn int __cdecl _tcsicoll(__in_z const char * _Str1, __in_z const char * _Str2);
_CRTIMP __checkReturn int __cdecl _tcsicoll_l(__in_z const char *_Str1, __in_z const char *_Str2, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn int __cdecl _tcsnccoll(__in_z const char * _Str1, __in_z const char * _Str2, __in size_t _MaxCount);
_CRTIMP __checkReturn int __cdecl _tcsnccoll_l(__in_z const char *_Str1, __in_z const char *_Str2, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn int __cdecl _tcsncoll(__in_z const char *_Str1, __in_z const char * _Str2, __in size_t _MaxCount);
_CRTIMP __checkReturn int __cdecl _tcsncoll_l(__in_z const char *_Str1, __in_z const char *_Str2, size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn int __cdecl _tcsncicoll(__in_z const char * _Str1, __in_z const char * _Str2, __in size_t _MaxCount);
_CRTIMP __checkReturn int __cdecl _tcsncicoll_l(__in_z const char *_Str1, __in_z const char *_Str2, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn int __cdecl _tcsnicoll(__in_z const char * _Str1, __in_z const char * _Str2, __in size_t _MaxCount);
_CRTIMP __checkReturn int __cdecl _tcsnicoll_l(__in_z const char *_Str1, __in_z const char *_Str2, __in size_t _MaxCount, __in_opt _locale_t _Locale);

/* "logical-character" mappings */

_CRTIMP __checkReturn size_t __cdecl _tcsclen(__in_z const char *_Str);
_CRTIMP __checkReturn size_t __cdecl _tcscnlen(__in_z const char *_Str, __in size_t _MaxCount);
_CRTIMP __checkReturn size_t __cdecl _tcsclen_l(__in_z const char *_Str, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn size_t __cdecl _tcscnlen_l(__in_z const char *_Str, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRT_INSECURE_DEPRECATE(_tcsnccat_s) _CRTIMP char * __cdecl _tcsnccat(__inout char *_Dst, __in_z const char *_Src, __in size_t _MaxCount);
_CRTIMP char * __cdecl _tcsnccat_s(__inout_ecount(_DstSizeInChars) char *_Dst, __in size_t _DstSizeInChars, __in_z const char *_Src, __in size_t _MaxCount);
_CRT_INSECURE_DEPRECATE(_tcsnccat_s_l) _CRTIMP char * __cdecl _tcsnccat_l(__inout char *_Dst, __in_z const char *_Src, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP char * __cdecl _tcsnccat_s_l(__inout_ecount(_DstSizeInChars) char *_Dst, __in size_t _DstSizeInChars, __in_z const char *_Src, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRT_INSECURE_DEPRECATE(_tcsnccpy_s) _CRTIMP char * __cdecl _tcsnccpy(__out_ecount(_MaxCount) char *_Dst, __in_z const char *_Src, __in size_t _MaxCount);
_CRTIMP char * __cdecl _tcsnccpy_s(__out_ecount(_DstSizeInChars) char *_Dst, __in size_t _DstSizeInChars, __in_z const char *_Src, __in size_t _MaxCount);
_CRT_INSECURE_DEPRECATE(_tcsnccpy_s_l) _CRTIMP char * __cdecl _tcsnccpy_l(__out_ecount(_DstSizeInChars) char *_Dst, __in_z const char *_Src, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP char * __cdecl _tcsnccpy_s_l(__out_ecount(_DstSizeInChars) char *_Dst, __in size_t _DstSizeInChars, __in_z const char *_Src, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRT_INSECURE_DEPRECATE(_tcsncset_s) _CRTIMP char * __cdecl _tcsncset(__inout_ecount_z(_MaxCount) char * _Str, __in unsigned int _Val, __in size_t _MaxCount);
_CRTIMP char * __cdecl _tcsncset_s(__inout_ecount_z(_SizeInChars) char * _Str, __in size_t _SizeInChars, __in unsigned int _Val, __in size_t _MaxCount);
_CRT_INSECURE_DEPRECATE(_tcsncset_s_l) _CRTIMP char * __cdecl _tcsncset_l(__inout_ecount_z(_MaxCount) char * _Str, __in unsigned int _Val, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP char * __cdecl _tcsncset_s_l(__inout_ecount_z(_SizeInChars) char * _Str, __in size_t _SizeInChars, __in unsigned int _Val, __in size_t _MaxCount, __in_opt _locale_t _Locale);

/* MBCS-specific mappings */

_CRTIMP char * __cdecl _tcsdec(__in_ecount_z(_Pos-_Start+1) const char * _Start, __in_z const char * _Pos);
_CRTIMP char * __cdecl _tcsinc(__in_z const char * _Ptr);
_CRTIMP size_t __cdecl _tcsnbcnt(__in_ecount_z(_MaxCount) const char * _Str, __in size_t _MaxCount);
_CRTIMP size_t __cdecl _tcsnccnt(__in_ecount_z(_MaxCount) const char * _Str, __in size_t _MaxCount);
_CRTIMP unsigned int __cdecl _tcsnextc (__in_z const char * _Str);
_CRTIMP char * __cdecl _tcsninc(__in_ecount_z(_Count) const char * _Ptr, __in size_t _Count);
_CRTIMP char * __cdecl _tcsspnp(__in_z const char * _Str1, __in_z const char * _Str2);

_CRT_INSECURE_DEPRECATE(_tcslwr_s) _CRTIMP char * __cdecl _tcslwr(__inout char *_Str);
_CRT_INSECURE_DEPRECATE(_tcslwr_s_l) _CRTIMP char * __cdecl _tcslwr_l(__inout char *_Str, __in_opt _locale_t _Locale);
_CRTIMP char * __cdecl _tcslwr_s(__inout_ecount(_SizeInChars) char *_Str, __in size_t _SizeInChars);
_CRTIMP char * __cdecl _tcslwr_s_l(__inout_ecount(_SizeInChars) char *_Str, __in size_t _SizeInChars, __in_opt _locale_t _Locale);
_CRT_INSECURE_DEPRECATE(_tcsupr_s) _CRTIMP char * __cdecl _tcsupr(__inout char *_Str);
_CRT_INSECURE_DEPRECATE(_tcsupr_s_l) _CRTIMP char * __cdecl _tcsupr_l(__inout char *_Str, __in_opt _locale_t _Locale);
_CRTIMP char * __cdecl _tcsupr_s(__inout_ecount(_SizeInChars) char *_Str, __in size_t _SizeInChars);
_CRTIMP char * __cdecl _tcsupr_s_l(__inout_ecount(_SizeInChars) char *_Str, __in size_t _SizeInChars, __in_opt _locale_t _Locale);

_CRTIMP __checkReturn size_t __cdecl _tclen(__in_z const char * _Str);
_CRT_INSECURE_DEPRECATE(_tccpy_s) _CRTIMP void __cdecl _tccpy(__out_z char * _DstCh, __in_z const char * _SrcCh);
_CRT_INSECURE_DEPRECATE(_tccpy_s_l) _CRTIMP void __cdecl _tccpy_l(__out_z char * _DstCh, __in_z const char * _SrcCh, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn_wat errno_t __cdecl _tccpy_s(__out_bcount_z(_SizeInBytes) char * _DstCh, size_t _SizeInBytes, __out_opt int *_PCopied, __in_z const char * _SrcCh);
_CRTIMP __checkReturn_wat errno_t __cdecl _tccpy_s_l(__out_bcount_z(_SizeInBytes) char * _DstCh, size_t _SizeInBytes, __out_opt int *_PCopied, __in_z const char * _SrcCh, __in_opt _locale_t _Locale);

#else   /* __STDC__ */

/* the default: use type-safe inline function thunks */

#define _PUC    unsigned char *
#define _CPUC   const unsigned char *
#define _PC     char *
#define _CRPC   _CONST_RETURN char *
#define _CPC    const char *
#define _UI     unsigned int


/* String functions */

__inline _CRPC _tcschr(__in _CPC _s1,__in _UI _c) {return (_CRPC)_mbschr((_CPUC)_s1,_c);}
__inline size_t _tcscspn(__in _CPC _s1,__in _CPC _s2) {return _mbscspn((_CPUC)_s1,(_CPUC)_s2);}

__inline __checkReturn_wat errno_t _tcsncat_s(__inout_bcount_z(_Destination_size_chars) char *_Destination, __in size_t _Destination_size_chars, __in_z const char *_Source, __in size_t _Count) 
{
    return _mbsnbcat_s((unsigned char *)_Destination, _Destination_size_chars, (const unsigned char *)_Source,_Count);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _tcsncat_s, __inout_ecount_z(_Size) char, _Dest, __in_z const char *, _Source, __in size_t, _Count)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsncat, _tcsncat_s, __inout_ecount_z(_Size) char, __inout_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsnbcat((unsigned char *)_Dst,(const unsigned char *)_Source,_Count);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsncat, _tcsncat_s, __inout_ecount_z(_Size) char, __inout_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count)

__inline __checkReturn_wat errno_t _tcsncat_s_l(__inout_bcount_z(_Destination_size_chars) char *_Destination, __in size_t _Destination_size_chars, __in_z const char *_Source, __in size_t _Count, __in_opt _locale_t _Locale) 
{
    return _mbsnbcat_s_l((unsigned char *)_Destination, _Destination_size_chars, (const unsigned char *)_Source,_Count, _Locale);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(errno_t, _tcsncat_s_l, __inout_bcount_z(_Size) char, _Dest, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsncat_l, _tcsncat_s_l, __inout_bcount_z(_Size) char, __inout_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsnbcat_l((unsigned char *)_Dst,(const unsigned char *)_Source,_Count, _Locale);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsncat_l, _tcsncat_s_l, __inout_ecount_z(_Size) char, __inout_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

__inline __checkReturn_wat errno_t _tcsncpy_s(__out_bcount_z(_Destination_size_chars) char * _Destination, __in size_t _Destination_size_chars, __in_z const char * _Source,__in size_t _Count) 
{
    return _mbsnbcpy_s((unsigned char *)_Destination, _Destination_size_chars, (const unsigned char *)_Source,_Count);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _tcsncpy_s, __out_bcount_z(_Size) char, _Dest, __in_z const char *, _Source, __in size_t, _Count)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsncpy, _tcsncpy_s, __out_bcount_z(_Size) char, __inout_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsnbcpy((unsigned char *)_Dst,(const unsigned char *)_Source,_Count);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsncpy, _tcsncpy_s, __out_bcount_z(_Size) char, __inout_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count)

__inline __checkReturn_wat errno_t _tcsncpy_s_l(__out_bcount_z(_Destination_size_chars) char * _Destination, __in size_t _Destination_size_chars, __in_z const char * _Source,__in size_t _Count, __in_opt _locale_t _Locale) 
{
    return _mbsnbcpy_s_l((unsigned char *)_Destination, _Destination_size_chars, (const unsigned char *)_Source,_Count, _Locale);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(errno_t, _tcsncpy_s_l, __out_bcount_z(_Size) char, _Dest, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsncpy_l, _tcsncpy_s_l, __out_bcount(_Size) char, __out_bcount_z(_Count) char, _Dst, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsnbcpy_l((unsigned char *)_Dst,(const unsigned char *)_Source,_Count, _Locale);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsncpy_l, _tcsncpy_s_l, __out_bcount(_Size) char, __out_bcount_z(_Count) char, _Dst, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

__inline __checkReturn _CRPC _tcspbrk(__in _CPC _s1,__in _CPC _s2) {return (_CRPC)_mbspbrk((_CPUC)_s1,(_CPUC)_s2);}
__inline __checkReturn _CRPC _tcsrchr(__in _CPC _s1,__in _UI _c) {return (_CRPC)_mbsrchr((_CPUC)_s1,_c);}
__inline __checkReturn size_t _tcsspn(__in _CPC _s1,__in _CPC _s2) {return _mbsspn((_CPUC)_s1,(_CPUC)_s2);}
__inline __checkReturn _CRPC _tcsstr(__in _CPC _s1,__in _CPC _s2) {return (_CRPC)_mbsstr((_CPUC)_s1,(_CPUC)_s2);}

_CRT_INSECURE_DEPRECATE(_tcstok_s) __inline __checkReturn char *  _tcstok(__inout_z_opt char * _String,__in_z const char * _Delimiters) 
{
#pragma warning(push)
#pragma warning(disable:4996)
	return (char * )_mbstok((unsigned char *)_String,(const unsigned char *)_Delimiters);
#pragma warning(pop)
}

__inline __checkReturn char *  _tcstok_s(__inout_z_opt char * _String,__in_z const char * _Delimiters, __deref_inout_z_opt char **_Current_position) 
{
	return (char * )_mbstok_s((unsigned char *)_String,(const unsigned char *)_Delimiters, (unsigned char **)_Current_position);
}

_CRT_INSECURE_DEPRECATE(_tcstok_s_l) __inline __checkReturn char *  _tcstok_l(__inout_z_opt char * _String,__in_z const char * _Delimiters, __in_opt _locale_t _Locale) 
{
#pragma warning(push)
#pragma warning(disable:4996)
	return (char * )_mbstok_l((unsigned char *)_String,(const unsigned char *)_Delimiters, _Locale);
#pragma warning(pop)
}

__inline __checkReturn char *  _tcstok_s_l(__inout_z_opt char * _String,__in_z const char * _Delimiters, __deref_inout_z_opt char **_Current_position, __in_opt _locale_t _Locale) 
{
	return (char * )_mbstok_s_l((unsigned char *)_String,(const unsigned char *)_Delimiters, (unsigned char **)_Current_position, _Locale);
}

__inline __checkReturn_wat errno_t _tcsnset_s(__inout_bcount_z(_SizeInBytes) char * _Dst, __in size_t _SizeInBytes, __in unsigned int _Value , __in size_t _Count)
{
    return _mbsnbset_s((unsigned char *)_Dst, _SizeInBytes, _Value, _Count);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _tcsnset_s, __inout_bcount_z(_Size) char, _Dest, __in unsigned int, _Value , __in size_t, _Count)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsnset, _tcsnset_s, __inout_bcount_z(_Size) char, __inout_bcount_z(_Count) char, _Dst, __in unsigned int, _Value , __in size_t, _Count)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsnbset((unsigned char *)_Dst, _Value, _Count);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsnset, _tcsnset_s, __inout_bcount_z(_Size) char, __inout_bcount_z(_Count) char, _Dst, __in unsigned int, _Value , __in size_t, _Count)

__inline __checkReturn_wat errno_t _tcsnset_s_l(__inout_bcount_z(_SizeInBytes) char * _Dst, __in size_t _SizeInBytes, __in unsigned int _Value , __in size_t _Count, __in_opt _locale_t _Locale)
{
    return _mbsnbset_s_l((unsigned char *)_Dst, _SizeInBytes, _Value, _Count, _Locale);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(errno_t, _tcsnset_s_l, __inout_bcount_z(_Size) char, _Dest, __in unsigned int, _Value , __in size_t, _Count, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsnset_l, _tcsnset_s_l, __inout_bcount_z(_Size) char, __inout_bcount_z(_Count) char, _Dst, __in unsigned int, _Value , __in size_t, _Count, __in_opt _locale_t, _Locale)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsnbset_l((unsigned char *)_Dst, _Value, _Count, _Locale);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsnset_l, _tcsnset_s_l, __inout_bcount_z(_Size) char, __inout_bcount_z(_Count) char, _Dst, __in unsigned int, _Value , __in size_t, _Count, __in_opt _locale_t, _Locale)

__inline _PC _tcsrev(__inout _PC _s1) {return (_PC)_mbsrev((_PUC)_s1);}

__inline __checkReturn_wat errno_t _tcsset_s(__inout_bcount_z(_SizeInBytes) char * _Dst, __in size_t _SizeInBytes, __in unsigned int _Value)
{
    return _mbsset_s((unsigned char *)_Dst, _SizeInBytes, _Value);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _tcsset_s, __inout_bcount_z(_Size) char, _Dest, __in unsigned int, _Value)

__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(char *, __RETURN_POLICY_DST, _tcsset, _tcsset_s, __inout_bcount_z(_Size) char, __inout_z char, _Dst, __in unsigned int, _Value)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsset((unsigned char *)_Dst, _Value);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(char *, __RETURN_POLICY_DST, _tcsset, _tcsset_s, __inout_bcount_z(_Size) char, __inout_z char, _Dst, __in unsigned int, _Value)

__inline __checkReturn_wat errno_t _tcsset_s_l(__inout_bcount_z(_SizeInBytes) char * _Dst, __in size_t _SizeInBytes, __in unsigned int _Value, __in_opt _locale_t _Locale)
{
    return _mbsset_s_l((unsigned char *)_Dst, _SizeInBytes, _Value, _Locale);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _tcsset_s_l, __inout_bcount_z(_Size) char, _Dest, __in unsigned int, _Value, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsset_l, _tcsset_s_l, __inout_bcount_z(_Size) char, __inout_z char, _Dst, __in unsigned int, _Value, __in_opt _locale_t, _Locale)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsset_l((unsigned char *)_Dst, _Value, _Locale);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsset_l, _tcsset_s_l, __inout_bcount_z(_Size) char, __inout_z char, _Dst, __in unsigned int, _Value, __in_opt _locale_t, _Locale)

__inline __checkReturn int _tcscmp(__in _CPC _s1,__in _CPC _s2) {return _mbscmp((_CPUC)_s1,(_CPUC)_s2);}

__inline __checkReturn int _tcsicmp(__in_z const char * _String1, __in_z const char * _String2) 
{
    return _mbsicmp((const unsigned char *)_String1,(const unsigned char *)_String2);
}

__inline __checkReturn int _tcsicmp_l(__in_z const char * _String1, __in_z const char * _String2, __in_opt _locale_t _Locale) 
{
    return _mbsicmp_l((const unsigned char *)_String1,(const unsigned char *)_String2, _Locale);
}

__inline __checkReturn int _tcsnccmp(__in _CPC _s1,__in _CPC _s2,__in size_t _n) {return _mbsncmp((_CPUC)_s1,(_CPUC)_s2,_n);}
__inline int _tcsncmp(__in _CPC _s1,__in _CPC _s2,__in size_t _n) {return _mbsnbcmp((_CPUC)_s1,(_CPUC)_s2,_n);}

__inline __checkReturn int _tcsncicmp(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Char_count)
{
    return _mbsnicmp((const unsigned char *)_String1,(const unsigned char *)_String2,_Char_count);
}

__inline __checkReturn int _tcsncicmp_l(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Char_count, __in_opt _locale_t _Locale)
{
    return _mbsnicmp_l((const unsigned char *)_String1,(const unsigned char *)_String2,_Char_count, _Locale);
}

__inline __checkReturn int _tcsnicmp(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Char_count) 
{
    return _mbsnbicmp((const unsigned char *)_String1,(const unsigned char *)_String2,_Char_count);
}

__inline __checkReturn int _tcsnicmp_l(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Char_count, __in_opt _locale_t _Locale) 
{
    return _mbsnbicmp_l((const unsigned char *)_String1,(const unsigned char *)_String2,_Char_count, _Locale);
}

__inline __checkReturn int _tcscoll(__in_z const char * _String1, __in_z const char * _String2)
{
    return _mbscoll((const unsigned char *)_String1,(const unsigned char *)_String2);
}

__inline __checkReturn int _tcscoll_l(__in_z const char * _String1, __in_z const char * _String2, __in_opt _locale_t _Locale)
{
    return _mbscoll_l((const unsigned char *)_String1,(const unsigned char *)_String2, _Locale);
}

__inline __checkReturn int _tcsicoll(__in_z const char * _String1, __in_z const char * _String2)
{
    return _mbsicoll((const unsigned char *)_String1,(const unsigned char *)_String2);
}

__inline __checkReturn int _tcsicoll_l(__in_z const char * _String1, __in_z const char * _String2, __in_opt _locale_t _Locale)
{
    return _mbsicoll_l((const unsigned char *)_String1,(const unsigned char *)_String2, _Locale);
}

__inline __checkReturn int _tcsnccoll(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Count)
{
    return _mbsncoll((const unsigned char *)_String1,(const unsigned char *)_String2, _Count);
}

__inline __checkReturn int _tcsnccoll_l(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Count, __in_opt _locale_t _Locale)
{
    return _mbsncoll_l((const unsigned char *)_String1,(const unsigned char *)_String2, _Count, _Locale);
}

__inline __checkReturn int _tcsncoll(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Count)
{
    return _mbsnbcoll((const unsigned char *)_String1,(const unsigned char *)_String2, _Count);
}

__inline __checkReturn int _tcsncoll_l(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Count, __in_opt _locale_t _Locale)
{
    return _mbsnbcoll_l((const unsigned char *)_String1,(const unsigned char *)_String2, _Count, _Locale);
}

__inline __checkReturn int _tcsncicoll(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Count)
{
    return _mbsnicoll((const unsigned char *)_String1,(const unsigned char *)_String2, _Count);
}

__inline __checkReturn int _tcsncicoll_l(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Count, __in_opt _locale_t _Locale)
{
    return _mbsnicoll_l((const unsigned char *)_String1,(const unsigned char *)_String2, _Count, _Locale);
}

__inline __checkReturn int _tcsnicoll(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Count)
{
    return _mbsnbicoll((const unsigned char *)_String1,(const unsigned char *)_String2, _Count);
}

__inline __checkReturn int _tcsnicoll_l(__in_z const char * _String1, __in_z const char * _String2, __in size_t _Count, __in_opt _locale_t _Locale)
{
    return _mbsnbicoll_l((const unsigned char *)_String1,(const unsigned char *)_String2, _Count, _Locale);
}

/* "logical-character" mappings */
__inline __checkReturn size_t _tcsclen(__in_z const char * _String) 
{
    return _mbslen((const unsigned char *)_String);
}

__inline __checkReturn size_t _tcscnlen(__in_z const char * _String, __in size_t _Maximum) 
{
    return _mbsnlen((const unsigned char *)_String, _Maximum);
}

__inline __checkReturn size_t _tcsclen_l(__in_z const char * _String, __in_opt _locale_t _Locale) 
{
    return _mbslen_l((const unsigned char *)_String, _Locale);
}

__inline __checkReturn size_t _tcscnlen_l(__in_z const char * _String, __in size_t _Maximum, __in_opt _locale_t _Locale) 
{
    return _mbsnlen_l((const unsigned char *)_String, _Maximum, _Locale);
}

__inline __checkReturn_wat errno_t _tcsnccat_s(__inout_bcount_z(_Destination_size_chars) char * _Destination, __in size_t _Destination_size_chars, __in_z const char * _Source, __in size_t _Count) 
{
    return _mbsncat_s((unsigned char *)_Destination, _Destination_size_chars, (const unsigned char *)_Source, _Count);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _tcsnccat_s, __inout_bcount_z(_Size) char, _Dest, __in_z const char *, _Source, __in size_t, _Count)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsnccat, _tcsnccat_s, __inout_bcount_z(_Size) char, __inout_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsncat((unsigned char *)_Dst,(const unsigned char *)_Source, _Count);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsnccat, _tcsnccat_s, __inout_bcount_z(_Size) char, __inout_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count)

__inline __checkReturn_wat errno_t _tcsnccat_s_l(__inout_bcount_z(_Destination_size_chars) char * _Destination, __in size_t _Destination_size_chars, __in_z const char * _Source, __in size_t _Count, __in_opt _locale_t _Locale) 
{
    return _mbsncat_s_l((unsigned char *)_Destination, _Destination_size_chars, (const unsigned char *)_Source, _Count, _Locale);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(errno_t, _tcsnccat_s_l, __inout_bcount_z(_Size) char, _Dest, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsnccat_l, _tcsnccat_s_l, __inout_bcount_z(_Size) char, __inout_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsncat_l((unsigned char *)_Dst,(const unsigned char *)_Source, _Count, _Locale);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsnccat_l, _tcsnccat_s_l, __inout_bcount_z(_Size) char, __inout_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

__inline __checkReturn_wat errno_t _tcsnccpy_s(__out_bcount_z(_Destination_size_chars) char * _Destination, __in size_t _Destination_size_chars, __in_z const char * _Source, __in size_t _Count) 
{
    return _mbsncpy_s((unsigned char *)_Destination, _Destination_size_chars, (const unsigned char *)_Source, _Count);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _tcsnccpy_s, __out_bcount_z(_Size) char, _Dest, __in_z const char *, _Source, __in size_t, _Count)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsnccpy, _tcsnccpy_s, __out_bcount_z(_Size) char, __out_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsncpy((unsigned char *)_Dst,(const unsigned char *)_Source, _Count);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsnccpy, _tcsnccpy_s, __out_bcount_z(_Size) char, __out_z char, _Dst, __in_z const char *, _Source, __in size_t, _Count)

__inline __checkReturn_wat errno_t _tcsnccpy_s_l(__out_bcount_z(_Destination_size_chars) char * _Destination, __in size_t _Destination_size_chars, __in_z const char * _Source, __in size_t _Count, __in_opt _locale_t _Locale) 
{
    return _mbsncpy_s_l((unsigned char *)_Destination, _Destination_size_chars, (const unsigned char *)_Source, _Count, _Locale);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(errno_t, _tcsnccpy_s_l, __out_bcount_z(_Size) char, _Dest, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsnccpy_l, _tcsnccpy_s_l, __out_bcount_z(_Size) char, __out_bcount_z(_Count) char, _Dst, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsncpy_l((unsigned char *)_Dst,(const unsigned char *)_Source, _Count, _Locale);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsnccpy_l, _tcsnccpy_s_l, __out_bcount_z(_Size) char, __out_bcount_z(_Count) char, _Dst, __in_z const char *, _Source, __in size_t, _Count, __in_opt _locale_t, _Locale)

__inline __checkReturn_wat errno_t _tcsncset_s(__inout_bcount(_SizeInBytes) char *_Destination, __in size_t _SizeInBytes, __in unsigned int _Value, __in size_t _Count)
{
    return _mbsnset_s((unsigned char *)_Destination, _SizeInBytes, _Value, _Count);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _tcsncset_s, __inout_bcount(_Size) char, _Dest, __in unsigned int, _Value, __in size_t, _Count)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsncset, _tcsncset_s, __inout_bcount_z(_Size) char, __inout_bcount(_Count) char, _Dst, __in unsigned int, _Value, __in size_t, _Count)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsnset((unsigned char *)_Dst, _Value, _Count);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(char *, __RETURN_POLICY_DST, _tcsncset, _tcsncset_s, __out_bcount_z(_Size) char, __inout_bcount(_Count) char, _Dst, __in unsigned int, _Value, __in size_t, _Count)

__inline __checkReturn_wat errno_t _tcsncset_s_l(__inout_bcount(_SizeInBytes) char *_Destination, __in size_t _SizeInBytes, __in unsigned int _Value, __in size_t _Count, __in_opt _locale_t _Locale)
{
    return _mbsnset_s_l((unsigned char *)_Destination, _SizeInBytes, _Value, _Count, _Locale);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(errno_t, _tcsncset_s_l, __inout_bcount(_Size) char, _Dest, __in unsigned int, _Value, __in size_t, _Count, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsncset_l, _tcsncset_s_l, __inout_bcount_z(_Size) char, __inout_bcount(_Count) char, _Dst, __in unsigned int, _Value, __in size_t, _Count, __in_opt _locale_t, _Locale)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsnset_l((unsigned char *)_Dst, _Value, _Count, _Locale);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(char *, __RETURN_POLICY_DST, _tcsncset_l, _tcsncset_s_l, __inout_bcount_z(_Size) char, __inout_bcount(_Count) char, _Dst, __in unsigned int, _Value, __in size_t, _Count, __in_opt _locale_t, _Locale)

/* MBCS-specific mappings */

__inline __checkReturn _PC _tcsdec(__in _CPC _s1,__in _CPC _s2) {return (_PC)_mbsdec((_CPUC)_s1,(_CPUC)_s2);}
__inline __checkReturn _PC _tcsinc(__in _CPC _s1) {return (_PC)_mbsinc((_CPUC)_s1);}
__inline __checkReturn size_t _tcsnbcnt(__in _CPC _s1,__in size_t _n) {return _mbsnbcnt((_CPUC)_s1,_n);}
__inline __checkReturn size_t _tcsnccnt(__in _CPC _s1,__in size_t _n) {return _mbsnccnt((_CPUC)_s1,_n);}
__inline __checkReturn _PC _tcsninc(__in _CPC _s1,__in size_t _n) {return (_PC)_mbsninc((_CPUC)_s1,_n);}
__inline __checkReturn _PC _tcsspnp(__in _CPC _s1,__in _CPC _s2) {return (_PC)_mbsspnp((_CPUC)_s1,(_CPUC)_s2);}

__inline __checkReturn_wat errno_t _tcslwr_s(__inout_bcount_z(_SizeInBytes) char * _String, size_t _SizeInBytes) 
{
    return _mbslwr_s((unsigned char *)_String, _SizeInBytes);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(errno_t, _tcslwr_s, __inout_bcount_z(_Size) char, _String)

__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(char *, __RETURN_POLICY_DST, _tcslwr, _tcslwr_s, __inout_bcount_z(_Size) char, __inout_z char, _String)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbslwr((unsigned char *)_String);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(char *, __RETURN_POLICY_DST, _tcslwr, _tcslwr_s, __inout_bcount_z(_Size) char, __inout_z char, _String)

__inline __checkReturn_wat errno_t _tcslwr_s_l(__inout_bcount_z(_SizeInBytes) char * _String, __in size_t _SizeInBytes, __in_opt _locale_t _Locale) 
{
    return _mbslwr_s_l((unsigned char *)_String, _SizeInBytes, _Locale);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _tcslwr_s_l, __inout_bcount_z(_Size) char, _String, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(char *, __RETURN_POLICY_DST, _tcslwr_l, _tcslwr_s_l, __inout_bcount_z(_Size) char, __inout_z char, _String, __in_opt _locale_t, _Locale)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbslwr_l((unsigned char *)_String, _Locale);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(char *, __RETURN_POLICY_DST, _tcslwr_l, _tcslwr_s_l, __inout_bcount_z(_Size) char, __inout_z char, _String, __in_opt _locale_t, _Locale)

__inline __checkReturn_wat errno_t _tcsupr_s(__inout_bcount_z(_Count) char * _String, __in size_t _Count) 
{
    return _mbsupr_s((unsigned char *)_String, _Count);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(errno_t, _tcsupr_s, __inout_bcount_z(_Size) char, _String)

__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(char *, __RETURN_POLICY_DST, _tcsupr, _tcsupr_s, __inout_bcount_z(_Size) char, __inout_z char, _String)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsupr((unsigned char *)_String);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(char *, __RETURN_POLICY_DST, _tcsupr, _tcsupr_s, __inout_bcount_z(_Size) char, __inout_z char, _String)

__inline __checkReturn_wat errno_t _tcsupr_s_l(__inout_bcount_z(_Count) char * _String, __in size_t _Count, __in_opt _locale_t _Locale) 
{
    return _mbsupr_s_l((unsigned char *)_String, _Count, _Locale);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _tcsupr_s_l, __inout_bcount_z(_Size) char, _String, __in_opt _locale_t, _Locale)

__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(char *, __RETURN_POLICY_DST, _tcsupr_l, _tcsupr_s_l, __inout_bcount_z(_Size) char, __inout_z char, _String, __in_opt _locale_t, _Locale)
{
#pragma warning(push)
#pragma warning(disable:4996)
    return (char *)_mbsupr_l((unsigned char *)_String, _Locale);
#pragma warning(pop)
}

__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(char *, __RETURN_POLICY_DST, _tcsupr_l, _tcsupr_s_l, __inout_bcount_z(_Size) char, __inout_z char, _String, __in_opt _locale_t, _Locale)

__inline __checkReturn size_t _tclen(__in_z _CPC _s1) {return _mbclen((_CPUC)_s1);}

__inline __checkReturn_wat errno_t _tccpy_s(__out_bcount_z(_SizeInBytes) char * _Destination, size_t _SizeInBytes, __out_opt int *_PCopied, __in_z const char * _Source) 
{
    return _mbccpy_s((unsigned char *)_Destination, _SizeInBytes, _PCopied, (const unsigned char *)_Source);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _tccpy_s, __out_bcount_z(_SizeInBytes) char, _Dest, __out_opt  int *, _PCopied, __in_z const char *, _Source)

_CRT_INSECURE_DEPRECATE(_tccpy_s) __inline void _tccpy(__out_bcount_z(2) char * _Destination, __in_z const char * _Source) 
{
#pragma warning(push)
#pragma warning(disable:4996)
    _mbccpy((unsigned char *)_Destination, (const unsigned char *)_Source);
#pragma warning(pop)
}

__inline __checkReturn_wat errno_t _tccpy_s_l(__out_bcount_z(_SizeInBytes) char * _Destination, __in size_t _SizeInBytes, __out_opt int *_PCopied, __in_z const char * _Source, __in_opt _locale_t _Locale) 
{
    return _mbccpy_s_l((unsigned char *)_Destination, _SizeInBytes, _PCopied, (const unsigned char *)_Source, _Locale);
}

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(errno_t, _tccpy_s_l, __out_bcount_z(_Size) char, _Dest, __out_opt int *, _PCopied, __in_z const char *, _Source, __in_opt _locale_t, _Locale)

_CRT_INSECURE_DEPRECATE(_tccpy_s_l) __inline void _tccpy_l(__out_bcount_z(2) char * _Destination, __in_z const char * _Source, __in_opt _locale_t _Locale) 
{
#pragma warning(push)
#pragma warning(disable:4996)
    _mbccpy_l((unsigned char *)_Destination,( const unsigned char *)_Source, _Locale);
#pragma warning(pop)
}

/* inline helper */
__inline __checkReturn _UI _tcsnextc(__in_z _CPC _s1)
{
    _UI _n=0; 
    if (_ismbblead((_UI)*(_PUC)_s1)) 
    {
        /*  for a dud MBCS string (leadbyte, EOS), we don't move forward 2
            We do not assert here because this routine is too low-level
        */
        if(_s1[1]!='\0')
        {
            _n=((_UI)*(_PUC)_s1)<<8; 
            _s1++;
        }
    } 
    _n+=(_UI)*(_PUC)_s1; 
    
    return(_n);
}

#endif  /* __STDC__ */

#ifdef  __cplusplus
#ifndef _CPP_TCHAR_INLINES_DEFINED
#define _CPP_TCHAR_INLINES_DEFINED
extern "C++" {
inline __checkReturn char * __CRTDECL _tcschr(__in_z char *_S, __in unsigned int _C)
        {return ((char *)_tcschr((const char *)_S, _C)); }
inline __checkReturn char * __CRTDECL _tcspbrk(__in_z char *_S, __in_z const char *_P)
        {return ((char *)_tcspbrk((const char *)_S, _P)); }
inline __checkReturn char * __CRTDECL _tcsrchr(__in_z char *_S, __in unsigned int _C)
        {return ((char *)_tcsrchr((const char *)_S, _C)); }
inline __checkReturn char * __CRTDECL _tcsstr(__in_z char *_S, __in_z const char *_P)
        {return ((char *)_tcsstr((const char *)_S, _P)); }
}
#endif
#endif  /* __cplusplus */

#endif  /* _MB_MAP_DIRECT */


/* MBCS-specific mappings */

#define _tccmp(_cp1,_cp2)   _tcsnccmp(_cp1,_cp2,1)


/* ctype functions */

#define _istalnum       _ismbcalnum
#define _istalnum_l     _ismbcalnum_l
#define _istalpha       _ismbcalpha
#define _istalpha_l     _ismbcalpha_l
#define _istdigit       _ismbcdigit
#define _istdigit_l     _ismbcdigit_l
#define _istgraph       _ismbcgraph
#define _istgraph_l     _ismbcgraph_l
#define _istlegal       _ismbclegal
#define _istlegal_l     _ismbclegal_l
#define _istlower       _ismbclower
#define _istlower_l     _ismbclower_l
#define _istprint       _ismbcprint
#define _istprint_l     _ismbcprint_l
#define _istpunct       _ismbcpunct
#define _istpunct_l     _ismbcpunct_l
#define _istspace       _ismbcspace
#define _istspace_l     _ismbcspace_l
#define _istupper       _ismbcupper
#define _istupper_l     _ismbcupper_l

#define _totupper       _mbctoupper
#define _totupper_l     _mbctoupper_l
#define _totlower       _mbctolower
#define _totlower_l     _mbctolower_l

#define _istlead        _ismbblead
#define _istleadbyte    isleadbyte
#define _istleadbyte_l  _isleadbyte_l



#endif  /* _UNICODE */


/* Generic text macros to be used with string literals and character constants.
   Will also allow symbolic constants that resolve to same. */

#define _T(x)       __T(x)
#define _TEXT(x)    __T(x)


#ifdef  __cplusplus
}   /* ... extern "C" */
#endif

#endif  /* _INC_TCHAR */

