#include<stdio.h>
#include<ctype.h>
#define NUMBER '0'
int getch(void);
void ungetch(int);
int getop(char s[])
{
	int i,c;
	while((s[0]=c=getch())==' '||c=='\t')//till the first non_space
	;
	s[1]='\0';
	if(!isdigit(c)&&c!='.')
		return c;
	
	i=0;
	if(isdigit(c))
		while(isdigit(s[++i]=c=getch()))//already put in s[0]
			;
	if(c=='.')
		while(isdigit(s[++i]=c=getch()))
		;
	s[i]='\0';
	if(c!=EOF)
		ungetch(c);
		
	return NUMBER;
			
	
}
