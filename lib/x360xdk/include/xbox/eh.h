/***
*eh.h - User include file for exception handling.
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       User include file for exception handling.
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif

#include <crtdefs.h>

#ifndef _INC_EH
#define _INC_EH
#ifndef RC_INVOKED
#ifdef  _MSC_VER
/* Currently, all MS C compilers for Win32 platforms default to 8 byte 
 * alignment.
 */
#pragma pack(push,_CRT_PACKING)
#endif  /* _MSC_VER */

#ifndef __cplusplus
#error "eh.h is only for C++!"
#endif

/* terminate_handler is the standard name; terminate_function is supported for historical reasons */
typedef void (__cdecl *terminate_function)();
typedef void (__cdecl *terminate_handler)();
typedef void (__cdecl *unexpected_function)();
typedef void (__cdecl *unexpected_handler)();


struct _EXCEPTION_POINTERS;
typedef void (__cdecl *_se_translator_function)(unsigned int, struct _EXCEPTION_POINTERS*);

_CRTIMP __declspec(noreturn) void __cdecl terminate(void);
_CRTIMP void __cdecl unexpected(void);

_CRTIMP int __cdecl _is_exception_typeof(__in const type_info &_Type, __in struct _EXCEPTION_POINTERS * _ExceptionPtr);

/* only __clrcall versions provided by the MRT exist in pure */
_CRTIMP terminate_function __cdecl set_terminate(__in_opt terminate_function _NewPtFunc);
extern "C" _CRTIMP terminate_function __cdecl _get_terminate(void);
_CRTIMP unexpected_function __cdecl set_unexpected(__in_opt unexpected_function _NewPtFunc);
extern "C" _CRTIMP unexpected_function __cdecl _get_unexpected(void);

/* set_se_translator cannot be a managed implementation, and so cannot be called from _M_CEE_PURE code */
_CRTIMP _se_translator_function __cdecl _set_se_translator(__in_opt _se_translator_function _NewPtFunc);
_CRTIMP bool __cdecl __uncaught_exception();

/*
 * These overload helps in resolving NULL
 */


#ifdef  _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */
#endif /* RC_INVOKED */
#endif  /* _INC_EH */
