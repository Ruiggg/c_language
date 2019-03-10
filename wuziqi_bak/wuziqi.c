#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 15
#define CHARSIZE 3
#define MAXLEN 1000
#define FIRST 1
void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);
int scan(int i,int j);
int is_win(int i,int j);

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
    int a,c,i=FIRST;
    char b;
    char s[MAXLEN];
    printf("input \"quit\" to quit the game, others to continue:");
    scanf("%s",s);
    while(strcmp(s,"quit")!=0)
    {
     	printf("input a integer and a char:");
   	
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
    		c=scanf("%d %c",&a,&b);
    		if(c!=2)
    		{
    			printf("error:please input a integer and a char:");
    			while(getchar()!='\n')
    			;
    			continue;
    		}
    		else if(a<1||a>15||b<'a'||b>'o')
    		{
    			printf("a should be 1~15;b should be \'a\'to \'o\'\n");
    			printf("input a integer and a char:");
    			continue;
    		}
    		else if(aRecordBoard2[15-a][b-'a']!=0)
    		{
    			printf("There is already taken! Try again!\n");
    			printf("input a integer and a char:");
    			continue;
    		}
    		else
    		{
    			break;
    		}
    	}
    	
    	
    	if(i%2==1)
    		aRecordBoard2[15-a][b-'a']=1;
    	else
    		aRecordBoard2[15-a][b-'a']=2;
    	recordtoDisplayArray();
    	displayBoard();
    	
    	//判断输赢
    	if(is_win(15-a,b-'a')==1)
    	{	
    		printf("the black has won!\n");
    		break;
    	}
    	else if(is_win(15-a,b-'a')==2)
    	{
    		printf("the white has won!\n");
    		break;
    	}
    	else
    	{	
    		if(i==225+FIRST)
    		{	
    			printf("The game has drawn!\n");
    			break;
		}    	
    	}
    	
    	i++;//i chuxian bianhua
    	
    	printf("input \"quit\" to quit the game, others to continue:");
    	scanf("%s",s);
   
    }// while xun huan jie shu
    
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

int is_win(int i,int j)
{
			if(aRecordBoard2[i][j]==1)
			{
				if(scan(i,j)==1)
					return 1;
			}
			else if(aRecordBoard2[i][j]==2)
			{
				if(scan(i,j)==2)
					return 2;
			}
	return 0;
}

int scan(int i,int j)
{
	int count,x,y;
	count=0;
	if(aRecordBoard2[i][j]==1)
	{	//竖着向上搜索
		for(x=i-1,y=j;x>=i-4 && x>=0 && count<=4;x--)
			if(aRecordBoard2[x][y]==1)
				count++;
		if(count==4)
			return 1;
		else
			count=0;
		//竖着向下搜索
		for(x=i+1,y=j;x<=i+4 && x<=14 && count<=4;x++)
			if(aRecordBoard2[x][y]==1)
				count++;
		if(count==4)
			return 1;
		else
			count=0;
		//横着向左搜索	
		for(x=i,y=j-1;y>=j-4 && y>=0 && count<=4;y--)
			if(aRecordBoard2[x][y]==1)
				count++;
		if(count==4)
			return 1;
		else
			count=0;
		//横着向右搜索
		for(x=i,y=j+1;y<=j+4 && y<=14 && count<=4;y++)
			if(aRecordBoard2[x][y]==1)
				count++;
		if(count==4)
			return 1;
		else
			count=0;
		//左上搜索
		for(x=i-1,y=j-1;x>=i-4 && y>=j-4 && x>=0 && y>=0 && count<=4;x--,y--)
			if(aRecordBoard2[x][y]==1)
				count++;
		if(count==4)
			return 1;
		else
			count=0;	
		//右下搜索
		for(x=i+1,y=j+1;x<=i+4 && y<=j+4 && x<=14 && y<=14 && count<=4;x++,y++)
			if(aRecordBoard2[x][y]==1)
				count++;
		if(count==4)
			return 1;
		else
			count=0;
		//左下搜索
		for(x=i+1,y=j-1;x<=i+4 && y>=j-4 && x<=14 && y>=0 && count<=4;x++,y--)
			if(aRecordBoard2[x][y]==1)
				count++;
		if(count==4)
			return 1;
		else
			count=0;
		//右上搜索
		for(x=i-1,y=j+1;x>=i-4 && y<=j+4 && x>=0 && y<=14 && count<=4;x--,y++)
			if(aRecordBoard2[x][y]==1)
				count++;
		if(count==4)
			return 1;
		else
			count=0;
	}	
	else if(aRecordBoard2[i][j]==2)
	{
		//竖着向上搜索
		for(x=i-1,y=j;x>=i-4 && x>=0 && count<=4;x--)
			if(aRecordBoard2[x][y]==2)
				count++;
		if(count==4)
			return 2;
		else
			count=0;
		//竖着向下搜索
		for(x=i+1,y=j;x<=i+4 && x<=14 && count<=4;x++)
			if(aRecordBoard2[x][y]==2)
				count++;
		if(count==4)
			return 2;
		else
			count=0;
		//横着向左搜索	
		for(x=i,y=j-1;y>=j-4 && y>=0 && count<=4;y--)
			if(aRecordBoard2[x][y]==2)
				count++;
		if(count==4)
			return 2;
		else
			count=0;
		//横着向右搜索
		for(x=i,y=j+1;y<=j+4 && y<=14 && count<=4;y++)
			if(aRecordBoard2[x][y]==2)
				count++;
		if(count==4)
			return 2;
		else
			count=0;
		//左上搜索
		for(x=i-1,y=j-1;x>=i-4 && y>=j-4 && x>=0 && y>=0 && count<=4;x--,y--)
			if(aRecordBoard2[x][y]==2)
				count++;
		if(count==4)
			return 2;
		else
			count=0;	
		//右下搜索
		for(x=i+1,y=j+1;x<=i+4 && y<=j+4 && x<=14 && y<=14 && count<=4;x++,y++)
			if(aRecordBoard2[x][y]==2)
				count++;
		if(count==4)
			return 2;
		else
			count=0;
		//左下搜索
		for(x=i+1,y=j-1;x<=i+4 && y>=j-4 && x<=14 && y>=0 && count<=4;x++,y--)
			if(aRecordBoard2[x][y]==2)
				count++;
		if(count==4)
			return 2;
		else
			count=0;
		//右上搜索
		for(x=i-1,y=j+1;x>=i-4 && y<=j+4 && x>=0 && y<=14 && count<=4;x--,y++)
			if(aRecordBoard2[x][y]==2)
				count++;
		if(count==4)
			return 2;
		else
			count=0;
	}
	else
		return 0;
}





