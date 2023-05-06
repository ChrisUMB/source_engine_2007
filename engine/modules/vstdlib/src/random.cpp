//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Random number generator
//
// $Workfile: $
// $NoKeywords: $
//===========================================================================//


#include "vstdlib/random.h"
#include <math.h>
#include "dbg.h"

#include "tier0/memdbgon.h"

#define IA 16807
#define IM 2147483647
#define IQ 127773
#define IR 2836
#define NDIV (1+(IM-1)/NTAB)
#define MAX_RANDOM_RANGE 0x7FFFFFFFUL

// fran1 -- return a random floating-point number on the interval [0,1)
//
#define AM (1.0/IM)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

//-----------------------------------------------------------------------------
// globals
//-----------------------------------------------------------------------------
static CUniformRandomStream s_UniformStream;
static CGaussianRandomStream s_GaussianStream;
static IUniformRandomStream *s_pUniformStream = &s_UniformStream;


//-----------------------------------------------------------------------------
// Installs a global random number generator, which will affect the Random functions above
//-----------------------------------------------------------------------------
void InstallUniformRandomStream( IUniformRandomStream *pStream )
{
	s_pUniformStream = pStream ? pStream : &s_UniformStream;
}


static int rng_calls = 0;

void WriteRandomDebug(const char *function, const char *file, int line) {
//    FILE *f;
//    fopen_s(&f, "RandomDebug.txt", "a");
//    fprintf(f, "RAND:\t%s:%d %s() [%d]\n", file, line, function, rng_calls);
//    fclose(f);
}

static const char* last_file = nullptr;
static const char* last_function = nullptr;
static int last_line = 0;
static int num_duplicates = 0;

#include <string>
#include <filesystem>

std::string get_parent_directory_and_filename(const std::string& path) {
    std::string result;
    auto pos = path.find("\\src");
    if(pos == std::string::npos) {
        pos = path.find("\\common");
    }

    if (pos != std::string::npos) {
        std::string parent_dir = std::filesystem::path(path.substr(0, pos)).parent_path().filename().string();
        std::string filename = std::filesystem::path(path.substr(pos + 4)).filename().string();
        result = parent_dir + "\\" + filename;
    }

    return result;
}

void WriteConciseRandomDebug(const char* extra, const char *function, const char *file, int line) {
    // Simple pointer check
    if(last_file == file && last_function == function) {
        num_duplicates++;
        return;
    }

    // Check if the strings are the same
    if(last_file != nullptr && strcmp(last_file, file) == 0 && last_function != nullptr && strcmp(last_function, function) == 0) {
        num_duplicates++;
        return;
    }

    if(last_file != nullptr) {
        const std::string& path = get_parent_directory_and_filename(last_file);

        FILE *f;
        fopen_s(&f, "RandomDebug.txt", "a");
        fprintf(f, "%24s:\t%s:%d %s() [%d, %d]\n", extra, path.c_str(), last_line, last_function, rng_calls, num_duplicates);
        fclose(f);
    }

    last_file = file;
    last_function = function;
    last_line = line;
    num_duplicates = 1;
}

//-----------------------------------------------------------------------------
// A couple of convenience functions to access the library's global uniform stream
//-----------------------------------------------------------------------------
void RandomSeed( int iSeed, DEBUG_ARGS )
{
    WriteConciseRandomDebug("RandomSeed", function, file, line);
	s_pUniformStream->SetSeed( iSeed );
}

float RandomFloat( float flMinVal, float flMaxVal, DEBUG_ARGS )
{
    WriteConciseRandomDebug("RandomFloat", function, file, line);
#undef RandomFloat
	return s_pUniformStream->RandomFloat( flMinVal, flMaxVal );
#define RandomFloat RandomFloatDebug
}

float RandomFloatExp( float flMinVal, float flMaxVal, float flExponent, DEBUG_ARGS )
{
    WriteConciseRandomDebug("RandomFloatExp", function, file, line);
#undef RandomFloatExp
	return s_pUniformStream->RandomFloatExp( flMinVal, flMaxVal, flExponent );
#define RandomFloatExp RandomFloatExpDebug
}

int RandomInt( int iMinVal, int iMaxVal, DEBUG_ARGS )
{
    WriteConciseRandomDebug("RandomInt", function, file, line);
#undef RandomInt
	return s_pUniformStream->RandomInt( iMinVal, iMaxVal );
#define RandomInt RandomIntDebug
}

float RandomGaussianFloat( float flMean, float flStdDev, DEBUG_ARGS )
{
    WriteConciseRandomDebug("RandomGaussianFloat", function, file, line);
#undef RandomGaussianFloat
	return s_GaussianStream.RandomFloat( flMean, flStdDev );
#define RandomGaussianFloat RandomGaussianFloatDebug
}

float CUniformRandomStream::RandomFloat(float flMinVal, float flMaxVal, DEBUG_ARGS) {
//    WriteConciseRandomDebug("CUniformRandomStream::RandomFloat", function, file, line);
#undef RandomFloat
    return this->RandomFloat(flMinVal, flMaxVal);
#define RandomFloat RandomFloatDebug
}

int CUniformRandomStream::RandomInt(int iMinVal, int iMaxVal, DEBUG_ARGS) {
//    WriteConciseRandomDebug("CUniformRandomStream::RandomInt", function, file, line);
#undef RandomInt
    return this->RandomInt(iMinVal, iMaxVal);
#define RandomInt RandomIntDebug
}

float CUniformRandomStream::RandomFloatExp(float flMinVal, float flMaxVal, float flExponent, DEBUG_ARGS) {
//    WriteConciseRandomDebug("CUniformRandomStream::RandomFloatExp", function, file, line);
#undef RandomFloatExp
    return this->RandomFloatExp(flMinVal, flMaxVal, flExponent);
#define RandomFloatExp RandomFloatExpDebug
}

float CGaussianRandomStream::RandomFloat(float flMinVal, float flMaxVal, DEBUG_ARGS) {
//    WriteConciseRandomDebug("CGaussianRandomStream::RandomFloat", function, file, line);
#undef RandomFloat
    return this->RandomFloat(flMinVal, flMaxVal);
#define RandomFloat RandomFloatDebug
}

#undef RandomSeed
#undef RandomFloat
#undef RandomInt
#undef RandomFloatExp
#undef RandomGaussianFloat
void RandomSeed( int iSeed )
{
    s_pUniformStream->SetSeed( iSeed );
}

float RandomFloat( float flMinVal, float flMaxVal)
{
    return s_pUniformStream->RandomFloat( flMinVal, flMaxVal );
}

float RandomFloatExp( float flMinVal, float flMaxVal, float flExponent )
{
    return s_pUniformStream->RandomFloatExp( flMinVal, flMaxVal, flExponent );
}

int RandomInt( int iMinVal, int iMaxVal )
{
    return s_pUniformStream->RandomInt( iMinVal, iMaxVal );
}

float RandomGaussianFloat( float flMean, float flStdDev )
{
    return s_GaussianStream.RandomFloat( flMean, flStdDev );
}

#define RandomSeed RandomSeedDebug
#define RandomFloat RandomFloatDebug
#define RandomInt RandomIntDebug
#define RandomFloatExp RandomFloatExpDebug
#define RandomGaussianFloat RandomGaussianFloatDebug

//-----------------------------------------------------------------------------
//
// Implementation of the uniform random number stream
//
//-----------------------------------------------------------------------------
CUniformRandomStream::CUniformRandomStream()
{
	SetSeed(0);
}

void CUniformRandomStream::SetSeed( int iSeed )
{
	int cache = m_idum;
	AUTO_LOCK( m_mutex );
	m_idum = ( ( iSeed < 0 ) ? iSeed : -iSeed );
	m_iy = 0;

	FILE *f;
	fopen_s(&f, "RandomDebug.txt", "a");
	fprintf(f, "%24s:\t%d -> %d [%d]\n", "SEED", cache, m_idum, rng_calls);
	fclose(f);
//    WriteConciseRandomDebug()

	rng_calls = 0;
}

int CUniformRandomStream::GenerateRandomNumber()
{
	AUTO_LOCK( m_mutex );
	rng_calls++;
	int j;
	int k;

	if (m_idum <= 0 || !m_iy)
	{
		if (-(m_idum) < 1)
			m_idum=1;
		else
			m_idum = -(m_idum);

		for ( j=NTAB+7; j>=0; j--)
		{
			k = (m_idum)/IQ;
			m_idum = IA*(m_idum-k*IQ)-IR*k;
			if (m_idum < 0)
				m_idum += IM;
			if (j < NTAB)
				m_iv[j] = m_idum;
		}
		m_iy=m_iv[0];
	}
	k=(m_idum)/IQ;
	m_idum=IA*(m_idum-k*IQ)-IR*k;
	if (m_idum < 0)
		m_idum += IM;
	j=m_iy/NDIV;

	// We're seeing some strange memory corruption in the contents of s_pUniformStream.
	// Perhaps it's being caused by something writing past the end of this array?
	// Bounds-check in release to see if that's the case.
	if (j >= NTAB || j < 0)
	{
		DebuggerBreakIfDebugging();
		Warning("CUniformRandomStream had an array overrun: tried to write to element %d of 0..31. Contact Tom or Elan.\n", j);
		j = ( j % NTAB ) & 0x7fffffff;
	}

	m_iy=m_iv[j];
	m_iv[j] = m_idum;

	return m_iy;
}

#undef RandomFloat
#undef RandomFloatExp
#undef RandomInt
float CUniformRandomStream::RandomFloat( float flLow, float flHigh )
{
	// float in [0,1)
	float fl = AM * GenerateRandomNumber();
	if (fl > RNMX)
	{
		fl = RNMX;
	}
	return (fl * ( flHigh - flLow ) ) + flLow; // float in [low,high)
}

float CUniformRandomStream::RandomFloatExp( float flMinVal, float flMaxVal, float flExponent )
{
	// float in [0,1)
	float fl = AM * GenerateRandomNumber();
	if (fl > RNMX)
	{
		fl = RNMX;
	}
	if ( flExponent != 1.0f )
	{
		fl = powf( fl, flExponent );
	}
	return (fl * ( flMaxVal - flMinVal ) ) + flMinVal; // float in [low,high)
}

int CUniformRandomStream::RandomInt( int iLow, int iHigh )
{
	//ASSERT(lLow <= lHigh);
	unsigned int maxAcceptable;
	unsigned int x = iHigh-iLow+1;
	unsigned int n;
	if (x <= 1 || MAX_RANDOM_RANGE < x-1)
	{
		return iLow;
	}

	// The following maps a uniform distribution on the interval [0,MAX_RANDOM_RANGE]
	// to a smaller, client-specified range of [0,x-1] in a way that doesn't bias
	// the uniform distribution unfavorably. Even for a worst case x, the loop is
	// guaranteed to be taken no more than half the time, so for that worst case x,
	// the average number of times through the loop is 2. For cases where x is
	// much smaller than MAX_RANDOM_RANGE, the average number of times through the
	// loop is very close to 1.
	//
	maxAcceptable = MAX_RANDOM_RANGE - ((MAX_RANDOM_RANGE+1) % x );
	do
	{
		n = GenerateRandomNumber();
	} while (n > maxAcceptable);

	return iLow + (n % x);
}


//-----------------------------------------------------------------------------
//
// Implementation of the gaussian random number stream
// We're gonna use the Box-Muller method (which actually generates 2
// gaussian-distributed numbers at once)
//
//-----------------------------------------------------------------------------
CGaussianRandomStream::CGaussianRandomStream( IUniformRandomStream *pUniformStream )
{
	AttachToStream( pUniformStream );
}


//-----------------------------------------------------------------------------
// Attaches to a random uniform stream
//-----------------------------------------------------------------------------
void CGaussianRandomStream::AttachToStream( IUniformRandomStream *pUniformStream )
{
	AUTO_LOCK( m_mutex );
	m_pUniformStream = pUniformStream;
	m_bHaveValue = false;
}


//-----------------------------------------------------------------------------
// Generates random numbers
//-----------------------------------------------------------------------------
float CGaussianRandomStream::RandomFloat( float flMean, float flStdDev )
{
	AUTO_LOCK( m_mutex );
	IUniformRandomStream *pUniformStream = m_pUniformStream ? m_pUniformStream : s_pUniformStream;
	float fac,rsq,v1,v2;

	if (!m_bHaveValue)
	{
		// Pick 2 random #s from -1 to 1
		// Make sure they lie inside the unit circle. If they don't, try again
		do
		{
			v1 = 2.0f * pUniformStream->RandomFloat() - 1.0f;
			v2 = 2.0f * pUniformStream->RandomFloat() - 1.0f;
			rsq = v1*v1 + v2*v2;
		} while ((rsq > 1.0f) || (rsq == 0.0f));

		// The box-muller transformation to get the two gaussian numbers
		fac = sqrtf( -2.0f * log(rsq) / rsq );

		// Store off one value for later use
		m_flRandomValue = v1 * fac;
		m_bHaveValue = true;

		return flStdDev * (v2 * fac) + flMean;
	}
	else
	{
		m_bHaveValue = false;
		return flStdDev * m_flRandomValue + flMean;
	}
}


//-----------------------------------------------------------------------------
// Creates a histogram (for testing)
//-----------------------------------------------------------------------------
