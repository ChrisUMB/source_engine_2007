/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       pix.h
 *  Content:    Xenon PIX include file
 *
 ****************************************************************************/

#ifndef _PIX_H_
#define _PIX_H_

// the standalone PIXBeginNamedEvent/PIXEndNamedEvent/PIXSetMarker APIs 
// compile to nothing on retail builds and on x86 builds
//
// if this changes, USE_D3D_PIX_METHODS in d3d9.h will probably also have
// to be changed accordingly because that is used for the corresponding
// PixBeginNamedEvent/PixEndNamedEvent/PixSetMarker D3D device methods
#if ((defined(_DEBUG) || DBG || (defined(PROFILE) && !defined(FASTCAP)) || defined(PROFILE_BUILD)) && !defined(i386) && !defined(_PREFAST_))
#define USE_PIX
#endif

// the maximum string length for any of the PIX APIs is 32
#define MAX_PIX_STRING_LENGTH 32


#ifdef  __cplusplus
extern "C" {
#endif

void WINAPI PIXAddNamedCounter( float value, const char *szName, ...);

#if defined(USE_PIX)

    void WINAPI PIXBeginNamedEvent_Copy_NoVarArgs( DWORD Color, const char *pFormat );
    void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, ...);
    void WINAPI PIXBeginNamedEvent_Copy_Float( DWORD Color, const char *pFormat, float Float );
    void WINAPI PIXBeginNamedEvent_Copy_Double( DWORD Color, const char *pFormat, double Double );
    void WINAPI PIXBeginNamedEvent_Copy_Int( DWORD Color, const char *pFormat, int Int );
    void WINAPI PIXBeginNamedEvent_Copy_Int64( DWORD Color, const char *pFormat, INT64 Int64 );

    #if defined(__cplusplus) && !defined(PIX_NO_OVERLOAD)
    
        extern "C++"
        {
            // The following inline routines special-case the most common var-args
            // parameter types.  They're only available with C++ since they use
            // function overloading.
                    
            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, float Float )
            {
                PIXBeginNamedEvent_Copy_Float( Color, pFormat, Float );
            }
            
            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, double Double )
            {
                PIXBeginNamedEvent_Copy_Double( Color, pFormat, Double );
            }
            
            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, char Char )
            {
                PIXBeginNamedEvent_Copy_Int( Color, pFormat, (int)Char );
            }

            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, short Short )
            {
                PIXBeginNamedEvent_Copy_Int( Color, pFormat, (int)Short );
            }

            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, int Int )
            {
                PIXBeginNamedEvent_Copy_Int( Color, pFormat, Int );
            }
            
            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, long Long )
            {
                PIXBeginNamedEvent_Copy_Int( Color, pFormat, (int)Long );
            }
            
            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, INT64 Int64 )
            {
                PIXBeginNamedEvent_Copy_Int64( Color, pFormat, Int64 );
            }

            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, unsigned char Char )
            {
                PIXBeginNamedEvent_Copy_Int( Color, pFormat, (int)Char );
            }

            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, unsigned short Short )
            {
                PIXBeginNamedEvent_Copy_Int( Color, pFormat, (int)Short );
            }

            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, UINT Uint )
            {
                PIXBeginNamedEvent_Copy_Int( Color, pFormat, (int)Uint );
            }
            
            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, ULONG Ulong )
            {
                PIXBeginNamedEvent_Copy_Int( Color, pFormat, (int)Ulong );
            }

            __forceinline void WINAPI PIXBeginNamedEvent_Copy_VarArgs( DWORD Color, const char *pFormat, UINT64 Uint64 )
            {
                PIXBeginNamedEvent_Copy_Int64( Color, pFormat, (INT64)Uint64 );
            }
        }

    #endif

    // This macro decides whether any varargs are passed in by looking at the
    // stringified varargs parameters and seeing if the resulting string is
    // empty or not.

    #define PIXHasVarArgs(szString, ...) ("" #__VA_ARGS__[0] != 0)

    // This macro implements various compile-time optimized flavors of the
    // PIXBeginNamedEvent API.
    #define PIXBeginNamedEvent(Color, pFormat, ...)   \
        (PIXHasVarArgs(pFormat, __VA_ARGS__) ? \
            (PIXBeginNamedEvent_Copy_VarArgs(Color, pFormat, __VA_ARGS__), 0) : \
            (PIXBeginNamedEvent_Copy_NoVarArgs(Color, pFormat), 0))

    void WINAPI PIXEndNamedEvent( );
    void WINAPI PIXSetMarker( DWORD Color, const char *szName, ...);
    void WINAPI PIXNameThread( const char *szName );
    
#else // USE_PIX
    
    // eliminate these APIs in Release builds
    #define PIXBeginNamedEvent 0&&
    #define PIXEndNamedEvent()
    #define PIXSetMarker 0&&
    #define PIXNameThread 0&&

    // don't show warnings about expressions with no effect
    #pragma warning(disable:4548)		
    #pragma warning(disable:4555)
    
#endif // USE_PIX

#ifdef  __cplusplus
}
#endif

#endif // _PIX_H_
