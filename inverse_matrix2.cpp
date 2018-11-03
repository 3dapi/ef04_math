

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

	float k[16];

	k[ 0] = v[ 9] * v[14] - v[10] * v[13];
	k[ 1] = v[10] * v[12] - v[ 8] * v[14];
	k[ 2] = v[ 8] * v[13] - v[ 9] * v[12];
	k[ 3] = v[ 1] * v[ 6] - v[ 2] * v[ 5];

	k[ 4] = v[ 2] * v[ 4] - v[ 0] * v[ 6];
	k[ 5] = v[ 0] * v[ 5] - v[ 1] * v[ 4];
	k[ 6] = v[10] * v[15] - v[11] * v[14];
	k[ 7] = v[11] * v[13] - v[ 9] * v[15];

	k[ 8] = v[ 2] * v[ 7] - v[ 3] * v[ 6];
	k[ 9] = v[ 3] * v[ 5] - v[ 1] * v[ 7];
	k[10] = v[11] * v[12] - v[ 8] * v[15];
	k[11] = v[ 8] * v[14] - v[10] * v[12];

	k[12] = v[ 3] * v[ 4] - v[ 0] * v[ 7];
	k[13] = v[ 0] * v[ 6] - v[ 2] * v[ 4];
	k[14] = v[ 9] * v[15] - v[11] * v[13];
	k[15] = v[ 1] * v[ 7] - v[ 3] * v[ 5];

	d += ( k[ 8]) * (k[ 2]);
	d += ( k[ 6]) * (k[ 5]);

	d += (-k[12]) * (k[ 0]);
	d += (-k[ 9]) * (k[ 1]);

	d += (-k[10]) * (k[ 3]);
	d += (-k[ 7]) * (k[ 4]);


	if(det) *det = d;
	if(-0.00001F < d && d <0.00001F)
		return -1;

	d = 1.0F/d;


	pOut[ 0]= +(v[ 5] * k[ 6] + v[ 6] * k[ 7] + v[ 7] * k[ 0]);
	pOut[ 1]= -(v[ 1] * k[ 6] + v[ 2] * k[ 7] + v[ 3] * k[ 0]);

	pOut[ 2]= +(v[13] * k[ 8] + v[14] * k[ 9] + v[15] * k[ 3]);
	pOut[ 3]= -(v[ 9] * k[ 8] + v[10] * k[ 9] + v[11] * k[ 3]);

	pOut[ 4]= -(v[ 4] * k[ 6] + v[ 6] * k[10] + v[ 7] * k[11]);
	pOut[ 5]= +(v[ 0] * k[ 6] + v[ 2] * k[10] + v[ 3] * k[11]);

	pOut[ 6]= -(v[12] * k[ 8] + v[14] * k[12] + v[15] * k[13]);
	pOut[ 7]= +(v[ 8] * k[ 8] + v[10] * k[12] + v[11] * k[13]);

	pOut[ 8]= +(v[ 4] * k[14] + v[ 5] * k[10] + v[ 7] * k[ 2]);
	pOut[ 9]= -(v[ 0] * k[14] + v[ 1] * k[10] + v[ 3] * k[ 2]);

	pOut[10]= +(v[12] * k[15] + v[13] * k[12] + v[15] * k[ 5]);
	pOut[11]= -(v[ 8] * k[15] + v[ 9] * k[12] + v[11] * k[ 5]);

	pOut[12]= -(v[ 4] * k[ 0] + v[ 5] * k[ 1] + v[ 6] * k[ 2]);
	pOut[13]= +(v[ 0] * k[ 0] + v[ 1] * k[ 1] + v[ 2] * k[ 2]);

	pOut[14]= -(v[12] * k[ 3] + v[13] * k[ 4] + v[14] * k[ 5]);
	pOut[15]= +(v[ 8] * k[ 3] + v[ 9] * k[ 4] + v[10] * k[ 5]);


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


	printf("\n\n-----------------------------------------\n\n");


	DWORD bgn, end;
	INT delta1, delta2;
	INT Cnt = 4500000;

	INT t1=0, t2=0;




	for(i=0; i<20; ++i)
	{
		mtT = D3DXMATRIX(FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100)
							  , FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100)
							  , FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100)
							  , FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100), FLOAT(rand()%100)
							  );


		bgn = timeGetTime();

		for(n=0; n<Cnt; ++n)
			D3DXMatrixInverse(&mtI1, &det1, &mtT);

		end = timeGetTime();
		delta1 = end - bgn;

		t1 += delta1;

		printf("D3D Inverse: %5d", delta1);


		bgn = timeGetTime();

		for(n=0; n<Cnt; ++n)
			_DGE_MatInv4x4((FLOAT*)&mtI2, &det2 , (FLOAT*)&mtT);

		end = timeGetTime();
		delta2 = end - bgn;
		t2 += delta2;

		printf("	DGE Inverse: %5d\n", delta2);
	}

	printf("\n\n");

	printf("Aspect Ratio: %f\n", float(t2)/float(t1));

	printf("\n\n-----------------------------------------\n\n");



}