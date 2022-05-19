//===========================================================================
// Filename:	XMassiveAdClienttSubscriber.h
//
// Declaration file for the Massive AdClient Subscriber. (External)
//
// Copyright (c) Microsoft Corp. All rights reserved.
//
//===========================================================================

#ifndef __MASSIVEADOBJECTSUBSCRIBER_H__
#define __MASSIVEADOBJECTSUBSCRIBER_H__

#include "XMassiveAdClientMediaTypes.h"

#ifdef  __cplusplus

namespace MassiveAdClient3
{

// Forward Declaration
class CMassiveAdObject;

//===========================================================================
// XMassiveAdClientSubscriber Class

class XMassiveAdClientSubscriber
{
public:
	// Construction
	XMassiveAdClientSubscriber(IN const char *szName);
	~XMassiveAdClientSubscriber();

	// Accessors
	char const *GetName();					// Name of the Subscriber
	UINT GetInvElementID();			// Inventory Element ID
	UINT GetCrexID();					// Crex ID
	char const *GetCrexFileName();			// Name of current crex, assigned after download is complete
	MAD_MEDIATYPE GetCrexAssetType();		// Asset Type of current crex (jpg, bmp, etc)

	// Impressions
	void SetImpression(IN MAD_Impression *pImpression);		// Set Impression data for Subscriber
	DWORD SetInteraction(IN MASSIVE_INTERACTION type);	// Set Interaction data for Subscriber

	// View State
	MAD_VIEW_STATE GetViewState() { return m_eViewState; }

	// Download Media
	virtual BOOL MediaDownload(IN const UINT uAssetID);
    virtual BOOL MediaDownloadComplete(IN const char *MediaData, IN const UINT uDataLength, IN const UINT uMediaType, IN const UINT uAssetID);
	DWORD VerifyData(IN const UINT uCrexID, IN const UINT uDataLength, IN const char *MediaData);

	// Update
	virtual void Update();

	// State Control
	DWORD Suspend();
	DWORD Resume();

	DWORD GetLastError();

	// Clear the downloaded Media Buffer
	void ClearMediaBuffer();

private:
	char *m_pName;							// Subscriber Name
	CMassiveAdObject *m_pMassiveAdObject;	// Used internally by Massive AdClient
	DWORD	m_LastError;		// Last Error
	BOOL			m_bMediaDownloaded;	// Media Downloaded flag

	MAD_Impression m_CurrentImpression;		// Current Impression of Subscriber
	MAD_Impression m_CopyImpression;		// Internal data structure
	MAD_VIEW_STATE m_eViewState;			// Current ViewState of Subscriber
};

}	//namespace MassiveAdClient3
#else

	// C Interface
	typedef struct _XMassiveAdClientSubscriber XMassiveAdClientSubscriber;

	// Callback Function Pointers
	typedef BOOL (*MediaDownloadCallback)(XMassiveAdClientSubscriber *p_sub, const UINT uAssetID);
	typedef BOOL (*MediaDownloadCompleteCallback)(XMassiveAdClientSubscriber *p_sub, const char *MediaData, const UINT uDataLength, const UINT uMediaType, const UINT uAssetID);
	typedef void (*UpdateCallback)(XMassiveAdClientSubscriber *p_sub);


	XMassiveAdClientSubscriber *XMassiveAdClientSubscriberCreate(
		const char *szName, 
		MediaDownloadCallback fp_mediaDownloadCallback,
		MediaDownloadCompleteCallback fp_mediaDownloadCompleteCallback,
		UpdateCallback fp_updateCallback);

	DWORD XMassiveAdClientSubscriberDestroy(XMassiveAdClientSubscriber **pSub);

	// Accessors
	const char *XMassiveAdClientSubscriberGetName(XMassiveAdClientSubscriber *pSub);
	const char *XMassiveAdClientSubscriberGetCrexFileName(XMassiveAdClientSubscriber *pSub);
	UINT XMassiveAdClientSubscriberGetInvElementID(XMassiveAdClientSubscriber *pSub);
	UINT XMassiveAdClientSubscriberGetCrexID(XMassiveAdClientSubscriber *pSub);
	MAD_MEDIATYPE XMassiveAdClientSubscriberGetCrexAssetType(XMassiveAdClientSubscriber *pSub);

	// Impressions
	void XMassiveAdClientSubscriberSetImpression(XMassiveAdClientSubscriber *pSub, MAD_Impression *pImpression);
	DWORD XMassiveAdClientSubscriberSetInteraction(XMassiveAdClientSubscriber *pSub, MASSIVE_INTERACTION eInteraction);

	// View State
	MAD_VIEW_STATE XMassiveAdClientSubscriberGetViewState(XMassiveAdClientSubscriber *pSub);

	// State Control
	DWORD XMassiveAdClientSubscriberSuspend(XMassiveAdClientSubscriber *pSub);
	DWORD XMassiveAdClientSubscriberResume(XMassiveAdClientSubscriber *pSub);

	DWORD XMassiveAdClientSubscriberGetLastError(XMassiveAdClientSubscriber *pSub);

	// Clear the downloaded Media Buffer
	XMassiveAdClientSubscriberClearMediaBuffer(XMassiveAdClientSubscriber *pSub);

#endif  // _cplusplus

#endif	// __MASSIVEADOBJECTSUBSCRIBER_H__
