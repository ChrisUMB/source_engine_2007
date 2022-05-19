/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       xuibase.h
 *  Content:    Xbox 360 UI runtime defines, structures and functions
 *
 ****************************************************************************/

#ifndef __XUIBASE_H__
#define __XUIBASE_H__

#pragma warning(disable : 4505)

#pragma warning(push)
#pragma warning(disable: 4201)  // unnamed struct/union

#define XUI_VERSION     0x000C      // high byte is the major version, and the low byte is the minor version

#ifdef __cplusplus
extern "C" {
#endif

#include <sal.h>

typedef struct XUIMessage
{
    DWORD cbSize;
    DWORD dwMessage;
    BOOL bHandled;
    size_t cbData;
    void *pvData;
} XUIMessage;

static __declspec(noinline) void XuiMessage(XUIMessage *pMsg, DWORD dwMessage)
{
    memset(pMsg,0x00,sizeof(*pMsg));
    pMsg->cbSize = sizeof(*pMsg);
    pMsg->dwMessage = dwMessage;
}

typedef void XUIMessageData;

static __declspec(noinline) void _XuiMessageExtra(XUIMessage *pMsg, __out_bcount_full(cbData) XUIMessageData* pData, size_t cbData)
{
    pMsg->pvData = pData;
    memset(pData,0x00,cbData);
    pMsg->cbData = cbData;
}

#include "xuidecl.h"

typedef struct _XUIOBJ* HXUIOBJ;
typedef struct _XUICLASS* HXUICLASS;
typedef struct _XUISTRINGTABLE* HXUISTRINGTABLE;
typedef struct XUIQuaternion XUIQuaternion;
typedef struct XUIMessage XUIMessage;
typedef struct XUIObjectMethods XUIObjectMethods;
typedef struct XUIClass XUIClass;
typedef struct XUIInitParams XUIInitParams;
typedef struct IXUIRuntimeHooks IXUIRuntimeHooks;
typedef struct IXUIRuntimeHooksVTBL IXUIRuntimeHooksVTBL;
typedef struct XUIElementPropDef XUIElementPropDef;
typedef struct XUIElementPropVal XUIElementPropVal;
typedef enum XUI_ELEMENT_PROPERTY_TYPE XUI_ELEMENT_PROPERTY_TYPE;

typedef const XUIElementPropDef* (APIENTRY *PFN_GETPROPDEF)(DWORD *pdwCount);

typedef HRESULT (APIENTRY *PFN_GETPROP)(DWORD dwIndex, PVOID pvObj, XUIElementPropVal *pVal);
typedef HRESULT (APIENTRY *PFN_SETPROP)(DWORD dwIndex, PVOID pvObj, const XUIElementPropVal *pVal);
typedef HRESULT (APIENTRY *PFN_GETCOUNT)(PVOID pvObj, DWORD *pdwCount);

enum XUI_ELEMENT_PROPERTY_TYPE
{
    XUI_EPT_EMPTY,
    XUI_EPT_BOOL,
    XUI_EPT_INTEGER,
    XUI_EPT_UNSIGNED,
    XUI_EPT_FLOAT,
    XUI_EPT_STRING,
    XUI_EPT_COLOR,
    XUI_EPT_VECTOR,
    XUI_EPT_QUATERNION,
    XUI_EPT_OBJECT,
    XUI_EPT_CUSTOM
};

struct XUIElementPropDef
{
    DECLARE_XUI_ALLOC()

    DWORD dwFlags;
    DWORD dwId;
    DWORD dwOffset;
    DWORD dwExtra;
    LPCWSTR szPropName;
    XUI_ELEMENT_PROPERTY_TYPE Type;
    const XUIElementPropVal *pDefaultVal;
    XUICustomPropHandler *pCustomHandler;
    PFN_GETPROP pfnGetProp;
    PFN_SETPROP pfnSetProp;
    PFN_GETPROPDEF pfnGetPropDef;
    PFN_GETCOUNT pfnGetCount;

#ifndef _XBOX
    LPCWSTR szPropertyEditor;
#endif
};

// property flags
#define XUI_ELEMENT_PROPF_NONE      0x0000       // no flags specified
#define XUI_ELEMENT_PROPF_INDEXED   0x0001       // the property is indexed
#define XUI_ELEMENT_PROPF_HIDDEN    0x0002       // the property is hidden in the design time environment
#define XUI_ELEMENT_PROPF_LOCALIZE  0x0004       // the property is localizable
#define XUI_ELEMENT_PROPF_NOANIM    0x0008       // the property must not be animated
#define XUI_ELEMENT_PROPF_FILEPATH  0x0010       // the property represents a file path
#define XUI_ELEMENT_PROPF_EVENT     0x0020       // treat as an event (set on keyframes only)
#define XUI_ELEMENT_PROPF_DESIGN    0x0040       // design time only property

struct XUIQuaternion
{
    DECLARE_XUI_ALLOC()

    float x;
    float y;
    float z;
    float w;

#ifdef __cplusplus

    D3DXQUATERNION& operator=(const D3DXQUATERNION& q)
    {
        x = q.x;
        y = q.y;
        z = q.z;
        w = q.w;
        return *((D3DXQUATERNION *) this);
    }

    operator D3DXQUATERNION&()
    {
        return *((D3DXQUATERNION *) this);
    }

#endif
};

void APIENTRY XUIElementPropVal_Construct(XUIElementPropVal* pThis);
void APIENTRY XUIElementPropVal_Destruct(XUIElementPropVal* pThis);
void APIENTRY XUIElementPropVal_ConstructFromInt(XUIElementPropVal* pThis, int n);
void APIENTRY XUIElementPropVal_ConstructFromUint(XUIElementPropVal* pThis, unsigned int u);
void APIENTRY XUIElementPropVal_ConstructFromFloat(XUIElementPropVal* pThis, float f);
void APIENTRY XUIElementPropVal_ConstructFromD3DXVECTOR(XUIElementPropVal* pThis, const D3DXVECTOR3* vOther);
void APIENTRY XUIElementPropVal_ConstructFromD3DXQUATERNION(XUIElementPropVal* pThis, const D3DXQUATERNION* qOther);
void APIENTRY XUIElementPropVal_Clear(XUIElementPropVal* pThis);
void APIENTRY XUIElementPropVal_Reset(XUIElementPropVal* pThis);
void APIENTRY XUIElementPropVal_SetBool(XUIElementPropVal* pThis, BOOL val);
void APIENTRY XUIElementPropVal_SetInt(XUIElementPropVal* pThis, int val);
void APIENTRY XUIElementPropVal_SetUint(XUIElementPropVal* pThis, unsigned int val);
void APIENTRY XUIElementPropVal_SetFloat(XUIElementPropVal* pThis, float val);
void APIENTRY XUIElementPropVal_SetColorFromUint(XUIElementPropVal* pThis, unsigned int val);
void APIENTRY XUIElementPropVal_SetColorFromARGB(XUIElementPropVal* pThis, BYTE a, BYTE r, BYTE g, BYTE b);
HRESULT APIENTRY XUIElementPropVal_SetString(XUIElementPropVal* pThis, LPCWSTR val);
void APIENTRY XUIElementPropVal_SetD3DVECTOR(XUIElementPropVal* pThis, const D3DVECTOR *val);
void APIENTRY XUIElementPropVal_SetD3DVECTOR3(XUIElementPropVal* pThis, const D3DXVECTOR3 *val);
void APIENTRY XUIElementPropVal_SetXUIQuaternion(XUIElementPropVal* pThis, const XUIQuaternion *val);
void APIENTRY XUIElementPropVal_SetD3DXQUATERNION(XUIElementPropVal* pThis, const D3DXQUATERNION *val);
void APIENTRY XUIElementPropVal_SetIXUIPropObj(XUIElementPropVal* pThis, IXUIPropObj *pObject);
void APIENTRY XUIElementPropVal_SetCustom(XUIElementPropVal* pThis, void *pvData, XUICustomPropHandler *pSrcHandler);
HRESULT APIENTRY XUIElementPropVal_Copy(XUIElementPropVal* pThis, const XUIElementPropVal *pVal);
HRESULT APIENTRY XUIElementPropVal_GetStringLen(XUIElementPropVal* pThis, size_t *pdwLen);
HRESULT APIENTRY XUIElementPropVal_ToString(XUIElementPropVal* pThis, WCHAR **szDest);
HRESULT APIENTRY XUIElementPropVal_ToBinary(XUIElementPropVal* pThis, XUIMemoryBuffer * pDest);
BOOL APIENTRY XUIElementPropVal_IsEqual(XUIElementPropVal* pThis, const XUIElementPropVal *pOther);

struct XUIElementPropVal
{
    DECLARE_XUI_ALLOC()

    XUI_ELEMENT_PROPERTY_TYPE type;
    union
    {
        BOOL bVal;
        int nVal;
        unsigned int uVal;
        float fVal;
        WCHAR *szVal;
        D3DVECTOR vecVal;
        XUIQuaternion quatVal;
        IXUIPropObj *pObj;
        struct
        {
            void *pvCustomData; // pointer to custom data type
            XUICustomPropHandler *pHandler;
        } CustomVal;
    };

#ifdef __cplusplus

    XUIElementPropVal()
    {
        XUIElementPropVal_Construct(this);
    }
    ~XUIElementPropVal()
    {
        XUIElementPropVal_Destruct(this);
    }
    XUIElementPropVal(int n)
    {
        XUIElementPropVal_ConstructFromInt(this, n);
    }
    XUIElementPropVal(unsigned int u)
    {
        XUIElementPropVal_ConstructFromUint(this, u);
    }
    XUIElementPropVal(float f)
    {
        XUIElementPropVal_ConstructFromFloat(this, f);
    }
    XUIElementPropVal(const D3DXVECTOR3& vOther)
    {
        XUIElementPropVal_ConstructFromD3DXVECTOR(this, &vOther);
    }
    XUIElementPropVal(const D3DXQUATERNION& qOther)
    {
        XUIElementPropVal_ConstructFromD3DXQUATERNION(this, &qOther);
    }
    void Clear()
    {
        XUIElementPropVal_Clear(this);
    }
    void Reset()
    {
        XUIElementPropVal_Reset(this);
    }
    void SetVal(bool val)
    {
        XUIElementPropVal_SetBool(this, (BOOL) val);
    }
    void SetBoolVal(BOOL val)
    {
        XUIElementPropVal_SetBool(this, val);
    }
    void SetVal(int val)
    {
        XUIElementPropVal_SetInt(this, val);
    }
    void SetVal(unsigned int val)
    {
        XUIElementPropVal_SetUint(this, val);
    }
    void SetVal(float val)
    {
        XUIElementPropVal_SetFloat(this, val);
    }
    void SetColorVal(unsigned int val)
    {
        XUIElementPropVal_SetColorFromUint(this, val);
    }
    void SetColorVal(BYTE a, BYTE r, BYTE g, BYTE b)
    {
        XUIElementPropVal_SetColorFromARGB(this, a, r, g, b);
    }
    HRESULT SetVal(LPCWSTR val)
    {
        return XUIElementPropVal_SetString(this, val);
    }
    void SetVal(const D3DVECTOR *val)
    {
        XUIElementPropVal_SetD3DVECTOR(this, val);
    }
    void SetVal(const D3DVECTOR &val)
    {
        XUIElementPropVal_SetD3DVECTOR(this, &val);
    }
    void SetVal(const D3DXVECTOR3 *val)
    {
        XUIElementPropVal_SetD3DVECTOR(this, val);
    }
    void SetVal(const XUIQuaternion *val)
    {
        XUIElementPropVal_SetXUIQuaternion(this, val);
    }
    void SetVal(const D3DXQUATERNION &val)
    {
        XUIElementPropVal_SetD3DXQUATERNION(this, &val);
    }
    void SetVal(const D3DXQUATERNION *val)
    {
        XUIElementPropVal_SetD3DXQUATERNION(this, val);
    }
    void SetVal(IXUIPropObj *pObject)
    {
        XUIElementPropVal_SetIXUIPropObj(this, pObject);
    }
    void SetVal(void *pvData, XUICustomPropHandler *pSrcHandler)
    {
        XUIElementPropVal_SetCustom(this, pvData, pSrcHandler);
    }
    HRESULT Copy(const XUIElementPropVal *pVal)
    {
        return XUIElementPropVal_Copy(this, pVal);
    }
    HRESULT GetStringLen(size_t *pdwLen)
    {
        return XUIElementPropVal_GetStringLen(this, pdwLen);
    }
    HRESULT ToString(WCHAR **szDest)
    {
        return XUIElementPropVal_ToString(this, szDest);
    }
    HRESULT ToBinary(XUIMemoryBuffer * pDest)
    {
        return XUIElementPropVal_ToBinary(this, pDest);
    }
    BOOL IsEqual(const XUIElementPropVal *pOther)
    {
        return XUIElementPropVal_IsEqual(this, pOther);
    }
#endif
};

#define XUI_BEGIN_PROPERTY_MAP(className)\
    static const XUIElementPropDef *_GetPropDef(DWORD *pdwCount)\
    { \
        int nIndex=0; \
        typedef className _currClass; \
        static XUIElementPropDef _defs[] = \
        {

#define XUI_IMPLEMENT_EMPTY_PROPERTY_MAP(className)\
    static const XUIElementPropDef *_GetPropDef(DWORD *pdwCount)\
    { \
        *pdwCount = 0; \
        return NULL; \
    }


#ifdef _XBOX
//
// These macros map only the values valid at runtime.
//

#define XUI_IMPLEMENT_PROPERTY(propName, propMember, propType, pDefVal)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal },

#define XUI_IMPLEMENT_PROPERTY_EXTRA(propName, propMember, extra, propType, pDefVal)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), extra, propName, propType, pDefVal },

#define XUI_IMPLEMENT_PROPERTY_EDITOR(propName, propMember, propType, pDefVal, szPropEditor)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal },

#define XUI_IMPLEMENT_PROPERTY_EDITOR_GET_SET(propName, propMember, propType, pDefVal, GetFunc, SetFunc, szPropEditor)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, GetFunc, SetFunc },

#define XUI_IMPLEMENT_PROPERTY_EDITOR_GET_SET_FLAGS(flags, propName, propMember, propType, pDefVal, GetFunc, SetFunc, szPropEditor)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, GetFunc, SetFunc },

#define XUI_IMPLEMENT_PROPERTY_FLAGS(flags, propName, propMember, propType, pDefVal)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal },

#define XUI_IMPLEMENT_PROPERTY_EXTRA_FLAGS(flags, propName, propMember, extra, propType, pDefVal)\
    { flags, nIndex++, offsetof(_currClass, propMember), extra, propName, propType, pDefVal },

#define XUI_IMPLEMENT_PROPERTY_EDITOR_FLAGS(flags, propName, propMember, propType, pDefVal, szPropEditor)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal },

#define XUI_IMPLEMENT_INDEXED_PROPERTY(propName, propMember, propType, pDefVal, GetFunc, SetFunc, GetCountFunc)\
    { XUI_ELEMENT_PROPF_INDEXED, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, GetFunc, SetFunc, NULL, GetCountFunc },

#define XUI_IMPLEMENT_COMPOUND_PROPERTY(propName, propMember, propCompoundType, pDefVal)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), 0, propName, XUI_EPT_OBJECT, pDefVal, NULL, NULL, NULL, propCompoundType::_GetPropDef },

#define XUI_IMPLEMENT_COMPOUND_PROPERTY_FLAGS(flags, propName, propMember, propCompoundType, pDefVal)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, XUI_EPT_OBJECT, pDefVal, NULL, NULL, NULL, propCompoundType::_GetPropDef },

#define XUI_IMPLEMENT_PROPERTY_GET_SET(propName, propMember, propType, pDefVal, GetFunc, SetFunc)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, GetFunc, SetFunc },

#define XUI_IMPLEMENT_PROPERTY_GET_SET_EXTRA(propName, propMember, extra, propType, pDefVal, GetFunc, SetFunc)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), extra, propName, propType, pDefVal, NULL, GetFunc, SetFunc },

#define XUI_IMPLEMENT_PROPERTY_GET_SET_FLAGS(flags, propName, propMember, propType, pDefVal, GetFunc, SetFunc)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, GetFunc, SetFunc },

#define XUI_IMPLEMENT_PROPERTY_GET_SET_FLAGS_EXTRA(flags, propName, propMember, extra, propType, pDefVal, GetFunc, SetFunc)\
    { flags, nIndex++, offsetof(_currClass, propMember), extra, propName, propType, pDefVal, NULL, GetFunc, SetFunc },

#define XUI_IMPLEMENT_PROPERTY_CUSTOM(flags, propName, propMember, pDefVal, pHandler)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, XUI_EPT_CUSTOM, pDefVal, pHandler },

#else
//
// These macros map design time values also.
//

#define XUI_IMPLEMENT_PROPERTY(propName, propMember, propType, pDefVal)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal },

#define XUI_IMPLEMENT_PROPERTY_EXTRA(propName, propMember, extra, propType, pDefVal)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), extra, propName, propType, pDefVal },

#define XUI_IMPLEMENT_PROPERTY_EDITOR(propName, propMember, propType, pDefVal, szPropEditor)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, NULL, NULL, NULL, NULL, szPropEditor },

#define XUI_IMPLEMENT_PROPERTY_EDITOR_GET_SET(propName, propMember, propType, pDefVal, GetFunc, SetFunc, szPropEditor)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, GetFunc, SetFunc, NULL, NULL, szPropEditor },

#define XUI_IMPLEMENT_PROPERTY_EDITOR_GET_SET_FLAGS(flags, propName, propMember, propType, pDefVal, GetFunc, SetFunc, szPropEditor)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, GetFunc, SetFunc, NULL, NULL, szPropEditor },

#define XUI_IMPLEMENT_PROPERTY_FLAGS(flags, propName, propMember, propType, pDefVal)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal },

#define XUI_IMPLEMENT_PROPERTY_EXTRA_FLAGS(flags, propName, propMember, extra, propType, pDefVal)\
    { flags, nIndex++, offsetof(_currClass, propMember), extra, propName, propType, pDefVal },

#define XUI_IMPLEMENT_PROPERTY_EDITOR_FLAGS(flags, propName, propMember, propType, pDefVal, szPropEditor)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, NULL, NULL, NULL, NULL, szPropEditor },

#define XUI_IMPLEMENT_INDEXED_PROPERTY(propName, propMember, propType, pDefVal, GetFunc, SetFunc, GetCountFunc)\
    { XUI_ELEMENT_PROPF_INDEXED, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, GetFunc, SetFunc, NULL, GetCountFunc },

#define XUI_IMPLEMENT_COMPOUND_PROPERTY(propName, propMember, propCompoundType, pDefVal)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), 0, propName, XUI_EPT_OBJECT, pDefVal, NULL, NULL, NULL, propCompoundType::_GetPropDef },

#define XUI_IMPLEMENT_COMPOUND_PROPERTY_FLAGS(flags, propName, propMember, propCompoundType, pDefVal)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, XUI_EPT_OBJECT, pDefVal, NULL, NULL, NULL, propCompoundType::_GetPropDef },

#define XUI_IMPLEMENT_PROPERTY_GET_SET(propName, propMember, propType, pDefVal, GetFunc, SetFunc)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, GetFunc, SetFunc },

#define XUI_IMPLEMENT_PROPERTY_GET_SET_EXTRA(propName, propMember, extra, propType, pDefVal, GetFunc, SetFunc)\
    { XUI_ELEMENT_PROPF_NONE, nIndex++, offsetof(_currClass, propMember), extra, propName, propType, pDefVal, NULL, GetFunc, SetFunc },

#define XUI_IMPLEMENT_PROPERTY_GET_SET_FLAGS(flags, propName, propMember, propType, pDefVal, GetFunc, SetFunc)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, propType, pDefVal, NULL, GetFunc, SetFunc },

#define XUI_IMPLEMENT_PROPERTY_GET_SET_FLAGS_EXTRA(flags, propName, propMember, extra, propType, pDefVal, GetFunc, SetFunc)\
    { flags, nIndex++, offsetof(_currClass, propMember), extra, propName, propType, pDefVal, NULL, GetFunc, SetFunc },

#define XUI_IMPLEMENT_PROPERTY_CUSTOM(flags, propName, propMember, pDefVal, pHandler)\
    { flags, nIndex++, offsetof(_currClass, propMember), 0, propName, XUI_EPT_CUSTOM, pDefVal, pHandler },

#endif

#define XUI_END_PROPERTY_MAP() \
        }; \
        *pdwCount = sizeof(_defs)/sizeof(_defs[0]);\
        return _defs;\
        }

typedef HRESULT (APIENTRY *PFN_OBJECT_PROC)(HXUIOBJ hObj, XUIMessage *pMessage, void *pvThis);
typedef HRESULT (APIENTRY *PFN_CREATEINST)(HXUIOBJ hObj, void **ppvObj);
typedef HRESULT (APIENTRY *PFN_DESTROYINST)(void *pvObj);
typedef HRESULT (APIENTRY *PFN_MESSAGE_FILTER)(HXUIOBJ hObj, XUIMessage *pMessage);

struct XUIObjectMethods
{
    PFN_OBJECT_PROC ObjectProc;
    PFN_CREATEINST CreateInstance;
    PFN_DESTROYINST DestroyInstance;
};

struct XUIClass
{
    DWORD cbSize;
    LPCWSTR szClassName;
    LPCWSTR szBaseClassName;
    LPCWSTR szClassDetails;
    XUIObjectMethods Methods;
    const XUIElementPropDef *pPropDefs;
    DWORD dwPropDefCount;
    BOOL bExtensionClass;
};

// Runtime hook functions should return E_NOTIMPL if they choose not to provide any behavior.
struct IXUIRuntimeHooksVTBL
{
    HRESULT (STDMETHODCALLTYPE *RewriteResourceLocator)(IXUIRuntimeHooks* pThis, LPCWSTR szLocator, LPWSTR * pszNewLocator);
    HRESULT (STDMETHODCALLTYPE *FindClassByName)(IXUIRuntimeHooks* pThis, LPCWSTR szClassName, HXUICLASS *phClass);
    HRESULT (STDMETHODCALLTYPE *GetTextPresenterText)(IXUIRuntimeHooks* pThis, HXUIOBJ hObj, LPCWSTR * pszText);
    HRESULT (STDMETHODCALLTYPE *LogMessage)(IXUIRuntimeHooks* pThis, HRESULT hr, LPCWSTR pszText);
#ifndef _XBOX
    HRESULT (STDMETHODCALLTYPE *OnSetCapture)(IXUIRuntimeHooks* pThis, HXUIOBJ hObj);
    HRESULT (STDMETHODCALLTYPE *OnReleaseCapture)(IXUIRuntimeHooks* pThis, HXUIOBJ hObj);
#endif
};

struct IXUIRuntimeHooks
{
#ifdef __cplusplus
    
    virtual HRESULT STDMETHODCALLTYPE RewriteResourceLocator(LPCWSTR szLocator, LPWSTR * pszNewLocator) = 0;
    virtual HRESULT STDMETHODCALLTYPE FindClassByName(LPCWSTR szClassName, HXUICLASS *phClass) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetTextPresenterText(HXUIOBJ hObj, LPCWSTR * pszText) = 0;
    virtual HRESULT STDMETHODCALLTYPE LogMessage(HRESULT hr, LPCWSTR pszText) = 0;
#ifndef _XBOX
    virtual HRESULT STDMETHODCALLTYPE OnSetCapture(HXUIOBJ hObj) = 0;
    virtual HRESULT STDMETHODCALLTYPE OnReleaseCapture(HXUIOBJ hObj) = 0;
#endif

#else

    struct IXUIRuntimeHooksVTBL * pVtbl;

#endif
};

// XUI Init Parameters

#define XUI_INIT_PARAMS_FLAGS_NONE          0x00000000
#define XUI_INIT_PARAMS_FLAGS_NOKEYBOARD    0x00000001  // don't use keyboard for controls

#ifndef _XBOX
// Windows specific initialization flags
#define XUI_INIT_PARAMS_FLAGS_FOCUSONHOVER  0x00000002  // set focus to controls on hover

#endif

#define XUI_INIT_PARAMS(InitParams) \
        memset(&(InitParams), 0, sizeof(XUIInitParams)); \
        (InitParams).cbSize = sizeof(XUIInitParams);        

struct XUIInitParams
{
    DWORD cbSize;
    DWORD dwFlags;
    IXUIRuntimeHooks * pHooks;
};

// class enumeration
#ifndef _XBOX
typedef void (CALLBACK *XuiClassEnumerateFn)(HXUICLASS hClass, void* pUserData);
HRESULT APIENTRY XuiClassEnumerate(XuiClassEnumerateFn pFn, void* pUserData);
#endif

// public APIs
HRESULT APIENTRY XuiInit(const XUIInitParams *pInitParams);
HRESULT APIENTRY XuiUninit(void);
IXUIRuntimeHooks* APIENTRY XuiGetRuntimeHooks(void);
HRESULT APIENTRY XuiSetRuntimeHooks(IXUIRuntimeHooks* pHooks);
USHORT APIENTRY XuiGetVersion(void);
HRESULT APIENTRY XuiLoadFromBinary(LPCWSTR szFileName, HXUIOBJ * phRootObj, BOOL bInitNow);
HXUICLASS APIENTRY XuiFindClass(LPCWSTR szClassName);
BOOL APIENTRY XuiClassDerivesFrom(HXUICLASS hClass, HXUICLASS hClassBase);
HRESULT APIENTRY XuiRegisterClass(const XUIClass *pClass, HXUICLASS *phClass);
HRESULT APIENTRY XuiUnregisterClass(LPCWSTR szClassName);
HRESULT APIENTRY XuiGetClass(HXUICLASS hClass, XUIClass *pClass);
HRESULT APIENTRY XuiGetBaseClass(HXUICLASS hClass, HXUICLASS * phBaseClass);
HRESULT APIENTRY XuiClassGetPropDef(HXUICLASS hClass, const XUIElementPropDef **ppDef, DWORD *pdwCount);
HRESULT APIENTRY XuiClassGetPropertyDefById(HXUICLASS hClass, DWORD dwPropId, const XUIElementPropDef **ppDef);
HRESULT APIENTRY XuiClassGetPropertyDef(HXUICLASS hClass, LPCWSTR szPropName, const XUIElementPropDef **ppDef);
HRESULT APIENTRY XuiObjectFromHandle(HXUIOBJ hObj, void **ppObj);
HRESULT APIENTRY XuiGetBaseObject(HXUIOBJ hObj, HXUIOBJ *phBaseObj);
HXUICLASS APIENTRY XuiGetObjectClass(HXUIOBJ hObj);
HRESULT APIENTRY XuiCreateObject(LPCWSTR szClassName, HXUIOBJ *phObj);
HRESULT APIENTRY XuiDestroyObject(HXUIOBJ hObj);
BOOL APIENTRY XuiHandleIsValid(HXUIOBJ hObj);
BOOL APIENTRY XuiIsInstanceOf(HXUIOBJ hObj, HXUICLASS hClass);
HXUIOBJ APIENTRY XuiDynamicCast(HXUIOBJ hObj, HXUICLASS hClass);
HRESULT APIENTRY XuiSendMessage(HXUIOBJ hObj, XUIMessage *pMessage);
HRESULT APIENTRY XuiBubbleMessage(HXUIOBJ hObj, XUIMessage *pMessage);
HRESULT APIENTRY XuiBroadcastMessage(HXUIOBJ hObj, XUIMessage *pMessage);
HXUIOBJ APIENTRY XuiGetOuter(HXUIOBJ hObj);
PFN_MESSAGE_FILTER APIENTRY XuiSetMessageFilter(PFN_MESSAGE_FILTER pfnFilter);
HRESULT APIENTRY XuiSetTimer(HXUIOBJ hObj, DWORD nId, DWORD nElapse);
HRESULT APIENTRY XuiKillTimer(HXUIOBJ hObj, DWORD nId);
HRESULT APIENTRY XuiTimersRun(void);

HRESULT APIENTRY XuiElementPropValFromString(LPCWSTR szText, XUI_ELEMENT_PROPERTY_TYPE type, XUIElementPropVal *pVal);
HRESULT APIENTRY XuiElementPropValFromBinary(const BYTE * pb, UINT * pcb, XUI_ELEMENT_PROPERTY_TYPE type, XUIElementPropVal *pVal);

const XUIElementPropDef* APIENTRY XuiObjectGetPropDef(HXUIOBJ hObj, DWORD *pdwCount);
HRESULT APIENTRY XuiObjectGetPropertyId(HXUIOBJ hObj, LPCWSTR szPropName, DWORD *pdwId);
HRESULT APIENTRY XuiObjectGetPropertyDefById(HXUIOBJ hObj, DWORD dwPropId, const XUIElementPropDef **ppDef);
HRESULT APIENTRY XuiObjectGetPropertyDef(HXUIOBJ hObj, LPCWSTR szPropName, const XUIElementPropDef **ppDef);
HRESULT APIENTRY XuiObjectGetProperty(HXUIOBJ hObj, DWORD dwPropId, DWORD dwIndex, XUIElementPropVal *pVal);
HRESULT APIENTRY XuiObjectSetProperty(HXUIOBJ hObj, DWORD dwPropId, DWORD dwIndex, const XUIElementPropVal *pVal);
HRESULT APIENTRY XuiObjectGetPropertyRef(HXUIOBJ hObj, DWORD dwPropId, void **ppvData);
HRESULT APIENTRY XuiObjectGetPropertyCount(HXUIOBJ hObj, DWORD dwPropId, DWORD *pdwCount);

HRESULT APIENTRY XuiLoadStringTableFromFile(LPCWSTR szFile, HXUISTRINGTABLE *ph);
HRESULT APIENTRY XuiLoadStringTableFromMemory(LPCVOID pData, HXUISTRINGTABLE *ph);
HRESULT APIENTRY XuiFreeStringTable(HXUISTRINGTABLE h);
LPCWSTR APIENTRY XuiLookupStringTable(HXUISTRINGTABLE h, LPCWSTR szKey);
LPCWSTR APIENTRY XuiLookupStringTableByIndex(HXUISTRINGTABLE h, DWORD nIndex);

HRESULT APIENTRY XuiMuteSound(BOOL bMute);

#define XUI_LOCALE_NO_VISUALS_RELOAD        0x00000001

HRESULT APIENTRY XuiSetLocaleEx(LPCWSTR szLocale, DWORD dwFlags);
HRESULT APIENTRY XuiSetLocale(LPCWSTR szLocale);
LPCWSTR APIENTRY XuiGetLocale(void);
HRESULT APIENTRY XuiApplyLocale(HXUIOBJ hObj, HXUISTRINGTABLE hStringTable);

HRESULT APIENTRY XuiCopyString(LPWSTR *ppszOut, LPCWSTR szIn);

#ifdef __cplusplus
}
#endif

#pragma warning(pop)

#endif // __XUIBASE_H__

