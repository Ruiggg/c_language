#include<stdio.h>

int main(){
	int nw,state,c;
	state = 0;
	nw=0;
	while((c=getchar())!=EOF)
	{
		if(c==' ' || c=='\n' || c=='\t')
			state = 0;
		else
			if(state==0)
			{
				++nw;
				state=1;
			}
	}
	
	printf("\n The amount of words is %d. \n",nw);
	return 0;
}
