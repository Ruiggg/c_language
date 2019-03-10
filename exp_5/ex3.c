#include<stdio.h>
#include<string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];
int readlines(char *lineptr[],int nlines);
void writelines(char *lineptr[],int nlines);
//void myqsort(char *lineptr[],int left,int right);
int shellsort(char *v[],int len);
int main(){
    int nlines;
    if((nlines=readlines(lineptr,MAXLINES))>=0){
       shellsort(lineptr,nlines);
       printf("After Sorting ....\n");
       writelines(lineptr,nlines);
       return 0;    
    }else{
       printf("error: input too big to sort\n");
       return 1;
    }
}

//readline writelines 的实现
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAXLEN 1000

int mygetline(char[],int);  //需要mygetline的实现
char *alloc(int);

int readlines(char *lineptr[],int maxlines){
    int len,nlines;
    char *p,line[MAXLEN];
    nlines=0;
    while((len=mygetline(line,MAXLEN))>0)
       if(nlines>=maxlines || (p=alloc(len))==NULL)
          return -1;
       else{
          line[len-1]='\0';
          strcpy(p,line);
          lineptr[nlines++]=p;
       }
    return nlines;
}

void writelines(char *lineptr[],int nlines){
     int i;
     for(i=0;i<nlines;i++)
     printf("%s\n",lineptr[i]);
}

//mygetline
#include<stdio.h>
int mygetline(char s[], int lim){
    int i,c;
    i=0;
    while(--lim>0 && (c=getchar())!=EOF &&c!='\n')
          s[i++]=c;
    if(c=='\n')
          s[i++]='\n';
    s[i]='\0';
    return i;
}

//alloc函数的实现
#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char *allocp=allocbuf;
char *alloc(int n){
      if(allocbuf+ALLOCSIZE-allocp>=n){
         allocp+=n;
         return allocp-n;
      }else
         return 0;
}

void afree(char *p){
     
     if(p>=allocbuf && p<allocbuf+ALLOCSIZE)
     allocp=p;
     }
     
//qsort 的实现
/*#include<string.h>

void myqsort(char *v[], int left, int right){
     int i,last;
     void swap(char *v[], int i,int j);
     if(left>=right)
        return;
     swap(v,left,(left+right)/2);
     last=left;
     for(i=left+1; i<=right; i++)
         if(strcmp(v[i],v[left])<0)
                  swap(v,++last,i);
            swap(v, left, last);
            myqsort(v, left, last-1);
            myqsort(v,last+1,right);
}

void swap(char *v[], int i,int j){
     char *temp;
     temp=v[i];
     v[i]=v[j];
     v[j]=temp;
}*/

int shellsort(char *s[],int len)
{
	int i,j,gap;
	char *temp;
	for(gap=len/2;gap>0;gap/=2)
		for(i=gap;i<len;i+=1)
			for(j=i-gap;j>0 && strcmp(s[j],s[j+gap])>0;j-=gap)
			{
				temp=s[j+gap];
				s[j+gap]=s[j];
				s[j]=temp;
			}
}

