#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXOP 100
#define NUMBER '0'
int getop(char []);
void push(double);
double pop(void);
extern int sp;
int main()
{	
	int type;
	double op1,op2;
	char s[MAXOP];
	int num=0,cnum=0;
	while((type=getop(s))!=EOF)
	{
		switch(type)
		{
			case NUMBER:
				push(atof(s)); num++;break;
			case '+':
				push(pop()+pop()); cnum++;break;
			case '*':
				push(pop()*pop());cnum++; break;
			case '-':
				op2=pop();
				push(pop()-op2); cnum++;break;
			case '/':
				cnum++;
				op2=pop();
				if(op2!=0.0)
					push(pop()/op2);
				else
					{printf("error: zero divisor!\n");sp=0;}
				break;
			case '%':
				cnum++;
				op2=pop();
				if(op2!=0.0)
					push((double)((int)pop()%(int)op2)); 
				else
					{printf("error: zero remainder!\n"); sp=0;}break;
			case '&':
				cnum++;
				push((double)((int)pop()&(int)pop())); break;
			case '|':
				cnum++;
				push((double)((int)pop()|(int)pop())); break;
			
			case '<':
				cnum++;
				if(getop(s)=='<')
				{op2=pop();
				push((double)((int)pop()<<(int)op2));}
				else
				{
				printf("error: lack a <\n");
				sp=0;
				}
				 break;
			case	'>':
				cnum++;
				if(getop(s)=='>')
				{op2=pop();
				push((double)((int)pop()>>(int)op2));}
				else
				{
				printf("error: lack a >\n");
				sp=0;
				}	
				break;
			case '\n':
				if(num!=cnum+1)
				{
					printf("error: incompelete expression!\n");
					sp=0;
					num=cnum=0;
				}
				else
				{printf("\t%.8g\n",pop()); sp=0; num=cnum=0;}
				
				break;
			default:
				printf("error: unknown command %s\n",s); sp=0; break;
		}
	}
	return 0;
}
