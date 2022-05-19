/*==========================================================================;
 *
 *  Copyright (C) Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       xuiresource.h
 *  Content:    Xbox 360 UI resource defines, structures, and functions
 *
 ****************************************************************************/
 
#ifndef __XUIRESOURCE_H__
#define __XUIRESOURCE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _XUIRESOURCE* HXUIRESOURCE;
typedef struct _XUIPACKAGE*  HXUIPACKAGE;
typedef enum XUI_SEEK_OPTIONS XUI_SEEK_OPTIONS;

enum XUI_SEEK_OPTIONS
{
    XUI_SEEK_FROM_START   = 0x1,
    XUI_SEEK_FROM_CURRENT = 0x2,
    XUI_SEEK_FROM_END     = 0x4
};


typedef struct IXuiResourceManager IXuiResourceManager;
typedef struct IXuiResourceReader IXuiResourceReader;

struct IXuiResourceReaderVTBL
{
    VOID                 (STDMETHODCALLTYPE *AddRef)(IXuiResourceReader* pThis);
    UINT                 (STDMETHODCALLTYPE *Release)(IXuiResourceReader* pThis);
    IXuiResourceManager* (STDMETHODCALLTYPE *GetManager)(IXuiResourceReader* pThis);
    HRESULT              (STDMETHODCALLTYPE *SetManager)(IXuiResourceReader* pThis, IXuiResourceManager* pManager);
    UINT                 (STDMETHODCALLTYPE *GetTotalSize)(IXuiResourceReader* pThis);
    UINT                 (STDMETHODCALLTYPE *GetRemainingBytes)(IXuiResourceReader* pThis);
    HRESULT              (STDMETHODCALLTYPE *Read)(IXuiResourceReader* pThis, BYTE * pbDst, UINT cb, UINT * cbRead);
    HRESULT              (STDMETHODCALLTYPE *Seek)(IXuiResourceReader* pThis, UINT fFlags, INT iOffset);
    HRESULT              (STDMETHODCALLTYPE *GetBuffer)(IXuiResourceReader* pThis, CONST BYTE **ppBuffer);
    HRESULT              (STDMETHODCALLTYPE *ReleaseBuffer)(IXuiResourceReader* pThis);
    HRESULT              (STDMETHODCALLTYPE *Duplicate)(IXuiResourceReader* pThis, IXuiResourceReader** ppDuplicateReader);
};

struct IXuiResourceReader
{
#ifdef __cplusplus

    virtual VOID                  STDMETHODCALLTYPE AddRef()=0;
    virtual UINT                  STDMETHODCALLTYPE Release()=0;
    virtual IXuiResourceManager * STDMETHODCALLTYPE GetManager()=0;
    virtual HRESULT               STDMETHODCALLTYPE SetManager(IXuiResourceManager* pManager)=0;
    virtual UINT                  STDMETHODCALLTYPE GetTotalSize()=0;
    virtual UINT                  STDMETHODCALLTYPE GetRemainingBytes()=0;
    virtual HRESULT               STDMETHODCALLTYPE Read(BYTE * pbDst, UINT cb, UINT * cbRead)=0;
    virtual HRESULT               STDMETHODCALLTYPE Seek(UINT fFlags, INT iOffset)=0;
    virtual HRESULT               STDMETHODCALLTYPE GetBuffer(CONST BYTE **ppBuffer) = 0;
    virtual HRESULT               STDMETHODCALLTYPE ReleaseBuffer() = 0;
    virtual HRESULT               STDMETHODCALLTYPE Duplicate(IXuiResourceReader** ppDuplicateReader) = 0;

#else
 
    struct IXuiResourceReaderVTBL * pVtbl;

#endif
};



struct IXuiResourceManagerVTBL
{
    VOID    (STDMETHODCALLTYPE *AddRef)(IXuiResourceManager* pThis);
    UINT    (STDMETHODCALLTYPE *Release)(IXuiResourceManager* pThis);
    LPCWSTR (STDMETHODCALLTYPE *GetName)(IXuiResourceManager* pThis);
    BOOL    (STDMETHODCALLTYPE *IsTransport)(IXuiResourceManager* pThis);
    HRESULT (STDMETHODCALLTYPE *Init)(IXuiResourceManager* pThis, IXuiResourceReader * pBaseReader);
    HRESULT (STDMETHODCALLTYPE *Open)(IXuiResourceManager* pThis, LPCWSTR szPath, IXuiResourceReader ** pReader);
    HRESULT (STDMETHODCALLTYPE *GetFileAttributes)(IXuiResourceManager* pThis, LPCWSTR szPath, WIN32_FILE_ATTRIBUTE_DATA * pAttributes);
};

struct IXuiResourceManager
{
#ifdef __cplusplus

    virtual VOID    STDMETHODCALLTYPE  AddRef()=0;
    virtual UINT    STDMETHODCALLTYPE Release()=0;
    virtual LPCWSTR STDMETHODCALLTYPE GetName()=0;
    virtual BOOL    STDMETHODCALLTYPE IsTransport()=0;
    virtual HRESULT STDMETHODCALLTYPE Init(IXuiResourceReader * pBaseReader)=0;
    virtual HRESULT STDMETHODCALLTYPE Open(LPCWSTR szPath, IXuiResourceReader ** pReader)=0; 
    virtual HRESULT STDMETHODCALLTYPE GetFileAttributes(LPCWSTR szPath, WIN32_FILE_ATTRIBUTE_DATA * pAttributes) = 0;

#else
 
    struct IXuiResourceManagerVTBL * pVtbl;

#endif
};


BOOL    APIENTRY XuiResourceLocatorIsAbsolute(LPCWSTR szLocator);
BOOL    APIENTRY XuiResourceLocatorIsFile(LPCWSTR szLocator);
HRESULT APIENTRY XuiResourceComposeLocator(LPWSTR * pszComposedPath, LPCWSTR szBase, LPCWSTR szRelative);
HRESULT APIENTRY XuiResourceOpen(LPCWSTR szLocator, HXUIRESOURCE * phResource, BOOL *pbIsMemoryResource);
HRESULT APIENTRY XuiResourceOpenNoLoc(LPCWSTR szLocator, HXUIRESOURCE * phResource, BOOL *pbIsMemoryResource);
HRESULT APIENTRY XuiResourceDuplicateHandle(HXUIRESOURCE hResource, HXUIRESOURCE *phDuplicate);
HRESULT APIENTRY XuiResourceGetBuffer(HXUIRESOURCE hResource, CONST BYTE **ppBuffer);
HRESULT APIENTRY XuiResourceReleaseBuffer(HXUIRESOURCE hResource, CONST BYTE *pBuffer);
HRESULT APIENTRY XuiResourceRead(HXUIRESOURCE hResource, BYTE * pbDest, UINT cb, UINT * pcbRead);
UINT    APIENTRY XuiResourceGetTotalSize(HXUIRESOURCE hResource);
HRESULT APIENTRY XuiResourceSeek(HXUIRESOURCE hResource, DWORD dwSeekOptions, INT iOffset);
VOID    APIENTRY XuiResourceClose(HXUIRESOURCE hResource);
HRESULT APIENTRY XuiResourceLoadAll(LPCWSTR szLocator, BYTE ** ppb, UINT * pcb);
HRESULT APIENTRY XuiResourceLoadAllNoLoc(LPCWSTR szLocator, BYTE ** ppb, UINT * pcb);
HRESULT APIENTRY XuiRegisterResourceTransport(IXuiResourceManager * pManager, IXuiResourceManager ** ppPreviousManager);
VOID    APIENTRY XuiUnregisterResourceTransport(LPCWSTR szTransport);

VOID    APIENTRY XuiResourcePackageExpiration(BOOL bEnable);
HRESULT APIENTRY XuiResourceOpenPackage(LPWSTR szLocator, HXUIPACKAGE *phPackage, BOOL fLocalizePath);
UINT    APIENTRY XuiResourceGetPackageEntryCount(HXUIPACKAGE hPackage);
HRESULT APIENTRY XuiResourceGetPackageEntryInfo(HXUIPACKAGE hPackage, UINT index, LPWSTR szLocator, UINT *pLocatorSize, 
                                                UINT *pFileOffset, UINT *pLength, FILETIME *pFileTime);
VOID    APIENTRY XuiResourceReleasePackage(HXUIPACKAGE hPackage);

#ifdef __cplusplus
}
#endif

#endif // __XUIRESOURCE_H__

