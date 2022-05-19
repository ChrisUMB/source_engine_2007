
/*
 * Version 3.0
 *
 * xonline.h
 *
 * This module defines Xbox Live structures and function prototypes
 *
 * Created on 07/19/07 at 00:06:59.
 */

#ifndef __XONLINE__
#define __XONLINE__

#ifdef __cplusplus
extern "C" {
#endif


//
// Country Codes
//
#define XONLINE_COUNTRY_UNITED_ARAB_EMIRATES 1
#define XONLINE_COUNTRY_ALBANIA              2
#define XONLINE_COUNTRY_ARMENIA              3
#define XONLINE_COUNTRY_ARGENTINA            4
#define XONLINE_COUNTRY_AUSTRIA              5
#define XONLINE_COUNTRY_AUSTRALIA            6
#define XONLINE_COUNTRY_AZERBAIJAN           7
#define XONLINE_COUNTRY_BELGIUM              8
#define XONLINE_COUNTRY_BULGARIA             9
#define XONLINE_COUNTRY_BAHRAIN              10
#define XONLINE_COUNTRY_BRUNEI_DARUSSALAM    11
#define XONLINE_COUNTRY_BOLIVIA              12
#define XONLINE_COUNTRY_BRAZIL               13
#define XONLINE_COUNTRY_BELARUS              14
#define XONLINE_COUNTRY_BELIZE               15
#define XONLINE_COUNTRY_CANADA               16
#define XONLINE_COUNTRY_SWITZERLAND          18
#define XONLINE_COUNTRY_CHILE                19
#define XONLINE_COUNTRY_CHINA                20
#define XONLINE_COUNTRY_COLOMBIA             21
#define XONLINE_COUNTRY_COSTA_RICA           22
#define XONLINE_COUNTRY_CZECH_REPUBLIC       23
#define XONLINE_COUNTRY_GERMANY              24
#define XONLINE_COUNTRY_DENMARK              25
#define XONLINE_COUNTRY_DOMINICAN_REPUBLIC   26
#define XONLINE_COUNTRY_ALGERIA              27
#define XONLINE_COUNTRY_ECUADOR              28
#define XONLINE_COUNTRY_ESTONIA              29
#define XONLINE_COUNTRY_EGYPT                30
#define XONLINE_COUNTRY_SPAIN                31
#define XONLINE_COUNTRY_FINLAND              32
#define XONLINE_COUNTRY_FAROE_ISLANDS        33
#define XONLINE_COUNTRY_FRANCE               34
#define XONLINE_COUNTRY_GREAT_BRITAIN        35
#define XONLINE_COUNTRY_GEORGIA              36
#define XONLINE_COUNTRY_GREECE               37
#define XONLINE_COUNTRY_GUATEMALA            38
#define XONLINE_COUNTRY_HONG_KONG            39
#define XONLINE_COUNTRY_HONDURAS             40
#define XONLINE_COUNTRY_CROATIA              41
#define XONLINE_COUNTRY_HUNGARY              42
#define XONLINE_COUNTRY_INDONESIA            43
#define XONLINE_COUNTRY_IRELAND              44
#define XONLINE_COUNTRY_ISRAEL               45
#define XONLINE_COUNTRY_INDIA                46
#define XONLINE_COUNTRY_IRAQ                 47
#define XONLINE_COUNTRY_IRAN                 48
#define XONLINE_COUNTRY_ICELAND              49
#define XONLINE_COUNTRY_ITALY                50
#define XONLINE_COUNTRY_JAMAICA              51
#define XONLINE_COUNTRY_JORDAN               52
#define XONLINE_COUNTRY_JAPAN                53
#define XONLINE_COUNTRY_KENYA                54
#define XONLINE_COUNTRY_KYRGYZSTAN           55
#define XONLINE_COUNTRY_KOREA                56
#define XONLINE_COUNTRY_KUWAIT               57
#define XONLINE_COUNTRY_KAZAKHSTAN           58
#define XONLINE_COUNTRY_LEBANON              59
#define XONLINE_COUNTRY_LIECHTENSTEIN        60
#define XONLINE_COUNTRY_LITHUANIA            61
#define XONLINE_COUNTRY_LUXEMBOURG           62
#define XONLINE_COUNTRY_LATVIA               63
#define XONLINE_COUNTRY_LIBYA                64
#define XONLINE_COUNTRY_MOROCCO              65
#define XONLINE_COUNTRY_MONACO               66
#define XONLINE_COUNTRY_MACEDONIA            67
#define XONLINE_COUNTRY_MONGOLIA             68
#define XONLINE_COUNTRY_MACAU                69
#define XONLINE_COUNTRY_MALDIVES             70
#define XONLINE_COUNTRY_MEXICO               71
#define XONLINE_COUNTRY_MALAYSIA             72
#define XONLINE_COUNTRY_NICARAGUA            73
#define XONLINE_COUNTRY_NETHERLANDS          74
#define XONLINE_COUNTRY_NORWAY               75
#define XONLINE_COUNTRY_NEW_ZEALAND          76
#define XONLINE_COUNTRY_OMAN                 77
#define XONLINE_COUNTRY_PANAMA               78
#define XONLINE_COUNTRY_PERU                 79
#define XONLINE_COUNTRY_PHILIPPINES          80
#define XONLINE_COUNTRY_PAKISTAN             81
#define XONLINE_COUNTRY_POLAND               82
#define XONLINE_COUNTRY_PUERTO_RICO          83
#define XONLINE_COUNTRY_PORTUGAL             84
#define XONLINE_COUNTRY_PARAGUAY             85
#define XONLINE_COUNTRY_QATAR                86
#define XONLINE_COUNTRY_ROMANIA              87
#define XONLINE_COUNTRY_RUSSIAN_FEDERATION   88
#define XONLINE_COUNTRY_SAUDI_ARABIA         89
#define XONLINE_COUNTRY_SWEDEN               90
#define XONLINE_COUNTRY_SINGAPORE            91
#define XONLINE_COUNTRY_SLOVENIA             92
#define XONLINE_COUNTRY_SLOVAK_REPUBLIC      93
#define XONLINE_COUNTRY_EL_SALVADOR          95
#define XONLINE_COUNTRY_SYRIA                96
#define XONLINE_COUNTRY_THAILAND             97
#define XONLINE_COUNTRY_TUNISIA              98
#define XONLINE_COUNTRY_TURKEY               99
#define XONLINE_COUNTRY_TRINIDAD_AND_TOBAGO  100
#define XONLINE_COUNTRY_TAIWAN               101
#define XONLINE_COUNTRY_UKRAINE              102
#define XONLINE_COUNTRY_UNITED_STATES        103
#define XONLINE_COUNTRY_URUGUAY              104
#define XONLINE_COUNTRY_UZBEKISTAN           105
#define XONLINE_COUNTRY_VENEZUELA            106
#define XONLINE_COUNTRY_VIET_NAM             107
#define XONLINE_COUNTRY_YEMEN                108
#define XONLINE_COUNTRY_SOUTH_AFRICA         109
#define XONLINE_COUNTRY_ZIMBABWE             110

// XUID compatibility macros
#define XOnlineAreUsersIdentical                        IsEqualXUID

//
// XOnline Error Codes
//

#define FACILITY_XONLINE                                21

// Generic errors
#define XONLINE_E_OVERFLOW                              _HRESULT_TYPEDEF_(0x80150001L)
#define XONLINE_E_NO_SESSION                            _HRESULT_TYPEDEF_(0x80150002L)
#define XONLINE_E_USER_NOT_LOGGED_ON                    _HRESULT_TYPEDEF_(0x80150003L)
#define XONLINE_E_NO_GUEST_ACCESS                       _HRESULT_TYPEDEF_(0x80150004L)
#define XONLINE_E_NOT_INITIALIZED                       _HRESULT_TYPEDEF_(0x80150005L)
#define XONLINE_E_NO_USER                               _HRESULT_TYPEDEF_(0x80150006L)
#define XONLINE_E_INTERNAL_ERROR                        _HRESULT_TYPEDEF_(0x80150007L)
#define XONLINE_E_OUT_OF_MEMORY                         _HRESULT_TYPEDEF_(0x80150008L)
#define XONLINE_E_TASK_BUSY                             _HRESULT_TYPEDEF_(0x80150009L)
#define XONLINE_E_SERVER_ERROR                          _HRESULT_TYPEDEF_(0x8015000AL)
#define XONLINE_E_IO_ERROR                              _HRESULT_TYPEDEF_(0x8015000BL)
#define XONLINE_E_USER_NOT_PRESENT                      _HRESULT_TYPEDEF_(0x8015000DL)
#define XONLINE_E_INVALID_REQUEST                       _HRESULT_TYPEDEF_(0x80150010L)
#define XONLINE_E_TASK_THROTTLED                        _HRESULT_TYPEDEF_(0x80150011L)
#define XONLINE_E_TASK_ABORTED_BY_DUPLICATE             _HRESULT_TYPEDEF_(0x80150012L)
#define XONLINE_E_INVALID_TITLE_ID                      _HRESULT_TYPEDEF_(0x80150013L)
#define XONLINE_E_SERVER_CONFIG_ERROR                   _HRESULT_TYPEDEF_(0x80150014L)
#define XONLINE_E_END_OF_STREAM                         _HRESULT_TYPEDEF_(0x80150015L)
// 0x80150016L is defined as XONLINE_E_ACCESS_DENIED
#define XONLINE_E_GEO_DENIED                            _HRESULT_TYPEDEF_(0x80150017L)

// Live connection state success codes
#define XONLINE_S_LOGON_CONNECTION_ESTABLISHED          _HRESULT_TYPEDEF_(0x001510F0L)
#define XONLINE_S_LOGON_DISCONNECTED                    _HRESULT_TYPEDEF_(0x001510F1L)

// Live connection state failure codes
#define XONLINE_E_LOGON_NO_NETWORK_CONNECTION           _HRESULT_TYPEDEF_(0x80151000L)
#define XONLINE_E_LOGON_CANNOT_ACCESS_SERVICE           _HRESULT_TYPEDEF_(0x80151001L)
#define XONLINE_E_LOGON_UPDATE_REQUIRED                 _HRESULT_TYPEDEF_(0x80151002L)
#define XONLINE_E_LOGON_SERVERS_TOO_BUSY                _HRESULT_TYPEDEF_(0x80151003L)
#define XONLINE_E_LOGON_CONNECTION_LOST                 _HRESULT_TYPEDEF_(0x80151004L)
#define XONLINE_E_LOGON_KICKED_BY_DUPLICATE_LOGON       _HRESULT_TYPEDEF_(0x80151005L)
#define XONLINE_E_LOGON_INVALID_USER                    _HRESULT_TYPEDEF_(0x80151006L)
#define XONLINE_E_LOGON_FLASH_UPDATE_REQUIRED           _HRESULT_TYPEDEF_(0x80151007L)
#define XONLINE_E_LOGON_SERVICE_NOT_REQUESTED           _HRESULT_TYPEDEF_(0x80151100L)
#define XONLINE_E_LOGON_SERVICE_NOT_AUTHORIZED          _HRESULT_TYPEDEF_(0x80151101L)
#define XONLINE_E_LOGON_SERVICE_TEMPORARILY_UNAVAILABLE _HRESULT_TYPEDEF_(0x80151102L)


//  Errors returned by matchmaking                      = 0x801551XX
#define XONLINE_E_MATCH_INVALID_SESSION_ID              _HRESULT_TYPEDEF_(0x80155100L)  // specified session id does not exist
#define XONLINE_E_MATCH_INVALID_TITLE_ID                _HRESULT_TYPEDEF_(0x80155101L)  // specified title id is zero, or does not exist
#define XONLINE_E_MATCH_INVALID_DATA_TYPE               _HRESULT_TYPEDEF_(0x80155102L)  // attribute ID or parameter type specifies an invalid data type
#define XONLINE_E_MATCH_REQUEST_TOO_SMALL               _HRESULT_TYPEDEF_(0x80155103L)  // the request did not meet the minimum length for a valid request
#define XONLINE_E_MATCH_REQUEST_TRUNCATED               _HRESULT_TYPEDEF_(0x80155104L)  // the self described length is greater than the actual buffer size
#define XONLINE_E_MATCH_INVALID_SEARCH_REQ              _HRESULT_TYPEDEF_(0x80155105L)  // the search request was invalid
#define XONLINE_E_MATCH_INVALID_OFFSET                  _HRESULT_TYPEDEF_(0x80155106L)  // one of the attribute/parameter offsets in the request was invalid.  Will be followed by the zero based offset number.
#define XONLINE_E_MATCH_INVALID_ATTR_TYPE               _HRESULT_TYPEDEF_(0x80155107L)  // the attribute type was something other than user or session
#define XONLINE_E_MATCH_INVALID_VERSION                 _HRESULT_TYPEDEF_(0x80155108L)  // bad protocol version in request
#define XONLINE_E_MATCH_OVERFLOW                        _HRESULT_TYPEDEF_(0x80155109L)  // an attribute or parameter flowed past the end of the request
#define XONLINE_E_MATCH_INVALID_RESULT_COL              _HRESULT_TYPEDEF_(0x8015510AL)  // referenced stored procedure returned a column with an unsupported data type
#define XONLINE_E_MATCH_INVALID_STRING                  _HRESULT_TYPEDEF_(0x8015510BL)  // string with length-prefix of zero, or string with no terminating null
#define XONLINE_E_MATCH_STRING_TOO_LONG                 _HRESULT_TYPEDEF_(0x8015510CL)  // string exceeded 400 characters
#define XONLINE_E_MATCH_BLOB_TOO_LONG                   _HRESULT_TYPEDEF_(0x8015510DL)  // blob exceeded 800 bytes
#define XONLINE_E_MATCH_INVALID_ATTRIBUTE_ID            _HRESULT_TYPEDEF_(0x80155110L)  // attribute id is invalid
#define XONLINE_E_MATCH_SESSION_ALREADY_EXISTS          _HRESULT_TYPEDEF_(0x80155112L)  // session id already exists in the db
#define XONLINE_E_MATCH_CRITICAL_DB_ERR                 _HRESULT_TYPEDEF_(0x80155115L)  // critical error in db
#define XONLINE_E_MATCH_NOT_ENOUGH_COLUMNS              _HRESULT_TYPEDEF_(0x80155116L)  // search result set had too few columns
#define XONLINE_E_MATCH_PERMISSION_DENIED               _HRESULT_TYPEDEF_(0x80155117L)  // incorrect permissions set on search sp
#define XONLINE_E_MATCH_INVALID_PART_SCHEME             _HRESULT_TYPEDEF_(0x80155118L)  // title specified an invalid partitioning scheme
#define XONLINE_E_MATCH_INVALID_PARAM                   _HRESULT_TYPEDEF_(0x80155119L)  // bad parameter passed to sp
#define XONLINE_E_MATCH_DATA_TYPE_MISMATCH              _HRESULT_TYPEDEF_(0x8015511DL)  // data type specified in attr id did not match type of attr being set
#define XONLINE_E_MATCH_SERVER_ERROR                    _HRESULT_TYPEDEF_(0x8015511EL)  // error on server not correctable by client
#define XONLINE_E_MATCH_NO_USERS                        _HRESULT_TYPEDEF_(0x8015511FL)  // no authenticated users in search request.
#define XONLINE_E_MATCH_INVALID_BLOB                    _HRESULT_TYPEDEF_(0x80155120L)  // invalid blob attribute
#define XONLINE_E_MATCH_TOO_MANY_USERS                  _HRESULT_TYPEDEF_(0x80155121L)  // too many users in search request
#define XONLINE_E_MATCH_INVALID_FLAGS                   _HRESULT_TYPEDEF_(0x80155122L)  // invalid flags were specified in a search request
#define XONLINE_E_MATCH_PARAM_MISSING                   _HRESULT_TYPEDEF_(0x80155123L)  // required parameter not passed to sp
#define XONLINE_E_MATCH_TOO_MANY_PARAM                  _HRESULT_TYPEDEF_(0x80155124L)  // too many paramters passed to sp or in request structure
#define XONLINE_E_MATCH_DUPLICATE_PARAM                 _HRESULT_TYPEDEF_(0x80155125L)  // a paramter was passed to twice to a search procedure
#define XONLINE_E_MATCH_TOO_MANY_ATTR                   _HRESULT_TYPEDEF_(0x80155126L)  // too many attributes in the request structure


XBOXAPI
DWORD
WINAPI
XUserMuteListQuery(
    DWORD       dwUserIndex,
    XUID        XuidRemoteTalker,
    BOOL        *pfOnMuteList
    );

#define X_ATTRIBUTE_DATATYPE_NULL                        0x00F00000
#define X_ATTRIBUTE_ID_MASK                              0x0000FFFF
#define X_ATTRIBUTE_SCOPE_TITLE_SPECIFIC                 0x00000000
#define STRING_MAX_RESULTS                               100
#define MAX_STRINGSVR_STRING_LEN                         512
#define MAX_RICHPRESENCE_SIZE                            64
#define PQUEUE_TRANSIENT_MSGS                            5
#define PQUEUE_INVALID                                   8
#define PLIST_BUDDY_NOP                                  0
#define PLIST_BUDDY_ADD                                  1
#define PLIST_BUDDY_ADDED                                2
#define PLIST_BUDDY_ACCEPT                               3
#define PLIST_BUDDY_REJECT                               4
#define PLIST_BUDDY_DELETE                               5
#define MAX_PEER_SUBSCRIPTIONS                           1000
#define XHTTP_REQUEST_MAX_HOST                           512
#define XHTTP_REQUEST_MAX_URL                            512
#define XHTTP_REQUEST_MAX_EXTRA_HEADERS                  256
#define XHTTP_REQUEST_TYPE_GET                           0x0000000
#define XHTTP_REQUEST_TYPE_POST                          0x0000001
#define XHTTP_REQUEST_TYPE_MASK                          0x0000001
#define XPRESENCE_MAX_TITLE_SUBS                         400
#define XPRESENCE_MAX_SYS_SUBS                           400
#define XPRESENCE_MIN_SYS_SUBS_PER_USER                  100
#define XPRESENCE_SYNC_SUBS_FLAG_CHANGELIST              0x00000001
#define MAX_FIRSTNAME_SIZE                               64
#define MAX_LASTNAME_SIZE                                64
#define MAX_EMAIL_SIZE                                   129
#define MAX_STREET_SIZE                                  128
#define MAX_CITY_SIZE                                    64
#define MAX_DISTRICT_SIZE                                64
#define MAX_STATE_SIZE                                   64
#define MAX_COUNTRYCODE_SIZE                             2
#define MAX_POSTALCODE_SIZE                              16
#define MAX_CC_TYPE_SIZE                                 32
#define MAX_CC_EXPIRATION_SIZE                           6
#define ACCOUNT_PIN_LENGTH                               4
#define VOUCHER_LENGTH                                   25
#define MAX_VOUCHER_SIZE                                 VOUCHER_LENGTH+1
#define MAX_DASH_LANGUAGE_ID                             9
#define XONLINE_PASSPORT_PASSWORD_MAX_LEN                32
#define XONLINE_PASSPORT_SECRET_ANSWER_MIN_LEN           5
#define XONLINE_PASSPORT_SECRET_ANSWER_MAX_LEN           64
#define XONLINE_PASSPORT_SESSION_TOKEN_LEN               28
#define XONLINE_PASSPORT_PUBLIC_KEY_DIGEST_LEN           20
#define XONLINE_PASSPORT_LOGIN_NONCE_MIN_LEN             32
#define XONLINE_PASSPORT_LOGIN_LEGACY_SERVICE_ID         0
#define XONLINE_XBOS_MAX_TITLE_CATEGORY_LENGTH           60
#define XONLINE_ASSET_SIGNATURE_SIZE                     256
#define XMARKETPLACE_MAX_ASSETS_CONSUMED                 100
#define XACTIVATION_SIGNATURE_SIZE                       256
#define XONLINE_QUERY_MAX_PAGE                           32
#define XONLINE_QUERY_MAX_PAGE_SIZE                      32
#define XONLINE_MAX_STATS_RATING_COUNT                   101
#define XUSER_PRIVATE_DATA_TYPE_INT32                    1
#define XUSER_PRIVATE_DATA_TYPE_INT64                    2
#define XUSER_PRIVATE_DATA_TYPE_DOUBLE                   3
#define XUSER_PRIVATE_DATA_TYPE_FLOAT                    5
#define XCONTENT_PATH_MAX_SIZE                           256
#define XMSG_MAX_RECIPIENTS                              100
#define XMSG_MAX_GAMERTAG_LENGTH                         15
#define XMSG_MAX_SUBJECT_SIZE                            20
#define XMSG_DELETE_MESSAGE_FLAG_BLOCK_SENDER            0x00000001
#define MAX_AFFILIATES_ADD                               16
#define X_AFFILIATE_ENCOUNTERED_INDEX                    0
#define X_AFFILIATE_COMPLETED_GAME_INDEX                 1
#define X_AFFILIATE_POSITIVE_FEEDBACK_INDEX              2
#define X_AFFILIATE_NEGATIVE_FEEDBACK_INDEX              3
#define X_AFFILIATE_AVOIDING_ME_INDEX                    4
#define NUM_STORED_AFFILIATE_LISTS                       5
#define X_AFFILIATE_FRIEND_INDEX                         16
#define X_AFFILIATE_BLOCK_INDEX                          17
#define X_AFFILIATE_MUTE_INDEX                           18
#define X_AFFILIATE_INDEX_ERROR                          0xFFFFFFFF
#define X_AFFILIATE_FLAGS_IN_USE                         0x0007001F
#define X_ADD_AFFILIATE_MAX                              16
#define XONLINE_SIGNATURE_DIGEST_SIZE                    20
#define XSIGNATURE_CONSOLE_ID_LEN                        5
#define XSIGNATURE_USER_PUIDS                            4
#define XSIGNATURE_DIGEST_LEN                            20
#define RSAPUB_2048_SIZE                                 272
#define XONLINE_MAX_PATHNAME_LENGTH                      255
#define XSTORAGE_MAX_MEMORY_BUFFER_SIZE                  100000000
#define XSTORAGE_CONTENT_TYPE_PACKAGE                    0
#define XSTORAGE_CONTENT_TYPE_BLOB                       1
#define XSTORAGE_COMPRESSION_TYPE_NONE                   0
#define XSTORAGE_ACCESS_TOKEN_VERSION                    1
#define XSTORAGE_OPERATION_UPLOAD                        1
#define XSTORAGE_OPERATION_DOWNLOAD                      2
#define XSTORAGE_OPERATION_DELETEFILE                    3
#define XSTORAGE_OPERATION_ENUMERATE                     4
#define XSTORAGE_MAX_RESULTS_TO_RETURN                   256
#define XSTORAGE_DOWNLOAD_TO_MEMORY_EXTRA_OBJECT_SIZE    448
#define XSTORAGE_UPLOAD_FROM_MEMORY_EXTRA_OBJECT_SIZE    48
#define XSTORAGE_ENUMERATE_EXTRA_OBJECT_SIZE             48
#define XSTORAGE_DELETE_EXTRA_OBJECT_SIZE                48
#define XINVITE_SEND_MESSAGE_EXTRA_OBJECT_SIZE           1500
#define XCONTENT_REFERRAL_SYM_KEY_SIZE                   16
#define XCONTENT_REFERRAL_PUB_KEY_SIZE                   284
#define XCONTENT_DOWNLOAD_NO_NOTIFICATION                0x00000001
#define XCONTENT_DOWNLOAD_NO_UIPOPUP                     0x00000002
#define XCONTENT_DOWNLOAD_UPDATE_REDIRECT                0x00000004
#define REVOCATION_LIST_CLIENT_NONCE_SIZE                16
#define REVOCATION_LIST_SIGNATURE_SIZE                   256
#define REVOCATION_LIST_SERVER_NONCE_SIZE                16
#define REVOCATION_LIST_ENTRY_DIGEST_SIZE                20
#define XWMDRM_DEVICE_PUBLIC_KEY                         40
#define XARB_PROTOCOL_VERSION                            1
#define FB_REVIEW_PREFER                                 0
#define FB_REVIEW_AVOID_TRASH_TALK                       1
#define FB_REVIEW_AVOID_LANGUAGE                         2
#define FB_REVIEW_AVOID_DISRUPTIVE                       3
#define FB_REVIEW_AVOID_AGGRESSIVE                       4
#define FB_REVIEW_AVOID_UNSPORTING                       5
#define FB_REVIEW_AVOID_DISCONNECT                       6
#define FB_REVIEW_AVOID_UNSKILLED                        7
#define FB_REVIEW_AVOID_TOO_GOOD                         8
#define FB_REVIEW_AVOID_UNFAMILIAR                       9
#define FB_COMPLAINT_OFFENSIVE_GAMERTAG                  0
#define FB_COMPLAINT_OFFENSIVE_MOTTO                     1
#define FB_COMPLAINT_OFFENSIVE_TEXT                      2
#define FB_COMPLAINT_OFFENSIVE_VOICE_MAIL                3
#define FB_COMPLAINT_OFFENSIVE_VOICE_CHAT                4
#define FB_COMPLAINT_OFFENSIVE_IN_GAME                   5
#define FB_COMPLAINT_TAMPERING_FEEDBACK                  6
#define FB_COMPLAINT_TAMPERING_SYSTEM                    7
#define FB_COMPLAINT_TAMPERING_CHEATING                  8
#define FB_COMPLAINT_OFFENSIVE_CONTENT                   9
#define FB_COMPLAINT_OFFENSIVE_VIDEOMESSAGE              10
#define FB_COMPLAINT_OFFENSIVE_VIDEOCHAT                 11
#define FB_COMPLAINT_OFFENSIVE_GAMERPICTURE              12
#define FB_COMPLAINT_OFFENSIVE_INGAME_VIDEO              13
#define FB_COMPLAINT_OFFENSIVE_PHOTOMESSAGE              14
#define FB_COMPLAINT_MAX_TYPE                            15


//
// Friends
//

#define XONLINE_FRIENDSTATE_FLAG_NONE                   0x00000000
#define XONLINE_FRIENDSTATE_FLAG_ONLINE                 0x00000001
#define XONLINE_FRIENDSTATE_FLAG_PLAYING                0x00000002
#define XONLINE_FRIENDSTATE_FLAG_VOICE                  0x00000008
#define XONLINE_FRIENDSTATE_FLAG_JOINABLE               0x00000010
#define XONLINE_FRIENDSTATE_MASK_GUESTS                 0x00000060
#define XONLINE_FRIENDSTATE_FLAG_RESERVED0              0x00000080
#define XONLINE_FRIENDSTATE_FLAG_JOINABLE_FRIENDS_ONLY  0x00000100
#define XONLINE_FRIENDSTATE_FLAG_SENTINVITE             0x04000000
#define XONLINE_FRIENDSTATE_FLAG_RECEIVEDINVITE         0x08000000
#define XONLINE_FRIENDSTATE_FLAG_INVITEACCEPTED         0x10000000
#define XONLINE_FRIENDSTATE_FLAG_INVITEREJECTED         0x20000000
#define XONLINE_FRIENDSTATE_FLAG_SENTREQUEST            0x40000000
#define XONLINE_FRIENDSTATE_FLAG_RECEIVEDREQUEST        0x80000000

#define XONLINE_FRIENDSTATE_ENUM_ONLINE            0x00000000
#define XONLINE_FRIENDSTATE_ENUM_AWAY              0x00010000
#define XONLINE_FRIENDSTATE_ENUM_BUSY              0x00020000
#define XONLINE_FRIENDSTATE_MASK_USER_STATE        0x000F0000
#define XONLINE_FRIENDSTATE_ENUM_CONSOLE_XBOX1     0x00000000
#define XONLINE_FRIENDSTATE_ENUM_CONSOLE_XBOX360   0x00001000
#define XONLINE_FRIENDSTATE_ENUM_CONSOLE_WINPC     0x00002000
#define XONLINE_FRIENDSTATE_MASK_CONSOLE_TYPE      0x00007000

#define XOnlineIsUserAway(dwState) ((dwState & XONLINE_FRIENDSTATE_FLAG_ONLINE) && \
                                    ((dwState & XONLINE_FRIENDSTATE_MASK_USER_STATE) == \
                                    XONLINE_FRIENDSTATE_ENUM_AWAY))

#define XOnlineIsUserBusy(dwState) ((dwState & XONLINE_FRIENDSTATE_FLAG_ONLINE) && \
                                    ((dwState & XONLINE_FRIENDSTATE_MASK_USER_STATE) == \
                                    XONLINE_FRIENDSTATE_ENUM_BUSY))

#define XOnlineGetGuests(dwState) ((dwState & XONLINE_FRIENDSTATE_MASK_GUESTS) >> 5)

#define MAX_FRIENDS                             100

#pragma pack(push, 1)

typedef struct _XONLINE_FRIEND
{
    XUID                    xuid;
    CHAR                    szGamertag[XUSER_NAME_SIZE];
    DWORD                   dwFriendState;
    XNKID                   sessionID;
    DWORD                   dwTitleID;
    FILETIME                ftUserTime;
    XNKID                   xnkidInvite;
    FILETIME                gameinviteTime;
    DWORD                   cchRichPresence;
    WCHAR                   wszRichPresence[MAX_RICHPRESENCE_SIZE];

} XONLINE_FRIEND, *PXONLINE_FRIEND;

#define MAX_PRESENCE                100


typedef struct _XONLINE_PRESENCE
{
    XUID                    xuid;
    DWORD                   dwState;
    XNKID                   sessionID;
    DWORD                   dwTitleID;
    FILETIME                ftUserTime;
    DWORD                   cchRichPresence;
    WCHAR                   wszRichPresence[MAX_RICHPRESENCE_SIZE];
} XONLINE_PRESENCE, *PXONLINE_PRESENCE;

#pragma pack(pop)


//
// Storage facilities
//
typedef enum _XSTORAGE_FACILITY
{
    XSTORAGE_FACILITY_GAME_CLIP      = 1,
    XSTORAGE_FACILITY_PER_TITLE      = 2,
    XSTORAGE_FACILITY_PER_USER_TITLE = 3,
} XSTORAGE_FACILITY;

typedef struct _XSTORAGE_FACILITY_INFO_GAME_CLIP
{
    DWORD   dwLeaderboardID;
} XSTORAGE_FACILITY_INFO_GAME_CLIP;


// Errors returned by Marketplace offer APIs            = 0x801530XX + 0x801531XX
#define XONLINE_E_OFFERING_INVALID_CONSUME_ITEMS        _HRESULT_TYPEDEF_(0x80153013L)


//  Errors returned by session APIs                     = 0x801552XX
#define XONLINE_E_SESSION_NOT_FOUND                     _HRESULT_TYPEDEF_(0x80155200L)  // specified session id does not exist
#define XONLINE_E_SESSION_INSUFFICIENT_PRIVILEGES       _HRESULT_TYPEDEF_(0x80155201L)  // The requester does not have permissions to perform this operation
#define XONLINE_E_SESSION_FULL                          _HRESULT_TYPEDEF_(0x80155202L)  // The session is full, and the join operation failed, or joining is disallowe
#define XONLINE_E_SESSION_INVITES_DISABLED              _HRESULT_TYPEDEF_(0x80155203L)  // Invites have been disabled for this session
#define XONLINE_E_SESSION_INVALID_FLAGS                 _HRESULT_TYPEDEF_(0x80155204L)  // Invalid flags passed to XSessionCreate
#define XONLINE_E_SESSION_REQUIRES_ARBITRATION          _HRESULT_TYPEDEF_(0x80155205L)  // The Session owner has the GAME_TYPE context set to ranked, but the session is not arbitrated
#define XONLINE_E_SESSION_WRONG_STATE                   _HRESULT_TYPEDEF_(0x80155206L)  // The session is in the wrong state for the requested operation to be performed
#define XONLINE_E_SESSION_INSUFFICIENT_BUFFER           _HRESULT_TYPEDEF_(0x80155207L)  // Ran out of memory attempting to process search results
#define XONLINE_E_SESSION_REGISTRATION_ERROR            _HRESULT_TYPEDEF_(0x80155208L)  // Could not perform arbitration registration because some logged on users have not joined the session
#define XONLINE_E_SESSION_NOT_LOGGED_ON                 _HRESULT_TYPEDEF_(0x80155209L)  // User is not logged on to Live but attempted to create a session using Live features.
#define XONLINE_E_SESSION_JOIN_ILLEGAL                  _HRESULT_TYPEDEF_(0x8015520AL)  // User attempted to join a USES_PRESENCE session when the user is already in a USES_PRESENCE session on the console. Can only have 1 at a time.
#define XONLINE_E_SESSION_CREATE_KEY_FAILED             _HRESULT_TYPEDEF_(0x8015520BL)  // Key creation failed during session creation.
#define XONLINE_E_SESSION_NOT_REGISTERED                _HRESULT_TYPEDEF_(0x8015520CL)  // Can not start the session if registration has not completed
#define XONLINE_E_SESSION_REGISTER_KEY_FAILED           _HRESULT_TYPEDEF_(0x8015520DL)  // Key registration failed during session creation.
#define XONLINE_E_SESSION_UNREGISTER_KEY_FAILED         _HRESULT_TYPEDEF_(0x8015520EL)  // Key registration failed during session creation.


// Errors returned by Query service                     = 0x801561XX
#define XONLINE_E_QUERY_QUOTA_FULL                      _HRESULT_TYPEDEF_(0x80156101L)  // this user or team's quota for the dataset is full.  you must remove an entity first.
#define XONLINE_E_QUERY_ENTITY_NOT_FOUND                _HRESULT_TYPEDEF_(0x80156102L)  // the requested entity didn't exist in the provided dataset.
#define XONLINE_E_QUERY_PERMISSION_DENIED               _HRESULT_TYPEDEF_(0x80156103L)  // the user tried to update or delete an entity that he didn't own.
#define XONLINE_E_QUERY_ATTRIBUTE_TOO_LONG              _HRESULT_TYPEDEF_(0x80156104L)  // attribute passed exceeds schema definition
#define XONLINE_E_QUERY_UNEXPECTED_ATTRIBUTE            _HRESULT_TYPEDEF_(0x80156105L)  // attribute passed was a bad param for the database operation
#define XONLINE_E_QUERY_INVALID_ACTION                  _HRESULT_TYPEDEF_(0x80156107L)  // the specified action (or dataset) doesn't have a select action associated with it.
#define XONLINE_E_QUERY_SPEC_COUNT_MISMATCH             _HRESULT_TYPEDEF_(0x80156108L)  // the provided number of QUERY_ATTRIBUTE_SPECs doesn't match the number returned by the procedure
#define XONLINE_E_QUERY_DATASET_NOT_FOUND               _HRESULT_TYPEDEF_(0x80156109L)  // The specified dataset id was not found.
#define XONLINE_E_QUERY_PROCEDURE_NOT_FOUND             _HRESULT_TYPEDEF_(0x8015610AL)  // The specified proc index was not found.


// Errors returned by Competitions service              = 0x801562XX
#define XONLINE_E_COMP_ACCESS_DENIED                    _HRESULT_TYPEDEF_(0x80156202L)  // The specified source (client) is not permitted to execute this method
#define XONLINE_E_COMP_REGISTRATION_CLOSED              _HRESULT_TYPEDEF_(0x80156203L)  // The competition is closed to registration
#define XONLINE_E_COMP_FULL                             _HRESULT_TYPEDEF_(0x80156204L)  // The competition has reached it's max enrollment
#define XONLINE_E_COMP_NOT_REGISTERED                   _HRESULT_TYPEDEF_(0x80156205L)  // The user or team isn't registered for the competition
#define XONLINE_E_COMP_CANCELLED                        _HRESULT_TYPEDEF_(0x80156206L)  // The competition has been cancelled, and the operation is invalid.
#define XONLINE_E_COMP_CHECKIN_TIME_INVALID             _HRESULT_TYPEDEF_(0x80156207L)  // The user is attempting to checkin to an event outside the allowed time.
#define XONLINE_E_COMP_CHECKIN_BAD_EVENT                _HRESULT_TYPEDEF_(0x80156208L)  // The user is attempting to checkin to an event in which they are not a valid participant.
#define XONLINE_E_COMP_EVENT_SCORED                     _HRESULT_TYPEDEF_(0x80156209L)  // The user is attempting to checkin to an event which has already been scored by the service (user has forfeited or been ejected)
#define XONLINE_S_COMP_EVENT_SCORED                     _HRESULT_TYPEDEF_(0x00156209L)  // The user is attempting to checkin to an event but the users event has been updated. Re-query for a new event
#define XONLINE_E_COMP_UNEXPECTED                       _HRESULT_TYPEDEF_(0x80156210L)  // Results from the Database are unexpected or inconsistent with the current operation.
#define XONLINE_E_COMP_TOPOLOGY_ERROR                   _HRESULT_TYPEDEF_(0x80156216L)  // The topology request cannot be fulfilled by the server
#define XONLINE_E_COMP_TOPOLOGY_PENDING                 _HRESULT_TYPEDEF_(0x80156217L)  // The topology request has not completed yet
#define XONLINE_E_COMP_CHECKIN_TOO_EARLY                _HRESULT_TYPEDEF_(0x80156218L)  // The user is attempting to checkin to an event before the allowed time.
#define XONLINE_E_COMP_ALREADY_REGISTERED               _HRESULT_TYPEDEF_(0x80156219L)  // The user has already registered for this competition.
#define XONLINE_E_COMP_INVALID_ENTRANT_TYPE             _HRESULT_TYPEDEF_(0x8015621AL)  // dwTeamId was non-0 for a user competition, or dwTeamId was 0 for a team competition
#define XONLINE_E_COMP_TOO_LATE                         _HRESULT_TYPEDEF_(0x8015621BL)  // The time allotted for performing the requested action has already passed
#define XONLINE_E_COMP_TOO_EARLY                        _HRESULT_TYPEDEF_(0x8015621CL)  // The specified action cannot yet be performed
#define XONLINE_E_COMP_NO_BYES_AVAILABLE                _HRESULT_TYPEDEF_(0x8015621DL)  // No bytes remain to be granted
#define XONLINE_E_COMP_SERVICE_OUTAGE                   _HRESULT_TYPEDEF_(0x8015621EL)  // A service outage has occurred, try again in a bit

// Errors returned by the v1 Message Service            = 0x801570XX
#define XONLINE_E_MSGSVR_INVALID_REQUEST                _HRESULT_TYPEDEF_(0x80157001L)  // an invalid request type was received

// Errors returned by the String Service                = 0x801571XX
#define XONLINE_E_STRING_TOO_LONG                       _HRESULT_TYPEDEF_(0x80157101L)  // the string was longer than the allowed maximum
#define XONLINE_E_STRING_OFFENSIVE_TEXT                 _HRESULT_TYPEDEF_(0x80157102L)  // the string contains offensive text
#define XONLINE_E_STRING_NO_DEFAULT_STRING              _HRESULT_TYPEDEF_(0x80157103L)  // returned by AddString when no string of the language specified as the default is found
#define XONLINE_E_STRING_INVALID_LANGUAGE               _HRESULT_TYPEDEF_(0x80157104L)  // returned by AddString when an invalid language is specified for a string

// Errors returned by the Feedback Service              = 0x801580XX
#define XONLINE_E_FEEDBACK_NULL_TARGET                  _HRESULT_TYPEDEF_(0x80158001L)  // target PUID of feedback is NULL
#define XONLINE_E_FEEDBACK_BAD_TYPE                     _HRESULT_TYPEDEF_(0x80158002L)  // bad feedback type
#define XONLINE_E_FEEDBACK_CANNOT_LOG                   _HRESULT_TYPEDEF_(0x80158006L)  // cannot write to feedback log

// Errors returned by the Statistics Service            = 0x80159XXX
#define XONLINE_E_STAT_BAD_REQUEST                      _HRESULT_TYPEDEF_(0x80159001L)  // server received incorrectly formatted request.
#define XONLINE_E_STAT_INVALID_TITLE_OR_LEADERBOARD     _HRESULT_TYPEDEF_(0x80159002L)  // title or leaderboard id were not recognized by the server.
#define XONLINE_E_STAT_TOO_MANY_SPECS                   _HRESULT_TYPEDEF_(0x80159004L)  // too many stat specs in a request.
#define XONLINE_E_STAT_TOO_MANY_STATS                   _HRESULT_TYPEDEF_(0x80159005L)  // too many stats in a spec or already stored for the user.
#define XONLINE_E_STAT_USER_NOT_FOUND                   _HRESULT_TYPEDEF_(0x80159003L)  // user not found.
#define XONLINE_E_STAT_SET_FAILED_0                     _HRESULT_TYPEDEF_(0x80159100L)  // set operation failed on spec index 0
#define XONLINE_E_STAT_PERMISSION_DENIED                _HRESULT_TYPEDEF_(0x80159200L)  // operation failed because of credentials. UserId is not logged in or this operation is not supported in production (e.g. userId=0 in XOnlineStatReset)
#define XONLINE_E_STAT_LEADERBOARD_WAS_RESET            _HRESULT_TYPEDEF_(0x80159201L)  // operation failed because user was logged on before the leaderboard was reset.
#define XONLINE_E_STAT_INVALID_ATTACHMENT               _HRESULT_TYPEDEF_(0x80159202L)  // attachment is invalid.
#define XONLINE_S_STAT_CAN_UPLOAD_ATTACHMENT            _HRESULT_TYPEDEF_(0x00159203L)  // Use XOnlineStatWriteGetResults to get a handle to upload a attachment.
#define XONLINE_E_STAT_TOO_MANY_PARAMETERS              _HRESULT_TYPEDEF_(0x80159204L)
#define XONLINE_E_STAT_TOO_MANY_PROCEDURES              _HRESULT_TYPEDEF_(0x80159205L)
#define XONLINE_E_STAT_STAT_POST_PROC_ERROR             _HRESULT_TYPEDEF_(0x80159206L)
#define XONLINE_E_STAT_NOT_ENOUGH_PARAMETERS            _HRESULT_TYPEDEF_(0x80159208L)
#define XONLINE_E_STAT_INVALID_PROCEDURE                _HRESULT_TYPEDEF_(0x80159209L)
#define XONLINE_E_STAT_EXCEEDED_WRITE_READ_LIMIT        _HRESULT_TYPEDEF_(0x8015920AL)
#define XONLINE_E_STAT_LEADERBOARD_READONLY             _HRESULT_TYPEDEF_(0x8015920BL)
#define XONLINE_E_STAT_MUSIGMA_ARITHMETIC_OVERFLOW      _HRESULT_TYPEDEF_(0x8015920CL)
#define XONLINE_E_STAT_READ_NO_SPEC                     _HRESULT_TYPEDEF_(0x8015920DL)
#define XONLINE_E_STAT_MUSIGMA_NO_GAME_MODE             _HRESULT_TYPEDEF_(0x8015920EL)  // no game mode found for this leaderboard

//  Errors returned by xsuppapi service                 = 0x8015A0XX

// Errors returned by Signature Service                 = 0x8015B0XX
#define XONLINE_E_SIGNATURE_VER_INVALID_SIGNATURE       _HRESULT_TYPEDEF_(0x8015B001L)  // presented signature does not match
#define XONLINE_E_SIGNATURE_VER_UNKNOWN_KEY_VER         _HRESULT_TYPEDEF_(0x8015B002L)  // signature key version specified is not found among the valid signature keys
#define XONLINE_E_SIGNATURE_VER_UNKNOWN_SIGNATURE_VER   _HRESULT_TYPEDEF_(0x8015B003L)  // signature version is unknown, currently only version 1 is supported
#define XONLINE_E_SIGNATURE_BANNED_XBOX                 _HRESULT_TYPEDEF_(0x8015B004L)  // signature is not calculated or revoked because Xbox is banned
#define XONLINE_E_SIGNATURE_BANNED_USER                 _HRESULT_TYPEDEF_(0x8015B005L)  // signature is not calculated or revoked because at least one user is banned
#define XONLINE_E_SIGNATURE_BANNED_TITLE                _HRESULT_TYPEDEF_(0x8015B006L)  // signature is not calculated or revoked because the given title and version is banned
#define XONLINE_E_SIGNATURE_BANNED_DIGEST               _HRESULT_TYPEDEF_(0x8015B007L)  // signature is not calculated or revoked because the digest is banned
#define XONLINE_E_SIGNATURE_GET_BAD_AUTH_DATA           _HRESULT_TYPEDEF_(0x8015B008L)  // fail to retrieve AuthData from SG, returned by GetSigningKey api
#define XONLINE_E_SIGNATURE_SERVICE_UNAVAILABLE         _HRESULT_TYPEDEF_(0x8015B009L)  // fail to retrieve a signature server master key, returned by GetSigningKey or SignOnBehalf api

// Errors returned by Arbitration Service                          = 0x8015B1XX
#define XONLINE_E_ARBITRATION_SERVICE_UNAVAILABLE                  _HRESULT_TYPEDEF_(0x8015B101L)   // Service temporarily unavailable
#define XONLINE_E_ARBITRATION_INVALID_REQUEST                      _HRESULT_TYPEDEF_(0x8015B102L)   // The request is invalidly formatted
#define XONLINE_E_ARBITRATION_SESSION_NOT_FOUND                    _HRESULT_TYPEDEF_(0x8015B103L)   // The session is not found or has expired
#define XONLINE_E_ARBITRATION_REGISTRATION_FLAGS_MISMATCH          _HRESULT_TYPEDEF_(0x8015B104L)   // The session was registered with different flags by another Xbox
#define XONLINE_E_ARBITRATION_REGISTRATION_SESSION_TIME_MISMATCH   _HRESULT_TYPEDEF_(0x8015B105L)   // The session was registered with a different session time by another Xbox
#define XONLINE_E_ARBITRATION_REGISTRATION_TOO_LATE                _HRESULT_TYPEDEF_(0x8015B106L)   // Registration came too late, the session has already been arbitrated
#define XONLINE_E_ARBITRATION_NEED_TO_REGISTER_FIRST               _HRESULT_TYPEDEF_(0x8015B107L)   // Must register in seesion first, before any other activity
#define XONLINE_E_ARBITRATION_TIME_EXTENSION_NOT_ALLOWED           _HRESULT_TYPEDEF_(0x8015B108L)   // Time extension of this session not allowed, or session is already arbitrated
#define XONLINE_E_ARBITRATION_INCONSISTENT_FLAGS                   _HRESULT_TYPEDEF_(0x8015B109L)   // Inconsistent flags are used in the request
#define XONLINE_E_ARBITRATION_INCONSISTENT_COMPETITION_STATUS      _HRESULT_TYPEDEF_(0x8015B10AL)   // Whether the session is a competition is inconsistent between registration and report
#define XONLINE_E_ARBITRATION_REPORT_ALREADY_CALLED                _HRESULT_TYPEDEF_(0x8015b10BL)   // Report call for this session already made by this client
#define XONLINE_E_ARBITRATION_TOO_MANY_XBOXES_IN_SESSION           _HRESULT_TYPEDEF_(0x8015b10CL)   // Only up to 255 Xboxes can register in a session
#define XONLINE_E_ARBITRATION_1_XBOX_1_USER_SESSION_NOT_ALLOWED    _HRESULT_TYPEDEF_(0x8015b10DL)   // Single Xbox single user sessions should not be arbitrated
#define XONLINE_E_ARBITRATION_REPORT_TOO_LARGE                     _HRESULT_TYPEDEF_(0x8015b10EL)   // The stats or query submission is too large
#define XONLINE_E_ARBITRATION_INVALID_TEAMTICKET                   _HRESULT_TYPEDEF_(0x8015b10FL)   // An invalid team ticket was submitted
// Arbitration success HRESULTS
#define XONLINE_S_ARBITRATION_INVALID_XBOX_SPECIFIED               _HRESULT_TYPEDEF_(0x0015b1F0L)   // Invalid/duplicate Xbox specified in lost connectivity or suspicious info. Never the less, this report is accepted
#define XONLINE_S_ARBITRATION_INVALID_USER_SPECIFIED               _HRESULT_TYPEDEF_(0x0015b1F1L)   // Invalid/duplicate user specified in lost connectivity or suspicious info. Never the less, this report is accepted
#define XONLINE_S_ARBITRATION_DIFFERENT_RESULTS_DETECTED           _HRESULT_TYPEDEF_(0x0015b1F2L)   // Differing result submissions have been detected in this session. Never the less, this report submission is accepted

// Errors returned by the Storage services              = 0x8015C0XX
#define XONLINE_E_STORAGE_INVALID_REQUEST               _HRESULT_TYPEDEF_(0x8015c001L)  // Request is invalid
#define XONLINE_E_STORAGE_ACCESS_DENIED                 _HRESULT_TYPEDEF_(0x8015c002L)  // Client doesn't have the rights to upload the file
#define XONLINE_E_STORAGE_FILE_IS_TOO_BIG               _HRESULT_TYPEDEF_(0x8015c003L)  // File is too big
#define XONLINE_E_STORAGE_FILE_NOT_FOUND                _HRESULT_TYPEDEF_(0x8015c004L)  // File not found
#define XONLINE_E_STORAGE_INVALID_ACCESS_TOKEN          _HRESULT_TYPEDEF_(0x8015c005L)  // Access token signature is invalid
#define XONLINE_E_STORAGE_CANNOT_FIND_PATH              _HRESULT_TYPEDEF_(0x8015c006L)  // name resolution failed
#define XONLINE_E_STORAGE_FILE_IS_ELSEWHERE             _HRESULT_TYPEDEF_(0x8015c007L)  // redirection request
#define XONLINE_E_STORAGE_INVALID_STORAGE_PATH          _HRESULT_TYPEDEF_(0x8015c008L)  // Invalid storage path
#define XONLINE_E_STORAGE_INVALID_FACILITY              _HRESULT_TYPEDEF_(0x8015c009L)  // Invalid facility code
#define XONLINE_E_STORAGE_UNKNOWN_DOMAIN                _HRESULT_TYPEDEF_(0x8015c00AL)  // Bad pathname
#define XONLINE_E_STORAGE_SYNC_TIME_SKEW                _HRESULT_TYPEDEF_(0x8015c00BL)  // SyncDomain timestamp skew
#define XONLINE_E_STORAGE_SYNC_TIME_SKEW_LOCALTIME      _HRESULT_TYPEDEF_(0x8015c00CL)  // SyncDomain timestamp appears to be localtime
#define XONLINE_E_STORAGE_QUOTA_EXCEEDED                _HRESULT_TYPEDEF_(0x8015c00DL)  // Quota exceeded for storage domain
#define XONLINE_E_STORAGE_UNSUPPORTED_CONTENT_TYPE      _HRESULT_TYPEDEF_(0x8015c00EL)  // The type of the content is not supported by this API

#define XONLINE_E_STORAGE_FILE_ALREADY_EXISTS           _HRESULT_TYPEDEF_(0x8015c011L)  // File already exists and storage domain does not allow overwrites
#define XONLINE_E_STORAGE_DATABASE_ERROR                _HRESULT_TYPEDEF_(0x8015c012L)  // Unknown database error
#define XONLINE_S_STORAGE_FILE_NOT_MODIFIED             _HRESULT_TYPEDEF_(0x0015c013L)  // The file was not modified since the last installation




//-----------------------------------------------------------------------------
//  Profile setting definitions
//-----------------------------------------------------------------------------

#define XUSER_DATA_TYPE_CONTEXT     ((BYTE)0)
#define XUSER_DATA_TYPE_INT32       ((BYTE)1)
#define XUSER_DATA_TYPE_INT64       ((BYTE)2)
#define XUSER_DATA_TYPE_DOUBLE      ((BYTE)3)
#define XUSER_DATA_TYPE_UNICODE     ((BYTE)4)
#define XUSER_DATA_TYPE_FLOAT       ((BYTE)5)
#define XUSER_DATA_TYPE_BINARY      ((BYTE)6)
#define XUSER_DATA_TYPE_DATETIME    ((BYTE)7)
#define XUSER_DATA_TYPE_NULL        ((BYTE)0xFF)

#define XPROFILE_SETTING_MAX_SIZE               1000
#define XPROFILE_SETTING_MAX_PICTURE_KEY_PATH   100
#define XPROFILE_SETTING_MAX_GAMERCARD_MOTTO    (22 * sizeof(WCHAR))

#define XPROFILEID(type, size, id)              (((type & 0xf) << 28) | ((size & 0xfff) << 16) | (id & 0x3fff))

//                                                                      type                        size                    id

// These settings are readable and writable by titles
#define XPROFILE_OPTION_CONTROLLER_VIBRATION                XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          3)

#define XPROFILE_TITLE_SPECIFIC1                            XPROFILEID( XUSER_DATA_TYPE_BINARY,     XPROFILE_SETTING_MAX_SIZE,  0x3FFF)
#define XPROFILE_TITLE_SPECIFIC2                            XPROFILEID( XUSER_DATA_TYPE_BINARY,     XPROFILE_SETTING_MAX_SIZE,  0x3FFE)
#define XPROFILE_TITLE_SPECIFIC3                            XPROFILEID( XUSER_DATA_TYPE_BINARY,     XPROFILE_SETTING_MAX_SIZE,  0x3FFD)

// These settings are readable by titles (but not writable)
#define XPROFILE_GAMER_YAXIS_INVERSION                      XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          2)
#define XPROFILE_GAMERCARD_ZONE                             XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          4)
#define XPROFILE_GAMERCARD_REGION                           XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          5)
#define XPROFILE_GAMERCARD_CRED                             XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          6)
#define XPROFILE_GAMERCARD_REP                              XPROFILEID( XUSER_DATA_TYPE_FLOAT,      sizeof(DWORD),          11)

#define XPROFILE_OPTION_VOICE_MUTED                         XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          12)
#define XPROFILE_OPTION_VOICE_THRU_SPEAKERS                 XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          13)
#define XPROFILE_OPTION_VOICE_VOLUME                        XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          14)

#define XPROFILE_GAMERCARD_PICTURE_KEY                      XPROFILEID( XUSER_DATA_TYPE_UNICODE,    XPROFILE_SETTING_MAX_PICTURE_KEY_PATH,  15)
#define XPROFILE_GAMERCARD_MOTTO                            XPROFILEID( XUSER_DATA_TYPE_UNICODE,    XPROFILE_SETTING_MAX_GAMERCARD_MOTTO,   17)

#define XPROFILE_GAMERCARD_TITLES_PLAYED                    XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          18)
#define XPROFILE_GAMERCARD_ACHIEVEMENTS_EARNED              XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          19)

#define XPROFILE_GAMER_DIFFICULTY                           XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          21)
#define XPROFILE_GAMER_CONTROL_SENSITIVITY                  XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          24)
#define XPROFILE_GAMER_PREFERRED_COLOR_FIRST                XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          29)
#define XPROFILE_GAMER_PREFERRED_COLOR_SECOND               XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          30)
#define XPROFILE_GAMER_ACTION_AUTO_AIM                      XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          34)
#define XPROFILE_GAMER_ACTION_AUTO_CENTER                   XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          35)
#define XPROFILE_GAMER_ACTION_MOVEMENT_CONTROL              XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          36)
#define XPROFILE_GAMER_RACE_TRANSMISSION                    XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          38)
#define XPROFILE_GAMER_RACE_CAMERA_LOCATION                 XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          39)
#define XPROFILE_GAMER_RACE_BRAKE_CONTROL                   XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          40)
#define XPROFILE_GAMER_RACE_ACCELERATOR_CONTROL             XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          41)

#define XPROFILE_GAMERCARD_TITLE_CRED_EARNED                XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          56)
#define XPROFILE_GAMERCARD_TITLE_ACHIEVEMENTS_EARNED        XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          57)


typedef enum _XPROFILE_GAMERCARD_ZONE_OPTIONS
{
    XPROFILE_GAMERCARD_ZONE_XBOX_1 = 0,
    XPROFILE_GAMERCARD_ZONE_RR,
    XPROFILE_GAMERCARD_ZONE_PRO,
    XPROFILE_GAMERCARD_ZONE_FAMILY,
    XPROFILE_GAMERCARD_ZONE_UNDERGROUND

} XPROFILE_GAMERCARD_ZONE_OPTIONS;

typedef enum _XPROFILE_GAMER_DIFFICULTY_OPTIONS
{
    XPROFILE_GAMER_DIFFICULTY_NORMAL = 0,
    XPROFILE_GAMER_DIFFICULTY_EASY,
    XPROFILE_GAMER_DIFFICULTY_HARD

} XPROFILE_GAMER_DIFFICULTY_OPTIONS;

typedef enum _XPROFILE_CONTROL_SENSITIVITY_OPTIONS
{
    XPROFILE_CONTROL_SENSITIVITY_MEDIUM = 0,
    XPROFILE_CONTROL_SENSITIVITY_LOW,
    XPROFILE_CONTROL_SENSITIVITY_HIGH

} XPROFILE_CONTROL_SENSITIVITY_OPTIONS;

typedef enum _XPROFILE_PREFERRED_COLOR_OPTIONS
{
    XPROFILE_PREFERRED_COLOR_NONE = 0,
    XPROFILE_PREFERRED_COLOR_BLACK,
    XPROFILE_PREFERRED_COLOR_WHITE,
    XPROFILE_PREFERRED_COLOR_YELLOW,
    XPROFILE_PREFERRED_COLOR_ORANGE,
    XPROFILE_PREFERRED_COLOR_PINK,
    XPROFILE_PREFERRED_COLOR_RED,
    XPROFILE_PREFERRED_COLOR_PURPLE,
    XPROFILE_PREFERRED_COLOR_BLUE,
    XPROFILE_PREFERRED_COLOR_GREEN,
    XPROFILE_PREFERRED_COLOR_BROWN,
    XPROFILE_PREFERRED_COLOR_SILVER

} XPROFILE_PREFERRED_COLOR_OPTIONS;

typedef enum _XPROFILE_ACTION_AUTO_AIM_OPTIONS
{
    XPROFILE_ACTION_AUTO_AIM_OFF = 0,
    XPROFILE_ACTION_AUTO_AIM_ON

} XPROFILE_ACTION_AUTO_AIM_OPTIONS;

typedef enum _XPROFILE_ACTION_AUTO_CENTER_OPTIONS
{
    XPROFILE_ACTION_AUTO_CENTER_OFF = 0,
    XPROFILE_ACTION_AUTO_CENTER_ON

} XPROFILE_ACTION_AUTO_CENTER_OPTIONS;

typedef enum _XPROFILE_ACTION_MOVEMENT_CONTROL_OPTIONS
{
    XPROFILE_ACTION_MOVEMENT_CONTROL_L_THUMBSTICK = 0,
    XPROFILE_ACTION_MOVEMENT_CONTROL_R_THUMBSTICK

} XPROFILE_ACTION_MOVEMENT_CONTROL_OPTIONS;

typedef enum _XPROFILE_RACE_TRANSMISSION_OPTIONS
{
    XPROFILE_RACE_TRANSMISSION_AUTO = 0,
    XPROFILE_RACE_TRANSMISSION_MANUAL

} XPROFILE_RACE_TRANSMISSION_OPTIONS;

typedef enum _XPROFILE_RACE_CAMERA_LOCATION_OPTIONS
{
    XPROFILE_RACE_CAMERA_LOCATION_BEHIND = 0,
    XPROFILE_RACE_CAMERA_LOCATION_IN_FRONT,
    XPROFILE_RACE_CAMERA_LOCATION_INSIDE

} XPROFILE_RACE_CAMERA_LOCATION_OPTIONS;

typedef enum _XPROFILE_RACE_BRAKE_CONTROL_OPTIONS
{
    XPROFILE_RACE_BRAKE_CONTROL_TRIGGER = 0,
    XPROFILE_RACE_BRAKE_CONTROL_BUTTON

} XPROFILE_RACE_BRAKE_CONTROL_OPTIONS;

typedef enum _XPROFILE_RACE_ACCELERATOR_CONTROL_OPTIONS
{
    XPROFILE_RACE_ACCELERATOR_CONTROL_TRIGGER = 0,
    XPROFILE_RACE_ACCELERATOR_CONTROL_BUTTON

} XPROFILE_RACE_ACCELERATOR_CONTROL_OPTIONS;

typedef enum _XPROFILE_GAMER_YAXIS_INVERSION_OPTIONS
{
    XPROFILE_YAXIS_INVERSION_OFF = 0,
    XPROFILE_YAXIS_INVERSION_ON

} XPROFILE_GAMER_YAXIS_INVERSION_OPTIONS;

typedef enum _XPROFILE_CONTROLLER_VIBRATION_OPTIONS
{
    XPROFILE_CONTROLLER_VIBRATION_OFF = 0,
    XPROFILE_CONTROLLER_VIBRATION_ON = 3
} XPROFILE_CONTROLLER_VIBRATION_OPTIONS;

typedef enum _XPROFILE_VOICE_THRU_SPEAKERS_OPTIONS
{
    XPROFILE_VOICE_THRU_SPEAKERS_OFF = 0,
    XPROFILE_VOICE_THRU_SPEAKERS_ON,
    XPROFILE_VOICE_THRU_SPEAKERS_BOTH
} XPROFILE_VOICE_THRU_SPEAKERS_OPTIONS;


typedef enum _XUSER_PROFILE_SOURCE
{
    XSOURCE_NO_VALUE = 0,
    XSOURCE_DEFAULT,
    XSOURCE_TITLE,
    XSOURCE_PERMISSION_DENIED,
} XUSER_PROFILE_SOURCE;


typedef struct _XUSER_PROFILE_SETTING
{
    XUSER_PROFILE_SOURCE    source;

    union                                   // Used only on read, ignored for write
    {
        DWORD               dwUserIndex;    // Valid only after local read
        XUID                xuid;           // Valid only after online read
    } user;

    DWORD                   dwSettingId;

    XUSER_DATA              data;
} XUSER_PROFILE_SETTING, *PXUSER_PROFILE_SETTING;


typedef struct _XUSER_READ_PROFILE_SETTING_RESULT
{
    DWORD                  dwSettingsLen;
    XUSER_PROFILE_SETTING *pSettings;
} XUSER_READ_PROFILE_SETTING_RESULT, *PXUSER_READ_PROFILE_SETTING_RESULT;


//------------------------------------------------------------------------------
// Session API Structs
//------------------------------------------------------------------------------

typedef struct _XSESSION_INFO
{
    XNKID sessionID;                // 8 bytes
    XNADDR hostAddress;             // 36 bytes
    XNKEY keyExchangeKey;           // 16 bytes
} XSESSION_INFO, *PXSESSION_INFO;

typedef struct _XSESSION_SEARCHRESULT
{
    XSESSION_INFO   info;
    DWORD           dwOpenPublicSlots;
    DWORD           dwOpenPrivateSlots;
    DWORD           dwFilledPublicSlots;
    DWORD           dwFilledPrivateSlots;
    DWORD           cProperties;
    DWORD           cContexts;
    PXUSER_PROPERTY pProperties;
    PXUSER_CONTEXT  pContexts;
} XSESSION_SEARCHRESULT, *PXSESSION_SEARCHRESULT;

typedef struct _XSESSION_SEARCHRESULT_HEADER
{
    DWORD dwSearchResults;
    XSESSION_SEARCHRESULT *pResults;
} XSESSION_SEARCHRESULT_HEADER, *PXSESSION_SEARCHRESULT_HEADER;

typedef struct _XSESSION_REGISTRANT
{
    ULONGLONG qwMachineID;
    DWORD bTrustworthiness;
    DWORD bNumUsers;
    XUID *rgUsers;

} XSESSION_REGISTRANT;

typedef struct _XSESSION_REGISTRATION_RESULTS
{
    DWORD wNumRegistrants;
    XSESSION_REGISTRANT *rgRegistrants;
} XSESSION_REGISTRATION_RESULTS, *PXSESSION_REGISTRATION_RESULTS;

typedef struct _XSESSION_VIEW_PROPERTIES
{
    DWORD                   dwViewId;
    DWORD                   dwNumProperties;
    XUSER_PROPERTY*         pProperties;
} XSESSION_VIEW_PROPERTIES;

typedef enum _XSESSION_STATE
{
    XSESSION_STATE_LOBBY = 0,              // Session is newly created
    XSESSION_STATE_REGISTRATION,           // Session is registering with arbitration
    XSESSION_STATE_INGAME,                 // Start has been called
    XSESSION_STATE_REPORTING,              // End has been called, uploading stats
    XSESSION_STATE_DELETED                 // Delete has been called, session is invalid
} XSESSION_STATE;


#define XSESSION_MEMBER_FLAGS_PRIVATE_SLOT      0x00000001
#define XSESSION_MEMBER_FLAGS_ZOMBIE            0x00000002

typedef struct _XSESSION_MEMBER
{
    XUID                xuidOnline;
    DWORD               dwUserIndex;
    DWORD               dwFlags;
} XSESSION_MEMBER;


typedef struct _XSESSION_LOCAL_DETAILS
{
    DWORD               dwUserIndexHost;      // Only valid if the host is local to the console
    DWORD               dwGameType;
    DWORD               dwGameMode;
    DWORD               dwFlags;
    DWORD               dwMaxPublicSlots;
    DWORD               dwMaxPrivateSlots;
    DWORD               dwAvailablePublicSlots;
    DWORD               dwAvailablePrivateSlots;
    DWORD               dwActualMemberCount;
    DWORD               dwReturnedMemberCount;
    XSESSION_STATE      eState;
    ULONGLONG           qwNonce;
    XSESSION_INFO       sessionInfo;
    XNKID               xnkidArbitration;

    XSESSION_MEMBER*    pSessionMembers;
} XSESSION_LOCAL_DETAILS;


#define XTITLE_SERVER_MAX_SERVER_INFO_LEN       200
#define XTITLE_SERVER_MAX_LSP_INFO              1000

typedef struct
{
    IN_ADDR         inaServer;
    DWORD           dwFlags;
    CHAR            szServerInfo[XTITLE_SERVER_MAX_SERVER_INFO_LEN];
} XTITLE_SERVER_INFO, *PXTITLE_SERVER_INFO;

#define XMARKETPLACE_MAX_OFFER_PRICE_TEXT_LENGTH        50
#define XMARKETPLACE_MAX_OFFER_NAME_LENGTH              100
#define XMARKETPLACE_MAX_OFFER_SELL_TEXT_LENGTH         1000
#define XMARKETPLACE_MAX_TITLE_NAME_LENGTH              100
#define XMARKETPLACE_MAX_OFFERS_ENUMERATED              100

#define XMARKETPLACE_CONTENT_ID_LEN                     20

typedef enum {
    XMARKETPLACE_OFFERING_TYPE_CONTENT              = 0x00000002,
    XMARKETPLACE_OFFERING_TYPE_GAME_DEMO            = 0x00000020,
    XMARKETPLACE_OFFERING_TYPE_GAME_TRAILER         = 0x00000040,
    XMARKETPLACE_OFFERING_TYPE_THEME                = 0x00000080,
    XMARKETPLACE_OFFERING_TYPE_TILE                 = 0x00000800,
    XMARKETPLACE_OFFERING_TYPE_ARCADE               = 0x00002000,
    XMARKETPLACE_OFFERING_TYPE_VIDEO                = 0x00004000,
    XMARKETPLACE_OFFERING_TYPE_CONSUMABLE           = 0x00010000,
} XMARKETPLACE_OFFERING_TYPE;

typedef struct _XMARKETPLACE_CONTENTOFFER_INFO
{
    ULONGLONG                       qwOfferID;
    ULONGLONG                       qwPreviewOfferID;
    DWORD                           dwOfferNameLength;
    WCHAR                          *wszOfferName;
    DWORD                           dwOfferType;
    BYTE                            contentId[XMARKETPLACE_CONTENT_ID_LEN];
    BOOL                            fIsUnrestrictedLicense;
    DWORD                           dwLicenseMask;
    DWORD                           dwTitleID;
    DWORD                           dwContentCategory;
    DWORD                           dwTitleNameLength;
    WCHAR                          *wszTitleName;
    BOOL                            fUserHasPurchased;
    DWORD                           dwPackageSize;
    DWORD                           dwInstallSize;
    DWORD                           dwSellTextLength;
    WCHAR                          *wszSellText;
    DWORD                           dwAssetID;
    DWORD                           dwPurchaseQuantity;     
    DWORD                           dwPointsPrice;                    
} XMARKETPLACE_CONTENTOFFER_INFO, *PXMARKETPLACE_CONTENTOFFER_INFO;

#define XMARKETPLACE_ASSET_MAX_ENUM_SIZE     100
#define XMARKETPLACE_ASSET_SIGNATURE_SIZE    256

typedef struct _XMARKETPLACE_ASSET
{
    DWORD                               dwAssetID;
    DWORD                               dwQuantity;
} XMARKETPLACE_ASSET, *PXMARKETPLACE_ASSET;

typedef struct _XMARKETPLACE_ASSET_PACKAGE
{
    FILETIME                            ftEnumerate;
    DWORD                               cAssets;
    DWORD                               cTotalAssets;
    XMARKETPLACE_ASSET                  aAssets[1];         // this array contains cAssets number of entries... not 1.
} XMARKETPLACE_ASSET_PACKAGE, *PXMARKETPLACE_ASSET_PACKAGE;

typedef struct _XMARKETPLACE_ASSET_ENUMERATE_REPLY
{
    BYTE                                signature[XMARKETPLACE_ASSET_SIGNATURE_SIZE];
    XMARKETPLACE_ASSET_PACKAGE          assetPackage;
} XMARKETPLACE_ASSET_ENUMERATE_REPLY, *PXMARKETPLACE_ASSET_ENUMERATE_REPLY;

#pragma pack(push, 1)

typedef struct _STRING_DATA
{
    WORD wStringSize;
    WCHAR *pszString;
} STRING_DATA;

typedef struct _STRING_VERIFY_RESPONSE
{
    WORD wNumStrings;
    HRESULT *pStringResult;
} STRING_VERIFY_RESPONSE;

typedef struct _ADDRESS_INFO
{
    WORD wStreet1Length;
    WCHAR *wszStreet1;
    WORD wStreet2Length;
    WCHAR *wszStreet2;
    WORD wCityLength;
    WCHAR *wszCity;
    WORD wDistrictLength;
    WCHAR *wszDistrict;
    WORD wStateLength;
    WCHAR *wszState;
    WORD wPostalCodeLength;
    WCHAR *wszPostalCode;
} ADDRESS_INFO;

typedef struct _GET_USER_INFO_RESPONSE
{
    WORD wFirstNameLength;
    WCHAR *wszFirstName;
    WORD wLastNameLength;
    WCHAR *wszLastName;
    ADDRESS_INFO addressInfo;
    WORD wEmailLength;
    WCHAR *wszEmail;
    WORD wLanguageId;
    BYTE bCountryId;
    BYTE bMsftOptIn;
    BYTE bParterOptIn;
    BYTE bAge;
} GET_USER_INFO_RESPONSE;

typedef struct _XUSER_RANK_REQUEST
{
    DWORD dwViewId;
    LONGLONG i64Rating;
} XUSER_RANK_REQUEST;

typedef struct _XUSER_ESTIMATE_RANK_RESULTS
{
    DWORD dwNumRanks;
    DWORD *pdwRanks;
} XUSER_ESTIMATE_RANK_RESULTS;

typedef struct _XINVITE_INFO
{
    XUID xuidInvitee;
    XUID xuidInviter;
    DWORD dwTitleID;
    XSESSION_INFO hostInfo;
    BOOL fFromGameInvite;
} XINVITE_INFO, *PXINVITE_INFO;

typedef struct _XSTORAGE_FILE_INFO
{
    DWORD dwTitleID;
    DWORD dwTitleVersion;
    ULONGLONG qwOwnerPUID;
    BYTE bCountryID;
    ULONGLONG qwReserved;
    DWORD dwContentType;
    DWORD dwStorageSize;
    DWORD dwInstalledSize;
    FILETIME ftCreated;
    FILETIME ftLastModified;
    WORD wAttributesSize;
    WORD cchPathName;
    WCHAR *pwszPathName;
    BYTE *pbAttributes;
} XSTORAGE_FILE_INFO, *PXSTORAGE_FILE_INFO;

typedef struct _XSTORAGE_ENUMERATE_RESULTS
{
    DWORD dwTotalNumItems;
    DWORD dwNumItemsReturned;
    XSTORAGE_FILE_INFO *pItems;
} XSTORAGE_ENUMERATE_RESULTS;

typedef struct _XSTORAGE_DOWNLOAD_TO_MEMORY_RESULTS
{
    DWORD dwBytesTotal;
    XUID xuidOwner;
    FILETIME ftCreated;
} XSTORAGE_DOWNLOAD_TO_MEMORY_RESULTS;

#pragma pack(pop)


//
// Initialization and shutdown of the Live features
//

XBOXAPI
DWORD
WINAPI
XOnlineStartup();

XBOXAPI
DWORD
WINAPI
XOnlineCleanup();


//
// NAT type identification values
//

typedef enum
{
    XONLINE_NAT_OPEN = 1,
    XONLINE_NAT_MODERATE,
    XONLINE_NAT_STRICT
} XONLINE_NAT_TYPE;

XBOXAPI
XONLINE_NAT_TYPE
WINAPI
XOnlineGetNatType();


//
// Service info
//

#pragma pack(push, 4)
typedef struct _XONLINE_SERVICE_INFO
{
    DWORD          dwServiceID;
    IN_ADDR        serviceIP;
    WORD           wServicePort;
    WORD           wReserved;
} XONLINE_SERVICE_INFO, *PXONLINE_SERVICE_INFO;
#pragma pack(pop)

XBOXAPI
DWORD
WINAPI
XOnlineGetServiceInfo(
    IN DWORD dwServiceID,
    OUT PXONLINE_SERVICE_INFO pServiceInfo
    );


XAMINLINE
DWORD
WINAPI
XAccountGetUserInfoResponseSize()
{
    return sizeof(GET_USER_INFO_RESPONSE) +
        (MAX_FIRSTNAME_SIZE * sizeof(WCHAR)) +
        (MAX_LASTNAME_SIZE * sizeof(WCHAR)) +
        (MAX_EMAIL_SIZE * sizeof(WCHAR)) +
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street1
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street2
        (MAX_CITY_SIZE * sizeof(WCHAR)) +
        (MAX_DISTRICT_SIZE * sizeof(WCHAR)) +
        (MAX_STATE_SIZE * sizeof(WCHAR)) +
        (MAX_POSTALCODE_SIZE * sizeof(WCHAR));
}


XBOXAPI
DWORD
WINAPI
XStorageBuildServerPath(
    IN DWORD dwUserIndex,
    IN XSTORAGE_FACILITY StorageFacility,
    IN CONST void *pvStorageFacilityInfo    OPTIONAL,
    IN DWORD dwStorageFacilityInfoSize      OPTIONAL,
    IN LPCWSTR pwszItemName,
    IN OUT WCHAR *pwszServerPath            OPTIONAL,
    IN OUT DWORD *pdwServerPathLength
    );

XBOXAPI
DWORD
WINAPI
XStorageBuildServerPathByXuid(
    IN XUID xuidUser,
    IN XSTORAGE_FACILITY StorageFacility,
    IN CONST void *pvStorageFacilityInfo    OPTIONAL,
    IN DWORD dwStorageFacilityInfoSize      OPTIONAL,
    IN LPCWSTR pwszItemName,
    IN OUT WCHAR *pwszServerPath            OPTIONAL,
    IN OUT DWORD *pdwServerPathLength
    );

XBOXAPI
DWORD
WINAPI
XStorageDownloadToMemoryGetProgress(
    IN OUT XOVERLAPPED *pXOverlapped,
    OUT DWORD *pdwPercentComplete           OPTIONAL,
    OUT ULONGLONG *pqwNumerator             OPTIONAL,
    OUT ULONGLONG *pqwDenominator           OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XStorageUploadFromMemoryGetProgress(
    IN OUT XOVERLAPPED *pXOverlapped,
    OUT DWORD *pdwPercentComplete           OPTIONAL,
    OUT ULONGLONG *pqwNumerator             OPTIONAL,
    OUT ULONGLONG *pqwDenominator           OPTIONAL
    );


//-----------------------------------------------------------------------------
//  Profile Setting APIs
//-----------------------------------------------------------------------------

XBOXAPI
DWORD
WINAPI
XUserWriteProfileSettings(
    IN DWORD                    dwUserIndex,        // User index of player whose settings are written
    IN DWORD                    dwNumSettings,      // Count of settings in pSettings
    IN const PXUSER_PROFILE_SETTING pSettings,      // Pointer to array of settings to set
    IN OUT PXOVERLAPPED         pXOverlapped            OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XUserReadProfileSettings(
    IN DWORD                    dwTitleId,          // A title in your family or 0 for the current title
    IN DWORD                    dwUserIndex,        // User index of requesting user
    IN DWORD                    dwNumSettingIds,    // Count of setting ids in pdwSettingIds
    IN const DWORD*             pdwSettingIds,      // Pointer to array of settings to retrieve
    IN OUT DWORD*               pcbResults,         // Size of pResults buffer.  If *pcbResults is 0 then required size is returned.
    IN OUT PXUSER_READ_PROFILE_SETTING_RESULT pResults,
    IN OUT PXOVERLAPPED         pXOverlapped            OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XUserReadProfileSettingsByXuid(
    IN DWORD                    dwTitleId,          // A title in your family or 0 for the current title
    IN DWORD                    dwUserIndexRequester,   // User index of requesting user.  Used for permission checking.
    IN DWORD                    dwNumFor,           // Count of XUIDs in pxuidFor
    IN const XUID*              pxuidFor,           // Pointer to array of XUIDs to request settings for
    IN DWORD                    dwNumSettingIds,    // Count of setting ids in pdwSettingIds
    IN const DWORD*             pdwSettingIds,      // Pointer to array of settings to retrieve
    IN OUT DWORD*               pcbResults,         // Size of pResults buffer.  If *pcbResults is 0 then required size is returned.
    IN OUT PXUSER_READ_PROFILE_SETTING_RESULT pResults,
    IN OUT PXOVERLAPPED         pXOverlapped            OPTIONAL
    );


#define XUserGetProfileSettingMaxSize(dwSettingId)  ((dwSettingId & 0x0fff0000) >> 16)
#define XUserGetProfileSettingType(dwSettingId)     ((BYTE)((dwSettingId & 0xf0000000) >> 28))


// Creation Flags
#define XSESSION_CREATE_USES_MASK                       0x0000003F

#define XSESSION_CREATE_HOST                            0x00000001  // Set only on the host of a multiplayer session. The user who sets the host flag is the user that interacts with Live
#define XSESSION_CREATE_USES_PRESENCE                   0x00000002  // Session is used across games to keep players together. Advertises state via Presence
#define XSESSION_CREATE_USES_STATS                      0x00000004  // Session is used for stats tracking
#define XSESSION_CREATE_USES_MATCHMAKING                0x00000008  // Session is advertised in matchmaking for searching
#define XSESSION_CREATE_USES_ARBITRATION                0x00000010  // Session stats are arbitrated (and therefore tracked for everyone in the game)
#define XSESSION_CREATE_USES_PEER_NETWORK               0x00000020  // Session XNKey is registered and PC settings are enforced

// Optional modifiers to sessions that are created with XSESSION_CREATE_USES_PRESENCE
#define XSESSION_CREATE_MODIFIERS_MASK                  0x00000F00

#define XSESSION_CREATE_INVITES_DISABLED                0x00000100  // Game Invites cannot be sent by the HUD for this session
#define XSESSION_CREATE_JOIN_VIA_PRESENCE_DISABLED      0x00000200  // Session will not ever be displayed as joinable via Presence
#define XSESSION_CREATE_JOIN_IN_PROGRESS_DISABLED       0x00000400  // Session will not be joinable between XSessionStart and XSessionEnd
#define XSESSION_CREATE_JOIN_VIA_PRESENCE_FRIENDS_ONLY  0x00000800  // Session is only joinable via presence for friends of the host

// Common Developer Scenarios
#define XSESSION_CREATE_SINGLEPLAYER_WITH_STATS         ( \
      XSESSION_CREATE_USES_PRESENCE \
    | XSESSION_CREATE_USES_STATS \
    | XSESSION_CREATE_INVITES_DISABLED \
    | XSESSION_CREATE_JOIN_VIA_PRESENCE_DISABLED \
    | XSESSION_CREATE_JOIN_IN_PROGRESS_DISABLED )

#define XSESSION_CREATE_LIVE_MULTIPLAYER_STANDARD       ( \
      XSESSION_CREATE_USES_PRESENCE \
    | XSESSION_CREATE_USES_STATS \
    | XSESSION_CREATE_USES_MATCHMAKING \
    | XSESSION_CREATE_USES_PEER_NETWORK )

#define XSESSION_CREATE_LIVE_MULTIPLAYER_RANKED         ( \
      XSESSION_CREATE_LIVE_MULTIPLAYER_STANDARD \
    | XSESSION_CREATE_USES_ARBITRATION)

#define XSESSION_CREATE_SYSTEMLINK                      ( \
      XSESSION_CREATE_USES_PEER_NETWORK)

#define XSESSION_CREATE_GROUP_LOBBY                    ( \
      XSESSION_CREATE_USES_PRESENCE \
    | XSESSION_CREATE_USES_PEER_NETWORK)

#define XSESSION_CREATE_GROUP_GAME                     ( \
      XSESSION_CREATE_USES_STATS \
    | XSESSION_CREATE_USES_MATCHMAKING \
    | XSESSION_CREATE_USES_PEER_NETWORK)


// Search defines
#define XSESSION_SEARCH_MAX_PARAMS                      30  // We only allow the client to have 30 params on a query
#define XSESSION_SEARCH_MAX_RETURNS                     50  // We only allow the client to have 50 columns on a search result

XBOXAPI
DWORD
WINAPI
XSessionCreate(
    IN DWORD                dwFlags,
    IN DWORD                dwUserIndex,
    IN DWORD                dwMaxPublicSlots,
    IN DWORD                dwMaxPrivateSlots,
    IN OUT ULONGLONG*       pqwSessionNonce,
    IN OUT PXSESSION_INFO   pSessionInfo,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL,
    OUT HANDLE*             ph
    );

XBOXAPI
DWORD
WINAPI
XSessionModify (
    IN HANDLE               hSession,
    IN DWORD                dwFlags,
    IN DWORD                dwMaxPublicSlots,
    IN DWORD                dwMaxPrivateSlots,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionDelete(
    IN HANDLE               hSession,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionJoinLocal(
    IN HANDLE               hSession,
    IN DWORD                dwUserCount,
    IN const DWORD*         pdwUserIndexes,
    IN const BOOL*          pfPrivateSlots,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionJoinRemote(
    IN HANDLE               hSession,
    IN DWORD                dwXuidCount,
    IN const XUID*          pXuids,
    IN const BOOL*          pfPrivateSlots,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionLeaveLocal(
    IN HANDLE               hSession,
    IN DWORD                dwUserCount,
    IN const DWORD*         pdwUserIndexes,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionLeaveRemote(
    IN HANDLE               hSession,
    IN DWORD                dwXuidCount,
    IN const XUID*          pXuids,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionArbitrationRegister(
    IN HANDLE               hSession,
    IN DWORD                dwFlags,
    IN ULONGLONG            qwSessionNonce,
    IN OUT DWORD*           pcbResultsBuffer,
    IN OUT PXSESSION_REGISTRATION_RESULTS pRegistrationResults,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionStart(
    IN HANDLE               hSession,
    IN DWORD                dwFlags,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionEnd(
    IN HANDLE               hSession,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionSearch(
    IN DWORD                dwProcedureIndex,
    IN DWORD                dwUserIndex,
    IN DWORD                dwNumResults,
    IN WORD                 wNumProperties,
    IN WORD                 wNumContexts,
    IN PXUSER_PROPERTY      pSearchProperties,
    IN PXUSER_CONTEXT       pSearchContexts,
    IN OUT DWORD*           pcbResultsBuffer,
    IN OUT PXSESSION_SEARCHRESULT_HEADER pSearchResults,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionSearchEx(
    IN DWORD                dwProcedureIndex,
    IN DWORD                dwUserIndex,
    IN DWORD                dwNumResults,
    IN DWORD                dwNumUsers,
    IN WORD                 wNumProperties,
    IN WORD                 wNumContexts,
    IN PXUSER_PROPERTY      pSearchProperties,
    IN PXUSER_CONTEXT       pSearchContexts,
    IN OUT DWORD*           pcbResultsBuffer,
    IN OUT PXSESSION_SEARCHRESULT_HEADER pSearchResults,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionSearchByID(
    IN XNKID                sessionID,
    IN DWORD                dwUserIndex,
    IN OUT DWORD*           pcbResultsBuffer,
    IN OUT PXSESSION_SEARCHRESULT_HEADER pSearchResults,
    IN OUT PXOVERLAPPED     pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionGetDetails(
    IN HANDLE                       hSession,
    IN OUT DWORD*                   pcbResultsBuffer,
    IN OUT XSESSION_LOCAL_DETAILS*  pSessionDetails,
    IN OUT PXOVERLAPPED             pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionMigrateHost(
    IN HANDLE                       hSession,
    IN DWORD                        dwUserIndex,
    IN OUT XSESSION_INFO*           pSessionInfo,
    IN OUT PXOVERLAPPED             pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionModifySkill(
    IN      HANDLE                  hSession,
    IN      DWORD                   dwNumXuids,
    IN      CONST XUID*             rgXuid,
    IN OUT  PXOVERLAPPED            pXOverlapped    OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XSessionCalculateSkill(
    IN      DWORD                   dwNumSkills,
    IN      double*                 rgMu,
    IN      double*                 rgSigma,
    OUT     double*                 pdblAggregateMu,
    OUT     double*                 pdblAggregateSigma
    );


//-----------------------------------------------------------------------------
// Session stats
//-----------------------------------------------------------------------------

// View id used to write to skill leaderboard
#define X_STATS_VIEW_SKILL                      0xFFFF0000

#define X_STATS_MAX_VIEWS                       64
#define X_STATS_MAX_PROPERTIES_IN_VIEW          64
#define X_STATS_MAX_USER_COUNT                  101
#define X_STATS_MAX_ROW_COUNT                   100


XBOXAPI
DWORD
WINAPI
XSessionWriteStats(
    IN      HANDLE                          hSession,
    IN      XUID                            xuid,                       // Remote XUID to update
    IN      DWORD                           dwNumViews,                 // Number of structs in pViews
    IN      CONST XSESSION_VIEW_PROPERTIES* pViews,                     // List of views to update
    IN OUT  XOVERLAPPED*                    pXOverlapped    OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XSessionFlushStats(
    IN      HANDLE                          hSession,
    IN OUT  XOVERLAPPED*                    pXOverlapped    OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XTitleServerCreateEnumerator(
    IN      LPCSTR                      pszServerInfo,
    IN      DWORD                       cItem,
    OUT     PDWORD                      pcbBuffer           OPTIONAL,
    OUT     PHANDLE                     phEnum
    );


XBOXAPI
DWORD
WINAPI
XMarketplaceCreateOfferEnumerator(
    IN      DWORD                   dwUserIndex,
    IN      DWORD                   dwOfferType,
    IN      DWORD                   dwContentCategories,
    IN      DWORD                   cItem,
    OUT     PDWORD                  pcbBuffer               OPTIONAL,
    OUT     PHANDLE                 phEnum
    );


XBOXAPI
DWORD
WINAPI
XMarketplaceCreateAssetEnumerator(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       cItem,
    OUT     PDWORD                      pcbBuffer               OPTIONAL,
    OUT     PHANDLE                     phEnum
    );

XBOXAPI
DWORD
WINAPI
XFriendsCreateEnumerator(
    IN DWORD dwUserIndex,
    IN DWORD dwStartingIndex,
    IN DWORD dwFriendsToReturn,
    OUT DWORD *pcbBuffer,
    OUT HANDLE *ph
    );

XBOXAPI
DWORD
WINAPI
XInviteGetAcceptedInfo(
    IN DWORD dwUserIndex,
    OUT XINVITE_INFO *pInfo
    );

XBOXAPI
DWORD
WINAPI
XInviteSend(
    IN DWORD dwUserIndex,
    IN DWORD cInvitees,
    IN const XUID *pXuidInvitees,
    IN const WCHAR *pszText,
    IN OUT XOVERLAPPED *pXOverlapped           OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XMarketplaceConsumeAssets(
    IN DWORD dwUserIndex,
    IN DWORD cAssets,
    IN const XMARKETPLACE_ASSET *pAssets,
    IN OUT XOVERLAPPED *pXOverlapped           OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XPresenceCreateEnumerator(
    IN DWORD dwUserIndex,
    IN DWORD cPeers,
    IN const XUID *pPeers,
    IN DWORD dwStartingIndex,
    IN DWORD dwPeersToReturn,
    OUT DWORD *pcbBuffer,
    OUT HANDLE *ph
    );

XBOXAPI
DWORD
WINAPI
XPresenceInitialize(
    IN DWORD cPeerSubscriptions
    );

XBOXAPI
DWORD
WINAPI
XPresenceSubscribe(
    IN DWORD dwUserIndex,
    IN DWORD cPeers,
    IN const XUID *pPeers
    );

XBOXAPI
DWORD
WINAPI
XPresenceUnsubscribe(
    IN DWORD dwUserIndex,
    IN DWORD cPeers,
    IN const XUID *pPeers
    );

XBOXAPI
DWORD
WINAPI
XStorageDelete(
    IN DWORD dwUserIndex,
    IN const WCHAR *wszServerPath,
    IN OUT XOVERLAPPED *pXOverlapped           OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XStorageDownloadToMemory(
    IN DWORD dwUserIndex,
    IN const WCHAR *wszServerPath,
    IN DWORD dwBufferSize,
    IN const BYTE *pbBuffer,
    IN DWORD cbResults,
    OUT XSTORAGE_DOWNLOAD_TO_MEMORY_RESULTS *pResults,
    IN OUT XOVERLAPPED *pXOverlapped           OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XStorageEnumerate(
    IN DWORD dwUserIndex,
    IN const WCHAR *wszServerPath,
    IN DWORD dwStartingIndex,
    IN DWORD dwMaxResultsToReturn,
    IN DWORD cbResults,
    OUT XSTORAGE_ENUMERATE_RESULTS *pResults,
    IN OUT XOVERLAPPED *pXOverlapped           OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XStorageUploadFromMemory(
    IN DWORD dwUserIndex,
    IN const WCHAR *wszServerPath,
    IN DWORD dwBufferSize,
    IN const BYTE *pbBuffer,
    IN OUT XOVERLAPPED *pXOverlapped           OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XStringVerify(
    IN DWORD dwFlags,
    IN const CHAR *szLocale,
    IN DWORD dwNumStrings,
    IN const STRING_DATA *pStringData,
    IN DWORD cbResults,
    OUT STRING_VERIFY_RESPONSE *pResults,
    IN OUT XOVERLAPPED *pXOverlapped           OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XUserEstimateRankForRating(
    IN DWORD dwNumRequests,
    IN const XUSER_RANK_REQUEST *pRankRequests,
    IN DWORD cbResults,
    OUT XUSER_ESTIMATE_RANK_RESULTS *pResults,
    IN OUT XOVERLAPPED *pXOverlapped           OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
_XAccountGetUserInfo(
    IN DWORD dwUserIndex,
    IN DWORD cbResults,
    OUT GET_USER_INFO_RESPONSE *pResults,
    IN OUT XOVERLAPPED *pXOverlapped           OPTIONAL
    );


#ifdef __cplusplus
}
#endif

#endif  // __XONLINE__


