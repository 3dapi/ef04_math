
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LNMATH_MAX_LOOKUP	31416
#ifndef LNMATH_PI
#  define LNMATH_PI	3.1415926535897932f
#endif
#ifndef DEG90toRAD
#  define DEG90toRAD	1.5707963267948966f
#endif
#define RADtoDEG(p) ( (p)*180/LNMATH_PI)
#ifndef LN_EPSILON
#  define LN_EPSILON	0.00001
#endif

#ifndef LN_ALMOST_ONE
#  define LN_ALMOST_ONE	0.99999
#endif


class LnMathLookUp
{
protected:
	static double* m_pCos;
	static double* m_pSin;
	static double* m_pACos;
	static double* m_pASin;

	static double fA;
	static double fB;

public:
	
	LnMathLookUp()
	{
		if(NULL == m_pCos)
		{
			SetUpLookUpTable();
		}
	}

	float Cos(float f)
	{
		int		nIdx = 0;

		nIdx = int( fabsf(f) * 10000);

		if(nIdx >=LNMATH_MAX_LOOKUP)
			nIdx %=LNMATH_MAX_LOOKUP;

		return float(m_pCos[nIdx]);
	}
	
		float Sin(float f)
	{
		float	fOrder =1.f;
		int		nIdx = 0;
		
		if(f<0)
			fOrder = -1;

		nIdx = int( fabsf(f) * 10000);

		if(nIdx >=LNMATH_MAX_LOOKUP)
			nIdx %=LNMATH_MAX_LOOKUP;

		return float(m_pSin[nIdx]) * fOrder;
	}

	float ACos(float f)
	{
		if(f>LN_ALMOST_ONE)
			return 1.0F-f*f*f/6.0F;
		if(f<-LN_ALMOST_ONE)
			return LNMATH_PI-(1.0F-f*f*f/6.0F);

		double fdx = (LNMATH_MAX_LOOKUP-1)*(f+1.)/2.;
		int nIdx = int(fdx);

		return float(m_pACos[nIdx]);
	}

	float ASin(float f)
	{
		if(f>LN_ALMOST_ONE)
			return DEG90toRAD;

		if(f<-LN_ALMOST_ONE)
			return -(DEG90toRAD);

		double fdx = (LNMATH_MAX_LOOKUP-1)*(f+1.)/2.;
		int nIdx = int(fdx);

		return float(m_pASin[nIdx]);
	}


	int Release()
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
		m_pCos	= new double[LNMATH_MAX_LOOKUP];
		m_pSin	= new double[LNMATH_MAX_LOOKUP];
		m_pACos	= new double[LNMATH_MAX_LOOKUP];
		m_pASin	= new double[LNMATH_MAX_LOOKUP];

		double i=0.;
		int nIdx=0;

		for(i=0.; i<LNMATH_PI; i+=0.0001, ++nIdx)
		{
			m_pCos[nIdx]	= cos(i);
			m_pSin[nIdx]	= sin(i);

			double t = fA * i + fB;
			m_pACos[nIdx]	= acos(t);
			m_pASin[nIdx]	= asin(t);
		}

//		nIdx=10;
	}
};

double* LnMathLookUp::m_pCos = NULL;
double* LnMathLookUp::m_pSin = NULL;
double* LnMathLookUp::m_pACos = NULL;
double* LnMathLookUp::m_pASin = NULL;

double LnMathLookUp::fA = 2./LNMATH_PI;
double LnMathLookUp::fB = -1;


int main(void)
{
	std::cos()
	std::sin()

	FILE * fp = fopen("Tst.txt", "wt");


	clock_t start, finish;
	double  duration;
   	
	LnMathLookUp c;
	int	 i=0;
	int	nCnt = 2000000000;

	start = clock();
	
	for(i=0; i<nCnt; ++i)
		c.ACos(0.3998f);
		
	finish = clock();
 	duration = finish - start;

	fprintf(fp, "cosf: %10.8lf\n", duration);

	
	unsigned char s1[4];
	unsigned char s2[4];
	
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
