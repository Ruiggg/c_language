#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HASHSIZE 101
struct node{
	struct node *next;
	char *name;
	char *defn;
};
static struct node *hashtab[HASHSIZE];//静态全局变量
struct node *install(char *name,char *defn);
struct node *lookup(char *s);
unsigned hash(char *s);
void buildlist();
char *mystrdup(char *s);
int main(){
	struct node *pnode;
	char keyword[100];
	buildlist();
	printf("Please input keyword:");
	scanf("%s",(char *)keyword);
	
	pnode=(struct node*)lookup(keyword);
	if(pnode)
		printf("%s>>>%s\n",pnode->name,pnode->defn);
	else
		printf("not found\n");
	return 0;
}

void buildlist(){
	struct name_and_defn{
		char *name;
		char *defn;
	};
	struct name_and_defn ndpairs[]={
		{"IN","1"},{"OUT","2"},{"MAX","10000"},{"ZHANGSAN","1"},
		{"LIST","2"},{"MIN","3"},{"NUMBER","1024"}
	};
	int i;
	
	for(i=0;i<sizeof(ndpairs)/sizeof(struct name_and_defn);i++)
		install(ndpairs[i].name,ndpairs[i].defn);
	
	return;
}

struct node *install(char *name, char *defn){
//插入，根据name查找，如果找到，替换defn;没找到，建立
	struct node *np;
	unsigned hashval;
	
	if((np=lookup(name))==NULL){//如果这个没在列表中
		np=(struct node*) malloc(sizeof(*np));
		if(np==NULL || (np->name = strdup(name))==NULL)
			return NULL;//由于意外导致操作失败
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval]=np;		
	}else
		free((void *)np->defn);//原来的defn被释放
	
	if((np->defn = mystrdup(defn))==NULL)
		return NULL;
	return np;
}

unsigned hash(char *s){
	unsigned hashval;
	for(hashval = 0; *s!='\0';s++)
		hashval = *s+31*hashval;
	return hashval % HASHSIZE;
}

char *mystrdup(char *s){
	char *p;
	p=(char *)malloc(strlen(s)+1);
	if(p!=NULL)
		strcpy(p,s);
	return p;
}

struct node *lookup(char *s){
	struct node *np;
	for(np=hashtab[hash(s)];np!=NULL;np=np->next)
		if(strcmp(s,np->name)==0)
			return np;
	return NULL;
}










