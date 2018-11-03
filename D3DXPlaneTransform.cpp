
#pragma comment(lib, "d3dx9.lib")


#include <Windows.h>
#include <d3dx9.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char** argv)
{
	for(int i=0; i<140; ++i)
	{
		D3DXMATRIX tm;
		D3DXMATRIX tp;


		// setup the Transform matrix
		{
			D3DXVECTOR3	Axis( -100, -100, -100 );
			float	Angle = float( rand()%360 );
			float	Radian = 0;

			Radian = D3DXToRadian(Angle);
			Axis += D3DXVECTOR3( float(rand() % 201), float(rand() % 201), float(rand() % 201) );
			D3DXVec3Normalize(&Axis, &Axis);

			D3DXMatrixIdentity(&tm);
			D3DXMatrixRotationAxis(&tm, &Axis, Radian);

			tm._41 = float(rand() % 100);
			tm._42 = float(rand() % 100);
			tm._43 = float(rand() % 100);

			D3DXMatrixInverse(&tp, NULL, &tm);
			D3DXMatrixTranspose(&tp, &tp);
		}


		// setup the random plane
		D3DXPLANE	org;
		D3DXPLANE	op1;
		D3DXPLANE	op2;
		D3DXPLANE	op3;

		{
			D3DXVECTOR3	t( -30, 20, 10 );
			FLOAT		d = -10.5F + rand()% 20;

			t += D3DXVECTOR3( float(rand() % 10), float(rand() % 10), float(rand() % 10) );
			D3DXVec3Normalize(&t, &t);

			org = D3DXPLANE(t.x, t.y, t.z, d);
		}


		// gain the op1
		D3DXPlaneTransform(&op1, &org, &tp);

		// gain the op2
		D3DXVec3TransformNormal((D3DXVECTOR3*)&op2, (D3DXVECTOR3*)&org, &tm);
		op2.d = org.d - D3DXVec3Dot((D3DXVECTOR3*)&op2, &D3DXVECTOR3(tm._41, tm._42, tm._43) );

		// gain the op3
		{
			D3DXVECTOR3 A( -org.d/org.a,  0          ,  0);
			D3DXVECTOR3 B(  0          , -org.d/org.b,  0);
			D3DXVECTOR3 C(  0          ,  0          , -org.d/org.c);

			D3DXVECTOR3 a;
			D3DXVECTOR3 b;

			D3DXVec3TransformCoord(&A, &A, &tm);
			D3DXVec3TransformCoord(&B, &B, &tm);
			D3DXVec3TransformCoord(&C, &C, &tm);


			a = B - A;
			b = C - A;

			D3DXVec3Cross((D3DXVECTOR3*)&op3, &b, &a);
			D3DXVec3Normalize((D3DXVECTOR3*)&op3, (D3DXVECTOR3*)&op3);
			op3.d = -D3DXVec3Dot((D3DXVECTOR3*)&op3, &A);
		}


		int c;
		c = 0;

		printf("%3d %f, %f, %f, %f,   %f, %f, %f, %f\n"
				, i
				, fabsf((op1.a - op2.a)/op1.a)
				, fabsf((op1.b - op2.b)/op1.b)
				, fabsf((op1.c - op2.c)/op1.c)
				, fabsf((op1.d - op2.d)/op1.d)

				, fabsf((op1.a - op3.a)/op1.a)
				, fabsf((op1.b - op3.b)/op1.b)
				, fabsf((op1.c - op3.c)/op1.c)
				, fabsf((op1.d - op3.d)/op1.d)
				);
	}


	return 0;
}
