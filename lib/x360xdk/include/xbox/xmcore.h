/************************************************************************
*                                                                       *
*   XMCore.h -- This module defines the Xbox multicore APIs             *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/
#pragma once 

#ifdef __cplusplus
extern "C"
{  
#endif


///////////////////////////////
// LOCK FREE DECLARATIONS    //
///////////////////////////////

typedef DWORD_PTR XLOCKFREE_HANDLE;
typedef DWORD_PTR XLOCKFREE_LOG;

/////////////////////////////////////////////////////////////////////////////
// Wait function prototype called when a lock-free data structure needs    //
// to block before it can add an element or must wait to remove an         //
// element. Routine must return WAIT_OBJECT_0 if event is signaled.        //
/////////////////////////////////////////////////////////////////////////////
typedef DWORD (CALLBACK *XLockFreeWait)(PVOID context,            // Developer supplied context for the wait.
                                        HANDLE event,             // Event the xmcore library wants to wait on. 
                                        DWORD dwMilliSeconds,     // Expected wait time.
                                        BOOL fAlertable);         // Should the wait allow APC's

///////////////////////////////////////////////////////////////////////////////
// Function prototypes if allocators are to be replace. Memory call backs    //
// are specific to one data structure. If all allocations need to be         //
// replaced then XMemAlloc can be overridden.                                //
///////////////////////////////////////////////////////////////////////////////
typedef PVOID (CALLBACK *XLockFreeMemoryAllocate)(PVOID context, DWORD dwSize);
typedef void (CALLBACK *XLockFreeMemoryFree)(PVOID context, PVOID pAddress);

//////////////////////////////////////////////////////////////////////////////
// Default Allocation routines used by the lock free library. Allocation    //
// is done through XMemAlloc using allocator ID                             //
// eXALLOCAllocatorID_XMCORE.                                               //
//////////////////////////////////////////////////////////////////////////////
PVOID  APIENTRY XLFAllocate(DWORD dwSize);
void   APIENTRY XLFFree(PVOID pAddress);

/////////////////////////////
// Lock free attributes    //
/////////////////////////////
#define XLOCKFREE_NO_ATTRIBUTES                   0x000
#define XLOCKFREE_ATTRIBUTE_FLAG                  0x001    // Reservered for internal use
#define XLOCKFREE_RESERVED_FLAG                   0x002
#define XLOCKFREE_ADD_WAIT                        0x004    // Wait until there is room in the queue/stack to add an element.
#define XLOCKFREE_REMOVE_WAIT                     0x008    // Wait until there is an entry to remove from the queue/stack.
#define XLOCKFREE_SPIN_ON_ADD                     0x010    // If we need to wait do we spin first before adding an entry
#define XLOCKFREE_SPIN_ON_REMOVE                  0x020    // If we need to wait do we spin first before removing an entry
#define XLOCKFREE_ALERTABLE_ADD                   0x040    // If we wait while adding an entry, is the wait altertable
#define XLOCKFREE_ALERTABLE_REMOVE                0x080    // If we wait while removing an entry, is the wait  altertable
#define XLOCKFREE_SINGLE_KEY_ENTRY                0x100    // Allow a single key value (PRIORITY QUEUE and HASH TABLE only)

/////////////////////////////////////////////////////////////////////////////
// The XLOCKFREE_CREATE structure is used to initialize the data           //
// structures. All entries in the structure are optional. The structure    //
// can be used to create data structures that have customized wait         //
// characteristics and memory allocations.                                 //
/////////////////////////////////////////////////////////////////////////////
typedef struct _XLOCKFREE_CREATE
{
    DWORD attributes;              // See attributes defined above (OPTIONAL)
    PVOID addWaitContext;          // User data passed when in when an add would wait (OPTIONAL)
    PVOID removeWaitContext;       // User data passed when in when a remove would wait (OPTIONAL)
    DWORD addWaitTime;             // Amount of time to wait before a timeout happens when adding an element (OPTIONAL)
    DWORD removeWaitTime;          // Amount of time to wait before a timeout happens when deleting an element (OPTIONAL)
    XLockFreeWait addWait;         // Custom wait function used if an element cannot be added to the data structure (OPTIONAL)
    XLockFreeWait removeWait;      // Custom wait function used if there is no element to removed from the data structure (OPTIONAL)
   
    // All information after here is used only during creation
    DWORD structureSize;                 // Must be set to sizeof(XLOCKFREE_CREATE)!.
    DWORD allocationLength;              // Number of elements to allocate when the data structure needs to allocate more nodes (OPTIONAL)
    DWORD maximumLength;                 // Total number of entries allowed in the data structure. -1 or 0 means unlimited (OPTIONAL)
    XLockFreeMemoryAllocate allocate;    // Custom Allocator (OPTIONAL)
    XLockFreeMemoryFree     free;        // Matching release for custom Allocator (OPTIONAL)
    PVOID memoryContext;                 // Memory context if required.
} XLOCKFREE_CREATE, *PXLOCKFREE_CREATE;

///////////////////////////////////////////////////////////////////////////////
// XXLFInitializeCreate will initialize a XLOCKFREE_CREATE structure with    //
// all the default settings.                                                 //
///////////////////////////////////////////////////////////////////////////////
HRESULT XLFInitializeCreate(IN PXLOCKFREE_CREATE lockFreeAttributes);

////////////////////////////////////////////////////////////////////////////
// The 'C' API for the queue data structure provides the ability to       //
// create, destroy, add elements and remove elements from a FIFO          //
// queue. The queue is an opaque handle that must be passed into every    //
// function.                                                              //
////////////////////////////////////////////////////////////////////////////
HRESULT XLFQueueAdd(IN XLOCKFREE_HANDLE queue, IN void* data);
HRESULT XLFQueueAllocated(IN XLOCKFREE_HANDLE queue, OUT DWORD* size);
HRESULT XLFQueueCreate(IN PXLOCKFREE_CREATE info, OUT XLOCKFREE_HANDLE* queue);
void    XLFQueueDestroy(IN XLOCKFREE_HANDLE queue);
HRESULT XLFQueueGetEntryCount(IN XLOCKFREE_HANDLE queue, OUT LONG* entries);
BOOL    XLFQueueIsEmpty(IN XLOCKFREE_HANDLE queue);
HRESULT XLFQueueRemove(IN XLOCKFREE_HANDLE queue, OUT void** data);

//////////////////////////////////////////////////
// The 'C' API for the stack data structure.    //
//////////////////////////////////////////////////
HRESULT XLFStackAllocated(IN XLOCKFREE_HANDLE stack, OUT DWORD* size);
HRESULT XLFStackCreate(IN PXLOCKFREE_CREATE info, OUT XLOCKFREE_HANDLE* stack);
void    XLFStackDestroy(IN XLOCKFREE_HANDLE stack);
HRESULT XLFStackGetEntryCount(IN XLOCKFREE_HANDLE stack, OUT LONG* entries);
BOOL    XLFStackIsEmpty(IN XLOCKFREE_HANDLE stack);
HRESULT XLFStackPop(IN XLOCKFREE_HANDLE stack, OUT void** data);
HRESULT XLFStackPush(IN XLOCKFREE_HANDLE stack, IN void* data);

///////////////////////////////////////////////////////////////////////////////
// Compare functions to compare and hash keys used in Priority Queues and    //
// Hash Tables. Call back functions can be used in the Priority Queue and    //
// Hash Table to customize how entries are added and removed from the        //
// data structures.                                                          //
///////////////////////////////////////////////////////////////////////////////
typedef int (CALLBACK *XLockFreeCompareKeys)(int, int);
typedef unsigned int (CALLBACK *XLockFreeHashKey)(DWORD key, DWORD size);

typedef struct _XLOCKFREE_FUNCTIONS
{
    XLockFreeCompareKeys compare;                     // Function to compare to keys (OPTIONAL)
    XLockFreeHashKey     hash;                        // Function that calculates the bucket [hashtable only] (OPTIONAL)
    DWORD                structureSize;               // Must be set to the sizeof(XLOCKFREE_FUNCTIONS).
} XLOCKFREE_FUNCTIONS, *PXLOCKFREE_FUNCTIONS;

///////////////////////////////////////////////////////////
// The 'C' API for the priority queue data structure.    //
///////////////////////////////////////////////////////////
HRESULT XLFPriorityQueueAdd(IN XLOCKFREE_HANDLE queue, IN DWORD key, IN PVOID data);
HRESULT XLFPriorityQueueAllocated(IN XLOCKFREE_HANDLE queue, OUT DWORD* size);
HRESULT XLFPriorityQueueCreate(IN PXLOCKFREE_CREATE info, IN PXLOCKFREE_FUNCTIONS functions, OUT XLOCKFREE_HANDLE* queue);
void    XLFPriorityQueueDestroy(IN XLOCKFREE_HANDLE queue);
HRESULT XLFPriorityQueueGetEntryCount(IN XLOCKFREE_HANDLE queue, OUT LONG* entries);
BOOL    XLFPriorityQueueIsEmpty(IN XLOCKFREE_HANDLE queue);
HRESULT XLFPriorityQueueRemoveFirst(IN XLOCKFREE_HANDLE queue, OUT PVOID* data);
HRESULT XLFPriorityQueueRemove(IN XLOCKFREE_HANDLE queue, IN DWORD key, OUT PVOID* data);

///////////////////////////////////////////////////////
// The 'C' API for the hash table data structure.    //
///////////////////////////////////////////////////////
HRESULT XLFHashTableAdd(IN XLOCKFREE_HANDLE hashTable, IN DWORD key, IN PVOID data);
HRESULT XLFHashTableAllocated(IN XLOCKFREE_HANDLE hashTable, OUT DWORD* size);
HRESULT XLFHashTableCreate(IN PXLOCKFREE_CREATE info, IN PXLOCKFREE_FUNCTIONS functions, IN DWORD buckets, OUT XLOCKFREE_HANDLE* hashTable);
void    XLFHashTableDestroy(IN XLOCKFREE_HANDLE hashTable);
HRESULT XLFHashTableGetEntryCount(IN XLOCKFREE_HANDLE hashTable, OUT LONG* entries);
BOOL    XLFHashTableIsEmpty(IN XLOCKFREE_HANDLE hashTable);
HRESULT XLFHashTableRemoveFirst(IN XLOCKFREE_HANDLE hashTable, OUT PVOID* data);
HRESULT XLFHashTableRemove(IN XLOCKFREE_HANDLE hashTable, IN DWORD key, OUT PVOID* data);


//////////////////
// LOCK POOL    //
//////////////////
#define XLOCKFREE_POOL_ALLOW_RECURSION            0x1    // Allow recursive calls to locks
#define XLOCKFREE_POOL_WATCH_THREAD               0x2    // Fail if another thread tries to destroy a lock
#define XLOCKFREE_POOL_ACQUIRE_WAIT               0x4    // Wait until the lock can be acquired 
#define XLOCKFREE_POOL_SPIN_ON_WAIT               0x10   // If we need to wait do we spin first
#define XLOCKFREE_POOL_ALERTABLE_WAIT             0x20   // If we wait, the wait is altertable
    
typedef enum _TWO_WAY_LOCK_ACTIONS
{
    XLF_LOCK_SHARED,              // acquire shared lock (may require waiting); 
    XLF_LOCK_EXCLUSIVE,           // acquire exclusive lock (may require waiting); 
    XLF_LOCK_DOWNGRADE,           // downgrade exclusive lock to shared (non-blocking request); 
    XLF_LOCK_UPGRADE_SAFELY,      // upgrade shared lock to exclusive in order (may require waiting); 
    XLF_LOCK_UPGRADE_IGNORE       // upgrade shared 
} TWO_WAY_LOCK_ACTIONS;

typedef struct _TWO_WAY_LOCK
{
    __int64 data[2];
} TWO_WAY_LOCK, *PTWO_WAY_LOCK;

typedef struct _XLOCKFREE_POOL
{
    DWORD attributes;              // See attributes defined above (OPTIONAL)
    DWORD allocationLength;        // Number of elements to allocate when the data
                                   //   structure needs to allocate more nodes (OPTIONAL)
    PVOID waitContext;             // User data passed into the wait function associated
                                   //   with the data structure (OPTIONAL)
    DWORD acquireWaitTime;         // Amount of time to wait before a timeout happens when acquiring a lock
    XLockFreeWait acquireWait;     // Custom wait function used if an element cannot be
                                   //    added to the data structure (OPTIONAL)
    DWORD structureSize;           // Must be set to sizeof(XLOCKFREE_POOL).
} XLOCKFREE_POOL, *PXLOCKFREE_POOL;


HRESULT XLFPoolAcquireLock(IN XLOCKFREE_HANDLE pool, IN TWO_WAY_LOCK_ACTIONS action, IN TWO_WAY_LOCK* lock);
HRESULT XLFPoolAllocated(IN XLOCKFREE_HANDLE pool, OUT DWORD* size);
HRESULT XLFPoolCreate(IN XLOCKFREE_POOL* info, OUT XLOCKFREE_HANDLE* pool);
HRESULT XLFPoolCreateLock(IN XLOCKFREE_HANDLE pool, OUT PTWO_WAY_LOCK* lock);
void    XLFPoolDestroy(IN XLOCKFREE_HANDLE pool);
HRESULT XLFPoolDestroyLock(IN XLOCKFREE_HANDLE pool, IN TWO_WAY_LOCK* lock);
HRESULT XLFPoolIncreaseEvents(IN XLOCKFREE_HANDLE pool, IN DWORD number);
HRESULT XLFPoolIncreaseLocks(IN XLOCKFREE_HANDLE pool, IN DWORD number);
HRESULT XLFPoolInitializeLock(IN XLOCKFREE_HANDLE pool, IN TWO_WAY_LOCK* lock);
HRESULT XLFPoolNumberOfEvents(IN XLOCKFREE_HANDLE pool, OUT DWORD* number);
HRESULT XLFPoolNumberOfLocks(IN XLOCKFREE_HANDLE pool, OUT DWORD* number);
HRESULT XLFPoolReleaseLock(IN XLOCKFREE_HANDLE pool, IN TWO_WAY_LOCK_ACTIONS action, IN TWO_WAY_LOCK* lock);

////////////////////
// Error codes    //
////////////////////
#define FACILITY_XLOCKFREE 0x31
#define XLOCKFREE_STRUCTURE_FULL                ((HRESULT)0x80310001L)
#define XLOCKFREE_STRUCTURE_EMPTY               ((HRESULT)0x80310002L)
#define XLOCKFREE_INVALID_ACTION                ((HRESULT)0x80310003L) // When releasing a lock the action must be XLF_LOCK_SHARED or XLF_LOCK_EXCLUSIVE


////////////////////////////////////////////////////////////////////////////
// LOGGING FACILITY                                                       //
//                                                                        //
// Create a log file that does the physical writes to the file on the     //
// requested core. The log allocates a fixed number of messages of a      //
// specified length. The can log can either be blocking or                //
// non-blocking. If the log is non-blocking it will drop messages. The    //
// number of dropped messages is reported when the log is shut down.      //
////////////////////////////////////////////////////////////////////////////
typedef HRESULT (CALLBACK *XLFLogMessage)(PVOID messageContext, PBYTE buffer, DWORD length);
HRESULT XLFStartLog(int requestedCore,     // Run the logging facility on this core
                    LPCSTR logFile,        // Log messages to this file
                    int messageLength,     // Maximum message length
                    int numberOfMessages,  // Maximum number of messages allowed to be queued up 
                    BOOL blockOnWrite,     // Block if queue is at is maximum
                    XLOCKFREE_LOG* log);   // Handle to the log is returned

HRESULT XLFStartUserLog(int requestedCore,     // Run the logging facility on this core
                        PVOID messageContext,  // Context passed to the callback
                        XLFLogMessage callback, // Callback processes message 
                        int messageLength,     // Maximum message length
                        int numberOfMessages,  // Maximum number of messages allowed to be queued up 
                        BOOL blockOnWrite,     // Block if queue is at is maximum
                        XLOCKFREE_LOG* log);   // Handle to the log is returned

void    XLFEndLog(XLOCKFREE_LOG log);
void    XLFLogPrint(XLOCKFREE_LOG log, const char* format, ...);
void    XLFLogBuffer(XLOCKFREE_LOG log, PBYTE buffer, DWORD length);



///////////////////////////////////////////////////////////////////////////
// XLockFree library will RIP in debug mode unless a error handler is    //
// supplied and it returns S_OK after being passed an error message.     //
///////////////////////////////////////////////////////////////////////////
typedef HRESULT (CALLBACK *XLockFreeErrorHandler)(const char* msg);
XLockFreeErrorHandler APIENTRY XLockFreeGetErrorHandler(void);
XLockFreeErrorHandler APIENTRY XLockFreeSetErrorHandler(XLockFreeErrorHandler func);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

///////////////////////////////////////////////////////////////////////////////////////////
// Elements added to the lock free data structures do not need to                        //
// inherit a link structure. These algorithm allocate external link                      //
// structures because it is very difficult to know when the link structures              //
// can be released or changed. The link structure can be referenced on                   //
// multiple threads at the same and failure can occur if the link structure is updated   //
// outside the data structure.                                                           //
//                                                                                       //
// User data cannot be delete when it is added to a list. After the data                 //
// is removed from a list it can be safely deleted at any time.                          //
// Only one thread will have a reference to the user data after it is                    //
// removed from a list.                                                                  //
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
// XLockFreeStack                                                                        //
// --------------                                                                        //
// Creates a stack structure that can accept T objects. The stack stores pointers        //
// to T, it does not copy the contents of T. If the object T is deleted while the        //
// stack holds a reference results can be unpredictable.                                 //
//                                                                                       //
// Care needs to be taken when creating a stack structure that will be visible to        //
// multiple threads. The stack should either be constructed before threads are           //
// started, passed as a parameter to the thread procedure, or have global references     //
// updated using an interlocked function.                                                //
///////////////////////////////////////////////////////////////////////////////////////////

template <class _T> class XLockFreeStack 
{
  public:
    XLockFreeStack();   // Creates a stack structure. 
    ~XLockFreeStack();  // Releases all the stack resources.

    ///////////////////////////////////////////////////////////////////////////
    // Manually release all the stack resources.                             //
    ///////////////////////////////////////////////////////////////////////////
    void     Destroy(); 

    ///////////////////////////////////////////////////////////////////////////
    // Returns the amount of memory allocated for the stack.                 //
    ///////////////////////////////////////////////////////////////////////////
    DWORD GetAllocated() const;

    ///////////////////////////////////////////////////////////////////////////
    // Returns the maximum number entries that could be in the stack         //
    ///////////////////////////////////////////////////////////////////////////
    DWORD GetEntryCount() const;

    ///////////////////////////////////////////////////////////////////////////
    // Creates a Stack structure that will allocate nodes as required and    //
    // will not block on Pushes and Pops.                                    //
    ///////////////////////////////////////////////////////////////////////////
    HRESULT Initialize();       

    ////////////////////////////////////////////////////////////////////////////
    // Creates a queue structure where the maximum number of elements, the    //
    // number of allocations and whether calls will block can be              //
    // specified. If waiting is specified in the attributes then an           //
    // optional custom Wait functions can be also added.                      //
    ////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(PXLOCKFREE_CREATE info);

    // Returns TRUE if there are no items in the stack.
    BOOL IsEmpty() const;

    //////////////////////////////////////////////////////////////////////////////
    // Returns the top data type in the stack. Returns NULL if no entry is      //
    // available. Because the stack can be used in a multithreaded              //
    // environment it is very possible that a call to IsEmpty() will return     //
    // FALSE and the Pop() will return NULL.  By the time the Pop() has         //
    // executed another thread may have taken all the available entries. The    //
    // program must always test for a NULL.                                     //
    //////////////////////////////////////////////////////////////////////////////
    _T* Pop(); 

    ///////////////////////////////////////////////////////////////////////////
    // Returns the top data type in the stack.  Returns                      //
    // XLOCKFREE_STRUCTURE_EMPTY if no entry is available.  If there is a    //
    // wait function added to the stack the error code from that function    //
    // would be returned in the case of a failure.                           //
    ///////////////////////////////////////////////////////////////////////////
    HRESULT Pop(_T** ref); 

    /////////////////////////////////////////////////////////////////////////////
    // Adds a data type to the stack.  Returns XLOCKFREE_STRUCTURE_FULL if     //
    // the stack was full.  If there is a wait function added to the stack     //
    // the error code from that function would be returned in the case of a    //
    // failure.                                                                //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Push(_T* entry);

    PVOID operator new( size_t size);
    void  operator delete(PVOID p);
    PVOID operator new[]( size_t size);
    void  operator delete[](PVOID p);

  private:
    XLOCKFREE_HANDLE stack;
    XLockFreeStack(const XLockFreeStack& s) {} // Copy constructor not allowed
};


///////////////////////////////////////////////////////////////////////////////
// XLockFreeQueue                                                            //
// --------------                                                            //
//                                                                           //
// Creates an queue structure that can accept T objects. The queue stores    //
// pointers to T, it does not copy the contents of T. If the object T is     //
// deleted while the queue holds a reference results can be                  //
// unpredictable.                                                            //
//                                                                           //
// Creates a queue structure. Care needs to be taken when creating a         //
// queue structure that will be visible to multiple threads. The queue       //
// should be constructed before threads are started, should be passed as     //
// a parameter to the thread procedure, or should have the global            //
// reference updated using an interlocked function.                          //
///////////////////////////////////////////////////////////////////////////////

template <class _T> class XLockFreeQueue
{
public:
    XLockFreeQueue(); 
    ~XLockFreeQueue(); 

    /////////////////////////////////////////////////////////////////////////////
    // Adds an entry to the queue, returns S_OK if element successfully        //
    // added.  Returns XLOCKFREE_STRUCTURE_FULL if a free node was not         //
    // available to link in the data.  If there is a wait function added to    //
    // the stack the error code from that function would be returned in the    //
    // case of a failure.                                                      //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Add(_T* entry); 

    ///////////////////////////////////////////////////////////////////////////
    // Manually releases all the resources associated with the queue. The    //
    // queue should not be used after this method has been called.           //
    ///////////////////////////////////////////////////////////////////////////
    void    Destroy();

    //////////////////////////////////////////////////////////////
    // Returns the amount of memory allocated for the Queue.    //
    //////////////////////////////////////////////////////////////
    DWORD GetAllocated() const;

    //////////////////////////////////////////////////////////////////////
    // Returns the maximum number entries that could be in the stack    //
    //////////////////////////////////////////////////////////////////////
    DWORD GetEntryCount() const;

    ///////////////////////////////////////////////////////////////////////////////
    // Creates a queue structure that will grow as necessary and will not        //
    // block on when adding or removing elements. An Initialize() method must    //
    // be called before the queue can be used.                                   //
    ///////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize();

    ////////////////////////////////////////////////////////////////////////////
    // Creates a queue structure where the maximum number of elements, the    //
    // number of allocations and whether calls will block can be              //
    // specified. If waiting is specified in the attributes then an           //
    // optional custom Wait functions can be also added.                      //
    ////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(PXLOCKFREE_CREATE info);

    //////////////////////////////////////////////////////////////
    // Returns TRUE if there currently no items in the queue    //
    //////////////////////////////////////////////////////////////
    BOOL IsEmpty() const; 

    //////////////////////////////////////////////////////////////////////////////
    // Returns the last entry in the queue. Returns NULL if no entry is         //
    // available. Because the queue can be used in a multithreaded              //
    // environment it is very possible that a call to IsEmpty() will return     //
    // FALSE and Remove() will return NULL.  By the time the Remove() has       //
    // executed another thread may have taken all the available entries. The    //
    // program must always test for a NULL.                                     //
    //////////////////////////////////////////////////////////////////////////////
    _T* Remove();

    ///////////////////////////////////////////////////////////////////////////////
    // Returns the last entry in the queue.  Return XLOCKFREE_STRUCTURE_EMPTY    //
    // if no entry is available.  If there is a wait function added to the       //
    // queue the error code from that function would be returned in the case     //
    // of a failure.                                                             //
    ///////////////////////////////////////////////////////////////////////////////
    HRESULT Remove(_T** ref);                   

    PVOID operator new( size_t size );
    void  operator delete(PVOID p);
    PVOID operator new[]( size_t size );
    void  operator delete[](PVOID p);
private:
    XLockFreeQueue(const XLockFreeQueue& q) {} // Copy constructor not allowed
    XLOCKFREE_HANDLE queue;
};


class XLockFreeCustom
{ 
public:
    static int compare(int p1, int p2); 
    static unsigned int hash(unsigned int key, unsigned int buckets);
    static unsigned int bucketSize(unsigned int buckets);
};

template <class _T,
    class _Functions = XLockFreeCustom>
class XLockFreeFunctions
{
public:
    XLockFreeFunctions() {}
    XLockFreeFunctions(_Functions c) : _func(c) {}
protected:
    _Functions _func;
};

/////////////////////////////////////////////////////////////////////////////
// XLockFreePriorityQueue                                                  //
// ----------------------                                                  //
//                                                                         //
// Creates a queue structure that can accept T objects. The default        //
// implementation supplies functions for comparing keys and for hashing    //
// the key.                                                                //
//                                                                         //
// Creates a priority queue structure. Care needs to be taken when         //
// creating a priority queue structure that will be visible to multiple    //
// threads. The queue should be constructed before threads are started,    //
// should be passed as a parameter to the thread procedure, or should      //
// have the global reference updated using an interlocked function.        //
/////////////////////////////////////////////////////////////////////////////

template <class _T,
          class _XFunctions = XLockFreeFunctions<_T> >
class XLockFreePriorityQueue : _XFunctions
{
public:
    XLockFreePriorityQueue();
    ~XLockFreePriorityQueue(); 
    
    ////////////////////////////////////////////////////////////////////////////////
    // Adds and entry to the priority queue.  Returns                             //
    // XLOCKFREE_STRUCTURE_FULL if there is no space to add the entry             //
    //                                                                            //
    // Returns XLOCKFREE_STRUCTURE_FULL if there is no space to add the           //
    // entry or the key exists in the queue and the queue was initialized         //
    // with XLOCKFREE_SINGLE_ENTRY                                                //
    //                                                                            //
    // If there is a wait function added to the queue the error code from that    //
    // function would be returned in the case of a failure                        //
    ////////////////////////////////////////////////////////////////////////////////
    HRESULT Add(DWORD key, _T* entry);

    ///////////////////////////////////////////////////////////////////////////////
    // Manually release all the priority queue resources.  The priority queue    //
    // should not be used after this method has been called.                     //
    ///////////////////////////////////////////////////////////////////////////////
    void    Destroy();

    ///////////////////////////////////////////////////////////////////////
    // Returns the amount of memory allocated for the priority queue.    //
    ///////////////////////////////////////////////////////////////////////
    DWORD GetAllocated() const;

    ////////////////////////////////////////////////////////////////////////////////
    // Returns the maximum number of entries that could be in the priority queue. //
    ////////////////////////////////////////////////////////////////////////////////
    DWORD GetEntryCount() const;

    ///////////////////////////////////////////////////////////////////////////////
    // Creates a priority queue structure that will allocate nodes as            //
    // required to add new entries and will not block when adding or removing    //
    // entries.                                                                  //
    ///////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize();

    /////////////////////////////////////////////////////////////////////////////
    // Creates a priority queue structure where the maximum number of          //
    // elements, the number of allocations and whether calls will block can    //
    // be specified. If waiting is specified in the attributes then an         //
    // optional custom Wait functions can be also added.                       //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(PXLOCKFREE_CREATE info);
    
    ////////////////////////////////////////////////////////////////////////////
    // Returns TRUE if there are currently no items in the priority queue     //
    ////////////////////////////////////////////////////////////////////////////
    BOOL IsEmpty() const; 

    /////////////////////////////////////////////////////////////////////////////
    // Returns the first entry in the priority queue (the entry with the       //
    // lowest key).  Returns NULL if no entry is available.  Because the       //
    // queue can be used in a multithreaded environment it is very possible    //
    // that a call to Search() will return TRUE and Remove() will return       //
    // NULL.  By the time the Remove() has executed another thread may have    //
    // taken entries. The program must always test for a NULL.                 //
    /////////////////////////////////////////////////////////////////////////////
    _T* RemoveFirst();

    //////////////////////////////////////////////////////////////////////////////
    // Returns the first entry in the queue (the entry with the lowest key).    //
    // Returns XLOCKFREE_STRUCTURE_EMPTY if no entry is available.  If there    //
    // is a wait function added to the queue the error code from that           //
    // function would be returned in the case of a failure.                     //
    //////////////////////////////////////////////////////////////////////////////
    HRESULT RemoveFirst(_T** ref);

    ///////////////////////////////////////////////////////////////////////////////
    // Returns the entry in the queue identified by 'key'. Returns NULL if no    //
    // entry is available. Because the queue can be used in a multithreaded      //
    // environment it is very possible that a call to Search() will return       //
    // TRUE and Remove() will return NULL.  By the time the Remove() has         //
    // executed another thread may have taken entries. The program must          //
    // always test for a NULL.                                                   //
    ///////////////////////////////////////////////////////////////////////////////
    _T* Remove(DWORD key);

    ///////////////////////////////////////////////////////////////////////////
    // Returns the entry in the queue identified by 'key'.  Returns          //
    // XLOCKFREE_STRUCTURE_EMPTY if no entry is available.  If there is a    //
    // wait function added to the queue the error code from that function    //
    // would be returned in the case of a failure.                           //
    ///////////////////////////////////////////////////////////////////////////
    HRESULT Remove(DWORD key, _T** ref);

    PVOID operator new( size_t size );
    void  operator delete(PVOID p);
    PVOID operator new[]( size_t size );
    void  operator delete[](PVOID p);

private:
    XLockFreePriorityQueue(const XLockFreePriorityQueue& q) {} // Copy constructor not allowed.
    XLOCKFREE_HANDLE queue;
};



/////////////////////////////////////////////////////////////////////////////////
// XLockFreeHashTable                                                          //
// ------------------                                                          //
//                                                                             //
// Creates a hash table that can accept T objects. The default                 //
// implementation supplies functions for comparing keys and for hashing        //
// the key                                                                     //
//                                                                             //
// Creates a hash table structure. Care needs to be taken when                 //
// creating a hash table structure that will be visible to multiple            //
// threads. The hash table should be constructed before threads are started    //
// should be passed as a parameter to the thread procedure, or should          //
// have the global reference updated using an interlocked function             //
/////////////////////////////////////////////////////////////////////////////////

template <class _T,
          class _XFunctions = XLockFreeFunctions<_T> >
class XLockFreeHashTable : _XFunctions
{
public:
    XLockFreeHashTable(); 
    ~XLockFreeHashTable(); 

    /////////////////////////////////////////////////////////////////////////////
    // Adds an entry to the hash table. The entries are added in the           //
    // numerical order of the keys.                                            //
    //                                                                         //
    // Returns XLOCKFREE_STRUCTURE_FULL if there is no space to add the entry  //
    // or the entry exists in the table and the table was initialized with     //
    // XLOCKFREE_SINGLE_ENTRY.                                                 //
    //                                                                         //
    // If there is a wait function added to the queue the error code from      //
    // that function would be returned in the case of a failure                //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Add(DWORD key, _T* entry);

    /////////////////////////////////////////////////////////////////////////////
    // Manually release all the hash table resources. The hash table should    //
    // not be used after this method is called.                                //
    /////////////////////////////////////////////////////////////////////////////
    void    Destroy();

    /////////////////////////////////////////////////////////////////////////////
    // Returns the amount of memory currently allocated for the hash table.    //
    /////////////////////////////////////////////////////////////////////////////
    DWORD GetAllocated() const;

    /////////////////////////////////////////////////////////////////////////////
    // Returns the maximum number of entries that could be in the hash table.  //
    /////////////////////////////////////////////////////////////////////////////
    DWORD GetEntryCount() const;

    /////////////////////////////////////////////////////////////////////////////
    // Creates a hash table that will allocate nodes as required to add new    //
    // entries and will not block when adding or removing entries.             //
    //                                                                         //
    // There hash table will be created with a fixed number of buckets.        //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(DWORD buckets);

    /////////////////////////////////////////////////////////////////////////////
    // Creates a hash table structure where the maximum number of elements,    //
    // the number of allocations and whether calls will block can be           //
    // specified. If the maximum number of elements is specified then          //
    // optional custom Wait functions can be also added.                       //
    //                                                                         //
    // There hash table will be created with a fixed number of buckets.        //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(PXLOCKFREE_CREATE info, DWORD buckets);

    /////////////////////////////////////////////////////////////////////////////
    // Returns TRUE if there are currently no items in the hash table          //
    /////////////////////////////////////////////////////////////////////////////
    BOOL IsEmpty() const; 

    /////////////////////////////////////////////////////////////////////////////
    // Returns the first entry in the hash table (the entry with the lowest    //
    // key).                                                                   //
    //                                                                         //
    // Returns NULL if no entry is available.                                  //
    /////////////////////////////////////////////////////////////////////////////
    _T* RemoveFirst();

    ////////////////////////////////////////////////////////////////////////////
    // Returns the first entry in the hash table queue (the entry with the    //
    // lowest key).                                                           //
    //                                                                        //
    // Returns XLOCKFREE_STRUCTURE_EMPTY if no entry is available.            //
    ////////////////////////////////////////////////////////////////////////////
    HRESULT RemoveFirst(_T** ref);

    ///////////////////////////////////////////////////////////////////////////////
    // Returns the entry in the table identified by 'key'. Returns NULL if no    //
    // entry is available. Because the table can be used in a multithreaded      //
    // environment it is very possible that a call to Remove() will return       //
    // NULL. The program must always test for a NULL.                            //
    ///////////////////////////////////////////////////////////////////////////////
    _T* Remove(DWORD key);

    ///////////////////////////////////////////////////////////////////////////
    // Returns the entry in the queue identified by 'key'.                   //
    //                                                                       //
    // Returns XLOCKFREE_STRUCTURE_EMPTY if no entry is available.           //
    //                                                                       //
    // If there is a wait function added to the queue the error code from    //
    // that function would be returned in the case of a failure.             //
    ///////////////////////////////////////////////////////////////////////////
    HRESULT Remove(DWORD key, _T** ref);

    PVOID operator new( size_t size );
    void  operator delete(PVOID p);
    PVOID operator new[]( size_t size );
    void  operator delete[](PVOID p);
private:
    XLOCKFREE_HANDLE hashTable;
    XLockFreeHashTable(const XLockFreeHashTable& h) {}
};


/////////////////////////////////////////////////////////////////////////////////
// Often the number of lockable objects is huge. For example, an               //
// implementation of a thread-safe hash table requires one lock per hash       //
// chain (using one lock per hash table considerably reduces                   //
// performance). In such situations the number of two-way locks (and thus      //
// event handles and size of memory required) grows proportionally to the      //
// number of lockable objects.                                                 //
//                                                                             //
// This class implements a pool of fast two locks. A fast two lock provides    //
// exclusive or shared access where requests for exclusive lock will be        //
// satisfied ahead of any requests for shared locks (it does not matter        //
// of timing (traditional implementations process lock requests on "first      //
// came first served" basis).                                                  //
//                                                                             //
// In this implementation the number of event/semaphore pairs that are         //
// actually required never exceeds the max number of threads running           //
// simultaneousely (this limit may be reached on complete deadlock), and       //
// since this number of threads that process may simultaneousely create is     //
// very limited and the use of too many threads (more than few dozens)         //
// considerably reduces performance, the total amount of required              //
// synchonization events is limited and does not depend on number of           //
// lockable objects.                                                           //
/////////////////////////////////////////////////////////////////////////////////

class XLockFreeLockPool
{
  public:
    XLockFreeLockPool();
    ~XLockFreeLockPool();

    //
    // Pool functions
    //
    /////////////////////////////////////////////////////////////////////////////
    // Releases all resources associated with the pool The pool cannot be      //
    // used after calling this function.                                       //
    /////////////////////////////////////////////////////////////////////////////
    void    Destroy();

    /////////////////////////////////////////////////////////////////////////////
    // Returns the amount of memory allocated for the Pool.                    //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT GetAllocated(DWORD* allocated);

    /////////////////////////////////////////////////////////////////////////////
    // Sets up the lock pool. This must be done prior to any other methods     //
    // calls on the Pool are attempted. If multiple threads will be accessing  //
    // the Pool it must be finished initializing before any other thread uses  //
    // the object.                                                             //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize();

    /////////////////////////////////////////////////////////////////////////////
    // Initializes the pool with custom information.  The amount of memory     //
    // that is allocated, whether a thread should wait or not when accessing   //
    // the pool, and what the custom wait function should be.                  //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Initialize(XLOCKFREE_POOL* info);

    //
    // Lock functions
    //
    /////////////////////////////////////////////////////////////////////////////
    // Acquire a lock. The lock can either be shared (multiple readers) or     //
    // exclusive (one writer). The writers are queued up in order of           //
    // requests. The only exception to this is when a shared lock is           //
    // upgraded.                                                               //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Acquire(TWO_WAY_LOCK_ACTIONS action, TWO_WAY_LOCK* lock);

    /////////////////////////////////////////////////////////////////////////////
    // Returns the number of locks allocated for the pool (does not include    //
    // locks that were created using external memory - see SetupExternal())    //
    /////////////////////////////////////////////////////////////////////////////
    DWORD GetCount() const;

    /////////////////////////////////////////////////////////////////////////////
    // Increases the number of locks created in the Pool. Useful when the      //
    // total number of locks is known.                                         //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Increase(DWORD number);

    /////////////////////////////////////////////////////////////////////////////
    // Creates a lock that can be used to protect data or synchronize          //
    // execution.  The lock is created using the Pool's memory routines.       //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Obtain(TWO_WAY_LOCK** lock);

    /////////////////////////////////////////////////////////////////////////////
    // Releases a lock that has been acquired (see Acquire()).  The action     //
    // must be identical to the action used when acquiring the lock.           //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Release(TWO_WAY_LOCK_ACTIONS action, TWO_WAY_LOCK* lock);

    /////////////////////////////////////////////////////////////////////////////
    // Returns the lock to pool so it can be reused. Only locks that were      //
    // created with Obtain() can be returned to the pool. Locks that are       //
    // created using SetupExternal() are not returned.                         //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT Return(TWO_WAY_LOCK* lock);

    /////////////////////////////////////////////////////////////////////////////
    // Initializes a lock using memory supplied by the caller. The memory      //
    // must by 4 byte aligned. Memory management of the lock is the            //
    // responsibility of the caller. This lock can not be returned to the      //
    // pool (see Return()).                                                    //
    /////////////////////////////////////////////////////////////////////////////
    HRESULT SetupExternal(TWO_WAY_LOCK* lock);

    //
    // System resource functions
    //
    ///////////////////////////////////////////////////////////////////////////////
    // Returns the number of event/semaphore pairs used by the Pool. The         //
    // number will not exceed 32767. An event/semaphore pair is only required    //
    // when there is contention between locks. Pairs are shared between locks    //
    // because the maximum number required at any given point during             //
    // execution is determined by the number of simultaneously executing         //
    // threads.                                                                  //
    ///////////////////////////////////////////////////////////////////////////////
    DWORD GetEventCount() const;

    ///////////////////////////////////////////////////////////////////////////////
    // Increase the number of events/semaphore pairs available to the            //
    // Pool. (Maximum 32767). This function is useful when the maximum number    //
    // concurrently running threads is known in advance.                         //
    /////////////////////////////////////////////////////////////////////////////// 
    HRESULT IncreaseEvents(DWORD number);


  private:
    XLOCKFREE_HANDLE pool;
};

#include <xmcore.inl>

#endif /* __cplusplus */
