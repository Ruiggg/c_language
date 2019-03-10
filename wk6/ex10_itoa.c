#include<stdio.h>
#include<string.h>
#define MAXLEN 1000
void itoa(int, char []);
void reverse(char s[]);
int main()
{
	int n;
	char s[MAXLEN];
	printf("Enter an integer:");
	scanf("%d",&n);
	itoa(n,s);
	printf("\ns=%s\n",s);
	return 0;
}

void itoa(int n, char s[])
{
	int i,sign;
	sign=n;
	if(n<0){
	n=-n;}
	
	i=0;
	do{
		s[i++]=n%10+'0';
		n/=10;
	}while(n>0);
	
	if(sign<0)
		s[i++]='-';
	s[i]='\0';
	reverse(s);
}
void reverse(char s[])
{
	int c,i,j;
	for(i=0,j=strlen(s)-1;i<j;i++,j--)
	{
		c=s[i],s[i]=s[j],s[j]=c;
	}
}

