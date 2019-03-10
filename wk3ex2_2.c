#include<stdio.h>
int main()
{
	int c;
	long nc;
	nc = 0;
	while((c=getchar())!=EOF)
	{
		nc++;
		
	}
	printf("\nThe total number: %ld",nc);
	return 0;
}
