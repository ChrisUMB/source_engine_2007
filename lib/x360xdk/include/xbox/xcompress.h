/************************************************************************
*                                                                       *
*   xcompress.h -- This module defines the Xbox Compression APIs        *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/
#pragma once

#ifndef _XCOMPRESS_H_
#define _XCOMPRESS_H_

#ifndef XBOXAPI
#define XBOXAPI
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#pragma warning(push)
#pragma warning(disable: 4200) // zero-sized array

typedef enum _XMEMCODEC_TYPE
{
    XMEMCODEC_DEFAULT =                     0,
    XMEMCODEC_LZX =                         1
} XMEMCODEC_TYPE;

/*
 * Data compression flags
 */

#define XMEMCOMPRESS_STREAM                 0x00000001
 
/*
 * Data compression functions
 */

typedef VOID*                               XMEMCOMPRESSION_CONTEXT;

XBOXAPI
HRESULT 
WINAPI 
XMemCreateCompressionContext(
    IN      XMEMCODEC_TYPE                  CodecType,
    IN      CONST VOID*                     pCodecParams,
    IN      DWORD                           Flags,
    OUT     XMEMCOMPRESSION_CONTEXT*        pContext
    );

XBOXAPI
XMEMCOMPRESSION_CONTEXT
WINAPI 
XMemInitializeCompressionContext(
    IN      XMEMCODEC_TYPE                  CodecType,
    IN      CONST VOID*                     pCodecParams,
    IN      DWORD                           Flags,
    IN OUT  VOID*                           pContextData,
    IN      SIZE_T                          ContextSize
    );

XBOXAPI
VOID
WINAPI 
XMemDestroyCompressionContext(
    IN OUT  XMEMCOMPRESSION_CONTEXT         Context
    );

XBOXAPI
SIZE_T
WINAPI 
XMemGetCompressionContextSize(
    IN      XMEMCODEC_TYPE                  CodecType,
    IN      CONST VOID*                     pCodecParams,
    IN      DWORD                           Flags
    );

XBOXAPI
HRESULT 
WINAPI 
XMemResetCompressionContext(
    IN      XMEMCOMPRESSION_CONTEXT         Context);

XBOXAPI
HRESULT 
WINAPI 
XMemCompress(
    IN      XMEMCOMPRESSION_CONTEXT         Context,
    OUT     VOID*                           pDestination,
    IN OUT  SIZE_T*                         pDestSize,
    IN      CONST VOID*                     pSource,
    IN      SIZE_T                          SrcSize
    );

XBOXAPI
HRESULT 
WINAPI 
XMemCompressStream(
    IN      XMEMCOMPRESSION_CONTEXT         Context,
    OUT     VOID*                           pDestination,
    IN OUT  SIZE_T*                         pDestSize,
    IN      CONST VOID*                     pSource,
    IN OUT  SIZE_T*                         pSrcSize
    );

/*
 * Data decompression functions
 */

typedef VOID*                               XMEMDECOMPRESSION_CONTEXT;

XBOXAPI
HRESULT 
WINAPI 
XMemCreateDecompressionContext(
    IN      XMEMCODEC_TYPE                  CodecType,
    IN      CONST VOID*                     pCodecParams,
    IN      DWORD                           Flags,
    OUT     XMEMDECOMPRESSION_CONTEXT*      pContext
    );

XBOXAPI
XMEMDECOMPRESSION_CONTEXT
WINAPI 
XMemInitializeDecompressionContext(
    IN      XMEMCODEC_TYPE                  CodecType,
    IN      CONST VOID*                     pCodecParams,
    IN      DWORD                           Flags,
    IN OUT  VOID*                           pContextData,
    IN      SIZE_T                          ContextSize
    );

XBOXAPI
VOID
WINAPI 
XMemDestroyDecompressionContext(
    IN OUT  XMEMDECOMPRESSION_CONTEXT       Context
    );

XBOXAPI
SIZE_T
WINAPI 
XMemGetDecompressionContextSize(
    IN      XMEMCODEC_TYPE                  CodecType,
    IN      CONST VOID*                     pCodecParams,
    IN      DWORD                           Flags
    );

XBOXAPI
HRESULT 
WINAPI 
XMemResetDecompressionContext(
    IN      XMEMDECOMPRESSION_CONTEXT       Context);

XBOXAPI
HRESULT 
WINAPI 
XMemDecompress(
    IN      XMEMDECOMPRESSION_CONTEXT       Context,
    OUT     VOID*                           pDestination,
    IN OUT  SIZE_T*                         pDestSize,
    IN      CONST VOID*                     pSource,
    IN      SIZE_T                          SrcSize
    );

XBOXAPI
HRESULT 
WINAPI 
XMemDecompressStream(
    IN      XMEMDECOMPRESSION_CONTEXT       Context,
    OUT     VOID*                           pDestination,
    IN OUT  SIZE_T*                         pDestSize,
    IN      CONST VOID*                     pSource,
    IN OUT  SIZE_T*                         pSrcSize
    );

/*
 * LZX codec for lossless compression
 */

typedef struct _XMEMCODEC_PARAMETERS_LZX
{
    DWORD Flags;
    DWORD WindowSize;
    DWORD CompressionPartitionSize;
} XMEMCODEC_PARAMETERS_LZX;

#define XCOMPRESS_LZX_BLOCK_SIZE            (32 * 1024)
#define XCOMPRESS_LZX_BLOCK_GROWTH_SIZE_MAX 6150

/*
 * Error codes
 */

#define XMCDERR_MOREDATA                    _HRESULT_TYPEDEF_(0x81DE2001)

/*
 * Transparent decoding
 */

#if defined(_M_PPCBE)

typedef struct _XTDECODER_PARAMETERS
{
    XMEMCODEC_TYPE CodecType;
    CONST VOID* pCodecParams;
    DWORD Flags;
    DWORD HardwareThread;
    INT ThreadPriority;
    DWORD SegmentSizeLimit;
    DWORD PendingReadLimit;
    DWORD OpenFileLimit;
    DWORD TranslationCacheSize;
} XTDECODER_PARAMETERS;

/*
 * Transparent decoding flags
 */

#define XTDECODER_NO_READ_ALIGNMENT_ENFORCEMENT     0x00000001

/*
 * Transparent decoding functions
 */

XBOXAPI
HRESULT
WINAPI
XFileEnableTransparentDecompression(
    IN CONST XTDECODER_PARAMETERS*          pDecoderParams
    );

XBOXAPI
VOID
WINAPI
XFileDisableTransparentDecompression();

#endif

/*
 * Compression file headers
 */

#define XCOMPRESS_FILE_IDENTIFIER_LZXTDECODE        0x0FF512ED
#define XCOMPRESS_FILE_IDENTIFIER_LZXNATIVE         0x0FF512EE

#define XCOMPRESS_SET_FILE_VERSION(Major, Minor)    ((((Major) & 0xFF) << 8) | ((Minor) & 0xFF))
#define XCOMPRESS_GET_FILE_VERSION_MAJOR(Version)   (((Version) >> 8) & 0xFF)
#define XCOMPRESS_GET_FILE_VERSION_MINOR(Version)   ((Version) & 0xFF)

#define XCOMPRESS_LZXTDECODE_VERSION_MAJOR          1
#define XCOMPRESS_LZXTDECODE_VERSION_MINOR          0

#define XCOMPRESS_LZXNATIVE_VERSION_MAJOR           1
#define XCOMPRESS_LZXNATIVE_VERSION_MINOR           1

typedef struct _XCOMPRESS_FILE_HEADER
{
    DWORD                                   Identifier;
    WORD                                    Version;
    WORD                                    Reserved;
} XCOMPRESS_FILE_HEADER;

typedef struct _XCOMPRESS_FILE_HEADER_LZXNATIVE
{
    XCOMPRESS_FILE_HEADER                   Common;
    DWORD                                   ContextFlags;
    XMEMCODEC_PARAMETERS_LZX                CodecParams;
    DWORD                                   UncompressedSizeHigh;
    DWORD                                   UncompressedSizeLow;
    DWORD                                   CompressedSizeHigh;
    DWORD                                   CompressedSizeLow;
    DWORD                                   UncompressedBlockSize;
    DWORD                                   CompressedBlockSizeMax;
} XCOMPRESS_FILE_HEADER_LZXNATIVE;

typedef struct _XCOMPRESS_BLOCK_HEADER_LZXNATIVE
{
    DWORD                                   CompressedBlockSize;
    BYTE                                    pCompressedData[0];
} XCOMPRESS_BLOCK_HEADER_LZXNATIVE;

#pragma warning(pop)

#ifdef __cplusplus
}
#endif

#endif /* _XCOMPRESS_H_ */
