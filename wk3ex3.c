#include<stdio.h>
int main()
{
	int nl,c;
	while((c=getchar())!=EOF)
		if(c=='\n')
			nl++;
	printf("\nthe number of line: %d",nl);
	
	return 0;
}
