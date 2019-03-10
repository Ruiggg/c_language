#include <stdio.h>
#include <ctype.h>
#define MAXLEN 200
void sum(char *t,char *s1,char *s2,int len1,int len2);
int getnum(char *s);
int main()
{	
	int j,len1,len2;
	char s1[MAXLEN];
	char s2[MAXLEN];
	//for(j=0;j<MAXLEN;j++)
	//	s1[j]=s2[j]=0;
	char t[MAXLEN+1];
	for(j=0;j<MAXLEN+1;j++)
		t[j]=0;
	
	printf("input an integer:\n");
	len1=getnum(s1);
	if(len1>MAXLEN)
		printf("warnning: only the first 200 can be read!");
	printf("input an integer:\n");
	len2=getnum(s2);
	if(len2>MAXLEN)
		printf("warnning: only the first 200 can be read!");
	sum(t,s1,s2,len1,len2);
	printf("sum=");
	for(j=0;t[j]==0;j++)
		;
	for(;j<=MAXLEN;j++)
		printf("%c",t[j]+'0');
	printf("\n");
	return 0;
}

int getnum(char *s)//将读到的数给数组s,过长则只读前200位，出现非数字则只读它前面的数字
{
	int c,i=0;
	while(i<=MAXLEN-1 && (c=getchar())!='\n' && isdigit(c))
			s[i++]=c-'0';
	return i;
}

void sum(char *t,char *s1,char *s2,int len1,int len2)
{
	int m,n;
	int lenlo,lensh;
	if(len1>len2)
		lenlo=len1,lensh=len2;
	else
		lenlo=len2,lensh=len1;
	
	int i;
	for(i=0;i<lensh;i++)
		t[MAXLEN-i]=s1[len1-i-1]+s2[len2-i-1];
	
	for(i=lensh;i<lenlo;i++)
		t[MAXLEN-i]=(len1>len2?s1:s2)[lenlo-i];
	
	for(i=MAXLEN;i>0;i--)
	{	
		if(t[i]>9)
			t[i-1]++,t[i]-=10;
		
	}
}











