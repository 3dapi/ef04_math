

#include <windows.h>
#include <stdio.h>
#include <math.h>

#include <Mmsystem.h>
#include <d3dx.h>

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "Winmm.lib")



int _DGE_MatInv4x4(FLOAT *pOut, FLOAT* det, FLOAT* v)
{
	FLOAT d = 0;

	FLOAT t1;
	FLOAT t2;
	FLOAT t3;

	d += (v[ 7] * v[ 0] - v[ 3] * v[ 4]) * (v[ 9] * v[14] - v[10] * v[13]);
	d += (v[ 7] * v[ 1] - v[ 3] * v[ 5]) * (v[10] * v[12] - v[ 8] * v[14]);
	d += (v[ 7] * v[ 2] - v[ 3] * v[ 6]) * (v[ 8] * v[13] - v[ 9] * v[12]);

	d += (v[15] * v[ 8] - v[11] * v[12]) * (v[ 1] * v[ 6] - v[ 2] * v[ 5]);
	d += (v[15] * v[ 9] - v[11] * v[13]) * (v[ 2] * v[ 4] - v[ 0] * v[ 6]);
	d += (v[15] * v[10] - v[11] * v[14]) * (v[ 0] * v[ 5] - v[ 1] * v[ 4]);

	*det = d;
	if(-0.00001F < d && d <0.00001F)
		return -1;

	d = 1.F/d;


	t1 = v[10] * v[15] - v[11] * v[14];
	t2 = v[11] * v[13] - v[ 9] * v[15];
	t3 = v[ 9] * v[14] - v[10] * v[13];

	pOut[ 0]= +(v[ 5] * t1 + v[ 6] * t2 + v[ 7] * t3);
	pOut[ 1]= -(v[ 1] * t1 + v[ 2] * t2 + v[ 3] * t3);


	t1 = v[ 2] * v[ 7] - v[ 3] * v[ 6];
	t2 = v[ 3] * v[ 5] - v[ 1] * v[ 7];
	t3 = v[ 1] * v[ 6] - v[ 2] * v[ 5];

	pOut[ 2]= +(v[13] * t1 + v[14] * t2 + v[15] * t3);
	pOut[ 3]= -(v[ 9] * t1 + v[10] * t2 + v[11] * t3);


	t1 = v[10] * v[15] - v[11] * v[14];
	t2 = v[11] * v[12] - v[ 8] * v[15];
	t3 = v[ 8] * v[14] - v[10] * v[12];

	pOut[ 4]= -(v[ 4] * t1 + v[ 6] * t2 + v[ 7] * t3);
	pOut[ 5]= +(v[ 0] * t1 + v[ 2] * t2 + v[ 3] * t3);


	t1 = v[ 2] * v[ 7] - v[ 3] * v[ 6];
	t2 = v[ 3] * v[ 4] - v[ 0] * v[ 7];
	t3 = v[ 0] * v[ 6] - v[ 2] * v[ 4];

	pOut[ 6]= -(v[12] * t1 + v[14] * t2 + v[15] * t3);
	pOut[ 7]= +(v[ 8] * t1 + v[10] * t2 + v[11] * t3);


	t1 = v[ 9] * v[15] - v[11] * v[13];
	t2 = v[11] * v[12] - v[ 8] * v[15];
	t3 = v[ 8] * v[13] - v[ 9] * v[12];

	pOut[ 8]= +(v[ 4] * t1 + v[ 5] * t2 + v[ 7] * t3);
	pOut[ 9]= -(v[ 0] * t1 + v[ 1] * t2 + v[ 3] * t3);


	t1 = v[ 1] * v[ 7] - v[ 3] * v[ 5];
	t2 = v[ 3] * v[ 4] - v[ 0] * v[ 7];
	t3 = v[ 0] * v[ 5] - v[ 1] * v[ 4];

	pOut[10]= +(v[12] * t1 + v[13] * t2 + v[15] * t3);
	pOut[11]= -(v[ 8] * t1 + v[ 9] * t2 + v[11] * t3);


	t1 = v[ 9] * v[14] - v[10] * v[13];
	t2 = v[10] * v[12] - v[ 8] * v[14];
	t3 = v[ 8] * v[13] - v[ 9] * v[12];

	pOut[12]= -(v[ 4] * t1 + v[ 5] * t2 + v[ 6] * t3);
	pOut[13]= +(v[ 0] * t1 + v[ 1] * t2 + v[ 2] * t3);


	t1 = v[ 1] * v[ 6] - v[ 2] * v[ 5];
	t2 = v[ 2] * v[ 4] - v[ 0] * v[ 6];
	t3 = v[ 0] * v[ 5] - v[ 1] * v[ 4];

	pOut[14]= -(v[12] * t1 + v[13] * t2 + v[14] * t3);
	pOut[15]= +(v[ 8] * t1 + v[ 9] * t2 + v[10] * t3);



	pOut[ 0] *= d;	pOut[ 1] *= d;	pOut[ 2] *= d;	pOut[ 3] *= d;
	pOut[ 4] *= d;	pOut[ 5] *= d;	pOut[ 6] *= d;	pOut[ 7] *= d;
	pOut[ 8] *= d;	pOut[ 9] *= d;	pOut[10] *= d;	pOut[11] *= d;
	pOut[12] *= d;	pOut[13] *= d;	pOut[14] *= d;	pOut[15] *= d;

	return 0;
}


void main()
{
	INT n, i, j;

	double d1;
	double d2;

	D3DXMATRIX	mtI1;
	FLOAT		det1;

	D3DXMATRIX	mtI2;
	FLOAT		det2;

	D3DXMATRIX mtT;

	int c;

	for(n=0; n<2000; ++n)
	{
		mtT = D3DXMATRIX(FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100)
						  , FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100)
						  , FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100)
						  , FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100)
						  );

		
		mtT *=0.1f;


		D3DXMatrixInverse(&mtI1, &det1, &mtT);
		_DGE_MatInv4x4((FLOAT*)&mtI2, &det2 , (FLOAT*)&mtT);

		c = 0;

		for(j=0; j<4; ++j)
		{
			for(i=0; i<4; ++i)
			{
				d1 = fabs(mtI1(j, i) - mtI2(j, i));
				d2 = fabs(d1/mtI1(j, i));

				if(d2>0.0001)
				{
					c = 0;
				}
			}
		}

	}

}