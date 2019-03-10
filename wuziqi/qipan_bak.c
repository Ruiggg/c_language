#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 15
#define CHARSIZE 3
#define MAXLEN 1000
void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);


//棋盘使用的是GBK编码，每一个中文字符占用2个字节。

//棋盘基本模板 
char aInitDisplayBoardArray[SIZE][SIZE*CHARSIZE+1] = 
{
		"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};
//此数组用于显示棋盘 
char aDisplayBoardArray[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="●";//黑棋子;
char play1CurrentPic[]="▲"; 

char play2Pic[]="◎";//白棋子;
char play2CurrentPic[]="△";

//此数组用于记录棋盘格局 
int aRecordBoard[SIZE][SIZE];
int aRecordBoard2[SIZE][SIZE];

int main()

{
    initRecordBorard();
    recordtoDisplayArray();
    displayBoard();
    int a,b,c,i=1;
    char s[MAXLEN];
    printf("input \"quit\" to quit the game, others to continue:");
    scanf("%s",s);
    printf("\n");
    while(strcmp(s,"quit")!=0)
    {
     	printf("input 2 integer:");
   	
   	/*while(scanf("%d %d",&a,&b)!=2)
    	{
    		printf("error:please input 2 integers:");
    		while(getchar()!='\n')
    			;
    	}
    	
    	while(a<1||a>15||b<1||b>15)
    	{
    		printf("a and b should be 1~15\n");
    		scanf("%d %d",&a,&b);
    	}
    	
    	while(aRecordBoard2[15-a][b-1]!=0)
    	{
    		printf("There is already taken! Try again!\n");
    		scanf("%d %d",&a,&b);
    	}*/
    	while(1)
    	{	
    		c=scanf("%d %d",&a,&b);
    		if(c!=2)
    		{
    			printf("error:please input 2 integers:");
    			while(getchar()!='\n')
    			;
    			continue;
    		}
    		else if(a<1||a>15||b<1||b>15)
    		{
    			printf("a and b should be 1~15\n");
    			printf("input 2 integer:");
    			continue;
    		}
    		else if(aRecordBoard2[15-a][b-1]!=0)
    		{
    			printf("There is already taken! Try again!\n");
    			printf("input 2 integer:");
    			continue;
    		}
    		else
    		{
    			break;
    		}
    	}
    	
    	
    	if(i%2==1)
    		aRecordBoard2[15-a][b-1]=1;
    	else
    		aRecordBoard2[15-a][b-1]=2;
    	recordtoDisplayArray();
    	displayBoard();
    	
    	i++;//i chuxian bianhua
    	
    	printf("input \"quit\" to quit the game, others to continue:");
    	scanf("%s",s);
   
    }//xun huan jie shu
    
    return 0;
}

//初始化棋盘格局 
void initRecordBorard(void){
//通过双重循环，将aRecordBoard清0
	int i,j;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			aRecordBoard[i][j]=0;
}

//将aRecordBoard中记录的棋子位置，转化到aDisplayBoardArray中
void recordtoDisplayArray(void){
//第一步：将aInitDisplayBoardArray中记录的空棋盘，复制到aDisplayBoardArray中
	int i,j;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE*CHARSIZE+1;j++)
			aDisplayBoardArray[i][j]=aInitDisplayBoardArray[i][j];
//第二步：扫描aRecordBoard，当遇到非0的元素，将●或者◎复制到aDisplayBoardArray的相应位置上
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
		{
			if(aRecordBoard2[i][j]!=0)
				if(aRecordBoard2[i][j]==1 && aRecordBoard[i][j]==aRecordBoard2[i][j])
				{
					aDisplayBoardArray[i][3*j]=play1Pic[0];
					aDisplayBoardArray[i][3*j+1]=play1Pic[1];
					aDisplayBoardArray[i][3*j+2]=play1Pic[2];
		   	        }
		   	      else if(aRecordBoard2[i][j]==2 && aRecordBoard[i][j]==aRecordBoard2[i][j])
		   	      	{
		   	      	aDisplayBoardArray[i][3*j]=play2Pic[0];
		   	      	aDisplayBoardArray[i][3*j+1]=play2Pic[1];
		   	      	aDisplayBoardArray[i][3*j+2]=play2Pic[2];	
		   	      	}
		   	      else if(aRecordBoard2[i][j]==1 && aRecordBoard[i][j]!=aRecordBoard2[i][j])
		   	       {
					aDisplayBoardArray[i][3*j]=play1CurrentPic[0];
					aDisplayBoardArray[i][3*j+1]=play1CurrentPic[1];
					aDisplayBoardArray[i][3*j+2]=play1CurrentPic[2];		   	      
		   	       }
		   	      else if(aRecordBoard2[i][j]==2 && aRecordBoard[i][j]!=aRecordBoard2[i][j])
		   	       {
					aDisplayBoardArray[i][3*j]=play2CurrentPic[0];
					aDisplayBoardArray[i][3*j+1]=play2CurrentPic[1];
					aDisplayBoardArray[i][3*j+2]=play2CurrentPic[2];		   	      
		   	       }
		}	
	
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			aRecordBoard[i][j]=aRecordBoard2[i][j];
//注意：aDisplayBoardArray所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
}


//显示棋盘格局 
void displayBoard(void){
	int i;
	//第一步：清屏
	system("clear");   //清屏  
	//第二步：将aDisplayBoardArray输出到屏幕上
	for(i=0;i<SIZE;i++)
		{
			if(i<=5)
			{
			printf("%d",SIZE-i);
			printf("%s\n",aDisplayBoardArray[i]);
			}
			else
			{
			printf("%d ",SIZE-i);
			printf("%s\n",aDisplayBoardArray[i]);
			}
		}
	//第三步：输出最下面的一行字母A B .... 
	printf("   ");
	for(i=0;i<SIZE;i++)
		printf("%c ",'A'+i);
	printf("\n");
} 


