#include<stdio.h>
#define MAXLEN 1000
int atoi(char s[]);

int main()
{	
	int data;
	char string[MAXLEN];
	scanf("%s",string);
	data=atoi(string);
	printf("%d\n",data);
}

int atoi(char s[])
{
	int i=0;
	int n=0;
	while(s[i]>='0' && s[i]<='9')
	{
		n=10*n+s[i]-'0';
		i++ ;
	}
	
	return n;
}
