#include<stdio.h>
int func1(int a, int b);
int func2(int a, int b);

int main()
{
	int choice;
	int a=10,b=8,c;
	int (*pf)(int,int);
	printf("input your choice\n");
	printf("1 for func1, 2 for func2 :");
	scanf("%d",&choice);
	if(choice==1)
		pf=func1;
	else if(choice==2)
		pf=func2;
	else
		printf("Please input 1 or 2\n");
	c=(*pf)(a,b);
	printf("a=%d b=%d result=%d\n",a,b,c);
}

int func1(int a,int b)
{
	return a+b;
}	

int func2(int a,int b)
{
	return a-b;
}	

