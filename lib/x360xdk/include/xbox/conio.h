/***
*conio.h - console and port I/O declarations
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This include file contains the function declarations for
*       the MS C V2.03 compatible console I/O routines.
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _INC_CONIO
#define _INC_CONIO

#include <crtdefs.h>

#ifndef _XBSTRICT

#ifdef __cplusplus
extern "C" {
#endif

/* Function prototypes */

_XBOX_CRT_UNSUPPORTED(_cgets_s)
_CRTIMP __checkReturn_wat errno_t __cdecl _cgets_s(__out_ecount_z(_Size)                char * _Buffer, size_t _Size, __out size_t * _SizeRead);
#if defined(__cplusplus)
_XBOX_CRT_UNSUPPORTED(_cgets_s)
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _cgets_s, __out_ecount_part(_Size, *_Buffer) char, _Buffer, __out size_t *, _Size)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(char *, _CRTIMP, _cgets, __out_z char, _Buffer)
_XBOX_CRT_UNSUPPORTED(_cprintf)
_CRTIMP __checkReturn_opt int __cdecl _cprintf(__in_z __format_string const char * _Format, ...);
_XBOX_CRT_UNSUPPORTED(_cprintf_s)
_CRTIMP __checkReturn_opt int __cdecl _cprintf_s(__in_z __format_string const char * _Format, ...);
_XBOX_CRT_UNSUPPORTED(_cputs)
_CRTIMP __checkReturn_opt int __cdecl _cputs(__in_z const char * _Str);
_XBOX_CRT_UNSUPPORTED_INSECURE(_cscanf, _cscanf_s)
_CRTIMP __checkReturn_opt int __cdecl _cscanf(__in_z __format_string const char * _Format, ...);
_XBOX_CRT_UNSUPPORTED_INSECURE(_cscanf_l, _cscanf_s_l)
_CRTIMP __checkReturn_opt int __cdecl _cscanf_l(__in_z __format_string const char * _Format, __in_opt _locale_t _Locale, ...);
_XBOX_CRT_UNSUPPORTED(_cscanf_s)
_CRTIMP __checkReturn_opt int __cdecl _cscanf_s(__in_z __format_string const char * _Format, ...);
_XBOX_CRT_UNSUPPORTED(_cscanf_s_l)
_CRTIMP __checkReturn_opt int __cdecl _cscanf_s_l(__in_z __format_string const char * _Format, __in_opt _locale_t _Locale, ...);
_XBOX_CRT_UNSUPPORTED(_getch)
_CRTIMP __checkReturn int __cdecl _getch(void);
_XBOX_CRT_UNSUPPORTED(_getche)
_CRTIMP __checkReturn int __cdecl _getche(void);
_XBOX_CRT_UNSUPPORTED(_vcprintf)
_CRTIMP __checkReturn_opt int __cdecl _vcprintf(__in_z __format_string const char * _Format, va_list _ArgList);
_XBOX_CRT_UNSUPPORTED(_vcprintf_s)
_CRTIMP __checkReturn_opt int __cdecl _vcprintf_s(__in_z __format_string const char * _Format, va_list _ArgList);

_XBOX_CRT_UNSUPPORTED(_cprintf_p)
_CRTIMP __checkReturn_opt int __cdecl _cprintf_p(__in_z __format_string const char * _Format, ...);
_XBOX_CRT_UNSUPPORTED(_vcprintf_p)
_CRTIMP __checkReturn_opt int __cdecl _vcprintf_p(__in_z const char * _Format, va_list _ArgList);

_XBOX_CRT_UNSUPPORTED(_cprintf_l)
_CRTIMP __checkReturn_opt int __cdecl _cprintf_l(__in_z __format_string const char * _Format, __in_opt _locale_t _Locale, ...);
_XBOX_CRT_UNSUPPORTED(_cprintf_s_l)
_CRTIMP __checkReturn_opt int __cdecl _cprintf_s_l(__in_z __format_string const char * _Format, __in_opt _locale_t _Locale, ...);
_XBOX_CRT_UNSUPPORTED(_vcprintf_l)
_CRTIMP __checkReturn_opt int __cdecl _vcprintf_l(__in_z __format_string const char * _Format, __in_opt _locale_t _Locale, va_list _ArgList);
_XBOX_CRT_UNSUPPORTED(_vcprintf_s_l)
_CRTIMP __checkReturn_opt int __cdecl _vcprintf_s_l(__in_z __format_string const char * _Format, __in_opt _locale_t _Locale, va_list _ArgList);
_XBOX_CRT_UNSUPPORTED(_cprintf_p_l)
_CRTIMP __checkReturn_opt int __cdecl _cprintf_p_l(__in_z __format_string const char * _Format, __in_opt _locale_t _Locale, ...);
_XBOX_CRT_UNSUPPORTED(_vcprintf_p_l)
_CRTIMP __checkReturn_opt int __cdecl _vcprintf_p_l(__in_z __format_string const char * _Format, __in_opt _locale_t _Locale, va_list _ArgList);

_XBOX_CRT_UNSUPPORTED(_kbhit)
_CRTIMP int __cdecl _kbhit(void);
_XBOX_CRT_UNSUPPORTED(_putch)
_CRTIMP int __cdecl _putch(__in int _Ch);
_XBOX_CRT_UNSUPPORTED(_ungetch)
_CRTIMP int __cdecl _ungetch(__in int _Ch);

_XBOX_CRT_UNSUPPORTED(_getch_nolock)
_CRTIMP __checkReturn int __cdecl _getch_nolock(void);
_XBOX_CRT_UNSUPPORTED(_getche_nolock)
_CRTIMP __checkReturn int __cdecl _getche_nolock(void);
_XBOX_CRT_UNSUPPORTED(_putch_nolock)
_CRTIMP int __cdecl _putch_nolock(__in int _Ch);
_XBOX_CRT_UNSUPPORTED(_ungetch_nolock)
_CRTIMP int __cdecl _ungetch_nolock(__in int _Ch);



#ifndef _WCONIO_DEFINED

/* wide function prototypes, also declared in wchar.h */

#ifndef WEOF
#define WEOF (wint_t)(0xFFFF)
#endif

_XBOX_CRT_UNSUPPORTED(_cgetws_s)
_CRTIMP __checkReturn_wat errno_t __cdecl _cgetws_s(__out_ecount_part(_SizeInWords, *_SizeRead) wchar_t * _Buffer, size_t _SizeInWords, __out size_t * _SizeRead);
#if defined(__cplusplus)
_XBOX_CRT_UNSUPPORTED(_cgetws_s)
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(errno_t, _cgetws_s, __out_ecount_part(_Size, *_Buffer) wchar_t, _Buffer, size_t *, _Size)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(wchar_t *, _CRTIMP, _cgetws, __out_z wchar_t, _Buffer)
_XBOX_CRT_UNSUPPORTED(_getwch)
_CRTIMP __checkReturn wint_t __cdecl _getwch(void);
_XBOX_CRT_UNSUPPORTED(_getwche)
_CRTIMP __checkReturn wint_t __cdecl _getwche(void);
_XBOX_CRT_UNSUPPORTED(_putwch)
_CRTIMP __checkReturn wint_t __cdecl _putwch(wchar_t _WCh);
_XBOX_CRT_UNSUPPORTED(_ungetwch)
_CRTIMP __checkReturn wint_t __cdecl _ungetwch(wint_t _WCh);
_XBOX_CRT_UNSUPPORTED(_cputws)
_CRTIMP __checkReturn_opt int __cdecl _cputws(__in_z const wchar_t * _String);
_XBOX_CRT_UNSUPPORTED(_cwprintf)
_CRTIMP __checkReturn_opt int __cdecl _cwprintf(__in_z __format_string const wchar_t * _Format, ...);
_XBOX_CRT_UNSUPPORTED(_cwprintf_s)
_CRTIMP __checkReturn_opt int __cdecl _cwprintf_s(__in_z __format_string const wchar_t * _Format, ...);
_XBOX_CRT_UNSUPPORTED_INSECURE(_cwscanf, _cwscanf_s)
_CRTIMP __checkReturn_opt int __cdecl _cwscanf(__in_z __format_string const wchar_t * _Format, ...);
_XBOX_CRT_UNSUPPORTED_INSECURE(_cwscanf_l, _cwscanf_s_l)
_CRTIMP __checkReturn_opt int __cdecl _cwscanf_l(__in_z __format_string const wchar_t * _Format, __in_opt _locale_t _Locale, ...);
_XBOX_CRT_UNSUPPORTED(_cwscanf_s)
_CRTIMP __checkReturn_opt int __cdecl _cwscanf_s(__in_z __format_string const wchar_t * _Format, ...);
_XBOX_CRT_UNSUPPORTED(_cwscanf_s_l)
_CRTIMP __checkReturn_opt int __cdecl _cwscanf_s_l(__in_z __format_string const wchar_t * _Format, __in_opt _locale_t _Locale, ...);
_XBOX_CRT_UNSUPPORTED(_vcwprintf)
_CRTIMP __checkReturn_opt int __cdecl _vcwprintf(__in_z __format_string const wchar_t *_Format, va_list _ArgList);
_XBOX_CRT_UNSUPPORTED(_vcwprintf_s)
_CRTIMP __checkReturn_opt int __cdecl _vcwprintf_s(__in_z __format_string const wchar_t *_Format, va_list _ArgList);

_XBOX_CRT_UNSUPPORTED(_cwprintf_p)
_CRTIMP __checkReturn_opt int __cdecl _cwprintf_p(__in_z __format_string const wchar_t * _Format, ...);
_XBOX_CRT_UNSUPPORTED(_vcwprintf_p)
_CRTIMP __checkReturn_opt int __cdecl _vcwprintf_p(__in_z __format_string const wchar_t*  _Format, va_list _ArgList);

_XBOX_CRT_UNSUPPORTED(_cwprintf_l)
_CRTIMP int __cdecl _cwprintf_l(__in_z const __format_string wchar_t * _Format, __in_opt _locale_t _Locale, ...);
_XBOX_CRT_UNSUPPORTED(_cwprintf_s_l)
_CRTIMP int __cdecl _cwprintf_s_l(__in_z __format_string const wchar_t * _Format, __in_opt _locale_t _Locale, ...);
_XBOX_CRT_UNSUPPORTED(_vcwprintf_l)
_CRTIMP int __cdecl _vcwprintf_l(__in_z __format_string const wchar_t *_Format, __in_opt _locale_t _Locale, va_list _ArgList);
_XBOX_CRT_UNSUPPORTED(_vcwprintf_s_l)
_CRTIMP int __cdecl _vcwprintf_s_l(__in_z __format_string const wchar_t * _Format, __in_opt _locale_t _Locale, va_list _ArgList);
_XBOX_CRT_UNSUPPORTED(_cwprintf_p_l)
_CRTIMP int __cdecl _cwprintf_p_l(__in_z __format_string const wchar_t * _Format, __in_opt _locale_t _Locale, ...);
_XBOX_CRT_UNSUPPORTED(_vcwprintf_p_l)
_CRTIMP int __cdecl _vcwprintf_p_l(__in_z __format_string const wchar_t * _Format, __in_opt _locale_t _Locale, va_list _ArgList);

_XBOX_CRT_UNSUPPORTED(_putwch_nolock)
_CRTIMP __checkReturn_opt wint_t __cdecl _putwch_nolock(wchar_t _WCh);
_XBOX_CRT_UNSUPPORTED(_getwch_nolock)
_CRTIMP __checkReturn wint_t __cdecl _getwch_nolock(void);
_XBOX_CRT_UNSUPPORTED(_getwche_nolock)
_CRTIMP __checkReturn wint_t __cdecl _getwche_nolock(void);
_XBOX_CRT_UNSUPPORTED(_ungetwch_nolock)
_CRTIMP __checkReturn_opt wint_t __cdecl _ungetwch_nolock(wint_t _WCh);


#define _WCONIO_DEFINED
#endif  /* _WCONIO_DEFINED */

#if     !__STDC__

/* Non-ANSI names for compatibility */

#pragma warning(push)
#pragma warning(disable: 4141) /* Using deprecated twice */ 
_XBOX_CRT_UNSUPPORTED_NONSTDC_INSECURE(cgets, _cgets, _cgets_s)
_CRTIMP __checkReturn_opt char * __cdecl cgets(__out_ecount_z(*_Buffer+2) char * _Buffer);
#pragma warning(pop)
_XBOX_CRT_UNSUPPORTED_NONSTDC(cprintf, _cprintf)
_CRTIMP __checkReturn_opt int __cdecl cprintf(__in_z __format_string const char * _Format, ...);
_XBOX_CRT_UNSUPPORTED_NONSTDC(cputs, _cputs)
_CRTIMP __checkReturn_opt int __cdecl cputs(__in_z const char * _Str);
_XBOX_CRT_UNSUPPORTED_NONSTDC(cscanf, _cscanf)
_CRTIMP __checkReturn_opt int __cdecl cscanf(__in_z __format_string const char * _Format, ...);
_XBOX_CRT_UNSUPPORTED_NONSTDC(getch, _getch)
_CRTIMP __checkReturn int __cdecl getch(void);
_XBOX_CRT_UNSUPPORTED_NONSTDC(getche, _getche)
_CRTIMP __checkReturn int __cdecl getche(void);
_XBOX_CRT_UNSUPPORTED_NONSTDC(kbhit, _kbhit)
_CRTIMP __checkReturn int __cdecl kbhit(void);
_XBOX_CRT_UNSUPPORTED_NONSTDC(putch, _putch)
_CRTIMP __checkReturn_opt int __cdecl putch(int _Ch);
_XBOX_CRT_UNSUPPORTED_NONSTDC(ungetch, _ungetch)
_CRTIMP __checkReturn_opt int __cdecl ungetch(int _Ch);

#endif  /* __STDC__ */

#ifdef  __cplusplus
}
#endif

#endif // XBSTRICT

#endif  /* _INC_CONIO */
