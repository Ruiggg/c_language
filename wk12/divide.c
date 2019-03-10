#include <stdio.h>
#include <stdlib.h>
#define NUM 10


void print_num(int a[],int n);
int all_equal(int a[],int n);

int main(int argc, char * argv[])
{
	int a[NUM];
	int num,i;
	for(i=1;i<=NUM;i++)
		a[i-1]=atoi(*(argv+i));
	
	print_num(a,NUM);
	
	while(!all_equal(a,NUM))
	{
		for(i=0;i<NUM;i++)
			if(a[i]%2==1)
				a[i]++;
		
		print_num(a,NUM);
		
		int a_bak[NUM];
		for(i=0;i<NUM;i++)
			a_bak[i]=a[i];
			
		for(i=1;i<NUM;i++)
			a[i]=a_bak[i]/2+a_bak[i-1]/2;
		a[0]=a_bak[0]/2+a_bak[NUM-1]/2;
		
		print_num(a,NUM);
	}
	
	return 0;
}

void print_num(int a[],int n)
{	
	int j;
	for(j=0;j<n;j++)
		printf("%d ",a[j]);
	printf("\n");
}


int all_equal(int a[],int n)
{
	int j;
	for(j=0;j<n;j++)
		if(a[j]!=a[0])
			return 0;
	return 1;
}






