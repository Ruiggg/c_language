#include<stdio.h>

int main()
{
	int a=5,b=10;
	b = b + a++;
	printf("a=%d,b=%d\n",a,b);
	return 0;
}
