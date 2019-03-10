#include<stdio.h>
#include<string.h>
#define MAXLEN 100
void move(char *p,int m);
int main()
{
	char t[MAXLEN]="ABCDEFGHIJK";
	int m=3;
	
	move(t,m);
	printf("after move, t = %s\n",t);
	return 0;
}

void move(char *pr,int m)
{
	int i,j,k,temp;
	char s[MAXLEN];
	for(j=0;j<m;j++)
	{
		*(s+j)=*(pr+j);
	}
	for(i=0;i<strlen(pr)-m;i++)
		*(pr+i)=*(pr+i+m);
	
	for(k=i;k<strlen(pr);k++)
		*(pr+k)=*(s+k-i);
}
