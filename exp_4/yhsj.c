#include<stdio.h>

int main(){
	int i,j;
	int t[10][20];
	for(i=0;i<10;i++)
		for(j=0;j<19;j++)
			t[i][j]=0;
	
	t[0][9]=1;
	for(i=1;i<10;i++)
		for(j=9-i;j<=9+i;j++)
		{
			if(j==9-i||j==9+i)
				t[i][j]=1;
			else
				t[i][j]=t[i-1][j-1]+t[i-1][j+1];
		}
	
	/*for(i=0;i<10;i++)
		for(j=0;j<19;j++)
		{
			if(t[i][j]==0)
				t[i][j]=' ';
			else
				t[i][j]=t[i][j]+'0';
		}*/
	
	for(i=0;i<10;i++)
		t[i][19]='\n';
	
	for(i=0;i<10;i++)
	{	
		for(j=0;j<19;j++)
		{
			if(t[i][j]==0)
			printf("%c",' ');
			else
			printf("%d",t[i][j]);
			
		}	
		printf("%c",'\n');
	}
	return 0;
}
