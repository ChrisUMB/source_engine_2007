/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       xuihtml.h
 *  Content:    Xbox 360 UI runtime HTML support
 *
 ****************************************************************************/
#ifndef __XUIHTML_H__
#define __XUIHTML_H__

#ifdef __cplusplus
extern "C" {
#endif

// Html class names
#define XUI_CLASS_HTML_ELEMENT          L"XuiHtmlElement"
#define XUI_CLASS_HTML_PRESENTER        L"XuiHtmlPresenter"
#define XUI_CLASS_HTML_CONTROL          L"XuiHtmlControl"


// Html control visual part names
#define HTML_CONTROL_SCROLL_UP          L"ScrollUp"
#define HTML_CONTROL_SCROLL_DOWN        L"ScrollDown"
#define HTML_CONTROL_SCROLL_BAR         L"ScrollBar"
#define HTML_CONTROL_HTML_PRESENTER     L"HtmlPresenter"

// Registration APIs
HRESULT APIENTRY XuiHtmlRegister();
void APIENTRY XuiHtmlUnregister();

// Message wrapper functions that are shared between XuiHtmlElement and XuiHtmlControl
static __declspec(noinline) LPCWSTR XuiHtmlGetText(HXUIOBJ hObj)
{
    XUIMessage msg;
    XUIMessageGetSourceText msgExt;
    XuiMessageGetSourceText(&msg, &msgExt, 0, 0, FALSE);
    XuiSendMessage(XuiGetOuter(hObj), &msg);
    return msgExt.szText;
}

static __declspec(noinline) HRESULT XuiHtmlSetText(HXUIOBJ hObj, LPCWSTR szText)
{
    XUIMessage msg;
    XUIMessageSetSourceText msgExt;
    XuiMessageSetSourceText(&msg, &msgExt, 0, 0, FALSE, szText);
    return XuiSendMessage(XuiGetOuter(hObj), &msg);
}

static __declspec(noinline) HRESULT XuiHtmlGetContentDims(HXUIOBJ hObj, XUIContentDims *pContentDims)
{
    HRESULT hr;
    XUIMessage msg;
    XUIMessageContentDims msgData;
    XuiMessageGetContentDims(&msg, &msgData);
    hr = XuiSendMessage(XuiGetOuter(hObj), &msg);
    if (FAILED(hr))
        return hr;
    memcpy(pContentDims, &msgData.contentDims, sizeof(*pContentDims));
    return S_OK;
}

static __declspec(noinline) HRESULT XuiHtmlSetVScrollPos(HXUIOBJ hObj, int nPos)
{
    XUIMessage msg;
    XUIMessageScroll msgExt;
    XuiMessageVScroll(&msg, &msgExt, nPos);
    return XuiSendMessage(XuiGetOuter(hObj), &msg);
}

// XuiHtmlControl related structures
typedef struct XUIHtmlScrollInfo
{
    BOOL bScrolling;    // TRUE=currently scrolling
    int nPos;           // current scrolling position
    int nTarget;        // target position
    int nStep;          // current step
    int nMax;           // maximum position
} XUIHtmlScrollInfo;

// XuiHtmlControl specific APIs
HRESULT APIENTRY XuiHtmlControlSetLineHeight(HXUIOBJ hObj, int nLineHeight);
HRESULT APIENTRY XuiHtmlControlVScrollBy(HXUIOBJ hObj, int nPixels);
HRESULT APIENTRY XuiHtmlControlGetVScrollInfo(HXUIOBJ hObj, XUIHtmlScrollInfo *pScrollInfo);

static __declspec(noinline) HRESULT XuiHtmlControlSetSmoothScroll(HXUIOBJ hObj,
                                                           XUI_SMOOTHSCROLL_ORIENTATION orientation,
                                                           BOOL bEnabled,
                                                           float fBaseSpeed,
                                                           float fAccel,
                                                           float fMaxSpeed)
{
    XUIMessage msg;
    XUIMessageSmoothScroll msgData;
    XuiMessageSetSmoothScroll(&msg, &msgData, orientation, bEnabled, fBaseSpeed, fAccel, fMaxSpeed);
    return XuiSendMessage(hObj, &msg);
}

static __declspec(noinline) HRESULT XuiHtmlControlGetSmoothScroll(HXUIOBJ hObj,
                                                           XUI_SMOOTHSCROLL_ORIENTATION orientation,
                                                           BOOL *pbEnabled,
                                                           float *pfBaseSpeed,
                                                           float *pfAccel,
                                                           float *pfMaxSpeed)
{
    HRESULT hr = S_OK;
    XUIMessage msg;
    XUIMessageSmoothScroll msgData;
    XuiMessageGetSmoothScroll(&msg, &msgData, orientation);
    hr = XuiSendMessage(hObj, &msg);
    if (SUCCEEDED(hr))
    {
        if (pbEnabled)
            *pbEnabled = msgData.bEnabled;
        if (pfBaseSpeed)
            *pfBaseSpeed = msgData.fBaseSpeed;
        if (pfAccel)
            *pfAccel = msgData.fAccel;
        if (pfMaxSpeed)
            *pfMaxSpeed = msgData.fMaxSpeed;
    }
    return hr;
}

#ifdef __cplusplus
};
#endif

#endif // __XUIHTML_H__