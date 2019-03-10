#include<stdio.h>
int main()
{	
	int nwhite,nother,c;
	nwhite=nother=0;
	int ndigit[10];
	int i;
	
	for(i=0;i<10;i++)
		ndigit[i] = 0;
	
	while((c=getchar())!=EOF)
	{
		if(c>='0'&&c<='9')
			ndigit[c-'0']++;
		else if(c==' '||c=='\n'||c=='\t')
			nwhite++;
		else
			nother++;
	}
	
	printf("white space = %d\nothers = %d\n",nwhite,nother);
	printf("digits:\n");
	for(i=0;i<10;i++)
		printf("%d occurs %d times. \n",i,ndigit[i]);
	return 0;
}
