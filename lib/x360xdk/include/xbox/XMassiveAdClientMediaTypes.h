//===========================================================================
// Filename:	XMassiveAdClientMediaTypes.h
//
// Definitions for Massive AdClient objects and types.
//
// Copyright (c) Microsoft Corp. All rights reserved.
//
//===========================================================================

#ifndef ___MASSIVEMEDIATYPES_H___
#define ___MASSIVEMEDIATYPES_H___

#ifdef __cplusplus
extern "C" {

namespace MassiveAdClient3
{
#endif

// Memory
typedef void *(*massiveMalloc) (size_t);
typedef void (*massiveFree) (void *);

//===========================================================================
// Massive AdClient Error Codes

#define MAD_INTERNAL_SUCCESS				   			  0	// Successfully handled request
#define MAD_INTERNAL_GENERROR							100	// Unclassified error code
#define MAD_INTERNAL_MEMORY_ERROR						101	// Couldn't allocate any more memory
#define MAD_INTERNAL_INVALID_SESSION					102	// Bad Session ID
#define MAD_INTERNAL_MULTIPLE_SESSIONS_ERROR			103	// Cannot join multiple sessions call MAD_INTERNAL_LeaveSession()
#define MAD_INTERNAL_FEATURE_DISABLED					104
#define MAD_INTERNAL_THREAD_ERROR						105	// Unable to obtain/releash thread issues   

// Client Core
#define MAD_INTERNAL_CORE_NOT_INITIALIZED				200
#define MAD_INTERNAL_CORE_ALREADY_INITIALIZED			201
#define MAD_INTERNAL_CORE_INVALID_INITSTRUCT			202
#define MAD_INTERNAL_CORE_INVALID_SKU					203
#define MAD_INTERNAL_CORE_INVALID_SKU_VERSION			204
#define MAD_INTERNAL_CORE_INVALID_PUBLIC_KEY			205
#define MAD_INTERNAL_CORE_INVALID_GUID					206
#define MAD_INTERNAL_CORE_INVALID_STATE					207
#define MAD_INTERNAL_CORE_IMPRESSION_TIME_NOT_REACHED	208
#define MAD_INTERNAL_CORE_TICK_TIME_NOT_REACHED			209
#define MAD_INTERNAL_CORE_NO_CURRENT_ZONE				210
#define MAD_INTERNAL_CORE_FAILED_LOCATE_SERVICE			211
#define MAD_INTERNAL_CORE_FAILED_OPEN_SESSION			212
#define MAD_INTERNAL_CORE_FAILED_CLOSE_SESSION			213
#define MAD_INTERNAL_CORE_SHUTDOWN_INVALID				214
#define MAD_INTERNAL_CORE_SHUTDOWN_TIMEOUT				215

// ZoneManager
#define MAD_INTERNAL_ZONE_INVALID_NAME					300
#define MAD_INTERNAL_ZONE_FAILED_IMPUPDATE_REQUEST_CREATION	301
#define MAD_INTERNAL_ZONE_FAILED_ENTERZONE				302
#define MAD_INTERNAL_ZONE_FAILED_EXITZONE				303

// MAO
#define MAD_INTERNAL_MAO_INVALID_NAME					400
#define MAD_INTERNAL_MAO_FAILED_CREATION				401
#define MAD_INTERNAL_MAO_EXISTS							402
#define MAD_INTERNAL_MAO_INVALID_ASSET					403
#define MAD_INTERNAL_MAO_FAILED_ASSET_DOWNLOAD			404
#define MAD_INTERNAL_MAO_FAILED_ROTATE					405
#define MAD_INTERNAL_MAO_INVALID_DATA_BUFFER			406
#define MAD_INTERNAL_MAO_NO_CURRENT_VIEW_RECORD			407
#define MAD_INTERNAL_MAO_IS_PAUSED						408
#define MAD_INTERNAL_MAO_FAILED_IMPRESSION_REPORT		409
#define MAD_INTERNAL_MAO_FAILED_IMPRESSION_SET			410
#define MAD_INTERNAL_MAO_FAILED_INTERACTION_SET			411

// Subscriber
#define MAD_INTERNAL_MAOSUB_INVALID_NAME				500
#define MAD_INTERNAL_MAOSUB_EXISTS						501
#define MAD_INTERNAL_MAOSUB_DATA_HASH_FAILED			502

// Asset
#define MAD_INTERNAL_ASSET_INVALID_ID					600
#define MAD_INTERNAL_ASSET_EXISTS						601
#define MAD_INTERNAL_ASSET_FAILED_DOWNLOAD				602
#define MAD_INTERNAL_ASSET_INVALID_URL					603
#define MAD_INTERNAL_ASSET_INVALID_HASH					604
#define MAD_INTERNAL_ASSET_INVALID_SIZE					605
#define MAD_INTERNAL_ASSET_INVALID_DATE					606
#define MAD_INTERNAL_ASSET_INVALID_DATALENGTH			607
#define MAD_INTERNAL_ASSET_FAILED_IMPRESSION_REPORT		608
#define MAD_INTERNAL_ASSET_FAILED_IMPRESSION_SET		609

	// Request Manager
#define MAD_INTERNAL_REQ_MAN_BAD_REQ_STATUS				700
#define MAD_INTERNAL_REQ_MAN_NOT_WRITABLE				701
#define MAD_INTERNAL_REQ_MAN_CANT_ADD_TO_QUEUE			702
#define MAD_INTERNAL_REQ_MAN_CANT_FIND_REQUEST			703
#define MAD_INTERNAL_REQ_MAN_CANT_ACCESS_QUEUE			704

// Network Manager
#define MAD_INTERNAL_NETWORK_SOCKET_ERROR				800
#define MAD_INTERNAL_NETWORK_ADDRESS_NOT_RESOLVED		801
#define MAD_INTERNAL_NETWORK_DNS_ERROR					802
#define MAD_INTERNAL_NETWORK_SEND_ERROR					803
#define MAD_INTERNAL_NETWORK_RECV_ERROR					804
#define MAD_INTERNAL_NETWORK_CONNECT_ERROR				805
#define MAD_INTERNAL_NETWORK_DISCONNECT_ERROR			806		
#define MAD_INTERNAL_NETWORK_BAD_STATUS					807

// Transaction
#define MAD_INTERNAL_TRANSACTION_NULL_REQUEST			900
#define MAD_INTERNAL_TRANSACTION_REQ_BAD_STATE			901

// RequestBuilder
#define MAD_INTERNAL_REQ_BUILDER_CANT_ADD				1000
#define MAD_INTERNAL_REQ_BUILDER_NOT_FOUND				1001
#define MAD_INTERNAL_REQ_BUILDER_EMPTY					1002

// Request
#define MAD_INTERNAL_REQ_INVALID_PARAMETER				1100
#define MAD_INTERNAL_REQ_SERVER_INDEX_OUT_OF_BOUNDS		1101
#define MAD_INTERNAL_REQ_INVALID_STATUS					1102
#define MAD_INTERNAL_REQ_GENERAL_ERROR					1103


//===========================================================================
// Define types
//===========================================================================

#if !defined massiveBool
	typedef int massiveBool;
#endif

#if !defined massiveUByte
	#undef massiveByte
	typedef unsigned char massiveUByte; //The best variable type ever!!!
	typedef signed char   massiveByte;
#endif

#if !defined massiveU8						
	#undef massiveI8
	typedef unsigned char massiveU8;		
	typedef signed   char massiveI8;
#endif

#if !defined massiveU16						
	#undef massiveI16
	typedef unsigned short massiveU16;				
	typedef signed   short massiveI16;
#endif

#if !defined massiveU32
	#undef massiveI32
	typedef unsigned int massiveU32;
	typedef signed   int massiveI32;
#endif

#if !defined massiveFloat
	typedef float massiveFloat;
#endif

//===========================================================================
// The AdClient libray can be configured at startup with certain behaviors

typedef enum __MAD_CONFIG
{
	MAD_DEFAULT_CONFIG_FLAGS		= 0x00000000, // No specific configuration needed
	MAD_MANUAL_MEDIABUFFER_FLUSH	= 0x00000001, // The Asset Media buffer will not be Automatically  Deleted
	MAD_DOWNLOAD_MEDIA_IMMEDIATE	= 0x00000002, // Tells the client to download all media immediately and not wait for subsribers
	MAD_CREATE_DEBUG_CSV			= 0x00000004, // Enable Debug Logging of Zones/Subscribers to CSV file 
	MAD_NETWORK_FAST				= 0x00000020, // Doubles the normal TCP buffersize as well as the AdClients internal network buffer
	MAD_NETWORK_SMALL				= 0x00000040, // Halves the normal TCP buffersize as well as the AdClients internal network buffer
} MAD_CONFIG;

//===========================================================================
// The AdClient library can deliver a variety of advertisements efficiently and
// securely. Game developers that use a proprietary image format should contact
// Massive or provide a runtime conversion for one of the supported types.
typedef enum __MAD_MEDIATYPE
{
	MAD_MEDIA_INVALID = 0,
	MAD_MEDIA_IMAGE_JPG,					// Standard JPEG image files
	MAD_MEDIA_IMAGE_GIF,					// GIF89 image files (special use only)
	MAD_MEDIA_IMAGE_PNG,					// Standard PNG image files
	MAD_MEDIA_IMAGE_BMP_24,					// 24 Bit Bitmap image files
	MAD_MEDIA_IMAGE_TGA,					// Targa image files
	MAD_MEDIA_IMAGE_DXT1,					// DirectX compressed texture format (1)
	MAD_MEDIA_IMAGE_DXT5,					// DirectX compressed texture format (5)
	MAD_MEDIA_IMAGE_CUSTOM,					// Custom image file definition (special use only)
	MAD_MEDIA_IMAGE_LEGACY_JPG_SUB,			// Special JPEG image files for subway demo
	MAD_MEDIA_IMAGE_DXT1_M,					// DirectX compressed texture format with mipmaps(1)
	MAD_MEDIA_IMAGE_DXT3_M,					// DirectX compressed texture format with mipmaps(3)
	MAD_MEDIA_IMAGE_DXT5_M,					// DirectX compressed texture format with mipmaps(5)
	MAD_MEDIA_IMAGE_DXT1_A,					// DirectX compressed texture format with alpha(1)
	MAD_MEDIA_IMAGE_DXT5_A,					// DirectX compressed texture format with alpha(5)
	MAD_MEDIA_IMAGE_DXT1_AM,				// DirectX compressed texture format with alpha and mipmaps(1)
	MAD_MEDIA_IMAGE_LEGACY_WAV,				// WAV Audio [Obsolete]
	MAD_MEDIA_IMAGE_LEGACY_BIK,				// BIK Video [Obsolete]
	MAD_MEDIA_IMAGE_LEGACY_3D_MODEL,		// 3D Model Generic [Obsolete]
	MAD_MEDIA_IMAGE_MASSIVE_JPG,			// **Massive Internal Use Only**
	MAD_MEDIA_IMAGE_TX2,					// TX2 Image Files
	MAD_MEDIA_IMAGE_BMP_8,					// 8 Bit Bitmap image files
	MAD_MEDIA_IMAGE_BMP_16,					// 16 Bit Bitmap image files
	MAD_MEDIA_IMAGE_BMP_32,					// 32 Bit Bitmap image files
	MAD_MEDIA_IMAGE_TGA_VC_COMPRESSED,		// VC Compressed Tga
	MAD_MEDIA_IMAGE_TGA_32,					// 32 Bit Targa files
	MAD_MEDIA_IMAGE_LEGACY_TGA_COMPRESSED,	// Legacy Targa files
	MAD_MEDIA_IMAGE_INTERACTIVE_AD_FC,		// Custom FC Interactive Ad
	MAD_MEDIA_IMAGE_CUSTOM_SC4,				// Custom SC4 File
	MAD_MEDIA_IMAGE_CUSTOM_IFF,				// Custom IFF File
	MAD_MEDIA_IMAGE_CUSTOM_Z,				// Custom Z File
	MAD_MEDIA_IMAGE_CUSTOM_IFF_2,			// Custom IFF 2 File
	MAD_MEDIA_IMAGE_CUSTOM_SC4_2,			// Custom SC3 - 2 File
	MAD_MEDIA_IMAGE_CUSTOM_NFS_DXT1,		// Custom 360 DXT1 Format
	MAD_MEDIA_IMAGE_CUSTOM_PNG_E_UI,		// Custom UI PNG Format
	MAD_MEDIA_IMAGE_DXT1_360,				// DXT 360 Optimized texture 1, tiled
	MAD_MEDIA_IMAGE_DXT5_360,				// DXT 360 Optimized texture 5, tiled
	MAD_MEDIA_IMAGE_CUSTOM_XPR,				// Custom xpr File Format
	MAD_MEDIA_IMAGE_DXT1_360_LINEAR,		// DXT 360 Optimized texture 1, linear
	MAD_MEDIA_IMAGE_DXT5_360_LINEAR,		// DXT 360 Optimized texture 5, linear
	MAD_MEDIA_IMAGE_CUSTOM_HO,				// Custom ho File Format


	MAD_MEDIA_VIDEO_START = 1024,
	MAD_MEDIA_VIDEO_BINK,					// Bink Video
	MAD_MEDIA_VIDEO_SWF,					// SWF (Flash)
	MAD_MEDIA_VIDEO_ID,						// ID Video File
	MAD_MEDIA_VIDEO_CUSTOM_VP6,				// Custom VP6 Format

	MAD_MEDIA_AUDIO_START = 2048,
	MAD_MEDIA_AUDIO_WAV,					// Standard WAV file
	MAD_MEDIA_AUDIO_OGG,					// Standard OGG File

	MAD_MEDIA_3DOBJ_START = 4096,
	MAD_MEDIA_MODEL_GENERIC,				// 3d model of unspecified type
	MAD_MEDIA_MODEL_3DS,					// 3ds model

	MAD_MEDIA_OTHER_START = 8192,
	MAD_MEDIA_OTHER_TEXT_FILE,				// Text file for url, other string data
	MAD_MEDIA_OTHER_FLV,					// Flash Video

	MAD_MEDIA_TYPES_END

} MAD_MEDIATYPE ;

//===========================================================================
// Level of detail for the client to log in Debug and Logging Builds

typedef enum __MASSIVE_ENUM_LOG_LEVEL
{
	LOG_LEVEL_NONE = 0,
	LOG_LEVEL_SEVERE,		// Malloc Fails, Internal Null Pointer, Network Error
	LOG_LEVEL_ERROR,		// Null Pointer passed to Lib, Parsing Error
	LOG_LEVEL_WARNING,		// Non critical problems/events
	LOG_LEVEL_INFO,			// Success/Fail of Transactions, Zone Names, IE Names
	LOG_LEVEL_DEBUG,		// Object Dumps, Full Request/Response Dumps, IE spreadsheet
	LOG_LEVEL_IMPRESSION,	// Shows Impression and View Information
	LOG_LEVEL_TRACE,		// Fuction Calls

	LOG_LEVEL_MAX			// Max Log Level

} MASSIVE_ENUM_LOG_LEVEL;

//===========================================================================
// Types of Interactions with Objects

typedef enum __MASSIVE_INTERACTION
{
	INTERACTION_NONE = 0,	// No Interaction
	INTERACTION_USE,		// Use, Open, Activate
	INTERACTION_HOSTILE,	// Attack, shoot, melee etc
	INTERACTION_CONSUME,	// Eat, drink, etc
	INTERACTION_PICKUP,		// Pickup, move, carry etc
	INTERACTION_AREA,		// Enter, Leave area etc
	INTERACTION_BENEFIT,	// Beneficial to player
	INTERACTION_MAX

} MASSIVE_INTERACTION;

//===========================================================================
// Subscriber View States

typedef enum __MAD_VIEW_STATE
{
	VIEW_STATE_INVALID = 0,
	VIEW_STATE_VIEW,
	VIEW_STATE_IMPRESSION,
	VIEW_STATE_OFFSCREEN,
	VIEW_STATE_MAX
} MAD_VIEW_STATE;


//===========================================================================

#define MAD_RESTRICT_ROTATION_NONE				(0x00000000) // No specific configuration needed
#define MAD_RESTRICT_ZONE_ROTATION 				(0x00000001) // Notify game before uploading impression data
#define MAD_RESTRICT_LINE_OF_SIGHT_ROTATION     (0x00000002) // Have incoming binary data streamed via callback

//===========================================================================
// The structure is passed in MassiveClientCore::Initialize() and MAD_Initialize()

typedef struct __MAD_MASSIVE_INIT_STRUCT
{
	char *szSku;								// Massive Assigned SKU
	char *szSkuVersion;							// Version of the SKU
	unsigned short u_libraryConfigFlags;		// Massive Client Configuration Options
	MASSIVE_ENUM_LOG_LEVEL eLogLevelFile;		// Value from MASSIVE_ENUM_LOG_LEVEL for log file
	MASSIVE_ENUM_LOG_LEVEL eLogLevelDebugger;	// Value from MASSIVE_ENUM_LOG_LEVEL for the Debuger Output Window
	unsigned long u_impressionFlushTime;		// Set to 0 to disable Auto Flush
} MAD_MASSIVE_INIT_STRUCT;


//===========================================================================
// The structure is passed in MassiveClientCore::

typedef struct __MAD_MASSIVE_DEMOGRAPH_STRUCT
{
	char *szMassiveID;
} MAD_MASSIVE_DEMOGRAPH_STRUCT;


//===========================================================================
// Impression Structures

typedef enum __MAD_REPORT_SIZE
{
	SIZE_LINEAR = 0,		// Default
	SIZE_PIXELS,
	MAD_REPORT_SIZE_MAX,
} MAD_REPORT_SIZE;

typedef enum __MAD_REPORT_ANGLE
{
	ANGLE_DOTPRODUCT = 0,	// Default
	ANGLE_RADIANS,
	ANGLE_DEGREES,
	MAD_REPORT_ANGLE_MAX,
} MAD_REPORT_ANGLE;

typedef struct _MAD_Impression
{
	// Reporting Types
	MAD_REPORT_SIZE  reportSize;
	MAD_REPORT_ANGLE reportAngle;

	// Generic
	massiveBool bInView;
	short siScreenWidth;
	short siScreenHeight;

	// Size & Angle - Texture, Video, Model
	unsigned int uSize;
	float fAngle;

	// Audio Specific
	massiveBool bPlayed;			
	float fFalloff;

}  MAD_Impression;

//===========================================================================
// Massive Object States

typedef enum __MAD_STATE
{
	// Standard States
	STATE_ERROR = 0,					// Error State
	STATE_INITIALIZING,					// Starting / Initializing State
	STATE_READY,						// Normal/Idle/Ready State
	STATE_PAUSED,						// Paused State
	STATE_SHUTDOWN,						// Object is shutting down

	// Core Specific States
	STATE_NOT_CONNECTED,				// Not Connected to the Massive
	STATE_LOCATE_SERVICE,				// Connecting
	STATE_LOCATE_SERVICE_REQUEST,		// Request Connection
	STATE_OPEN_SESSION,					// Opening Session
	STATE_OPEN_SESSION_REQUEST,			// Request Open Session
	STATE_CONNECTED,					// Connected (with Session)

	STATE_ENTERZONE,					// Receiving Zone information
	STATE_ENTERZONE_REQUEST,			// Request Zone information

	// ZoneManager Specific States
	STATE_EXITZONE,						// Exiting A Zone
	STATE_EXITZONE_REQUEST,				// Request to Exit a Zone

	// Mao Specific States
	STATE_MEDIA_REQUEST,
	STATE_MEDIA_DOWNLOAD,
	STATE_MEDIA_DOWNLOAD_COMPLETE,
	STATE_MEDIA_CLEAR_BUFFER,
	STATE_MEDIA_IDLE,
	STATE_MEDIA_ERROR,
	STATE_ROTATE_ASSET,

	STATE_MAX							// Max State for navigation

} MAD_STATE;

//===========================================================================
//  HELPER DEFINITIONS

#define MAD_IS_MEDIA_IMAGE_TYPE(x)	((MAD_MEDIA_IMAGE_START < (x)) && (MAD_MEDIA_IMAGE_END > (x)))
#define MAD_IS_MEDIA_AUDIO_TYPE(x)	((MAD_MEDIA_AUDIO_START < (x)) && (MAD_MEDIA_AUDIO_END > (x)))
#define MAD_INVALID_HANDLE (0)

#ifdef __cplusplus

} //namespace MassiveAdClient3

} // extern "C"
#endif


#endif //__MASSIVEMEDIATYPES_H__



