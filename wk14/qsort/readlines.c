#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 1000

int mygetline(char*,int);
char *alloc(int);

//readlines把最多maxlines行读到指针数组lineptr中，每个指针指向一个字符串（带\0）的首字母
int readlines(char *lineptr[],int maxlines)
{
	int len,nlines;
	char *p,line[MAXLEN];
	nlines=0;
	while((len=mygetline(line,MAXLEN))>0)
		if(nlines>=maxlines || (p=alloc(len))==NULL)
			return -1;
		else
		{
			line[len-1]='\0';
			strcpy(p,line);
			lineptr[nlines++]=p;
		}
	return nlines;
}

void writelines(char *lineptr[],int nlines)
{
	int i;
	printf("after sorting:\n");
	for(i=0;i<nlines;i++)
		printf("%s\n",lineptr[i]);
}
