#include <stdio.h>

struct TEST //이 구조체의 이름은 struct TEST
{
	int a;
	char b;
};
/*struct D
{
	int a;
	int b;
	struct D a; //선언이 되지 않아서 사용이 불가능함
};*/
struct D1 //자신참조구조체
{
	int a;
	int b;
	struct D1 *A; // 3번째 방에 4바이트를 잡아서 주소를 저장 따라서 가능
};
 struct BD
{
	int a;
	char b;
	struct TEST A; // 구조체 안에 구조체가 들어갈 수 있다.
};

 struct VBD
 {
	 int a;
	 char b;
	 struct BD A1;
 };


#if 0


void main()
{
	typedef struct TEST TEST;
	struct TEST aa; //구조체 선언
	char i[10];int k;
	for (k = 0; k < 10; k++)
	{
		printf("%d\n", &i[k]);
	}
}



//2번째 구조체 생성방법
typedef struct
{
	int a;
	char b;
}TEST;


void main()
{
	struct TEST aa, bb;
	aa.a = 1;
	aa.b = 'a';
	bb = aa; //항끼리 서로 복사됨
/*	if (aa == bb) //오류 => 구조체끼리 비교할 때는 각 성분끼리 비교해야 한다.
	{
		printf("%d %c\n", bb.a, bb.b);
	}*/
	if (aa.a == bb.a && aa.b == bb.b)
	{
		printf("1234\n");
	}
}


struct BD aaa;
struct VBD x;
void main()
{
	aaa.a = 10;
	aaa.b = 'a';
	aaa.A.a = 20;
	aaa.A.b = 'b';
	x.a = 10;
	x.b = 'c';
	x.A1.a = 10;
	x.A1.b = 'd';
	x.A1.A.a = 30;
	x.A1.A.b = 'e';
}
#endif
void main()
{
	int i = 10;
	int *j;
	int **jj;
	j = &i;
	*j = 20; //j가 저장되어 있는 주소값에 가서 20을 대입한다.
	jj = &j;
	**jj = 30;

	printf("%d\n", i);
}