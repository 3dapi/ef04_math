# 📘 실습 과제: Vector2 Math Library

---

## ■ 과제 목표

- Vector2를 직접 구현하고, 연산자 오버로딩을 이용하여 벡터 연산을 구현한다.


## ■ 규칙

- main 함수는 **수정 금지**
- Vector2 구현하여 동작하도록 할 것
- 학번_이름_Vector2
  - zip 제출
  - 반드시 다른 폴더에서 압축 해제 후 실행 확인

---

## ■ 구현 범위

### 1. Vector2 구현

```cpp
// 기본형
struct Vector2
{
    float x, y;
	
    // 과제 구현
};

// 선택사항
// Vector2는 x, y 또는 배열 형태(m[2])로 접근할 수 있도록 구현해도 됨

struct Vector2
{
    union {
        struct{ float x, y;};
        float m[2];		
    };
	
    // 과제 구현
};
```
---

### 2. 기본 벡터

상수 벡터 정의

```cpp
struct Vector2
{

    // ...

    static const Vector2 Zero;   // (0, 0)
    static const Vector2 UnitX;  // (1, 0)
    static const Vector2 UnitY;  // (0, 1)
};
```
---

### 3. 생성자

- 기본 생성자
- (x, y) 초기화 생성자

---

### 4. 연산자 오버로딩

#### ✔ 벡터 연산
- `+` : 벡터 덧셈
- `-` : 벡터 뺄셈


#### ✔ 스칼라 곱 (양방향 필수)

```cpp
Vector2 operator*(float s) const;          
```

```cpp
Vector2 operator*(float s, const Vector2& v); 
```

---

#### ✔ 내적 (Dot Product)

```cpp
float operator*(const Vector2& v) const;
```

```
V1 * V2 = V1.x * V2.x + V1.y * V2.y
```

---

#### ✔ 외적 (2D → Z값)

```cpp
float operator^(const Vector2& v) const;
```

```
V1 ^ V2 = V1.x * V2.y - V1.y * V2.x
```

---

### 5. 함수

- Length()
- Normalize()
- Dot()
- Angle() : 두벡터 사이의 각도 구하기: float Angle(const Vector2& v) const;
  - θ = atan2(cross, dot)
  - $\theta = \tan^{-1}\left(\frac{cross}{dot}\right)$


### 6. 캐스팅

```cpp
operator float*()
operator const float*()
```

---

## ■ 확인용 main (수정 금지)

### ✔ 1단계: 고정값 테스트

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Vector2.h"

void FixedTest(void)
{
    printf("===== FIXED TEST =====\n");

    Vector2 V1(3.0f, 4.0f);
    Vector2 V2(1.0f, 2.0f);
    float s = 2.0f;

    printf("V1: %.3f %.3f\n", V1.x, V1.y);
    printf("V2: %.3f %.3f\n", V2.x, V2.y);
    printf("s: %.3f\n", s);

    Vector2 add = V1 + V2;   // (4, 6)
    Vector2 sub = V1 - V2;   // (2, 2)

    Vector2 vs = V1 * s;     // (6, 8)
    Vector2 sv = s * V1;     // (6, 8)

    float dot = V1 * V2;     // 11
    float cross = V1 ^ V2;   // 2

    printf("ADD: %.3f %.3f (expected: 4.000 6.000)\n", add.x, add.y);
    printf("SUB: %.3f %.3f (expected: 2.000 2.000)\n", sub.x, sub.y);

    printf("V*s: %.3f %.3f (expected: 6.000 8.000)\n", vs.x, vs.y);
    printf("s*V: %.3f %.3f (expected: 6.000 8.000)\n", sv.x, sv.y);

    printf("DOT: %.3f (expected: 11.000)\n", dot);
    printf("CROSS: %.3f (expected: 2.000)\n", cross);

    printf("LEN_V1: %.3f (expected: 5.000)\n", V1.Length());

    Vector2 n = V1.Normalize(); // (0.6, 0.8)
    printf("NORM_V1: %.3f %.3f (expected: 0.600 0.800)\n", n.x, n.y);	

    printf("-----------------------------------------------------------\n");
    printf("ZERO: %.3f %.3f\n", Vector2::Zero.x, Vector2::Zero.y);
    printf("UNITX: %.3f %.3f\n", Vector2::UnitX.x, Vector2::UnitX.y);
    printf("UNITY: %.3f %.3f\n", Vector2::UnitY.x, Vector2::UnitY.y);

    printf("\n\n");
}

```

---

### ✔ 2단계: 랜덤 테스트

```cpp
float frand(float min, float max)
{
    return min + (float)rand() / RAND_MAX * (max - min);
}

void RandomTest(void)
{

	printf("===== RANDOM TEST =====\n");

	srand((unsigned)time(NULL));

	for (int i = 0; i < 5; ++i)
	{
		Vector2 V1(frand(-10, 10), frand(-10, 10));
		Vector2 V2(frand(-10, 10), frand(-10, 10));
		float s = frand(-5, 5);

		printf("V1: %.3f %.3f\n", V1.x, V1.y);
		printf("V2: %.3f %.3f\n", V2.x, V2.y);
		printf("s: %.3f\n", s);

		printf("DOT: %.3f\n", V1 * V2);
		printf("CROSS: %.3f\n", V1 ^ V2);

		printf("-----------------\n");
	}
}


int main(void)
{
    FixedTest();
    RandomTest();
    return 0;
}
```
---

