#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include "statement.h"
#define SIZE 15
#define CHARSIZE 3
#define MAXLEN 1000
/*struct point {
	int x;
	int y;
	int is_quit;
};*/
struct point {
	int x;
	int y;
	int is_quit;
};  
struct loc {
	int i;
	int j;
};

struct SingleInfo {
	int linkNum;
	int oppNum;
};

struct SingleScore {
	struct SingleInfo si[4];
	int score;
};

void ai_set(int n,int i,int j);
struct loc find_max_man(void);
struct loc find_max_ai(void);
void cal_score_ai(void);
int cal_grade_point(int live[],int half[],int dead[]);
void cal_situation_ai(int player);
struct SingleInfo cal0(int s,int t,int player);
struct SingleInfo cal1(int s,int t,int player);
struct SingleInfo cal2(int s,int t,int player);
struct SingleInfo cal3(int s,int t,int player);
void cal_score_man(void);
void cal_situation_man(int player);
void initgrade(void);
void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);
int scan(int i,int j);
int is_win(int i,int j);
struct point ai_play(int i);
int mygetline(char s[], int lim);
struct point man_man(int i);
struct point analyse(char s[]);
int info_illegal(struct point a);
int is_Game_over(struct point a, int i);
struct point man_ai(int first,int i);
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
			a=man_ai(first,1+i%2);
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
//机器下棋，t代表下黑棋（1）还是白棋（2）,返回所下棋的位置。
/*struct point ai_play(int t)
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
	}while(info_illegal(a));
	
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
//分析位置是否合法，1：不合法；2：合法
int info_illegal(struct point a){
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
struct point man_ai(int first,int i){
	struct point a;
	char s[MAXLEN];
	if(first==0){
		if(i==1)
			a=ai_play(i);
		else{
			do{
				printf("Please input the position or \"quit\" to quit:");
				mygetline(s,MAXLEN);
				a=analyse_line(s);
			}while(info_illegal(a));
			aRecordBoard2[15-a.x][a.y-'a']=2;
		}	
	}
	else if(first==1){
		if(i==2)
			a=ai_play(i);
		else{
			do{
				printf("Please input the position or \"quit\" to quit:");
				mygetline(s,MAXLEN);
				a=analyse_line(s);
			}while(info_illegal(a));
			aRecordBoard2[15-a.x][a.y-'a']=1;
		}
	}
	return a;
}

struct SingleScore ai_BoardScore[15][15];
struct SingleScore man_BoardScore[15][15];
//ai下棋函数
struct point ai_play(int t)
{	
	
	initgrade();
	struct point a;
	struct loc loc1,loc2,temp;
	int anti=((t==2)?1:2);
	cal_situation_ai(t);
	cal_situation_man(anti);
	cal_score_ai();
	cal_score_man();
	
	loc1=find_max_man();
	loc2=find_max_ai();
	
	if(ai_BoardScore[loc2.i][loc2.j].score > man_BoardScore[loc1.i][loc1.j].score){
		ai_set(t,loc2.i,loc2.j);
		a.x=loc2.i;
		a.y=loc2.j;
		a.is_quit=-1;
	}	
	else{
		ai_set(t,loc1.i,loc1.j);		
		a.x=loc1.i;
		a.y=loc1.j;
		a.is_quit=-1;
	} 	

	return a;	
}

//下子操作
void ai_set(int n,int i,int j)
{
	if((n==1 || n==2) && i>=0 && i<15 && j>=0 && j<15)
		aRecordBoard2[i][j]=n;
	else
		printf("\n critical error in void ai_set(...) in ai_play.c\n");
}

struct loc find_max_man(void)
{
	struct loc locc={0,0};
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
		{
			if(man_BoardScore[s][t].score>man_BoardScore[locc.i][locc.j].score)
			{
				locc.i=s;locc.j=t;
			}
		}
	return locc;
}

struct loc find_max_ai(void)
{
	struct loc locc={0,0};
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
		{
			if(ai_BoardScore[s][t].score>ai_BoardScore[locc.i][locc.j].score)
			{
				locc.i=s;locc.j=t;
			}
		}
	return locc;
}


void initgrade(void)
{
	int i,j;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			ai_BoardScore[i][j].score=man_BoardScore[i][j].score=0;
}

void cal_score_ai(void)
{
	int live[6];
	int half[6];
	int dead[6];
	int n;
	for(n=0;n<6;n++)
		live[n]=half[n]=dead[n]=0;
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
		{	
			int temp;
			for(n=0;n<4;n++)
			{
				temp=ai_BoardScore[s][t].si[n].linkNum;
				
				if(ai_BoardScore[s][t].si[n].oppNum==0)
					live[temp]++;
				else if(ai_BoardScore[s][t].si[n].oppNum==1)
					half[temp]++;
				else if(ai_BoardScore[s][t].si[n].oppNum==2)
					dead[temp]++;
			}	
			if(aRecordBoard2[s][t]!=0)
				ai_BoardScore[s][t].score=cal_grade_point(live,half,dead);
			else
				ai_BoardScore[s][t].score=-1;		
		}
}


int cal_grade_point(int live[],int half[],int dead[])
{
	if(live[5]>=1 || half[5]>=1 || dead[5]>=1)
		return 1000;
	else if(live[4]>=1)
		return 999;
	else if(live[3]>=1)
		return 998;
	else if(half[4]>=1)
		return 900;
	else if(half[3]>=1)
		return 800;
	else if(live[2]>=1)
		return 700;
	else if(dead[4]>=1 || dead[3]>=1)
		return 600;
	else if(dead[2]>=1)
		return 500;
	else 
		return 400;
}
/*
struct SingleInfo {
	int linkNum;
	int oppNum;
};

struct SingleScore {
	struct SingleInfo[4];
	int score;
};

struct SingleScore ai_BoardScore[15][15];
struct SingleScore man_BoardScore[15][15];

*/

void cal_situation_ai(int player)
{
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
			if(aRecordBoard2[s][t]==0){
				ai_BoardScore[s][t].si[0]=cal0(s,t,player);//横
				ai_BoardScore[s][t].si[1]=cal1(s,t,player);//竖
				ai_BoardScore[s][t].si[2]=cal2(s,t,player);//左下-右上
				ai_BoardScore[s][t].si[3]=cal3(s,t,player);//左上-右下
			}
}

struct SingleInfo cal0(int s,int t,int player)//横着,player depends on whether ai is white or black player
{	
	struct SingleInfo a={0,0};
	int i=1,count=0,anti;
	
	if(player==1)
		anti==2;
	else if(player==2)
		anti==1;
	
	int x=s,y=t;
	y--;
	while(y>=0 && i<=5 && aRecordBoard2[x][y--]==player)
			count++,i++;
			
	if(y>=0){
		if(aRecordBoard2[x][y]==anti)
			a.oppNum++;
	}
	i=1;
	x=s,y=t;
	y++;
	while(y<=14 && i<=5 && aRecordBoard2[x][y++]==player)
			count++,i++;
	
	if(y<=14){
		if(aRecordBoard2[x][y]==anti)
			a.oppNum++;
	}
	
	a.linkNum=count+1;
	return a;
}

struct SingleInfo cal1(int s,int t,int player)//竖着,player depends on whether ai is white or black player
{	
	struct SingleInfo a={0,0};
	int i=1,count=0,anti;
	
	if(player==1)
		anti==2;
	else if(player==2)
		anti==1;
	
	int x=s,y=t;
	x--;	
	while(x>=0 && i<=5 && aRecordBoard2[x--][y]==player)
			count++,i++;
			
	if(x>=0){
		if(aRecordBoard2[x][y]==anti)
			a.oppNum++;
	}
	i=1;
	x=s,y=t;
	x++;
	while(x<=14 && i<=5 && aRecordBoard2[x++][y]==player)
			count++,i++;
	
	if(x<=14){
		if(aRecordBoard2[x][y]==anti)
			a.oppNum++;
	}
	
	a.linkNum=count+1;
	return a;
}

struct SingleInfo cal2(int s,int t,int player)//左下-右上,player depends on whether ai is white or black player
{	
	struct SingleInfo a={0,0};
	int i=1,count=0,anti;
	
	if(player==1)
		anti==2;
	else if(player==2)
		anti==1;
	
	int x=s,y=t;
	x++,y--;	
	while(y>=0 && x<=14 && i<=5 && aRecordBoard2[x++][y--]==player)
			count++,i++;
			
	if(y>=0 && x<=14){
		if(aRecordBoard2[x][y]==anti)
			a.oppNum++;
	}
	i=1;
	x=s,y=t;
	x--,y++;
	while(y<=14 && x>=0 && i<=5 && aRecordBoard2[x--][y++]==player)
			count++,i++;
	
	if(y<=14 && x>=0){
		if(aRecordBoard2[x][y]==anti)
			a.oppNum++;
	}
	
	a.linkNum=count;
	return a;
}

struct SingleInfo cal3(int s,int t,int player)//左上-右下,player depends on whether ai is white or black player
{	
	struct SingleInfo a={0,0};
	int i=1,count=0,anti;
	
	if(player==1)
		anti==2;
	else if(player==2)
		anti==1;
	int x=s,y=t;
	x--,y--;
	while(y>=0 && x>=0 && i<=5 && aRecordBoard2[x--][y--]==player)
			count++,i++;
			
	if(y>=0 && x>=0){
		if(aRecordBoard2[x][y]==anti)
			a.oppNum++;
	}
	i=1;
	x=s,y=t;
	x++,y++;
	while(y<=14 && x<=14 && i<=5 && aRecordBoard2[x++][y++]==player)
			count++,i++;
	
	if(y<=14 && x<=14){
		if(aRecordBoard2[x][y]==anti)
			a.oppNum++;
	}
	
	a.linkNum=count;
	return a;
}

void cal_score_man(void)
{
	int live[6];
	int half[6];
	int dead[6];
	int n;
	for(n=0;n<6;n++)
		live[n]=half[n]=dead[n]=0;
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
		{	
			int temp;
			for(n=0;n<4;n++)
			{
				temp=man_BoardScore[s][t].si[n].linkNum;
				
				if(man_BoardScore[s][t].si[n].oppNum==0)
					live[temp]++;
				else if(man_BoardScore[s][t].si[n].oppNum==1)
					half[temp]++;
				else if(man_BoardScore[s][t].si[n].oppNum==2)
					dead[temp]++;
			}	
			if(aRecordBoard2[s][t]!=0)
				man_BoardScore[s][t].score=cal_grade_point(live,half,dead);
			else
				man_BoardScore[s][t].score=-1;
		}
}

void cal_situation_man(int player)
{
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
			if(aRecordBoard2[s][t]==0){
				man_BoardScore[s][t].si[0]=cal0(s,t,player);//横
				man_BoardScore[s][t].si[1]=cal1(s,t,player);//竖
				man_BoardScore[s][t].si[2]=cal2(s,t,player);//左下-右上
				man_BoardScore[s][t].si[3]=cal3(s,t,player);//左上-右下
			}
}


