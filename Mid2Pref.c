#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;

typedef struct Stack {
    char* * base;
    char* * top;
    int stacksize;
}SqStack;

Status InitStack(SqStack * S){
    //create a empty stack
    S->base = (char**)malloc(STACK_INIT_SIZE * sizeof(char*));
    if(!S->base)
        exit(OVERFLOW);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack *S,char *e){
    if(S->top - S->base >= S->stacksize) {
        S->base = (char * *)realloc(S->base,(S->stacksize + STACKINCREMENT)*sizeof(char *));
        if(!S->base)exit(OVERFLOW);

        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *(S->top++) = e;
    return OK;
}

Status Pop(SqStack *S,char **e){
    if(S->top == S->base)return ERROR;
    *e = *(--S->top);
    return OK;
}

char * getstring(void){
    char *pr = (char *)malloc(2*sizeof(char));
    pr[0] = getchar();
    pr[1] = '\0';
    return pr;
}

char * mergeString(char *front,char *back){
    int length = strlen(front) + strlen(back);
    char * pr = (char*)malloc((length+1)*sizeof(char));
    strcpy(pr,front);
    strcat(pr,back);
    //free(front);
    //free(back);
    return pr;
}

char * GetTop(SqStack *S){
    if(S->base == S->top) exit(ERROR);
    char *e = *(S->top - 1);
    return e;
}

char Precede(char c1,char c2,char Board[7][7]){
    int i,j;
    switch(c1){
        case '+': i=0;break;
        case '-': i=1;break;
        case '*': i=2;break;
        case '/': i=3;break;
        case '(': i=4;break;
        case ')': i=5;break;
        case '#': i=6;break;
    }
    switch(c2){
        case '+': j=0;break;
        case '-': j=1;break;
        case '*': j=2;break;
        case '/': j=3;break;
        case '(': j=4;break;
        case ')': j=5;break;
        case '#': j=6;break;
    }
    return Board[i][j];
}

char * MidtoPost(char Board[7][7]){
    SqStack OPTR,OPND;
    char* theta,*a,*b,*t,*m;
    char s[2] = "#";
    InitStack(&OPTR); Push(&OPTR,s);
    InitStack(&OPND);
    char *str=getstring();
    while(str[0]!='\n' || GetTop(&OPTR)[0]!='#'){
        if(str[0]=='\n'){
            Pop(&OPTR,&theta); Pop(&OPND,&b); Pop(&OPND,&a);
            t = mergeString(mergeString(a,b),theta);
            Push(&OPND,t);
        }
        else if((str[0]>='A' && str[0]<='Z')||(str[0]>='a' && str[0]<='z')){
            Push(&OPND,str);
            str = getstring();
        }
        else{
            switch(Precede(GetTop(&OPTR)[0],str[0],Board)){
                case '<': Push(&OPTR,str); str=getstring(); break;
                case '=': Pop(&OPTR,&str); str=getstring(); break;
                case '>': Pop(&OPTR,&theta); Pop(&OPND,&b); Pop(&OPND,&a);
                          t = mergeString(mergeString(a,b),theta);
                          Push(&OPND,t); break;
            }
        }
    }

    return GetTop(&OPND);
}

int main(void){
    char PriorBoard[7][7]={
    //+   -   *   /   (   )   #
    {'>','>','<','<','<','>','>'},//+
    {'>','>','<','<','<','>','>'},//-
    {'>','>','>','>','<','>','>'},//*
    {'>','>','>','>','<','>','>'},// /
    {'<','<','<','<','<','=',' '},//(
    {'>','>','>','>',' ','>','>'},//)
    {'<','<','<','<','<',' ','='} //#
    };
    char *result;
    result = MidtoPost(PriorBoard);
    printf("%s",result);
}
