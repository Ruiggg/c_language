#include<stdio.h>
int is_sx(int n);
int main(){
	int i;
	for(i=100;i<1000;i++)
		if(is_sx(i))
			printf("%6d",i);
	return 0;
}

int is_sx(int n)
{
	int b,s,g;
	b=n/100;
	s=(n/10)%10;
	g=n%10;
	if(n==(b*b*b+s*s*s+g*g*g))
		return 1;
	else 
		return 0;
}
