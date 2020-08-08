#include <stdio.h>
#include <stdlib.h> //malloc함수 사용시 필요

#if 0
void main()
{
	int *a = (int *)malloc(12); //malloc에서 주는 주소를 int 포인터형으로 저장
	printf("%x\n", a);  //16진수를 10진수로 변환하는 과정에서 음수로 출력가능
	*a = 10;
	*(a + 1) = 20; //a 다음 주소는 int형이므로 4커진 a+4이다
	*(a + 2) = 30;
	printf("%d %d %d\n", a[0],a[1],a[2]);
}
#endif

#if 0
void main()
{
	int *a = (int *)malloc(12); //malloc에서 주는 주소를 int형으로 저장
	int *b;
	b = a;
	printf("%d %d\n", a,b);  //16진수를 10진수로 변환하는 과정에서 음수로 출력가능
	*b = 10;
	*(b + 1) = 20; //a 다음 주소는 int형이므로 4커진 a+4이다
	*(b + 2) = 30;
	printf("%d %d %d\n", b[0], b[1], b[2]);
}
#endif
#if 0
void main()
{
	int *a = (int *)malloc(1024);
	int *b;
	b = a;
	free(b);
	*a = 2; //정상작동한다. 하지만 특정 데이터 위에 그냥 덮어쓰는 거라서 디버깅 힘듦
}
#endif
typedef struct
{
	int a;
	int b;
}A;
A a[10]; //80바이트 할당
void main() //정적 할당
{
	A *pa = (A*)malloc(10 * sizeof(A)); //80바이트 할당
	pa->a = 3; //구조체 int a에 3 저장
	pa->b = 5; 
	free(pa);
	A *pa1 = (A*)malloc(10 * sizeof(A)); 
	(pa1+9)->a = 3; //
	(pa1 + 9)->b = 5; //pa1 마지막 주소값에 저장
	/*pa1[9].a = 3;
	pa1[9].b = 5; 
	(pa1 + 9)->a = 3;
	(pa1 + 9)->b = 5;*/
	printf("%d %d\n", pa1[9].a, pa1[9].b);
}