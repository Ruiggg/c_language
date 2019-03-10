#include<stdio.h>
#include<string.h>
#define MAXLEN 1000
void reverse(char s[]);
void itoh(long long n, char s[]);
int main()
{
	int j;
	long long n;
	char s[MAXLEN];
	for(j=0;j<MAXLEN;j++)
		s[j]='0';
	printf("Enter an integer:");
	scanf("%ld",&n);
	itoh(n,s);
	printf("n=%ld, s=%s\n",n,s);
	return 0;
}

void itoh(long long n,char s[])
{	
	int i,temp,sign;
	i=0;
	sign=n;
		if(n<0)
		{	
			n=(((long long)(1))<<32)+n;
		}
		do{
			temp = n%16;
			if(temp>=0 && temp <=9)
			{
				s[i]=temp+'0';
			}
			else
			{
				s[i]=temp-10+'A';
			}
			n=n/16;
			i++;
		}while(n>0);
		
	
	
	
	while(i<=7)
		if(sign>=0)
			s[i++]='0';
		else
			s[i++]='F';
	s[i++]='x';
	s[i++]='0';
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





