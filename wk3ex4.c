#include<stdio.h>
int main()
{
	int nw,state,c;
	nw=state=0;
	while((c=getchar())!=EOF)
	{
		if(c==' '||c=='\t'||c=='\n')
			state = 0;
		else
		{
		if(state == 0)
			{
			state = 1;
			nw++;
			}
		}
	}
	printf("\nThe amount of words is %d",nw);
return 0;
}
		
