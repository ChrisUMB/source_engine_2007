

//
//
// Xbox Debug Monitor APIs - for use on PC
// Copyright Microsoft Corporation 2000-2005. All Rights Reserved.
//
//
#ifndef __XBDM_H__
#define __XBDM_H__

#define XBDMAPI

#include <XeCtx.h>



#ifdef __cplusplus
extern "C" {
#endif


/*
HPGOMODULE - used to refer to the run-time state of a PGO-instrumented
module.
*/
DECLARE_HANDLE(HPGOMODULE);

#define DMHRAPI XBDMAPI HRESULT __stdcall

// Notification types
#define DM_NONE 0
#define DM_BREAK 1
#define DM_DEBUGSTR 2
#define DM_EXEC 3
#define DM_SINGLESTEP 4
#define DM_MODLOAD 5
#define DM_MODUNLOAD 6
#define DM_CREATETHREAD 7
#define DM_DESTROYTHREAD 8
#define DM_EXCEPTION 9
#define DM_ASSERT 12
#define DM_DATABREAK 13
#define DM_RIP 14
#define DM_SECTIONLOAD 16
#define DM_SECTIONUNLOAD 17
#define DM_FIBER 18
#define DM_STACKTRACE 19
#define DM_BUGCHECK 20
#define DM_ASSERTION_FAILURE 21
#define DM_PGO_MODULE_STARTUP 22
#define DM_NOTIFYMAX 22

#define DM_NOTIFICATIONMASK 0xffffff
#define DM_STOPTHREAD 0x80000000

typedef DWORD (__stdcall *PDM_NOTIFY_FUNCTION)(ULONG dwNotification, DWORD dwParam);



// Break notification structure
typedef struct _DMN_BREAK {
    PVOID Address;
    DWORD ThreadId;
} DMN_BREAK, *PDMN_BREAK;

// Data breakpoint notification structure {
typedef struct _DMN_DATABREAK {
    PVOID Address;
    DWORD ThreadId;
    DWORD BreakType;
    PVOID DataAddress;
} DMN_DATABREAK, *PDMN_DATABREAK;

// Debugstr notification structure
typedef struct _DMN_DEBUGSTR {
    DWORD ThreadId;
    DWORD Length;
    LPCSTR String;
} DMN_DEBUGSTR, *PDMN_DEBUGSTR;

// execution notification values
#define DMN_EXEC_STOP 0
#define DMN_EXEC_START 1
#define DMN_EXEC_REBOOT 2
#define DMN_EXEC_PENDING 3
#define DMN_EXEC_REBOOT_TITLE 4
#define DMN_EXEC_PENDING_TITLE 5

// Module load notification structure
typedef struct _DMN_MODLOAD {
    char Name[MAX_PATH];
    PVOID BaseAddress;
    ULONG Size;
    ULONG TimeStamp;
    ULONG CheckSum;
    ULONG Flags;
    PVOID PDataAddress;
    ULONG PDataSize;
    DWORD ThreadId;
} DMN_MODLOAD, *PDMN_MODLOAD;

// Module load notification structure
typedef struct _DMN_MODLOAD_EX {
    ULONG SizeOfStruct;       //Size of this structure
    char  Name[MAX_PATH];
    PVOID BaseAddress;
    ULONG Size;
    ULONG TimeStamp;
    ULONG CheckSum;
    ULONG Flags;
    PVOID PDataAddress;
    ULONG PDataSize;
    DWORD ThreadId;
    ULONG OriginalSize;
} DMN_MODLOAD_EX, *PDMN_MODLOAD_EX;

#define DMN_MODFLAG_XBE     0x0001
#define DMN_MODFLAG_TLS     0x0002
#define DMN_MODFLAG_DLL     0x0004

// Section load/unload notification structure
typedef struct _DMN_SECTIONLOAD {
    char Name[MAX_PATH];
    PVOID BaseAddress;
    ULONG Size;
    USHORT Index;
    USHORT Flags;
} DMN_SECTIONLOAD, *PDMN_SECTIONLOAD;

#define DMN_SECFLAG_LOADED        0x0001
#define DMN_SECFLAG_READABLE      0x0002
#define DMN_SECFLAG_WRITEABLE     0x0004
#define DMN_SECFLAG_EXECUTABLE    0x0008
#define DMN_SECFLAG_UNINITIALIZED 0x0010

// thread create notification structure
typedef struct _DMN_CREATETHREAD {
    DWORD ThreadId;
    PVOID StartAddress;
    PCHAR ThreadNameAddress;
} DMN_CREATETHREAD, *PDMN_CREATETHREAD;

// fiber create/delete notification structure
typedef struct _DMN_FIBER {
    DWORD FiberId;
    BOOL Create;
    PVOID StartAddress;
} DMN_FIBER, *PDMN_FIBER;


// exception notification
typedef struct _DMN_EXCEPTION {
    DWORD ThreadId;
    DWORD Code;
    PVOID Address;
    DWORD Flags;
    DWORD Information[2];
} DMN_EXCEPTION, *PDMN_EXCEPTION;

// bugcheck notification
typedef struct _DMN_BUGCHECK {
    DWORD BugCheckData[5];
} DMN_BUGCHECK, *PDMN_BUGCHECK;

#define DM_EXCEPT_NONCONTINUABLE 1
#define DM_EXCEPT_FIRSTCHANCE 2

// PGO module load notification
typedef struct _DMN_PGO_MODLOAD {
    PCSTR pszModuleName;
    HPGOMODULE hPgoModule;
    DWORD ThreadId;
} DMN_PGO_MODLOAD, *PDMN_PGO_MODLOAD;


// Notification
#define DM_PERSISTENT       0x00000001
#define DM_DEBUGSESSION     0x00000002
#define DM_ASYNCSESSION     0x00000004
typedef struct _DMN_SESSION *PDMN_SESSION;
DMHRAPI DmOpenNotificationSession(DWORD dwFlags, PDMN_SESSION *pSession);
DMHRAPI DmCloseNotificationSession(PDMN_SESSION Session);
DMHRAPI DmNotify(PDMN_SESSION Session, DWORD dwNotification,
    PDM_NOTIFY_FUNCTION pfnHandler);

// notification extensions
typedef DWORD (__stdcall *PDM_EXT_NOTIFY_FUNCTION)(LPCSTR szNotification);
DMHRAPI DmRegisterNotificationProcessor(PDMN_SESSION Session, LPCSTR szType,
    PDM_EXT_NOTIFY_FUNCTION pfn);

// protocol
#define DEBUGGER_PORT 0x2da

// breakpoint types
#define DMBREAK_NONE 0
#define DMBREAK_WRITE 1
#define DMBREAK_READWRITE 2
#define DMBREAK_EXECUTE 3
#define DMBREAK_FIXED 4
#define DMBREAK_READ 5

// breakpoint routines
DMHRAPI DmSetBreakpoint(PVOID addr);
DMHRAPI DmRemoveBreakpoint(PVOID addr);
DMHRAPI DmSetInitialBreakpoint(void);
DMHRAPI DmSetDataBreakpoint(PVOID addr, DWORD dwType, DWORD dwSize);
DMHRAPI DmIsBreakpoint(PVOID addr, LPDWORD dwType);

// execution start and stop
DMHRAPI DmStop(void);
DMHRAPI DmGo(void);
DMHRAPI DmHaltThread(DWORD dwThreadId);
DMHRAPI DmContinueThread(DWORD dwThreadId, BOOL fException);

// File I/O monitor
DMHRAPI DmStartFileEventCapture();
DMHRAPI DmStopFileEventCapture();

// debugger
DMHRAPI DmIsDebuggerPresent(void);
DMHRAPI DmConnectDebugger(BOOL fConnect);

// process id (fabricated)
DMHRAPI DmGetPid(LPDWORD pdwPid);

// event stop control
#define DMSTOP_CREATETHREAD     0x00000001
#define DMSTOP_FCE              0x00000002
#define DMSTOP_DEBUGSTR         0x00000004
#define DMSTOP_STACKTRACE       0x00000008
#define DMSTOP_MODLOAD          0x00000010
#define DMSTOP_TITLELAUNCH      0x00000020
#define DMSTOP_PGOMODSTARTUP    0x00000040
DMHRAPI DmStopOn(DWORD dwStopFlags, BOOL fStop);


// reboot
#define DMBOOT_TITLE 0
#define DMBOOT_WAIT  1
// WARM does not exist, it is now a cold boot. So we do not break existing tools we have left the define.
#define DMBOOT_WARM_DEPRECATED  2  
#define DMBOOT_COLD  4
#define DMBOOT_STOP  8

DMHRAPI DmReboot(DWORD dwFlags);


DMHRAPI DmRebootEx(DWORD dwFlags, LPCSTR szImagePath, LPCSTR szMediaPath, LPCSTR szDbgCmdLine);

//crash dump
DMHRAPI DmCrashDump();

// memory
DMHRAPI DmGetMemory(LPCVOID lpbAddr, DWORD cb, LPVOID lpbBuf,
    LPDWORD pcbRet);

// The checksum is computed on the Xbox, without transferring the
// memory across the network. Each block of bytes will have its own
// 32-bit CRC calculated separately. (If you just want to checksum
// the whole chunk of data, pass the same value for both cb
// and cbBlockSize.)
// Requirements:
//  lpbAddr must be aligned on an 8-byte boundary.
//  lpbAddr can't point to code
//  cb must be a multiple of cbBlockSize
//  cbBlockSize must be a multiple of 8 bytes
//  lpbBuf will have sizeof(DWORD)*(cb/cbBlockSize) bytes written to it.

DMHRAPI DmGetMemoryChecksum(LPCVOID lpbAddr, DWORD cb,
    DWORD cbBlockSize, LPVOID lpbBuf, LPDWORD pcbRet);

DMHRAPI DmSetMemory(LPVOID lpbAddr, DWORD cb, LPCVOID lpbBuf,
    LPDWORD pcbRet);

typedef struct _DM_WALK_MEMORY *PDM_WALK_MEMORY;
typedef struct _DM_MEMORY_REGION
{
    PVOID BaseAddress;
    DWORD Size;
    DWORD Protect;
} DM_MEMORY_REGION, *PDM_MEMORY_REGION;
DMHRAPI DmWalkCommittedMemory(PDM_WALK_MEMORY *, PDM_MEMORY_REGION);
DMHRAPI DmCloseCommittedMemory(PDM_WALK_MEMORY);



// thread stopped info
typedef struct _DM_THREADSTOP {
    DWORD NotifiedReason;
    union {
        DMN_BREAK Break;
        DMN_DATABREAK DataBreak;
        DMN_EXCEPTION Exception;
        DMN_DEBUGSTR DebugStr;
        DMN_BUGCHECK BugCheck;
    } u;
} DM_THREADSTOP, *PDM_THREADSTOP;

// thread general info
typedef struct _DM_THREADINFO {
    DWORD SuspendCount;
    DWORD Priority;
    LPVOID TlsBase;
} DM_THREADINFO, *PDM_THREADINFO;

typedef struct _DM_THREADINFOEX {
    DWORD    Size; //Size of this structure
    DWORD    SuspendCount;
    DWORD    Priority;
    LPVOID   TlsBase;
    LPVOID   StartAddress;
    LPVOID   StackBase;
    LPVOID   StackLimit;
    FILETIME CreateTime;
    DWORD    StackSlackSpace;
    PCHAR    ThreadNameAddress;
    DWORD    ThreadNameLength; //Including NULL termination
    UCHAR    CurrentProcessor;
    DWORD    LastError;
} DM_THREADINFOEX, *PDM_THREADINFOEX;

// thread routines
DMHRAPI DmGetThreadList(LPDWORD rgdwThreads, LPDWORD pcThreads);
DMHRAPI DmGetThreadContext(DWORD dwThreadId, PXCONTEXT pdmcr);
DMHRAPI DmSetThreadContext(DWORD dwThreadId, PXCONTEXT pdmcr);
DMHRAPI DmIsThreadStopped(DWORD dwThreadId, PDM_THREADSTOP pdmts);
DMHRAPI DmGetThreadInfoEx(DWORD dwThreadId, PDM_THREADINFOEX pdmti);
DMHRAPI DmSuspendThread(DWORD dwThreadId);
DMHRAPI DmResumeThread(DWORD dwThreadId);


// loaded modules and sections
typedef struct _DM_WALK_MODULES *PDM_WALK_MODULES;
DMHRAPI DmWalkLoadedModules(PDM_WALK_MODULES *, PDMN_MODLOAD);
DMHRAPI DmWalkLoadedModulesEx(PDM_WALK_MODULES *, PDMN_MODLOAD_EX);
DMHRAPI DmCloseLoadedModules(PDM_WALK_MODULES);
typedef struct _DM_WALK_MODSECT *PDM_WALK_MODSECT;
DMHRAPI DmWalkModuleSections(PDM_WALK_MODSECT *, LPCSTR, PDMN_SECTIONLOAD);
DMHRAPI DmCloseModuleSections(PDM_WALK_MODSECT);


DMHRAPI 
DmGetXexHeaderField(
    IN  LPCSTR szImageName,
    IN  ULONG  HeaderField,
    OUT PUCHAR Buffer,
    IN  ULONG  BufferLength,
    IN  ULONG *FieldSize
    );

// XBE info
typedef struct _DM_XBE {
    char LaunchPath[MAX_PATH+1];
    DWORD TimeStamp;
    DWORD CheckSum;
    DWORD StackSize;
} DM_XBE, *PDM_XBE;
DMHRAPI DmGetXbeInfo(LPCSTR szName, PDM_XBE);

#define DM_XBEONDISKONLY  0x00000001
DMHRAPI DmGetXbeInfoEx(LPCSTR szName, PDM_XBE, DWORD dwFlags);


// socket-level commands
typedef struct _DM_CONNECTION *PDM_CONNECTION;
DMHRAPI DmSetConnectionTimeout(DWORD dwConnectTimeout, DWORD dwConversationTimeout);
DMHRAPI DmOpenConnection(PDM_CONNECTION *);
DMHRAPI DmOpenSecureConnection(PDM_CONNECTION *, LPCSTR szPassword);
DMHRAPI DmCloseConnection(PDM_CONNECTION);
DMHRAPI DmSendCommand(PDM_CONNECTION, LPCSTR szCommand, LPSTR szResponse,
    LPDWORD lpdwResponseSize);
DMHRAPI DmReceiveStatusResponse(PDM_CONNECTION, LPSTR szResponse,
    LPDWORD lpdwResponseSize);
DMHRAPI DmReceiveSocketLine(PDM_CONNECTION, LPSTR szResponse,
    LPDWORD lpdwResponseSize);
DMHRAPI DmDedicateConnection(PDM_CONNECTION, LPCSTR szHandler);
DMHRAPI DmSendBinary(PDM_CONNECTION, LPCVOID pv, DWORD cb);
DMHRAPI DmReceiveBinary(PDM_CONNECTION, LPCVOID pv, DWORD cb, LPDWORD pcbRet);
DMHRAPI DmResolveXboxName(LPDWORD lpdwAddress);
DMHRAPI DmGetNameOfXbox(LPSTR szName, LPDWORD lpdwSize, BOOL fResolvable);
DMHRAPI DmGetAltAddress(LPDWORD lpdwAddress);
DMHRAPI DmFindConsole(DWORD dwRetryCount, DWORD dwRetryDelay);

// protocol commands
DMHRAPI DmUseSharedConnection(BOOL);

// file attributes
typedef struct _DM_FILE_ATTRIBUTES {
    char Name[256];
    FILETIME CreationTime;
    FILETIME ChangeTime;
    DWORD SizeHigh;
    DWORD SizeLow;
    DWORD Attributes;
} DM_FILE_ATTRIBUTES, *PDM_FILE_ATTRIBUTES;

// filesystem
DMHRAPI DmSendFileA(LPCSTR szLocalName, LPCSTR szRemoteName);
// filesystem
DMHRAPI DmSendFileW(LPCWSTR szLocalName, LPCSTR szRemoteName);
#ifdef UNICODE
#define DmSendFile  DmSendFileW
#else
#define DmSendFile  DmSendFileA
#endif // !UNICODE

DMHRAPI DmReceiveFileA(LPCSTR szLocalName, LPCSTR szRemoteName);
DMHRAPI DmReceiveFileW(LPCWSTR szLocalName, LPCSTR szRemoteName);
#ifdef UNICODE
#define DmReceiveFile  DmReceiveFileW
#else
#define DmReceiveFile  DmReceiveFileA
#endif // !UNICODE

DMHRAPI DmGetFileAttributes(LPCSTR szFileName, PDM_FILE_ATTRIBUTES);
DMHRAPI DmSetFileAttributes(LPCSTR szFileName, PDM_FILE_ATTRIBUTES);
DMHRAPI DmMkdir(LPCSTR szDirectoryName);
DMHRAPI DmRenameFile(LPCSTR szOldName, LPCSTR szNewName);
DMHRAPI DmDeleteFile(LPCSTR szFileName, BOOL fIsDirectory);

// partial file I/O
DMHRAPI DmWriteFilePartial(LPCSTR szFileName, DWORD dwFileOffset,
    LPBYTE pbDataBuffer, DWORD dwDataSize, LPDWORD lpdwBytesWritten);
DMHRAPI DmReadFilePartial(LPCSTR szFileName, DWORD dwFileOffset,
    LPBYTE pbDataBuffer, DWORD dwDataSize, LPDWORD lpdwBytesRead);
DMHRAPI DmSetFileSize(LPCSTR szFileName, DWORD dwFileOffset,
    DWORD dwCreateDisposition);


// directory walking
typedef struct _DM_WALK_DIR *PDM_WALK_DIR;
DMHRAPI DmWalkDir(PDM_WALK_DIR *, LPCSTR szDir, PDM_FILE_ATTRIBUTES);
DMHRAPI DmCloseDir(PDM_WALK_DIR);

// time
DMHRAPI DmGetSystemTime(LPSYSTEMTIME lpSysTime);

// config functions
DMHRAPI DmSetConfigValue(ULONG ulValueIndex, ULONG ulType, PVOID pValue, ULONG cbValueLength);
DMHRAPI DmSetServerName(LPCSTR szServerName);


// name functions
#define DM_XBOX_NAME_MAX 21
DMHRAPI DmGetXboxName(LPSTR, LPDWORD);
DMHRAPI DmSetXboxName(LPCSTR);
DMHRAPI DmSetXboxNameNoRegister(LPCSTR);

// Debug settings

// Dump mode: behavior when exception occurs (while not debugging)
#define DM_DUMPMODE_SMART  0  // Debug if xbdm can, dumps if kd required
#define DM_DUMPMODE_ENABLED 1  // Always dump
#define DM_DUMPMODE_DISABLED  2  // Always debug

DMHRAPI DmGetDumpMode(DWORD *pdwDumpMode);
DMHRAPI DmSetDumpMode(DWORD dwDumpMode);

// Dump reporting flags
#define DUMP_RF_REPORT_PROMPT      0
#define DUMP_RF_REPORT_ALWAYS      0x00000001
#define DUMP_RF_REPORT_NEVER       0x00000002
#define DUMP_RF_REPORT_MASK        0x0000000F
#define DUMP_RF_REPORT_SHIFT       0

#define DUMP_RF_DESTINATION_LOCAL  0
#define DUMP_RF_DESTINATION_REMOTE 0x00000010
#define DUMP_RF_DESTINATION_MASK   0x000000F0
#define DUMP_RF_DESTINATION_SHIFT  4

#define DUMP_RF_FORMAT_FULL        0          //Full heap
#define DUMP_RF_FORMAT_PARTIAL     0x00000100 //Partial Heap (scan memory)
#define DUMP_RF_FORMAT_NOHEAP      0x00000200 //Just Threads and Exception Info
#define DUMP_RF_FORMAT_RETAIL      0x00000300 //A retail dump - NYI
#define DUMP_RF_FORMAT_MASK        0x00000F00
#define DUMP_RF_FORMAT_SHIFT       8

typedef struct _DM_DUMP_SETTINGS
{
    DWORD ReportingFlags;
    char  NetworkPath[MAX_PATH];
} DM_DUMP_SETTINGS, *PDM_DUMP_SETTINGS;

DMHRAPI DmGetDumpSettings(PDM_DUMP_SETTINGS pSettings);
DMHRAPI DmSetDumpSettings(PDM_DUMP_SETTINGS pSettings);

// Event defer flags
#define DM_CANDEFER_EXECUTION_BREAK 1
#define DM_CANDEFER_DEBUG_STRING    2
#define DM_CANDEFER_SINGLE_STEP     4
#define DM_CANDEFER_ASSERTION       8
#define DM_CANDEFER_NT_ASSERTION   16
#define DM_CANDEFER_DATA_BREAK     32
#define DM_CANDEFER_RIP            64

DMHRAPI DmGetEventDeferFlags(DWORD *pdwEvent);
DMHRAPI DmSetEventDeferFlags(DWORD dwEvent);

#define DMCT_DEVELOPMENT_KIT      0
#define DMCT_TEST_KIT             1
#define DMCT_REVIEWER_KIT         2
DMHRAPI DmGetConsoleType(DWORD *pdwConsoleType);



#define DM_XBOX_HW_FLAG_HDD                            0x00000020
#define DM_XBOX_HW_FLAG_TESTKIT                        0x02000000

typedef struct _DM_VERSION_INFO
{
		USHORT Major;
		USHORT Minor;
		USHORT Build;
		USHORT Qfe;

} DM_VERSION_INFO, *PDM_VERSION_INFO;

typedef struct _DM_SYSTEM_INFO
{
	int SizeOfStruct;
	
	DM_VERSION_INFO BaseKernelVersion;
	DM_VERSION_INFO KernelVersion;
	DM_VERSION_INFO XDKVersion;
	
	ULONG dmSystemInfoFlags;
	
} DM_SYSTEM_INFO, *PDM_SYSTEM_INFO;


DMHRAPI DmGetSystemInfo(PDM_SYSTEM_INFO pdmGetSystemInfo);


// management functions
typedef struct _DM_USER {
    char UserName[256];
    DWORD AccessPrivileges;
} DM_USER, *PDM_USER;

#define DMPL_PRIV_READ           0x0001
#define DMPL_PRIV_WRITE          0x0002
#define DMPL_PRIV_CONTROL        0x0004
#define DMPL_PRIV_CONFIGURE      0x0008
#define DMPL_PRIV_MANAGE         0x0010

DMHRAPI DmAddUser(LPCSTR szUserName, DWORD dwAccess);
DMHRAPI DmRemoveUser(LPCSTR szUserName);
DMHRAPI DmSetUserAccess(LPCSTR szUserName, DWORD dwAccess);
DMHRAPI DmGetUserAccess(LPCSTR szUserName, LPDWORD lpdwAccess);
typedef struct _DM_WALK_USERS *PDM_WALK_USERS;
DMHRAPI DmWalkUserList(PDM_WALK_USERS *, PDM_USER);
DMHRAPI DmCloseUserList(PDM_WALK_USERS);
DMHRAPI DmEnableSecurity(BOOL fEnable);
DMHRAPI DmIsSecurityEnabled(LPBOOL pfEnabled);
DMHRAPI DmSetAdminPassword(LPCSTR szPassword);

// title to launch
#define DMTITLE_PERSIST    0x0001
#define DMTITLE_UNPERSIST  0x0002
DMHRAPI DmSetTitle(LPCSTR szDir, LPCSTR szTitle, LPCSTR szCmdLine);
DMHRAPI DmSetTitleEx(LPCSTR szDir, LPCSTR szTitle, LPCSTR szCmdLine, DWORD dwFlags);


// Screenshot functionality
DMHRAPI DmScreenShot(LPCSTR filename);



// start / stop profile data collection
DMHRAPI DmCAPControl(LPCSTR action);

// performance counters
#define DMCOUNT_FREQUENCY   0x000F
#define DMCOUNT_FREQ100MS   0x0001
#define DMCOUNT_FREQ1SEC    0x000A

#define DMCOUNT_COUNTTYPE   0x0030
#define DMCOUNT_EVENT       0x0010
#define DMCOUNT_VALUE       0x0000
#define DMCOUNT_PRATIO      0x0020
#define DMCOUNT_COUNTSUBTYPE 0x0FC0

// event rates
#define DMCOUNT_PERSEC      0x0040
#define DMCOUNT_PERMSEC     0x0080
#define DMCOUNT_PERFRAME    0x0100
#define DMCOUNT_PERTICK     0x0200

// value types
#define DMCOUNT_AVERAGE     0x0040

typedef struct _DM_COUNTDATA {
    LARGE_INTEGER CountValue;
    LARGE_INTEGER RateValue;
    DWORD CountType;
} DM_COUNTDATA, *PDM_COUNTDATA;

typedef struct _DM_COUNTINFO {
    char Name[256];
    DWORD Type;
} DM_COUNTINFO, *PDM_COUNTINFO;

DMHRAPI DmQueryPerformanceCounter(LPCSTR szName, DWORD dwType, PDM_COUNTDATA);
typedef struct _DM_WALK_COUNTERS *PDM_WALK_COUNTERS;
DMHRAPI DmWalkPerformanceCounters(PDM_WALK_COUNTERS *, PDM_COUNTINFO);
DMHRAPI DmCloseCounters(PDM_WALK_COUNTERS);
DMHRAPI DmEnableGPUCounter(BOOL);


DMHRAPI DmGetDriveList(LPSTR rgchDrives, DWORD *pcDrives);
DMHRAPI DmGetDiskFreeSpace(char *szDrive,
                           PULARGE_INTEGER pnFreeBytesAvailableToCaller,
                           PULARGE_INTEGER pnTotalNumberOfBytes,
                           PULARGE_INTEGER pnTotalNumberOfFreeBytes);





// error codes
#define FACILITY_XBDM 0x2da
#ifndef MAKE_HRESULT
#define MAKE_HRESULT(sev,fac,code) \
    ((HRESULT)(((unsigned long)sev<<31)|((unsigned long)fac<<16)|((unsigned long)code)))
#endif
#define XBDM_HRESERR(code) MAKE_HRESULT(1, FACILITY_XBDM, code)
#define XBDM_HRESSUCC(code) MAKE_HRESULT(0, FACILITY_XBDM, code)

#define XBDM_NOERR XBDM_HRESSUCC(0)

#define XBDM_UNDEFINED XBDM_HRESERR(0)
#define XBDM_MAXCONNECT XBDM_HRESERR(1)
#define XBDM_NOSUCHFILE XBDM_HRESERR(2)
#define XBDM_NOMODULE XBDM_HRESERR(3)
#define XBDM_MEMUNMAPPED XBDM_HRESERR(4)
#define XBDM_NOTHREAD XBDM_HRESERR(5)
#define XBDM_CLOCKNOTSET XBDM_HRESERR(6)
#define XBDM_INVALIDCMD XBDM_HRESERR(7)
#define XBDM_NOTSTOPPED XBDM_HRESERR(8)
#define XBDM_MUSTCOPY XBDM_HRESERR(9)
#define XBDM_ALREADYEXISTS XBDM_HRESERR(10)
#define XBDM_DIRNOTEMPTY XBDM_HRESERR(11)
#define XBDM_BADFILENAME XBDM_HRESERR(12)
#define XBDM_CANNOTCREATE XBDM_HRESERR(13)
#define XBDM_CANNOTACCESS XBDM_HRESERR(14)
#define XBDM_DEVICEFULL XBDM_HRESERR(15)
#define XBDM_NOTDEBUGGABLE XBDM_HRESERR(16)
#define XBDM_BADCOUNTTYPE XBDM_HRESERR(17)
#define XBDM_COUNTUNAVAILABLE XBDM_HRESERR(18)
#define XBDM_NOTLOCKED XBDM_HRESERR(20)
#define XBDM_KEYXCHG XBDM_HRESERR(21)
#define XBDM_MUSTBEDEDICATED XBDM_HRESERR(22)
#define XBDM_INVALIDARG XBDM_HRESERR(23)
#define XBDM_PROFILENOTSTARTED XBDM_HRESERR(24)
#define XBDM_PROFILEALREADYSTARTED XBDM_HRESERR(25)
#define XBDM_ALREADYSTOPPED XBDM_HRESERR(26)
#define XBDM_FASTCAPNOTENABLED XBDM_HRESERR(27)
#define XBDM_NOMEMORY XBDM_HRESERR(28)
#define XBDM_TIMEOUT XBDM_HRESERR(29)
#define XBDM_NOSUCHPATH XBDM_HRESERR(30)
#define XBDM_INVALID_SCREEN_INPUT_FORMAT XBDM_HRESERR(31)
#define XBDM_INVALID_SCREEN_OUTPUT_FORMAT XBDM_HRESERR(32)
#define XBDM_CALLCAPNOTENABLED XBDM_HRESERR(33)
#define XBDM_INVALIDCAPCFG XBDM_HRESERR(34)
#define XBDM_CAPNOTENABLED XBDM_HRESERR(35)
#define XBDM_TOOBIGJUMP XBDM_HRESERR(36)
#define XBDM_FIELDNOTPRESENT XBDM_HRESERR(37)
#define XBDM_OUTPUTBUFFERTOOSMALL XBDM_HRESERR(38)
#define XBDM_PROFILEREBOOT XBDM_HRESERR(39)
#define XBDM_PROFILENOTITLE XBDM_HRESERR(40)
#define XBDM_MAXDURATIONEXCEEDED XBDM_HRESERR(41)
#define XBDM_INVALIDSTATE XBDM_HRESERR(42)
#define XBDM_MAXEXTENSIONS XBDM_HRESERR(43)
#define XBDM_D3D_DEBUG_COMMAND_NOT_IMPLEMENTED XBDM_HRESERR(0x50)
#define XBDM_D3D_INVALID_SURFACE XBDM_HRESERR(0x51)
#define XBDM_CANNOTCONNECT XBDM_HRESERR(0x100)
#define XBDM_CONNECTIONLOST XBDM_HRESERR(0x101)
#define XBDM_FILEERROR XBDM_HRESERR(0x103)
#define XBDM_ENDOFLIST XBDM_HRESERR(0x104)
#define XBDM_BUFFER_TOO_SMALL XBDM_HRESERR(0x105)
#define XBDM_NOTXBEFILE XBDM_HRESERR(0x106)
#define XBDM_MEMSETINCOMPLETE XBDM_HRESERR(0x107)
#define XBDM_NOXBOXNAME XBDM_HRESERR(0x108)
#define XBDM_NOERRORSTRING XBDM_HRESERR(0x109)
#define XBDM_INVALIDSTATUS XBDM_HRESERR(0x10A)
#define XBDM_TASK_PENDING XBDM_HRESERR(0x150)

#define XBDM_CONNECTED XBDM_HRESSUCC(1)
#define XBDM_MULTIRESPONSE XBDM_HRESSUCC(2)
#define XBDM_BINRESPONSE XBDM_HRESSUCC(3)
#define XBDM_READYFORBIN XBDM_HRESSUCC(4)
#define XBDM_DEDICATED XBDM_HRESSUCC(5)
#define XBDM_PROFILERESTARTED XBDM_HRESSUCC(6)
#define XBDM_FASTCAPENABLED XBDM_HRESSUCC(7)
#define XBDM_CALLCAPENABLED XBDM_HRESSUCC(8)

// Call-Attributed Profiler Support Function
DMHRAPI DmStartProfiling(LPCSTR szLogFileName, DWORD dwDataBufferSize);
DMHRAPI DmStopProfiling(VOID);
DMHRAPI DmAbortProfiling(VOID);
DMHRAPI DmIsFastCAPEnabled(VOID);
DMHRAPI DmSetProfilingOptions(DWORD dwFlags);

// Flags for DmSetProfilingOptions
// Should the extra counter be recorded by DmStartProfiling
#define DM_PROFILE_FLAG_CAPTURE_PERFCOUNTER  0x00010000L
// DM_PROFILE_FLAG_CAPTURE_L2_MISSES is obsolete--use DM_PROFILE_FLAG_CAPTURE_PERFCOUNTER
#define DM_PROFILE_FLAG_CAPTURE_L2_MISSES DM_PROFILE_FLAG_CAPTURE_PERFCOUNTER
#define DM_PROFILE_FLAG_CAPTURE_CURRENT_HW_THREAD 0x00020000L

// Which hardware threads should be recorded
#define DM_PROFILE_FLAG_HW_THREAD0 (1<<0)
#define DM_PROFILE_FLAG_HW_THREAD1 (1<<1)
#define DM_PROFILE_FLAG_HW_THREAD2 (1<<2)
#define DM_PROFILE_FLAG_HW_THREAD3 (1<<3)
#define DM_PROFILE_FLAG_HW_THREAD4 (1<<4)
#define DM_PROFILE_FLAG_HW_THREAD5 (1<<5)

// If the extra counter is being recorded, which counter should it be?
// These enums must be used as parameters to DM_PROFILE_FLAG_PMC to
// align them properly.
typedef enum
{
    DM_PROFILE_PMC_L2 = 0,

    DM_PROFILE_PMC_DL1,
    DM_PROFILE_PMC_IL1 ,
    DM_PROFILE_PMC_LHS,
    DM_PROFILE_PMC_DERAT,
    DM_PROFILE_PMC_IERAT,
    DM_PROFILE_PMC_BRANCH,

    DM_PROFILE_PMC_UCODE,
    DM_PROFILE_PMC_INSTR,

    DM_PROFILE_PMC_MISALIGNED,
    DM_PROFILE_PMC_STQ_FULL,

    DM_PROFILE_PMC_DIVSQRT,
    DM_PROFILE_PMC_DENORM,
    DM_PROFILE_PMC_FPU_NAN,
    DM_PROFILE_PMC_VMX_ABNORMAL,


    DM_PROFILE_PMC_LAST
} eDM_PROFILE_PMC_SETUP;

#define DM_PROFILE_PMC_SHIFT     6

#define DM_PROFILE_PMC_MASK      ((0xF) << DM_PROFILE_PMC_SHIFT)
#define DM_PROFILE_FLAG_PMC(x)    (((x) << DM_PROFILE_PMC_SHIFT) & DM_PROFILE_PMC_MASK)

// E.g. to measure instruction L1 misses on threads 0 and 2:
// DWORD flags =  DM_PROFILE_FLAG_CAPTURE_PERFCOUNTER | DM_PROFILE_FLAG_HW_THREAD2 | DM_PROFILE_FLAG_PMC(DM_PROFILE_PMC_IL1);
// DmSetProfilingOptions(flags);

// PoGO Support Functions

/*
DmPgo{Start|Stop}DataCollection - enables/disables PGO data collection.
This does not affect the instrumentation itself.  The instrumentation will
still execute, but it will not save any results.  This is intended to be used
to scope the profiling data to useful scenarios, and not to throttle
performance.  This may be called in response to DM_PGO_MODULE_STARTUP to
specify that data collection should be initially disabled.

hPgoModule - specifies module to control data collection.  If NULL, controls
all loaded modules.
*/
DMHRAPI DmPgoStartDataCollection (HPGOMODULE hPgoModule);
DMHRAPI DmPgoStopDataCollection (HPGOMODULE hPgoModule);

/*
DmPgoSaveSnapshot - saves a snapshot of the current PGO instrumentation
data for the caller's module to a new file.  A unique filename will be chosen
by appending a number to the filename.

pszPhase - string to append to the filename.  If NULL, no string is appended.

fReset - if TRUE, resets all profiling counters

hPgoModule - specifies module to save snapshot.  If NULL, save a snapshot for
every loaded module.
*/
DMHRAPI DmPgoSaveSnapshot (
    PCSTR pszPhase,
    BOOL fReset,
    HPGOMODULE hPgoModule);

/*
DmPgoSetAllocScale - sets the buffer size multiplier.  This function may
only be called in response to DM_PGO_MODULE_STARTUP.

dwBufferAllocScale - specifies the buffer size multiplier.  The actual
allocated size of the profiling data buffer is the default size times this
value.  If the multiplier is 0, or if there is insufficient memory for the
computed size, the default size will be used.
*/
DMHRAPI DmPgoSetAllocScale (
    HPGOMODULE hPgoModule,
    DWORD dwBufferAllocScale);


#ifndef XBDM_STATIC_LIB
DMHRAPI DmTranslateErrorA(HRESULT hr, LPSTR lpBuffer, int nBufferMax);
DMHRAPI DmTranslateErrorW(HRESULT hr, LPWSTR lpBuffer, int nBufferMax);
#ifdef UNICODE
#define DmTranslateError  DmTranslateErrorW
#else
#define DmTranslateError  DmTranslateErrorA
#endif // !UNICODE
#endif //XBDM_STATIC_LIB



//
// Allocation tracking types and definitions
//

#define DM_TRACK_HEAP                   0x0001
#define DM_TRACK_VIRTUAL_MEMORY         0x0002
#define DM_TRACK_CONTIGUOUS_MEMORY      0x0004
#define DM_TRACK_SYSTEM_MEMORY          0x0008
#define DM_TRACK_DEBUG_MEMORY           0x0010
#define DM_TRACK_KERNEL_POOL            0x0020
#define DM_TRACK_HANDLE                 0x0040
#define DM_TRACK_CUSTOM                 0x0080
#define DM_TRACK_TYPEMASK               0x00FF
#define DM_TRACK_ASSERT_ON_FAILURES     0x0100
#define DM_TRACK_MASK                   0x01FF

DMHRAPI DmQueryAllocationTypeName(USHORT AllocationType, LPSTR pszName, SIZE_T nSize);


typedef enum _X_RUNTIME_FUNCTION_TYPE {
    XFunctionTypeSaveMillicode,
    XFunctionTypeNoHandler,
    XFunctionTypeRestoreMillicode,
    XFunctionTypeHandler,
} X_RUNTIME_FUNCTION_TYPE;

typedef struct _X_RUNTIME_FUNCTION {
    ULONG BeginAddress;
    ULONG FunctionType : 2;
    ULONG FunctionLength : 22;
    ULONG PrologLength : 8;
} X_RUNTIME_FUNCTION, * PX_RUNTIME_FUNCTION;

typedef struct _X_STACK_FRAME
{
    XCONTEXT               FrameContext;        // RegisterContext
    BOOL                   fHasFunctionEntry;
    X_RUNTIME_FUNCTION     FunctionEntry;
} X_STACK_FRAME, *PX_STACK_FRAME;



#ifndef XCRASHAPI
#define XCRASHAPI __declspec(dllimport)
#endif

XCRASHAPI
HANDLE
WINAPI
XcrashOpenFile(
    IN LPCWSTR wszFileName
);

XCRASHAPI
VOID
WINAPI
XcrashCloseFile(
    IN HANDLE hCrashFile
);

XCRASHAPI
BOOL
WINAPI
XcrashGetMemory(
    IN HANDLE hCrashFile,
    IN LPCVOID lpAddrToRead,
    IN DWORD dwNumberOfBytesToRead,
    OUT LPVOID lpDataRead,
    OUT LPDWORD lpdwNumberOfBytesRead
);

XCRASHAPI
BOOL
WINAPI
XcrashGetThreadList(
    IN HANDLE hCrashFile,
    IN LPDWORD lpdwThreadIdList,
    IN OUT LPDWORD lpdwNumberOfThreads
);

XCRASHAPI
BOOL
WINAPI
XcrashGetThreadContext(
    IN HANDLE hCrashFile,
    IN DWORD dwThreadId,
    IN OUT PXCONTEXT pThreadContext
);

XCRASHAPI
BOOL
WINAPI
XcrashGetThreadInfoEx(
  IN  HANDLE hCrashFile,
  IN  DWORD dwThreadId,
  OUT PDM_THREADINFOEX pDmThreadInfoEx
  );

XCRASHAPI
BOOL
WINAPI
XcrashIsThreadStopped(
  IN  HANDLE hCrashFile,
  IN  DWORD dwThreadId,
  OUT PBOOL pfStopped,
  OUT PDM_THREADSTOP pDmThreadStop
  );

XCRASHAPI
BOOL
WINAPI
XcrashWalkLoadedModules(
    IN     HANDLE      hCrashFile,
    IN OUT PHANDLE     phLoadedModules,
    OUT    DMN_MODLOAD *pDmLoadedModule
);


XCRASHAPI
VOID
WINAPI
XcrashCloseLoadedModules(
    HANDLE hLoadedModules
);

XCRASHAPI
BOOL
WINAPI
XcrashWalkModuleSections(
  IN     HANDLE            hCrashFile,
  IN OUT PHANDLE           phModuleSections,
  IN     LPCSTR            pszModuleName,
  OUT    PDMN_SECTIONLOAD  pdmSectionLoad
  );

XCRASHAPI
VOID
WINAPI
XcrashCloseModuleSections(
    HANDLE hModuleSections
    );

XCRASHAPI
BOOL
WINAPI
XcrashGetModuleLongName(
  IN     HANDLE   hCrashFile,
  IN     LPCSTR   pszShortName,
  OUT    LPSTR    pszLongName,
  IN OUT LPDWORD  pcchLongName
  );

XCRASHAPI
BOOL
WINAPI
XcrashCopySz(
  IN     HANDLE hCrashFile,
  IN     LPCSTR pszStringVA,
  OUT    LPSTR  pszString,
  IN OUT PDWORD pcchLength
  );




//
// Symbol APIs
//

typedef struct _DM_PDB_SIGNATURE {
    GUID Guid;
    DWORD Age;
    CHAR Path[MAX_PATH];
} DM_PDB_SIGNATURE, *PDM_PDB_SIGNATURE;

DMHRAPI
DmFindPdbSignature(
    IN PVOID BaseAddress,
    OUT PDM_PDB_SIGNATURE PdbSignature
    );


//
// Get the path of the XDK installed symbol server
// that contains system symbols.
//

DMHRAPI
DmGetSystemSymbolServerPathA(
    OUT LPSTR szSymbolServerPath,
    IN OUT DWORD  *pcchSymbolServerPath
    );
DMHRAPI
DmGetSystemSymbolServerPathW(
    OUT LPWSTR szSymbolServerPath,
    IN OUT DWORD  *pcchSymbolServerPath
    );
#ifdef UNICODE
#define DmGetSystemSymbolServerPath  DmGetSystemSymbolServerPathW
#else
#define DmGetSystemSymbolServerPath  DmGetSystemSymbolServerPathA
#endif // !UNICODE

//
// DmLoadSymbolsForModule and DmLoadSymbolsForModuleEx
//
// This API loads PDB symbol for the module specified by ModuleName.
//

DMHRAPI
DmLoadSymbolsForModule(
    IN CONST CHAR* ModuleName,
    IN PVOID BaseAddress,
    IN SIZE_T Size,
    IN ULONG TimeStamp
    );

DMHRAPI
DmLoadSymbolsForModuleEx(
    IN CONST CHAR* ModuleName,
    IN PVOID BaseAddress,
    IN SIZE_T Size,
    IN ULONG TimeStamp,
    IN CONST DM_PDB_SIGNATURE* PdbSignature
    );

//
// DmUnloadSymbolsForModule
//
// This API unloads the symbol table
//

DMHRAPI
DmUnloadSymbolsForModule(
    IN ULONG_PTR BaseAddress
    );

//
// DmLoadSymbolsForAllLoadedModules
//
// This API enumerates all loaded modules and load symbols for each one of them
// It is equipvalent to call DmWalkLoadedModules and call DmLoadSymbolsForModule
// for each module.
//

DMHRAPI
DmLoadSymbolsForAllLoadedModules(
    VOID
    );

//
// DmGetSymbolFromAddress
//
// This API similar to SymGetSymFromAddr64. It locates the symbol for
// specified address.
//

DMHRAPI
DmGetSymbolFromAddress(
    IN  ULONG_PTR Address,
    OUT CHAR* SymbolName,
    IN  SIZE_T BufferSize,
    OUT PULONG Displacement OPTIONAL
    );

//
// DmGetSourceLineFromAddress
//
// This API similar to SymGetLineFromAddr64. It locates the source file and line
// number for specified address.
//

DMHRAPI
DmGetSourceLineFromAddress(
    IN  ULONG_PTR Address,
    OUT CHAR* FileName,
    IN  SIZE_T BufferSize,
    OUT PULONG LineNumber
    );

//
// DmSetSymbolSearchPath
//
// This API allow user to add additional symbol search paths
//

DMHRAPI
DmSetSymbolSearchPath(
    IN LPCTSTR lpszPath
    );

// Constants for gamepad buttons
#define DM_XINPUT_GAMEPAD_DPAD_UP          0x0001
#define DM_XINPUT_GAMEPAD_DPAD_DOWN        0x0002
#define DM_XINPUT_GAMEPAD_DPAD_LEFT        0x0004
#define DM_XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
#define DM_XINPUT_GAMEPAD_START            0x0010
#define DM_XINPUT_GAMEPAD_BACK             0x0020
#define DM_XINPUT_GAMEPAD_LEFT_THUMB       0x0040
#define DM_XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
#define DM_XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
#define DM_XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define DM_XINPUT_GAMEPAD_A                0x1000
#define DM_XINPUT_GAMEPAD_B                0x2000
#define DM_XINPUT_GAMEPAD_X                0x4000
#define DM_XINPUT_GAMEPAD_Y				   0x8000

#define DM_XINPUT_GAMEPAD_SYSTEM_BUTTON_X360    0x0400
#define DM_XINPUT_GAMEPAD_SYSTEM_BUTTON_BIND    0x0800

typedef struct _DM_XINPUT_GAMEPAD
{
    WORD                                wButtons;
    BYTE                                bLeftTrigger;
    BYTE                                bRightTrigger;
    SHORT                               sThumbLX;
    SHORT                               sThumbLY;
    SHORT                               sThumbRX;
    SHORT                               sThumbRY;
} DM_XINPUT_GAMEPAD, *PDM_XINPUT_GAMEPAD;

//
// DmAutomation Support
//

#define DM_XUSER_MAX_COUNT 4

DMHRAPI
DmAutomationGetInputProcess (
    IN DWORD dwUserIndex,
    OUT BOOL* pfSystemProcess
    );

DMHRAPI
DmAutomationBindController(
    IN DWORD dwUserIndex,
    IN DWORD dwQueueLength
    );
    
DMHRAPI
DmAutomationUnbindController(
    IN DWORD dwUserIndex
    );
    
DMHRAPI
DmAutomationConnectController(
    IN DWORD dwUserIndex
    );

DMHRAPI
DmAutomationDisconnectController(
    IN DWORD dwUserIndex
    );

DMHRAPI
DmAutomationSetGamepadState(
    IN DWORD dwUserIndex,
    IN PDM_XINPUT_GAMEPAD pXGamepad
    );

DMHRAPI
DmAutomationQueueGamepadState(
    IN  DWORD  dwUserIndex,
    IN  PDM_XINPUT_GAMEPAD pGamepadArray,
    IN  PDWORD pdwTimedDurationArray OPTIONAL,
    IN  PDWORD pdwCountDurationArray OPTIONAL,
    IN  DWORD  dwItemCount,
    OUT PDWORD pdwItemsAddedToQueue
    );

DMHRAPI
DmAutomationClearGamepadQueue (
    IN  DWORD  dwUserIndex
    );

DMHRAPI
DmAutomationQueryGamepadQueue(
    IN  DWORD   dwUserIndex,
    OUT PDWORD	pdwQueueLength OPTIONAL, 
    OUT PDWORD	pdwItemsInQueue OPTIONAL,
    OUT PDWORD	pdwTimedDurationRemaining OPTIONAL,
    OUT PDWORD	pdwCountDurationRemaining OPTIONAL
    );

typedef unsigned __int64 DM_XUID, *PDM_XUID;

DMHRAPI
DmAutomationGetUserDefaultProfile(
    OUT PDM_XUID pXuid
    );

DMHRAPI
DmAutomationSetUserDefaultProfile(
    DM_XUID xuid
    );

#ifdef __cplusplus
}
#endif


#endif  //__XBDM_H__
