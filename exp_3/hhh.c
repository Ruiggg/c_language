#include<stdio.h>
#define MAXLEN 1000
int mygetline(char s[],int lim);
void copy(char to[],char from[]);
int main()
{
	int min[2];
	int len[2];
	char line1[MAXLEN];
	char line2[MAXLEN];
	char short1[MAXLEN];
	char short2[MAXLEN];
	
	len[0]=mygetline(line1,MAXLEN);
	len[1]=mygetline(line2,MAXLEN);
	
	if(len[0]<len[1])
	{
		copy(short1,line1);
		copy(short2,line2);
		min[0]=len[0];
		min[1]=len[1];
	}
	else
	{
		copy(short2,line1);
		copy(short1,line2);
		min[1]=len[0];
		min[0]=len[1];
	}
	while((len[0]=mygetline(line1,MAXLEN))>0)
	{
		if(len[0]<min[0])
		{
			copy(line2,short1);
			copy(short1,line1);
			copy(short2,line2);
			min[1]=min[0];
			min[0]=len[0];
		}
		else if(len[0]<min[1])
		{
			copy(short2,line1);
			min[1]=len[0];
			
		}
	}
return 0;
}

int mygetline(char s[],int lim)
{
	int c,i;
	for(i=0;i<lim&&(c=getchar())!=EOF && c!='\n';i++)
		s[i]=c;
	if(c=='\n')
	{
		s[i]=c;
		i++;
	}
	s[i]='\0';
	return i;
}

void copy(char to[],char from[])
{
	int i=0;
	while((to[i]=from[i])!='\n')
	++i;
}







