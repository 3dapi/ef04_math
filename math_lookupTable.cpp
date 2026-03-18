
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <math.h>


#define LNMATH_MAX_LOOKUP	31416

#ifndef LNMATH_PI
#	define LNMATH_PI	3.1415926535897932f
#endif

#ifndef DEG90toRAD
#	define DEG90toRAD	1.5707963267948966f
#endif


#define RADtoDEG(p) ( (p)*180/LNMATH_PI)



#ifndef LN_ROUNDING_DELTA
#	define LN_ROUNDING_DELTA	0.0001f
#endif

#ifndef LN_ROUNDING_ONE
#	define LN_ROUNDING_ONE	0.9999f
#endif



class LnMathLookUp
{
protected:
	static DOUBLE* m_pCos;
	static DOUBLE* m_pSin;
	static DOUBLE* m_pACos;
	static DOUBLE* m_pASin;

	static DOUBLE fA;
	static DOUBLE fB;


public:
	
	LnMathLookUp()
	{
		if(NULL == m_pCos)
		{
			SetUpLookUpTable();
		}
	}


	FLOAT Cos(FLOAT f)
	{
		int		nIdx = 0;

		nIdx = INT( fabsf(f) * 10000);

		if(nIdx >=LNMATH_MAX_LOOKUP)
			nIdx %=LNMATH_MAX_LOOKUP;

		return FLOAT(m_pCos[nIdx]);
	}
	
	
	FLOAT Sin(FLOAT f)
	{
		FLOAT	fOrder =1.f;
		int		nIdx = 0;
		
		if(f<0)
			fOrder = -1;

		nIdx = INT( fabsf(f) * 10000);

		if(nIdx >=LNMATH_MAX_LOOKUP)
			nIdx %=LNMATH_MAX_LOOKUP;

		return FLOAT(m_pSin[nIdx]) * fOrder;
	}


	

	FLOAT ACos(FLOAT f)
	{
		if(f>0.9999f)
			return 0;

		if(f<-0.9999f)
			return LNMATH_PI;

		DOUBLE fdx = (LNMATH_MAX_LOOKUP-1)*(f+1.)/2.;
		int nIdx = int(fdx);

		return FLOAT(m_pACos[nIdx]);
	}


	FLOAT ASin(FLOAT f)
	{
		if(f>0.9999f)
			return DEG90toRAD;

		if(f<-0.9999f)
			return -(DEG90toRAD);

		DOUBLE fdx = (LNMATH_MAX_LOOKUP-1)*(f+1.)/2.;
		int nIdx = int(fdx);

		return FLOAT(m_pASin[nIdx]);
	}





	HRESULT Release()
	{
		if(m_pCos)
		{
			delete [] m_pCos;
			delete [] m_pSin;
			delete [] m_pACos;
			delete [] m_pASin;

			m_pCos = NULL;
			m_pSin = NULL;
			m_pACos = NULL;
			m_pASin = NULL;
		}

		return 1;
	}

protected:
	void SetUpLookUpTable()
	{
		m_pCos	= new DOUBLE[LNMATH_MAX_LOOKUP];
		m_pSin	= new DOUBLE[LNMATH_MAX_LOOKUP];
		m_pACos	= new DOUBLE[LNMATH_MAX_LOOKUP];
		m_pASin	= new DOUBLE[LNMATH_MAX_LOOKUP];

		DOUBLE i=0.;
		int nIdx=0;

		for(i=0.; i<LNMATH_PI; i+=0.0001, ++nIdx)
		{
			m_pCos[nIdx]	= cos(i);
			m_pSin[nIdx]	= sin(i);

			DOUBLE t = fA * i + fB;
			m_pACos[nIdx]	= acos(t);
			m_pASin[nIdx]	= asin(t);
		}

//		nIdx=10;
	}
};

DOUBLE* LnMathLookUp::m_pCos = NULL;
DOUBLE* LnMathLookUp::m_pSin = NULL;
DOUBLE* LnMathLookUp::m_pACos = NULL;
DOUBLE* LnMathLookUp::m_pASin = NULL;

DOUBLE LnMathLookUp::fA = 2./LNMATH_PI;
DOUBLE LnMathLookUp::fB = -1;


int main(void)
{
	FILE * fp = fopen("Tst.txt", "wt");


	clock_t start, finish;
	double  duration;
   	
	LnMathLookUp c;
	int	 i=0;
	int	nCnt = 20000000000;

	start = clock();
	
	for(i=0; i<nCnt; ++i)
		c.ACos(0.3998f);
		
	finish = clock();
 	duration = finish - start;

	fprintf(fp, "cosf: %10.8lf\n", duration);

	
	CHAR s1[4];
	CHAR s2[4];
	
	start = clock();

	for(i=0; i<nCnt; ++i)
	{
		// sqrt(0.3998f);

		memcpy(s1, s2, sizeof s1);
	}
		
	finish = clock();
 	duration = finish - start;

	fprintf(fp, "cosf: %10.8lf\n", duration);
		

	fclose(fp);

	c.Release();

	return 0;
}
