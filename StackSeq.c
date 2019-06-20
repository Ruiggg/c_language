#include<stdio.h>
#include<stdlib.h>

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
    int * base;
    int * top;
    int stacksize;
}SqStack;

Status InitStack(SqStack * S){
    //create a empty stack
    S->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if(!S->base)
        exit(OVERFLOW);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack *S,int e){
    if(S->top - S->base >= S->stacksize) {
        S->base = (int *)realloc(S->base,(S->stacksize + STACKINCREMENT)*sizeof(int));
        if(!S->base)exit(OVERFLOW);

        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *(S->top++) = e;
    return OK;
}

Status Pop(SqStack *S,int *e){
    if(S->top == S->base)return ERROR;
    *e = *(--S->top);
    return OK;
}
int match(void){
    SqStack S;
    InitStack(&S);
    int c,sign=0;
    while((c=getchar())!='@'){
        if(c!='&' && sign ==0)
            Push(&S,c);
        else if(c!='&' && sign ==1 && c==*(S.top-1)){
            Pop(&S,&c);
        }
        else if(c=='&'){
            sign = 1;
        }
    }
    if(S.top == S.base)
        return 1;
    else
        return 0;
}

int main(void){
    int n = match();
    printf("%d",n);
    return 0;
}



