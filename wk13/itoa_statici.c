#include<stdio.h>
#define MAXLEN 10
void itoa(int data, char a[]);

int main(){
	int n;
	char a[MAXLEN];
	scanf("%d",&n);
	itoa(n,a);
	printf("%s\n",a);
	return 0;
} 	

void itoa(int data, char a[])
{	
	static int i=0;
	if(data<0)
	{
		a[i++]='-';
		data=-data;
	}
	if(data/10)
		itoa(data/10,a);
	a[i++]=data%10+'0';
	a[i]='\0';
}
