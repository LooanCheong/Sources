#include<unistd.h>
#include<stdio.h>
//함수 정의, 시스템 콜 번호로 지정되어 있는 번호를 인자로 지정
#define my_stack_push 335
#define my_stack_pop 336

int main()
{
	int i, result, n = 3;
	//1을 우선 Push
	i = 1;
	syscall(my_stack_push, i);
	printf("Push %d\n", i);
	//1~3까지 차례대로 Push
	for (i = 1; i <= n; i++){
		syscall(my_stack_push, i);
		printf("Push %d\n", i);
	}
	//3부터 차례대로 Pop
	for (i = 1; i <= n; i++){
		result = syscall(my_stack_pop);
		printf("Pop %d\n", result);
	}

	return 0;
}

