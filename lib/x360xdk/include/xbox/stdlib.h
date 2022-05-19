/***
*stdlib.h - declarations/definitions for commonly used library functions
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This include file contains the function declarations for commonly
*       used library functions which either don't fit somewhere else, or,
*       cannot be declared in the normal place for other reasons.
*       [ANSI]
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _INC_STDLIB
#define _INC_STDLIB

#include <crtdefs.h>
#include <limits.h>

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

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/* Definition of the argument values for the exit() function */

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1


#ifndef _ONEXIT_T_DEFINED

typedef int (__cdecl * _onexit_t)(void);


#if     !__STDC__
/* Non-ANSI name for compatibility */
#define onexit_t _onexit_t
#endif

#define _ONEXIT_T_DEFINED
#endif


/* Data structure definitions for div and ldiv runtimes. */

#ifndef _DIV_T_DEFINED

typedef struct _div_t {
        int quot;
        int rem;
} div_t;

typedef struct _ldiv_t {
        long quot;
        long rem;
} ldiv_t;

#define _DIV_T_DEFINED
#endif

/*
 * structs used to fool the compiler into not generating floating point
 * instructions when copying and pushing [long] double values
 */

#ifndef _CRT_DOUBLE_DEC

#ifndef _LDSUPPORT

#pragma pack(4)
typedef struct {
    unsigned char ld[10];
} _LDOUBLE;
#pragma pack()

#define _PTR_LD(x) ((unsigned char  *)(&(x)->ld))

#else

/* push and pop long, which is #defined as __int64 by a spec2k test */
#pragma push_macro("long")
#undef long
typedef long double _LDOUBLE;
#pragma pop_macro("long")

#define _PTR_LD(x) ((unsigned char  *)(x))

#endif

typedef struct {
        double x;
} _CRT_DOUBLE;

typedef struct {
    float f;
} _CRT_FLOAT;

/* push and pop long, which is #defined as __int64 by a spec2k test */
#pragma push_macro("long")
#undef long

typedef struct {
        /*
         * Assume there is a long double type
         */
        long double x;
} _LONGDOUBLE;

#pragma pop_macro("long")

#pragma pack(4)
typedef struct {
    unsigned char ld12[12];
} _LDBL12;
#pragma pack()

#define _CRT_DOUBLE_DEC
#endif

/* Maximum value that can be returned by the rand function. */

#define RAND_MAX 0x7fff

/*
 * Maximum number of bytes in multi-byte character in the current locale
 * (also defined in ctype.h).
 */
#ifndef MB_CUR_MAX
#define MB_CUR_MAX ___mb_cur_max_func()
_CRTIMP extern int __mb_cur_max;
_CRTIMP int __cdecl ___mb_cur_max_func(void);
_CRTIMP int __cdecl ___mb_cur_max_l_func(_locale_t);
#endif  /* MB_CUR_MAX */

/* Minimum and maximum macros */

#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))

/*
 * Sizes for buffers used by the _makepath() and _splitpath() functions.
 * note that the sizes include space for 0-terminator
 */
#define _MAX_PATH   260 /* max. length of full pathname */
#define _MAX_DRIVE  3   /* max. length of drive component */
#define _MAX_DIR    256 /* max. length of path component */
#define _MAX_FNAME  256 /* max. length of file name component */
#define _MAX_EXT    256 /* max. length of extension component */

/*
 * Argument values for _set_error_mode().
 */
#define _OUT_TO_DEFAULT 0
#define _OUT_TO_STDERR  1
#define _OUT_TO_MSGBOX  2
#define _REPORT_ERRMODE 3

/*
 * Argument values for _set_abort_behavior().
 */
#define _WRITE_ABORT_MSG    0x1
#define _CALL_REPORTFAULT   0x2

/*
 * Sizes for buffers used by the getenv/putenv family of functions.
 */
#define _MAX_ENV 32767   

/* a purecall handler procedure. Never returns normally */
typedef void (__cdecl *_purecall_handler)(void); 

/* establishes a purecall handler for the process */
_CRTIMP _purecall_handler __cdecl _set_purecall_handler(__in_opt _purecall_handler _Handler);
_CRTIMP _purecall_handler __cdecl _get_purecall_handler();

#if defined(__cplusplus)
extern "C++"
{

}
#endif

/* a invalid_arg handler procedure. */
typedef void (__cdecl *_invalid_parameter_handler)(const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t); 

/* establishes a invalid_arg handler for the process */
_CRTIMP _invalid_parameter_handler __cdecl _set_invalid_parameter_handler(__in_opt _invalid_parameter_handler _Handler);
_CRTIMP _invalid_parameter_handler __cdecl _get_invalid_parameter_handler(void);

#if defined(__cplusplus)
extern "C++"
{

}
#endif

/* External variable declarations */
#ifndef _CRT_ERRNO_DEFINED
#define _CRT_ERRNO_DEFINED
_CRTIMP extern int * __cdecl _errno(void);
#define errno   (*_errno())

errno_t __cdecl _set_errno(__in int _Value);
errno_t __cdecl _get_errno(__out int * _Value);
#endif

_CRTIMP unsigned long * __cdecl __doserrno(void);
#define _doserrno   (*__doserrno())

errno_t __cdecl _set_doserrno(__in unsigned long _Value);
errno_t __cdecl _get_doserrno(__out unsigned long * _Value);

/* you can't modify this, but it is non-const for backcompat */
_CRTIMP _CRT_INSECURE_DEPRECATE(strerror) char ** __cdecl __sys_errlist(void);
#define _sys_errlist (__sys_errlist())

_CRTIMP _CRT_INSECURE_DEPRECATE(strerror) int * __cdecl __sys_nerr(void);
#define _sys_nerr (*__sys_nerr())


_CRTIMP extern int __argc;          /* count of cmd line args */
_CRTIMP extern char ** __argv;      /* pointer to table of cmd line args */
_CRTIMP extern wchar_t ** __wargv;  /* pointer to table of wide cmd line args */

_CRTIMP extern char ** _environ;    /* pointer to environment table */
_CRTIMP extern wchar_t ** _wenviron;    /* pointer to wide environment table */

_CRT_INSECURE_DEPRECATE_GLOBALS(_get_pgmptr) _CRTIMP extern char * _pgmptr;      /* points to the module (EXE) name */
_CRT_INSECURE_DEPRECATE_GLOBALS(_get_wpgmptr) _CRTIMP extern wchar_t * _wpgmptr;  /* points to the module (EXE) wide name */



errno_t __cdecl _get_pgmptr(__deref_out_z char ** _Value);
errno_t __cdecl _get_wpgmptr(__deref_out_z wchar_t ** _Value);


_CRT_INSECURE_DEPRECATE_GLOBALS(_get_fmode) _CRTIMP extern int _fmode;          /* default file translation mode */

_CRTIMP errno_t __cdecl _set_fmode(__in int _Mode);
_CRTIMP errno_t __cdecl _get_fmode(__out int * _PMode);


/* _countof helper */
#if !defined(_countof)
#if !defined(__cplusplus)
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#else
extern "C++"
{
template <typename _CountofType, size_t _SizeOfArray>
char (*__countof_helper(UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
#define _countof(_Array) sizeof(*__countof_helper(_Array))
}
#endif
#endif

/* function prototypes */

#ifndef _CRT_TERMINATE_DEFINED
#define _CRT_TERMINATE_DEFINED
_CRTIMP __declspec(noreturn) void __cdecl exit(__in int _Code);
_CRTIMP __declspec(noreturn) void __cdecl _exit(__in int _Code);
_CRTIMP void __cdecl abort(void);
#endif

_CRTIMP unsigned int __cdecl _set_abort_behavior(__in unsigned int _Flags, __in unsigned int _Mask);

#ifndef _CRT_ABS_DEFINED
#define _CRT_ABS_DEFINED
        int     __cdecl abs(__in int _X);
        long    __cdecl labs(__in long _X);
#endif

#if _INTEGRAL_MAX_BITS >= 64   
        __int64    __cdecl _abs64(__int64);
#endif
#if _MSC_VER >= 1400 && defined(_M_CEE)
        __checkReturn int    __clrcall _atexit_m_appdomain(__in_opt void (__clrcall * _Func)(void));
        __checkReturn inline int __clrcall _atexit_m(__in_opt void (__clrcall *_Function)(void))
        {
            return _atexit_m_appdomain(_Function);
        }
#endif
        int    __cdecl atexit(void (__cdecl *)(void));
#ifndef _CRT_ATOF_DEFINED
#define _CRT_ATOF_DEFINED
_CRTIMP __checkReturn double  __cdecl atof(__in_z const char *_String);
_CRTIMP __checkReturn double  __cdecl _atof_l(__in_z const char *_String, __in_opt _locale_t _Locale);
#endif
_CRTIMP _CRT_JIT_INTRINSIC __checkReturn int    __cdecl atoi(__in_z const char *_Str);
_CRTIMP __checkReturn int    __cdecl _atoi_l(__in_z const char *_Str, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn long   __cdecl atol(__in_z const char *_Str);
_CRTIMP __checkReturn long   __cdecl _atol_l(__in_z const char *_Str, __in_opt _locale_t _Locale);
#ifndef _CRT_ALGO_DEFINED
#define _CRT_ALGO_DEFINED
#if __STDC_WANT_SECURE_LIB__
_CRTIMP __checkReturn void * __cdecl bsearch_s(__in const void * _Key, __in_bcount(_NumOfElements * _SizeOfElements) const void * _Base, 
        __in rsize_t _NumOfElements, __in rsize_t _SizeOfElements,
        __in int (__cdecl * _PtFuncCompare)(void *, const void *, const void *), void * _Context);
#endif
_CRTIMP __checkReturn void * __cdecl bsearch(__in const void * _Key, __in_bcount(_NumOfElements * _SizeOfElements) const void * _Base, 
        __in size_t _NumOfElements, __in size_t _SizeOfElements,
        __in int (__cdecl * _PtFuncCompare)(const void *, const void *));

#if __STDC_WANT_SECURE_LIB__
_CRTIMP void __cdecl qsort_s(__inout_bcount(_NumOfElements* _SizeOfElements) void * _Base, 
        __in rsize_t _NumOfElements, __in rsize_t _SizeOfElements,
        __in int (__cdecl * _PtFuncCompare)(void *, const void *, const void *), void *_Context);
#endif
_CRTIMP void __cdecl qsort(__inout_bcount(_NumOfElements * _SizeOfElements) void * _Base, 
	__in size_t _NumOfElements, __in size_t _SizeOfElements, 
        __in int (__cdecl * _PtFuncCompare)(const void *, const void *));
#endif

unsigned short      _byteswap_ushort            (unsigned short     value);
unsigned long       _byteswap_ulong             (unsigned long      value);
unsigned __int64    _byteswap_uint64            (unsigned __int64   value);
_CRTIMP __checkReturn div_t  __cdecl div(__in int _Numerator, __in int _Denominator);
#ifndef _XBSTRICT
_XBOX_CRT_UNSUPPORTED_INSECURE(getenv, _dupenv_s)
_CRTIMP __checkReturn char * __cdecl getenv(__in_z const char * _VarName);
#if __STDC_WANT_SECURE_LIB__
_XBOX_CRT_UNSUPPORTED(getenv_s)
_CRTIMP __checkReturn_opt errno_t __cdecl getenv_s(__out size_t * _ReturnSize, __out_ecount_z(_DstSize) char * _DstBuf, __in rsize_t _DstSize, __in_z const char * _VarName);
#endif
#if defined(__cplusplus)
_XBOX_CRT_UNSUPPORTED(getenv_s)
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, getenv_s, __out size_t *, _ReturnSize, __out_ecount(_Size) char, _Dest, __in_z const char *, _VarName)
#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_dupenv_s")
#undef _dupenv_s
#endif

#if defined(__cplusplus)
_XBOX_CRT_UNSUPPORTED(_dupenv_s)
#endif
_CRTIMP __checkReturn_opt errno_t __cdecl _dupenv_s(__deref_out_ecount_z_opt(*_PBufferSizeInBytes) char **_PBuffer, __out_opt size_t * _PBufferSizeInBytes, __in_z const char * _VarName);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_dupenv_s")
#endif

#endif // XBSTRICT

_CRTIMP __checkReturn_opt errno_t __cdecl _itoa_s(__in int _Value, __out_ecount_z(_Size) char * _DstBuf, __in size_t _Size, __in int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _itoa_s, __in int, _Value, __out_ecount(_Size) char, _Dest, __in int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(char *, __RETURN_POLICY_DST, _CRTIMP, _itoa, __in int, _Value, __out_z char, _Dest, __in int, _Radix)
#if _INTEGRAL_MAX_BITS >= 64   
_CRTIMP __checkReturn_opt errno_t __cdecl _i64toa_s(__in __int64 _Val, __out_ecount_z(_Size) char * _DstBuf, __in size_t _Size, __in int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_i64toa_s) char * __cdecl _i64toa(__in __int64 _Val, __out_z char * _DstBuf, __in int _Radix);
_CRTIMP __checkReturn_opt errno_t __cdecl _ui64toa_s(__in unsigned __int64 _Val, __out_ecount_z(_Size) char * _DstBuf, __in size_t _Size, __in int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_ui64toa_s) char * __cdecl _ui64toa(__in unsigned __int64 _Val, __out_z char * _DstBuf, __in int _Radix);
_CRTIMP __checkReturn __int64 __cdecl _atoi64(__in_z const char * _String);
_CRTIMP __checkReturn __int64 __cdecl _atoi64_l(__in_z const char * _String, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn __int64 __cdecl _strtoi64(__in_z const char * _String, __deref_opt_out_z char ** _EndPtr, __in int _Radix);
_CRTIMP __checkReturn __int64 __cdecl _strtoi64_l(__in_z const char * _String, __deref_opt_out_z char ** _EndPtr, __in int _Radix, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn unsigned __int64 __cdecl _strtoui64(__in_z const char * _String, __deref_opt_out_z char ** _EndPtr, __in int _Radix);
_CRTIMP __checkReturn unsigned __int64 __cdecl _strtoui64_l(__in_z const char * _String, __deref_opt_out_z char ** _EndPtr, __in int  _Radix, __in_opt _locale_t _Locale);
#endif
_CRTIMP __checkReturn ldiv_t __cdecl ldiv(__in long _Numerator, __in long _Denominator);
#ifdef __cplusplus
extern "C++"
{
    inline ldiv_t  div(__in long _A1, __in long _A2)
    {
        return ldiv(_A1, _A2);
    }
}
#endif
_CRTIMP __checkReturn_opt errno_t __cdecl _ltoa_s(__in long _Val, __out_ecount_z(_Size) char * _DstBuf, __in size_t _Size, __in int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ltoa_s, __in long, _Value, __out_ecount(_Size) char, _Dest, __in int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(char *, __RETURN_POLICY_DST, _CRTIMP, _ltoa, __in long, _Value, __out_z char, _Dest, __in int, _Radix)
_CRTIMP __checkReturn int    __cdecl mblen(__in_bcount_z_opt(_MaxCount) const char * _Ch, __in size_t _MaxCount);
_CRTIMP __checkReturn int    __cdecl _mblen_l(__in_bcount_z_opt(_MaxCount) const char * _Ch, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn size_t __cdecl _mbstrlen(__in_z const char * _Str);
_CRTIMP __checkReturn size_t __cdecl _mbstrlen_l(__in_z const char *_Str, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn size_t __cdecl _mbstrnlen(__in_z const char *_Str, __in size_t _MaxCount);
_CRTIMP __checkReturn size_t __cdecl _mbstrnlen_l(__in_z const char *_Str, __in size_t _MaxCount, __in_opt _locale_t _Locale);
_CRTIMP int    __cdecl mbtowc(__out_z wchar_t * _DstCh, __in_bcount_z_opt(_SrcSizeInBytes) const char * _SrcCh, __in size_t _SrcSizeInBytes);
_CRTIMP int    __cdecl _mbtowc_l(__out_z wchar_t * _DstCh, __in_bcount_z_opt(_SrcSizeInBytes) const char * _SrcCh, __in size_t _SrcSizeInBytes, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn_opt errno_t __cdecl mbstowcs_s(__out_opt size_t * _PtNumOfCharConverted, __out_ecount_part_opt(_SizeInWords, *_PtNumOfCharConverted) wchar_t * _DstBuf, __in size_t _SizeInWords, __in_ecount_z(_MaxCount) const char * _SrcBuf, __in size_t _MaxCount );
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(errno_t, mbstowcs_s, __out_opt size_t *, _PtNumOfCharConverted, __out_ecount_z(_Size) wchar_t, _Dest, __in_z const char *, _Source, __in size_t, _MaxCount)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE(_CRTIMP, mbstowcs, __out_ecount_z(_MaxCount) wchar_t, _Dest, __in_z const char *, _Source, __in size_t, _MaxCount)

_CRTIMP __checkReturn_opt errno_t __cdecl _mbstowcs_s_l(__out_opt size_t * _PtNumOfCharConverted, __out_ecount_part_opt(_SizeInWords, *_PtNumOfCharConverted) wchar_t * _DstBuf, __in size_t _SizeInWords, __in_ecount_z(_MaxCount) const char * _SrcBuf, __in size_t _MaxCount, __in_opt _locale_t _Locale);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(errno_t, _mbstowcs_s_l, __out_opt size_t *, _PtNumOfCharConverted, __out_ecount(_Size) wchar_t, _Dest, __in_z const char *, _Source, __in size_t, _MaxCount, __in_opt _locale_t, _Locale)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_CRTIMP, _mbstowcs_l, _mbstowcs_s_l, __out_ecount_z_opt(_Size) wchar_t, __out_ecount_z(_MaxCount) wchar_t, _Dest, __in_z const char *, _Source, __in size_t, _MaxCount, __in_opt _locale_t, _Locale)

_CRTIMP __checkReturn int    __cdecl rand(void);
_CRTIMP errno_t __cdecl rand_s ( __out unsigned int *_RandomValue);

_CRTIMP __checkReturn_opt int    __cdecl _set_error_mode(__in int _Mode);

_CRTIMP void   __cdecl srand(__in unsigned int _Seed);
_CRTIMP __checkReturn double __cdecl strtod(__in_z const char * _Str, __deref_opt_out_z char ** _EndPtr);
_CRTIMP __checkReturn double __cdecl _strtod_l(__in_z const char * _Str, __deref_opt_out_z char ** _EndPtr, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn long   __cdecl strtol(__in_z const char * _Str, __deref_opt_out_z char ** _EndPtr, __in int _Radix );
_CRTIMP __checkReturn long   __cdecl _strtol_l(__in_z const char *_Str, __deref_opt_out_z char **_EndPtr, __in int _Radix, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn unsigned long __cdecl strtoul(__in_z const char * _Str, __deref_opt_out_z char ** _EndPtr, __in int _Radix);
_CRTIMP __checkReturn unsigned long __cdecl _strtoul_l(const char * _Str, __deref_opt_out_z char **_EndPtr, __in int _Radix, __in_opt _locale_t _Locale);
#ifndef _CRT_SYSTEM_DEFINED
#define _CRT_SYSTEM_DEFINED
_CRTIMP int __cdecl system(__in_z_opt const char * _Command);
#endif
_CRTIMP __checkReturn_opt errno_t __cdecl _ultoa_s(__in unsigned long _Val, __out_ecount_z(_Size) char * _DstBuf, __in size_t _Size, __in int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ultoa_s, __in unsigned long, _Value, __out_ecount(_Size) char, _Dest, __in int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(char *, __RETURN_POLICY_DST, _CRTIMP, _ultoa, __in unsigned long, _Value, __out_z char, _Dest, __in int, _Radix)
_CRTIMP _CRT_INSECURE_DEPRECATE(wctomb_s) int    __cdecl wctomb(__out_bcount_z_opt(MB_LEN_MAX) char * _MbCh, __in_z wchar_t _WCh);
_CRTIMP _CRT_INSECURE_DEPRECATE(_wctomb_s_l) int    __cdecl _wctomb_l(__out_z_opt char * _MbCh, __in wchar_t _WCh, __in_opt _locale_t _Locale);
#if __STDC_WANT_SECURE_LIB__
_CRTIMP __checkReturn_wat errno_t __cdecl wctomb_s(__out_opt int * _SizeConverted, __out_bcount_part_opt(_SizeInBytes, *_SizeConverted) char * _MbCh, __in rsize_t _SizeInBytes, __in wchar_t _WCh);
#endif
_CRTIMP __checkReturn_wat errno_t __cdecl _wctomb_s_l(__out_opt int * _SizeConverted, __out_bcount_z_opt(_SizeInBytes) char * _MbCh, __in size_t _SizeInBytes, __in wchar_t _WCh, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn_wat errno_t __cdecl wcstombs_s(__out_opt size_t * _PtNumOfCharConverted, __out_bcount_part_opt(_DstSizeInBytes, *_PtNumOfCharConverted) char * _Dst, __in size_t _DstSizeInBytes, __in_z const wchar_t * _Src, __in size_t _MaxCountInBytes);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(errno_t, wcstombs_s, __out_opt size_t *, _PtNumOfCharConverted, __out_bcount_opt(_Size) char, _Dest, __in_z const wchar_t *, _Source, __in size_t, _MaxCount)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE(_CRTIMP, wcstombs, __out_ecount_z(_MaxCount) char, _Dest, __in_z const wchar_t *, _Source, __in size_t, _MaxCount)
_CRTIMP __checkReturn_wat errno_t __cdecl _wcstombs_s_l(__out_opt size_t * _PtNumOfCharConverted, __out_bcount_part_opt(_DstSizeInBytes, *_PtNumOfCharConverted) char * _Dst, __in size_t _DstSizeInBytes, __in_z const wchar_t * _Src, __in size_t _MaxCountInBytes, __in_opt _locale_t _Locale);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(errno_t, _wcstombs_s_l, __out_opt size_t *,_PtNumOfCharConverted, __out_ecount_opt(_Size) char, _Dest, __in_z const wchar_t *, _Source, __in size_t, _MaxCount, __in_opt _locale_t, _Locale)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_CRTIMP, _wcstombs_l, _wcstombs_s_l, __out_ecount_z_opt(_Size) char, __out_ecount_z(_MaxCount) char, _Dest, __in_z const wchar_t *, _Source, __in size_t, _MaxCount, __in_opt _locale_t, _Locale)

#if _MSC_VER >= 1400 && defined(__cplusplus) && defined(_M_CEE)
/*
 * Managed search routines. Note __cplusplus, this is because we only support
 * managed C++.
 */
extern "C++"
{
#if __STDC_WANT_SECURE_LIB__
__checkReturn void * __clrcall bsearch_s(__in const void * _Key, __in_bcount(_NumOfElements*_SizeOfElements) const void * _Base, __in rsize_t _NumOfElements, __in rsize_t _SizeOfElements, 
        __in int (__clrcall * _PtFuncCompare)(void *, const void *, const void *), void * _Context);
#endif
__checkReturn void * __clrcall bsearch  (__in const void * _Key, __in_bcount(_NumOfElements*_SizeOfElements) const void * _Base, __in size_t _NumOfElements, __in size_t _SizeOfElements,
        __in int (__clrcall * _PtFuncCompare)(const void *, const void *));

#if __STDC_WANT_SECURE_LIB__
void __clrcall qsort_s(__inout_bcount(_NumOfElements*_SizeOfElements) void * _Base, __in rsize_t _NumOfElements, __in rsize_t _SizeOfElements, 
        __in int (__clrcall * _PtFuncCompare)(void *, const void *, const void *), void * _Context);
#endif
void __clrcall qsort  (__inout_bcount(_NumOfElements*_SizeOfElements) void * _Base, __in size_t _NumOfElements, __in size_t _SizeOfElements, 
        __in int (__clrcall * _PtFuncCompare)(const void *, const void *));
}
#endif

#ifndef _CRT_ALLOCATION_DEFINED
#define _CRT_ALLOCATION_DEFINED

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma push_macro("calloc")
#pragma push_macro("free")
#pragma push_macro("malloc")
#pragma push_macro("realloc")
#pragma push_macro("_recalloc")
#pragma push_macro("_aligned_free")
#pragma push_macro("_aligned_malloc")
#pragma push_macro("_aligned_offset_malloc")
#pragma push_macro("_aligned_realloc")
#pragma push_macro("_aligned_recalloc")
#pragma push_macro("_aligned_offset_realloc")
#pragma push_macro("_aligned_offset_recalloc")
#pragma push_macro("_aligned_msize")

#undef calloc
#undef free
#undef malloc
#undef realloc
#undef _recalloc
#undef _aligned_free
#undef _aligned_malloc
#undef _aligned_offset_malloc
#undef _aligned_realloc
#undef _aligned_recalloc
#undef _aligned_offset_realloc
#undef _aligned_offset_recalloc
#undef _aligned_msize

#endif
_CRTIMP _CRT_JIT_INTRINSIC  _CRTNOALIAS _CRTRESTRICT __checkReturn __bcount_opt(_NumOfElements* _SizeOfElements)    void * __cdecl calloc(__in size_t _NumOfElements, __in size_t _SizeOfElements);
_CRTIMP                     _CRTNOALIAS                                                                             void   __cdecl free(__inout_opt void * _Memory);
_CRTIMP _CRT_JIT_INTRINSIC  _CRTNOALIAS _CRTRESTRICT __checkReturn __bcount_opt(_Size)                              void * __cdecl malloc(__in size_t _Size);
_CRTIMP                     _CRTNOALIAS _CRTRESTRICT __checkReturn __bcount_opt(_NewSize)                           void * __cdecl realloc(__in_opt void * _Memory, __in size_t _NewSize);
_CRTIMP                     _CRTNOALIAS _CRTRESTRICT __checkReturn __bcount_opt(_Size*_Count)                       void * __cdecl _recalloc(__in_opt void * _Memory, __in size_t _Count, __in size_t _Size);
_CRTIMP                     _CRTNOALIAS                                                                             void   __cdecl _aligned_free(__inout_opt void * _Memory);
_CRTIMP                     _CRTNOALIAS _CRTRESTRICT __checkReturn __bcount_opt(_Size)                              void * __cdecl _aligned_malloc(__in size_t _Size, __in size_t _Alignment);
_CRTIMP                     _CRTNOALIAS _CRTRESTRICT __checkReturn __bcount_opt(_Size)                              void * __cdecl _aligned_offset_malloc(__in size_t _Size, __in size_t _Alignment, __in size_t _Offset);
_CRTIMP                     _CRTNOALIAS _CRTRESTRICT __checkReturn __bcount_opt(_Size)                              void * __cdecl _aligned_realloc(__in_opt void * _Memory, __in size_t _Size, __in size_t _Alignment);
_CRTIMP                     _CRTNOALIAS _CRTRESTRICT __checkReturn __bcount_opt(_Size*_Count)                       void * __cdecl _aligned_recalloc(__in_opt void * _Memory, __in size_t _Count, __in size_t _Size, __in size_t _Alignment);
_CRTIMP                     _CRTNOALIAS _CRTRESTRICT __checkReturn __bcount_opt(_Size)                              void * __cdecl _aligned_offset_realloc(__in_opt void * _Memory, __in size_t _Size, __in size_t _Alignment, __in size_t _Offset);
_CRTIMP                     _CRTNOALIAS _CRTRESTRICT __checkReturn __bcount_opt(_Size*_Count)                       void * __cdecl _aligned_offset_recalloc(__in_opt void * _Memory, __in size_t _Count, __in size_t _Size, __in size_t _Alignment, __in size_t _Offset);
_CRTIMP                                              __checkReturn                                                  size_t __cdecl _aligned_msize(__in void * _Memory, __in size_t _Alignment, __in size_t _Offset);


#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma pop_macro("_aligned_msize")
#pragma pop_macro("_aligned_offset_recalloc")
#pragma pop_macro("_aligned_offset_realloc")
#pragma pop_macro("_aligned_recalloc")
#pragma pop_macro("_aligned_realloc")
#pragma pop_macro("_aligned_offset_malloc")
#pragma pop_macro("_aligned_malloc")
#pragma pop_macro("_aligned_free")
#pragma pop_macro("_recalloc")
#pragma pop_macro("realloc")
#pragma pop_macro("malloc")
#pragma pop_macro("free")
#pragma pop_macro("calloc")

#endif

#endif /*_CRT_ALLOCATION_DEFINED */

#ifndef _WSTDLIB_DEFINED

/* wide function prototypes, also declared in wchar.h  */

_CRTIMP __checkReturn_wat errno_t __cdecl _itow_s (__in int _Val, __out_ecount_z(_SizeInWords) wchar_t * _DstBuf, __in size_t _SizeInWords, __in int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _itow_s, __in int, _Value, __out_ecount(_Size) wchar_t, _Dest, __in int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _itow, __in int, _Value, __out_z wchar_t, _Dest, __in int, _Radix)
_CRTIMP __checkReturn_wat errno_t __cdecl _ltow_s (__in long _Val, __out_ecount_z(_SizeInWords) wchar_t * _DstBuf, __in size_t _SizeInWords, __in int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ltow_s, __in long, _Value, __out_ecount(_Size) wchar_t, _Dest, __in int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _ltow, __in long, _Value, __out_z wchar_t, _Dest, __in int, _Radix)
_CRTIMP __checkReturn_wat errno_t __cdecl _ultow_s (__in unsigned long _Val, __out_ecount_z(_SizeInWords) wchar_t * _DstBuf, __in size_t _SizeInWords, __in int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ultow_s, __in unsigned long, _Value, __out_ecount(_Size) wchar_t, _Dest, __in int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _ultow, __in unsigned long, _Value, __out_z wchar_t, _Dest, __in int, _Radix)
_CRTIMP __checkReturn double __cdecl wcstod(__in_z const wchar_t * _Str, __deref_opt_out_z wchar_t ** _EndPtr);
_CRTIMP __checkReturn double __cdecl _wcstod_l(__in_z const wchar_t *_Str, __deref_opt_out_z wchar_t ** _EndPtr, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn long   __cdecl wcstol(__in_z const wchar_t *_Str, __deref_opt_out_z wchar_t ** _EndPtr, int _Radix);
_CRTIMP __checkReturn long   __cdecl _wcstol_l(__in_z const wchar_t *_Str, __deref_opt_out_z wchar_t **_EndPtr, int _Radix, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn unsigned long __cdecl wcstoul(__in_z const wchar_t *_Str, __deref_opt_out_z wchar_t ** _EndPtr, int _Radix);
_CRTIMP __checkReturn unsigned long __cdecl _wcstoul_l(__in_z const wchar_t *_Str, __deref_opt_out_z wchar_t **_EndPtr, int _Radix, __in_opt _locale_t _Locale);
#ifndef _XBSTRICT
_XBOX_CRT_UNSUPPORTED_INSECURE(_wgetenv, _wdupenv_s)
_CRTIMP __checkReturn wchar_t * __cdecl _wgetenv(__in_z const wchar_t * _VarName);
_XBOX_CRT_UNSUPPORTED(_wgetenv_s)
_CRTIMP __checkReturn_wat errno_t __cdecl _wgetenv_s(__out size_t * _ReturnSize, __out_ecount_z(_DstSizeInWords) wchar_t * _DstBuf, __in size_t _DstSizeInWords, __in_z const wchar_t * _VarName);
#if defined(__cplusplus)
_XBOX_CRT_UNSUPPORTED(_wgetenv_s)
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _wgetenv_s, __out size_t *, _ReturnSize, __out_ecount(_Size) wchar_t, _Dest, __in_z const wchar_t *, _VarName)

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_wdupenv_s")
#undef _wdupenv_s
#endif

#if defined(__cplusplus)
_XBOX_CRT_UNSUPPORTED(_wdupenv_s)
#endif
_CRTIMP __checkReturn_wat errno_t __cdecl _wdupenv_s(__deref_out_ecount_z_opt(*_BufferSizeInWords) wchar_t **_Buffer, __out_opt size_t *_BufferSizeInWords, __in_z const wchar_t *_VarName);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_wdupenv_s")
#endif

#endif // XBSTRICT

#ifndef _CRT_WSYSTEM_DEFINED
#define _CRT_WSYSTEM_DEFINED
_CRTIMP int __cdecl _wsystem(__in_z_opt const wchar_t * _Command);
#endif
_CRTIMP __checkReturn double __cdecl _wtof(__in_z const wchar_t *_Str);
_CRTIMP __checkReturn double __cdecl _wtof_l(__in_z const wchar_t *_Str, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn int __cdecl _wtoi(__in_z const wchar_t *_Str);
_CRTIMP __checkReturn int __cdecl _wtoi_l(__in_z const wchar_t *_Str, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn long __cdecl _wtol(__in_z const wchar_t *_Str);
_CRTIMP __checkReturn long __cdecl _wtol_l(__in_z const wchar_t *_Str, __in_opt _locale_t _Locale);

#if _INTEGRAL_MAX_BITS >= 64   
_CRTIMP __checkReturn_wat errno_t __cdecl _i64tow_s(__in __int64 _Val, __out_ecount_z(_SizeInWords) wchar_t * _DstBuf, __in size_t _SizeInWords, __in int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_i65tow_s) wchar_t * __cdecl _i64tow(__in __int64 _Val, __out_z wchar_t * _DstBuf, __in int _Radix);
_CRTIMP __checkReturn_wat errno_t __cdecl _ui64tow_s(__in unsigned __int64 _Val, __out_ecount_z(_SizeInWords) wchar_t * _DstBuf, __in size_t _SizeInWords, __in int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_ui64tow_s) wchar_t * __cdecl _ui64tow(__in unsigned __int64 _Val, __out_z wchar_t * _DstBuf, __in int _Radix);
_CRTIMP __checkReturn __int64   __cdecl _wtoi64(__in_z const wchar_t *_Str);
_CRTIMP __checkReturn __int64   __cdecl _wtoi64_l(__in_z const wchar_t *_Str, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn __int64   __cdecl _wcstoi64(__in_z const wchar_t * _Str, __deref_opt_out_z wchar_t ** _EndPtr, __in int _Radix);
_CRTIMP __checkReturn __int64   __cdecl _wcstoi64_l(__in_z const wchar_t * _Str, __deref_opt_out_z wchar_t ** _EndPtr, __in int _Radix, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn unsigned __int64  __cdecl _wcstoui64(__in_z const wchar_t * _Str, __deref_opt_out_z wchar_t ** _EndPtr, __in int _Radix);
_CRTIMP __checkReturn unsigned __int64  __cdecl _wcstoui64_l(__in_z const wchar_t *_Str , __deref_opt_out_z wchar_t ** _EndPtr, __in int _Radix, __in_opt _locale_t _Locale);
#endif

#define _WSTDLIB_DEFINED
#endif



/* 
Buffer size required to be passed to _gcvt, fcvt and other fp conversion routines
*/
#define _CVTBUFSIZE (309+40) /* # of digits in max. dp value + slop */

#ifndef _XBSTRICT

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma push_macro("_fullpath")
#undef _fullpath

#endif

_XBOX_CRT_UNSUPPORTED(_fullpath)
_CRTIMP __checkReturn char * __cdecl _fullpath(__out_ecount_z_opt(_SizeInBytes) char * _FullPath, __in_z const char * _Path, __in size_t _SizeInBytes);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma pop_macro("_fullpath")

#endif
#endif // XBSTRICT

_CRTIMP __checkReturn_wat errno_t __cdecl _ecvt_s(__out_ecount_z(_Size) char * _DstBuf, __in size_t _Size, __in double _Val, __in int _NumOfDights, __out int * _PtDec, __out int * _PtSign);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _ecvt_s, __out_ecount(_Size) char, _Dest, __in double, _Value, __in int, _NumOfDigits, __out int *, _PtDec, __out int *, _PtSign)
_CRTIMP _CRT_INSECURE_DEPRECATE(_ecvt_s) __checkReturn char * __cdecl _ecvt(__in double _Val, __in int _NumOfDigits, __out int * _PtDec, __out int * _PtSign);
_CRTIMP __checkReturn_wat errno_t __cdecl _fcvt_s(__out_ecount_z(_Size) char * _DstBuf, __in size_t _Size, __in double _Val, __in int _NumOfDec, __out int * _PtDec, __out int * _PtSign);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _fcvt_s, __out_ecount(_Size) char, _Dest, __in double, _Value, __in int, _NumOfDigits, __out int *, _PtDec, __out int *, _PtSign)
_CRTIMP _CRT_INSECURE_DEPRECATE(_fcvt_s) __checkReturn char * __cdecl _fcvt(__in double _Val, __in int _NumOfDec, __out int * _PtDec, __out int * _PtSign);
_CRTIMP errno_t __cdecl _gcvt_s(__out_ecount_z(_Size) char * _DstBuf, __in size_t _Size, __in double _Val, __in int _NumOfDigits);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _gcvt_s, __out_ecount(_Size) char, _Dest, __in double, _Value, __in int, _NumOfDigits)
_CRTIMP _CRT_INSECURE_DEPRECATE(_gcvt_s) char * __cdecl _gcvt(__in double _Val, __in int _NumOfDigits, __out_z char * _DstBuf);

_CRTIMP __checkReturn int __cdecl _atodbl(__out _CRT_DOUBLE * _Result, __in_z char * _Str);
_CRTIMP __checkReturn int __cdecl _atoldbl(__out _LDOUBLE * _Result, __in_z char * _Str);
_CRTIMP __checkReturn int __cdecl _atoflt(__out _CRT_FLOAT * _Result, __in_z char * _Str);
_CRTIMP __checkReturn int __cdecl _atodbl_l(__out _CRT_DOUBLE * _Result, __in_z char * _Str, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn int __cdecl _atoldbl_l(__out _LDOUBLE * _Result, __in_z char * _Str, __in_opt _locale_t _Locale);
_CRTIMP __checkReturn int __cdecl _atoflt_l(__out _CRT_FLOAT * _Result, __in_z char * _Str, __in_opt _locale_t _Locale);
        __checkReturn unsigned long __cdecl _lrotl(__in unsigned long _Val, __in int _Shift);
        __checkReturn unsigned long __cdecl _lrotr(__in unsigned long _Val, __in int _Shift);
_CRTIMP_ALTERNATIVE __checkReturn_wat errno_t   __cdecl _makepath_s(__out_ecount_z(_Size) char * _PathResult, __in_opt size_t _Size, __in_z_opt const char * _Drive, __in_z_opt const char * _Dir, __in_z_opt const char * _Filename,
        __in_z_opt const char * _Ext);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _makepath_s, __out_ecount(_Size) char, _Path, __in_z_opt const char *, _Drive, __in_z_opt const char *, _Dir, __in_z_opt const char *, _Filename, __in_z_opt const char *, _Ext)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(void, __RETURN_POLICY_VOID, _CRTIMP, _makepath, __out_z char, _Path, __in_z_opt const char *, _Drive, __in_z_opt const char *, _Dir, __in_z_opt const char *, _Filename, __in_z_opt const char *, _Ext)

#if _MSC_VER >= 1400 && defined(_M_CEE)
		_onexit_m_t    __clrcall _onexit_m_appdomain(_onexit_m_t _Function);
		inline _onexit_m_t    __clrcall _onexit_m(_onexit_t _Function)
		{
			return _onexit_m_appdomain(_Function);
		}
        
#endif
        _onexit_t __cdecl _onexit(__in_opt _onexit_t _Func);
        
#ifndef _CRT_PERROR_DEFINED
#define _CRT_PERROR_DEFINED
_CRTIMP void __cdecl perror(__in_z_opt const char * _ErrMsg);
#endif
#ifndef _XBSTRICT
_XBOX_CRT_UNSUPPORTED(_putenv)
_CRTIMP __checkReturn int    __cdecl _putenv(__in_z const char * _EnvString);
_XBOX_CRT_UNSUPPORTED(_putenv_s)
_CRTIMP __checkReturn_wat errno_t __cdecl _putenv_s(__in_z const char * _Name, __in_z const char * _Value);
#endif // XBSTRICT
        __checkReturn unsigned int __cdecl _rotl(__in unsigned int _Val, __in int _Shift);
#if _INTEGRAL_MAX_BITS >= 64   
        __checkReturn unsigned __int64 __cdecl _rotl64(__in unsigned __int64 _Val, __in int _Shift);
#endif
        __checkReturn unsigned int __cdecl _rotr(__in unsigned int _Val, __in int _Shift);
#if _INTEGRAL_MAX_BITS >= 64   
        __checkReturn unsigned __int64 __cdecl _rotr64(__in unsigned __int64 _Val, __in int _Shift);
#endif
_CRTIMP errno_t __cdecl _searchenv_s(__in_z const char * _Filename, __in_z const char * _EnvVar, __out_ecount_z(_SizeInBytes) char * _ResultPath, __in size_t _SizeInBytes);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(errno_t, _searchenv_s, __in_z const char *, _Filename, __in_z const char *, _EnvVar, __out_ecount(_Size) char, _ResultPath)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0(void, __RETURN_POLICY_VOID, _CRTIMP, _searchenv, __in_z const char *, _Filename, __in_z const char *, _EnvVar, __out_z char, _ResultPath)

_CRT_INSECURE_DEPRECATE(_splitpath_s) _CRTIMP void   __cdecl _splitpath(__in_z const char * _FullPath, __out_z_opt char * _Drive, __out_z_opt char * _Dir, __out_z_opt char * _Filename, __out_z_opt char * _Ext);
_CRTIMP_ALTERNATIVE __checkReturn_wat errno_t  __cdecl _splitpath_s(__in_z const char * _FullPath, 
		__out_ecount_z_opt(_DriveSize) char * _Drive, __in size_t _DriveSize, 
		__out_ecount_z_opt(_DirSize) char * _Dir, __in size_t _DirSize, 
		__out_ecount_z_opt(_FilenameSize) char * _Filename, __in size_t _FilenameSize, 
		__out_ecount_z_opt(_ExtSize) char * _Ext, __in size_t _ExtSize);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(errno_t, _splitpath_s,  char, _Dest)

_CRTIMP void   __cdecl _swab(__inout_ecount_full(_SizeInBytes) char * _Buf1, __inout_ecount_full(_SizeInBytes) char * _Buf2, int _SizeInBytes);

#ifndef _WSTDLIBP_DEFINED

/* wide function prototypes, also declared in wchar.h  */

#ifndef _XBSTRICT

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_wfullpath")
#undef _wfullpath
#endif

_XBOX_CRT_UNSUPPORTED(_wfullpath)
_CRTIMP __checkReturn wchar_t * __cdecl _wfullpath(__out_ecount_z_opt(_SizeInWords) wchar_t * _FullPath, __in_z const wchar_t * _Path, __in size_t _SizeInWords);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_wfullpath")
#endif
#endif // XBSTRICT

_CRTIMP_ALTERNATIVE __checkReturn_wat errno_t __cdecl _wmakepath_s(__out_ecount_z(_SizeInWords) wchar_t * _PathResult, __in_opt size_t _SizeInWords, __in_z_opt const wchar_t * _Drive, __in_z_opt const wchar_t * _Dir, __in_z_opt const wchar_t * _Filename,
        __in_z_opt const wchar_t * _Ext);        
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _wmakepath_s, __out_ecount(_Size) wchar_t, _ResultPath, __in_z_opt const wchar_t *, _Drive, __in_z_opt const wchar_t *, _Dir, __in_z_opt const wchar_t *, _Filename, __in_z_opt const wchar_t *, _Ext)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(void, __RETURN_POLICY_VOID, _CRTIMP, _wmakepath, __out_z wchar_t, _ResultPath, __in_z_opt const wchar_t *, _Drive, __in_z_opt const wchar_t *, _Dir, __in_z_opt const wchar_t *, _Filename, __in_z_opt const wchar_t *, _Ext)
#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED
_CRTIMP void __cdecl _wperror(__in_z_opt const wchar_t * _ErrMsg);
#endif 
_CRTIMP __checkReturn int    __cdecl _wputenv(__in_z const wchar_t * _EnvString);
_CRTIMP __checkReturn_wat errno_t __cdecl _wputenv_s(__in_z const wchar_t * _Name, __in_z const wchar_t * _Value);
_CRTIMP errno_t __cdecl _wsearchenv_s(__in_z const wchar_t * _Filename, __in_z const wchar_t * _EnvVar, __out_ecount_z(_SizeInWords) wchar_t * _ResultPath, __in size_t _SizeInWords);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(errno_t, _wsearchenv_s, __in_z const wchar_t *, _Filename, __in_z const wchar_t *, _EnvVar, __out_ecount(_Size) wchar_t, _ResultPath)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0(void, __RETURN_POLICY_VOID, _CRTIMP, _wsearchenv, __in_z const wchar_t *, _Filename, __in_z const wchar_t *, _EnvVar, __out_z wchar_t, _ResultPath)
_CRT_INSECURE_DEPRECATE(_wsplitpath_s) _CRTIMP void   __cdecl _wsplitpath(__in_z const wchar_t * _FullPath, __out_z_opt wchar_t * _Drive, __out_z_opt wchar_t * _Dir, __out_z_opt wchar_t * _Filename, __out_z_opt wchar_t * _Ext);
_CRTIMP_ALTERNATIVE errno_t __cdecl _wsplitpath_s(__in_z const wchar_t * _FullPath, 
		__out_ecount_z_opt(_DriveSizeInWords) wchar_t * _Drive, __in size_t _DriveSizeInWords, 
		__out_ecount_z_opt(_DirSizeInWords) wchar_t * _Dir, __in size_t _DirSizeInWords, 
		__out_ecount_z_opt(_FilenameSizeInWords) wchar_t * _Filename, __in size_t _FilenameSizeInWords, 
		__out_ecount_z_opt(_ExtSizeInWords) wchar_t * _Ext, __in size_t _ExtSizeInWords);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(errno_t, _wsplitpath_s, wchar_t, _Path)

#define _WSTDLIBP_DEFINED
#endif

/* The Win32 API SetErrorMode, Beep and Sleep should be used instead. */
_CRT_OBSOLETE(Sleep) _CRTIMP void __cdecl _sleep(__in unsigned long _Duration);


#if     !__STDC__


/* Non-ANSI names for compatibility */

#ifndef __cplusplus
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#define sys_errlist _sys_errlist
#define sys_nerr    _sys_nerr
#define environ     _environ

#pragma warning(push)
#pragma warning(disable: 4141) /* Using deprecated twice */ 
_CRT_NONSTDC_DEPRECATE(_ecvt) _CRT_INSECURE_DEPRECATE(_ecvt_s)		_CRTIMP __checkReturn char * __cdecl ecvt(__in double _Val, __in int _NumOfDigits, __out int * _PtDec, __out int * _PtSign);
_CRT_NONSTDC_DEPRECATE(_fcvt) _CRT_INSECURE_DEPRECATE(_fcvt_s)		_CRTIMP __checkReturn char * __cdecl fcvt(__in double _Val, __in int _NumOfDec, __out int * _PtDec, __out int * _PtSign);
_CRT_NONSTDC_DEPRECATE(_gcvt) _CRT_INSECURE_DEPRECATE(_fcvt_s)		_CRTIMP char * __cdecl gcvt(__in double _Val, __in int _NumOfDigits, __out_z char * _DstBuf);
_CRT_NONSTDC_DEPRECATE(_itoa) _CRT_INSECURE_DEPRECATE(_itoa_s)		_CRTIMP char * __cdecl itoa(__in int _Val, __out_z char * _DstBuf, __in int _Radix);
_CRT_NONSTDC_DEPRECATE(_ltoa) _CRT_INSECURE_DEPRECATE(_ltoa_s)		_CRTIMP char * __cdecl ltoa(__in long _Val, __out_z char * _DstBuf, __in int _Radix);
#ifndef _XBSTRICT
_XBOX_CRT_UNSUPPORTED_NONSTDC(putenv, _putenv)                      _CRTIMP __checkReturn int    __cdecl putenv(__in_z const char * _EnvString);
#endif // XBSTRICT
_CRT_NONSTDC_DEPRECATE(_swab)										_CRTIMP void   __cdecl swab(__inout_bcount_z(_SizeInBytes) char * _Buf1,__inout_bcount_z(_SizeInBytes) char * _Buf2, __in int _SizeInBytes);
_CRT_NONSTDC_DEPRECATE(_ultoa) _CRT_INSECURE_DEPRECATE(_ultoa_s)	_CRTIMP char * __cdecl ultoa(__in unsigned long _Val, __out_z char * _Dstbuf, __in int _Radix);
#pragma warning(pop)
onexit_t __cdecl onexit(__in_opt onexit_t _Func);


#endif  /* __STDC__ */

#ifdef  __cplusplus
}

#endif

#ifdef  _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_STDLIB */
