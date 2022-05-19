/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       xuirender.h
 *  Content:    Xbox 360 UI rendering defines, structures, and functions
 *
 ****************************************************************************/

#ifndef __XUIRENDER_H__
#define __XUIRENDER_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _XUIDC* HXUIDC;
typedef struct _XUISHAPE* HXUISHAPE;
typedef struct _XUIBRUSH* HXUIBRUSH;
typedef struct _XUITEX* HXUITEX;
typedef struct _XUIFONT* HXUIFONT;
typedef struct XUIRect XUIRect;
typedef struct XUIImageInfo XUIImageInfo;
typedef struct XUIGradientStop  XUIGradientStop;
typedef struct XUIRenderStats XUIRenderStats;
typedef struct XUIFontMetrics XUIFontMetrics;
typedef struct XUICharMetrics XUICharMetrics;
typedef struct CharData CharData;
typedef struct IXuiFontRenderer IXuiFontRenderer;
typedef struct IXuiFontRendererVTBL IXuiFontRendererVTBL;
typedef enum XUI_BLEND_MODE XUI_BLEND_MODE;
typedef struct XUIFigurePoint XUIFigurePoint;
typedef struct IXuiTextureCache IXuiTextureCache;

typedef struct ID3D10ShaderResourceView ID3D10ShaderResourceView;
typedef struct ID3D10Texture2D ID3D10Texture2D;
//
// IXuiTexture interface
//
#undef  INTERFACE
#define INTERFACE IXuiTexture
DECLARE_INTERFACE(IXuiTexture)
{    
    STDMETHOD_(DWORD, AddRef)(THIS);
    STDMETHOD_(DWORD, Release)(THIS);
    STDMETHOD_(IDirect3DTexture9*, GetD3D9Texture)(THIS);
    STDMETHOD_(ID3D10ShaderResourceView*, GetD3D10View)(THIS);
    STDMETHOD_(ID3D10Texture2D*, GetD3D10Texture)(THIS);
    STDMETHOD(GetDimensions)(THIS_ UINT unLevel, UINT* punWidth, UINT* punHeight);
};


//
// IXuiDevice interface
//
#undef  INTERFACE
#define INTERFACE IXuiDevice

DECLARE_INTERFACE(IXuiDevice)
{    
    STDMETHOD_(DWORD, AddRef)(THIS);
    STDMETHOD_(DWORD, Release)(THIS);

    STDMETHOD_(IDirect3DDevice9 *, GetD3DDevice)(THIS);
    STDMETHOD_(IXuiTextureCache *, GetTextureCache)(THIS);
    STDMETHOD_(const D3DPRESENT_PARAMETERS *, GetPresentParams)(THIS);

    STDMETHOD(BeginScene)(THIS);
    STDMETHOD(EndScene)(THIS);
    STDMETHOD(CreateTexture)(THIS_ UINT Width, UINT Height,  UINT Levels, 
            UINT Usage, D3DFORMAT Format, D3DPOOL Pool,  
            IDirect3DTexture9 **ppTexture, HANDLE *pSharedHandle);
    STDMETHOD(SetTexture)(THIS_ DWORD Sampler, IDirect3DBaseTexture9 * pTexture);
    STDMETHOD(SetVertexShaderConstantF)(THIS_ UINT StartRegister, CONST float * pConstantData, UINT Vector4fCount);
    STDMETHOD(SetPixelShaderConstantF)(THIS_ UINT StartRegister, CONST float * pConstantData, UINT Vector4fCount);
    STDMETHOD(Clear)(THIS_ DWORD Count, CONST D3DRECT * pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil);
    STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE State, DWORD Value);
    STDMETHOD(SetSamplerState)(THIS_ DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value);
    STDMETHOD(SetVertexDeclaration)(THIS_ IDirect3DVertexDeclaration9 * pDecl);
    STDMETHOD(SetVertexShader)(THIS_ IDirect3DVertexShader9* pShader);
    STDMETHOD(SetPixelShader)(THIS_ IDirect3DPixelShader9* pShader);
#ifdef _XBOX    
    STDMETHOD(CreateRenderTarget)(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD UnusedMultisampleQuality,
            BOOL UnusedLockable, IDirect3DSurface9 **ppSurface, CONST D3DSURFACE_PARAMETERS *pParameters);
    STDMETHOD(Resolve)(THIS_ DWORD Flags, CONST D3DRECT *pSourceRect, IDirect3DBaseTexture9 *pDestTexture, CONST D3DPOINT *pDestPoint,
                       UINT DestLevel, UINT DestSliceOrFace, CONST D3DVECTOR4 *pClearColor, float ClearZ, DWORD ClearStencil,
                       CONST D3DRESOLVE_PARAMETERS *pParameters);
#endif
    STDMETHOD(GetDepthStencilSurface)(THIS_ IDirect3DSurface9 **ppZStencilSurface);
    STDMETHOD(SetDepthStencilSurface)(THIS_ IDirect3DSurface9 *pZStencilSurface);
    STDMETHOD(SetRenderTarget)(THIS_ DWORD RenderTargetIndex, IDirect3DSurface9 *pRenderTarget);
    STDMETHOD(GetRenderTarget)(THIS_ DWORD RenderTargetIndex, IDirect3DSurface9 **pRenderTarget);
    STDMETHOD(Present)(THIS_ CONST RECT * pSourceRect, CONST RECT * pDestRect, HWND hDestWindowOverride, void * pDirtyRegion);
    STDMETHOD(CreateVertexShader)(THIS_ CONST DWORD * pFunction, IDirect3DVertexShader9** ppShader);
    STDMETHOD(CreatePixelShader)(THIS_ CONST DWORD * pFunction, IDirect3DPixelShader9** ppShader);
    STDMETHOD(CreateVertexDeclaration)(THIS_ CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl);
    STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT9 * pViewport);
    STDMETHOD(DrawPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);
    STDMETHOD(DrawIndexedPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void * pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride);

#ifdef _XBOX
    STDMETHOD(BeginVertices)(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount, UINT VertexStreamZeroStride, void **ppVertexData);
    STDMETHOD(EndVertices)(THIS);
#endif

    STDMETHOD(LockTextureRect)(THIS_ IDirect3DTexture9 *pTexture, UINT Level, D3DLOCKED_RECT *pLockedRect, CONST RECT *pRect, DWORD Flags);
    STDMETHOD(UnlockTextureRect)(THIS_ IDirect3DTexture9 *pTexture, UINT Level);

    STDMETHOD(SetClipPlane)(THIS_ DWORD Index, CONST float *pPlane);

    STDMETHOD(CalculateTextureMemorySize)(THIS_ IXuiTexture* pTex, DWORD *pdwSize);

#ifndef _XBOX
    STDMETHOD_(const D3DCAPS9 *, GetDeviceCaps)(THIS);
    STDMETHOD(CreateQuery)(THIS_ D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery);
    STDMETHOD(GetBackBuffer)(THIS_ UINT iSwapChain, UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9 ** ppBackBuffer);
#endif
};

#ifdef XUI_USE_D3D10
//
// IXuiDevice10 interface
//
#undef  INTERFACE
#define INTERFACE IXuiDevice10

DECLARE_INTERFACE(IXuiDevice10)
{    
    STDMETHOD_(DWORD, AddRef)(THIS);
    STDMETHOD_(DWORD, Release)(THIS);

    STDMETHOD_(ID3D10Device*, GetD3DDevice)(THIS);
    STDMETHOD_(IXuiTextureCache *, GetTextureCache)(THIS);
    STDMETHOD_(const DXGI_SWAP_CHAIN_DESC *, GetSwapChainDesc)(THIS);

    STDMETHOD(CreateTexture2D)(THIS_ D3D10_TEXTURE2D_DESC *pDesc, const D3D10_SUBRESOURCE_DATA *pInitialData, ID3D10Texture2D **ppTexture2D);
    STDMETHOD(CreateShaderResourceView)(THIS_ ID3D10Resource *pResource, const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc, ID3D10ShaderResourceView **ppSRView);
    STDMETHOD_(void, PSSetShaderResources)(THIS_ UINT StartSlot, UINT NumViews, ID3D10ShaderResourceView *const *ppShaderResourceViews);
    STDMETHOD_(void, VSSetShaderResources)(THIS_ UINT StartSlot, UINT NumViews, ID3D10ShaderResourceView *const *ppShaderResourceViews);
 
    STDMETHOD(CreateBuffer)(THIS_ const D3D10_BUFFER_DESC *pDesc, const D3D10_SUBRESOURCE_DATA *pInitialData, ID3D10Buffer **ppBuffer);
    STDMETHOD(CreateInputLayout)(THIS_ const D3D10_INPUT_ELEMENT_DESC *pInputElementDescs, UINT NumElements,
            const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D10InputLayout **ppInputLayout);
    STDMETHOD_(void, IASetInputLayout)(THIS_ ID3D10InputLayout *pInputLayout);
    STDMETHOD_(void, PSSetConstantBuffers)(THIS_ UINT StartSlot, UINT NumBuffers, ID3D10Buffer *const *ppConstantBuffers);
    STDMETHOD_(void, VSSetConstantBuffers)(THIS_ UINT StartSlot, UINT NumBuffers, ID3D10Buffer *const *ppConstantBuffers);
    STDMETHOD_(void, IASetVertexBuffers)(THIS_ UINT StartSlot, UINT NumBuffers, ID3D10Buffer *const *ppVertexBuffers, const UINT *pStrides, const UINT *pOffsets);
    STDMETHOD_(void, IASetIndexBuffer)(THIS_ ID3D10Buffer *pIndexBuffer, DXGI_FORMAT Format, UINT Offset);
    STDMETHOD_(void, IASetPrimitiveTopology)(THIS_ D3D10_PRIMITIVE_TOPOLOGY Topology);

    STDMETHOD_(void, Draw)(THIS_ UINT VertexCount, UINT StartVertexLocation);
    STDMETHOD_(void, DrawIndexed)(THIS_ UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);

    STDMETHOD_(void, OMSetRenderTargets)(THIS_ UINT NumViews, ID3D10RenderTargetView *const *ppRenderTargetViews, ID3D10DepthStencilView *pDepthStencilView);
    STDMETHOD_(void, OMGetRenderTargets)(THIS_ UINT NumViews, ID3D10RenderTargetView **ppRenderTargetViews, ID3D10DepthStencilView **ppDepthStencilView);
    STDMETHOD_(void, ClearRenderTargetView)(THIS_ ID3D10RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);
    STDMETHOD_(void, ClearDepthStencilView)(THIS_ ID3D10DepthStencilView *pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil);

    STDMETHOD(CreateBlendState)(THIS_ const D3D10_BLEND_DESC *pBlendStateDesc, ID3D10BlendState **ppBlendState);
    STDMETHOD(CreateDepthStencilState)(THIS_ const D3D10_DEPTH_STENCIL_DESC *pDepthStencilDesc, ID3D10DepthStencilState **ppDepthStencilState);
    STDMETHOD(CreateRasterizerState)(THIS_ const D3D10_RASTERIZER_DESC *pRasterizerDesc, ID3D10RasterizerState **ppRasterizerState);
    STDMETHOD(CreateSamplerState)(THIS_ const D3D10_SAMPLER_DESC *pSamplerDesc, ID3D10SamplerState **ppSamplerState);
    STDMETHOD_(void, PSSetSamplers)(THIS_ UINT Offset,UINT NumSamplers,ID3D10SamplerState *const *ppSamplers);
    STDMETHOD_(void, RSGetState)(THIS_ ID3D10RasterizerState **ppRasterizerState);
    STDMETHOD_(void, RSSetState)(THIS_ ID3D10RasterizerState *pRasterizerState);
    STDMETHOD_(void, OMSetBlendState)(THIS_ ID3D10BlendState *pBlendState, const FLOAT BlendFactor[ 4 ], UINT SampleMask);
    STDMETHOD_(void, OMSetDepthStencilState)(THIS_ ID3D10DepthStencilState *pDepthStencilState,UINT StencilRef);

    STDMETHOD(CreateVertexShader)(THIS_ const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D10VertexShader **ppVertexShader);
    STDMETHOD(CreatePixelShader)(THIS_  const void *pShaderBytecode,  SIZE_T BytecodeLength, ID3D10PixelShader **ppPixelShader);
    STDMETHOD_(void, VSSetShader)(THIS_ ID3D10VertexShader *pVertexShader);
    STDMETHOD_(void, GSSetShader)(THIS_ ID3D10GeometryShader *pShader);
    STDMETHOD_(void, PSSetShader)(THIS_ ID3D10PixelShader *pPixelShader);

    STDMETHOD_(void, RSGetViewports)(THIS_ UINT *NumViewports, D3D10_VIEWPORT *pViewports);

    STDMETHOD(Texture2DMap)(THIS_ ID3D10Texture2D* pTexture2D, UINT Subresource, D3D10_MAP MapType, UINT Flags, D3D10_MAPPED_TEXTURE2D *pMappedTex2D);
    STDMETHOD_(void, Texture2DUnmap)(THIS_ ID3D10Texture2D* pTexture2D, UINT Subresource);
    STDMETHOD_(void, CopySubresourceRegion)(THIS_ ID3D10Resource* pDstResource, UINT DstSubresrouce, UINT DstX, UINT DstY, UINT DstZ, ID3D10Resource* pSrcResource, UINT SrcSubresource, const D3D10_BOX* pSrcBox);
    STDMETHOD(BufferMap)(THIS_ ID3D10Buffer* pBuffer, D3D10_MAP MapType, UINT MapFlags, void** ppData);
    STDMETHOD_(void, BufferUnmap)(THIS_ ID3D10Buffer* pBuffer);
    
    STDMETHOD(CalculateTextureMemorySize)(THIS_ IXuiTexture* pTex, DWORD *pdwSize);
};
#endif // XUI_USE_D3D10

// data structures
struct XUIRect
{
    DECLARE_XUI_ALLOC()

    float left;
    float top;
    float right;
    float bottom;
    
#ifdef __cplusplus
    XUIRect()
    {
    }

    XUIRect(float l, float t, float r, float b)
    {
        left = l;
        top = t;
        right = r;
        bottom = b;
    }
    
    float GetWidth() const
    {
        return right - left;
    }
    
    float GetHeight() const
    {
        return bottom - top;
    }
    
    BOOL Contains(const D3DXVECTOR2& pt) const
    {
        if (pt.x >= left && pt.x <= right &&
            pt.y >= top && pt.y <= bottom)
            return TRUE;
        return FALSE;
    }
#endif
};

struct XUIImageInfo
{
    DECLARE_XUI_ALLOC()
    UINT                 Width;
    UINT                 Height;
    UINT                 Depth;
    UINT                 MipLevels;
    UINT                 ImageFileFormat;   // D3D9:D3DXIMAGE_FILEFORMAT -or- D3DX10_IMAGE_FILE_FORMAT
#ifndef XUI_USE_D3D10
    D3DFORMAT            Format;
    D3DRESOURCETYPE      ResourceType;
#else
    UINT                 Format;         // D3D9:D3DFORMAT -or- D3D10:DXGI_FORMAT
    UINT                 ResourceType;   // D3D9:D3DRESOURCETYPE -or- D3D10:D3D10_RESOURCE_DIMENSION
#endif
};

struct XUIGradientStop
{
    DECLARE_XUI_ALLOC()

    DWORD dwColor;
    float fPos;
#ifdef __cplusplus
    XUIGradientStop()
    {
        dwColor = 0;
        fPos = 0.0f;
    }
#endif
};

struct XUIFigurePoint
{
    D3DXVECTOR2 point;
    D3DXVECTOR2 ptCtl1;
    D3DXVECTOR2 ptCtl2;
    BOOL bSmooth;
};

struct XUIRenderStats
{
    DECLARE_XUI_ALLOC()

    DWORD dwFaces;  // number of rendered triangles
    DWORD dwVerts;  // number of rendered vertices
    
    DWORD dwNumCachedTextures;      // total number of textures in the cache (includes unused textures)
    DWORD dwTextureMemory;          // approximate number of bytes used by active textures in the cache
    DWORD dwNumUnusedTextures;      // number of unused textures still in the cache
    DWORD dwUnusedTextureMemory;    // approximate number of bytes used by unreferenced textures in the cache
};

// blending modes
enum XUI_BLEND_MODE
{
    XUI_BLEND_DEFAULT,  // inherit current blending mode
    XUI_BLEND_NORMAL,
    XUI_BLEND_MULTIPLY,
    XUI_BLEND_DARKEN,
    XUI_BLEND_LIGHTEN,
    XUI_BLEND_ADD,
    XUI_BLEND_SUBTRACT
};



// color buffer write flags
#define XUI_COLOR_WRITE_DEFAULT         0
#define XUI_COLOR_WRITE_RED             1
#define XUI_COLOR_WRITE_GREEN           2
#define XUI_COLOR_WRITE_BLUE            4
#define XUI_COLOR_WRITE_ALPHA           8
#define XUI_COLOR_WRITE_ALL             (XUI_COLOR_WRITE_RED|XUI_COLOR_WRITE_GREEN|XUI_COLOR_WRITE_BLUE|XUI_COLOR_WRITE_ALPHA)

//
// Texture Loader
//
typedef HRESULT (APIENTRY *PFN_XUITEXTURELOADER)(IXuiDevice *pDevice, LPCWSTR szFileName, XUIImageInfo *pImageInfo, IDirect3DTexture9 **ppTex);
typedef HRESULT (APIENTRY *PFN_XUISHADERCOMPILER)(LPCSTR pSrcData, UINT srcDataLen, CONST D3DXMACRO* pDefines, 
                                                  LPD3DXINCLUDE pInclude, LPCSTR pFunctionName, LPCSTR pProfile, 
                                                  DWORD Flags, LPD3DXBUFFER* ppShader, LPD3DXBUFFER* ppErrorMsgs, 
                                                  LPD3DXCONSTANTTABLE *ppConstantTable);
#ifdef XUI_USE_D3D10
typedef HRESULT (APIENTRY *PFN_XUITEXTURELOADER10)(IXuiDevice10 *pDevice, LPCWSTR szFileName, XUIImageInfo *pImageInfo, ID3D10Texture2D **ppTex);
typedef HRESULT (APIENTRY *PFN_XUISHADERCOMPILER10)(LPCSTR pSrcData, SIZE_T SrcDataLen, LPCSTR pFileName, 
                                                    CONST D3D10_SHADER_MACRO* pDefines, LPD3D10INCLUDE pInclude, 
                                                    LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags, 
                                                    ID3D10Blob** ppShader, ID3D10Blob** ppErrorMsgs);
#endif

//
// Texture brush wrap modes (passed to XuiSelectBrushEx)
//
#define XUI_TEXTURE_U_WRAP        0
#define XUI_TEXTURE_U_MIRROR      1
#define XUI_TEXTURE_U_CLAMP       2
#define XUI_TEXTURE_U_MIRROR_ONCE 3
#define XUI_TEXTURE_U_MASK        3
#define XUI_TEXTURE_U_SHIFT       0

#define XUI_TEXTURE_V_WRAP        0
#define XUI_TEXTURE_V_MIRROR      4
#define XUI_TEXTURE_V_CLAMP       8
#define XUI_TEXTURE_V_MIRROR_ONCE 12
#define XUI_TEXTURE_V_MASK        12
#define XUI_TEXTURE_V_SHIFT       2

//
// Texture filtering modes (passed to XuiSelectBrushEx)
//
#define XUI_TEXTURE_MIN_LINEAR      0
#define XUI_TEXTURE_MIN_POINT       16
#define XUI_TEXTURE_MIN_MASK        16
#define XUI_TEXTURE_MIN_SHIFT       4

#define XUI_TEXTURE_MAG_LINEAR      0
#define XUI_TEXTURE_MAG_POINT       32
#define XUI_TEXTURE_MAG_MASK        32
#define XUI_TEXTURE_MAG_SHIFT       5

#define XUI_RENDER_FREE_EFFECT_RESOURCES   1

#define XUI_RENDER_INIT_PARAMS_NONE             0x00000000

#ifndef _XBOX
#define XUI_RENDER_INIT_PARAMS_DYNAMIC_TEX      0x00000001  // should be used when using IDirect3DDevice9Ex
#endif


//
// D3D Version Flags
// Passed into:
//  XuiCreateTextureCache()
//
#define XUI_D3D_VER9    9
#define XUI_D3D_VER10   10

typedef struct XUIRenderInitParams
{
    DWORD cbSize;
    DWORD dwFlags;

    IDirect3DDevice9 *pDevice;
    IXuiDevice *pXuiDevice;

    PFN_XUITEXTURELOADER pfnTextureLoader;

    const D3DPRESENT_PARAMETERS *pPresentParams;
    
    PFN_XUISHADERCOMPILER pfnShaderCompiler;

#ifdef XUI_USE_D3D10
    ID3D10Device *pDevice10;
    IXuiDevice10 *pXuiDevice10;
    const DXGI_SWAP_CHAIN_DESC *pswapdesc10;

    size_t  IndexBufferCount;
    size_t  NormalVertexBufferCount;
    size_t  TextVertexBufferCount;
    
    PFN_XUITEXTURELOADER10 pfnTextureLoader10;
    PFN_XUISHADERCOMPILER10 pfnShaderCompiler10;
#endif
} XUIRenderInitParams;

// Initialization
HRESULT APIENTRY XuiRenderInit(HWND hWnd, PFN_XUITEXTURELOADER pfnTextureLoader);
HRESULT APIENTRY XuiRenderInitShared(IDirect3DDevice9 *pDevice, const D3DPRESENT_PARAMETERS *pPresentParams, PFN_XUITEXTURELOADER pfnTextureLoader);
HRESULT APIENTRY XuiRenderInitEx(const XUIRenderInitParams *pInitParams);
HRESULT APIENTRY XuiRenderAttachDevice(IDirect3DDevice9 *pDevice, const D3DPRESENT_PARAMETERS *pPresentParams);
void    APIENTRY XuiRenderFreeResources(DWORD dwFlags);
HRESULT APIENTRY XuiRenderUninit();
void APIENTRY XuiRenderResolutionChanged(UINT uWidth, UINT uHeight);

HRESULT APIENTRY XuiCreateTextureCache(IXuiTextureCache **ppTextureCache, DWORD dwD3DVer);
void APIENTRY XuiDestroyTextureCache(IXuiTextureCache *pTextureCache);

// DC functions
HRESULT APIENTRY XuiRenderBegin(HXUIDC hDC, DWORD dwClearColor);
HRESULT APIENTRY XuiRenderEnd(HXUIDC hDC);
HRESULT APIENTRY XuiPreRenderBegin(HXUIDC hDC, DWORD dwClearColor);
HRESULT APIENTRY XuiPreRenderEnd(HXUIDC hDC);
HRESULT APIENTRY XuiRenderGetBackBufferSize(HXUIDC hDC, UINT *puWidth, UINT *puHeight);
HRESULT APIENTRY XuiRenderPresent(HXUIDC hDC, HWND hWnd, const RECT *prctSrc, const RECT *prctDest);
HRESULT APIENTRY XuiRenderCreateDC(HXUIDC *phDC);
HRESULT APIENTRY XuiRenderDCDeviceChanged(HXUIDC hDC);
HRESULT APIENTRY XuiRenderDestroyDC(HXUIDC hDC);
HRESULT APIENTRY XuiRenderRestoreState(HXUIDC hDC);
HRESULT APIENTRY XuiRenderGetDevice(HXUIDC hDC, IDirect3DDevice9 **ppDevice);
HRESULT APIENTRY XuiRenderGetXuiDevice(HXUIDC hDC, IXuiDevice **ppXuiDevice);
HRESULT APIENTRY XuiRenderSetTransform(HXUIDC hDC, const D3DXMATRIX *pmatXForm);
HRESULT APIENTRY XuiRenderSetViewTransform(HXUIDC hDC, const D3DXMATRIX *pmatXForm);
HRESULT APIENTRY XuiRenderGetViewTransform(HXUIDC hDC, D3DXMATRIX *pmatXForm);
HRESULT APIENTRY XuiSelectBrush(HXUIDC hDC, HXUIBRUSH hBrush);
HRESULT APIENTRY XuiSelectBrushEx(HXUIDC hDC, HXUIBRUSH hBrush, DWORD dwFlags);
HRESULT APIENTRY XuiFillRect(HXUIDC hDC, const XUIRect *pRect);
HRESULT APIENTRY XuiDrawShape(HXUIDC hDC, HXUISHAPE hShape);
HRESULT APIENTRY XuiStrokeShape(HXUIDC hDC, HXUISHAPE hShape, float fStrokeWidth, BOOL bClose);
HRESULT APIENTRY XuiSetTextDropShadowColor(HXUIDC hDC, DWORD dwColor);
HRESULT APIENTRY XuiGetTextDropShadowColor(HXUIDC hDC, DWORD *pdwColor);
HRESULT APIENTRY XuiSetColorFactor(HXUIDC hDC, DWORD dwColorFactor);
HRESULT APIENTRY XuiSetBlendMode(HXUIDC hDC, XUI_BLEND_MODE nBlendMode);
HRESULT APIENTRY XuiGetDCStats(HXUIDC hDC, XUIRenderStats *pStats);
HRESULT APIENTRY XuiSetWireFrame(BOOL bWireFrame);
HRESULT APIENTRY XuiSetColorWriteFlags(HXUIDC hDC, DWORD dwColorWriteFlags);

// Brush functions
HRESULT APIENTRY XuiCreateSolidBrush(DWORD dwColor, HXUIBRUSH *phBrush);
HRESULT APIENTRY XuiCreateTextureBrush(LPCWSTR szFileName, HXUIBRUSH *phBrush);
HRESULT APIENTRY XuiCreateTextureBrushFromMemory(LPBYTE pImageData, size_t ImageDataSize, HXUIBRUSH *phBrush);
HRESULT APIENTRY XuiAttachTextureBrush(IDirect3DTexture9 *pTex, HXUIBRUSH *phBrush);
HRESULT APIENTRY XuiCreateLinearGradientBrush(int nNumStops, const XUIGradientStop *pStops, HXUIBRUSH *phBrush);
HRESULT APIENTRY XuiCreateRadialGradientBrush(int nNumStops, const XUIGradientStop *pStops, HXUIBRUSH *phBrush);
HRESULT APIENTRY XuiBrushSetXForm(HXUIBRUSH hBrush, const D3DXMATRIX *pmatXForm);
HRESULT APIENTRY XuiBrushGetDims(HXUIBRUSH hBrush, UINT *puWidth, UINT *puHeight);
HRESULT APIENTRY XuiDestroyBrush(HXUIBRUSH hBrush);
HRESULT APIENTRY XuiBrushGetTexture(HXUIBRUSH hBrush, IXuiTexture **ppTex);

// Shape functions
HRESULT APIENTRY XuiRenderCreateShape(int nNumVertices, const D3DXVECTOR2 *pVerts, BOOL bReverseWinding, HXUISHAPE *phShape);
HRESULT APIENTRY XuiRenderDestroyShape(HXUISHAPE hShape);
HRESULT APIENTRY XuiShapeGetVertices(HXUISHAPE hShape, D3DXVECTOR2 **ppVerts, int *pnNumVerts, USHORT **ppuIndices, int *pnNumIndices);
HRESULT APIENTRY XuiRenderCreateShapeScale(const XUIFigurePoint *pPoints, int nNumPoints, const D3DXVECTOR2 *pvScalingFactor, HXUISHAPE *phShape);

// Texture functions
HRESULT APIENTRY XuiAddTexture(LPCWSTR szFileName, IDirect3DTexture9 *pTex, const XUIImageInfo *pImageInfo, HXUITEX *phTex);
HXUITEX APIENTRY XuiLookupTexture(LPCWSTR szFileName, IXuiTexture **ppTex, XUIImageInfo *pImageInfo);
void APIENTRY XuiReleaseTexture(HXUITEX hTexture, BOOL bRemove);
void APIENTRY XuiFreeUnusedTextures(BOOL bFlushAllUnused);
DWORD APIENTRY XuiSetTextureMemoryLimit(DWORD dwMemoryLimit);
HRESULT APIENTRY XuiGetTextureInfo(HXUITEX hTexture, IXuiTexture **ppTex, XUIImageInfo *pImageInfo);
HRESULT APIENTRY XuiCreateXuiTexture9(HXUIDC hDC, IDirect3DTexture9* pTexture, IXuiTexture** ppXuiTexture);

HRESULT APIENTRY XuiRenderSetTextureLoader(PFN_XUITEXTURELOADER pfnTextureLoader);
HRESULT APIENTRY XuiCreateTextureFromPNG(BYTE *pbInputBuffer, DWORD dwInputBufferLen, IXuiDevice *pDevice, IDirect3DTexture9 **ppTex, XUIImageInfo *pImageInfo);
// XuiD3DXTextureLoader may be removed in the future in order to eliminate dependency on D3DX. Xui
// clients should implement their own texture loader functions (registered via XuiRenderInit(...), etc.).
HRESULT APIENTRY XuiD3DXTextureLoader(IXuiDevice *pDevice, LPCWSTR szFileName, XUIImageInfo *pImageInfo, IDirect3DTexture9 **ppTex);
HRESULT APIENTRY XuiPNGTextureLoader(IXuiDevice *pDevice, LPCWSTR szFileName, XUIImageInfo *pImageInfo, IDirect3DTexture9 **ppTex);

// Text functions
typedef HRESULT (APIENTRY *PFN_XUIGLYPHSUBSTITUTION)(HXUIFONT hFont, WCHAR wch, DWORD instanceData, USHORT *pWidth, USHORT *pHeight,
                                                     USHORT *pAlignment, IXuiTexture **ppTexture, XUIRect *pTextureCoords);

// StyleFlags to be passed to XuiDrawText
#define XUI_FONT_STYLE_NORMAL                       0x00000000
#define XUI_FONT_STYLE_DROPSHADOW                   0x00000001
#define XUI_FONT_STYLE_ITALIC                       0x00000002
#define XUI_FONT_STYLE_BOLD                         0x00000004
#define XUI_FONT_STYLE_UNDERLINE                    0x00000008
#define XUI_FONT_STYLE_NO_WORDWRAP                  0x00000010
#define XUI_FONT_STYLE_SINGLE_LINE                  0x00000020
#define XUI_FONT_STYLE_LEFT_ALIGN                   0x00000100   // This is the default alignment
#define XUI_FONT_STYLE_RIGHT_ALIGN                  0x00000200
#define XUI_FONT_STYLE_CENTER_ALIGN                 0x00000400 
#define XUI_FONT_STYLE_VERTICAL_CENTER              0x00001000
#define XUI_FONT_STYLE_MEASURE_HEIGHT               0x00002000
#define XUI_FONT_STYLE_ELLIPSIS                     0x00004000
#define XUI_FONT_STYLE_LINEBREAK_USE_DEFAULT        0x00000000  // Uses default or globally set linebreak style
#define XUI_FONT_STYLE_LINEBREAK_LEFT_HANGUL_WORD   0x00010000  // Word and Char are mutually exclusive...
#define XUI_FONT_STYLE_LINEBREAK_LEFT_HANGUL_CHAR   0x00020000
#define XUI_FONT_STYLE_LINEBREAK_CENTER_HANGUL_WORD 0x00040000
#define XUI_FONT_STYLE_LINEBREAK_CENTER_HANGUL_CHAR 0x00080000
#define XUI_FONT_STYLE_LINEBREAK_RIGHT_HANGUL_WORD  0x00100000
#define XUI_FONT_STYLE_LINEBREAK_RIGHT_HANGUL_CHAR  0x00200000
#define XUI_FONT_STYLE_LINEBREAK_MASK               0x003F0000

// Alignment flags for glyph substitution callback
#define XUI_FONT_GLYPH_SUBST_ALIGN_TOP                0
#define XUI_FONT_GLYPH_SUBST_ALIGN_CENTER             1
#define XUI_FONT_GLYPH_SUBST_ALIGN_BASELINE           2
#define XUI_FONT_GLYPH_SUBST_ALIGN_BOTTOM             3

HRESULT APIENTRY XuiCreateFont(LPCWSTR lpszTypeface, FLOAT fPointSize, DWORD dwStyle, DWORD dwReserved, HXUIFONT * phFont);
HRESULT APIENTRY XuiSelectFont(HXUIDC hDC, HXUIFONT hFont);
HRESULT APIENTRY XuiMeasureText(HXUIFONT hFont, LPCWSTR lpszText, int cch, DWORD dwStyleFlags, int iLineSpacingAdjust, XUIRect * pRect);
HRESULT APIENTRY XuiDrawText(HXUIDC hDC, LPCWSTR lpszText, DWORD dwStyleFlags, int iLineSpacingAdjust, XUIRect * pRect);
HRESULT APIENTRY XuiDrawTextEx(HXUIDC hDC, LPCWSTR lpszText, int cch, DWORD dwStyleFlags, int iLineSpacingAdjust, XUIRect * pRect, float vScroll);
HRESULT APIENTRY XuiGetTextBreaks(HXUIFONT hFont, LPCWSTR lpszText, int cch, DWORD dwStyleFlags, int iLineSpacingAdjust, BOOL fIgnoreHeight, XUIRect * pRect, UINT *pnCount, UINT ** pLineOffsets);
HRESULT APIENTRY XuiGetFontHeight(HXUIFONT hFont, UINT * pnHeight);
HRESULT APIENTRY XuiGetFontMetrics(HXUIFONT hFont, XUIFontMetrics *pFontMetrics);
HRESULT APIENTRY XuiGetCharMetrics(HXUIFONT hFont, WCHAR wch, XUICharMetrics *pCharMetrics);
HRESULT APIENTRY XuiGetDefaultLineBreakStyle(DWORD *pdwLineBreakStyle);
HRESULT APIENTRY XuiSetDefaultLineBreakStyle(DWORD dwLineBreakStyle);
HRESULT APIENTRY XuiSubstituteGlyph(WCHAR wch, PFN_XUIGLYPHSUBSTITUTION pfnCallback, DWORD dwInstanceData);

VOID APIENTRY XuiReleaseFont(HXUIFONT hFont);

// Replaceable text renderer definitions

typedef HANDLE HFONTOBJ;

#define XUI_FONT_RENDERER_CAP_INTERNAL_GLYPH_CACHE   0x00000001
#define XUI_FONT_RENDERER_CAP_POINT_SIZE_RESPECTED   0x00000002

#define XUI_FONT_RENDERER_STYLE_DROPSHADOW           0x00000001


typedef struct TypefaceDescriptor
{
    LPCWSTR szTypeface;
    LPCWSTR szLocator;
    LPCWSTR szReserved1;
    float   fBaselineAdjust;
    LPCWSTR szFallbackTypeface;
} TypefaceDescriptor;

struct XUIFontMetrics
{
   DECLARE_XUI_ALLOC()
 
   // units are pixels at current font size

   float fLineHeight; // font line height
   float fMaxAscent;  // max ascent above baseline
   float fMaxDescent; // max descent below baseline
   float fMaxWidth;   // max character width
   float fMaxHeight;  // max character height
   float fMaxAdvance; // max advance
};

struct XUICharMetrics
{
   DECLARE_XUI_ALLOC()

   // units are pixels at current font size

   float fMinX;    // min x coordinate
   float fMinY;    // min y coordinate
   float fMaxX;    // max x coordinate
   float fMaxY;    // max y coordinate
   float fAdvance; // advance value
};

struct CharData
{
    WCHAR wch;
    DWORD dwStyle;
    DWORD dwColor;
    float x, y;
};

#undef  INTERFACE
#define INTERFACE IXuiFontRenderer
DECLARE_INTERFACE(IXuiFontRenderer)
{    
    STDMETHOD(Init)(THIS_ float fDpi);
    STDMETHOD_(VOID, Term)(THIS);
    STDMETHOD(GetCaps)(THIS_ DWORD * pdwCaps);
    STDMETHOD(CreateFont)(THIS_ const TypefaceDescriptor * pTypefaceDescriptor, float fPointSize, DWORD dwStyle, DWORD dwReserved, HFONTOBJ * phFont);
    STDMETHOD_(VOID, ReleaseFont)(THIS_ HFONTOBJ hFont);
    STDMETHOD(GetFontMetrics)(THIS_ HFONTOBJ hFont, XUIFontMetrics *pFontMetrics);
    STDMETHOD(GetCharMetrics)(THIS_ HFONTOBJ hFont, WCHAR wch, XUICharMetrics *pCharMetrics);
    STDMETHOD(DrawCharToTexture)(THIS_ HFONTOBJ hFont, WCHAR wch, HXUIDC hDC, IXuiTexture *pTexture, UINT x, UINT y, UINT width, UINT height, UINT insetX, UINT insetY);
    STDMETHOD(DrawCharsToDevice)(THIS_ HFONTOBJ hFont, CharData * pCharData, DWORD dwCount, RECT *pClipRect, HXUIDC hDC, D3DXMATRIX * pWorldViewProj);
};

HRESULT APIENTRY XuiFontSetRenderer(IXuiFontRenderer * pRenderer);


// Helper functions
HRESULT APIENTRY XuiCreateGradientTexture(int nWidth, int nNumStops, const XUIGradientStop *pStops, IXuiTexture **pTex);
BOOL APIENTRY XuiPointInRect(const XUIRect *pRect, const D3DXVECTOR2 *pPoint);

// D3D10 Specific functions
#ifdef XUI_USE_D3D10
HRESULT APIENTRY XuiD3DX10TextureLoader(IXuiDevice10 *pDevice, LPCWSTR szFileName, XUIImageInfo *pImageInfo, ID3D10Texture2D **ppTex);
HRESULT APIENTRY XuiWindowsCodecsTextureLoader10(IXuiDevice10 *pDevice, LPCWSTR szFileName, XUIImageInfo *pImageInfo, ID3D10Texture2D **ppTex);
HRESULT APIENTRY XuiUpdateTextureFromImage10(
                    const BYTE *pInputBuffer, 
                    DWORD InputBufferLen, 
                    IXuiDevice10 *pDevice, 
                    ID3D10Texture2D *pTexture, 
                    XUIImageInfo *pImageInfo);
HRESULT APIENTRY XuiDecompressImageFromMemory10(
                    const BYTE *pInputBuffer, 
                    DWORD InputBufferLen, 
                    IXuiDevice10 *pDevice,
                    PBYTE  pbTexture,
                    DWORD  dwPitch,
                    DWORD  dwHeight,
                    XUIImageInfo *pImageInfo);
HRESULT APIENTRY XuiRenderGetXuiDevice10(HXUIDC hDC, IXuiDevice10 **ppXuiDevice);
HRESULT APIENTRY XuiAttachTextureBrush10(ID3D10Texture2D *pTex, HXUIBRUSH *phBrush);
HRESULT APIENTRY XuiAddTexture10(LPCWSTR szFileName, ID3D10Texture2D *pTex, const XUIImageInfo *pImageInfo, HXUITEX *phTex);
HRESULT APIENTRY XuiCreateXuiTexture10(HXUIDC hDC, ID3D10Texture2D* pTexture, IXuiTexture** ppXuiTexture);
#endif // XUI_USE_D3D10

#ifdef __cplusplus
}
#endif

#endif // __XUIRENDER_H__

