#include<stdio.h>
void insertsort(int s[],int len);
void show_ar(int s[],int len);
int main()
{	
	int MAXLEN,i;
	printf("Enter a integer:");
	scanf("%d",&MAXLEN);
	
	int ar1[MAXLEN];
	int ar2[MAXLEN];
	int ar3[MAXLEN];
	
	printf("the 1st array:");
	for(i=0;i<MAXLEN;i++)
	scanf("%d",&ar1[i]);
	
	printf("the 2nd array:");
	for(i=0;i<MAXLEN;i++)
	scanf("%d",&ar2[i]);
	
	printf("the 3rd array:");
	for(i=0;i<MAXLEN;i++)
	scanf("%d",&ar3[i]);
	
	insertsort(ar1,MAXLEN);
	insertsort(ar2,MAXLEN);
	insertsort(ar3,MAXLEN);
	printf("ar1:\n");
	show_ar(ar1,MAXLEN);
	printf("ar2:\n");
	show_ar(ar2,MAXLEN);
	printf("ar3:\n");
	show_ar(ar3,MAXLEN);
	return 0;
}

void insertsort(int s[],int len)
{	
	int i,j,t;
	for(i=0;i<len-1;i++)
		for(j=i+1;j<len;j++)
		{
			if(s[i]>s[j])
			{
				t=s[i];
				s[i]=s[j];
				s[j]=t;
			}
		}
}

void show_ar(int s[],int len)
{
	int i;
	for(i=0;i<len;i++)
	printf("array[%d]=%d\n",i,s[i]);
}
