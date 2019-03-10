#include<stdio.h>
int main(){
	int a,b,s,c;
	a=0,b=3,c=10;
	if(a++>0 || ++b<5 || c--)
		s=a+b^c;
	else
		s=a-b|c;
	printf("s=%d a=%d b=%d c=%d\n",s,a,b,c);
	return 0;
}
