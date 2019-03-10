#include<stdio.h>
#define MAXLEN 1000
int mystrlen(char s[]);
int main()
{	
	char mystring[MAXLEN];
	printf("\nPlease enter a string:\n");	
	scanf("%s",mystring);
	printf("\nLen=%d\n",mystrlen(mystring));
	return 0;
}
int mystrlen(char s[])
{
	int i=0;
	
	while(s[i]!='\0')
	i++;	
	
	return i;
}
