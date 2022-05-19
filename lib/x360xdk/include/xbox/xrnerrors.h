/*
 * Copyright (c) Microsoft Corporation
 *
 * Defines the error codes for XRN
 */

#ifndef __XRNERRORS_H__
#define __XRNERRORS_H__


#define FACILITY_XRN        0x7A
#define ERRBASE_XRN         0x1000

#ifndef MAKE_HRESULT
#define MAKE_HRESULT(sev,fac,code) \
    ((HRESULT) (((unsigned long)(sev) << 31) | ((unsigned long)(fac) << 16) | ((unsigned long)(code))) )
#endif
    
#define MAKE_XRNRESULTSUCCESS(code)     MAKE_HRESULT(0, FACILITY_XRN, (ERRBASE_XRN + (code)))
#define MAKE_XRNRESULTERROR(code)       MAKE_HRESULT(1, FACILITY_XRN, (ERRBASE_XRN + (code)))


//
// Success codes
//

#define XRN_S_OK                                S_OK

// No events currently available
#define XRN_S_NOEVENTS                          S_FALSE


//
// Failure codes
//

// Operation failed due to lack of memory
#define XRN_E_OUTOFMEMORY                       E_OUTOFMEMORY

// Insufficient buffer space was available to return the necessary data
// Repeat the call with a larger buffer space
#define XRN_E_INSUFFICIENTBUFFER                MAKE_XRNRESULTERROR(0x01)

// Network interface is reporting its not ready
#define XRN_E_NETNOTREADY                       MAKE_XRNRESULTERROR(0x02)

// Network interface has failed
#define XRN_E_NETDOWN                           MAKE_XRNRESULTERROR(0x03)

// Either a bind attempt failed as the local address is already in use
// or a link can't be created because one already exists to that remote address
#define XRN_E_ADDRESSINUSE                      MAKE_XRNRESULTERROR(0x04)

// An application or system defined limit was reached preventing the operation completing
#define XRN_E_LIMITREACHED                      MAKE_XRNRESULTERROR(0x05)

// Send data supplied to a create or deny link method was too large 
#define XRN_E_DATATOOLARGE                      MAKE_XRNRESULTERROR(0x06)

// There was no reponse from the remote side
#define XRN_E_NORESPONSE                        MAKE_XRNRESULTERROR(0x07)

// Far side denied an incoming connection
#define XRN_E_DENIED                            MAKE_XRNRESULTERROR(0x08)

// Attempted operation was invalid with current state or supplied parameters
#define XRN_E_INVALIDOPERATION                  MAKE_XRNRESULTERROR(0x09)

// An undefined network error occurred
#define XRN_E_NETGENERIC                        MAKE_XRNRESULTERROR(0x0A)

// An undefined error occurred
#define XRN_E_GENERIC                           MAKE_XRNRESULTERROR(0x0B)

// A packet was dropped on the wire
#define XRN_E_PKTDROPPED                        MAKE_XRNRESULTERROR(0x0C)

// A packet with malformed data was received
#define XRN_E_BADPKT                            MAKE_XRNRESULTERROR(0x0D)

// A duplicated handle was supplied
#define XRN_E_DUPLICATEHANDLE                   MAKE_XRNRESULTERROR(0x0E)

// Bad channel identity was used
#define XRN_E_BADCHANNEL                        MAKE_XRNRESULTERROR(0x0F)

// Channel was terminated 
#define XRN_E_CHANNELTERMINATED                 MAKE_XRNRESULTERROR(0x10)

// Link was remotely terminated
#define XRN_E_REMOTETERMINATE                   MAKE_XRNRESULTERROR(0x11)

// Link was locally terminated
#define XRN_E_LOCALTERMINATE                    MAKE_XRNRESULTERROR(0x12)

// Invalid address specified
#define XRN_E_INVALIDADDRESS                    MAKE_XRNRESULTERROR(0x13)

// Remote side forcibly closed socket 
#define XRN_E_CONNRESET                         MAKE_XRNRESULTERROR(0x14)

// Operation was cancelled by the user
#define XRN_E_USERCANCEL                        MAKE_XRNRESULTERROR(0x15)

// A timeout specified by a user expired
#define XRN_E_USERTIMEOUT                       MAKE_XRNRESULTERROR(0x16)

// Session was removed
#define XRN_E_REMOVED                           MAKE_XRNRESULTERROR(0x17)


#endif // end if not defined __XRNERRORS_H__
