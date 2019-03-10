#include <stdio.h>
#define MAXLEN 1000

int mygetline(char line[],int );
void copy(char to[],char from[]);
int main()
{
	int len;
	char line[MAXLEN];
	char shortest0[MAXLEN];
	char shortest1[MAXLEN];
	int lenShort[2]={MAXLEN+1,MAXLEN+1};
	int secOne=1;
	while((len=mygetline(line,MAXLEN))>0)
	{
		if(len<lenShort[secOne])
		{
			lenShort[secOne]=len;
			
			if(secOne==0)
				copy(shortest0,line);
			else
				copy(shortest1,line);
				
			secOne=(lenShort[0]>=lenShort[1])?0:1;
		}
	}	
	
	if(lenShort[0]<MAXLEN+1)
			printf("One of the shortest is:len=%d, string=%s.\n",lenShort[0],shortest0);
	if(lenShort[1]<MAXLEN+1)
			printf("One of the shortest is:len=%d, string=%s.\n",lenShort[1],shortest1);
	
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
	while((to[i]=from[i])!='\0')
	++i;
}

