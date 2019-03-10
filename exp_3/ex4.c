#include<stdio.h>
#define MAXLEN 1000
void yuanyin(char t[],char s[]);
int main(){
	char s[MAXLEN],t[MAXLEN];
	int c,i;
	i=0;
	while(((c=getchar())!=EOF) && i<MAXLEN)
	{
		s[i]=c;
		i++;
	}
	s[i]='\0';
	yuanyin(t,s);
	printf("t=%s",t);
	return 0;
}

void yuanyin(char t[],char s[])
{
	int i=0,j=0;
	while(s[i]!='\0')
	{	if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u')
			t[j++]=s[i];
		i++;
	}
	t[j]='\0';
}
