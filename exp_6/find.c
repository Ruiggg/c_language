#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLINE 1000
char *mystrstr(char *s,char *t,int m);
int mygetline(char *line,int max);
int main(int argc,char *argv[])
{
	char line[MAXLINE];
	long lineno=0;
	int c,except=0,number=0,found=0,m=0;
	//解析命令行参数
	while(--argc>0 && (*++argv)[0]=='-')
		while(c=*++argv[0])
		/*	switch(c)
			{
				case 'x':
					except=1;break;
				case 'n':
					number=1;break;
				case '':
				
				
				default:
					printf("find: illegal option%c\n",c);
					argc=0; found=-1; break;
			}*/
		{
			if(c=='x')
				except=1;
			else if(c=='n')
				number=1;
			else if('0'<=c && c<='9')
			{
				m=m*10+(c-'0');	
			}
			else
			{
				printf("find: illegal option%c\n",c);
				argc=0; found=-1; break;
			}
		}	
	
	
	if(argc!=1)
		printf("Usage: find -x -n etc pattern\n");
	else
		while(mygetline(line,MAXLINE)>0){
			lineno++;
			if((mystrstr(line,*argv,m)!=NULL)!=except)
			{
				if(number)
					printf("%ld:",lineno);
				printf("%s",line);
				found++;
			}
		
		}
	
	return found;
}

int mygetline(char s[], int lim){
    int i,c;
    i=0;
    while(--lim>0 && (c=getchar())!=EOF && c!='\n')
          s[i++]=c;
    if(c=='\n')
          s[i++]='\n';
    s[i]='\0';
    return i;
}

char *mystrstr(char *s,char *t,int m)
{
	int i,j,k,ct=0;	
		for(i=0;s[i]!='\0';i++)
			for(j=i,k=0;t[k]!='\0' && s[j]==t[k];j++,k++)
				if(t[k+1]=='\0')
					ct++;
	
	if(ct<m)
		return NULL;
	else
		return s+i;	
}




