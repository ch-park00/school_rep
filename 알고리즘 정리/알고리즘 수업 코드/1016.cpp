#include <stdio.h>
#include <stdlib.h>

int main()
{
	//              파일명		 read모드,text가 들어있다(눈으로 보이는 것은 text.아닌 것은 모두 binary->영상이나 음악 등)
	FILE *f = fopen("seoul.txt", "rt"); //file을 열 때는 file포인터 이용.시작 주소 반환

	char buf[100] = { 0 };
	/* fgets(buf, 99, f); //buf에 f에서 99개의 char값(string)을 읽어옴.1줄만*/

	while(1)
	{
		if (feof(f)) //파일의 끝을 알려줌
		{
			break;
		}
		fgets(buf, 99, f);
		printf("%s", buf);
		buf[0] = '\0';
	}
	fclose(f); //file 닫기
	return 0;
}