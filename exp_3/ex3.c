#include<stdio.h>

int main(){
	int c;
	while((c=getchar())!=EOF)
	printf("%c",jiami(c));
	return 0;
}

int jiami(int c)
{
	if((c>='A'&&c<='U')||(c>='a'&&c<='u'))
		return (c+5);
	else if((c>='V'&&c<='Z')||(c>='v'&&c<='z'))
		return c-26+5;
	else
		return c;
}
