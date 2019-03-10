#include<stdio.h>
#define MAXLEN 10
void itoa(int data, char a[]);

int i=0;
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
