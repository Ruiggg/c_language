#include "myhead.h"
int main(){
	struct tnode *ptree;
	char word[MAXWORD];
	ptree=NULL;
	while(getword(word,MAXWORD)!=EOF){
		if(isalpha(word[0])){
			ptree=addtree(ptree,word);
		}
	}
	printf("the results are:\n");
	treeprint(ptree);
	return 0;
}

struct tnode *addtree(struct tnode * ptree,char *word){
	struct tnode *p,*q;
	q=ptree;
	int cmpresult;
	if(ptree == NULL){
		p=talloc();
		p->word=mystrdup(word);
		p->count=1;
		p->left = p->right = NULL;
		return p;
	}
	q=ptree;
	while((cmpresult = strcmp(word,q->word))!=0){
		if(cmpresult > 0){
			if(q->right==NULL){
				p=talloc();
				p->word=mystrdup(word);
				p->count=1;
				p->left = p->right = NULL;
				q->right=p;
				return ptree;
			}else
				q=q->right;
		}
		else if(cmpresult < 0){
			if(q->left==NULL){
				p=talloc();
				p->word=mystrdup(word);
				p->count=1;
				p->left = p->right = NULL;
				q->left=p;
				return ptree;
			}else
				q=q->left;
		}
	}
	
	q->count++;
	return ptree;
}

struct tnode * talloc(void){
	return (struct tnode*)malloc(sizeof(struct tnode));
}

char *mystrdup(char *s){
	char *p;
	p=(char *)malloc(strlen(s)+1);
	if(p!=NULL)
		strcpy(p,s);
	return p;
}

void treeprint(struct tnode *ptree){
	if(ptree){
		treeprint(ptree->left);
		printf("%4d %s\n",ptree->count,ptree->word);
		treeprint(ptree->right);
	}
}






