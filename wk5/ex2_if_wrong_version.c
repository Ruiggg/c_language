#include<stdio.h>

int main(){
	int n=10,a=5;
	int i;
	if(n>0)
		for(i=0;i<n;i++)
			if(a>i)
				printf("a=%d, i=%d, and a>i\n",a,i);
	else
		printf("error:n<0\n");
	return 0;
}
