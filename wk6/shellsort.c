#include<stdio.h>
int shellsort(int s[], int len);
int main()
{	
	int s[8];
	int i,c;
	for(i=0;i<8;i++)
		s[i]=8-i;
	printf("\nbefore shell sort:\n");
	for(i=0;i<8;i++)
		printf(" s[%d]=%d ",i,s[i]);
	
	c=shellsort(s,8);
		
	printf("\nafter shell sort:\n");
	for(i=0;i<8;i++)
		printf(" s[%d]=%d ",i,s[i]);
		printf("\nthe number of swap is %d\n",c);
	return 0;
}

int shellsort(int s[], int len)
{
	int i,j,gap;
	int temp;
	int c=0;
	for(gap=len/2;gap>0;gap/=2)
	{
		for(i=gap;i<len;i++)
		{
			for(j=i-gap;j>=0 && s[j]>s[j+gap];j-=gap)
			{
				temp=s[j+gap];
				s[j+gap]=s[j];
				s[j]=temp;
				c++;
			}
		}
	}
	return c;
}
