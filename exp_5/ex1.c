#include<stdio.h>
#define MAXLEN 100
void itoa(int n);
char t[MAXLEN];
int main()
{	
	int n;
	//int times=0;
	printf("input an integer:");
	scanf("%d",&n);
	itoa(n);
	printf("itoa:%s\n",t);
}

void itoa(int n)
{	
	if(n<0)
	{
		t[0]='-';
		n=-n;
	}
	if(n/10)
		itoa(n/10);
	int i;
	for(i=0;t[i]!=0;i++)
	;
	t[i++]=n%10+'0';
	
		t[i]='\0';
}
