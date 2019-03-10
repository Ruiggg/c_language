#include<stdio.h>
int main(){
	void hanio(int n,char a,char b,char c);
	int m;
	printf("input the number of disks:");
	scanf("%d",&m);
	printf("the step to move %d disks:\n",m);
	hanio(m,'A','B','C');
	return 0;
}

void hanio(int n,char a,char b,char c)
{
	void move(char x,char y);
	if(n==1)
		move(a,c);
	else
	{
		hanio(n-1,a,c,b);
		move(a,c);
		hanio(n-1,b,a,c);
	}
}

void move(char x,char y)
{
	printf("%c->%c\n",x,y);
}
