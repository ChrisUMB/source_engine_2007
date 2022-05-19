/*==========================================================================;
 *
 *  Copyright (C) 2000 - 2003 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       xgraphics.h
 *  Content:    Xbox graphics helper utilities
 *
 ****************************************************************************/

#ifndef _XGRAPHICS_H_
#define _XGRAPHICS_H_

#include <xboxmath.h>
#if !defined(_X86_) && !defined(_X64_)
#include <PPCIntrinsics.h>
#endif

#define XGCONST extern CONST DECLSPEC_SELECTANY
#if !defined(_X86_) && !defined(_X64_) && !defined(_PREFAST_)
    #define XGRESTRICT __restrict
#else
    #define XGRESTRICT
#endif

#if DBG
    VOID XGRIP(PCHAR Format, ...);

    #define XGASSERT(cond) { if (!(cond)) XGRIP("Assertion failure: %s\n", #cond); }
#else
    #define XGASSERT(cond) {}
#endif

/****************************************************************************
 *
 * Texture memory layout.
 *
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _XGPOINT3D
{
    LONG x;
    LONG y;
    LONG z;
} XGPOINT3D;

#define XGTDESC_TILED           0x0001
#define XGTDESC_PACKED          0x0002
#define XGTDESC_BORDERED        0x0008

typedef struct _XGTEXTURE_DESC
{
    D3DRESOURCETYPE     ResourceType;
    UINT                Width;
    UINT                Height;
    UINT                Depth;
    D3DFORMAT           Format;
    UINT                RowPitch;
    UINT                SlicePitch;
    UINT                BitsPerPixel;
    UINT                WidthInBlocks;
    UINT                HeightInBlocks;
    UINT                DepthInBlocks;
    UINT                BytesPerBlock;
    INT                 ExpBias;
    DWORD               Flags;
    D3DMULTISAMPLE_TYPE MultiSampleType;
} XGTEXTURE_DESC;

typedef struct _XGMIPTAIL_DESC
{
    D3DRESOURCETYPE     ResourceType;
    UINT                Width;
    UINT                Height;
    UINT                Depth;
    D3DFORMAT           Format;
    UINT                RowPitch;
    UINT                SlicePitch;
    UINT                BitsPerPixel;
    UINT                WidthInBlocks;
    UINT                HeightInBlocks;
    UINT                DepthInBlocks;
    UINT                BytesPerBlock;
    INT                 ExpBias;
    DWORD               Flags;
    UINT                BaseLevel;
    UINT                Size;
} XGMIPTAIL_DESC;

/*
 * Texture information routines.
 */

// Returns the GPU data format of a D3DFORMAT

__forceinline DWORD WINAPI XGGetGpuFormat(
    D3DFORMAT Format)
{
    return (DWORD)((Format & D3DFORMAT_TEXTUREFORMAT_MASK) >> D3DFORMAT_TEXTUREFORMAT_SHIFT);
}

// Returns whether a texture format is tiled or not.

__forceinline BOOL WINAPI XGIsTiledFormat(
    D3DFORMAT Format
    )
{
    return (Format & D3DFORMAT_TILED_MASK) != 0;
}

// Returns whether a texture format is compressed or not.

__forceinline BOOL WINAPI XGIsCompressedFormat(
    D3DFORMAT Format
    )
{
    switch (XGGetGpuFormat(Format))
    {
        case GPUTEXTUREFORMAT_DXT1:
        case GPUTEXTUREFORMAT_DXT1_AS_16_16_16_16:
        case GPUTEXTUREFORMAT_DXT2_3:
        case GPUTEXTUREFORMAT_DXT2_3_AS_16_16_16_16:
        case GPUTEXTUREFORMAT_DXT4_5:
        case GPUTEXTUREFORMAT_DXT4_5_AS_16_16_16_16:
        case GPUTEXTUREFORMAT_DXN:
        case GPUTEXTUREFORMAT_DXT3A:
        case GPUTEXTUREFORMAT_DXT5A:
        case GPUTEXTUREFORMAT_CTX1:
        case GPUTEXTUREFORMAT_DXT3A_AS_1_1_1_1:
        case GPUTEXTUREFORMAT_Y1_Cr_Y0_Cb_REP:
        case GPUTEXTUREFORMAT_Cr_Y1_Cb_Y0_REP:
        case GPUTEXTUREFORMAT_32_AS_8:
        case GPUTEXTUREFORMAT_32_AS_8_INTERLACED:
        case GPUTEXTUREFORMAT_32_AS_8_8:
            return TRUE;
    }

    return FALSE;
}

// Map of GPU data format to pixel pitch in bits

XGCONST BYTE g_XGTextureFormatBitsPerPixel[] =
{
    1,   // GPUTEXTUREFORMAT_1_REVERSE
    1,   // GPUTEXTUREFORMAT_1
    8,   // GPUTEXTUREFORMAT_8
    16,  // GPUTEXTUREFORMAT_1_5_5_5
    16,  // GPUTEXTUREFORMAT_5_6_5
    16,  // GPUTEXTUREFORMAT_6_5_5
    32,  // GPUTEXTUREFORMAT_8_8_8_8
    32,  // GPUTEXTUREFORMAT_2_10_10_10
    8,   // GPUTEXTUREFORMAT_8_A
    8,   // GPUTEXTUREFORMAT_8_B
    16,  // GPUTEXTUREFORMAT_8_8
    16,  // GPUTEXTUREFORMAT_Cr_Y1_Cb_Y0_REP
    16,  // GPUTEXTUREFORMAT_Y1_Cr_Y0_Cb_REP
    32,  // GPUTEXTUREFORMAT_16_16_EDRAM
    32,  // GPUTEXTUREFORMAT_8_8_8_8_A
    16,  // GPUTEXTUREFORMAT_4_4_4_4
    32,  // GPUTEXTUREFORMAT_10_11_11
    32,  // GPUTEXTUREFORMAT_11_11_10
    4,   // GPUTEXTUREFORMAT_DXT1
    8,   // GPUTEXTUREFORMAT_DXT2_3
    8,   // GPUTEXTUREFORMAT_DXT4_5
    64,  // GPUTEXTUREFORMAT_16_16_16_16_EDRAM
    32,  // GPUTEXTUREFORMAT_24_8
    32,  // GPUTEXTUREFORMAT_24_8_FLOAT
    16,  // GPUTEXTUREFORMAT_16
    32,  // GPUTEXTUREFORMAT_16_16
    64,  // GPUTEXTUREFORMAT_16_16_16_16
    16,  // GPUTEXTUREFORMAT_16_EXPAND
    32,  // GPUTEXTUREFORMAT_16_16_EXPAND
    64,  // GPUTEXTUREFORMAT_16_16_16_16_EXPAND
    16,  // GPUTEXTUREFORMAT_16_FLOAT
    32,  // GPUTEXTUREFORMAT_16_16_FLOAT
    64,  // GPUTEXTUREFORMAT_16_16_16_16_FLOAT
    32,  // GPUTEXTUREFORMAT_32
    64,  // GPUTEXTUREFORMAT_32_32
    128, // GPUTEXTUREFORMAT_32_32_32_32
    32,  // GPUTEXTUREFORMAT_32_FLOAT
    64,  // GPUTEXTUREFORMAT_32_32_FLOAT
    128, // GPUTEXTUREFORMAT_32_32_32_32_FLOAT
    8,   // GPUTEXTUREFORMAT_32_AS_8
    16,  // GPUTEXTUREFORMAT_32_AS_8_8
    16,  // GPUTEXTUREFORMAT_16_MPEG
    32,  // GPUTEXTUREFORMAT_16_16_MPEG
    8,   // GPUTEXTUREFORMAT_8_INTERLACED
    8,   // GPUTEXTUREFORMAT_32_AS_8_INTERLACED
    16,  // GPUTEXTUREFORMAT_32_AS_8_8_INTERLACED
    16,  // GPUTEXTUREFORMAT_16_INTERLACED
    16,  // GPUTEXTUREFORMAT_16_MPEG_INTERLACED
    32,  // GPUTEXTUREFORMAT_16_16_MPEG_INTERLACED
    8,   // GPUTEXTUREFORMAT_DXN
    32,  // GPUTEXTUREFORMAT_8_8_8_8_AS_16_16_16_16
    4,   // GPUTEXTUREFORMAT_DXT1_AS_16_16_16_16
    8,   // GPUTEXTUREFORMAT_DXT2_3_AS_16_16_16_16
    8,   // GPUTEXTUREFORMAT_DXT4_5_AS_16_16_16_16
    32,  // GPUTEXTUREFORMAT_2_10_10_10_AS_16_16_16_16
    32,  // GPUTEXTUREFORMAT_10_11_11_AS_16_16_16_16
    32,  // GPUTEXTUREFORMAT_11_11_10_AS_16_16_16_16
    96,  // GPUTEXTUREFORMAT_32_32_32_FLOAT
    4,   // GPUTEXTUREFORMAT_DXT3A
    4,   // GPUTEXTUREFORMAT_DXT5A
    4,   // GPUTEXTUREFORMAT_CTX1
    4,   // GPUTEXTUREFORMAT_DXT3A_AS_1_1_1_1
    32,  // GPUTEXTUREFORMAT_8_8_8_8_GAMMA_EDRAM
    32,  // GPUTEXTUREFORMAT_2_10_10_10_FLOAT_EDRAM
};

// Returns the number of bits per texel of a GPU texture format.

__inline UINT WINAPI XGBitsPerPixelFromGpuFormat(
    DWORD GpuFormat
    )
{
#if DBG
    if (GpuFormat >= (sizeof(g_XGTextureFormatBitsPerPixel) / sizeof(g_XGTextureFormatBitsPerPixel[0])) ||
        g_XGTextureFormatBitsPerPixel[GpuFormat] == 0)
    {
        // Invalid format
        __debugbreak();
    }
#endif

    return g_XGTextureFormatBitsPerPixel[GpuFormat];
}

// Returns the number of bits per texel of a format.

__inline UINT WINAPI XGBitsPerPixelFromFormat(
    D3DFORMAT Format
    )
{
    GPUTEXTUREFORMAT GpuFormat = (GPUTEXTUREFORMAT)XGGetGpuFormat(Format);

    return XGBitsPerPixelFromGpuFormat(GpuFormat);
}

// Returns the number of bytes per texel of a format.

__inline UINT WINAPI XGBytesPerPixelFromFormat(
    D3DFORMAT Format
    )
{
    GPUTEXTUREFORMAT GpuFormat = (GPUTEXTUREFORMAT)XGGetGpuFormat(Format);
    UINT BitsPerPixel = XGBitsPerPixelFromGpuFormat(GpuFormat);

    return BitsPerPixel >> 3;
}

// Calculate the smallest multiple that is equal to or greater than the 
// specified value.

__inline UINT XGNextMultiple(
    UINT Value, 
    UINT Multiple
    )
{
    return ((Value + Multiple - 1) / Multiple) * Multiple;
}

// Calculate the size of the EDRAM allocation needed for the specified
// surface, in units of EDRAM tiles.

__inline UINT WINAPI XGSurfaceSize(
    UINT Width, 
    UINT Height, 
    D3DFORMAT Format, 
    D3DMULTISAMPLE_TYPE MultiSample
    )
{
    GPUTEXTUREFORMAT GpuFormat = (GPUTEXTUREFORMAT)XGGetGpuFormat(Format);
    DWORD bytesPerFragment = 4;
    DWORD sizeInBytes;
    DWORD sizeInTiles;

    // Compute the surface size in fragments:

    DWORD widthInFragments = Width;
    DWORD heightInFragments = Height;

    if (MultiSample >= D3DMULTISAMPLE_2_SAMPLES)
        heightInFragments *= 2;
    if (MultiSample == D3DMULTISAMPLE_4_SAMPLES)
        widthInFragments *= 2;

    // EDRAM memory has to be allocated with a granularity that is the
    // dimension of an EDRAM tile:

    widthInFragments = XGNextMultiple(widthInFragments, GPU_EDRAM_TILE_WIDTH_IN_FRAGMENTS);
    heightInFragments = XGNextMultiple(heightInFragments, GPU_EDRAM_TILE_HEIGHT_IN_FRAGMENTS);

    // Determine if this is a 64-bit render target format:

    if ((GpuFormat == GPUTEXTUREFORMAT_16_16_16_16_EDRAM) ||
        (GpuFormat == GPUTEXTUREFORMAT_16_16_16_16_FLOAT) ||
        (GpuFormat == GPUTEXTUREFORMAT_32_32_FLOAT))
    {
        bytesPerFragment = 8;
    }

    // Compute the total size of the allocation:

    sizeInBytes = widthInFragments * heightInFragments * bytesPerFragment;

    // Note that we're guaranteed that the total size in bytes is a multiple of
    // the tile size:

    sizeInTiles = sizeInBytes / GPU_EDRAM_TILE_SIZE;

    return (UINT)sizeInTiles;
}

// Calculate the size of the hierarchical Z allocation needed for the specified
// surface, in units of hierarchical Z tiles.

__inline UINT WINAPI XGHierarchicalZSize(
    UINT Width, 
    UINT Height, 
    D3DMULTISAMPLE_TYPE MultiSample
    )
{
    // Compute the hierarchical Z size in fragments:

    DWORD widthInFragments = Width;
    DWORD heightInFragments = Height;

    if (MultiSample >= D3DMULTISAMPLE_2_SAMPLES)
        heightInFragments *= 2;
    if (MultiSample == D3DMULTISAMPLE_4_SAMPLES)
        widthInFragments *= 2;

    // Hierarchical Z memory has to be allocated with a granularity that is the
    // dimension of a hierarchical Z tile:

    widthInFragments = XGNextMultiple(widthInFragments, GPU_HIERARCHICAL_Z_TILE_WIDTH_IN_FRAGMENTS);
    heightInFragments = XGNextMultiple(heightInFragments, GPU_HIERARCHICAL_Z_TILE_HEIGHT_IN_FRAGMENTS);

    return widthInFragments * heightInFragments / GPU_HIERARCHICAL_Z_TILE_SIZE;
}

// Return the description of a texture, cube texture, or volume texture.  This
// description contains memory footprint and tiling information in addition to
// the information that could typically be retrieved from GetLevelDesc, LockRect,
// etc.

VOID WINAPI XGGetTextureDesc(
    D3DBaseTexture* pTexture,   // Texture to describe
    UINT            Level,      // Mip level to describe
    XGTEXTURE_DESC* pDesc       // Structure to be filled with texture description
    );

// Return the description of a surface

__inline VOID WINAPI XGGetSurfaceDesc(
    D3DSurface*     pSurface,
    XGTEXTURE_DESC* pDesc
    )
{
    XGGetTextureDesc((D3DBaseTexture*)pSurface, 0, pDesc);
}

// Return the description of a volume

__inline VOID WINAPI XGGetVolumeDesc(
    D3DVolume*      pVolume,
    XGTEXTURE_DESC* pDesc
    )
{
    XGGetTextureDesc((D3DBaseTexture*)pVolume, 0, pDesc);
}

// Return memory layout information on a given texture

typedef struct _XGLAYOUT_REGION
{
    UINT StartOffset;
    UINT EndOffset;
} XGLAYOUT_REGION;

VOID WINAPI XGGetTextureLayout(
    D3DBaseTexture*  pTexture,             // Texture to examine
    UINT*            pBaseData,            // Memory address or offset to the base level data in the texture
    UINT*            pBaseSize,            // Allocation size of the base level data in the texture
    XGLAYOUT_REGION* pBaseRegionList,      // Pointer to a list of layout regions that will be filled with a 
                                           // set of isolated memory ranges that may potentially be referenced 
                                           // by fetches into the base texture allocation
    UINT*            pBaseRegionListCount, // IN: Size of the base region list buffer in entries; OUT: Number 
                                           // of used memory regions written to the base region list
    UINT             BaseRegionAlignment,  // Power-of-two alignment applied to the base memory regions
    UINT*            pMipData,             // Memory address or offset to the mip level data in the texture
    UINT*            pMipSize,             // Allocation size of the mip level data in the texture
    XGLAYOUT_REGION* pMipRegionList,       // Pointer to a list of layout regions that will be filled with a 
                                           // set of isolated memory ranges that may potentially be referenced 
                                           // by fetches into the mip texture allocation
    UINT*            pMipRegionListCount,  // IN: Size of the mip region list buffer in entries; OUT: Number 
                                           // of used memory regions written to the mip region list
    UINT             MipRegionAlignment    // Power-of-two alignment applied to the mip memory regions
    );

// Returns whether a texture packs small mip levels

__forceinline BOOL WINAPI XGIsPackedTexture(
    D3DBaseTexture* pTexture
    )
{
    return pTexture->Format.PackedMips != 0;
}

// Returns whether a texture includes a border

__forceinline BOOL WINAPI XGIsBorderTexture(
    D3DBaseTexture* pTexture
    )
{
    return pTexture->Format.BorderSize != 0;
}

// Return the offset in bytes to the start of the given mip level.
// This offset may be added to either the base address (for level 0 
// or in cases where the mip address is NULL) or to the mip address 
// to obtain a pointer to the level data.

UINT WINAPI XGGetMipLevelOffset(
    D3DBaseTexture* pTexture,   // Texture containing the mip level
    UINT            ArrayIndex, // Cubemap face or texture array index
    UINT            Level       // Mip level index
    );

// Return the description of a packed mip tail.

VOID WINAPI XGGetMipTailDesc(
    D3DBaseTexture* pTexture,   // Texture containing the tail to describe
    XGMIPTAIL_DESC* pDesc       // Structure to be filled with tail description
    );

// Return the index of the first packed level in a mip map.

UINT WINAPI XGGetMipTailBaseLevel(
    UINT Width,                 // Width of the texture
    UINT Height,                // Height of the texture
    BOOL Border                 // TRUE if the texture has a border, FALSE if it does not
    );

// Return the offset in bytes from the base address of the packed mip tail
// to the base address of the given mip level.  If the given level is
// not packed, an offset of 0 is returned.

UINT WINAPI XGGetMipTailLevelOffset(
    UINT  Width,                // Width of the texture
    UINT  Height,               // Height of the texture
    UINT  Depth,                // Depth of the texture
    UINT  Level,                // Mip level of the texture
    DWORD GpuFormat,            // Gpu format of the texture
    BOOL  Tiled,                // TRUE if the texture is tiled, FALSE if linear
    BOOL  Border                // TRUE if the texture has a border, FALSE if it does not
    );

// Return the texel dimensions of a compression block in the given format.
// If the format is not compressed, the size of a block is 1 x 1 texels.

VOID WINAPI XGGetBlockDimensions(
    DWORD GpuFormat,            // Gpu format of the compression block
    UINT* pWidth,               // Out: Width of a block
    UINT* pHeight               // Out: Height of a block
    );

/*
 * Address translation routines.
 */

//------------------------------------------------------------------------
// Calculate the log2 of a texel pitch which is less than or equal to 16 
// and a power of 2.

__forceinline UINT WINAPI XGLog2LE16(
    UINT TexelPitch)
{
    XGASSERT((TexelPitch > 0) && 
             (TexelPitch <= 16) && 
             (TexelPitch & (TexelPitch - 1)) == 0);

#if defined(_X86_) || defined(_X64_)
    return (TexelPitch >> 2) + ((TexelPitch >> 1) >> (TexelPitch >> 2));
#else
    return 31 - _CountLeadingZeros(TexelPitch);
#endif
}

//------------------------------------------------------------------------
// Translate the address of a surface texel/block from 2D array coordinates into 
// a tiled memory offset measured in texels/blocks.

__inline UINT WINAPI XGAddress2DTiledOffset(
    UINT x,             // x coordinate of the texel/block
    UINT y,             // y coordinate of the texel/block
    UINT Width,         // Width of the image in texels/blocks
    UINT TexelPitch     // Size of an image texel/block in bytes
    )
{
    UINT AlignedWidth;
    UINT LogBpp;
    UINT Macro;
    UINT Micro;
    UINT Offset;

    XGASSERT(Width <= 8192); // Width in memory must be less than or equal to 8K texels
    XGASSERT(x < Width);

    AlignedWidth = (Width + 31) & ~31;
    LogBpp       = XGLog2LE16(TexelPitch);
    Macro        = ((x >> 5) + (y >> 5) * (AlignedWidth >> 5)) << (LogBpp + 7);
    Micro        = (((x & 7) + ((y & 6) << 2)) << LogBpp);
    Offset       = Macro + ((Micro & ~15) << 1) + (Micro & 15) + ((y & 8) << (3 + LogBpp)) + ((y & 1) << 4);

    return (((Offset & ~511) << 3) + ((Offset & 448) << 2) + (Offset & 63) + 
            ((y & 16) << 7) + (((((y & 8) >> 2) + (x >> 3)) & 3) << 6)) >> LogBpp;
}

//------------------------------------------------------------------------
// Determine the amount of memory occupied by a tiled 2D surface to the 
// granularity of a matte (subtile).  The returned size refers to the
// largest tiled offset potentially referenced in the surface and is 
// measured in texels/blocks.

UINT WINAPI XGAddress2DTiledExtent(
    UINT Width,         // Width of the image in texels/blocks
    UINT Height,        // Height of the image in texels/blocks
    UINT TexelPitch     // Size of an image texel/block in bytes
    );


//------------------------------------------------------------------------
// Translate the address of a volume texel/block from 3D array coordinates into 
// a tiled memory offset measured in texels/blocks.

__inline UINT WINAPI XGAddress3DTiledOffset(
    UINT x,             // x coordinate of the texel/block
    UINT y,             // y coordinate of the texel/block
    UINT z,             // z coordinate of the texel/block
    UINT Width,         // Width of a volume slice in texels/blocks
    UINT Height,        // Height of a volume slice in texels/blocks
    UINT TexelPitch     // Size of a volume texel/block in bytes
    )
{
    UINT AlignedWidth;
    UINT AlignedHeight;
    UINT LogBpp;
    UINT Macro;
    UINT Micro;
    UINT64 Offset1;
    UINT64 Offset2;

    XGASSERT(Width <= 2048); // Width in memory must be less than or equal to 2K texels
    XGASSERT(Height <= 2048); // Height in memory must be less than or equal to 2K texels
    XGASSERT(x < Width);
    XGASSERT(y < Height);

    AlignedWidth  = (Width + 31) & ~31;
    AlignedHeight = (Height + 31) & ~31;
    LogBpp        = XGLog2LE16(TexelPitch);
    Macro         = ((z >> 2) * (AlignedHeight >> 4) + (y >> 4)) * (AlignedWidth >> 5) + (x >> 5);
    Micro         = (((y & 6) << 2) + (x & 7)) << LogBpp;
    Offset1       = (UINT64)(((UINT64)Macro << (8 + LogBpp)) + ((Micro & ~15) << 1) + (Micro & 15) + ((z & 3) << (6 + LogBpp)) + ((y & 1) << 4));
    Offset2       = (UINT64)(((z >> 2) + (y >> 3)) & 1);

    return (UINT)((((Offset1 & ~511ull) << 3ull) + ((Offset1 & 448ull) << 2ull) + (Offset1 & 63ull) + 
            (Offset2 << 11ull) + ((((Offset2 << 1ull) + (x >> 3)) & 3ull) << 6ull)) >> LogBpp);
}

//------------------------------------------------------------------------
// Determine the amount of memory occupied by a tiled 3D volume to the 
// granularity of a matte (subtile). The returned size refers to the
// largest tiled offset potentially referenced in the volume and is 
// measured in texels/blocks.

UINT WINAPI XGAddress3DTiledExtent(
    UINT Width,         // Width of a volume slice in texels/blocks
    UINT Height,        // Height of a volume slice in texels/blocks
    UINT Depth,         // Depth of a volume slice in texels/blocks
    UINT TexelPitch     // Size of a volume texel/block in bytes
    );

//------------------------------------------------------------------------
// Translate the address of a surface texel/block from a tiled memory offset 
// into a 2D array x coordinate measured in texels/blocks.

__inline UINT WINAPI XGAddress2DTiledX(
    UINT Offset,        // Tiled memory offset in texels/blocks
    UINT Width,         // Width of the image in texels/blocks
    UINT TexelPitch     // Size of an image texel/block in bytes
    )
{
    UINT AlignedWidth;
    UINT LogBpp;
    UINT OffsetB;
    UINT OffsetT;
    UINT OffsetM;
    UINT Tile;
    UINT Macro;
    UINT Micro;
    UINT MacroX;

    XGASSERT(Width <= 8192); // Width in memory must be less than or equal to 8K texels

    AlignedWidth = (Width + 31) & ~31;

    LogBpp       = XGLog2LE16(TexelPitch);
    OffsetB      = Offset << LogBpp;
    OffsetT      = ((OffsetB & ~4095) >> 3) + ((OffsetB & 1792) >> 2) + (OffsetB & 63);
    OffsetM      = OffsetT >> (7 + LogBpp);

    MacroX       = ((OffsetM % (AlignedWidth >> 5)) << 2);
    Tile         = ((((OffsetT >> (5 + LogBpp)) & 2) + (OffsetB >> 6)) & 3);
    Macro        = (MacroX + Tile) << 3;
    Micro        = ((((OffsetT >> 1) & ~15) + (OffsetT & 15)) & ((TexelPitch << 3) - 1)) >> LogBpp;

    return Macro + Micro;
}

//------------------------------------------------------------------------
// Translate the address of a surface texel/block from a tiled memory offset 
// into a 2D array y coordinate measured in texels/blocks.

__inline UINT WINAPI XGAddress2DTiledY(
    UINT Offset,        // Tiled memory offset in texels/blocks
    UINT Width,         // Width of the image in texels/blocks
    UINT TexelPitch     // Size of an image texel/block in bytes
    )
{
    UINT AlignedWidth;
    UINT LogBpp;
    UINT OffsetB;
    UINT OffsetT;
    UINT OffsetM;
    UINT Tile;
    UINT Macro;
    UINT Micro;
    UINT MacroY;

    XGASSERT(Width <= 8192); // Width in memory must be less than or equal to 8K texels

    AlignedWidth = (Width + 31) & ~31;

    LogBpp       = XGLog2LE16(TexelPitch);
    OffsetB      = Offset << LogBpp;
    OffsetT      = ((OffsetB & ~4095) >> 3) + ((OffsetB & 1792) >> 2) + (OffsetB & 63);
    OffsetM      = OffsetT >> (7 + LogBpp);

    MacroY       = ((OffsetM / (AlignedWidth >> 5)) << 2);
    Tile         = ((OffsetT >> (6 + LogBpp)) & 1) + (((OffsetB & 2048) >> 10));
    Macro        = (MacroY + Tile) << 3;
    Micro        = ((((OffsetT & (((TexelPitch << 6) - 1) & ~31)) + ((OffsetT & 15) << 1)) >> (3 + LogBpp)) & ~1);

    return Macro + Micro + ((OffsetT & 16) >> 4);
}

//------------------------------------------------------------------------
// Translate the address of a volume texel/block from a tiled memory offset 
// into a 3D array x coordinate measured in texels/blocks.

__inline UINT WINAPI XGAddress3DTiledX(
    UINT Offset,        // Tiled memory offset in texels/blocks
    UINT Width,         // Width of a volume slice in texels/blocks
    UINT Height,        // Height of a volume slice in texels/blocks
    UINT TexelPitch     // Size of a volume texel/block in bytes
    )
{
    UINT AlignedWidth;
    UINT LogBpp;
    UINT OffsetB;
    UINT OffsetT;
    UINT OffsetM;
    UINT Micro;
    UINT Macro;
    UINT Tile;

    XGASSERT(Width <= 2048); // Width in memory must be less than or equal to 2K texels
#if DBG
    XGASSERT(Height <= 2048); // Height in memory must be less than or equal to 2K texels
#else
    Height;
#endif

    AlignedWidth = (Width + 31) & ~31;

    LogBpp       = XGLog2LE16(TexelPitch);
    OffsetB      = Offset << LogBpp;
    OffsetM      = ((Offset >> 11) & (~1 >> LogBpp)) + ((OffsetB & 1024) >> (LogBpp + 10));
    OffsetT      = ((((Offset << LogBpp) & ~4095) >> 3) + (((OffsetB & 1792) >> 2) + (OffsetB & 63))) & ((TexelPitch << 6) - 1);
    Micro        = (((OffsetT & ~31) >> 1) + (OffsetT & 15));

    Macro        = OffsetM % (AlignedWidth >> 5);
    Tile         = (((OffsetB & 2048) >> 10) + (OffsetB >> 6)) & 3;

    return (((Macro << 2) + Tile) << 3) + ((Micro >> LogBpp) & 7);
}

//------------------------------------------------------------------------
// Translate the address of a volume texel/block from a tiled memory offset 
// into a 3D array y coordinate measured in texels/blocks.

__inline UINT WINAPI XGAddress3DTiledY(
    UINT Offset,        // Tiled memory offset in texels/blocks
    UINT Width,         // Width of a volume slice in texels/blocks
    UINT Height,        // Height of a volume slice in texels/blocks
    UINT TexelPitch     // Size of a volume texel/block in bytes
    )
{
    UINT AlignedWidth;
    UINT AlignedHeight;
    UINT LogBpp;
    UINT OffsetB;
    UINT OffsetT;
    UINT OffsetM;
    UINT Micro;
    UINT Macro;
    UINT Tile;
    UINT TileZ;

    XGASSERT(Width <= 2048); // Width in memory must be less than or equal to 2K texels
    XGASSERT(Height <= 2048); // Height in memory must be less than or equal to 2K texels

    AlignedWidth = (Width + 31) & ~31;
    AlignedHeight = (Height + 31) & ~31;

    LogBpp       = XGLog2LE16(TexelPitch);
    OffsetB      = Offset << LogBpp;
    OffsetM      = ((Offset >> 11) & (~1 >> LogBpp)) + ((OffsetB & 1024) >> (LogBpp + 10));
    OffsetT      = ((((Offset << LogBpp) & ~4095) >> 3) + (((OffsetB & 1792) >> 2) + (OffsetB & 63))) & ((TexelPitch << 6) - 1);
    Micro        = (((OffsetT & ~31) >> 1) + (OffsetT & 15));
    TileZ        = (OffsetM << 9) / (AlignedWidth * AlignedHeight);

    Macro        = (OffsetM / (AlignedWidth >> 5)) % (AlignedHeight >> 4);
    Tile         = (((OffsetB & 2048) >> 11) ^ TileZ) & 1;
    Micro        = (((Micro & 15) << 1) + (OffsetT & ~31)) >> (LogBpp + 3);

    return (((Macro << 1) + Tile) << 3) + (Micro & ~1) + ((OffsetT & 16) >> 4);
}

//------------------------------------------------------------------------
// Translate the address of a volume texel/block from a tiled memory offset 
// into a 3D array z coordinate measured in texels/blocks.

__inline UINT WINAPI XGAddress3DTiledZ(
    UINT Offset,        // Tiled memory offset in texels/blocks
    UINT Width,         // Width of a volume slice in texels/blocks
    UINT Height,        // Height of a volume slice in texels/blocks
    UINT TexelPitch     // Size of a volume texel/block in bytes
    )
{
    UINT AlignedWidth;
    UINT AlignedHeight;
    UINT LogBpp;
    UINT OffsetB;
    UINT OffsetM;
    UINT TileZ;

    XGASSERT(Width <= 2048); // Width in memory must be less than or equal to 2K texels
    XGASSERT(Height <= 2048); // Height in memory must be less than or equal to 2K texels

    AlignedWidth = (Width + 31) & ~31;
    AlignedHeight = (Height + 31) & ~31;

    LogBpp       = XGLog2LE16(TexelPitch);
    OffsetB      = Offset << LogBpp;
    OffsetM      = ((Offset >> 11) & (~1 >> LogBpp)) + ((OffsetB & 1024) >> (LogBpp + 10));
    TileZ        = (OffsetM << 9) / (AlignedWidth * AlignedHeight);

    return (((((Offset >> 9) & (~7 >> LogBpp))) + ((OffsetB & 1792) >> (LogBpp + 8))) & 3) + (TileZ << 2);
}

/*
 * Tile conversion routines.
 */

// Tile a subrectangle from a source image into a destination image.  The 
// rectangle, when offset by a given point into the destination, must be 
// completely contained within the destination image (no clipping).
// If pPoint and pRect are both NULL, the source and destination images
// are assumed to have the same dimensions and the entire image is tiled.

VOID WINAPI XGTileSurface(
    VOID*        pDestination, // Base address of the destination (tiled) image
    UINT         Width,        // Width of the destination image
    UINT         Height,       // Height of the destination image
    CONST POINT* pPoint,       // Offset in the destination image to place the tiled rectangle
    CONST VOID*  pSource,      // Base address of the source (linear) image
    UINT         RowPitch,     // Distance in bytes between one row of the source image and the next
    CONST RECT*  pRect,        // Rectangle within the source image to copy
    UINT         TexelPitch    // Size of an image texel/block in bytes
    );

// Untile a subrectangle from a source image into a destination image.
// If pPoint and pRect are both NULL, the source and destination images
// are assumed to have the same dimensions and the entire image is untiled.

VOID WINAPI XGUntileSurface(
    VOID*        pDestination, // Base address of the destination (linear) image
    UINT         RowPitch,     // Distance in bytes between one row of the destination image and the next
    CONST POINT* pPoint,       // Offset in the destination image to place the untiled rectangle
    CONST VOID*  pSource,      // Base address of the source (tiled) image
    UINT         Width,        // Width of the source image
    UINT         Height,       // Height of the source image
    CONST RECT*  pRect,        // Rectangle within the source image to copy
    UINT         TexelPitch    // Size of an image texel/block in bytes
    );

// Tile a box from a source volume into a destination volume.  The 
// box, when offset by a given point into the destination, must be 
// completely contained within the destination volume (no clipping).
// If pPoint and pBox are both NULL, the source and destination volumes
// are assumed to have the same dimensions and the entire volume is tiled.

VOID WINAPI XGTileVolume(
    VOID*            pDestination, // Base address of the destination (tiled) volume
    UINT             Width,        // Width of the destination volume
    UINT             Height,       // Height of the destination volume
    UINT             Depth,        // Depth of the destination volume
    CONST XGPOINT3D* pPoint,       // Offset in the destination volume to place the tiled box
    CONST VOID*      pSource,      // Base address of the source (linear) volume
    UINT             RowPitch,     // Distance in bytes between one row of the source volume and the next
    UINT             SlicePitch,   // Distance in bytes between one slice of the source volume and the next
    CONST D3DBOX*    pBox,         // Box within the source volume to copy
    UINT             TexelPitch    // Size of a volume texel/block in bytes
    );

// Untile a box from a source volume into a destination volume.
// If pPoint and pBox are both NULL, the source and destination volumes
// are assumed to have the same dimensions and the entire volume is untiled.

VOID WINAPI XGUntileVolume(
    VOID*            pDestination, // Base address of the destination (linear) volume
    UINT             RowPitch,     // Distance in bytes between one row of the destination volume and the next
    UINT             SlicePitch,   // Distance in bytes between one slice of the destination volume and the next
    CONST XGPOINT3D* pPoint,       // Offset in the destination volume to place the tiled box
    CONST VOID*      pSource,      // Base address of the source (tiled) volume
    UINT             Width,        // Width of the source volume
    UINT             Height,       // Height of the source volume
    UINT             Depth,        // Depth of the source volume
    CONST D3DBOX*    pBox,         // Box within the source volume to copy
    UINT             TexelPitch    // Size of a volume texel/block in bytes
    );

// Tile a subrectangle from a source image into the level of a destination texture.
// The rectangle, when offset by a given point into the destination, must be 
// completely contained within the destination image (no clipping).
// If pPoint and pRect are both NULL, the source and destination images
// are assumed to have the same dimensions and the entire level is tiled.
// Unlike with the surface tiling functions, tiling directly into individual packed levels is supported.

#define XGTILE_NONPACKED           0x1
#define XGTILE_BORDER              0x2

VOID WINAPI XGTileTextureLevel(
    UINT             Width,        // Width of the texture (base level) in texels (not blocks)
    UINT             Height,       // Height of the texture (base level) in texels (not blocks)
    UINT             Level,        // Mip level of the destination
    DWORD            GpuFormat,    // Gpu format of the texture
    DWORD            Flags,        // Tiling flags (border, non-packed, etc.)
    VOID*            pDestination, // Address of the first texel in the destination (tiled) level
    CONST POINT*     pPoint,       // Offset in the destination level (in texels) to place the tiled image
    CONST VOID*      pSource,      // Address of the source (linear) image
    UINT             RowPitch,     // Distance in bytes between one row of the source image and the next
    CONST RECT*      pRect         // Rect within the source image to copy (in texels)
    );

// Untile a subrectangle from a source texture level into a destination image.
// If pPoint and pRect are both NULL, the source level and destination image
// are assumed to have the same dimensions and the entire level is untiled.
// Untiling directly from individual packed levels is supported.

VOID WINAPI XGUntileTextureLevel(
    UINT             Width,        // Width of the texture (base level) in texels (not blocks)
    UINT             Height,       // Height of the texture (base level) in texels (not blocks)
    UINT             Level,        // Mip level of the destination
    DWORD            GpuFormat,    // Gpu format of the texture
    DWORD            Flags,        // Tiling flags (border, non-packed, etc.)
    VOID*            pDestination, // Base address of the destination (linear) image
    UINT             RowPitch,     // Distance in bytes between one row of the destination image and the next
    CONST POINT*     pPoint,       // Offset in the destination image (in texels) to place the untiled box
    CONST VOID*      pSource,      // Address of the first texel in the source (tiled) level
    CONST RECT*      pRect         // Rect within the source level to copy (in texels)
    );

// Tile a sub-box from a source volume into the level of a destination volume texture.
// The box, when offset by a given point into the destination, must be 
// completely contained within the destination volume (no clipping).
// If pPoint and pBox are both NULL, the source and destination volumes
// are assumed to have the same dimensions and the entire level is tiled.
// Unlike with the volume tiling functions, tiling directly into individual packed levels is supported.

VOID WINAPI XGTileVolumeTextureLevel(
    UINT             Width,        // Width of the volume texture (base level) in texels (not blocks)
    UINT             Height,       // Height of the volume texture (base level) in texels (not blocks)
    UINT             Depth,        // Depth of the volume texture (base level) in texels
    UINT             Level,        // Mip level of the destination
    DWORD            GpuFormat,    // Gpu format of the volume texture
    DWORD            Flags,        // Tiling flags (border, non-packed, etc.)
    VOID*            pDestination, // Address of the first texel in the destination (tiled) level
    CONST XGPOINT3D* pPoint,       // Offset in the destination level (in texels) to place the tiled image
    CONST VOID*      pSource,      // Address of the source (linear) image
    UINT             RowPitch,     // Distance in bytes between one row of the source image and the next
    UINT             SlicePitch,   // Distance in bytes between one slice of the source image and the next
    CONST D3DBOX*    pBox          // Box within the source image to copy (in texels)
    );

// Untile a sub-box from a source volume texture level into a destination volume.
// If pPoint and pBox are both NULL, the source level and destination volume
// are assumed to have the same dimensions and the entire level is untiled.
// Untiling directly from individual packed levels is supported.

VOID WINAPI XGUntileVolumeTextureLevel(
    UINT             Width,        // Width of the volume texture (base level) in texels (not blocks)
    UINT             Height,       // Height of the volume texture (base level) in texels (not blocks)
    UINT             Depth,        // Depth of the volume texture (base level) in texels
    UINT             Level,        // Mip level of the destination
    DWORD            GpuFormat,    // Gpu format of the volume texture
    DWORD            Flags,        // Tiling flags (border, non-packed, etc.)
    VOID*            pDestination, // Base address of the destination (linear) image
    UINT             RowPitch,     // Distance in bytes between one row of the destination image and the next
    UINT             SlicePitch,   // Distance in bytes between one slice of the destination image and the next
    CONST XGPOINT3D* pPoint,       // Offset in the destination image (in texels) to place the untiled box
    CONST VOID*      pSource,      // Address of the first texel in the source (tiled) level
    CONST D3DBOX*    pBox          // Box within the source level to copy (in texels)
    );

/****************************************************************************
 *
 * Texture compression.
 *
 ****************************************************************************/

#define XGCOMPRESS_PREMULTIPLY      0x0001 // Enable DXT2 or DXT4
#define XGCOMPRESS_ALPHADIVIDE      0x0002 // Remove DXT2 or DXT4 premultiplication
#define XGCOMPRESS_YUV_DESTINATION  0x0004 // Store the destination in a YUV format
#define XGCOMPRESS_YUV_SOURCE       0x0008 // Load the source from a YUV format
#define XGCOMPRESS_NO_DITHERING     0x0010 // Do not dither

// Compress a subrectangle from a source image into a destination image.  The 
// rectangle, when offset by a given point into the destination, must be 
// completely contained within the destination image (no clipping).
// If pPoint and pRect are both NULL, the source and destination images
// are assumed to have the same dimensions and the entire image is compressed.

HRESULT WINAPI XGCompressSurface(
    VOID*            pDestination,  // Base address of the destination (compressed) image
    UINT             DstRowPitch,   // Distance in bytes between one row of the destination image and the next
    UINT             Width,         // Width of the destination image in texels
    UINT             Height,        // Height of the destination image in texels
    D3DFORMAT        DstFormat,     // Compressed format of the destination image
    CONST POINT*     pPoint,        // Offset in the destination image to place the compressed rectangle
    CONST VOID*      pSource,       // Base address of the source (uncompressed) image
    UINT             SrcRowPitch,   // Distance in bytes between one row of the source image and the next
    D3DFORMAT        SrcFormat,     // Format of the source image
    CONST RECT*      pRect,         // Rectangle within the source image to compress
    DWORD            Flags,         // Compression flags
    FLOAT            AlphaRef       // Alpha threshold for DXT1 transparency
    );

// Compress a box from a source volume into a destination volume.  The 
// box, when offset by a given point into the destination, must be 
// completely contained within the destination volume (no clipping).
// If pPoint and pBox are both NULL, the source and destination volumes
// are assumed to have the same dimensions and the entire volume is compressed.

HRESULT WINAPI XGCompressVolume(
    VOID*            pDestination,  // Base address of the destination (compressed) volume
    UINT             DstRowPitch,   // Distance in bytes between one row of the destination volume and the next
    UINT             DstSlicePitch, // Distance in bytes between one slice of the destination volume and the next
    UINT             Width,         // Width of the destination volume in texels
    UINT             Height,        // Height of the destination volume in texels
    UINT             Depth,         // Depth of the destination volume in texels
    D3DFORMAT        DstFormat,     // Compressed format of the destination volume
    CONST XGPOINT3D* pPoint,        // Offset in the destination volume to place the compressed box
    CONST VOID*      pSource,       // Base address of the source (uncompressed) volume
    UINT             SrcRowPitch,   // Distance in bytes between one row of the source volume and the next
    UINT             SrcSlicePitch, // Distance in bytes between one slice of the source volume and the next
    D3DFORMAT        SrcFormat,     // Format of the source volume
    CONST D3DBOX*    pBox,          // Box within the source volume to compress
    DWORD            Flags,         // Compression flags
    FLOAT            AlphaRef       // Alpha threshold for DXT1 transparency
    );

/****************************************************************************
 *
 * PTC Texture compression.
 *
 * PTC (Progressive Transform Codec) is a lossy image compression algorithm
 * created by Microsoft Research similar to JPEG. It achieves better 
 * compression ratios with similar image quality.
 *
 ****************************************************************************/
 
// Compression parameters for use with XGPTCCompressSurfaceEx

typedef struct _XGPTC_COMPRESSION_PARAMS
{
    INT              Qs;            // Quantization step, 4..10000000 [default = 100]
                                    // Compression ratio increases for larger Qs
                                    // Compression is lossless for Qs = 0
    INT              Qa;            // Quantization step for alpha, same as Qs
    INT              ColorSpace;    // Color space of input pixels; options are:
                                    // 0 - undefined; channels coded independently
                                    // 1 - RGB     2 - CMY     3 - CMYK
    BOOL             OneBitAlpha;   // Treat alpha channel as a one-bit alpha channel
    INT              Ec;            // Entropy coding mode [default = 1]
                                    // 0 = bit-plane coder, scalable
                                    // 1 = adaptive run-length/Rice, nonscalable, faster
    INT              Eca;           // Entropy coding mode for the alpha channel
    INT              ChunkWidth;    // Encoding chunk width, in # of pixels, 32..5184 [default = 256]
    INT              Bd;            // # of bits to preserve for lossless compression
                                    // when the intput is 16-bits, from 8 to 16
    BOOL             Npp;           // Use non-overlapping transforms [not recommended]; improves
                                    // compression and speed in lossless mode, but precludes mipmap
                                    // decoding.
    LPCSTR           pMeta;	        // Inserts specified string into global metadata area
                                    // of the PTC image (may be NULL)
    LPCSTR           pFrameMeta;    // Inserts specified string into frame metadata area
                                    // of the PTC image (may be NULL)
    
} XGPTC_COMPRESSION_PARAMS;

// Compress a subrectangle from a source image into a destination image. The 
// rectangle must be completely contained within the source image (no clipping).
// If pRect is NULL, the entire source source is compressed. The memory for the
// destination image is allocated using XMemAlloc(). The Qs parameter controls
// the amount of compression. The source format must be linear - no tiling 
// operations will be performed.

HRESULT WINAPI XGPTCCompressSurface(
    VOID**           ppDestination, // Returned base address of the destination (PTC compressed) image
    UINT*            pDstSize,      // Returned size of the desination (PTC compressed) image in bytes
    CONST VOID*      pSource,       // Base address of the source (uncompressed) image
    UINT             SrcRowPitch,   // Distance in bytes between one row of the source image and the next
    UINT             Width,         // Width of the source image in texels
    UINT             Height,        // Height of the source image in texels
    D3DFORMAT        SrcFormat,     // Format of the source image
    CONST RECT*      pRect,         // Rectangle within the source image to compress
    INT              Qs             // Quantization step, 4..10000000 [default = 100]
                                    // Compression ratio increases for larger Qs
                                    // Compression is lossless for Qs = 0
    );

// Compress a subrectangle from a source image into a destination image. The 
// rectangle must be completely contained within the source image (no clipping).
// If pRect is NULL, the entire source source is compressed. The memory for the
// destination image is allocated using XMemAlloc(). The compression parameters 
// control the amount and type of compression. The source format must be linear 
// - no tiling operations will be performed.

HRESULT WINAPI XGPTCCompressSurfaceEx(
    VOID**           ppDestination, // Returned base address of the destination (PTC compressed) image
    UINT*            pDstSize,      // Returned size of the desination (PTC compressed) image in bytes
    CONST VOID*      pSource,       // Base address of the source (uncompressed) image
    UINT             SrcRowPitch,   // Distance in bytes between one row of the source image and the next
    UINT             Width,         // Width of the source image in texels
    UINT             Height,        // Height of the source image in texels
    D3DFORMAT        SrcFormat,     // Format of the source image
    CONST RECT*      pRect,         // Rectangle within the source image to compress
    CONST XGPTC_COMPRESSION_PARAMS* pParams  // Compression parameters
    );

// Free the memory allocated by XGPTCCompressSurface

VOID WINAPI XGPTCFreeMemory(
    VOID*            pMemory  // Address returned from XGPTCCompressSurface
    );

// Decompress a source image into a subrectangle of a destination image. The
// rectangle, when offset by a given point into the destination, must be 
// completely contained within the destination image. If pPoint is NULL, the 
// offset is (0,0). The destination format must be linear - no tiling 
// operations will be performed. For best performance the destination format
// should be the format returned by XGGetPTCImageDesc().

HRESULT WINAPI XGPTCDecompressSurface(
    VOID*            pDestination,  // Base address of the destination (decompressed) image
    INT              DstRowPitch,   // Distance in bytes between one row of the destination image and the next
    UINT             Width,         // Width of the destination image in texels
    UINT             Height,        // Height of the destination image in texels
    D3DFORMAT        DstFormat,     // Format of the destination image
    CONST POINT*     pPoint,        // Offset in the destination image to place the decompressed image
    CONST VOID*      pSource,       // Base address of the source (PTC compressed) image
    UINT             SrcSize        // Size of the source (PTC compressed) image in bytes
    );

// Decompress a subrectangle of the source image into a subrectangle of a destination 
// image. The rectangle, when offset by a given point into the destination, must be 
// completely contained within the destination image. If pPoint is NULL, the 
// offset is (0,0). The destination format must be linear - no tiling 
// operations will be performed. For best performance the destination format
// should be the format returned by XGGetPTCImageDesc(). A mip-level relative to 
// the resolution of the base source image may be specified allowing lower resolution
// image to be decoded more quickly. The rectangle coordinates are in terms of the base
// mip-level.

HRESULT WINAPI XGPTCDecompressSurfaceEx(
    VOID*            pDestination,  // Base address of the destination (decompressed) image
    INT              DstRowPitch,   // Distance in bytes between one row of the destination image and the next
    UINT             Width,         // Width of the destination image in texels
    UINT             Height,        // Height of the destination image in texels
    D3DFORMAT        DstFormat,     // Format of the destination image
    CONST POINT*     pPoint,        // Offset in the destination image to place the decompressed image
    CONST VOID*      pSource,       // Base address of the source (PTC compressed) image
    UINT             SrcSize,       // Size of the source (PTC compressed) image in bytes
    CONST RECT*      pRect,         // Rectangle within the source image to compress
    UINT             MipLevel       // Mip level of the source to decompress (0..4)
    );

// Return the width, height, and format of a PTC compressed image.

HRESULT WINAPI XGGetPTCImageDesc(
    CONST VOID*      pSource,       // Base address of the PTC compressed image
    UINT             SrcSize,       // Size of the PTC compressed image in bytes
    UINT*            pWidth,        // Width of the PTC compressed image in texels
    UINT*            pHeight,       // Height of the PTC compressed image in texels
    D3DFORMAT*       pFormat        // Best format for the PTC compressed image
    );

/****************************************************************************
 *
 * MCT texture compression.
 *
 * MCT is a lossless and lossy image compression algorithm for DXTn, DXN, and
 * CTX1 texture formats.  It provides a higher level of compression than raw 
 * DXT storage with better decode performance relative to PTC.
 *
 ****************************************************************************/

typedef VOID* XGMCTCOMPRESSION_CONTEXT;
typedef VOID* XGMCTDECOMPRESSION_CONTEXT;

// Flags to be used in MCT context initialization:

#define XGMCT_BORDER                                 0x00000008

// MCT compression flags:

#define XGCOMPRESS_MCT_CONTIGUOUS_MIP_LEVELS         0x00010000 // Compress the base and mip levels of a texture into a 
                                                                // single contiguous compressed data set

#define XGCOMPRESS_MCT_NO_ENCODER_RETRAIN            0x00020000 // Do not retrain the encoder (instead relying upon training
                                                                // from a prior texture encoding).  Use of the flag will
                                                                // increase compression performance at some expense to 
                                                                // resulting MCT data size.

// Compression parameters for use with XGMCTCompressTexture and XGMCTQuantizeTexture:

typedef struct _XGMCT_COMPRESSION_PARAMS
{
    FLOAT     Quality;              // Image color/normal quality control (ranges from 1.0 to 100.0, where 100.0 denotes lossless compression)
    UINT      LinearThreshold;      // Mip levels greater in dimension than the threshold will be compressed tiled
    FLOAT     AlphaRef;             // Alpha threshold for DXT1 transparency
    INT       Level;                // Control for compression size vs. speed (ranges from 1 to 5: 1 to maximize speed and 5 to minimize size)
    XGPOINT3D TrainingSampleSpread; // Distance between texture samples taken during training of the endoder
                                    //     (1 to 128 for x and y; 1 to 4 for z)
    FLOAT     AlphaQuality;         // Image alpha quality control (not yet supported)
} XGMCT_COMPRESSION_PARAMS;

// Initialize a compression context that may be used for MCT-encoding textures.

XGMCTCOMPRESSION_CONTEXT WINAPI XGMCTInitializeCompressionContext(
    VOID* pContextData,
    UINT  ContextSize
    );

// Destroy an MCT compression context.

VOID WINAPI XGMCTDestroyCompressionContext(
    XGMCTCOMPRESSION_CONTEXT Context
    );

// Obtain the allocation size required to accomodate an MCT compression context
// capable of encoding a texture of the specified configuration.

UINT WINAPI XGMCTGetCompressionContextSize(
    D3DRESOURCETYPE ResourceType,
    UINT            Width,
    UINT            Height,
    UINT            Depth,
    UINT            LevelCount,
    D3DFORMAT       Format,
    CONST D3DBOX*   pRegion,
    DWORD           Flags,
    CONST XGMCT_COMPRESSION_PARAMS* pMctParams
    );

// Compress a region from a source texture (2d, cube, array, or volume) into 
// encoded base and mip level data sets which may be subsequently decompressed
// into a destination texture constructed of equivalent attributes (dimensions,
// number of mip levels, etc.) but a DXTn, DNX, or CTX1 format.  The source 
// region, when offset by a given point into the destination texture must be 
// completely contained within the texture (no clipping).  If pRegion is NULL, 
// the entire source texture is compressed.  The given region dimensions will 
// be tile-aligned for tiled formats.
//
// Note that an explicit range of mip levels may be selected for the compression
// by setting the minimum and maximum mip levels in the fetch constant of the
// given source texture.

HRESULT WINAPI XGMCTCompressTexture(
    XGMCTCOMPRESSION_CONTEXT Context, // Compression context (use NULL to have a context created automatically)
    VOID*            pDstBaseData,    // Destination address for the compressed base level of the texture
    UINT*            pDstBaseSize,    // In: Allocation size of pBaseData buffer; Out: Size of the compressed base level
    VOID*            pDstMipData,     // Destination address for the compressed mip levels of the texture
    UINT*            pDstMipSize,     // In: Allocation size of pMipData buffer; Out: Size of the compressed mip levels
    D3DFORMAT        DstFormat,       // Format of the destination texture (DXTn, DXN, or CTX1)
    D3DBaseTexture*  pSrcTexture,     // Source texture containing the data to compress
    CONST D3DBOX*    pSrcRegion,      // Region within the source texture to compress
    DWORD            Flags,           // Compression flags
    CONST XGMCT_COMPRESSION_PARAMS* pParams // Compression parameters
    );

// Quantize a region from a source texture (2d, cube, array, or volume) into 
// a matching region offset within a destination texture that is constructed of equivalent 
// attributes (dimensions, number of mip levels, etc.) but a DXTn, DNX, or CTX1 format.  
// The source region, when offset by the given point into the destination texture must be 
// completely contained within the texture (no clipping).  If pRegion is NULL, 
// the entire source texture is quantized.
//
// Note that the destination texture receiving the quantized region will not have any data
// outside the bounds of its individual mip levels modified (to support quantization of paired
// compressed textures).  It is therefore recommended that the texture memory that will
// serve as a quantization destination be explicitly cleared on allocation for the improvement
// of any subsequent lossless compression.

HRESULT WINAPI XGMCTQuantizeTexture(
    XGMCTCOMPRESSION_CONTEXT Context, // Compression context (use NULL to have a context created automatically)
    D3DBaseTexture*  pDstTexture,     // Destination texture containing the quantized result
    CONST XGPOINT3D* pDstPoint,       // Offset in the destination texture to place the quantized region
    D3DBaseTexture*  pSrcTexture,     // Source texture containing the data to quantize
    CONST D3DBOX*    pSrcRegion,      // Region within the source texture to quantize
    DWORD            Flags,           // Compression flags used for the quantization
    CONST XGMCT_COMPRESSION_PARAMS* pParams // Compression parameters for the quantization
    );

// Initialize a context that may be used for decompressing MCT-encoded textures.

XGMCTDECOMPRESSION_CONTEXT WINAPI XGMCTInitializeDecompressionContext(
    VOID* pContextData,
    UINT  ContextSize
    );

// Destroy an MCT decompression context.

VOID WINAPI XGMCTDestroyDecompressionContext(
    XGMCTDECOMPRESSION_CONTEXT Context
    );

// Obtain the allocation size required to accomodate an MCT decompression context
// capable of decoding to a texture of the specified configuration.

UINT WINAPI XGMCTGetDecompressionContextSize(
    D3DRESOURCETYPE ResourceType,
    UINT            Width,
    UINT            Height,
    UINT            Depth,
    UINT            LevelCount,
    D3DFORMAT       Format,
    CONST D3DBOX*   pRegion,
    DWORD           Flags
    );

// Decompress the region contained within the level(s) of a given data set into a 
// destination texture.

HRESULT WINAPI XGMCTDecompressTexture(
    XGMCTDECOMPRESSION_CONTEXT Context, // Decompression context (use NULL to have a context created automatically)
    D3DBaseTexture*  pDstTexture,       // Destination texture
    CONST XGPOINT3D* pDstPoint,         // Offset in the destination texture to place the compressed region
    CONST VOID*      pSrcMctData,       // Address of the data set containing one or more MCT-encoded levels of the texture
    UINT             SrcMctSize,        // Size of the compressed MCT data set
    DWORD            Flags              // Compression flags
    );

// Obtain a description of the texture, the range of mip levels, and the region 
// that was encoded to produce the given MCT data.

VOID WINAPI XGMCTGetDesc(
    CONST VOID*     pMctData,
    UINT            MctSize,
    XGTEXTURE_DESC* pDesc,
    UINT*           pMipLevelCount,
    UINT*           pMinMipLevel,
    UINT*           pMaxMipLevel,
    D3DBOX*         pRegion
    );

// Initialize the header of a texture resource to a type and format compatible 
// with the decompression of an MCT-encoded set of data.

UINT WINAPI XGMCTSetBaseTextureHeader(
    CONST VOID*     pMctData,
    UINT            MctSize,
    DWORD           Usage,
    DWORD           Flags,
    UINT            BaseOffset,
    UINT            MipOffset,
    UINT            Pitch,
    D3DBaseTexture* pTexture,
    UINT*           pBaseSize,
    UINT*           pMipSize
    );

/****************************************************************************
 *
 * Texture conversion.
 *
 ****************************************************************************/

// Copy a subrectangle from a source image into a destination image, converting
// from the source format into the destination format.  The rectangle,
// when offset by a given point into the destination, must be 
// completely contained within the destination image (no clipping).
// If pPoint and pRect are both NULL, the source and destination images
// are assumed to have the same dimensions and the entire image is copied.
// Both source and destination formats must be linear - no tiling operations
// will be performed.  Compressed formats are allowed for both source and
// destination (the XGCOMPRESS_ flags may be used to direct the compression and/or
// decompression).

HRESULT WINAPI XGCopySurface(
    VOID*            pDestination,  // Base address of the destination image
    INT              DstRowPitch,   // Distance in bytes between one row of the destination image and the next
    UINT             Width,         // Width of the destination image in texels
    UINT             Height,        // Height of the destination image in texels
    D3DFORMAT        DstFormat,     // Format of the destination image
    CONST POINT*     pPoint,        // Offset in the destination image to place the copied rectangle
    CONST VOID*      pSource,       // Base address of the source image
    INT              SrcRowPitch,   // Distance in bytes between one row of the source image and the next
    D3DFORMAT        SrcFormat,     // Format of the source image
    CONST RECT*      pRect,         // Rectangle within the source image to copy
    DWORD            Flags,         // Conversion flags
    FLOAT            Threshold);    // Threshold for 1 bit components

// Copy a box from a source volume into a destination volume, converting from
// the source format into the destination format.  The box, when offset
// by a given point into the destination, must be completely contained within 
// the destination volume (no clipping).  If pPoint and pBox are both NULL, the 
// source and destination volumes are assumed to have the same dimensions 
// and the entire volume is copied.

HRESULT WINAPI XGCopyVolume(
    VOID*            pDestination,  // Base address of the destination volume
    INT              DstRowPitch,   // Distance in bytes between one row of the destination volume and the next
    INT              DstSlicePitch, // Distance in bytes between one slice of the destination volume and the next
    UINT             Width,         // Width of the destination volume in texels
    UINT             Height,        // Height of the destination volume in texels
    UINT             Depth,         // Depth of the destination volume in texels
    D3DFORMAT        DstFormat,     // Format of the destination volume
    CONST XGPOINT3D* pPoint,        // Offset in the destination volume to place the copied box
    CONST VOID*      pSource,       // Base address of the source volume
    INT              SrcRowPitch,   // Distance in bytes between one row of the source volume and the next
    INT              SrcSlicePitch, // Distance in bytes between one slice of the source volume and the next
    D3DFORMAT        SrcFormat,     // Format of the source volume
    CONST D3DBOX*    pBox,          // Box within the source volume to copy
    DWORD            Flags,         // Conversion flags
    FLOAT            Threshold);    // Threshold for 1 bit components

/****************************************************************************
 *
 * Endian reversals.
 *
 ****************************************************************************/

// Functions to perform endian reversals on given data:  These routines do not 
// support endian swaps between closely overlapped source and destination memory, 
// where the memory addresses are closer to one another than the data size of the
// reversal being peformed (without being equal).  For instance, a reversal
// using XGENDIAN_8IN32 could be performed on source and destination memory 
// addresses that are either equal (i.e. in place) or separated by at least
// 32 bits.

// IMPORTANT NOTE: These routines are provided for resource bundling tools and
// development time conversions (secondarily, as an aid in early resource porting).
// They should not be used at runtime in a final build.

#define XGENDIANTYPE_DATA_SIZE_MASK                 0xFFFF0000
#define XGENDIANTYPE_DATA_SIZE_SHIFT                16

#define XGENDIANTYPE_ELEMENT_SIZE_MASK              0x0000FFFF
#define XGENDIANTYPE_ELEMENT_SIZE_SHIFT             0

#define MAKE_XGENDIANTYPE(ElementSize, DataSize)    (((ElementSize) << XGENDIANTYPE_ELEMENT_SIZE_SHIFT) | \
                                                        ((DataSize) << XGENDIANTYPE_DATA_SIZE_SHIFT))

#define XGENDIANTYPE_SET(ElementSize, DataSize)     ((XGENDIANTYPE)(MAKE_XGENDIANTYPE((ElementSize), (DataSize))))
#define XGENDIANTYPE_GET_DATA_SIZE(Type)            (((Type) & XGENDIANTYPE_DATA_SIZE_MASK) >> XGENDIANTYPE_DATA_SIZE_SHIFT)
#define XGENDIANTYPE_GET_ELEMENT_SIZE(Type)         (((Type) & XGENDIANTYPE_ELEMENT_SIZE_MASK) >> XGENDIANTYPE_ELEMENT_SIZE_SHIFT)

// Predefined endian swap types (custom types may be defined with XGENDIANTYPE_SET using power-of-two sizes).

typedef enum 
{
    XGENDIAN_NONE                                   = MAKE_XGENDIANTYPE(0, 0),
    XGENDIAN_8IN16                                  = MAKE_XGENDIANTYPE(1, 2),
    XGENDIAN_8IN32                                  = MAKE_XGENDIANTYPE(1, 4),
    XGENDIAN_16IN32                                 = MAKE_XGENDIANTYPE(2, 4),
    XGENDIAN_8IN64                                  = MAKE_XGENDIANTYPE(1, 8),
    XGENDIAN_16IN64                                 = MAKE_XGENDIANTYPE(2, 8),
    XGENDIAN_32IN64                                 = MAKE_XGENDIANTYPE(4, 8),
    XGENDIAN_8IN128                                 = MAKE_XGENDIANTYPE(1, 16),
    XGENDIAN_16IN128                                = MAKE_XGENDIANTYPE(2, 16),
    XGENDIAN_32IN128                                = MAKE_XGENDIANTYPE(4, 16),
    XGENDIAN_64IN128                                = MAKE_XGENDIANTYPE(8, 16),
} XGENDIANTYPE;

// Endian reverse the elements of a single block of data.

VOID WINAPI XGEndianSwapData(
    VOID*               pDestination, 
    CONST VOID*         pSource,
    XGENDIANTYPE        SwapType
    );

// Endian reverse the elements of an array of data blocks.

VOID WINAPI XGEndianSwapMemory(
    VOID*               pDestination, 
    CONST VOID*         pSource, 
    XGENDIANTYPE        SwapType, 
    INT                 Stride, 
    UINT                Count
    );

// Endian reverse the elements of an array of composite data.  This may be used to 
// swap the elements of an array of structures composed of heterogenous data types.
// For instance a structure composed of an unsigned integer and an unsigned short
// could be endian reversed by defining a type list of two entries: XGENDIAN_8IN32
// and XGENDIAN_8IN16.

VOID WINAPI XGEndianSwapCompositeMemory(
    VOID*               pDestination, 
    CONST VOID*         pSource, 
    CONST XGENDIANTYPE* pTypeList, 
    UINT                TypeCount, 
    INT                 Stride, 
    UINT                SwapCount
    );

// Endian reverse the texel data contained in a surface resource (based on the texel format).

VOID WINAPI XGEndianSwapSurface(
    VOID*               pDestination, 
    UINT                RowPitchDst, 
    CONST VOID*         pSource, 
    UINT                RowPitchSrc, 
    UINT                Width, 
    UINT                Height, 
    D3DFORMAT           Format
    ); 

// Endian reverse the texel data contained in a volume resource (based on the texel format).

VOID WINAPI XGEndianSwapVolume(
    VOID*               pDestination, 
    UINT                RowPitchDst, 
    UINT                SlicePitchDst, 
    CONST VOID*         pSource, 
    UINT                RowPitchSrc, 
    UINT                SlicePitchSrc, 
    UINT                Width, 
    UINT                Height, 
    UINT                Depth, 
    D3DFORMAT           Format
    );

// Endian reverse the vertex elements in a vertex buffer resource.  The vertex elements are
// identified by an array of D3DVERTEXELEMENT9 structures and referenced by a stream index.
// In this way, a single array of vertex elements defined for multiple vertex buffers (and used
// in the construction of a vertex declaration) may be used to endian reverse all of the 
// vertex buffers by simply changing the stream index.

VOID WINAPI XGEndianSwapVertexBuffer(
    VOID*               pDestination, 
    CONST VOID*         pSource, 
    D3DVERTEXELEMENT9*  pElementList, 
    WORD                StreamIndex, 
    UINT                Stride, 
    UINT                VertexCount
    );

// Endian reverse the indices within an index buffer resource.

VOID WINAPI XGEndianSwapIndexBuffer(
    VOID*               pDestination, 
    CONST VOID*         pSource, 
    D3DFORMAT           Format, 
    UINT                IndexCount
    );

// Endian reverse the header of an IDirect3DSurface9 resource.

__inline VOID WINAPI XGEndianSwapSurfaceHeader(
    IDirect3DSurface9* pSurface)
{
    XGEndianSwapMemory(pSurface, pSurface, XGENDIAN_8IN32, sizeof(DWORD), sizeof(D3DSurface) / sizeof(DWORD));
}

// Endian reverse the header of an IDirect3DTexture9 resource.

__inline VOID WINAPI XGEndianSwapTextureHeader(
    IDirect3DTexture9* pTexture)
{
    XGEndianSwapMemory(pTexture, pTexture, XGENDIAN_8IN32, sizeof(DWORD), sizeof(D3DTexture) / sizeof(DWORD));
}

// Endian reverse the header of an IDirect3DArrayTexture9 resource.

__inline VOID WINAPI XGEndianSwapArrayTextureHeader(
    IDirect3DArrayTexture9* pTexture)
{
    XGEndianSwapMemory(pTexture, pTexture, XGENDIAN_8IN32, sizeof(DWORD), sizeof(D3DArrayTexture) / sizeof(DWORD));
}

// Endian reverse the header of an IDirect3DCubeTexture9 resource.

__inline VOID WINAPI XGEndianSwapCubeTextureHeader(
    IDirect3DCubeTexture9* pTexture)
{
    XGEndianSwapMemory(pTexture, pTexture, XGENDIAN_8IN32, sizeof(DWORD), sizeof(D3DCubeTexture) / sizeof(DWORD));
}

// Endian reverse the header of an IDirect3DVolumeTexture9 resource.

__inline VOID WINAPI XGEndianSwapVolumeTextureHeader(
    IDirect3DVolumeTexture9* pTexture)
{
    XGEndianSwapMemory(pTexture, pTexture, XGENDIAN_8IN32, sizeof(DWORD), sizeof(D3DVolumeTexture) / sizeof(DWORD));
}

// Endian reverse the header of an IDirect3DLineTexture9 resource.

__inline VOID WINAPI XGEndianSwapLineTextureHeader(
    IDirect3DLineTexture9* pTexture)
{
    XGEndianSwapMemory(pTexture, pTexture, XGENDIAN_8IN32, sizeof(DWORD), sizeof(D3DLineTexture) / sizeof(DWORD));
}

// Endian reverse the header of an IDirect3DVertexBuffer9 resource.

__inline VOID WINAPI XGEndianSwapVertexBufferHeader(
    IDirect3DVertexBuffer9* pVertexBuffer)
{
    XGEndianSwapMemory(pVertexBuffer, pVertexBuffer, XGENDIAN_8IN32, sizeof(DWORD), sizeof(D3DVertexBuffer) / sizeof(DWORD));
}

// Endian reverse the header of an IDirect3DIndexBuffer9 resource.

__inline VOID WINAPI XGEndianSwapIndexBufferHeader(
    IDirect3DIndexBuffer9* pIndexBuffer)
{
    XGEndianSwapMemory(pIndexBuffer, pIndexBuffer, XGENDIAN_8IN32, sizeof(DWORD), sizeof(D3DIndexBuffer) / sizeof(DWORD));
}

// Endian reverse the header of an IDirect3DConstantBuffer9 resource.

__inline VOID WINAPI XGEndianSwapConstantBufferHeader(
    IDirect3DConstantBuffer9* pConstantBuffer)
{
    XGEndianSwapMemory(pConstantBuffer, pConstantBuffer, XGENDIAN_8IN32, sizeof(DWORD), sizeof(D3DConstantBuffer) / sizeof(DWORD));
}

/****************************************************************************
 *
 * Resource header initialization.
 *
 ****************************************************************************/

// For texture, cube texture, and volume texture header initialization,
// the BaseOffset and MipOffset parameters are used to provide offsets to the 
// base mip level data and remaining mip level data (if any), respectively 
// for the texture.  These offsets are later applied to base memory addresses 
// given in a subsequent call to XGOffsetResourceAddress or 
// XGOffsetMipTextureAddress.  However, BaseOffset and MipOffset could also 
// be used to set explicit memory addresses during header initialization
// with no subsequent offset required.

// When the MipOffset parameter is set to XGHEADER_CONTIGUOUS_MIP_OFFSET,
// the calculated size of the base mip level will be added to the value 
// given in the BaseOffset parameter and the sum will be set as the offset 
// for the remaining mip levels.  The MipOffset parameter is ignored for 
// textures with a single mip level.

// The total memory size required to hold the texel data (including all
// mip levels) is returned from the texture initialization functions.  
// The size of the highest resolution mip level is returned separately in 
// the pBaseSize parameter and the size of the remaining mip levels is 
// returned in pMipSize.

#define XGHEADER_CONTIGUOUS_MIP_OFFSET          0xFFFFFFFF

#define XGHEADEREX_NONPACKED                    0x1
#define XGHEADEREX_BORDER                       0x2

// Initialize the header of an EDRAM surface resource and return the size of
// the EDRAM allocation required for the specified surface in units of EDRAM tiles.

UINT WINAPI XGSetSurfaceHeader(
    UINT                    Width,
    UINT                    Height,
    D3DFORMAT               Format,
    D3DMULTISAMPLE_TYPE     MultiSampleType,
    CONST D3DSURFACE_PARAMETERS* pParameters,
    IDirect3DSurface9*      pSurface,
    UINT*                   pHierarchicalZSize
    );

// Initialize the header of a 2D texture resource.  The Pitch parameter may be 
// used to set the stride for textures with a single mip level.  The value 
// provided must conform to the alignment restrictions for the specific
// texture to be initialized.  A Pitch value of zero causes the default 
// (minimum) pitch calculated for the texture to be used.

UINT WINAPI XGSetTextureHeader(
    UINT                    Width,
    UINT                    Height,
    UINT                    Levels,
    DWORD                   Usage,
    D3DFORMAT               Format,
    D3DPOOL                 Pool,
    UINT                    BaseOffset,
    UINT                    MipOffset,
    UINT                    Pitch,
    IDirect3DTexture9*      pTexture,
    UINT*                   pBaseSize,
    UINT*                   pMipSize
    );

UINT WINAPI XGSetTextureHeaderEx(
    UINT                    Width,
    UINT                    Height,
    UINT                    Levels,
    DWORD                   Usage,
    D3DFORMAT               Format,
    INT                     ExpBias,
    DWORD                   Flags,
    UINT                    BaseOffset,
    UINT                    MipOffset,
    UINT                    Pitch,
    IDirect3DTexture9*      pTexture,
    UINT*                   pBaseSize,
    UINT*                   pMipSize
    );

// Initialize a pair of interleaved compressed 2D texture resources that
// will occupy a shared memory space in order to conserve the amount required.

UINT WINAPI XGSetTextureHeaderPair(
    UINT                    BaseOffset,
    UINT                    MipOffset,
    UINT                    Width1,
    UINT                    Height1,
    UINT                    Levels1,
    DWORD                   Usage1,
    D3DFORMAT               Format1,
    INT                     ExpBias1,
    DWORD                   Flags1,
    UINT                    Pitch1,
    IDirect3DTexture9*      pTexture1,
    UINT                    Width2,
    UINT                    Height2,
    UINT                    Levels2,
    DWORD                   Usage2,
    D3DFORMAT               Format2,
    INT                     ExpBias2,
    DWORD                   Flags2,
    UINT                    Pitch2,
    IDirect3DTexture9*      pTexture2,
    UINT*                   pBaseSize,
    UINT*                   pMipSize
    );

// Initialize the header of a line (1D) texture resource.

UINT WINAPI XGSetLineTextureHeader(
    UINT                    Width,
    UINT                    Levels,
    DWORD                   Usage,
    D3DFORMAT               Format,
    D3DPOOL                 Pool,
    UINT                    BaseOffset,
    UINT                    MipOffset,
    IDirect3DLineTexture9*  pTexture,
    UINT*                   pBaseSize,
    UINT*                   pMipSize
    );

UINT WINAPI XGSetLineTextureHeaderEx(
    UINT                    Width,
    UINT                    Levels,
    DWORD                   Usage,
    D3DFORMAT               Format,
    INT                     ExpBias,
    DWORD                   Flags,
    UINT                    BaseOffset,
    UINT                    MipOffset,
    IDirect3DLineTexture9*  pTexture,
    UINT*                   pBaseSize,
    UINT*                   pMipSize
    );

// Initialize the header of a cube texture resource.

UINT WINAPI XGSetCubeTextureHeader(
    UINT                    EdgeLength,
    UINT                    Levels,
    DWORD                   Usage,
    D3DFORMAT               Format,
    D3DPOOL                 Pool,
    UINT                    BaseOffset,
    UINT                    MipOffset,
    IDirect3DCubeTexture9*  pCubeTexture,
    UINT*                   pBaseSize,
    UINT*                   pMipSize
    );

UINT WINAPI XGSetCubeTextureHeaderEx(
    UINT                    EdgeLength,
    UINT                    Levels,
    DWORD                   Usage,
    D3DFORMAT               Format,
    INT                     ExpBias,
    DWORD                   Flags,
    UINT                    BaseOffset,
    UINT                    MipOffset,
    IDirect3DCubeTexture9*  pCubeTexture,
    UINT*                   pBaseSize,
    UINT*                   pMipSize
    );

// Initialize a pair of interleaved compressed cube texture resources that
// will occupy a shared memory space in order to conserve the amount required.

UINT WINAPI XGSetCubeTextureHeaderPair(
    UINT                    BaseOffset,
    UINT                    MipOffset,
    UINT                    EdgeLength1,
    UINT                    Levels1,
    DWORD                   Usage1,
    D3DFORMAT               Format1,
    INT                     ExpBias1,
    DWORD                   Flags1,
    IDirect3DTexture9*      pCubeTexture1,
    UINT                    EdgeLength2,
    UINT                    Levels2,
    DWORD                   Usage2,
    D3DFORMAT               Format2,
    INT                     ExpBias2,
    DWORD                   Flags2,
    IDirect3DTexture9*      pCubeTexture2,
    UINT*                   pBaseSize,
    UINT*                   pMipSize
    );

// Initialize the header of an array texture resource.

UINT WINAPI XGSetArrayTextureHeader(
    UINT                    Width,
    UINT                    Height,
    UINT                    ArraySize,
    UINT                    Levels,
    DWORD                   Usage,
    D3DFORMAT               Format,
    D3DPOOL                 Pool,
    UINT                    BaseOffset,
    UINT                    MipOffset,
    UINT                    Pitch,
    IDirect3DArrayTexture9* pArrayTexture,
    UINT*                   pBaseSize,
    UINT*                   pMipSize
    );

UINT WINAPI XGSetArrayTextureHeaderEx(
    UINT                    Width,
    UINT                    Height,
    UINT                    ArraySize,
    UINT                    Levels,
    DWORD                   Usage,
    D3DFORMAT               Format,
    INT                     ExpBias,
    DWORD                   Flags,
    UINT                    BaseOffset,
    UINT                    MipOffset,
    UINT                    Pitch,
    IDirect3DArrayTexture9* pArrayTexture,
    UINT*                   pBaseSize,
    UINT*                   pMipSize
    );

// Initialize a pair of interleaved compressed array texture resources that
// will occupy a shared memory space in order to conserve the amount required.

UINT WINAPI XGSetArrayTextureHeaderPair(
    UINT                    BaseOffset,
    UINT                    MipOffset,
    UINT                    Width1,
    UINT                    Height1,
    UINT                    ArraySize1,
    UINT                    Levels1,
    DWORD                   Usage1,
    D3DFORMAT               Format1,
    INT                     ExpBias1,
    DWORD                   Flags1,
    UINT                    Pitch1,
    IDirect3DTexture9*      pArrayTexture1,
    UINT                    Width2,
    UINT                    Height2,
    UINT                    ArraySize2,
    UINT                    Levels2,
    DWORD                   Usage2,
    D3DFORMAT               Format2,
    INT                     ExpBias2,
    DWORD                   Flags2,
    UINT                    Pitch2,
    IDirect3DTexture9*      pArrayTexture2,
    UINT*                   pBaseSize,
    UINT*                   pMipSize
    );

// Initialize the header of a volume texture resource.

UINT WINAPI XGSetVolumeTextureHeader(
    UINT                     Width,
    UINT                     Height,
    UINT                     Depth,
    UINT                     Levels,
    DWORD                    Usage,
    D3DFORMAT                Format,
    D3DPOOL                  Pool,
    UINT                     BaseOffset,
    UINT                     MipOffset,
    IDirect3DVolumeTexture9* pVolumeTexture,
    UINT*                    pBaseSize,
    UINT*                    pMipSize
    );

UINT WINAPI XGSetVolumeTextureHeaderEx(
    UINT                     Width,
    UINT                     Height,
    UINT                     Depth,
    UINT                     Levels,
    DWORD                    Usage,
    D3DFORMAT                Format,
    INT                      ExpBias,
    DWORD                    Flags,
    UINT                     BaseOffset,
    UINT                     MipOffset,
    IDirect3DVolumeTexture9* pVolumeTexture,
    UINT*                    pBaseSize,
    UINT*                    pMipSize
    );

// Initialize the header of a vertex buffer resource.

VOID WINAPI XGSetVertexBufferHeader(
    UINT                    Length,
    DWORD                   Usage,
    D3DPOOL                 Pool,
    UINT                    Offset,
    IDirect3DVertexBuffer9* pVertexBuffer
    );

// Initialize the header of an index buffer resource.

VOID WINAPI XGSetIndexBufferHeader(
    UINT                    Length,
    DWORD                   Usage,
    D3DFORMAT               Format,
    D3DPOOL                 Pool,
    UINT                    Offset,
    IDirect3DIndexBuffer9*  pIndexBuffer
    );

// Initialize the header of a constants resource.

VOID WINAPI XGSetConstantBufferHeader(
    UINT                    VectorCount,
    DWORD                   Usage,
    UINT                    Offset,
    IDirect3DConstantBuffer9* pConstantBuffer
    );

// Add the given offset(s) to the EDRAM tile offset and/or hierarchical Z offset 
// stored in the surface header.

VOID WINAPI XGOffsetSurfaceAddress(
    IDirect3DSurface9*      pSurface,
    INT                     SurfaceOffset,
    INT                     HierarchicalZOffset
    );

// Add the given memory address to the offset value stored in the resource header 
// (in this way the resource header may be pointed at the resource data).

VOID WINAPI XGOffsetResourceAddress(
    IDirect3DResource9*     pResource,
    VOID*                   pBaseAddress
    );

// Add the given memory addresses to the offsets stored in the mip map header.
// The pMipAddress parameter is ignored for textures with a single mip level.

VOID WINAPI XGOffsetBaseTextureAddress(
    IDirect3DBaseTexture9*  pTexture,
    VOID*                   pBaseAddress,
    VOID*                   pMipAddress
    );

/****************************************************************************
*
* Shader utilities
*
****************************************************************************/

typedef enum {
    XGUCODESHADERVERSION_PIXEL      = 0,
    XGUCODESHADERVERSION_VERTEX     = 1,
} XGUCODESHADERVERSION;

typedef struct _XGSHADER_CONSTANT_MASKS
{
    // The MSB of the ALU constants is for constants 0-3 and the LSB is
    // for constants 252-255:

    UINT64 u64BitAluConstants;

    // If the MSB is defined as bit zero, then bit 0 is for integer constant 0
    // and bit 31 is for integer constant 31.  Bit 32 is for boolean constants
    // 0-31 and bit 39 is for boolean constants 224-255:

    UINT64 u64BitFlowConstants;
} XGSHADER_CONSTANT_MASKS;

VOID WINAPI XGPixelShaderGetDefinedConstantMasks(
    D3DDevice *pDevice,
    D3DPixelShader* pPixelShader,
    XGSHADER_CONSTANT_MASKS* pShaderConstantMasks);

VOID WINAPI XGVertexShaderGetDefinedConstantMasks(
    D3DDevice *pDevice,
    D3DVertexShader* pVertexShader,
    XGSHADER_CONSTANT_MASKS* pShaderConstantMasks);

VOID WINAPI XGShaderMicrocodeGetDefinedConstantMasks(
    const DWORD* pShaderMicrocode,
    XGUCODESHADERVERSION ShaderVersion,
    XGSHADER_CONSTANT_MASKS* pShaderConstantMasks);

typedef struct _XGSHADER_FETCHCONSTANT_MASKS
{
    // The MSB of the texture fetch constant is for constant tf0 and
    // the LSB is for constant tf31
    UINT32 u32TextureFetchConstants;

    // The MSB of vertex fetch constant[0] is for constant vf0
    // and the LSB of vertex fetch constant[2] is for constant vf95
    UINT32 u32VertexFetchConstants[3];
} XGSHADER_FETCHCONSTANT_MASKS;

VOID WINAPI XGPixelShaderGetFetchConstantMasks(
    D3DDevice *pDevice,
    D3DPixelShader* pPixelShader,
    XGSHADER_FETCHCONSTANT_MASKS* pShaderFetchConstantMasks);

VOID WINAPI XGVertexShaderGetFetchConstantMasks(
    D3DDevice *pDevice,
    D3DVertexShader* pVertexShader,
    XGSHADER_FETCHCONSTANT_MASKS* pShaderFetchConstantMasks);

VOID WINAPI XGShaderMicrocodeGetFetchConstantMasks(
    const DWORD* pShaderMicrocode,
    XGUCODESHADERVERSION ShaderVersion,
    XGSHADER_FETCHCONSTANT_MASKS* pShaderFetchConstantMasks);

typedef struct _XGUCODE_PASS_DESCRIPTION
{
    GPU_PROGRAMCONTROL  ProgramControl;
    GPU_CONTEXTMISC     ContextMisc;
    DWORD               PhysicalMicrocodeOffset;
    DWORD               PhysicalMicrocodeSize;
} XGUCODE_PASS_DESCRIPTION;

typedef struct _XGUCODE_DESCRIPTION
{
    BOOL                        IsPixelShader;
    DWORD                       PassCount;
    XGUCODE_PASS_DESCRIPTION    Pass[2];
} XGUCODE_DESCRIPTION;

VOID WINAPI XGGetMicrocodeDescription(
    LPCVOID pShaderMicrocode,
    XGUCODE_DESCRIPTION* pDescription);

//------------------------------------------------------------------------------------
// XGConvertDXTokensToMicrocode

#define XGCUCODE_SKIPOPTIMIZATION   0x00000008    // Do not optimize the microcode

typedef VOID (*XGConvertDXTokensToMicrocodeErrorCallbackFunction)(
    LPVOID pErrorCallbackContext,
    BOOL isError,
    DWORD errorNumber,
    LPCSTR message);

// pInput - pointer to D3D shader tokens.
// cbInputSize size of pInput, in bytes
// pOutput - pointer to buffer that will receive microcode
// cbOutputSize - size of output buffer
// pcbOutputUsed - pointer to DWORD that holds number of bytes of output buffer
//                 that are actually used.
// flags - use to pass flags in to control the way the shader tokens
//         are converted into microcode. (If no GPU flags are specified,
//         a fat shader with microcode for all GPUs will be produced.)
// pErrorCallbackContext - This argument is passed unchanged to the pErrorCallbackFunction
// pErrorCallbackFunction - this function is called when an error or warning is encountered.
//                          (the pErrorCallbackFunction can be NULL.)
// pConstantTable - this shader's constant table, can be NULL.
// tempRegisterLimit - the maximum number of temp registers allowed in this microcode.


typedef struct ID3DXConstantTable *LPD3DXCONSTANTTABLE;

HRESULT WINAPI XGConvertDXTokensToMicrocode(
    IN const DWORD* pInput,
    IN DWORD cbInputSize,
    OUT DWORD* pOutput,
    IN DWORD cbOutputSize,
    OUT DWORD* pcbOutputUsed, 
    IN DWORD flags,
    IN LPVOID pErrorCallbackContext,
    IN XGConvertDXTokensToMicrocodeErrorCallbackFunction pErrorCallbackFunction,
    IN LPD3DXCONSTANTTABLE pConstantTable,
    IN DWORD tempRegisterLimit);


// Split a microcode shader into cached and physical parts

typedef struct _XGMICROCODESHADERPARTS {
    VOID* pCachedPart;
    DWORD cbCachedPartSize;     // Size in bytes
    VOID* pPhysicalPart;
    DWORD cbPhysicalPartSize;   // Size in bytes
} XGMICROCODESHADERPARTS;

VOID WINAPI XGGetMicrocodeShaderParts(
    IN LPCVOID pFunction,
    OUT XGMICROCODESHADERPARTS* pParts);

// Shader physical memory must be aligned on a 32-byte boundary.

#define D3DSHADER_ALIGNMENT 32

VOID WINAPI XGSetPixelShaderHeader(
    IDirect3DPixelShader9* pShader,
    DWORD cbShaderSize,
    const XGMICROCODESHADERPARTS* pParts);

VOID WINAPI XGCopyNativeToUCodePixelShaderHeader(
    const IDirect3DPixelShader9* pShader,
    LPVOID pBuffer, DWORD cbBufferSize);

// Note: Physical pixel shader data must
// be allocated out of write-combined physical memory.

VOID WINAPI XGRegisterPixelShader(
    IDirect3DPixelShader9* pShader,
    VOID* pPhysicalPart);

VOID WINAPI XGSetVertexShaderHeader(
    IDirect3DVertexShader9* pShader,
    DWORD cbShaderSize,
    const XGMICROCODESHADERPARTS* pParts);

VOID WINAPI XGCopyNativeToUCodeVertexShaderHeader(
    const IDirect3DVertexShader9* pShader,
    LPVOID pBuffer, DWORD cbBufferSize);

// Note: Physical vertex shader data must
// be allocated out of cached physical memory.

VOID WINAPI XGRegisterVertexShader(
    IDirect3DVertexShader9* pShader,
    VOID* pPhysicalPart);

#ifndef __D3DX9SHADER_H__
struct _D3DXSHADER_CONSTANTTABLE;
typedef struct _D3DXSHADER_CONSTANTTABLE D3DXSHADER_CONSTANTTABLE;
#endif

HRESULT WINAPI XGCreateConstantTable(
    CONST D3DXSHADER_CONSTANTTABLE* pNativeConstantTableData,
    DWORD ConstantTableDataSize,
    LPD3DXCONSTANTTABLE* ppConstantTable);

HRESULT WINAPI XGMicrocodeGetConstantTable(
    CONST VOID* pFunction,
    CONST D3DXSHADER_CONSTANTTABLE** ppUCodeConstantTable,
    DWORD* pConstantTableSize);

VOID WINAPI XGCopyUCodeToNativeConstantTable(
    CONST D3DXSHADER_CONSTANTTABLE* pSrcUCodeConstantTable,
    D3DXSHADER_CONSTANTTABLE* pDestNativeConstantTable,
    DWORD ConstantTableSize);

HRESULT WINAPI XGMicrocodeDeleteConstantTable(
    CONST VOID* pFunction,
    VOID* pUpdatedFunctionBuffer,
    DWORD UpdatedFunctionBufferSize,  
    DWORD* pUpdatedFunctionSize);


// Literal table constant enumeration and removal

#define  XGMELCF_TYPE_IS_BOOL  0
#define  XGMELCF_TYPE_IS_FLOAT 1
#define  XGMELCF_TYPE_IS_INT   2

typedef HRESULT (*XGMicrocodeEnumerateLiteralsCallbackFunction)(
    VOID* pContext,
    DWORD PassIndex,  // UCODE_PASS_INDEX
    DWORD Type, // XGMELCCF_TYPE
    DWORD Index,
    CONST VOID* pData);

HRESULT WINAPI XGMicrocodeEnumerateLiterals(
    CONST VOID* pFunction,
    VOID* pContext,
    XGMicrocodeEnumerateLiteralsCallbackFunction pCallbackFunction);

#define  XGMDL_DELETE_BOOL_LITERALS     (1 << 0)
#define  XGMDL_DELETE_FLOAT_LITERALS    (1 << 1)
#define  XGMDL_DELETE_INT_LITERALS      (1 << 2)

HRESULT WINAPI XGMicrocodeDeleteLiterals(
    CONST VOID* pFunction,
    DWORD Flags, // XGMDL flags. Passing zero will delete all constant types.
    VOID* pUpdatedFunctionBuffer,
    DWORD UpdatedFunctionBufferSize,  
    DWORD* pUpdatedFunctionSize);


// Functions for managing collections of shaders.

#define XGMCS_IGNORE_DEBUG_INFO 0x1

// Returns <0, 0, or >0, depending upon whether pFunctionA is <, ==, or > pFunctionB

INT WINAPI XGMicrocodeCompareShaders(
    CONST VOID* pFunctionA,
    CONST VOID* pFunctionB,
    DWORD Flags);   // XGMCS_*

INT WINAPI XGMicrocodeHashShader(
    CONST VOID* pFunction,
    DWORD Flags);

HRESULT WINAPI XGMicrocodeDeleteDebugInfo(
    CONST VOID* pFunction,
    VOID* pUpdatedFunctionBuffer,
    DWORD UpdatedFunctionBufferSize,  
    DWORD* pUpdatedFunctionSize);

// VertexDeclaration utilities

UINT WINAPI XGGetVertexDeclarationSize(
    CONST D3DVERTEXELEMENT9* pVertexElements);

VOID WINAPI XGSetVertexDeclaration(
    CONST D3DVERTEXELEMENT9* pVertexElements,
    D3DVertexDeclaration* pVertexDeclaration);

VOID WINAPI XGEndianSwapVertexDeclaration(
    D3DVertexDeclaration* pVertexDeclaration);

VOID WINAPI XGRegisterVertexDeclaration(
    D3DVertexDeclaration* pVertexDeclaration);


// Returns <0, 0, or >0, depending upon whether pVertexDeclarationA is <, ==, or > pVertexDeclarationB

INT WINAPI XGCompareVertexDeclarations(
   CONST D3DVertexDeclaration* pVertexDeclarationA,
   CONST D3DVertexDeclaration* pVertexDeclarationB);

INT WINAPI XGHashVertexDeclaration(
    CONST D3DVertexDeclaration* pVertexDeclaration);

/****************************************************************************
 *
 * Shader Shrinker
 *
 ****************************************************************************/

typedef struct XGShaderShrinker XGShaderShrinker;
typedef struct XGShaderShrinker *LPXGSHADERSHRINKER, *PXGSHADERSHRINKER;

struct XGShaderShrinker
{
#ifdef __cplusplus

    ULONG WINAPI AddRef();
    ULONG WINAPI Release();

    VOID WINAPI SetVertexShaderConstantB(UINT StartRegister, CONST BOOL *pConstantData, DWORD BoolCount);
    VOID WINAPI SetVertexShaderConstantF(UINT StartRegister, CONST FLOAT *pConstantData, DWORD Vector4fCount);
    VOID WINAPI SetVertexShaderConstantI(UINT StartRegister, CONST int *pConstantData, DWORD Vector4iCount);
    VOID WINAPI SetPixelShaderConstantB(UINT StartRegister, CONST BOOL *pConstantData, DWORD BoolCount);
    VOID WINAPI SetPixelShaderConstantF(UINT StartRegister, CONST FLOAT *pConstantData, DWORD Vector4fCount);
    VOID WINAPI SetPixelShaderConstantI(UINT StartRegister, CONST int *pConstantData, DWORD Vector4iCount);

    VOID WINAPI UnsetVertexShaderConstantB(UINT StartRegister, DWORD BoolCount);
    VOID WINAPI UnsetVertexShaderConstantF(UINT StartRegister, DWORD Vector4fCount);
    VOID WINAPI UnsetVertexShaderConstantI(UINT StartRegister, DWORD Vector4iCount);
    VOID WINAPI UnsetPixelShaderConstantB(UINT StartRegister, DWORD BoolCount);
    VOID WINAPI UnsetPixelShaderConstantF(UINT StartRegister, DWORD Vector4fCount);
    VOID WINAPI UnsetPixelShaderConstantI(UINT StartRegister, DWORD Vector4iCount);
    VOID WINAPI UnsetAll();

    HRESULT WINAPI ExtractShader(void* pBuffer, UINT* pBufferSize);
    HRESULT WINAPI ExtractShaderParts(void* pCachedBuffer, UINT* pCachedBufferSize, void* pPhysicalBuffer, UINT* pPhysicalBufferSize);

#endif

    // Arrays to hold the values of known constants. To save space, only store 
    // the values for the 256 vertex constants (if it's a vertex shader), 
    // or 256 pixel c-consants (if it's a pixel shader).
    //
    D3DVECTOR4 m_FConstants[GPU_ALU_CONSTANTS / 2];

#pragma warning(push)
#pragma warning(disable:4201)
    union {
        DWORD Flow[GPU_FLOW_CONSTANTS];
        struct {
            DWORD VertexShaderB[GPU_D3D_VERTEX_CONSTANTB_COUNT/32];
            DWORD PixelShaderB[GPU_D3D_PIXEL_CONSTANTB_COUNT/32];
            DWORD VertexShaderI[GPU_D3D_VERTEX_CONSTANTI_COUNT];
            DWORD PixelShaderI[GPU_D3D_PIXEL_CONSTANTI_COUNT];
        };
    };
#pragma warning(pop)

    // Bitfields to keep track of which constants have known values.
    // Low bit=true implies constant 0 is known, etc.
    //
    UINT64 m_KnownUserFConstants[(GPU_ALU_CONSTANTS / 2) / 64];
    UINT64 m_KnownUserBConstants[GPU_BOOLEAN_CONSTANTS   / 64];
    DWORD  m_KnownUserIConstants[GPU_INTEGER_CONSTANTS   / 32];
};

HRESULT WINAPI XGCreateShaderShrinker(CONST DWORD* pShader, DWORD* pScratchBuffer, UINT* pScratchBufferSize, XGShaderShrinker **ppShaderShrinker);

ULONG                       WINAPI XGShaderShrinker_AddRef(XGShaderShrinker *pThis);
ULONG                       WINAPI XGShaderShrinker_Release(XGShaderShrinker *pThis);

void                        WINAPI XGShaderShrinker_SetVertexShaderConstantB(XGShaderShrinker *pThis, UINT StartRegister, CONST BOOL *pConstantData, DWORD BoolCount);
void                        WINAPI XGShaderShrinker_SetVertexShaderConstantF(XGShaderShrinker *pThis, UINT StartRegister, CONST float *pConstantData, DWORD Vector4fCount);
void                        WINAPI XGShaderShrinker_SetVertexShaderConstantI(XGShaderShrinker *pThis, UINT StartRegister, CONST int *pConstantData, DWORD Vector4iCount);
void                        WINAPI XGShaderShrinker_SetPixelShaderConstantB(XGShaderShrinker *pThis, UINT StartRegister, CONST BOOL *pConstantData, DWORD BoolCount);
void                        WINAPI XGShaderShrinker_SetPixelShaderConstantF(XGShaderShrinker *pThis, UINT StartRegister, CONST float *pConstantData, DWORD Vector4fCount);
void                        WINAPI XGShaderShrinker_SetPixelShaderConstantI(XGShaderShrinker *pThis, UINT StartRegister, CONST int *pConstantData, DWORD Vector4iCount);
void                        WINAPI XGShaderShrinker_UnsetVertexShaderConstantB(XGShaderShrinker *pThis, UINT StartRegister, DWORD BoolCount);
void                        WINAPI XGShaderShrinker_UnsetVertexShaderConstantF(XGShaderShrinker *pThis, UINT StartRegister, DWORD Vector4fCount);
void                        WINAPI XGShaderShrinker_UnsetVertexShaderConstantI(XGShaderShrinker *pThis, UINT StartRegister, DWORD Vector4iCount);
void                        WINAPI XGShaderShrinker_UnsetPixelShaderConstantB(XGShaderShrinker *pThis, UINT StartRegister, DWORD BoolCount);
void                        WINAPI XGShaderShrinker_UnsetPixelShaderConstantF(XGShaderShrinker *pThis, UINT StartRegister, DWORD Vector4fCount);
void                        WINAPI XGShaderShrinker_UnsetPixelShaderConstantI(XGShaderShrinker *pThis, UINT StartRegister, DWORD Vector4iCount);
void                        WINAPI XGShaderShrinker_UnsetAll(XGShaderShrinker *pThis);
HRESULT                     WINAPI XGShaderShrinker_ExtractShader(XGShaderShrinker *pThis, void* pBuffer, UINT* pBufferSize);
HRESULT                     WINAPI XGShaderShrinker_ExtractShaderParts(XGShaderShrinker *pThis, void* pCachedBuffer, UINT* pCachedBufferSize, void* pPhysicalBuffer, UINT* pPhysicalBufferSize);

#ifdef __cplusplus

D3DMINLINE ULONG            WINAPI XGShaderShrinker::AddRef() { return XGShaderShrinker_AddRef(this); }
D3DMINLINE ULONG            WINAPI XGShaderShrinker::Release() { return XGShaderShrinker_Release(this); }

D3DMINLINE VOID             WINAPI XGShaderShrinker::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL *pConstantData, DWORD BoolCount) { XGShaderShrinker_SetVertexShaderConstantB(this, StartRegister, pConstantData, BoolCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::SetVertexShaderConstantF(UINT StartRegister, CONST float *pConstantData, DWORD Vector4fCount) { XGShaderShrinker_SetVertexShaderConstantF(this, StartRegister, pConstantData, Vector4fCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::SetVertexShaderConstantI(UINT StartRegister, CONST int *pConstantData, DWORD Vector4iCount) { XGShaderShrinker_SetVertexShaderConstantI(this, StartRegister, pConstantData, Vector4iCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::SetPixelShaderConstantB(UINT StartRegister, CONST BOOL *pConstantData, DWORD BoolCount) { XGShaderShrinker_SetPixelShaderConstantB(this, StartRegister, pConstantData, BoolCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::SetPixelShaderConstantF(UINT StartRegister, CONST float *pConstantData, DWORD Vector4fCount) { XGShaderShrinker_SetPixelShaderConstantF(this, StartRegister, pConstantData, Vector4fCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::SetPixelShaderConstantI(UINT StartRegister, CONST int *pConstantData, DWORD Vector4iCount) { XGShaderShrinker_SetPixelShaderConstantI(this, StartRegister, pConstantData, Vector4iCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::UnsetVertexShaderConstantB(UINT StartRegister, DWORD BoolCount) { XGShaderShrinker_UnsetVertexShaderConstantB(this, StartRegister, BoolCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::UnsetVertexShaderConstantF(UINT StartRegister, DWORD Vector4fCount) { XGShaderShrinker_UnsetVertexShaderConstantF(this, StartRegister, Vector4fCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::UnsetVertexShaderConstantI(UINT StartRegister, DWORD Vector4iCount) { XGShaderShrinker_UnsetVertexShaderConstantI(this, StartRegister, Vector4iCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::UnsetPixelShaderConstantB(UINT StartRegister, DWORD BoolCount) { XGShaderShrinker_UnsetPixelShaderConstantB(this, StartRegister, BoolCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::UnsetPixelShaderConstantF(UINT StartRegister, DWORD Vector4fCount) { XGShaderShrinker_UnsetPixelShaderConstantF(this, StartRegister, Vector4fCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::UnsetPixelShaderConstantI(UINT StartRegister, DWORD Vector4iCount) { XGShaderShrinker_UnsetPixelShaderConstantI(this, StartRegister, Vector4iCount); }
D3DMINLINE VOID             WINAPI XGShaderShrinker::UnsetAll() { XGShaderShrinker_UnsetAll(this); }
D3DMINLINE HRESULT          WINAPI XGShaderShrinker::ExtractShader(void* pBuffer, UINT* pBufferSize) { return XGShaderShrinker_ExtractShader(this, pBuffer, pBufferSize); }
D3DMINLINE HRESULT          WINAPI XGShaderShrinker::ExtractShaderParts(void* pCachedBuffer, UINT* pCachedBufferSize, void* pPhysicalBuffer, UINT* pPhysicalBufferSize) { return XGShaderShrinker_ExtractShaderParts(this, pCachedBuffer, pCachedBufferSize, pPhysicalBuffer, pPhysicalBufferSize); }

#endif __cplusplus

/****************************************************************************
 *
 * CPU vertex processing.
 *
 ****************************************************************************/

// Values for ProcessVertices flags:

#define D3DPV_DONOTINVALIDATECACHE      0x1

// CPU shader limits.

#define XGCPUSHADER_MAX_THREADS         14
#define XGCPUSHADER_BRANCH_DEPTH        32
#define XGCPUSHADER_MAX_USAGE_TYPE      14
#define XGCPUSHADER_MAX_USAGE_INDEX     16
#define XGCPUSHADER_MAX_PREFETCHES      8

typedef struct _XGCPUSHADERVERTEXSTREAM
{
    DWORD BaseAddress;
    WORD  VertexStride;

} XGCPUSHADERVERTEXSTREAM;

typedef struct _XGCPUSHADERCONTEXT
{
    // Shader Registers

    XMVECTOR v[16][XGCPUSHADER_MAX_THREADS];                   // Input register
    XMVECTOR o[16][XGCPUSHADER_MAX_THREADS];                   // Output register
    XMVECTOR r[32][XGCPUSHADER_MAX_THREADS];                   // Temporary register
    XMVECTOR c[256];                                           // Constant float register
    XMVECTOR p[XGCPUSHADER_MAX_THREADS];                       // Predicate register
    XMVECTOR xBranchMask;                                      // Branch select register (1 byte per thread of execution)
    XMVECTOR xBreakMask;                                       // Break mask applied to xBranchMask when it is popped off the stack
    XMVECTOR xUR0;                                             // PPC uniform register (common for all threads)
    XMVECTOR xUR1;                                             // PPC uniform register (common for all threads)
    XMVECTOR xUR2;                                             // PPC uniform register (common for all threads)
    XMVECTOR xUR3;                                             // PPC uniform register (common for all threads)
    XMVECTOR xSR0[XGCPUSHADER_MAX_THREADS];                    // PPC temp register (swizzling, intermediate results, etc.)
    XMVECTOR xSR1[XGCPUSHADER_MAX_THREADS];                    // PPC temp register (swizzling, intermediate results, etc.)
    XMVECTOR xSR2[XGCPUSHADER_MAX_THREADS];                    // PPC temp register (swizzling, intermediate results, etc.)
    XMVECTOR xSR3[XGCPUSHADER_MAX_THREADS];                    // PPC temp register (swizzling, intermediate results, etc.)
    XMVECTOR xCR0;                                             // PPC constant register (mask, byte shift, and 1.0f generation) set to <0x00000000 0xFFFFFFFF 0x00FFFFFF 1.0f>
    XMVECTOR xCR1;                                             // PPC constant register (abs, negate, and negative abs generation) set to <0x80000000 0x7FFFFFFF dc dc>
    XMVECTOR xBranchMaskStack[XGCPUSHADER_BRANCH_DEPTH];       // Branch mask stack
    __declspec(align(16)) INT i[32][4];                        // Constant integer register
    __declspec(align(8)) SHORT a[XGCPUSHADER_MAX_THREADS][4];  // Address register
    INT      xLoopCounterStack[XGCPUSHADER_BRANCH_DEPTH];      // Loop counter stack
    INT      xLoopRepeatStack[XGCPUSHADER_BRANCH_DEPTH];       // Loop repeat stack
    UINT     xBranchMaskStackIndex;                            // Index of the top of the branch mask stack
    UINT     xLoopCounterStackIndex;                           // Index of the top of the loop counter stack
    UINT     xLoopRepeatStackIndex;                            // Index of the top of the loop repeat stack
    INT      l;                                                // Loop counter register
    INT      xLoopRepeat;                                      // Loop repeat register (number of times to repeat a loop)
    UINT     xCondition;                                       // Condition register to hold results from uniform recording comparisons
    UINT64   b;                                                // Constant boolean register

    // Stream information

    UINT                    VertexCount;
    UINT                    PrefetchCount;
    BOOL                    InvalidateCache;

    XGCPUSHADERVERTEXSTREAM PrefetchStream[XGCPUSHADER_MAX_PREFETCHES];
    XGCPUSHADERVERTEXSTREAM InputStream[XGCPUSHADER_MAX_USAGE_INDEX][XGCPUSHADER_MAX_USAGE_TYPE]; // Map from dcl_usage to location of vertex element in the stream
    XGCPUSHADERVERTEXSTREAM OutputStream[XGCPUSHADER_MAX_USAGE_INDEX][XGCPUSHADER_MAX_USAGE_TYPE];

} XGCPUSHADERCONTEXT;

// CPU shader function.

typedef VOID (__cdecl *XGCPUSHADERFUNCTION)(XGCPUSHADERCONTEXT* XGRESTRICT pContext);

/*
 * XGCpuVertexShader
 */

typedef struct XGCpuVertexShader XGCpuVertexShader;

struct XGCpuVertexShader
{
#ifdef __cplusplus

    ULONG WINAPI AddRef();
    ULONG WINAPI Release();

#endif // __cplusplus

    // Private internal data:

    XGCPUSHADERFUNCTION* pShaderFunction;
};

/*
 * XGCpuShaderDevice
 */

typedef struct XGCpuShaderDevice XGCpuShaderDevice;

struct XGCpuShaderDevice
{
#ifdef __cplusplus

    ULONG WINAPI AddRef();
    ULONG WINAPI Release();

    VOID  WINAPI SetVertexShader(XGCpuVertexShader *pShader);
    VOID  WINAPI GetVertexShader(XGCpuVertexShader **ppShader);

    VOID  WINAPI SetVertexDeclaration(D3DVertexDeclaration *pDecl);
    VOID  WINAPI GetVertexDeclaration(D3DVertexDeclaration **ppDecl);
    VOID  WINAPI SetVertexDeclarationDest(D3DVertexDeclaration *pDecl);
    VOID  WINAPI GetVertexDeclarationDest(D3DVertexDeclaration **ppDecl);
    VOID  WINAPI SetFVF(DWORD FVF);
    VOID  WINAPI GetFVF(DWORD* pFVF);
    VOID  WINAPI SetFVFDest(DWORD FVF);
    VOID  WINAPI GetFVFDest(DWORD* pFVF);

    VOID  WINAPI SetStreamSource(UINT StreamNumber, D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride);
    VOID  WINAPI GetStreamSource(UINT StreamNumber, D3DVertexBuffer **ppStreamData, UINT *pOffsetInBytes, UINT *pStride);
    VOID  WINAPI SetStreamDest(UINT StreamNumber, D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride);
    VOID  WINAPI GetStreamDest(UINT StreamNumber, D3DVertexBuffer **ppStreamData, UINT *pOffsetInBytes, UINT *pStride);

    VOID  WINAPI SetVertexShaderConstantB(UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount);
    VOID  WINAPI SetVertexShaderConstantF(UINT StartRegister, CONST FLOAT *pConstantData, DWORD Vector4fCount);
    VOID  WINAPI SetVertexShaderConstantI(UINT StartRegister, CONST INT *pConstantData, DWORD Vector4iCount);
    VOID  WINAPI GetVertexShaderConstantB(UINT StartRegister, BOOL *pConstantData, DWORD BoolCount);
    VOID  WINAPI GetVertexShaderConstantF(UINT StartRegister, FLOAT *pConstantData, DWORD Vector4fCount);
    VOID  WINAPI GetVertexShaderConstantI(UINT StartRegister, INT *pConstantData, DWORD Vector4iCount);

    VOID  WINAPI ProcessVertices(UINT IndexSource, UINT IndexDest, UINT VertexCount, DWORD Flags);

#endif // __cplusplus

    // Private internal data:

    XGCPUSHADERCONTEXT ShaderContext;
};

/*
 * XGCpuVertexShader functions and methods.
 */

ULONG                   WINAPI XGCpuVertexShader_AddRef(XGCpuVertexShader* pDevice);
ULONG                   WINAPI XGCpuVertexShader_Release(XGCpuVertexShader* pDevice);

#ifdef __cplusplus

__forceinline ULONG WINAPI XGCpuVertexShader::AddRef() { return XGCpuVertexShader_AddRef(this); }
__forceinline ULONG WINAPI XGCpuVertexShader::Release() { return XGCpuVertexShader_Release(this); }

#endif // __cplusplus

/*
 * XGCpuShaderDevice functions and methods.
 */

ULONG                   WINAPI XGCpuShaderDevice_AddRef(XGCpuShaderDevice* pDevice);
ULONG                   WINAPI XGCpuShaderDevice_Release(XGCpuShaderDevice* pDevice);

VOID                    WINAPI XGCpuShaderDevice_SetVertexShader(XGCpuShaderDevice* pDevice, XGCpuVertexShader *pShader);
XGCpuVertexShader*      WINAPI XGCpuShaderDevice_GetVertexShader(XGCpuShaderDevice* pDevice);

VOID                    WINAPI XGCpuShaderDevice_SetVertexDeclaration(XGCpuShaderDevice* pDevice, D3DVertexDeclaration *pDecl);
D3DVertexDeclaration*   WINAPI XGCpuShaderDevice_GetVertexDeclaration(XGCpuShaderDevice* pDevice);
VOID                    WINAPI XGCpuShaderDevice_SetVertexDeclarationDest(XGCpuShaderDevice* pDevice, D3DVertexDeclaration *pDecl);
D3DVertexDeclaration*   WINAPI XGCpuShaderDevice_GetVertexDeclarationDest(XGCpuShaderDevice* pDevice);
VOID                    WINAPI XGCpuShaderDevice_SetFVF(XGCpuShaderDevice* pDevice, DWORD FVF);
DWORD                   WINAPI XGCpuShaderDevice_GetFVF(XGCpuShaderDevice* pDevice);
VOID                    WINAPI XGCpuShaderDevice_SetFVFDest(XGCpuShaderDevice* pDevice, DWORD FVF);
DWORD                   WINAPI XGCpuShaderDevice_GetFVFDest(XGCpuShaderDevice* pDevice);

VOID                    WINAPI XGCpuShaderDevice_SetStreamSource(XGCpuShaderDevice* pDevice, UINT StreamNumber, D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride);
D3DVertexBuffer*        WINAPI XGCpuShaderDevice_GetStreamSource(XGCpuShaderDevice* pDevice, UINT StreamNumber, UINT *pOffsetInBytes, UINT *pStride);
VOID                    WINAPI XGCpuShaderDevice_SetStreamDest(XGCpuShaderDevice* pDevice, UINT StreamNumber, D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride);
D3DVertexBuffer*        WINAPI XGCpuShaderDevice_GetStreamDest(XGCpuShaderDevice* pDevice, UINT StreamNumber, UINT *pOffsetInBytes, UINT *pStride);

VOID                    WINAPI XGCpuShaderDevice_SetVertexShaderConstantB(XGCpuShaderDevice* pDevice, UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount);
VOID                    WINAPI XGCpuShaderDevice_SetVertexShaderConstantF(XGCpuShaderDevice* pDevice, UINT StartRegister, CONST FLOAT *pConstantData, DWORD Vector4fCount);
VOID                    WINAPI XGCpuShaderDevice_SetVertexShaderConstantI(XGCpuShaderDevice* pDevice, UINT StartRegister, CONST INT *pConstantData, DWORD Vector4iCount);
VOID                    WINAPI XGCpuShaderDevice_GetVertexShaderConstantB(XGCpuShaderDevice* pDevice, UINT StartRegister, BOOL *pConstantData, DWORD BoolCount);
VOID                    WINAPI XGCpuShaderDevice_GetVertexShaderConstantF(XGCpuShaderDevice* pDevice, UINT StartRegister, FLOAT *pConstantData, DWORD Vector4fCount);
VOID                    WINAPI XGCpuShaderDevice_GetVertexShaderConstantI(XGCpuShaderDevice* pDevice, UINT StartRegister, INT *pConstantData, DWORD Vector4iCount);

VOID                    WINAPI XGCpuShaderDevice_ProcessVertices(XGCpuShaderDevice* pDevice, UINT IndexSource, UINT IndexDest, UINT VertexCount, DWORD Flags);

#ifdef __cplusplus

__forceinline ULONG WINAPI XGCpuShaderDevice::AddRef() { return XGCpuShaderDevice_AddRef(this); }
__forceinline ULONG WINAPI XGCpuShaderDevice::Release() { return XGCpuShaderDevice_Release(this); }

__forceinline VOID  WINAPI XGCpuShaderDevice::SetVertexShader(XGCpuVertexShader *pShader) { return XGCpuShaderDevice_SetVertexShader(this, pShader); }
__forceinline VOID  WINAPI XGCpuShaderDevice::GetVertexShader(XGCpuVertexShader **ppShader) { *ppShader = XGCpuShaderDevice_GetVertexShader(this); }

__forceinline VOID  WINAPI XGCpuShaderDevice::SetVertexDeclaration(D3DVertexDeclaration *pDecl) { return XGCpuShaderDevice_SetVertexDeclaration(this, pDecl); }
__forceinline VOID  WINAPI XGCpuShaderDevice::GetVertexDeclaration(D3DVertexDeclaration **ppDecl) { *ppDecl = XGCpuShaderDevice_GetVertexDeclaration(this); }
__forceinline VOID  WINAPI XGCpuShaderDevice::SetVertexDeclarationDest(D3DVertexDeclaration *pDecl) { return XGCpuShaderDevice_SetVertexDeclarationDest(this, pDecl); }
__forceinline VOID  WINAPI XGCpuShaderDevice::GetVertexDeclarationDest(D3DVertexDeclaration **ppDecl) { *ppDecl = XGCpuShaderDevice_GetVertexDeclarationDest(this); }
__forceinline VOID  WINAPI XGCpuShaderDevice::SetFVF(DWORD FVF) { return XGCpuShaderDevice_SetFVF(this, FVF); }
__forceinline VOID  WINAPI XGCpuShaderDevice::GetFVF(DWORD* pFVF) { *pFVF = XGCpuShaderDevice_GetFVF(this); }
__forceinline VOID  WINAPI XGCpuShaderDevice::SetFVFDest(DWORD FVF) { return XGCpuShaderDevice_SetFVFDest(this, FVF); }
__forceinline VOID  WINAPI XGCpuShaderDevice::GetFVFDest(DWORD* pFVF) { *pFVF = XGCpuShaderDevice_GetFVFDest(this); }

__forceinline VOID  WINAPI XGCpuShaderDevice::SetStreamSource(UINT StreamNumber, D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride) { return XGCpuShaderDevice_SetStreamSource(this, StreamNumber, pStreamData, OffsetInBytes, Stride); }
__forceinline VOID  WINAPI XGCpuShaderDevice::GetStreamSource(UINT StreamNumber, D3DVertexBuffer **ppStreamData, UINT *pOffsetInBytes, UINT *pStride) { *ppStreamData = XGCpuShaderDevice_GetStreamSource(this, StreamNumber, pOffsetInBytes, pStride); }
__forceinline VOID  WINAPI XGCpuShaderDevice::SetStreamDest(UINT StreamNumber, D3DVertexBuffer *pStreamData, UINT OffsetInBytes, UINT Stride) { return XGCpuShaderDevice_SetStreamDest(this, StreamNumber, pStreamData, OffsetInBytes, Stride); }
__forceinline VOID  WINAPI XGCpuShaderDevice::GetStreamDest(UINT StreamNumber, D3DVertexBuffer **ppStreamData, UINT *pOffsetInBytes, UINT *pStride) { *ppStreamData = XGCpuShaderDevice_GetStreamDest(this, StreamNumber, pOffsetInBytes, pStride); }

__forceinline VOID  WINAPI XGCpuShaderDevice::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount) { return XGCpuShaderDevice_SetVertexShaderConstantB(this, StartRegister, pConstantData, BoolCount); }
__forceinline VOID  WINAPI XGCpuShaderDevice::SetVertexShaderConstantF(UINT StartRegister, CONST FLOAT *pConstantData, DWORD Vector4fCount) { return XGCpuShaderDevice_SetVertexShaderConstantF(this, StartRegister, pConstantData, Vector4fCount); }
__forceinline VOID  WINAPI XGCpuShaderDevice::SetVertexShaderConstantI(UINT StartRegister, CONST INT *pConstantData, DWORD Vector4iCount) { return XGCpuShaderDevice_SetVertexShaderConstantI(this, StartRegister, pConstantData, Vector4iCount); }
__forceinline VOID  WINAPI XGCpuShaderDevice::GetVertexShaderConstantB(UINT StartRegister, BOOL *pConstantData, DWORD BoolCount) { return XGCpuShaderDevice_GetVertexShaderConstantB(this, StartRegister, pConstantData, BoolCount); }
__forceinline VOID  WINAPI XGCpuShaderDevice::GetVertexShaderConstantF(UINT StartRegister, FLOAT *pConstantData, DWORD Vector4fCount) { return XGCpuShaderDevice_GetVertexShaderConstantF(this, StartRegister, pConstantData, Vector4fCount); }
__forceinline VOID  WINAPI XGCpuShaderDevice::GetVertexShaderConstantI(UINT StartRegister, INT *pConstantData, DWORD Vector4iCount) { return XGCpuShaderDevice_GetVertexShaderConstantI(this, StartRegister, pConstantData, Vector4iCount); }

__forceinline VOID  WINAPI XGCpuShaderDevice::ProcessVertices(UINT IndexSource, UINT IndexDest, UINT VertexCount, DWORD Flags) { return XGCpuShaderDevice_ProcessVertices(this, IndexSource, IndexDest, VertexCount, Flags); }

#endif // __cplusplus

/*
 * Create functions.
 */

HRESULT WINAPI XGCreateCpuShaderDevice(
    XGCpuShaderDevice** pCpuShaderDevice
    );

HRESULT WINAPI XGCreateCpuVertexShader(
    XGCPUSHADERFUNCTION* pFunction,
    D3DVertexDeclaration* pDeclSource,
    D3DVertexDeclaration* pDeclDest,
    XGCpuVertexShader** pCpuVertexShader
    );

HRESULT WINAPI XGCreateCpuVertexShaderFromDLL(
    CONST CHAR* pDLLName,
    CONST CHAR* pFunction,
    D3DVertexDeclaration* pDeclSource,
    D3DVertexDeclaration* pDeclDest,
    XGCpuVertexShader** pCpuVertexShader
    );

typedef struct _XGIDEALSHADERCOST
{
    float MinAlu;
    float MaxAlu;
    float Interpolator;
    float MinTexture;
    float MaxTexture;
    float MinVertex;
    float MaxVertex;
    float Sequencer;
    float MinOverall;          
    float MaxOverall;
    BOOL bHasHitUnknownControlFlow;
    BOOL bHasHitChangeableControlFlow;
    BOOL bHasHitPredicatedJump;
    BOOL bHasHitPredicatedEndloop;
    BOOL bHasHitUnknownFetchConstant;
    BOOL bHasHitUnpatchedVfetch;
    int MaxTempReg;
} XGIDEALSHADERCOST;


HRESULT WINAPI XGCalculateIdealShaderCost (
    BOOL VertexShader, 
    GPU_PROGRAMCONTROL ProgramControl,
    GPU_CONTEXTMISC ContextMisc,
    const DWORD* pShaderCode,
    DWORD  ShaderSizeInBytes,
    const DWORD* pBooleanConstants,
    const DWORD* pIntegerConstants,
    const GPUFETCH_CONSTANT* pFetchConstants,
    BOOL bLittleEndianShader,
    /*OUT*/ XGIDEALSHADERCOST* pShaderCost);


HRESULT WINAPI XGEstimateIdealShaderCost (
    const VOID* pFunction,
    DWORD pass,
    /*OUT*/ XGIDEALSHADERCOST* pShaderCost
);

#ifdef __cplusplus
}
#endif

#endif /* _XGRAPHICS_H_ */
