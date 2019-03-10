#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "statement.h"
#define SIZE 15
#define CHARSIZE 3
#define MAXLEN 1000
/*struct point {
	int x;
	int y;
	int is_quit;
};*/
void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);
int scan(int i,int j);
int is_win(int i,int j);
struct point ai_play(int i,int first,int step);
int mygetline(char s[], int lim);
struct point man_man(int i);
struct point analyse(char s[]);
int info_illegal(struct point a,int i);
int is_Game_over(struct point a, int i);
struct point man_ai(int first,int i,int step);
struct point analyse_line(char s[]);
//棋盘使用的是GBK编码，每一个中文字符占用2个字节。
//然而实际上用UTF，每一个中文字符占3个字节

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
extern struct SingleScore ai_BoardScore[15][15];
extern struct SingleScore man_BoardScore[15][15];

int main(int argc,char *argv[])
{	
	int c,player=0,first=1;
	//处理命令行参数
	while(--argc>0 && (*++argv)[0]=='-')
		while(c=*(++argv[0]))
			switch(c)
			{
				case 'h':player=1;break;//人人对战
				case 'm':player=0;break;//人机对战，默认状态
				case 'f':first=0;break;//机器先走，默认状态是人先走
				default:
				printf("find:illegal operator %c\n",c);
				argc=0;
				return 0;	
			}
	initgrade(ai_BoardScore,man_BoardScore);				
	initRecordBorard();//初始化
	
	struct point a;
	int is_quit,i=0;
	do{	
		recordtoDisplayArray();//映射到要显示的棋盘
		displayBoard();//打印棋盘
		if(i>0)
			printf("The last step:%d %c\n",a.x,a.y);
		if(player==1){
			a=man_man(1+i%2);
			i++;
		}	
		else{
			a=man_ai(first,1+i%2,i);
			i++;
		}	
	}while(!is_Game_over(a,i));
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
	printf("(By Guo Hongrui)\n");
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
		for(x=i-1,y=j;x>=i-4 && x>=0 && count<=4 && aRecordBoard2[x][y]==1;x--)
				count++;
		if(count==4)
			return 1;
		else
		{
		//竖着向下搜索
		for(x=i+1,y=j;x<=i+4 && x<=14 && count<=4 && aRecordBoard2[x][y]==1;x++)
				count++;
		if(count==4)
			return 1;
		else
			count=0;
		}
		//横着向左搜索	
		for(x=i,y=j-1;y>=j-4 && y>=0 && count<=4 && aRecordBoard2[x][y]==1;y--)
				count++;
		if(count==4)
			return 1;
		else
		{
		//横着向右搜索
		for(x=i,y=j+1;y<=j+4 && y<=14 && count<=4 && aRecordBoard2[x][y]==1;y++)
				count++;
		if(count==4)
			return 1;
		else
			count=0;
		}
		//左上搜索
		for(x=i-1,y=j-1;x>=i-4 && y>=j-4 && x>=0 && y>=0 && count<=4 && aRecordBoard2[x][y]==1;x--,y--)
				count++;
		if(count==4)
			return 1;
		else
		{	
		//右下搜索
		for(x=i+1,y=j+1;x<=i+4 && y<=j+4 && x<=14 && y<=14 && count<=4 && aRecordBoard2[x][y]==1;x++,y++)
				count++;
		if(count==4)
			return 1;
		else
			count=0;
		}
		//左下搜索
		for(x=i+1,y=j-1;x<=i+4 && y>=j-4 && x<=14 && y>=0 && count<=4 && aRecordBoard2[x][y]==1;x++,y--)
				count++;
		if(count==4)
			return 1;
		else
		{
		//右上搜索
		for(x=i-1,y=j+1;x>=i-4 && y<=j+4 && x>=0 && y<=14 && count<=4 && aRecordBoard2[x][y]==1;x--,y++)
				count++;
		if(count==4)
			return 1;
		}
		
		return 0;
	}	
	else if(aRecordBoard2[i][j]==2)
	{
		//竖着向上搜索
		for(x=i-1,y=j;x>=i-4 && x>=0 && count<=4 && aRecordBoard2[x][y]==2;x--)
				count++;
		if(count==4)
			return 2;
		else
		{
		//竖着向下搜索
		for(x=i+1,y=j;x<=i+4 && x<=14 && count<=4 && aRecordBoard2[x][y]==2;x++)
				count++;
		if(count==4)
			return 2;
		else
			count=0;
		}
		//横着向左搜索	
		for(x=i,y=j-1;y>=j-4 && y>=0 && count<=4 && aRecordBoard2[x][y]==2;y--)
				count++;
		if(count==4)
			return 2;
		else
		{
		//横着向右搜索
		for(x=i,y=j+1;y<=j+4 && y<=14 && count<=4 && aRecordBoard2[x][y]==2;y++)
				count++;
		if(count==4)
			return 2;
		else
			count=0;
		}
		//左上搜索
		for(x=i-1,y=j-1;x>=i-4 && y>=j-4 && x>=0 && y>=0 && count<=4 && aRecordBoard2[x][y]==2;x--,y--)
				count++;
		if(count==4)
			return 2;
		else
		{	
		//右下搜索
		for(x=i+1,y=j+1;x<=i+4 && y<=j+4 && x<=14 && y<=14 && count<=4 && aRecordBoard2[x][y]==2;x++,y++)
				count++;
		if(count==4)
			return 2;
		else
			count=0;
		}
		//左下搜索
		for(x=i+1,y=j-1;x<=i+4 && y>=j-4 && x<=14 && y>=0 && count<=4 && aRecordBoard2[x][y]==2;x++,y--)
				count++;
		if(count==4)
			return 2;
		else
		{
		//右上搜索
		for(x=i-1,y=j+1;x>=i-4 && y<=j+4 && x>=0 && y<=14 && count<=4 && aRecordBoard2[x][y]==2;x--,y++)
				count++;
		if(count==4)
			return 2;
		else
			count=0;
		}
		
		return 0;
	}
	else
		return 0;
}

int mygetline(char s[],int lim)
{
	int c,i;
	i=0;
	while(--lim>0 && (c=getchar())!=EOF && c!='\n')
		s[i++]=c;
	if(c=='\n')
		s[i++]=c;
	s[i]='\0';
	return i;
}
/*
//机器下棋，t代表下黑棋（1）还是白棋（2）,返回所下棋的位置。
struct point ai_play(int t,int first)
{	
	struct point a;
	int i,j;
		for(i=0;i<SIZE;i++)
			for(j=0;j<SIZE;j++)
				if(aRecordBoard2[i][j]==0)
				{	
					aRecordBoard2[i][j]=t;
					a.x=15-i;
					a.y=j+'a';
					a.is_quit==-1;
					return a;
				}		
}*/
//人人对战代码，i代表下黑棋（1）还是白棋（2）,返回所下棋的位置。
struct point man_man(int i){
	struct point a;
	char s[MAXLEN];
	do{
		printf("Please input the position or \"quit\" to quit:");
		mygetline(s,MAXLEN);
		a=analyse_line(s);
	}while(info_illegal(a,i));
	
	aRecordBoard2[15-a.x][a.y-'a']=i;
	return a;
}
//分析读入的字符串，返回所下棋的位置
struct point analyse_line(char s[]){//不合法的返回-1
	struct point a;
	char letter[3][10]={"","",""};
	int n,j,i=0;
	a.x=a.y=a.is_quit=-1;//初始化a
	//读前三个单词
	for(n=0;n<3;n++){
		j=0;
		//跳过空格：
		while(s[i]=='\t' || s[i]==' ')
			i++;
		//读取单词
		while(s[i]!='\0' && s[i]!='\n' && s[i]!='\t' && s[i]!=' ' && j<=8)
			letter[n][j++]=s[i++];
		letter[n][j]='\0';
	}
	//分析单词
	for(n=0;n<3;n++){
		if(strlen(letter[n])==1){
			if(isdigit(letter[n][0]))
				a.x=letter[n][0]-'0';
			else if(isalpha(letter[n][0]))
				a.y=tolower(letter[n][0]);
		}
		else if(strlen(letter[n])==2){
			if(isdigit(letter[n][0])){
				a.x=letter[n][0]-'0';
				if(isalpha(letter[n][1]))
					a.y=tolower(letter[n][1]);
				else if(isdigit(letter[n][1]))
					a.x=10*a.x+letter[n][1]-'0';
			}
			else if(isalpha(letter[n][0])){
				a.y=tolower(letter[n][0]);
				if(isdigit(letter[n][1]))
					a.x=letter[n][1]-'0';
			}
		}
		else if(strlen(letter[n])==3){
			if(isdigit(letter[n][0])){
				a.x=letter[n][0]-'0';
				if(isalpha(letter[n][1]))
					a.y=tolower(letter[n][1]);
				else if(isdigit(letter[n][1])){
					a.x=10*a.x+letter[n][1]-'0';
					if(isalpha(letter[n][2]))
						a.y=tolower(letter[n][2]);
				}	
			}
			else if(isalpha(letter[n][0])){
				a.y=tolower(letter[n][0]);
				if(isdigit(letter[n][1])){
					a.x=letter[n][1]-'0';
					if(isdigit(letter[n][2])){
						a.x=10*a.x+letter[n][2]-'0';
					}
				}
			}
		}
		else if(strcmp(letter[n],"quit")==0){
			a.is_quit=1;
		}
	}
	return a;
}
//分析位置是否合法，1：不合法；2：合法.i代表要下的棋子1：黑 2：白
int info_illegal(struct point a,int i){
	if(a.is_quit!=1){
		if(a.x==-1 || a.y==-1){
			printf("error:invalid position\n");
			return 1;
		}	
		else if(a.x<1 || a.x>15 || a.y<'a' || a.y>'z'){
			printf("error:x should 1~15; y should be a~z or A~Z\n");
			return 1;
		}
		else if(aRecordBoard2[15-a.x][a.y-'a']!=0){
			printf("error:the place has been taken\n");
			return 1;
		}
		else if(i==1){
			cal_situation(i,aRecordBoard2,man_BoardScore);

			if(is_ban(15-a.x,a.y-'a',i,aRecordBoard2,man_BoardScore)){
				printf("error: the place has been banned\n");
				return 1;
			}
		}
		else
			return 0;
	}	
	return 0;
}

//判断是否结束，输入所下棋的位置与总下棋数，输出1：结束，0：不结束
int is_Game_over(struct point a, int i){
	if(a.is_quit==1)
		return 1;
	else{
		//判断输赢
    		if(is_win(15-a.x,a.y-'a')==1)
    		{	
    			recordtoDisplayArray();//映射到要显示的棋盘
			displayBoard();//打印棋盘
    			printf("the black has won!\n");
    			return 1;
    		}
    		else if(is_win(15-a.x,a.y-'a')==2)
    		{	
    			recordtoDisplayArray();//映射到要显示的棋盘
			displayBoard();//打印棋盘
    			printf("the white has won!\n");
    			return 1;
    		}
    		else if(i==225)
    		{	
    			recordtoDisplayArray();//映射到要显示的棋盘
			displayBoard();//打印棋盘
    		 	printf("the game has drawn!\n");
    		 	return 1;   				
    		}   
	}
	return 0;
	
}
//人机对战，输入first(=0：机器先走；1：人先走)，i代表下黑棋（1）还是白棋（2）,返回所下棋的位置。
struct point man_ai(int first,int i,int step){
	struct point a;
	char s[MAXLEN];
	if(first==0){
		if(i==1){
			if(step==0){
				aRecordBoard2[7][7]=1;
				a.x=8;
				a.y='h';			
			}else{
				a=ai_play(i,first,step);
			}
		}else{
			do{
				printf("Please input the position or \"quit\" to quit:");
				mygetline(s,MAXLEN);
				a=analyse_line(s);
			}while(info_illegal(a,i));
			aRecordBoard2[15-a.x][a.y-'a']=2;
		}	
	}
	else if(first==1){
		if(i==2)
			a=ai_play(i,first,step);
		else{
			do{
				printf("Please input the position or \"quit\" to quit:");
				mygetline(s,MAXLEN);
				a=analyse_line(s);
			}while(info_illegal(a,i));
			aRecordBoard2[15-a.x][a.y-'a']=1;
		}
	}
	return a;
}


