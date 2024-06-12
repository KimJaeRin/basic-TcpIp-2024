#include <stdio.h>

int main (int argc, char* argv[])
{
	printf ("전 달 하 는 인자 갯 수 : %d\n", argc);
	printf ("실 행 파 일 : %s\n", argv[0]);

	for (int i = 1; i < argc; i++) {
		printf ("전 달 인 자 : %s\n", argv[i]);
	}

	return 0;
}	
