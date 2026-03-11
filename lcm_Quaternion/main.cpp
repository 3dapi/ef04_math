///////////////////////////////////////////////////////////////////////////////
// 
// Explain:  Using Quaternion
// Date : 2009-06-14, Author: AFEW



#pragma comment(lib, "d3d9.lib")
#if defined(_DEBUG) || defined(DEBUG)
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif

#include <stdio.h>
#include <time.h>

#include <d3d9.h>
#include <d3dx9.h>


void LcxVec3RotationAxis(D3DXVECTOR3* pOut				// Output Position
						 , const D3DXVECTOR3* pvcIn		// Input Position
						 , const D3DXVECTOR3* pvcAxis	// Rotation Axis(must be Normalized)
						 , FLOAT fRadian				// Ratotion Angle(Radian)
						 );


void main()
{
	////////////////////////////////////////////////////////////////////////////
	// Quaternion 회전 예제
	// 다음의 벡터 (1,1,1)을 Y축으로 45도 회전 하라
	////////////////////////////////////////////////////////////////////////////



	// 풀이
	// q * P q-1을 이용해서 풀어보자


	// 1. 회전 하려는 좌표를 D3DXVECTOR3 class 변수로 바꾼다.
	D3DXVECTOR3 vcIn(1,1,1);


	// 2. 회전 y축을 D3DXVECTOR3 class로 바꾼다.: (0,1,0)
	D3DXVECTOR3		vcAxis(0,1,0);


	// 3. 각도 45를 Radian으로 바꾼다.
	FLOAT	fAngle = D3DXToRadian(45);


	// 4.0 Quaterninon에서 회전각은 주어진 각의 1/2 값이다. 이를 이용해서
	// Quaterninon x, y, z, w 값은 다음과 같이 된다.
	// 주의할 것은 회전축은 항상 크기가 1인 벡터로 정규화 되어 있어야한다.
	// q.x = 회전 축.x * sin(θ/2)
	// q.y = 회전 축.y * sin(θ/2)
	// q.z = 회전 축.z * sin(θ/2)
	// q.w =             cos(θ/2)


	// 4.1 D3DXQUATERNION class 변수를 축과 회전각을 이용해서 다음과 같이 만들 수 있다.
	D3DXQUATERNION	q;
	q.x = vcAxis.x * sinf(fAngle/2.f);
	q.y = vcAxis.y * sinf(fAngle/2.f);
	q.z = vcAxis.z * sinf(fAngle/2.f);
	q.w =            cosf(fAngle/2.f);

	// 4.2 q의 q-1은 복소 공액 이므로 Quaternion x, y, z의 부호를 다음과 같이 반전(Negative)한다.
	// q_1 = ( -q.x, -q.y, -q.z, q.w);
	D3DXQUATERNION	q_1( -q.x, -q.y, -q.z, q.w);


	// 5. 회전 대상이 되는 벡터 vcIn(1,1,1)도 Quaterninon으로 바꾸어야 하는데
	// x, y, z는 그대로 유지하고 w=0 으로 으로 하는 Quaternion으로 만든다.
	D3DXQUATERNION	P( vcIn.x, vcIn.y, vcIn.z, 0);


	// 6. 회전은 q * P q-1을 이용한다.
	D3DXQUATERNION	R;
	R = q * P * q_1;



	// 7. 회전한 결과는 R의 x, y, z를 취한다.
	D3DXVECTOR3	vcR(R.x, R.y, R.z);

	printf("%f %f %f\n", R.x, R.y, R.z);





	////////////////////////////////////////////////////////////////////////////
	//
	// 위에서 구한 사원수 회전을 함수로 만들고 이를 DirectX와 비교해 보자.
	// 문제를 임의의 값, 임의의 축, 임의의 값에 대한 회전을 구해보자.
	////////////////////////////////////////////////////////////////////////////

	srand( (unsigned)time(NULL));
	
	D3DXVECTOR3 vOut;
	D3DXVECTOR3 vIn  ( FLOAT(rand()%RAND_MAX), FLOAT(rand()%RAND_MAX), FLOAT(rand()%RAND_MAX) );
	D3DXVECTOR3 vAxis( FLOAT(rand()%RAND_MAX), FLOAT(rand()%RAND_MAX), FLOAT(rand()%RAND_MAX) );
	float		fRadian = D3DXToRadian( FLOAT(rand()%360) );



	// 이 코드는 쉽게 결과를 예상하기 위해서 만든 것
	//	vIn		= D3DXVECTOR3( 1, 0, 1);
	//	vAxis	= D3DXVECTOR3( 0, 1, 0);
	//	fRadian = D3DXToRadian( 90);



	// ※ 회전에서 주의할 것은 DirectX의 경우 왼손 좌표를 사용한다.
	// 그런데 DirectX SDK함수는 오른손 좌표 기준으로 작성된 함수를 사용한다.


	// 2.1  Quaternion을 이용한 방법
	// q * P * q-1 을 내부에서 처리한다.(LcxVec3RotationAxis)
	// 주의 할 것은 축의 방향은 항상 정규화 되어야 한다.
	D3DXVECTOR3 vAxisN;
	D3DXVec3Normalize(&vAxisN, &vAxis);
	LcxVec3RotationAxis(&vOut, &vIn, &vAxisN, fRadian);
	printf("%f %f %f\n", vOut.x, vOut.y, vOut.z);


	// 2.2 DirectX 함수를 이용한 방법
	// DirectX의 함수는 전부 오른손 좌표 기준으로 하므로 각도는 반전해야 한다.
	// 회전행렬을 만든다. --> 이행렬에 변환을 한다.
	D3DXMATRIX mtR;
	D3DXMatrixRotationAxis(&mtR, &vAxis, -fRadian);
	D3DXVec3TransformCoord(&vOut, &vIn, &mtR);
	printf("%f %f %f\n", vOut.x, vOut.y, vOut.z);
}





void LcxVec3RotationAxis(D3DXVECTOR3* pOut, const D3DXVECTOR3* pvcIn, const D3DXVECTOR3* pvcAxis, FLOAT fRadian)
{
	D3DXVECTOR3		vcAxis = *pvcAxis;
	D3DXQUATERNION	P( pvcIn->x, pvcIn->y, pvcIn->z, 0);	// 입력 회전 대상을 Quaternion으로 만든다.

	D3DXQUATERNION	q;		// 축과 각도로 구성된 Quaternion
	D3DXQUATERNION	q_1;	// q의 복소 공액(Conjugate)
	D3DXQUATERNION	R;		// 최종 회전 값

	fRadian *= 0.5f;		// 각도를 절반으로 한다. => θ = θ/2

	FLOAT fSin = sinf(fRadian);
	FLOAT fCos = cosf(fRadian);

	q.x = vcAxis.x * fSin;
	q.y = vcAxis.y * fSin;
	q.z = vcAxis.z * fSin;
	q.w =            fCos;

	q_1 = D3DXQUATERNION( -q.x, -q.y, -q.z, q.w);


	// 회전: q * P * q_1 : dx -> q_1 * P * q
	//R = q * P * q_1;
	R = q_1 * P * q;

	
	if(pOut)
	{
		pOut->x = R.x;
		pOut->y = R.y;
		pOut->z = R.z;
	}
}

