#include<stdio.h>
#include<string.h>
#define MAXLEN 100
int trim(char []);
int main()
{
	char s[]="I love programming!                        ";
	trim(s);
	printf("s=%s\n",s);
	return 0;
}

int trim(char s[])
{
	int n;
	for(n=strlen(s)-1;n>=0;n--)
		if(s[n]!=' ' && s[n]!='\n' && s[n]!='\t')
		break;
		
	s[n+1]='\0';
	
	return n;
}

