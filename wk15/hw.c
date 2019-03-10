#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 100
#define NUM 10

struct stud{
	char p[MAXLEN];
	char name[MAXLEN];
	char gender[MAXLEN];
	int age;
};

void getinfo(struct stud *,int);
void show(struct stud *,int);
void qsort(struct stud *,int left,int right,int (*comp)(struct stud,struct stud));
int cmpage(struct stud ,struct stud );
void swap(struct stud *v,int i,int j);

int main(){
	struct stud s[NUM];
	getinfo(s,NUM);
	qsort(s,0,NUM-1,cmpage);
	show(s,NUM);
	return 0;
}

void getinfo(struct stud* s,int n){
	int i;
	for(i=0;i<n;i++){
		printf("please input the student ID:");
		scanf("%s",s[i].p);
		getchar();
		printf("please input the name:");
		scanf("%s",s[i].name);
		getchar();
		printf("please input the gender (male or female):");
		scanf("%s",s[i].gender);
		getchar();
		printf("please input the age:");
		scanf("%d",&(s[i].age));	
		getchar();
	}
}

void qsort(struct stud* v,int left,int right,int (*comp)(struct stud,struct stud))
{
	int i,last;
	void swap(struct stud *v,int,int);
	if(left>=right)
		return;
	swap(v,left,(left+right)/2);
	last=left;
	for(i=left+1;i<=right;i++)
		if((*comp)(v[i],v[left])<0)
			swap(v,++last,i);
	swap(v,left,last);
	qsort(v,left,last-1,comp);
	qsort(v,last+1,right,comp);
}

void swap(struct stud *v,int i,int j)
{
	struct stud temp;
	temp=v[i];
	v[i]=v[j];
	v[j]=temp;
}

int cmpage(struct stud s1,struct stud s2){
	int v1,v2;
	v1=s1.age;
	v2=s2.age;
	if(v1<v2)
		return -1;
	else if(v1>v2)
		return 1;
	else 
		return 0;
}


void show(struct stud* s,int n){
	int i;
		printf(" i	ID		name		gender	age\n");
	for(i=0;i<n;i++)
	{
		printf("%2d	%s		%s		%s	%3d\n",
			  i+1,s[i].p,s[i].name,s[i].gender,s[i].age);
	}
}
