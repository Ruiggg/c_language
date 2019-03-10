#include<stdio.h>
#define MAX 100
int main()
{	
	void mystrcat(char[],char []);
	char s[MAX]="Hello ";
	char t[]=" world!";
	mystrcat(s,t);
	printf("s=%s\n",s);
	return 0;
}

void mystrcat(char s[],char t[])
{
	int i,j;
	i=j=0;
	while(s[i]!='\0')
		i++;
	while((s[i++]=t[j++])!='\0')
	;
}
