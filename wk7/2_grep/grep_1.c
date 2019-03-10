#include<stdio.h>
#define MAXLEN 100
char pattern[]="ould";
int main(){
	char line[MAXLEN];
	int found=0;
	while(mygetline(line,MAXLEN)>0)
	{
		if(strindex(line,pattern)>=0)
			printf("%s",line);
			found++;
	}
	return found;
}


