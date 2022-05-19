
/*
 * Copyright (c) Microsoft Corporation
 *
 * Defines the interface to the XRN Messaging library
 */

#ifndef __XRNM_H__
#define __XRNM_H__



#include "XrnErrors.h"


#ifdef __cplusplus
extern "C" {
#endif // end if defined __cplusplus

#pragma pack(push, 8)


/*
 * Typedefs for Xrnm
 */

// Handle Types
typedef DWORD_PTR XRNM_HANDLE;

// Identity of channels
typedef DWORD XRNM_CHANNEL_ID;

// Invalid channel identity
static const XRNM_CHANNEL_ID XRNM_INVALID_CHANNEL_ID = 0;

/*
 * Enumerated Types for Xrnm
 */

typedef enum XRNM_STATUS
{
    XRNM_STATUS_ACTIVATING,
    XRNM_STATUS_ACTIVE,
    XRNM_STATUS_TERMINATING,
    XRNM_STATUS_TERMINATED
} XRNM_STATUS, * PXRNM_STATUS;

typedef enum XRNM_CHANNEL_TYPE
{
    XRNM_CHANNEL_TYPE_GAMEDATA,
    XRNM_CHANNEL_TYPE_CHAT,

    XRNM_NUM_CHANNEL_TYPES
} XRNM_CHANNEL_TYPE, * PXRNM_CHANNEL_TYPE;

typedef enum XRNM_RECEIPT_TYPE
{
    XRNM_RECEIPT_TYPE_TRANSMIT,
    XRNM_RECEIPT_TYPE_RECEIVE,
    XRNM_RECEIPT_TYPE_PROCESS
} XRNM_RECEIPT_TYPE, * PXRNM_RECEIPT_TYPE;

typedef enum XRNM_EVENT_TYPE
{
    XRNM_EVENT_TYPE_DATA_RECEIVED               = 1,
    XRNM_EVENT_TYPE_RECEIVE_CHANNEL_CREATED     = 2,
    XRNM_EVENT_TYPE_RECEIVE_CHANNEL_TERMINATED  = 3,
    XRNM_EVENT_TYPE_SEND_CHANNEL_TERMINATED     = 4,
    XRNM_EVENT_TYPE_SEND_BUFFER_RETURNED        = 5,
    XRNM_EVENT_TYPE_RECEIPT                     = 6,
    XRNM_EVENT_TYPE_LINK_STATUS_UPDATE          = 7,
    XRNM_EVENT_TYPE_INBOUND_LINK_REQUEST        = 8,
    XRNM_EVENT_TYPE_ALERT                       = 9,
} XRNM_EVENT_TYPE, * PXRNM_EVENT_TYPE;

typedef enum XRNM_INFO_TYPE
{
    XRNM_INFO_TYPE_SEND_CHANNEL_QUEUED_SENDS      = 0x10000000,
    XRNM_INFO_TYPE_SEND_CHANNEL_QUEUED_BYTES      = 0x10000001,
    XRNM_INFO_TYPE_SEND_CHANNEL_OUTSTANDING_SENDS = 0x10000002,
    XRNM_INFO_TYPE_SEND_CHANNEL_OUTSTANDING_BYTES = 0x10000003,
    XRNM_INFO_TYPE_LINK_AVERAGE_RTT               = 0x20000000,
    XRNM_INFO_TYPE_LINK_SEND_THROTTLE_RATE        = 0x20000001,
    XRNM_INFO_TYPE_LINK_SENT_PACKETS              = 0x20000002,
    XRNM_INFO_TYPE_LINK_SENT_BYTES                = 0x20000003,
    XRNM_INFO_TYPE_LINK_RETRIED_PACKETS           = 0x20000004,
    XRNM_INFO_TYPE_LINK_RETRIED_BYTES             = 0x20000005,
    XRNM_INFO_TYPE_LINK_RECEIVED_PACKETS          = 0x20000006,
    XRNM_INFO_TYPE_LINK_RECEIVED_BYTES            = 0x20000007,
    XRNM_INFO_TYPE_LINK_DROPPED_PACKETS           = 0x20000008,
    XRNM_INFO_TYPE_LINK_SEND_PACKETS_IN_USE       = 0x20000009,
} XRNM_INFO_TYPE, * PXRNM_INFO_TYPE;

typedef enum XRNM_ALERT_TYPE
{
    XRNM_ALERT_TYPE_SEND_CHANNEL_EXCEED_NUM_QUEUED_SENDS = 0x10000000,
    XRNM_ALERT_TYPE_SEND_CHANNEL_EXCEED_NUM_QUEUED_BYTES = 0x10000001,
    XRNM_ALERT_TYPE_LINK_EXCEED_AVERAGE_RTT              = 0x20000000,
    XRNM_ALERT_TYPE_LINK_EXCEED_SEND_BANDWIDTH_USED      = 0x20000001,
} XRNM_ALERT_TYPE, * PXRNM_ALERT_TYPE;

typedef enum XRNM_OPTION
{
    XRNM_OPTION_MIN_SEND_RATE            = 0x00000001,
    XRNM_OPTION_MAX_SEND_RATE            = 0x00000002,
    XRNM_OPTION_INITIAL_SEND_RATE        = 0x00000003,
    XRNM_OPTION_COALESCE_DELAY           = 0x00000004,
    XRNM_OPTION_MIN_RTT                  = 0x00000005,
    XRNM_OPTION_MAX_RTT                  = 0x00000006,
    XRNM_OPTION_CONNECT_RETRY_PERIOD     = 0x00000007,
    XRNM_OPTION_MAX_CONNECT_RETRIES      = 0x00000008,
    XRNM_OPTION_MAX_DATA_RETRIES         = 0x00000009,
    XRNM_OPTION_NORMAL_ACK_PERIOD        = 0x0000000A,
    XRNM_OPTION_LAZY_ACK_PERIOD          = 0x0000000B,
    XRNM_OPTION_SEND_PACKET_POOL_SIZE    = 0x0000000C,
    XRNM_OPTION_RECV_PACKET_POOL_SIZE    = 0x0000000D,
    XRNM_OPTION_KEEPALIVE_TIME           = 0x0000000E,
    XRNM_OPTION_NUM_SEND_CHANNELS_HINT   = 0x0000000F,
    XRNM_OPTION_MAX_NUM_SEND_CHANNELS    = 0x00000010,
    XRNM_OPTION_MAX_NUM_RECV_CHANNELS    = 0x00000011,
    XRNM_OPTION_MAX_NUM_QUEUED_SENDS     = 0x00000012,
    XRNM_OPTION_MAX_NUM_QUEUED_BYTES     = 0x00000013,
    XRNM_OPTION_MAX_MESSAGE_SIZE         = 0x00000014,
    XRNM_OPTION_MAX_QUEUED_LINK_REQUESTS = 0x00000015,
    XRNM_OPTION_RTT_SAMPLE_TIME          = 0x00000016,
    XRNM_OPTION_PROCESS_RECEIPT_PERIOD   = 0x00000017,
    XRNM_OPTION_MIN_DATA_RETRY_TIMEOUT   = 0x00000018,
    XRNM_OPTION_MAX_DATA_RETRY_TIMEOUT   = 0x00000019,
} XRNM_OPTION, * PXRNM_OPTION;

typedef enum XRNM_SEND_BUFFER_TYPE
{
    XRNM_SEND_BUFFER_TYPE_SEND,
    XRNM_SEND_BUFFER_TYPE_CREATESENDCHANNEL,
    XRNM_SEND_BUFFER_TYPE_TERMINATESENDCHANNEL
} XRNM_SEND_BUFFER_TYPE, * PXRNM_SEND_BUFFER_TYPE;


/*
 * Xrnm default channel macros and constants
 */

// Macros for making default channel IDs, use XrnmGetDefaultChannelComponents
// to convert back to channel type and index.
#define XrnmMakeDefaultChannelIdBase(ChannelType, Index)        (((0x7F - (DWORD) (ChannelType)) << 24) | (0x00FFFFFE - ((DWORD) (Index))))
#define XrnmMakeDefaultSendChannelId(ChannelType, Index)        ((XRNM_CHANNEL_ID) (0x00000000 | XrnmMakeDefaultChannelIdBase(ChannelType, Index)))
#define XrnmMakeDefaultReceiveChannelId(ChannelType, Index)     ((XRNM_CHANNEL_ID) (0x80000000 | XrnmMakeDefaultChannelIdBase(ChannelType, Index)))

// First default send channel identities for each type
static const XRNM_CHANNEL_ID XRNM_DEFAULT_GAMEDATA_SEND_CHANNEL_ID = XrnmMakeDefaultSendChannelId(XRNM_CHANNEL_TYPE_GAMEDATA, 0);
static const XRNM_CHANNEL_ID XRNM_DEFAULT_CHAT_SEND_CHANNEL_ID     = XrnmMakeDefaultSendChannelId(XRNM_CHANNEL_TYPE_CHAT, 0);

// First default receive channel identities for each type
static const XRNM_CHANNEL_ID XRNM_DEFAULT_GAMEDATA_RECEIVE_CHANNEL_ID = XrnmMakeDefaultReceiveChannelId(XRNM_CHANNEL_TYPE_GAMEDATA, 0);
static const XRNM_CHANNEL_ID XRNM_DEFAULT_CHAT_RECEIVE_CHANNEL_ID     = XrnmMakeDefaultReceiveChannelId(XRNM_CHANNEL_TYPE_CHAT, 0);


/*
 * Constant limits for Xrnm
 */

static const DWORD XRNM_LOWEST_SEND_PRIORITY  = 0;
static const DWORD XRNM_HIGHEST_SEND_PRIORITY = 15;


/*
 * Flags for Xrnm
 */


//
// Flags for XrnmCreateSendChannel
//

// Never coalesce channel creation with other outgoing data
static const DWORD XRNM_FLAG_CREATE_SEND_CHANNEL_COALESCE_NEVER   = 0x00000010;

// Coalesce channel creation if outgoing sends are already queued (default)
static const DWORD XRNM_FLAG_CREATE_SEND_CHANNEL_COALESCE_NODELAY = 0x00000000;

// Retain channel creation for short period in attempt to coalesce
static const DWORD XRNM_FLAG_CREATE_SEND_CHANNEL_COALESCE_DELAY   = 0x00000020;

// Retain channel creation until it can be coalesced
static const DWORD XRNM_FLAG_CREATE_SEND_CHANNEL_COALESCE_ALWAYS  = 0x00000040;

// Don't take a copy of the create data buffer(s), generate an
// XRNM_EVENT_TYPE_SEND_BUFFER_RETURNED event when data no longer needed.
static const DWORD XRNM_FLAG_CREATE_SEND_CHANNEL_DONT_COPY        = 0x00000080;



//
// Flags for XrnmTerminateSendChannel
//
 
// Never coalesce channel termination with other outgoing data
static const DWORD XRNM_FLAG_TERMINATE_SEND_CHANNEL_COALESCE_NEVER   = 0x00000010;

// Coalesce channel termination if outgoing sends are already queued (default)
static const DWORD XRNM_FLAG_TERMINATE_SEND_CHANNEL_COALESCE_NODELAY = 0x00000000;

// Retain channel termination for short period in attempt to coalesce
static const DWORD XRNM_FLAG_TERMINATE_SEND_CHANNEL_COALESCE_DELAY   = 0x00000020;

// Retain channel termination until it can be coalesced
static const DWORD XRNM_FLAG_TERMINATE_SEND_CHANNEL_COALESCE_ALWAYS  = 0x00000040;

// Don't take a copy of the terminate data buffer(s), generate an
// XRNM_EVENT_TYPE_SEND_BUFFER_RETURNED event when data no longer needed.
static const DWORD XRNM_FLAG_TERMINATE_SEND_CHANNEL_DONT_COPY        = 0x00000080;



//
// Flags for XrnmSend
//

// Transmit best-effort, do not resend if dropped (default)
static const DWORD XRNM_FLAG_SEND_NONRELIABLE      = 0x00000000;

// Ensure message is delivered, resending if necessary
static const DWORD XRNM_FLAG_SEND_RELIABLE         = 0x00000001;

// Deliver message as soon as it arrives, regardless of send order (default)
static const DWORD XRNM_FLAG_SEND_NONSEQUENTIAL    = 0x00000000;

// Deliver message only if no earlier sequential sends could be delivered on channel
static const DWORD XRNM_FLAG_SEND_SEQUENTIAL       = 0x00000002;

// Acknowledge as soon as packet is received
static const DWORD XRNM_FLAG_SEND_ACK_IMMEDIATELY  = 0x00000004;

// Acknowledge after normal delay (default)
static const DWORD XRNM_FLAG_SEND_ACK_NORMAL       = 0x00000000;

// Acknowledge after extended delay
static const DWORD XRNM_FLAG_SEND_ACK_LAZY         = 0x00000008;

// Never coalesce send with others
static const DWORD XRNM_FLAG_SEND_COALESCE_NEVER   = 0x00000010;

// Coalesce send if multiple sends are already queued (default)
static const DWORD XRNM_FLAG_SEND_COALESCE_NODELAY = 0x00000000;

// Retain send for short period in attempt to coalesce
static const DWORD XRNM_FLAG_SEND_COALESCE_DELAY   = 0x00000020;

// Retain send until it can be coalesced
static const DWORD XRNM_FLAG_SEND_COALESCE_ALWAYS  = 0x00000040;

// Don't take a copy of the send data buffer(s), generate an
// XRNM_EVENT_TYPE_SEND_BUFFER_RETURNED event when data no longer needed.
static const DWORD XRNM_FLAG_SEND_DONT_COPY        = 0x00000080;

// Generate receipt at the point the message is committed to the network
static const DWORD XRNM_FLAG_SEND_RECEIPT_TRANSMIT = 0x00000100;

// Generate receipt when packet is acknowledged
static const DWORD XRNM_FLAG_SEND_RECEIPT_RECEIVE  = 0x00000200;

// Generate receipt when message is processed
static const DWORD XRNM_FLAG_SEND_RECEIPT_PROCESS  = 0x00000400;



//
// Flags for XrnmCancelSends
//

// Cancel if CancelMask == CancelValue
static const DWORD XRNM_FLAG_CANCEL_SENDS_TEST_EQUALITY   = 0x00000001;

// Cancel if (CancelMask & CancelValue) != 0 
static const DWORD XRNM_FLAG_CANCEL_SENDS_TEST_AND        = 0x00000002;

// Cancel if (CancelMask | CancelValue) != 0
static const DWORD XRNM_FLAG_CANCEL_SENDS_TEST_OR         = 0x00000004;

// Cancel if CancelMask != CancelValue
static const DWORD XRNM_FLAG_CANCEL_SENDS_TEST_INEQUALITY = 0x00000008;


//
// Flags for XrnmGetAllChannels
//

// Include XRNM_CHANNEL_TYPE_GAMEDATA channels.
static const DWORD XRNM_FLAG_GET_ALL_CHANNELS_TYPE_GAMEDATA = 0x00000001;

// Include XRNM_CHANNEL_TYPE_CHAT channels.
static const DWORD XRNM_FLAG_GET_ALL_CHANNELS_TYPE_CHAT     = 0x00000002;

// Get send channels.
static const DWORD XRNM_FLAG_GET_ALL_CHANNELS_SEND          = 0x10000000;

// Get receive channels.
static const DWORD XRNM_FLAG_GET_ALL_CHANNELS_RECEIVE       = 0x20000000;

// Include default channels.
static const DWORD XRNM_FLAG_GET_ALL_CHANNELS_DEFAULT       = 0x40000000;

// Include non-default channels.
static const DWORD XRNM_FLAG_GET_ALL_CHANNELS_NONDEFAULT    = 0x80000000;

// Include all channel types
static const DWORD XRNM_FLAG_GET_ALL_CHANNELS_TYPE_ALL = XRNM_FLAG_GET_ALL_CHANNELS_TYPE_GAMEDATA |
                                                         XRNM_FLAG_GET_ALL_CHANNELS_TYPE_CHAT;



//
// Flags supplied in XRNM_EVENT_DATA_RECEIVED dwFlags field.
//

// Message was transmitted with reliability enabled
static const DWORD XRNM_FLAG_RECEIVE_RELIABLE        = 0x00000001;

// Message was delivered with sequencing information
static const DWORD XRNM_FLAG_RECEIVE_SEQUENTIAL      = 0x00000002;

// Message was delivered on a default channel
static const DWORD XRNM_FLAG_RECEIVE_DEFAULT_CHANNEL = 0x00000004;

// Message was fragmented during transmission
static const DWORD XRNM_FLAG_RECEIVE_FRAGMENTED      = 0x00000008;



//
// Flags supplied in XRNM_EVENT_SEND_BUFFER_RETURNED dwFlags field.
//

// Buffer was sent on a default channel
static const DWORD XRNM_FLAG_SEND_BUFFER_DEFAULT_CHANNEL = 0x00000001;



//
// Flags supplied in XRNM_EVENT_RECEIPT dwReceiptFlags field.
//

// Message was sent on a default channel
static const DWORD XRNM_FLAG_RECEIPT_DEFAULT_CHANNEL = 0x00000001;

// Message was fragmented during transmission
static const DWORD XRNM_FLAG_RECEIPT_SEND_FRAGMENTED = 0x00000002;



//
// Flags supplied in XRNM_EVENT_ALERT dwReceiptFlags field.
//

// Channel ID referenced is a default channel
static const DWORD XRNM_FLAG_ALERT_DEFAULT_CHANNEL = 0x00000001;



/*
 * Common structures for XRNM
 */

#pragma pack(push, 1)

typedef struct XRNM_ADDRESS
{
    IN_ADDR     ina;   // IPv4 address in network byte order (big endian)
    WORD        wPort; // Port number in network byte order (big endian)
} XRNM_ADDRESS, *PXRNM_ADDRESS;

#pragma pack(pop, 1)


typedef struct XRNM_SEND_BUFFER
{
    BYTE *  pbyData;    // Pointer to buffer
    DWORD   dwDataSize; // Size of buffer
} XRNM_SEND_BUFFER, *PXRNM_SEND_BUFFER;


typedef struct XRNM_SEND_QUEUE_OPTIONS
{
    DWORD   dwPriority;    // Relative urgency value between XRNM_LOWEST_SEND_PRIORITY and XRNM_HIGHEST_SEND_PRIORITY
    DWORD   dwCancelValue; // Cancel value to be interpreted by XrnmCancelSends
    DWORD   dwTimeout;     // Max amount of time to remain in queue without being sent, in ms
} XRNM_SEND_QUEUE_OPTIONS, *PXRNM_SEND_QUEUE_OPTIONS;


typedef struct XRNM_DEFAULT_CHANNELS
{
    WORD    NumChannels[XRNM_NUM_CHANNEL_TYPES]; // Array of default channel counts for each type
} XRNM_DEFAULT_CHANNELS, *PXRNM_DEFAULT_CHANNELS;


typedef struct XRNM_ALERT_SETTINGS
{
    ULONGLONG   qwTriggerThreshold;    // The threshold at which the alert is triggered
    ULONGLONG   qwResetThreshold;      // The threshold at which a triggered alert is reset for future triggering
    DWORD       dwMaxTriggerFrequency; // The time in ms that must elapse before alert triggers again, 0xFFFFFFFF = one-shot
    DWORD       dwSampleFrequency;     // The frequency in ms at which the alert value is analyzed, or zero for default
    BOOL        fRetrigger;            // TRUE to generate another event at dwMaxTriggerFrequency while alert remains triggered, FALSE otherwise
} XRNM_ALERT_SETTINGS, * PXRNM_ALERT_SETTINGS;



/*
 * Event structures that can be indicated from Xrnm
 */

typedef struct XRNM_EVENT
{
    DWORD                   dwEventSize;            // Size of the complete event structure
    XRNM_EVENT_TYPE         EventType;              // Type of event structure to which this should be cast
} XRNM_EVENT, * PXRNM_EVENT;

typedef struct XRNM_EVENT_INBOUND_LINK_REQUEST
{
    DWORD                   dwEventSize;            // Size of the complete event structure
    XRNM_EVENT_TYPE         EventType;              // XRNM_EVENT_TYPE_INBOUND_LINK_REQUEST
    XRNM_HANDLE             hEndpoint;              // Handle to endpoint on which request was received
    ULONG_PTR               ulpEndpointUserData;    // User data value associated with endpoint
    XRNM_ADDRESS            RemoteAddress;          // Remote address for inbound link
    const BYTE *            pbyLinkRequestData;     // Link request data specified by remote client
    DWORD                   dwLinkRequestDataSize;  // Size in bytes of link request data
    XRNM_DEFAULT_CHANNELS   DefaultReceiveChannels; // Structure describing default receive channels to be created with this link
} XRNM_EVENT_INBOUND_LINK_REQUEST, * PXRNM_EVENT_INBOUND_LINK_REQUEST;

typedef struct XRNM_EVENT_LINK_STATUS_UPDATE
{
    DWORD                   dwEventSize;            // Size of the complete event structure
    XRNM_EVENT_TYPE         EventType;              // XRNM_EVENT_TYPE_LINK_STATUS_UPDATE
    XRNM_HANDLE             hLink;                  // Handle to link
    ULONG_PTR               ulpLinkUserData;        // User data value associated with link
    XRNM_STATUS             OldStatus;              // XRNM_STATUS_ACTIVATING, ACTIVE or TERMINATING
    XRNM_STATUS             NewStatus;              // XRNM_STATUS_ACTIVE, TERMINATING or TERMINATED
    HRESULT                 hrNewStatusInfo;        // Extended info on new status code
    const BYTE *            pbyReplyData;           // Reply data associated with state change (if any)
    DWORD                   dwReplyDataSize;        // Size of reply data
    XRNM_DEFAULT_CHANNELS   DefaultReceiveChannels; // Structure describing default receive channels created by remote side
} XRNM_EVENT_LINK_STATUS_UPDATE, * PXRNM_EVENT_LINK_STATUS_UPDATE;

typedef struct XRNM_EVENT_SEND_CHANNEL_TERMINATED
{
    DWORD                   dwEventSize;            // Size of the complete event structure
    XRNM_EVENT_TYPE         EventType;              // XRNM_EVENT_TYPE_SEND_CHANNEL_TERMINATED
    XRNM_HANDLE             hLink;                  // Handle to link on which channel resides
    ULONG_PTR               ulpLinkUserData;        // User data value associated with link
    XRNM_CHANNEL_ID         idSendChannel;          // Identity of channel terminated
    ULONG_PTR               ulpChannelUserData;     // User data pointer associated with channel
    XRNM_CHANNEL_TYPE       ChannelType;            // Send channel's type
    HRESULT                 hrInfo;                 // Extended info on reason for termination
} XRNM_EVENT_SEND_CHANNEL_TERMINATED, * PXRNM_EVENT_SEND_CHANNEL_TERMINATED;

typedef struct XRNM_EVENT_RECEIVE_CHANNEL_CREATED
{
    DWORD                   dwEventSize;            // Size of the complete event structure
    XRNM_EVENT_TYPE         EventType;              // XRNM_EVENT_TYPE_RECEIVE_CHANNEL_CREATED
    XRNM_HANDLE             hLink;                  // Handle to link on which channel has been created
    ULONG_PTR               ulpLinkUserData;        // User data value associated with link
    XRNM_CHANNEL_ID         idReceiveChannel;       // Identity of receive channel created
    XRNM_CHANNEL_TYPE       ChannelType;            // One of the XRNM_CHANNEL_TYPE values
    const BYTE *            pbyCreateData;          // Data specified by remote side when creating channel
    DWORD                   dwCreateDataSize;       // Size of above data
} XRNM_EVENT_RECEIVE_CHANNEL_CREATED, * PXRNM_EVENT_RECEIVE_CHANNEL_CREATED;

typedef struct XRNM_EVENT_RECEIVE_CHANNEL_TERMINATED
{
    DWORD                   dwEventSize;            // Size of the complete event structure
    XRNM_EVENT_TYPE         EventType;              // XRNM_EVENT_TYPE_RECEIVE_CHANNEL_TERMINATED
    XRNM_HANDLE             hLink;                  // Handle to link associated with receive channel
    ULONG_PTR               ulpLinkUserData;        // User data value associated with link
    XRNM_CHANNEL_ID         idReceiveChannel;       // Identity of channel terminated
    ULONG_PTR               ulpChannelUserData;     // User data value associated with channel
    XRNM_CHANNEL_TYPE       ChannelType;            // Receive channel's type
    const BYTE *            pbyTerminateData;       // Data specified by remote side when terminating channel
    DWORD                   dwTerminateDataSize;    // Size of above data
    HRESULT                 hrInfo;                 // Extended info on reason for termination
} XRNM_EVENT_RECEIVE_CHANNEL_TERMINATED, * PXRNM_EVENT_RECEIVE_CHANNEL_TERMINATED;

typedef struct XRNM_EVENT_DATA_RECEIVED
{
    DWORD                   dwEventSize;            // Size of the complete event structure
    XRNM_EVENT_TYPE         EventType;              // XRNM_EVENT_TYPE_DATA_RECEIVED
    XRNM_HANDLE             hLink;                  // Handle to link over which the data arrived
    ULONG_PTR               ulpLinkUserData;        // User data value associated with above link
    XRNM_CHANNEL_ID         idReceiveChannel;       // Identity of channel over which the data arrived
    ULONG_PTR               ulpChannelUserData;     // User data value associated with receive channel
    XRNM_CHANNEL_TYPE       ChannelType;            // Receive channel's type
    const BYTE *            pbyData;                // Data received
    DWORD                   dwDataSize;             // Size of above data
    DWORD                   dwFlags;                // Flags describing receive (see XRNM_FLAG_RECEIVE_*)
} XRNM_EVENT_DATA_RECEIVED, * PXRNM_EVENT_DATA_RECEIVED;

typedef struct XRNM_EVENT_SEND_BUFFER_RETURNED
{
    DWORD                   dwEventSize;            // Size of the complete event structure
    XRNM_EVENT_TYPE         EventType;              // XRNM_EVENT_TYPE_SEND_BUFFER_RETURNED
    XRNM_HANDLE             hLink;                  // Handle to link used to send the buffer
    ULONG_PTR               ulpLinkUserData;        // User data value associated with above link
    XRNM_CHANNEL_ID         idSendChannel;          // Identity of channel used to send the buffer
    ULONG_PTR               ulpChannelUserData;     // User data value associated with send channel
    XRNM_CHANNEL_TYPE       ChannelType;            // Send channel's type
    ULONG_PTR               ulpSendUserData;        // User data value originally associated with send
    XRNM_SEND_BUFFER_TYPE   SendBufferType;         // Type of send buffer being returned
    XRNM_SEND_BUFFER *      pBuffers;               // Send buffer
    DWORD                   dwNumBuffers;           // Number of send buffers
    DWORD                   dwFlags;                // Flags describing send buffer (see XRNM_FLAG_SEND_BUFFER_*)
} XRNM_EVENT_SEND_BUFFER_RETURNED, * PXRNM_EVENT_SEND_BUFFER_RETURNED;

typedef struct XRNM_EVENT_RECEIPT
{
    DWORD                   dwEventSize;            // Size of the complete event structure
    XRNM_EVENT_TYPE         EventType;              // XRNM_EVENT_TYPE_RECEIPT
    XRNM_HANDLE             hLink;                  // Handle to link used in send operation
    ULONG_PTR               ulpLinkUserData;        // User data value associated with above link
    XRNM_CHANNEL_ID         idSendChannel;          // Identity of channel used in send operation
    ULONG_PTR               ulpChannelUserData;     // User data value associated with above channel
    XRNM_CHANNEL_TYPE       ChannelType;            // Send channel's type
    XRNM_RECEIPT_TYPE       ReceiptType;            // XRNM_RECEIPT_TYPE_TRANSMIT, RECEIVE or PROCESS
    HRESULT                 hrInfo;                 // Describes result of action associated with receipt
    XRNM_SEND_QUEUE_OPTIONS SendQueueOptions;       // Send queuing options originally specified for send
    ULONG_PTR               ulpSendUserData;        // User data value associated with the send
    DWORD                   dwSendFlags;            // Send flags originally specified for send
    DWORD                   dwReceiptFlags;         // Flags describing receipt (see XRNM_FLAG_RECEIPT_*)
} XRNM_EVENT_RECEIPT, * PXRNM_EVENT_RECEIPT;

typedef struct XRNM_EVENT_ALERT
{
    DWORD                   dwEventSize;            // Size of the complete event structure
    XRNM_EVENT_TYPE         EventType;              // XRNM_EVENT_TYPE_ALERT
    XRNM_HANDLE             hEndpoint;              // Handle to endpoint associated with alert
    ULONG_PTR               ulpEndpointUserData;    // User data value associated with above endpoint
    XRNM_HANDLE             hLink;                  // Handle to link associated with alert, or NULL if none
    ULONG_PTR               ulpLinkUserData;        // User data value associated with above link
    XRNM_CHANNEL_ID         idChannel;              // Identity of channel associated with alert, or XRNM_INVALID_CHANNEL_ID if none
    ULONG_PTR               ulpChannelUserData;     // User data value associated with above channel
    XRNM_ALERT_TYPE         AlertType;              // Type of alert
    ULONGLONG               qwValue;                // Value that triggered alert
    XRNM_ALERT_SETTINGS     AlertSettings;          // The current settings for the alert
    DWORD                   dwFlags;                // Flags describing alert (see XRNM_FLAG_ALERT_*)
} XRNM_EVENT_ALERT, * PXRNM_EVENT_ALERT;



#pragma pack(pop)



/*
 * Functions for Xrnm
 */

HRESULT
WINAPI
XrnmCreateEndpoint(
    IN  const XRNM_ADDRESS *                pLocalAddress               OPTIONAL,
    IN  ULONG_PTR                           ulpEndpointUserData         OPTIONAL,
    OUT XRNM_HANDLE *                       phEndpoint
    );


HRESULT
WINAPI
XrnmAllowInboundLinkRequests(
    IN  XRNM_HANDLE                         hEndpoint,
    IN  BOOL                                fAllow
    );


HRESULT
WINAPI
XrnmCreateOutboundLink(
    IN  XRNM_HANDLE                         hEndpoint,
    IN  const XRNM_ADDRESS *                pRemoteAddress,
    IN  const BYTE *                        pbyLinkRequestData          OPTIONAL,
    IN  DWORD                               dwLinkRequestDataSize       OPTIONAL,
    IN  const XRNM_DEFAULT_CHANNELS *       pDefaultSendChannels        OPTIONAL,
    IN  ULONG_PTR                           ulpLinkUserData             OPTIONAL,
    OUT XRNM_HANDLE *                       phLink
    );


HRESULT
WINAPI
XrnmCreateInboundLink(
    IN  XRNM_EVENT_INBOUND_LINK_REQUEST *   pEventInboundLinkRequest,
    IN  const BYTE *                        pbyReplyData                OPTIONAL,
    IN  DWORD                               dwReplyDataSize             OPTIONAL,
    IN  const XRNM_DEFAULT_CHANNELS *       pDefaultSendChannels        OPTIONAL,
    IN  ULONG_PTR                           ulpLinkUserData             OPTIONAL,
    OUT XRNM_HANDLE *                       phLink
    );


HRESULT
WINAPI
XrnmDenyInboundLink(
    IN  XRNM_EVENT_INBOUND_LINK_REQUEST *   pEventInboundLinkRequest,
    IN  const BYTE *                        pbyReplyData                OPTIONAL,
    IN  DWORD                               dwReplyDataSize             OPTIONAL
    );


HRESULT
WINAPI
XrnmTerminateLink(
    IN  XRNM_HANDLE                         hLink
    );


HRESULT
WINAPI
XrnmCreateSendChannel(
    IN  XRNM_HANDLE                         hLink,
    IN  XRNM_CHANNEL_TYPE                   ChannelType,
    IN  const XRNM_SEND_BUFFER *            pCreateDataBuffers          OPTIONAL,
    IN  DWORD                               dwNumCreateDataBuffers      OPTIONAL,
    IN  ULONG_PTR                           ulpCreateBuffersUserData    OPTIONAL,
    IN  ULONG_PTR                           ulpChannelUserData          OPTIONAL,
    IN  DWORD                               dwFlags                     OPTIONAL,
    OUT XRNM_CHANNEL_ID *                   pidSendChannel
    );


HRESULT
WINAPI
XrnmTerminateSendChannel(
    IN  XRNM_HANDLE                         hLink,
    IN  XRNM_CHANNEL_ID                     idSendChannel,
    IN  const XRNM_SEND_BUFFER *            pTerminateDataBuffers       OPTIONAL,
    IN  DWORD                               dwNumTerminateDataBuffers   OPTIONAL,
    IN  ULONG_PTR                           ulpTerminateBuffersUserData OPTIONAL,
    IN  DWORD                               dwFlags                     OPTIONAL
    );


HRESULT
WINAPI
XrnmSend(
    IN  XRNM_HANDLE                         hLink,
    IN  XRNM_CHANNEL_ID                     idSendChannel,
    IN  const XRNM_SEND_BUFFER *            pBuffers,
    IN  DWORD                               dwNumBuffers,
    IN  const XRNM_SEND_QUEUE_OPTIONS *     pSendQueueOptions           OPTIONAL,
    IN  ULONG_PTR                           ulpSendUserData             OPTIONAL,
    IN  DWORD                               dwFlags                     OPTIONAL
    );


HRESULT
WINAPI
XrnmFlushSends(
    IN  XRNM_HANDLE                         hLink,
    IN  XRNM_CHANNEL_ID                     idSendChannel               OPTIONAL
    );


HRESULT
WINAPI
XrnmCancelSends(
    IN  XRNM_HANDLE                         hLink,
    IN  XRNM_CHANNEL_ID                     idSendChannel               OPTIONAL,
    IN  DWORD                               dwCancelMaskValue,
    IN  DWORD                               dwFlags                     OPTIONAL,
    OUT DWORD *                             pdwNumSendsCancelled        OPTIONAL
    );


HRESULT
WINAPI
XrnmGetEvent(
    IN  XRNM_HANDLE                         hPoll                       OPTIONAL,
    IN  DWORD                               dwTimeout                   OPTIONAL,
    OUT XRNM_EVENT **                       ppEvent
    );


HRESULT
WINAPI
XrnmReturnEvent(
    IN  XRNM_EVENT *                        pEvent
    );


HRESULT
WINAPI
XrnmCloseHandle(
    IN  XRNM_HANDLE                         hToClose
    );


HRESULT
WINAPI
XrnmGetHandleStatus(
    IN  XRNM_HANDLE                         h,
    OUT XRNM_STATUS *                       pStatus
    );


HRESULT
WINAPI
XrnmSetHandleUserData(
    IN  XRNM_HANDLE                         h,
    IN  ULONG_PTR                           ulpUserData
    );


HRESULT
WINAPI
XrnmGetHandleUserData(
    IN  XRNM_HANDLE                         h,
    OUT ULONG_PTR *                         pulpUserData
    );


HRESULT
WINAPI
XrnmGetEndpointFromLink(
    IN  XRNM_HANDLE                         hLink,
    OUT XRNM_HANDLE *                       phEndpoint
    );


HRESULT
WINAPI
XrnmGetAllLinks(
    IN     XRNM_HANDLE                      hEndpoint,
    IN OUT XRNM_HANDLE *                    phLinks                     OPTIONAL,
    IN OUT DWORD *                          pdwNumLinks
    );


HRESULT
WINAPI
XrnmGetLocalAddressForEndpoint(
    IN  XRNM_HANDLE                         hEndpoint,
    OUT XRNM_ADDRESS *                      pAddress
    );


HRESULT
WINAPI
XrnmGetRemoteAddressForLink(
    IN  XRNM_HANDLE                         hLink,
    OUT XRNM_ADDRESS *                      pAddress
    );


HRESULT
WINAPI
XrnmSetChannelUserData(
    IN  XRNM_HANDLE                         hLink,
    IN  XRNM_CHANNEL_ID                     idChannel,
    IN  ULONG_PTR                           ulpUserData
    );


HRESULT
WINAPI
XrnmGetChannelUserData(
    IN  XRNM_HANDLE                         hLink,
    IN  XRNM_CHANNEL_ID                     idChannel,
    OUT ULONG_PTR *                         pulpUserData
    );


HRESULT
WINAPI
XrnmGetAllChannels(
    IN     XRNM_HANDLE                      hLink,
    IN OUT XRNM_CHANNEL_ID *                pidChannels                 OPTIONAL,
    IN OUT DWORD *                          pdwNumChannels,
    IN     DWORD                            dwFlags                     OPTIONAL
    );


HRESULT
WINAPI
XrnmGetDefaultChannelComponents(
    IN  XRNM_HANDLE                         hLink,
    IN  XRNM_CHANNEL_ID                     idChannel,
    OUT XRNM_CHANNEL_TYPE *                 pChannelType                OPTIONAL,
    OUT DWORD *                             pdwIndex                    OPTIONAL,
    OUT BOOL *                              pfReceive                   OPTIONAL
    );


HRESULT
WINAPI
XrnmQueryInfo(
    IN     XRNM_HANDLE                      h,
    IN     XRNM_CHANNEL_ID                  idChannel                   OPTIONAL,
    IN     XRNM_INFO_TYPE                   InfoType,
    IN OUT void *                           pvValueBuffer,
    IN     DWORD                            dwValueBufferSize
    );


HRESULT
WINAPI
XrnmSetAlertSettings(
    IN  XRNM_HANDLE                         h,
    IN  XRNM_CHANNEL_ID                     idChannel                   OPTIONAL,
    IN  XRNM_ALERT_TYPE                     AlertType,
    IN  const XRNM_ALERT_SETTINGS *         pAlertSettings
    );


HRESULT
WINAPI
XrnmGetAlertSettings(
    IN  XRNM_HANDLE                         h,
    IN  XRNM_CHANNEL_ID                     idChannel                   OPTIONAL,
    IN  XRNM_ALERT_TYPE                     AlertType,
    OUT XRNM_ALERT_SETTINGS *               pAlertSettings              OPTIONAL,
    OUT BOOL *                              pfCurrentlyTriggered        OPTIONAL
    );


HRESULT
WINAPI
XrnmSetOpt(
    IN  XRNM_HANDLE                         h,
    IN  XRNM_CHANNEL_ID                     idChannel                   OPTIONAL,
    IN  XRNM_OPTION                         Option,
    IN  void *                              pvOptionData,
    IN  DWORD                               dwOptionDataSize
    );


HRESULT
WINAPI
XrnmGetOpt(
    IN     XRNM_HANDLE                      h,
    IN     XRNM_CHANNEL_ID                  idChannel                   OPTIONAL,
    IN     XRNM_OPTION                      Option,
    IN OUT void *                           pvOptionData                OPTIONAL,
    IN OUT DWORD *                          pdwOptionDataSize
    );



#ifdef __cplusplus
}
#endif // end if defined __cplusplus

#endif // end if not defined __XRNM_H__
