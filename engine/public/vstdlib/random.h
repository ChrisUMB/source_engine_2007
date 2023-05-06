//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Random number generator
//
// $Workfile: $
// $NoKeywords: $
//===========================================================================//

#ifndef VSTDLIB_RANDOM_H
#define VSTDLIB_RANDOM_H

#include "vstdlib/vstdlib.h"
#include "tier0/basetypes.h"
#include "tier0/threadtools.h"
#include "tier1/interface.h"

#define NTAB 32

#pragma warning(push)
#pragma warning( disable:4251 )

VSTDLIB_INTERFACE void RandomSeed(int iSeed);
VSTDLIB_INTERFACE float RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f);
VSTDLIB_INTERFACE float RandomFloatExp(float flMinVal = 0.0f, float flMaxVal = 1.0f, float flExponent = 1.0f);
VSTDLIB_INTERFACE int RandomInt(int iMinVal, int iMaxVal);
VSTDLIB_INTERFACE float RandomGaussianFloat(float flMean = 0.0f, float flStdDev = 1.0f);

#define RandomSeed RandomSeedDebug
#define RandomFloat RandomFloatDebug
#define RandomInt RandomIntDebug
#define RandomFloatExp RandomFloatExpDebug
#define RandomGaussianFloat RandomGaussianFloatDebug

#define DEBUG_ARGS_DEFAULTS int line = __builtin_LINE(), const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION()
#define DEBUG_ARGS int line, const char* file, const char* function

//-----------------------------------------------------------------------------
// A generator of uniformly distributed random numbers
//-----------------------------------------------------------------------------
class IUniformRandomStream {
public:
    // Sets the seed of the random number generator
    virtual void SetSeed(int iSeed) = 0;

#undef RandomFloat
#undef RandomInt
#undef RandomFloatExp
    // Generates random numbers
    virtual float RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f) = 0;

    virtual int RandomInt(int iMinVal, int iMaxVal) = 0;

    virtual float RandomFloatExp(float flMinVal = 0.0f, float flMaxVal = 1.0f, float flExponent = 1.0f) = 0;
#define RandomFloat RandomFloatDebug
#define RandomInt RandomIntDebug
#define RandomFloatExp RandomFloatExpDebug

    virtual float RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f, DEBUG_ARGS_DEFAULTS) = 0;

    virtual int RandomInt(int iMinVal, int iMaxVal, DEBUG_ARGS_DEFAULTS) = 0;

    virtual float RandomFloatExp(float flMinVal = 0.0f, float flMaxVal = 1.0f, float flExponent = 1.0f, DEBUG_ARGS_DEFAULTS) = 0;
};


//-----------------------------------------------------------------------------
// The standard generator of uniformly distributed random numbers
//-----------------------------------------------------------------------------
class VSTDLIB_CLASS CUniformRandomStream : public IUniformRandomStream {
public:
    CUniformRandomStream();

    // Sets the seed of the random number generator
    virtual void SetSeed(int iSeed);

    // Generates random numbers
#undef RandomFloat
#undef RandomInt
#undef RandomFloatExp
    virtual float RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f);

    virtual int RandomInt(int iMinVal, int iMaxVal);

    virtual float RandomFloatExp(float flMinVal = 0.0f, float flMaxVal = 1.0f, float flExponent = 1.0f);
#define RandomFloat RandomFloatDebug
#define RandomInt RandomIntDebug
#define RandomFloatExp RandomFloatExpDebug

    virtual float RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f, DEBUG_ARGS_DEFAULTS);

    virtual int RandomInt(int iMinVal, int iMaxVal, DEBUG_ARGS_DEFAULTS) ;

    virtual float RandomFloatExp(float flMinVal = 0.0f, float flMaxVal = 1.0f, float flExponent = 1.0f, DEBUG_ARGS_DEFAULTS);
private:
    int GenerateRandomNumber();

    int m_idum;
    int m_iy;
    int m_iv[NTAB];

    CThreadFastMutex m_mutex;
};


//-----------------------------------------------------------------------------
// A generator of gaussian distributed random numbers
//-----------------------------------------------------------------------------
class VSTDLIB_CLASS CGaussianRandomStream {
public:
    // Passing in NULL will cause the gaussian stream to use the
    // installed global random number generator
    CGaussianRandomStream(IUniformRandomStream *pUniformStream = NULL);

    // Attaches to a random uniform stream
    void AttachToStream(IUniformRandomStream *pUniformStream = NULL);

#undef RandomFloat
    // Generates random numbers
    float RandomFloat(float flMean = 0.0f, float flStdDev = 1.0f);
#define RandomFloat RandomFloatDebug

    float RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f, DEBUG_ARGS_DEFAULTS);

private:
    IUniformRandomStream *m_pUniformStream;
    bool m_bHaveValue;
    float m_flRandomValue;

    CThreadFastMutex m_mutex;
};


//-----------------------------------------------------------------------------
// A couple of convenience functions to access the library's global uniform stream
//-----------------------------------------------------------------------------

VSTDLIB_INTERFACE void RandomSeed(int iSeed, DEBUG_ARGS_DEFAULTS);
VSTDLIB_INTERFACE float RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f, DEBUG_ARGS_DEFAULTS);
VSTDLIB_INTERFACE float RandomFloatExp(float flMinVal = 0.0f, float flMaxVal = 1.0f, float flExponent = 1.0f, DEBUG_ARGS_DEFAULTS);
VSTDLIB_INTERFACE int RandomInt(int iMinVal, int iMaxVal, DEBUG_ARGS_DEFAULTS);
VSTDLIB_INTERFACE float RandomGaussianFloat(float flMean = 0.0f, float flStdDev = 1.0f, DEBUG_ARGS_DEFAULTS);


//-----------------------------------------------------------------------------
// Installs a global random number generator, which will affect the Random functions above
//-----------------------------------------------------------------------------
VSTDLIB_INTERFACE void InstallUniformRandomStream(IUniformRandomStream *pStream);

VSTDLIB_INTERFACE void WriteRandomDebug(const char *function, const char *file, int line);
VSTDLIB_INTERFACE void WriteConciseRandomDebug(const char* extra, const char *function, const char *file, int line);

#define DEBUG_RAND() WriteRandomDebug(__FUNCTION__, __FILE__, __LINE__)

#pragma warning(pop)

#endif // VSTDLIB_RANDOM_H



