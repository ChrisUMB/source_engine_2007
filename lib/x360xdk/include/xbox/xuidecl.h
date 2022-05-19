/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       xuiprivate.h
 *  Content:    Xbox 360 UI runtime defines, structures and functions
 *
 ****************************************************************************/

#ifndef __XUIDECL_H__
#define __XUIDECL_H__

typedef struct XUIElementPropDef XUIElementPropDef;
typedef struct XUIElementPropVal XUIElementPropVal;
typedef struct IXUIPropObj IXUIPropObj;
typedef struct XUIMemoryBuffer XUIMemoryBuffer;

#define XUI_KILLING_FOCUS    FALSE
#define XUI_SETTING_FOCUS   TRUE

#define TIMELINE_STATE_STOPPED      0x00000001
#define TIMELINE_STATE_START        0x00000002

typedef struct XUIMessageFigureGetCount XUIMessageFigureGetCount;
typedef struct XUIMessageFigurePoint XUIMessageFigurePoint;
typedef struct XUIMessageFigurePointIndex XUIMessageFigurePointIndex;
typedef struct XUIMessageFigureVertexPoint XUIMessageFigureVertexPoint;

#define XM_FIGURE_GET_COUNT         1000
#define XM_FIGURE_ADD_POINT         1001
#define XM_FIGURE_DELETE_POINT      1002
#define XM_FIGURE_GET_POINTS        1003
#define XM_FIGURE_SET_POINTS        1004
#define XM_FIGURE_GET_NEXT_POINT    1005
#define XM_FIGURE_GET_PREV_POINT    1006
#define XM_FIGURE_VERTEX_FROM_POINT 1007

typedef struct IXUIPropObjVTBL
{
    const XUIElementPropDef* (*GetPropDef)(IXUIPropObj* pThis, DWORD *pdwCount);
    HRESULT (*GetPropertyId)(IXUIPropObj* pThis, LPCWSTR szPropName, DWORD *pdwId);
    HRESULT (*GetPropertyDef)(IXUIPropObj* pThis, LPCWSTR szPropName, const XUIElementPropDef **ppDef);
    HRESULT (*GetPropertyRef)(IXUIPropObj* pThis, DWORD dwPropId, void **ppvData);
    HRESULT (*GetProperty)(IXUIPropObj* pThis, DWORD dwPropId, DWORD dwIndex, XUIElementPropVal *pVal);
    HRESULT (*SetProperty)(IXUIPropObj* pThis, DWORD dwPropId, DWORD dwIndex, const XUIElementPropVal *pVal);
    HRESULT (*GetPropertyCount)(IXUIPropObj* pThis, DWORD dwPropId, DWORD *pdwCount);
} IXUIPropObjVTBL;

typedef struct IXUIPropObj
{
#ifdef __cplusplus

    virtual const XUIElementPropDef *GetPropDef(DWORD *pdwCount) = 0;
    virtual HRESULT GetPropertyId(LPCWSTR szPropName, DWORD *pdwId) = 0;
    virtual HRESULT GetPropertyDef(LPCWSTR szPropName, const XUIElementPropDef **ppDef) = 0;
    virtual HRESULT GetPropertyRef(DWORD dwPropId, void **ppvData) = 0;
    virtual HRESULT GetProperty(DWORD dwPropId, DWORD dwIndex, XUIElementPropVal *pVal) = 0;
    virtual HRESULT SetProperty(DWORD dwPropId, DWORD dwIndex, const XUIElementPropVal *pVal) = 0;
    virtual HRESULT GetPropertyCount(DWORD dwPropId, DWORD *pdwCount) = 0;

#else

    struct IXUIPropObjVTBL* pVtbl;

#endif
} IXUIPropObj;

typedef struct XUICustomPropHandler
{
    HRESULT (*Set)(void *pvVal, void *pvSrc, void *pvThis);
    HRESULT (*Get)(void *pvVal, void *pvDest, void *pvThis);
    HRESULT (*ToString)(void *pvVal, WCHAR **ppszDest, void *pvThis);
    HRESULT (*FromString)(void *pvVal, LPCWSTR szSrc, void *pvThis);
    HRESULT (*ToBinary)(void *pvVal, XUIMemoryBuffer * pDest, void *pvThis);
    HRESULT (*FromBinary)(void *pvVal, const BYTE * pb, UINT cb, void *pvThis);
    BOOL (*IsEqual)(void *pvVal, void *pvOther, void *pvThis);
    HRESULT (*ShowUI)(void *pvThis, IXUIPropObj *pObj, HWND hWndParent);
} XUICustomPropHandler;

void APIENTRY XUIMemoryBuffer_Construct(XUIMemoryBuffer* pThis);
void APIENTRY XUIMemoryBuffer_Destruct(XUIMemoryBuffer* pThis);
UINT APIENTRY XUIMemoryBuffer_Append(XUIMemoryBuffer* pThis, VOID * pv, UINT cb);
UINT APIENTRY XUIMemoryBuffer_AppendUint(XUIMemoryBuffer* pThis, UINT ui);
UINT APIENTRY XUIMemoryBuffer_AppendByte(XUIMemoryBuffer* pThis, BYTE b);
UINT APIENTRY XUIMemoryBuffer_AppendUlong(XUIMemoryBuffer* pThis, ULONG ul);
UINT APIENTRY XUIMemoryBuffer_AppendUshort(XUIMemoryBuffer* pThis, USHORT us);
UINT APIENTRY XUIMemoryBuffer_AppendBool(XUIMemoryBuffer* pThis, BOOL f);
UINT APIENTRY XUIMemoryBuffer_AppendInt(XUIMemoryBuffer* pThis, int i);
UINT APIENTRY XUIMemoryBuffer_AppendFloat(XUIMemoryBuffer* pThis, FLOAT f);
UINT APIENTRY XUIMemoryBuffer_AppendWchar(XUIMemoryBuffer* pThis, WCHAR * pwsz);
UINT APIENTRY XUIMemoryBuffer_AppendMemoryBuffer(XUIMemoryBuffer* pThis, XUIMemoryBuffer * pBuf);
UINT APIENTRY XUIMemoryBuffer_RewindBytes(XUIMemoryBuffer* pThis, UINT cb);
VOID APIENTRY XUIMemoryBuffer_WriteByte(XUIMemoryBuffer* pThis, ULONG pos, BYTE data);
VOID APIENTRY XUIMemoryBuffer_WriteUshort(XUIMemoryBuffer* pThis, ULONG pos, USHORT data);
VOID APIENTRY XUIMemoryBuffer_WriteUlong(XUIMemoryBuffer* pThis, ULONG pos, ULONG data);
BYTE* APIENTRY XUIMemoryBuffer_Data(XUIMemoryBuffer* pThis);
UINT APIENTRY XUIMemoryBuffer_Size(XUIMemoryBuffer* pThis);
BOOL APIENTRY XUIMemoryBuffer_Init(XUIMemoryBuffer* pThis, UINT cb);

typedef struct XUIMemoryBuffer
{
    DECLARE_XUI_ALLOC()

    BYTE * m_pb;
    UINT m_cbUsed;
    UINT m_cbTotal;

#ifdef __cplusplus

    XUIMemoryBuffer()
    {
        XUIMemoryBuffer_Construct(this);
    }
    ~XUIMemoryBuffer()
    {
        XUIMemoryBuffer_Destruct(this);
    }
    UINT Append(VOID * pv, UINT cb)
    {
        return XUIMemoryBuffer_Append(this, pv, cb);
    }
    UINT Append(UINT ui)
    {
        return XUIMemoryBuffer_AppendUint(this, ui);
    }
    UINT Append(BYTE b)
    {
        return XUIMemoryBuffer_AppendByte(this, b);
    }
    UINT Append(ULONG ul)
    {
        return XUIMemoryBuffer_AppendUlong(this, ul);
    }
    UINT Append(USHORT us)
    {
        return XUIMemoryBuffer_AppendUshort(this, us);
    }
    UINT AppendBool(BOOL f)
    {
        return XUIMemoryBuffer_AppendBool(this, f);
    }
    UINT Append(int i)
    {
        return XUIMemoryBuffer_AppendInt(this, i);
    }
    UINT Append(FLOAT f)
    {
        return XUIMemoryBuffer_AppendFloat(this, f);
    }
    UINT Append(WCHAR * pwsz)
    {
        return XUIMemoryBuffer_AppendWchar(this, pwsz);
    }
    UINT Append(XUIMemoryBuffer * pBuf)
    {
        return XUIMemoryBuffer_AppendMemoryBuffer(this, pBuf);
    }
    UINT RewindBytes(UINT cb)
    {
        return XUIMemoryBuffer_RewindBytes(this, cb);
    }
    VOID WriteByte(ULONG pos, BYTE data)
    {
        XUIMemoryBuffer_WriteByte(this, pos, data);
    }
    VOID WriteUshort(ULONG pos, USHORT data)
    {
        XUIMemoryBuffer_WriteUshort(this, pos, data);
    }
    VOID WriteUlong(ULONG pos, ULONG data)
    {
        XUIMemoryBuffer_WriteUlong(this, pos, data);
    }
    BYTE * Data()
    {
        return XUIMemoryBuffer_Data(this);
    }
    UINT Size()
    {
        return XUIMemoryBuffer_Size(this);
    }
    BOOL Init(UINT cb)
    {
        return XUIMemoryBuffer_Init(this, cb);
    }
#endif
} XUIMemoryBuffer;

struct XUIMessageFigureGetCount
{
    int nCount;
};

static __declspec(noinline) void XuiMessageFigureGetCount(XUIMessage *pMsg, XUIMessageFigureGetCount* pData)
{
    XuiMessage(pMsg,XM_FIGURE_GET_COUNT);
    _XuiMessageExtra(pMsg,(XUIMessageData*) pData, sizeof(*pData));
}

typedef struct XUIFigurePoint XUIFigurePoint;
struct XUIMessageFigurePoint
{
    int nPointIndex;
    XUIFigurePoint *pPoint;
    int nCount;
};

static __declspec(noinline) void XuiMessageFigureAddPoint(XUIMessage *pMsg, XUIMessageFigurePoint* pData, int nPointIndex, const XUIFigurePoint *pPoint)
{
    XuiMessage(pMsg,XM_FIGURE_ADD_POINT);
    _XuiMessageExtra(pMsg,(XUIMessageData*) pData, sizeof(*pData));
    pData->nPointIndex = nPointIndex;
    pData->pPoint = (XUIFigurePoint *) pPoint;
}

static __declspec(noinline) void XuiMessageFigureDeletePoint(XUIMessage *pMsg, XUIMessageFigurePoint* pData, int nPointIndex)
{
    XuiMessage(pMsg,XM_FIGURE_DELETE_POINT);
    _XuiMessageExtra(pMsg,(XUIMessageData*) pData, sizeof(*pData));
    pData->nPointIndex = nPointIndex;
}

static __declspec(noinline) void XuiMessageFigureGetPoints(XUIMessage *pMsg, XUIMessageFigurePoint* pData, int nPointIndex, XUIFigurePoint *pPoint, int nCount)
{
    XuiMessage(pMsg,XM_FIGURE_GET_POINTS);
    _XuiMessageExtra(pMsg,(XUIMessageData*) pData, sizeof(*pData));
    pData->nPointIndex = nPointIndex;
    pData->pPoint = pPoint;
    pData->nCount = nCount;
}

static __declspec(noinline) void XuiMessageFigureSetPoints(XUIMessage *pMsg, XUIMessageFigurePoint* pData, int nPointIndex, const XUIFigurePoint *pPoint, int nCount)
{
    XuiMessage(pMsg,XM_FIGURE_SET_POINTS);
    _XuiMessageExtra(pMsg,(XUIMessageData*) pData, sizeof(*pData));
    pData->nPointIndex = nPointIndex;
    pData->pPoint = (XUIFigurePoint *) pPoint;
    pData->nCount = nCount;
}

struct XUIMessageFigurePointIndex
{
    int nPointIndex;
    int nOtherIndex;
};

static __declspec(noinline) void XuiMessageFigureGetNextPoint(XUIMessage *pMsg, XUIMessageFigurePointIndex* pData, int nPointIndex)
{
    XuiMessage(pMsg,XM_FIGURE_GET_NEXT_POINT);
    _XuiMessageExtra(pMsg,(XUIMessageData*) pData, sizeof(*pData));
    pData->nPointIndex = nPointIndex;
}

static __declspec(noinline) void XuiMessageFigureGetPrevPoint(XUIMessage *pMsg, XUIMessageFigurePointIndex* pData, int nPointIndex)
{
    XuiMessage(pMsg,XM_FIGURE_GET_PREV_POINT);
    _XuiMessageExtra(pMsg,(XUIMessageData*) pData, sizeof(*pData));
    pData->nPointIndex = nPointIndex;
}

struct XUIMessageFigureVertexPoint
{
    D3DXVECTOR2 point;
    int nVertex;
};

static __declspec(noinline) void XuiMessageFigureVertexFromPoint(XUIMessage *pMsg, XUIMessageFigureVertexPoint* pData, const D3DXVECTOR2 *pt)
{
    XuiMessage(pMsg,XM_FIGURE_VERTEX_FROM_POINT);
    _XuiMessageExtra(pMsg,(XUIMessageData*) pData, sizeof(*pData));
    pData->point = *pt;
}

#endif // __XUIDECL_H__
