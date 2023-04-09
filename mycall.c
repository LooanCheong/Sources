#include<linux/syscalls.h>
#include<linux/kernel.h>
#include<linux/linkage.h>

//언더플로우 방지용 에러 코드 생성
#define ERROR_CODE 2147483647
//스택 생성
int stack[30];
int top = 0;
void print_stack(void);
//Push 함수 생성
SYSCALL_DEFINE1(os2023_push, int, input)
{
	int i;
	//오버플로우 방지
	if(top >= 30){
		printk("Stack Overflow. \n");

		return;
	}
	//중복 체크
	for(i = 0; i < top; i++) {
		if(stack[i] == input) {
			print_stack();
			return;
		}
	}
	//스택
	stack[top++] = input;
	print_stack();

	return;
}
//Pop 함수 생성
SYSCALL_DEFINE0(os2023_pop)
{
	int output;
	//언더플로우 방지
	if(top <= 0) {
		printk("Stack Underflow\n");
		return ERROR_CODE;
	}
	//팝
	output = stack[--top];
	print_stack();

	return output;
}
//스택 출력용 함수
void print_stack(void)
{
	int i;

	printk("Stack Top ----------\n");
	for (i = top - 1; i >= 0; i--) {
		printk("%d\n", stack[i]);
	}
	printk("Stack Bottom ----------\n");

	return;
}

