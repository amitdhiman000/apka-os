#include <ktest.h>
#include <kconsol.h>
#include <stdio.h>

void test_konsole(void)
{
    ConsolWriteString("Hello, Welcome to OS");
}

void test_stdio(void)
{
    printf("Enter your name : ");
    const char *str = gets();
	printf("Welcome %s!!\n", str);
}