#include<stdio.h>
#define MAXLEN 1000		//允许输入行的最大长度

int mygetline(char line[],int n);
void copy(char to[],char from[]);

int main()
{
	int max=0;
	int len;
	char longest[MAXLEN];
	char line[MAXLEN];
	
	while((len=mygetline(line,MAXLEN))>0)
	{
		if(len>max)
		{
			copy(longest,line);
			max = len;
		}
	}
	
	if(max>0)
		printf("\nThe longest is %s \n length=%d\n",longest,max);
	
	return 0;
}

int mygetline(char line[],int n)
{	
	int c,i;
	i=0;
	while((c=getchar())!=EOF && i<n-1 && c!='\n')
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

void copy(char to[],char from[])
{
	int i=0;
	
	while(from[i]!='\0')
	{
		to[i] = from[i];
		i++;
	}
}
