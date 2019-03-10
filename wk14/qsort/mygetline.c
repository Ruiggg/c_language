#include <stdio.h>
//把行保存到s中，并返回该行的长度
int mygetline(char s[],int lim)//最多有lim-1次读进c
{
	int i,c;
	i=0;
	while(--lim>0 && (c=getchar())!=EOF && c!='\n')
		s[i++]=c;
	
	if(c=='\n')
		s[i++]='\n';//把\n也存到s里面
		
	s[i]='\0';//在\n后面加上\0代表字符串结尾
	return i;//由于从0开始数，所以i既是\0的下标也是字符串长度，这里的长度算上了\n
}


