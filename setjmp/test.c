#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void function1(void);
void function2(void);

int main(void)
{
    printf("Hello World\n");
    function1();
    return 0;
}

void function1(void)
{
    printf("Funtion 1. Call 1\n");
    int ret = setjmp(env);
    if (ret == 0) function2();


    printf("Funtion 1. Call 2\n");
}

void function2(void)
{
    printf("Funtion 2. Call 1\n");
    longjmp(env, 2001);

    printf("Funtion 2. Call 2\n");
}
