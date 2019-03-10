#include<stdio.h>
#define MAXLEN 1000		//允许输入行的最大长度

int mygetline(void);
void copy(void);

int max;
int len;
char longest[MAXLEN];
char line[MAXLEN];
int main()
{	
	int len;
	extern int max;
	extern char longest[];
	max = 0;
	while((len=mygetline())>0)
	{
		if(len>max)
		{
			copy();
			max = len;
		}
	}
	
	if(max>0)
		printf("\nThe longest is %s \n length=%d\n",longest,max);
	
	return 0;
}

int mygetline(void)
{	
	int c,i;
	extern char line[];
	
	i=0;
	while((c=getchar())!=EOF && i<MAXLEN-1 && c!='\n')
	{
		line[i]=c;
		i++;
	}
	
	if(c=='\n')
	{
		line[i]=c;
		i++;	
	}
	
	line[i]='\0';
	
	return i;
}

void copy()
{
	int i=0;
	extern char line[],longest[];
	while(line[i]!='\0')
	{
		longest[i] = line[i];
		i++;
	}
}
