#include<stdio.h>
#define MAXLEN 100
int strindex(char s[],char t[]);
int mygetline(char s[],int lim);
char pattern[]="ould";
int main(){
	char line[MAXLEN];
	int found=0;
	while(mygetline(line,MAXLEN)>0)
	{
		if(strindex(line,pattern)>=0)
			printf("%s",line);
			found++;
	}
	return found;
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

int strindex(char s[],char t[])
{
	int i,j,k;
	for(i=0;s[i]!='\0';i++)
	{
		for(j=i,k=0;t[k]!='\0' && s[j]==t[k];j++,k++)
			;
		if(k>0&&t[k]=='\0')
			return i;
	}	
	
	return -1;
}






