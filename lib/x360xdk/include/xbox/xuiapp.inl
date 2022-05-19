
/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       xuiapp.inl
 *  Content:    Xbox 360 UI runtime C++ helpers
 *
 ****************************************************************************/

#ifdef _XBOX
#include <PPCIntrinsics.h>
#endif

#define XUI_INLINE inline

////////////////////////////////////////////////////////////////////////////////
// CXuiAnimRunner
////////////////////////////////////////////////////////////////////////////////
XUI_INLINE CXuiAnimRunner::CXuiAnimRunner()
{
    Reset();
}

XUI_INLINE void CXuiAnimRunner::Reset()
{
    QueryPerformanceFrequency(&m_liTicksPerSecond);
    QueryPerformanceCounter(&m_liLastFrameTime);
}

XUI_INLINE void CXuiAnimRunner::Resume()
{
    QueryPerformanceCounter(&m_liLastFrameTime);
}

// This function has been deprecated.  Calling Run() with no parameters
// will run animations using the delta time from the last frame
// If you have your own timer, then you can call XuiAnimRun with the delta time
// between frames
XUI_INLINE void __declspec(deprecated) CXuiAnimRunner::Run(DWORD /*dwTime*/)
{
    Run();
}

XUI_INLINE void CXuiAnimRunner::Run()
{
    XuiAnimRun(GetDeltaTime());
}

XUI_INLINE float CXuiAnimRunner::GetDeltaTime()
{
    LARGE_INTEGER liCurrFrameTime;
    QueryPerformanceCounter(&liCurrFrameTime);
    unsigned __int64 nDeltaTime = ((unsigned __int64) liCurrFrameTime.QuadPart) - ((unsigned __int64) m_liLastFrameTime.QuadPart);

    float fDeltaTime = (float) ((((double) nDeltaTime) / ((double) m_liTicksPerSecond.QuadPart))*1000.0);
    m_liLastFrameTime = liCurrFrameTime;
    return fDeltaTime;

}

XUI_INLINE void CXuiAnimRunner::GetLastFrameTime(LARGE_INTEGER *pliLastFrameTime)
{
    *pliLastFrameTime = m_liLastFrameTime;
}


////////////////////////////////////////////////////////////////////////////////
// CXuiModule
////////////////////////////////////////////////////////////////////////////////
XUI_INLINE CXuiModule::CXuiModule()
{
    m_hObjRoot = NULL;
    m_hDC = NULL;
    m_bXuiInited = FALSE;
    m_bInitRuntime = TRUE;
    m_bQuit = FALSE;
    m_bSkinLoaded = FALSE;
    m_bDefaultTypefaceRegistered = FALSE;
    m_bUsingEffects = FALSE;
}

XUI_INLINE CXuiModule::~CXuiModule()
{
    // make sure we haven't been constructed yet
    // or Uninit was called
    // it's OK if the DC is not reset when m_bInitRuntime is FALSE, it means
    // that this DC is shared among many CXuiModule
    ASSERT((m_bXuiInited == FALSE) && (m_hObjRoot == NULL) && ((m_hDC == NULL) || (m_bInitRuntime == FALSE)));
}


XUI_INLINE HRESULT CXuiModule::Init()
{
    // This version of Init is deprecated.
    // In order to reduce dependence on D3DX, XUI clients should implement their own
    // texture loader function and register it with the new version of this member function.
    return Init(XuiD3DXTextureLoader);
}

XUI_INLINE HRESULT CXuiModule::Init(PFN_XUITEXTURELOADER pfnTextureLoader, XUIInitParams *pInitParams/*=NULL*/)
{
    HRESULT hr;
    if (m_bInitRuntime)
    {
        hr = XuiRenderInit(NULL, pfnTextureLoader);
        if (FAILED(hr))
            return hr;
    }

    hr = InitCommon(pInitParams);
    if (FAILED(hr) && m_bInitRuntime)
        XuiRenderUninit();
    return hr;
}

#ifndef _XBOX
XUI_INLINE HRESULT CXuiModule::Init(PFN_XUITEXTURELOADER pfnTextureLoader, HWND hWnd, XUIInitParams *pInitParams/*=NULL*/)
{
    HRESULT hr;
    if (m_bInitRuntime)
    {
        hr = XuiRenderInit(hWnd, pfnTextureLoader);
        if (FAILED(hr))
            return hr;
    }

    hr = InitCommon(pInitParams);
    if (FAILED(hr) && m_bInitRuntime)
        XuiRenderUninit();
    return hr;
}
#endif

XUI_INLINE HRESULT CXuiModule::InitShared(IDirect3DDevice9 *pDevice, const D3DPRESENT_PARAMETERS *pPresentParams)
{
    // This version of InitShared is deprecated.
    // In order to reduce dependence on D3DX, XUI clients should implement their own
    // texture loader function and register it with the new version of this member function.
    return InitShared(pDevice, pPresentParams, XuiD3DXTextureLoader);
}

XUI_INLINE HRESULT CXuiModule::InitShared(IDirect3DDevice9 *pDevice, const D3DPRESENT_PARAMETERS *pPresentParams, PFN_XUITEXTURELOADER pfnTextureLoader, XUIInitParams *pInitParams/*=NULL*/)
{
    HRESULT hr = XuiRenderInitShared(pDevice, pPresentParams, pfnTextureLoader);
    if (FAILED(hr))
        return hr;
    hr = InitCommon(pInitParams);
    if (FAILED(hr))
        XuiRenderUninit();
    return hr;
}

XUI_INLINE HRESULT CXuiModule::InitEx(XUIRenderInitParams *pRenderInitParams, XUIInitParams *pInitParams/*=NULL*/)
{
    HRESULT hr = XuiRenderInitEx(pRenderInitParams);
    if (FAILED(hr))
        return hr;
    if (pRenderInitParams->pfnShaderCompiler != NULL)
        m_bUsingEffects = TRUE;
    hr = InitCommon(pInitParams);
    if (FAILED(hr))
        XuiRenderUninit();
    return hr;
}

XUI_INLINE HRESULT CXuiModule::InitCommon(XUIInitParams *pInitParams/*=NULL*/)
{
    HRESULT hr;

    if (m_bInitRuntime)
    {
        if (m_hDC == NULL)
        {
            hr = XuiRenderCreateDC(&m_hDC);
            if (FAILED(hr))
                return hr;
        }

        XUIInitParams initparams;
        
        if (pInitParams == NULL)
        {
            XUI_INIT_PARAMS(initparams);
            pInitParams = &initparams;
        }
        
        hr = XuiInit(pInitParams);
        if (FAILED(hr))
        {
            XuiRenderDestroyDC(m_hDC);
            m_hDC = NULL;
            return hr;
        }
    }
    m_bXuiInited = TRUE;

#ifdef XUIAPP_AUDITIONING
    XuiAuditioningInit(this);
#endif

    hr = RegisterXuiClasses();
    if (FAILED(hr))
    {
        Uninit();
        return hr;
    }

    // create the main canvas
    hr = CreateMainCanvas();
    if (FAILED(hr))
    {
        Uninit();
        return hr;
    }
    return S_OK;
}

XUI_INLINE void CXuiModule::Uninit()
{
    if (m_hObjRoot)
    {
        XuiDestroyObject(m_hObjRoot);
        m_hObjRoot = NULL;
    }

    UnregisterXuiClasses();

#ifdef XUIAPP_AUDITIONING
    XuiAuditioningUninit();
#endif

    if (m_bInitRuntime)
    {
        if (m_hDC)
        {
            XuiRenderDestroyDC(m_hDC);
            m_hDC = NULL;
        }

        if (m_bXuiInited)
        {
            XuiUninit();
        }

        XuiRenderUninit();
    }
    m_bXuiInited = FALSE;
}

XUI_INLINE int CXuiModule::Run()
{
    while (!m_bQuit)
    {
        RunFrame();
        if (m_bUsingEffects)
        {
            PreRender();
        }
        Render();
        XuiTimersRun();
    }
    return 0;
}

XUI_INLINE void CXuiModule::Resume()
{
    m_animRunner.Resume();
}

XUI_INLINE void CXuiModule::Quit()
{
    m_bQuit = TRUE;
}

XUI_INLINE HXUIDC CXuiModule::GetDC()
{
    return m_hDC;
}

XUI_INLINE HXUIOBJ CXuiModule::GetRootObj()
{
    return m_hObjRoot;
}

//
// RunFrame:
// This function runs animations based on the internal timer
// to use your own timer, call RunFrame(float fDeltaTime)
//
XUI_INLINE void CXuiModule::RunFrame()
{
    RunFrame(m_animRunner.GetDeltaTime());
}

XUI_INLINE void CXuiModule::RunFrame(float fDeltaTime)
{
#ifdef XUIAPP_AUDITIONING
    // Do async auditioning work
    XuiAuditioningProcess();
#endif

    //
    // Check controller input
    //
    ProcessInput();

    // Run animations
    XuiAnimRun(fDeltaTime);
}


XUI_INLINE HRESULT CXuiModule::ProcessInput()
{
#ifdef _XBOX
    XINPUT_KEYSTROKE keyStroke;
    if (ERROR_SUCCESS == XInputGetKeystroke(XUSER_INDEX_ANY, XINPUT_FLAG_ANYDEVICE,
        &keyStroke))
    {
        XuiProcessInput(&keyStroke);
    }
#endif
    return S_OK;
}

XUI_INLINE HRESULT CXuiModule::PreRender()
{
    ASSERT(m_hDC != NULL);
    HRESULT hr = XuiPreRenderBegin(m_hDC, D3DCOLOR_ARGB(255, 0, 0, 0));
    if (FAILED(hr))
        return hr;

    XUIMessage msg;
    XUIMessageRender msgRender;
    XuiMessagePreRender(&msg, &msgRender, m_hDC, 0xffffffff, XUI_BLEND_NORMAL);
    XuiSendMessage(m_hObjRoot, &msg);

    XuiPreRenderEnd(m_hDC);
    return S_OK;
}
XUI_INLINE HRESULT CXuiModule::Render()
{
    ASSERT(m_hDC != NULL);
    HRESULT hr = XuiRenderBegin(m_hDC, D3DCOLOR_ARGB(255, 0, 0, 0));
    if (FAILED(hr))
        return hr;

    XUIMessage msg;
    XUIMessageRender msgRender;
    XuiMessageRender(&msg, &msgRender, m_hDC, 0xffffffff, XUI_BLEND_NORMAL);
    XuiSendMessage(m_hObjRoot, &msg);

    XuiRenderEnd(m_hDC);
    XuiRenderPresent(m_hDC, NULL, NULL, NULL);
    return S_OK;
}

XUI_INLINE HRESULT CXuiModule::RegisterDefaultTypeface(LPCWSTR szTypeface, LPCWSTR szLocator, LPCWSTR szReserved1/*=NULL*/, float fBaselineAdjust/*=0.0f*/, LPCWSTR szFallbackTypeface/*=NULL*/)
{
    TypefaceDescriptor typeface = {szTypeface, szLocator, szReserved1, fBaselineAdjust, szFallbackTypeface};
    HRESULT hr = XuiRegisterTypeface(&typeface, TRUE);
    if (FAILED(hr))
        return hr;
    m_bDefaultTypefaceRegistered = TRUE;
    return S_OK;
}

XUI_INLINE HRESULT CXuiModule::RegisterTypeface(LPCWSTR szTypeface, LPCWSTR szLocator, LPCWSTR szReserved1/*=NULL*/, float fBaselineAdjust/*=0.0f*/, LPCWSTR szFallbackTypeface/*=NULL*/)
{
    TypefaceDescriptor typeface = {szTypeface, szLocator, szReserved1, fBaselineAdjust, szFallbackTypeface};
    return XuiRegisterTypeface(&typeface, FALSE);
}

XUI_INLINE HRESULT CXuiModule::LoadSkin(LPCWSTR szSkinFileName, LPCWSTR szVisualPrefix/*=NULL*/)
{
    HRESULT hr = XuiLoadVisualFromBinary(szSkinFileName, szVisualPrefix);
    if (FAILED(hr))
        return hr;
    m_bSkinLoaded = TRUE;
    return S_OK;
}

XUI_INLINE HRESULT CXuiModule::LoadFirstScene(LPCWSTR szBasePath, LPCWSTR szScenePath, void* pvInitData, HXUIOBJ *phObj /*=NULL*/, BYTE Port /*= XUSER_INDEX_FOCUS*/)
{
    if (phObj)
        *phObj = NULL;

    ASSERT(m_bDefaultTypefaceRegistered);
    ASSERT(m_bSkinLoaded);

    // make sure we've created the main canvas already
    ASSERT(m_hObjRoot);
    if (!m_hObjRoot)
        return E_UNEXPECTED;

    HXUIOBJ hScene;
    HRESULT hr = XuiSceneCreate(szBasePath, szScenePath, pvInitData, &hScene);
    if (FAILED(hr))
        return hr;

    hr = XuiSceneNavigateFirst(m_hObjRoot, hScene, Port);
    if (FAILED(hr))
    {
        XuiDestroyObject(hScene);
        return hr;
    }

    if (phObj)
        *phObj = hScene;

    return S_OK;
}

XUI_INLINE HRESULT CXuiModule::CreateMainCanvas()
{
    ASSERT(m_bXuiInited);
    if (!m_bXuiInited)
        return E_UNEXPECTED;

    ASSERT(m_hObjRoot == NULL);
    if (m_hObjRoot)
        return E_UNEXPECTED;


    UINT uWidth, uHeight;
    HRESULT hr = XuiRenderGetBackBufferSize(m_hDC, &uWidth, &uHeight);
    if (FAILED(hr))
        return hr;

    hr = XuiCreateObject(XUI_CLASS_CANVAS, &m_hObjRoot);
    if (FAILED(hr))
        return hr;

    hr = XuiElementSetBounds(m_hObjRoot, (float) uWidth, (float) uHeight);
    if (FAILED(hr))
        return hr;
    return S_OK;
}

#ifdef XUIAPP_AUDITIONING
////////////////////////////////////////////////////////////////////////////////
// IXuiAuditionHost implementation
////////////////////////////////////////////////////////////////////////////////
XUI_INLINE HRESULT CXuiModule::ProcessRemoteInput(const XINPUT_KEYSTROKE * pKeystroke)
{
    return E_NOTIMPL;
}

XUI_INLINE HRESULT CXuiModule::ChangeLocale()
{
    return E_NOTIMPL;
}

XUI_INLINE HRESULT CXuiModule::ChangeSkin(LPCWSTR szSkinResource, LPCWSTR szPrefix /* = NULL */)
{
    XuiFreeVisuals(szPrefix);

    HRESULT hr = XuiLoadVisualFromBinary(szSkinResource, szPrefix);
    if (FAILED(hr))
        return hr;

    XuiElementSkinChanged(m_hObjRoot);

    m_bSkinLoaded = TRUE;
    return S_OK;
}

XUI_INLINE HRESULT CXuiModule::ReloadResources()
{
    XuiElementDiscardResources(m_hObjRoot, XUI_DISCARD_ALL);
    return S_OK;
}

#endif // XUIAPP_AUDITIONING

#ifndef _XBOX
XUI_INLINE HRESULT CXuiModule::OnCreateDevice(IDirect3DDevice9 *pd3dDevice, const D3DPRESENT_PARAMETERS *pPresentParams, PFN_XUITEXTURELOADER pfnTextureLoader)
{
    if (m_hDC)
        return S_OK;

    HRESULT hr = XuiRenderInitShared(pd3dDevice, pPresentParams, pfnTextureLoader);
    if (FAILED(hr))
        return hr;

    hr = XuiRenderCreateDC(&m_hDC);
    if (FAILED(hr))
    {
        XuiRenderUninit();
        return hr;
    }

    return S_OK;
}

XUI_INLINE HRESULT CXuiModule::OnResetDevice()
{
    return S_OK;
}

XUI_INLINE void CXuiModule::OnLostDevice()
{

}

XUI_INLINE void CXuiModule::OnDestroyDevice()
{
    if (m_hObjRoot != NULL)
        XuiElementDiscardResources(m_hObjRoot, XUI_DISCARD_ALL);

    if (m_hDC)
    {
        XuiRenderDestroyDC(m_hDC);
        m_hDC = NULL;
    }
    XuiRenderUninit();
}

#endif

////////////////////////////////////////////////////////////////////////////////
// CXuiSceneCache implementation
////////////////////////////////////////////////////////////////////////////////
XUI_INLINE CXuiSceneCache::CXuiSceneCache()
{
    m_hClassControl = NULL;
    m_hClassNavButton = NULL;
    m_hClassScene = NULL;
    m_pHead = NULL;
    m_pTail = NULL;
}

XUI_INLINE HRESULT CXuiSceneCache::Init()
{
    m_hClassControl = XuiFindClass(XUI_CLASS_CONTROL);
    m_hClassNavButton = XuiFindClass(XUI_CLASS_NAVBUTTON);
    m_hClassScene = XuiFindClass(XUI_CLASS_SCENE);
    InitializeCriticalSection(&m_CS);
    return S_OK;
}
    
XUI_INLINE void CXuiSceneCache::Uninit()
{
    RemoveAll();
    m_hClassControl = NULL;
    m_hClassNavButton = NULL;
    m_hClassScene = NULL;
    DeleteCriticalSection(&m_CS);
}
    
XUI_INLINE void CXuiSceneCache::RemoveAll()
{
    EnterCriticalSection(&m_CS);
    SceneCacheEntry *pEntry = m_pHead;
    while (pEntry)
    {
        SceneCacheEntry *pNext = pEntry->m_pNext;
        delete pEntry;
        pEntry = pNext;
    }
    m_pHead = m_pTail = NULL;
    LeaveCriticalSection(&m_CS);
}
    
XUI_INLINE HRESULT CXuiSceneCache::CacheScene(LPCWSTR szFullPath, int nCacheLevels/*=0*/, HXUIOBJ *phScene/*=NULL*/)
{
    if (phScene != NULL)
        *phScene = NULL;

    HXUIOBJ hScene;
    HRESULT hr = S_OK;
    
    // see if the scene is already in the cache
    hScene = FindSceneObjInCache(szFullPath);
    if (hScene == NULL)
    {    
        // allocate a new entry
        SceneCacheEntry *pEntry = new SceneCacheEntry();
        if (!pEntry)
            return E_OUTOFMEMORY;

        hr = XuiSceneCreateEx(NULL, szFullPath, NULL, &hScene, 
                              XUI_SCENE_CREATE_FLAGS_SUSPENDED|XUI_SCENE_CREATE_FLAGS_INIT_RESOURCES);
        if (FAILED(hr))
        {
            delete pEntry;
            return hr;
        }

        hr = pEntry->SetFileName(szFullPath);
        if (FAILED(hr))
        {
            delete pEntry;
            XuiDestroyObject(hScene);
            return hr;
        }
        
        pEntry->m_hObj = hScene;
        
        // now link it to the list
        EnterCriticalSection(&m_CS);
        if (!m_pTail)
        {
            m_pHead = m_pTail = pEntry;
        }
        else
        {
            pEntry->m_pPrev = m_pTail;
            m_pTail->m_pNext = pEntry;
            m_pTail = pEntry;
        }
        LeaveCriticalSection(&m_CS);
    }
    
    if (phScene)
        *phScene = GetSceneFromCache(szFullPath);
        
    if (nCacheLevels > 0)
        hr = CacheNavButtonTargets(hScene, nCacheLevels-1);
    
    return hr;
}


struct XUICacheSceneAsyncThreadData
{
    CXuiSceneCache     *pThis;
    XUICacheSceneAsync *pScenes;
    DWORD               dwCount;
#ifdef _XBOX
    XOVERLAPPED        *pOverlapped;
#else
    OVERLAPPED         *pOverlapped;
#endif
};

XUI_INLINE /*static*/ DWORD _stdcall CXuiSceneCache::CacheSceneAsyncThreadProc(void *pThreadParam)
{
    XUICacheSceneAsyncThreadData *pThreadData = (XUICacheSceneAsyncThreadData*)pThreadParam;
    
    HRESULT hr = S_OK;
    DWORD i;
    for (i=0; i<pThreadData->dwCount; ++i)
    {
        hr = pThreadData->pThis->CacheScene(pThreadData->pScenes[i].pszFullPath, pThreadData->pScenes[i].nCacheLevels);
        if (FAILED(hr))
        {
            break;
        }
    }
    
    if (pThreadData->pOverlapped && pThreadData->pOverlapped->hEvent)
    {
        // Make sure overlapped result is available before InternalLow changes
        // from ERROR_IO_PENDING. InternalHigh contains the count of requested
        // scenes cached (not including automatic nav-path scenes).
        pThreadData->pOverlapped->InternalHigh = i;
#ifdef _XBOX
        pThreadData->pOverlapped->dwExtendedError = 0;
        MemoryBarrier();
#endif
        
        // Complete the overlapped object
#ifdef _XBOX
        pThreadData->pOverlapped->InternalLow = hr;
#else
        pThreadData->pOverlapped->Internal = hr;
#endif        
        SetEvent(pThreadData->pOverlapped->hEvent);
    }
    
    XuiFree((void*)pThreadData);
    return 0;
}

#ifdef _XBOX
XUI_INLINE HRESULT CXuiSceneCache::CacheSceneAsync(XUICacheSceneAsync pScenes[], DWORD dwCount, 
                                                   XOVERLAPPED *pOverlapped/*=NULL*/, DWORD dwHardwareThread/*=0xFFFFFFFF*/)
#else
XUI_INLINE HRESULT CXuiSceneCache::CacheSceneAsync(XUICacheSceneAsync pScenes[], DWORD dwCount, 
                                                   OVERLAPPED *pOverlapped/*=NULL*/, DWORD dwHardwareThread/*=0xFFFFFFFF*/)
#endif
{
    if (pScenes == NULL || dwCount == 0)
        return E_INVALIDARG;

    if (pOverlapped)
    {
        if (!pOverlapped->hEvent)
            return E_INVALIDARG;
        ResetEvent(pOverlapped->hEvent);
#ifdef _XBOX
        pOverlapped->InternalLow = ERROR_IO_PENDING;
#else
        pOverlapped->Internal = ERROR_IO_PENDING;
#endif
    }
        
    XUICacheSceneAsyncThreadData *pThreadData = (XUICacheSceneAsyncThreadData*)XuiAlloc(sizeof(XUICacheSceneAsync));
    if (!pThreadData)
        return E_OUTOFMEMORY;
        
    pThreadData->pThis = this;
    pThreadData->pScenes = pScenes;
    pThreadData->dwCount = dwCount;
    pThreadData->pOverlapped = pOverlapped;
    
    HANDLE hThread = CreateThread(NULL, 0, CacheSceneAsyncThreadProc, (void*)pThreadData, CREATE_SUSPENDED, NULL);
    if (hThread == NULL)
    {
        XuiFree((void*)pThreadData);
        return E_FAIL;
    }
    
    if (dwHardwareThread != 0xFFFFFFFF)
    {
        #ifdef _XBOX
            XSetThreadProcessor(hThread, dwHardwareThread);
        #else
            SetThreadIdealProcessor(hThread, dwHardwareThread);
        #endif
    }
    
    ResumeThread(hThread);
    
    CloseHandle(hThread);
    
    return S_OK;
}

XUI_INLINE HRESULT CXuiSceneCache::CacheNavButtonTargets(HXUIOBJ hObj, int nCacheLevels)
{    
    LPCWSTR szBasePath = XuiElementGetBasePath(hObj);
    // loop through the children of the scene
    HXUIOBJ hChild;
    XuiElementGetFirstChild(hObj, &hChild);
    while (hChild)
    {
        HXUIOBJ hNavButton = XuiDynamicCast(hChild, m_hClassNavButton);
        if (hNavButton != NULL)
        {
            LPCWSTR szPath = XuiNavButtonGetPressPath(hNavButton);
            WCHAR *szFullPath = NULL;
            HRESULT hr = XuiResourceComposeLocator(&szFullPath, szBasePath, szPath);
            if (FAILED(hr))
                return hr;

            hr = CacheScene(szFullPath, nCacheLevels, NULL);
            if (FAILED(hr))
                return hr;
            XuiFree(szFullPath);
        }
        else
        {
            HXUIOBJ hChildScene = XuiDynamicCast(hChild, m_hClassScene);
            if (hChildScene)
            {
                HRESULT hr = CacheNavButtonTargets(hChild, nCacheLevels);
                if (FAILED(hr))
                    return hr;
            }
        }
        XuiElementGetNext(hChild, &hChild);
    }
    return S_OK;
}
    
XUI_INLINE HXUIOBJ CXuiSceneCache::GetSceneFromCache(LPCWSTR szFullPath)
{    
    EnterCriticalSection(&m_CS);
    SceneCacheEntry *pEntry = m_pHead;
    while (pEntry != NULL)
    {
        if (!_wcsicmp(szFullPath, pEntry->m_szFileName))
        {
            if (!pEntry->m_bInUse)
            {
                pEntry->m_bInUse = TRUE;                
                HXUIOBJ hObj = pEntry->m_hObj;
                LeaveCriticalSection(&m_CS);
                XuiElementSuspend(hObj, FALSE);                
                return hObj;
            }
        }
        pEntry = pEntry->m_pNext;
    }
    LeaveCriticalSection(&m_CS);
    
    return NULL;
}
    
XUI_INLINE BOOL CXuiSceneCache::ReleaseScene(HXUIOBJ hObj)
{
    EnterCriticalSection(&m_CS);
    SceneCacheEntry *pEntry = m_pHead;
    while (pEntry != NULL)
    {
        if (pEntry->m_hObj == hObj)
        {
            ASSERT(pEntry->m_bInUse == TRUE);
            pEntry->m_bInUse = FALSE;
            HXUIOBJ hObj = pEntry->m_hObj;
            LeaveCriticalSection(&m_CS);
            XuiElementSuspend(hObj, TRUE);
            return TRUE;
        }
        pEntry = pEntry->m_pNext;
    }
    LeaveCriticalSection(&m_CS);
    
    return FALSE;
}

XUI_INLINE BOOL CXuiSceneCache::RemoveScene(HXUIOBJ hScene)
{
    EnterCriticalSection(&m_CS);
    
    // find the scene in the cache
    SceneCacheEntry *pEntry = m_pHead;
    while (pEntry != NULL)
    {
        if (pEntry->m_hObj == hScene)
        {
            break;        
        }
        pEntry = pEntry->m_pNext;
    }
    
    if (!pEntry)
    {
        LeaveCriticalSection(&m_CS);
        return FALSE;
    }

    // unlink from the list
    if (pEntry->m_pPrev)
    {
        pEntry->m_pPrev->m_pNext = pEntry->m_pNext;
    }
    else
    {
        // we're unlinking the head
        m_pHead = pEntry->m_pNext;
    }
    
    if (pEntry->m_pNext)
    {
        pEntry->m_pNext->m_pPrev = pEntry->m_pPrev;
    }
    else
    {
        // we're unlinking the tail
        m_pTail = pEntry->m_pPrev;
    }
    LeaveCriticalSection(&m_CS);
    
    // now detach the scene from the Entry
    pEntry->DetachObject();
    
    // finally free the memory
    delete pEntry;
    return TRUE;
}
    
XUI_INLINE BOOL CXuiSceneCache::HandleNavigation(HXUIOBJ hObjSource, XUINotify * /*pNotify*/)
{
    HXUIOBJ hCurrScene;
    XuiElementGetParent(hObjSource, &hCurrScene);
    if (!hCurrScene)
        return FALSE;

    LPCWSTR szBasePath = XuiElementGetBasePath(hCurrScene);
    LPCWSTR szPath = XuiNavButtonGetPressPath(hObjSource);
    
    WCHAR *szFullPath = NULL;
    
    HRESULT hr = XuiResourceComposeLocator(&szFullPath, szBasePath, szPath);
    if (FAILED(hr))
        return FALSE;
    
    HXUIOBJ hCachedScene = GetSceneFromCache(szFullPath);
    if (!hCachedScene)
    {
        XuiFree(szFullPath);
        return FALSE;
    }
    
    XuiFree(szFullPath);

    // get the transition index overrides from the nav button
    UINT uSrcTransIndex, uDestTransIndex;
    if (SUCCEEDED(XuiNavButtonGetTransIndices(hObjSource, &uSrcTransIndex, &uDestTransIndex)))
    {
        XuiSceneSetTransIndex(hCurrScene, XUI_NAV_FORWARD, uSrcTransIndex);
        XuiSceneSetTransIndex(hCachedScene, XUI_NAV_BACK, uDestTransIndex);
    }
    
    hr = XuiSceneNavigateForward(hCurrScene, XuiNavButtonGetStayVisible(hObjSource), hCachedScene, XUSER_INDEX_FOCUS);
    if (FAILED(hr))
    {
        ReleaseScene(hCachedScene);
        return FALSE;
    }

    return TRUE;
}
    
XUI_INLINE BOOL CXuiSceneCache::IsSceneInCache(HXUIOBJ hScene)
{
    SceneCacheEntry *pEntry = FindSceneInCache(hScene);
    return pEntry != NULL;
}
    
XUI_INLINE BOOL CXuiSceneCache::IsSceneInCache(LPCWSTR szFullPath)
{
    BOOL bResult = FALSE;
    
    EnterCriticalSection(&m_CS);
    SceneCacheEntry *pEntry = m_pHead;
    while (pEntry != NULL)
    {
        if (!_wcsicmp(szFullPath, pEntry->m_szFileName))
        {
            bResult = TRUE;
            break;
        }
        pEntry = pEntry->m_pNext;
    }
    LeaveCriticalSection(&m_CS);
    
    return bResult;
}
    
XUI_INLINE HRESULT CXuiSceneCache::OnSkinChanged()
{
    // send the skin change to all cached scenes that are not in use
    // we're assuming that scenes that are in use will get the skin change
    // through their current parent
    EnterCriticalSection(&m_CS);
    SceneCacheEntry *pEntry = m_pHead;
    while (pEntry != NULL)
    {
        if (!pEntry->m_bInUse)
        {
            XuiElementSkinChanged(pEntry->m_hObj);
        }
        pEntry = pEntry->m_pNext;
    }
    LeaveCriticalSection(&m_CS);

    return S_OK;
}

XUI_INLINE BOOL CXuiSceneCache::IsDescendantOfCachedScene(HXUIOBJ hScene)
{
    BOOL bResult = FALSE;
    
    EnterCriticalSection(&m_CS);
    SceneCacheEntry *pEntry = m_pHead;
    while (pEntry != NULL)
    {
        if (XuiElementIsDescendant(pEntry->m_hObj, hScene))
        {
            bResult = TRUE;
            break;
        }
        pEntry = pEntry->m_pNext;
    }
    LeaveCriticalSection(&m_CS);

    return bResult;
}
    
XUI_INLINE CXuiSceneCache::SceneCacheEntry *CXuiSceneCache::FindSceneInCache(HXUIOBJ hObj)
{
    EnterCriticalSection(&m_CS);
    SceneCacheEntry *pEntry = m_pHead;
    while (pEntry != NULL)
    {
        if (pEntry->m_hObj == hObj)
        {
            break;
        }
        pEntry = pEntry->m_pNext;
    }
    LeaveCriticalSection(&m_CS);
    
    return pEntry;
}

XUI_INLINE HXUIOBJ CXuiSceneCache::FindSceneObjInCache(LPCWSTR szFullPath)
{
    HXUIOBJ hObj = NULL;
    
    EnterCriticalSection(&m_CS);
    SceneCacheEntry *pEntry = m_pHead;
    while (pEntry != NULL)
    {
        if (!_wcsicmp(szFullPath, pEntry->m_szFileName))
        {
            hObj = pEntry->m_hObj;
            break;
        }
        pEntry = pEntry->m_pNext;
    }
    LeaveCriticalSection(&m_CS);
    
    return hObj;
}

////////////////////////////////////////////////////////////////////////////////
// CXuiCachingModule implementation
////////////////////////////////////////////////////////////////////////////////
XUI_INLINE CXuiCachingModule::CXuiCachingModule()
{
    m_hClassNavButton = NULL;
    m_hClassBackButton = NULL;
    m_hClassScene = NULL;
}

XUI_INLINE HRESULT CXuiCachingModule::Init(PFN_XUITEXTURELOADER pfnTextureLoader, XUIInitParams *pInitParams/*=NULL*/)
{
    HRESULT hr = CXuiModule::Init(pfnTextureLoader, pInitParams);
    if (FAILED(hr))
        return hr;

    return CompleteInitialization();
}

XUI_INLINE HRESULT CXuiCachingModule::InitShared(IDirect3DDevice9 *pDevice, const D3DPRESENT_PARAMETERS *pPresentParams, PFN_XUITEXTURELOADER pfnTextureLoader, XUIInitParams *pInitParams /*=NULL*/)
{
    HRESULT hr = CXuiModule::InitShared(pDevice, pPresentParams, pfnTextureLoader, pInitParams);
    if (FAILED(hr))
        return hr;

    return CompleteInitialization();
}

XUI_INLINE HRESULT CXuiCachingModule::InitEx(XUIRenderInitParams *pRenderInitParams, XUIInitParams *pInitParams /*=NULL*/)
{
    HRESULT hr = CXuiModule::InitEx(pRenderInitParams, pInitParams);
    if (FAILED(hr))
        return hr;
    return CompleteInitialization();
}

XUI_INLINE HRESULT CXuiCachingModule::CompleteInitialization()
{
    m_hClassNavButton = XuiFindClass(XUI_CLASS_NAVBUTTON);
    m_hClassBackButton = XuiFindClass(XUI_CLASS_BACKBUTTON);
    m_hClassScene = XuiFindClass(XUI_CLASS_SCENE);

    HRESULT hr = m_sceneCache.Init();
    if (FAILED(hr))
        return hr;

    s_cachingModuleInst = this;

    XuiSetMessageFilter((PFN_MESSAGE_FILTER)_SceneCacheMessageFilter);
    return S_OK;
}

/*virtual*/ XUI_INLINE void CXuiCachingModule::Uninit()
{
    XuiSetMessageFilter(NULL);
    m_sceneCache.Uninit();
    CXuiModule::Uninit();
}

XUI_INLINE HRESULT CXuiCachingModule::CacheScene(LPCWSTR szFullPath, int nCacheLevels/*=0*/, HXUIOBJ *phScene/*=NULL*/)
{
    return m_sceneCache.CacheScene(szFullPath, nCacheLevels, phScene);
}

#ifdef _XBOX
XUI_INLINE HRESULT CXuiCachingModule::CacheSceneAsync(XUICacheSceneAsync pScenes[], DWORD dwCount, 
                                                      XOVERLAPPED *pOverlapped/*=NULL*/, DWORD dwHardwareThread/*=0xFFFFFFFF*/)
#else
XUI_INLINE HRESULT CXuiCachingModule::CacheSceneAsync(XUICacheSceneAsync pScenes[], DWORD dwCount, 
                                                      OVERLAPPED *pOverlapped/*=NULL*/, DWORD dwHardwareThread/*=0xFFFFFFFF*/)
#endif
{
    return m_sceneCache.CacheSceneAsync(pScenes, dwCount, pOverlapped, dwHardwareThread);
}

XUI_INLINE BOOL CXuiCachingModule::ReleaseScene(HXUIOBJ hObj)
{
    return m_sceneCache.ReleaseScene(hObj);
}

XUI_INLINE BOOL CXuiCachingModule::RemoveSceneFromCache(HXUIOBJ hScene)
{
    return m_sceneCache.RemoveScene(hScene);
}

XUI_INLINE HXUIOBJ CXuiCachingModule::GetSceneFromCache(LPCWSTR szPath)
{
    return m_sceneCache.GetSceneFromCache(szPath);
}
    
XUI_INLINE HRESULT CXuiCachingModule::MessageFilter(HXUIOBJ hObj, XUIMessage *pMessage)
{
    if (pMessage->dwMessage == XM_NOTIFY)
    {
        XUINotify *pNotify = (XUINotify *) pMessage->pvData;
        if (pNotify->dwNotify == XN_PRESS)
        {
            HXUIOBJ hNavButton = XuiDynamicCast(pNotify->hObjSource, m_hClassNavButton);
            if (hNavButton)
            {
                if (m_sceneCache.HandleNavigation(hNavButton, pNotify))
                    pMessage->bHandled = TRUE;
            }
        }
    }
    else if (pMessage->dwMessage == XM_TRANSITION_END || pMessage->dwMessage == XM_TRANSITION_START)
    {
        XUIMessageTransition *pData = (XUIMessageTransition *) pMessage->pvData;
        if (pData->dwTransType == XUI_TRANSITION_BACKFROM)
        {
            if (m_sceneCache.IsSceneInCache(hObj))
            {
                pData->dwTransAction = XUI_TRANSITION_ACTION_UNLINK;
                
                if (pMessage->dwMessage == XM_TRANSITION_END)
                    m_sceneCache.ReleaseScene(hObj);
            }
        }
    }
    else if (pMessage->dwMessage == XM_GET_DISCARD_FLAGS)
    {
        XUIMessageDiscardResources *pData = (XUIMessageDiscardResources *) pMessage->pvData;
        if (m_sceneCache.IsDescendantOfCachedScene(hObj))
        {
            pData->dwFlags = 0;
            pMessage->bHandled = TRUE;
        }
    }
#ifdef _DEBUG
    else if (pMessage->dwMessage == XM_DESTROY)
    {
        HXUIOBJ hScene = XuiDynamicCast(hObj, m_hClassScene);
        if (hScene != NULL)
        {
            ASSERT(m_sceneCache.IsSceneInCache(hObj)==FALSE);
        }
    }
#endif
    return S_OK;
}

/*static*/ XUI_INLINE HRESULT APIENTRY CXuiCachingModule::_SceneCacheMessageFilter(HXUIOBJ hObj, XUIMessage *pMessage)
{
    return s_cachingModuleInst->MessageFilter(hObj, pMessage);
}
/*static*/ __declspec(selectany) CXuiCachingModule *CXuiCachingModule::s_cachingModuleInst;

