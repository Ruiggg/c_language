#include<stdio.h>
#include<ctype.h>
#define BUFSIZE 100
#define SIZE 10
int getch(void);
void ungetch(int);
//getint函数
int getint(int *pn){
	int c,sign;
	while(isspace(c=getch()))
		;
	if(!isdigit(c) && c!=EOF && c!='+' && c!='-'){
		ungetch(c);
		return 0;
	}
	sign=(c=='-')?-1:1;
	if(c=='+' || c=='-')
		c=getch();
	for(*pn=0;isdigit(c);c=getch())
		*pn=10* *pn+ (c-'0');
	*pn*=sign;
	if(c!=EOF)
		ungetch(c);
	return c;	
}

char buf[BUFSIZE];
int bufp=0;
//getch函数
int getch(void)
{
	return (bufp>0)?buf[--bufp]:getchar();
}
//ungetch函数
void ungetch(int c)
{
	if(bufp>=BUFSIZE)
		printf("ungetch: too many chararcters\n");
	else
		buf[bufp++]=c;
}


int array[SIZE];
//main函数
int main()
{
	int n,getint(int *);
	for(n=0;n<SIZE && getint(&array[n])!=EOF;n++)
		;
	for(n=0;n<SIZE;n++)
		printf("array[%d]=%d\n",n,array[n]);
	return 0;
}
