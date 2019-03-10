#include <stdio.h>
#include <stdlib.h>
struct lnode{
	int number;
	struct lnode* next;
};

int left(int n,int k,int t);
struct lnode* lalloc();
struct lnode* buildlist(int n);
int main(int argc,char *argv[]){
	int n,k,t,leftno;
	if(argc!=4 || (n=atoi(argv[1]))<=0 ||(k=atoi(argv[2]))<=0 ||(t=atoi(argv[3]))<=0){
		printf("Usage: ./ysf n k t\n");
		return 1;
	}
	/*while(t-->0){
	leftno = left(n,k,t);
	printf("The last %d to quit is %d\n",t,leftno);
	}*/
	leftno = left(n,k,t);
	return 0;
}

int left(int n,int k,int t){
	int count=1,leftno,i=n;
	struct lnode *plist,*pre,*p;
	plist = buildlist(n);
	pre=plist;
	while((pre->next)->next!=plist)
		pre=pre->next;  //pre point to the fomer of the 1st node
	while(n>0){
		if(count%k==0){
			p=pre->next;
			if(i==n+3)
				;
			pre->next=p->next;
			if(n<=t)
				printf("The last %d to quit is %d\n",n,p->number);
			free(p);
			n--;
		}else
			pre=pre->next;
		count++;
	}
	leftno=pre->number;
	//free(pre);
	return leftno;
}

struct lnode * buildlist(int n){
	struct lnode *plist,*plast,*p;
	plist=lalloc();
	plist->number=n;
	plist->next = plist;
	plast = plist;
	while(--n>0){
		p=lalloc();
		p->number=n;
		p->next=plist;
		plist=p;
	}
	plast->next = plist;
	return plist;
}

struct lnode* lalloc(){
	return (struct lnode*)malloc(sizeof(struct lnode));
}

