#include<stdio.h>
int main()
{
	long nc;
	nc = 0;
	for(nc=0;getchar()!=EOF;nc++)
	;
	printf("\nThe total number: %ld",nc);
	return 0;
}
