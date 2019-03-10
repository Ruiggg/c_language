#include<stdio.h>
int main()
{
	int c;
	long nc;
	nc = 0;
	c = getchar();
	while(c!=EOF)
	{
		nc++;
		c = getchar();
	}
	printf("\nThe total number: %ld",nc);
	return 0;
}
