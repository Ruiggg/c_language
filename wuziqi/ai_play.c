#include "statement.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
//#define NUM 10 //候选点个数
#define DEPTH 2//层数+1
extern int aRecordBoard2[SIZE][SIZE];
extern i;
struct SingleScore ai_BoardScore[15][15];
struct SingleScore man_BoardScore[15][15];
//ai下棋函数
struct point ai_play(int t,int first,int step)
{	
	
	initgrade(ai_BoardScore,man_BoardScore);
	struct point a;
	struct loc loc1,loc2,temp;
	
	int anti;
	if(t==1)
		anti=2;
	else
		anti=1;
	int hhh=DEPTH;
	if(step<=3)
		loc1=MaxMin(first,t,1,ai_BoardScore,man_BoardScore,aRecordBoard2);//前2步不要算那么久
	else
		loc1=MaxMin(first,t,hhh,ai_BoardScore,man_BoardScore,aRecordBoard2);
	ai_set(t,loc1.i,loc1.j);		
	a.x=15-loc1.i;
	a.y=loc1.j+'a';
	a.is_quit=-1;
	return a;	
}

//下子操作
void ai_set(int n,int i,int j)
{
	if((n==1 || n==2) && i>=0 && i<15 && j>=0 && j<15 && aRecordBoard2[i][j]==0)
		aRecordBoard2[i][j]=n;
	else
		printf("\n critical error in void ai_set(...) in ai_play.c\n");
}
struct loc find_max(struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15]){
	struct loc locc={0,0};
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
		{
			if(ai_BoardScore[s][t].score+man_BoardScore[s][t].score > ai_BoardScore[locc.i][locc.j].score+man_BoardScore[locc.i][locc.j].score)
			{
				locc.i=s;locc.j=t;
			}
		}
	return locc;
}

void initgrade(struct SingleScore player_BoardScore[15][15],struct SingleScore anti_BoardScore[15][15])
{
	int i,j,n;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++){
			player_BoardScore[i][j].score=anti_BoardScore[i][j].score=0;
			for(n=0;n<4;n++){
				player_BoardScore[i][j].si[n].linkNum=anti_BoardScore[i][j].si[n].linkNum=0;
				player_BoardScore[i][j].si[n].oppNum=anti_BoardScore[i][j].si[n].oppNum=0;	
			}
		}
}

void cal_score(int player,int first,struct SingleScore BoardScore[15][15])//first已经不用了，以后再删吧
{
	int live[7];
	int half[7];
	int dead[7];
	int n;
	for(n=0;n<7;n++)
		live[n]=half[n]=dead[n]=0;
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
		{	
			int temp;
			for(n=0;n<4;n++)
			{
				temp=BoardScore[s][t].si[n].linkNum;
				
				if(BoardScore[s][t].si[n].oppNum==0)
					live[temp]++;
				else if(BoardScore[s][t].si[n].oppNum==1)
					half[temp]++;
				else if(BoardScore[s][t].si[n].oppNum==2)
					dead[temp]++;
				else if(BoardScore[s][t].si[n].oppNum==3)
					half[temp]+=2;
			}	
			
			BoardScore[s][t].score=cal_grade_point(live,half,dead);
			for(n=0;n<7;n++)
				live[n]=half[n]=dead[n]=0;	//重新归0，下次再用
		}
}


int cal_grade_point(int live[],int half[],int dead[])
{
	if(live[5]>=1 || half[5]>=1 || dead[5]>=1)
		return 100000;
	else if(live[4]>=1 || half[4]>=2)
		return 49999;
	else if(live[3]>=2)
		return 49999;
	else if(live[3]>=1 && half[4]>=1)
		return 49999;
	else if(live[3]>=1)
		return 2499+live[2]*600+half[2]*300;
	else if(half[4]>=1)
		return 2499+live[2]*600+half[2]*300;
	else if(half[3]>=1)
		return 600*half[3]+2*live[2]+half[2];
	else if(live[2]>=1)
		return 600*live[2]+2*half[3]+half[2];
	else if(half[2]>=1)
		return 300;
	else if(dead[4]>=1 || dead[3]>=1)
		return 4;
	else 
		return 3;
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

void cal_situation(int player,int Board[15][15],struct SingleScore BoardScore[15][15])
{
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
			if(Board[s][t]==0){//只扫描空位置
				BoardScore[s][t].si[0]=cal0(s,t,player,Board);//横
				BoardScore[s][t].si[1]=cal1(s,t,player,Board);//竖
				BoardScore[s][t].si[2]=cal2(s,t,player,Board);//左下-右上
				BoardScore[s][t].si[3]=cal3(s,t,player,Board);//左上-右下
			}
}
//参数：记录连珠信息的棋盘（ai_Bo...:player方的棋盘，man_Bo...对方的棋盘），现在的棋盘，执子的颜色，如果这个子被禁或者被占，那么把分数修改为-1，传入的player是“我”方的棋子代号
void change_score(struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15],int Board[15][15],int player)
{
	int anti;
	if(player==1)
		anti=2;
	else
		anti=1;
		
	if(player==1){//如果是黑子，说明是先手，那就按照禁手标准判断
		int x,y;
		for(x=0;x<SIZE;x++)
			for(y=0;y<SIZE;y++){
				if(is_ban(x,y,player,Board,ai_BoardScore) || Board[x][y]!=0)
					ai_BoardScore[x][y].score=man_BoardScore[x][y].score=-1;//由于判断得分是按照两者的和来判断的，所以需要都变成-1，下同
			}
	}else if(player==2){//如果是白子，那就说明是后手，就只看有没有被占即可
		int x,y;
		for(x=0;x<SIZE;x++)
			for(y=0;y<SIZE;y++){
				if(is_ban(x,y,anti,Board,man_BoardScore))
					man_BoardScore[x][y].score=3;//则不考虑对手在这一点的得分
				if(Board[x][y]!=0)
					ai_BoardScore[x][y].score=man_BoardScore[x][y].score=-1;
			}	
	}
}



struct SingleInfo cal0(int s,int t,int player,int Board[15][15])//横着,player depends on whether ai is white or black player
{	
	struct SingleInfo a={0,0};
	int i=1,count=0,anti;
	struct loc l;
	l.i=s,l.j=t;
	if(player==1)
		anti=2;
	else if(player==2)
		anti=1;
	
	int m;
	if((m=is_five0(l,l,player,Board))==2){
		a.linkNum=6;
		a.oppNum=0;//长连将被禁掉，所以这个值没有意义
	}
	else if(m==1){
		a.linkNum=5;
		a.oppNum=0;//如果能成5，活不活同样重要，这个值不参考
	}
	else if((m=which_four0(l,l,player,Board))==3){
		a.linkNum=4;
		a.oppNum=3;//双冲四
	}
	else if(m==2){
		a.linkNum=4;
		a.oppNum=0;//活四
	}
	else if(m==1){
		a.linkNum=4;
		a.oppNum=1;//半活四
	}
	else if((m=which_three0(l,l,player,Board))==2){
		a.linkNum=3;
		a.oppNum=0;
	}
	else if(m==1){
		a.linkNum=3;
		a.oppNum=1;
	}else if((m=which_two0(l,l,player,Board))==2){
		a.linkNum=2;
		a.oppNum=0;
	}
	else if(m==1){
		a.linkNum=2;	
		a.oppNum=1;
	}
	else{
		int x=s,y=t;
		y--;
		while(y>=0 && i<=5 && Board[x][y]==player)
			{count++,i++,y--;}
			
		if(y>=0){
			if(Board[x][y]==anti)
				a.oppNum++;
		}else{
			a.oppNum++;
		}
	
		i=1;
		x=s,y=t;
		y++;
		while(y<=14 && i<=5 && Board[x][y]==player)
			{count++,i++,y++;}
	
		if(y<=14){
			if(Board[x][y]==anti)
				a.oppNum++;
		}else{
			a.oppNum++;
		}
		a.linkNum=count+1;
	}
	return a;
}

struct SingleInfo cal1(int s,int t,int player,int Board[15][15])//竖着,player depends on whether ai is white or black player
{	
	struct SingleInfo a={0,0};
	int i=1,count=0,anti;
	struct loc l;
	l.i=s,l.j=t;
	if(player==1)
		anti=2;
	else if(player==2)
		anti=1;
	
	
	int m;
	if((m=is_five1(l,l,player,Board))==2){
		a.linkNum=6;
		a.oppNum=0;//长连将被禁掉，所以这个值没有意义
	}
	else if(m==1){
		a.linkNum=5;
		a.oppNum=0;//如果能成5，活不活同样重要，这个值不参考
	}
	else if((m=which_four1(l,l,player,Board))==3){
		a.linkNum=4;
		a.oppNum=3;//双冲4
	}
	else if(m==2){
		a.linkNum=4;
		a.oppNum=0;//活4
	}
	else if(m==1){
		a.linkNum=4;
		a.oppNum=1;//半活四
	}
	else if((m=which_three1(l,l,player,Board))==2){
		a.linkNum=3;
		a.oppNum=0;
	}
	else if(m==1){
		a.linkNum=3;
		a.oppNum=1;
	}
	else if((m=which_two1(l,l,player,Board))==2){
		a.linkNum=2;
		a.oppNum=0;
	}
	else if(m==1){
		a.linkNum=2;	
		a.oppNum=1;
	}else{
		int x=s,y=t;
		x--;	
		while(x>=0 && i<=5 && Board[x][y]==player && count<=4)
			{count++,i++,x--;}
			
		if(x>=0){
			if(Board[x][y]==anti)
				a.oppNum++;
		}else{
			a.oppNum++;
		}
		i=1;
		x=s,y=t;
		x++;
		while(x<=14 && i<=5 && Board[x][y]==player && count<=4)
			{count++,i++,x++;}
	
		if(x<=14){
			if(Board[x][y]==anti)
				a.oppNum++;
		}else{
			a.oppNum++;
		}
	
		a.linkNum=count+1;
	}
	return a;
}

struct SingleInfo cal2(int s,int t,int player,int Board[15][15])//左上-右下,player depends on whether ai is white or black player
{	
	struct SingleInfo a={0,0};
	int i=1,count=0,anti;
	struct loc l;
	l.i=s,l.j=t;
	if(player==1)
		anti=2;
	else if(player==2)
		anti=1;
	
	int m;
	if((m=is_five2(l,l,player,Board))==2){
		a.linkNum=6;
		a.oppNum=0;//长连将被禁掉，所以这个值没有意义
	}
	else if(m==1){
		a.linkNum=5;
		a.oppNum=0;//如果能成5，活不活同样重要，这个值不参考
	}
	else if((m=which_four2(l,l,player,Board))==3){
		a.linkNum=4;
		a.oppNum=3;//双冲4
	}
	else if(m==2){
		a.linkNum=4;
		a.oppNum=0;//活4
	}
	else if(m==1){
		a.linkNum=4;
		a.oppNum=1;//半活四
	}
	else if((m=which_three2(l,l,player,Board))==2){
		a.linkNum=3;
		a.oppNum=0;
	}
	else if(m==1){
		a.linkNum=3;
		a.oppNum=1;
	}else if((m=which_two2(l,l,player,Board))==2){
		a.linkNum=2;
		a.oppNum=0;
	}
	else if(m==1){
		a.linkNum=2;	
		a.oppNum=1;
	}
	else{
		int x=s,y=t;
		x--,y--;
		while(y>=0 && x>=0 && i<=5 && Board[x][y]==player && count<=4){
			count++,i++,x--,y--;}
			
		if(y>=0 && x>=0){
			if(Board[x][y]==anti)
				a.oppNum++;
		}else{
			a.oppNum++;
		}
		i=1;
		x=s,y=t;
		x++,y++;
		while(y<=14 && x<=14 && i<=5 && Board[x][y]==player && count<=4){
			count++,i++,x++,y++;}
	
		if(y<=14 && x<=14){
			if(Board[x][y]==anti)
				a.oppNum++;
		}else{
			a.oppNum++;
		}
		a.linkNum=count+1;
		}
	return a;
}

struct SingleInfo cal3(int s,int t,int player,int Board[15][15])//左下-右上,player depends on whether ai is white or black player
{	
	struct SingleInfo a={0,0};
	int i=1,count=0,anti;
	struct loc l;
	l.i=s,l.j=t;
	if(player==1)
		anti=2;
	else if(player==2)
		anti=1;
	int m;
	if((m=is_five3(l,l,player,Board))==2){
		a.linkNum=6;
		a.oppNum=0;//长连将被禁掉，所以这个值没有意义
	}
	else if(m==1){
		a.linkNum=5;
		a.oppNum=0;//如果能成5，活不活同样重要，这个值不参考
	}
	else if((m=which_four3(l,l,player,Board))==3){
		a.linkNum=4;
		a.oppNum=3;//双冲4
	}
	else if(m==2){
		a.linkNum=4;
		a.oppNum=0;//活4
	}
	else if(m==1){
		a.linkNum=4;
		a.oppNum=1;//半活四
	}
	else if((m=which_three3(l,l,player,Board))==2){
		a.linkNum=3;
		a.oppNum=0;
	}
	else if(m==1){
		a.linkNum=3;
		a.oppNum=1;
	}else if((m=which_two3(l,l,player,Board))==2){
		a.linkNum=2;
		a.oppNum=0;
	}else if(m==1){
		a.linkNum=2;	
		a.oppNum=1;
	}else{
		int x=s,y=t;
		x++,y--;	
		while(y>=0 && x<=14 && i<=5 && Board[x][y]==player && count<=4)
			{count++,i++,x++,y--;}
			
		if(y>=0 && x<=14){
			if(Board[x][y]==anti)
				a.oppNum++;
		}else{
			a.oppNum++;
		}
		i=1;
		x=s,y=t;
		x--,y++;
		while(y<=14 && x>=0 && i<=5 && Board[x][y]==player && count<=4)
			{count++,i++,x--,y++;}
	
		if(y<=14 && x>=0){
			if(Board[x][y]==anti)
				a.oppNum++;
		}else{
			a.oppNum++;
		}
		a.linkNum=count+1;
	}
	return a;
}


int is_five0(struct loc a,struct loc b,int player,int Board[15][15])//a:point waiting to be judged b:point should be included in live5 etc.. if any
{	
	int s=a.i,t=a.j;
	int n,k;
	int temp[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int sign=0,count=0,y=t-1;
	if(a.i==b.i && a.j==b.j)
		sign++;
	while(y>=0 && temp[s][y]==player){
		if(s==b.i && y==b.j)
		sign++;	
		count++,y--;
	}	
	y=t+1;
	while(y<=14 && temp[s][y]==player){
		if(s==b.i && y==b.j)
		sign++;
		count++,y++;
	}
	if(count==4 && sign>0)
		return 1;
	if(count>4 && sign>0)
		return 2;
	else
		return 0;

}

//return:0-no 4; 1-half 4; 2-live 4 ;判断如果下了这个子，会不会成活四，冲四，或其他
int which_four0(struct loc a,struct loc b,int player,int Board[15][15])
{
	int s=a.i,t=a.j;
	int i=1,count=0;//count 记录能成5的点的个数
	int temp[15][15];
	int n,k,x,y;
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int count_lk=1;//为了区分活四和双冲四，需要看连起来的棋子个数
	x=s,y=t-1;
	while(y>=0 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,y--;}
	i=1;
	x=s,y=t+1;
	while(y<=14 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,y++;}
	struct loc c;
	for(y=t-1;y>=t-4 && y>=0;y--){
		c.i=s,c.j=y;
		if(temp[s][y]==0 && is_five0(c,b,player,temp)>=1)
			count++;
	}
	for(y=t+1;y<=t+4 && y<=14;y++){
		c.i=s,c.j=y;
		if(temp[s][y]==0 && is_five0(c,b,player,temp)>=1)
			count++;
	}
	if(count>=2 && count_lk<4)
		return 3;
	else if(count>=2)
		return 2;
	else if(count==1)
		return 1;
	else
		return 0;		
}

//return : 2-live 3; 1-half 3; 0-o.w.
int which_three0(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;	
	
	int x=s,y;
	struct loc c;
	for(y=t-1;y>=t-3 && y>=0;y--){
		c.i=s,c.j=y;
		if(temp[x][y]==0 && which_four0(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four0(c,b,player,temp)==1)
			count1++;	
	}
	for(y=t+1;y<=t+3 && y<=14;y++){
		c.i=s,c.j=y;
		if(temp[x][y]==0 && which_four0(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four0(c,b,player,temp)==1)
			count1++;
	}
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}

int which_two0(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;	
	
	int x=s,y;
	struct loc c;
	for(y=t-1;y>=t-2 && y>=0;y--){
		c.i=s,c.j=y;
		if(temp[x][y]==0 && which_three0(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three0(c,b,player,temp)==1)
			count1++;
			
	}
	
	for(y=t+1;y<=t+2 && y<=14;y++){
		c.i=s,c.j=y;
		if(temp[x][y]==0 && which_three0(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three0(c,b,player,temp)==1)
			count1++;
	}
	
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}
//竖着：
int is_five1(struct loc a,struct loc b,int player,int Board[15][15])//a:point waiting to be judged b:point should be included in live5 etc.. if any
{	
	int s=a.i,t=a.j;
	int n,k;
	int temp[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int sign=0,count=0,x=s-1;
	if(a.i==b.i && a.j==b.j)
		sign++;
	while(x>=0 && temp[x][t]==player){
		if(x==b.i && t==b.j)
		sign++;	
		count++,x--;
	}	
	x=s+1;
	while(x<=14 && temp[x][t]==player){
		if(x==b.i && t==b.j)
		sign++;
		count++,x++;
	}
	if(count==4 && sign>0)
		return 1;
	if(count>4 && sign>0)
		return 2;
	else
		return 0;
}
//return:0-no 4; 1-half 4; 2-live 4
int which_four1(struct loc a,struct loc b,int player,int Board[15][15])
{
	int s=a.i,t=a.j;
	int i=1,count=0;//count 记录能成5的点的个数
	int temp[15][15];
	int n,k,x,y;
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int count_lk=1;//为了区分活四和双冲四，需要看连起来的棋子个数
	x=s-1,y=t;
	while(x>=0 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,x--;}
	i=1;
	x=s+1,y=t;
	while(x<=14 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,x++;}
	
	
	
	struct loc c;
	for(x=s-1;x>=s-4 && x>=0;x--){
		c.i=x,c.j=t;
		if(temp[x][t]==0 && is_five1(c,b,player,temp)>=1)
			count++;
	}
	
	for(x=s+1;x<=s+4 && x<=14;x++){
		c.i=x,c.j=t;
		if(temp[x][t]==0 && is_five1(c,b,player,temp)>=1)
			count++;
	}
	
	if(count>=2 && count_lk<4)
		return 3;
	else if(count>=2)
		return 2;
	else if(count==1)
		return 1;
	else
		return 0;		
}

//return : 2-live 3; 1-half 3; 0-o.w.
int which_three1(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;	
	
	int x,y=t;
	struct loc c;
	for(x=s-1;x>=s-3 && x>=0;x--){
		c.i=x,c.j=t;
		if(temp[x][y]==0 && which_four1(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four1(c,b,player,temp)==1)
			count1++;
			
	}
	
	for(x=s+1;x<=s+3 && x<=14;x++){
		c.i=x,c.j=t;
		if(temp[x][y]==0 && which_four1(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four1(c,b,player,temp)==1)
			count1++;
	}
	
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}

int which_two1(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;	
	
	int x,y=t;
	struct loc c;
	for(x=s-1;x>=s-2 && x>=0;x--){
		c.i=x,c.j=t;
		if(temp[x][y]==0 && which_three1(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three1(c,b,player,temp)==1)
			count1++;
			
	}
	
	for(x=s+1;x<=s+2 && x<=14;x++){
		c.i=x,c.j=t;
		if(temp[x][y]==0 && which_three1(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three1(c,b,player,temp)==1)
			count1++;
	}
	
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}

//左上-右下:
int is_five2(struct loc a,struct loc b,int player,int Board[15][15])//a:point waiting to be judged b:point should be included in live5 etc.. if any
{	
	int s=a.i,t=a.j;
	int n,k;
	int temp[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int sign=0,count=0,x=s-1,y=t-1;
	if(a.i==b.i && a.j==b.j)
		sign++;
	while(x>=0 && y>=0 && temp[x][y]==player){
		if(x==b.i && y==b.j)
		sign++;	
		count++,x--,y--;
	}	
	x=s+1,y=t+1;
	while(x<=14 && y<=14 && temp[x][y]==player){
		if(x==b.i && y==b.j)
		sign++;
		count++,x++,y++;
	}
	if(count==4 && sign>0)
		return 1;
	if(count>4 && sign>0)
		return 2;
	else
		return 0;
}

//return:0-no 4; 1-half 4; 2-live 4
int which_four2(struct loc a,struct loc b,int player,int Board[15][15])
{
	int s=a.i,t=a.j;
	int i=1,count=0;//count 记录能成5的点的个数
	int temp[15][15];
	int n,k,x,y;
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int count_lk=1;//为了区分活四和双冲四，需要看连起来的棋子个数
	x=s-1,y=t-1;
	while(x>=0 && y>=0 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,x--,y--;}
	i=1;
	x=s+1,y=t+1;
	while(y<=14 && x<=14 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,y++,x++;}
	struct loc c;
	for(x=s-1,y=t-1;x>=s-4 && x>=0 &&y>=t-4 && y>=0;x--,y--){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && is_five2(c,b,player,temp)>=1)
			count++;
	}
	for(x=s+1,y=t+1;x<=s+4 && x<=14 &&y<=t+4 && y<=14;x++,y++){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && is_five2(c,b,player,temp)>=1)
			count++;
	}
	if(count>=2 && count_lk<4)
		return 3;
	else if(count>=2)
		return 2;
	else if(count==1)
		return 1;
	else
		return 0;
}


//return : 2-live 3; 1-half 3; 0-o.w.
int which_three2(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int x=s,y=t;
	struct loc c;
	for(x=s-1,y=t-1;x>=s-3 && x>=0 && y>=t-3 && y>=0;x--,y--){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_four2(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four2(c,b,player,temp)==1)
			count1++;
	}
	for(x=s+1,y=t+1;x<=s+3 && x<=14 && y<=t+3 && y<=14;x++,y++){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_four2(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four2(c,b,player,temp)==1)
			count1++;
	}
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}
int which_two2(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;

	int x=s,y=t;
	struct loc c;
	for(x=s-1,y=t-1;x>=s-2 && x>=0 && y>=t-2 && y>=0;x--,y--){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_three2(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three2(c,b,player,temp)==1)
			count1++;
	}
	for(x=s+1,y=t+1;x<=s+2 && x<=14 && y<=t+2 && y<=14;x++,y++){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_three2(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three2(c,b,player,temp)==1)
			count1++;
	}
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}


//左下-右上：
int is_five3(struct loc a,struct loc b,int player,int Board[15][15])//a:point waiting to be judged b:point should be included in live5 etc.. if any
{
	int s=a.i,t=a.j;
	int n,k;
	int temp[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int sign=0,count=0,x=s+1,y=t-1;
	if(a.i==b.i && a.j==b.j)
		sign++;
	while(x<=14 && y>=0 && temp[x][y]==player){
		if(x==b.i && y==b.j)
		sign++;
		count++,x++,y--;
	}
	x=s-1,y=t+1;
	while(x>=0 && y<=14 && temp[x][y]==player){
		if(x==b.i && y==b.j)
		sign++;
		count++,x--,y++;
	}
	if(count==4 && sign>0)
		return 1;
	if(count>4 && sign>0)
		return 2;
	else
		return 0;
}

//return:0-no 4; 1-half 4; 2-live 4
int which_four3(struct loc a,struct loc b,int player,int Board[15][15])
{
	int s=a.i,t=a.j;
	int i=1,count=0;//count 记录能成5的点的个数
	int temp[15][15];
	int n,k,x,y;
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int count_lk=1;//为了区分活四和双冲四，需要看连起来的棋子个数
	x=s+1,y=t-1;
	while(x<=14 && y>=0 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,x++,y--;}
	i=1;
	x=s-1,y=t+1;
	while(y<=14 && x>=0 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,y++,x--;}
	struct loc c;
	for(x=s+1,y=t-1;x<=s+4 && x<=14 &&y>=t-4 && y>=0;x++,y--){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && is_five3(c,b,player,temp)>=1)
			count++;
	}
	for(x=s-1,y=t+1;x>=s-4 && x>=0 &&y<=t+4 && y<=14;x--,y++){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && is_five3(c,b,player,temp)>=1)
			count++;
	}
	if(count>=2 && count_lk<4)
		return 3;
	else if(count>=2)
		return 2;
	else if(count==1)
		return 1;
	else
		return 0;
}
//return : 2-live 3; 1-half 3; 0-o.w.
int which_three3(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int x=s,y=t;
	struct loc c;
	for(x=s+1,y=t-1;x<=s+3 && x<=14 && y>=t-3 && y>=0;x++,y--){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_four3(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four3(c,b,player,temp)==1)
			count1++;
	}
	for(x=s-1,y=t+1;x>=s-3 && x>=0 && y<=t+3 && y<=14;x--,y++){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_four3(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four3(c,b,player,temp)==1)
			count1++;
	}
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}

int which_two3(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int x=s,y=t;
	struct loc c;
	for(x=s+1,y=t-1;x<=s+2 && x<=14 && y>=t-2 && y>=0;x++,y--){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_three3(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three3(c,b,player,temp)==1)
			count1++;
	}
	for(x=s-1,y=t+1;x>=s-2 && x>=0 && y<=t+2 && y<=14;x--,y++){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_three3(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three3(c,b,player,temp)==1)
			count1++;
	}
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}
//return 0:not ban 1:ban
int is_ban(int s,int t,int player,int Board[15][15],struct SingleScore BoardScore[15][15]){
	int live[7];
	int half[7];
	int dead[7];
	int n;
	for(n=0;n<7;n++)
		live[n]=half[n]=dead[n]=0;	
	int temp;
	for(n=0;n<4;n++)
	{
		temp=BoardScore[s][t].si[n].linkNum;
				
		if(BoardScore[s][t].si[n].oppNum==0)
			live[temp]++;
		else if(BoardScore[s][t].si[n].oppNum==1)
			half[temp]++;
		else if(BoardScore[s][t].si[n].oppNum==2)
			dead[temp]++;
		else if(BoardScore[s][t].si[n].oppNum==3)
			half[temp]+=2;
	}	
	if(Board[s][t]!=0)
		return 1;
	else if(live[6]>0 || half[6]>0 || dead[6]>0)
		return 1;
	else if(live[4]>=2 || half[4]>=2 || live[3]>=2)
		return 1;
	else if((live[4]+half[4])>=2)
		return 1;
	else 
		return 0;	
}
//参数：first-谁先手，t机器执子，deep深度，ai_Board...ai的状态棋盘，man_Boa...玩家的状态棋盘，Board当前的棋盘。
struct loc MaxMin(int first,int t,int deep,struct SingleScore aiBoardScore[15][15],struct SingleScore manBoardScore[15][15],int Board[15][15])//deep层数=向后看的步数
{	
	struct loc loc1;
	int anti;
	if(t==1)
		anti=2;
	else if(t==2)
		anti=1;
	//深度是0就不搜索	
	if(deep==0){
		cal_situation(t,aRecordBoard2,aiBoardScore);//计算ai的状态信息
		cal_situation(anti,aRecordBoard2,manBoardScore);//计算玩家的状态信息
		cal_score(t,first,aiBoardScore);//计算AI每个点的得分
		cal_score(anti,first,manBoardScore);//计算玩家每个点的得分
		change_score(aiBoardScore,manBoardScore,aRecordBoard2,t);//判断禁手，改变二者的得分（给ai看的）
		loc1=find_max(aiBoardScore,manBoardScore);//找到最大值点
		return loc1;//返回最大值点
	}else{
		struct loc candidate[NUM];//用来记录候选的AI的棋子
		select_point(t,first,NUM,candidate,Board,aiBoardScore,manBoardScore);//找出AI的NUM个候选点，不够的话剩余位置填（-1，-1）
		int score_of_candt[NUM];//记录每个候选点的分数
		int n,step=0;
		for(n=0;n<NUM;n++)
			if(candidate[n].i>=0 && candidate[n].j>=0)//如果被填上了//for n:0->deep-1
				score_of_candt[n]=evaluate(first,t,step,deep-1,candidate[n],Board);//搜索deep层，计算每个的得分（由于选择的时候考虑了禁手，所以不会评价被禁的）
			else  
				score_of_candt[n]=-100000000;//否则置一个超低分
		return (loc1=select_max_candt(candidate,score_of_candt));//返回得分最大的那个点
	}	
}
//选点函数，输入t棋子颜色，first谁先谁后，num暂时没用，候选子数组，棋盘，两个记录每点状态的数组,考虑了禁手
void select_point(int t,int first,int num,struct loc candt[NUM],int Board[15][15],struct SingleScore player_BoardScore[15][15],struct SingleScore anti_BoardScore[15][15])
{	//先算出对手的棋子颜色
	int anti;
	if(t==1)
		anti=2;
	else
		anti=1;
	struct loc temp={0,0};
	initgrade(player_BoardScore,anti_BoardScore);
	cal_situation(t,Board,player_BoardScore);
	cal_situation(anti,Board,anti_BoardScore);
	cal_score(t,first,player_BoardScore);
	cal_score(anti,first,anti_BoardScore);
	change_score(player_BoardScore,anti_BoardScore,Board,t);//判断禁手来改变分数，这个分数是给“我”看的
	temp=find_max(player_BoardScore,anti_BoardScore);
	
	int s;
	for(s=0;s<NUM;s++)
		candt[s].i=candt[s].j=-1;
	//找出最大值
	//int max=anti_BoardScore[0][0].score+player_BoardScore[0][0].score;
	int m=0,n,k;
	/*for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			if((anti_BoardScore[n][k].score+player_BoardScore[n][k].score)>(anti_BoardScore[temp.i][temp.j].score+player_BoardScore[temp.i][temp.j].score))
				temp.i=n,temp.j=k;*/
	int grade[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			grade[n][k]=anti_BoardScore[n][k].score+player_BoardScore[n][k].score;	
	//找出那些点	
	for(m=0;m<NUM;m++){
		candt[m]=max_of2d_array(grade);
		grade[candt[m].i][candt[m].j]=-100000;
	}
}
struct loc max_of2d_array(int grade[15][15]){
	int max=grade[0][0];
	int n,k;
	struct loc b;
	struct loc_value a={0,0,max};
	for(n=0;n<15;n++)
		for(k=0;k<15;k++){
			if(a.Value<grade[n][k]){
				a.x1=n,a.x2=k,a.Value=grade[n][k];
			}	
		}
	b.i=a.x1;
	b.j=a.x2;
	return b;
}

int evaluate(int first,int t,int step,int deep,struct loc candt,int Board[15][15])//t表示被判断的这个点是黑子还是白子,计算下上这个子以后棋盘的分数
{	//计算人执什么子
	int anti;
	if(t==1)
		anti=2;
	else 
		anti=1;
	//假设ai下了这个子	
	int temp[15][15];
	int n,k;
	for(n=0;n<15;n++)
		for(k=0;k<15;k++){
			temp[n][k]=Board[n][k];
		}
		temp[candt.i][candt.j]=t;
		
	if(already_five(candt.i,candt.j,temp,t)){
		if(t==1 && first==1)//人先走且t是黑棋——t是人的棋
			return -99999999;
		else if(t==1 && first==0)
			return 99999999;
		else if(t==2 && first==1)
			return 99999999;
		else if(t==2 && first==0)
			return -99999999;
	}else if(is_to_win(candt.i,candt.j,temp,t) /*&& !is_to_win(candt.i,candt.j,temp,anti)*/ && no_five(temp,anti)){
		if(t==1 && first==1)//人先走且t是黑棋——t是人的棋
			return -99999998;
		else if(t==1 && first==0)
			return 99999998;
		else if(t==2 && first==1)
			return 99999998;
		else if(t==2 && first==0)
			return -99999998;
	}
	
	//递归求值
	if((step%2)==0){
		if(deep==0){
			return cal_board_score4ai(temp,t,first);
		}else if(deep>0){
			struct loc candidate[NUM];//to record the candidates of people 
			struct SingleScore player_BoardScore[15][15];
			struct SingleScore anti_BoardScore[15][15];
			select_point(anti,first,NUM,candidate,temp,player_BoardScore,anti_BoardScore);//为对手（人）找出NUM个候选点
			int score_of_candt[NUM];//to record the grade of the candidate of people
			int l;//,step=0;
			int NextBoard[NUM][15][15];//to record the board after the people set each candidate 
			for(l=0;l<NUM;l++){
				for(n=0;n<15;n++)
					for(k=0;k<15;k++){
						NextBoard[l][n][k]=temp[n][k];
					}
			}
			
			for(l=0;l<NUM;l++){
				if(candidate[l].i>=0 && candidate[l].j>=0){
						NextBoard[l][candidate[l].i][candidate[l].j]=anti;
				}
			}
			step++,deep--;
			for(n=0;n<NUM;n++)
				if(candidate[n].i>=0 && candidate[n].j>=0)
					score_of_candt[n]=evaluate(first,anti,step,deep,candidate[n],NextBoard[n]);//搜索deep-1层，计算每个的得分
				else
					score_of_candt[n]=-100000000;
			return min_of_array(score_of_candt);
		}
	}else if((step%2)==1){
		if(deep==0){
			return cal_board_score4ai(temp,t,first);
		}else if(deep>0){
			struct loc candidate[NUM];
			struct SingleScore player_BoardScore[15][15];
			struct SingleScore anti_BoardScore[15][15];
			select_point(t,NUM,first,candidate,temp,player_BoardScore,anti_BoardScore);//找出NUM个候选点
			int score_of_candt[NUM];
			int l;//,step=0;
			int NextBoard[NUM][15][15];
			for(l=0;l<NUM;l++){
				for(n=0;n<15;n++)
					for(k=0;k<15;k++){
						NextBoard[l][n][k]=temp[n][k];
					}
			}
			
			for(l=0;l<NUM;l++){
				if(candidate[l].i>=0 && candidate[l].j>=0){
					NextBoard[l][candidate[l].i][candidate[l].j]=anti;
				}
			}
			step++,deep--;
			for(n=0;n<NUM;n++)
				if(candidate[n].i>=0 && candidate[n].j>=0)
					score_of_candt[n]=evaluate(first,anti,step,deep,candidate[n],NextBoard[n]);//搜索deep-1层，计算每个的得分
				else
					score_of_candt[n]=100000000;
			return max_of_array(score_of_candt);
		}
	}
}

int max_of_array(int score_of_candt[NUM]){
	int n,max=-100000001;
	for(n=0;n<NUM;n++){
		if(max<score_of_candt[n])
			max=score_of_candt[n];
	}
	return max;
}

int min_of_array(int score_of_array[NUM]){
	int n,min=100000001;
	for(n=0;n<NUM;n++){
		if(min>score_of_array[n])
			min=score_of_array[n];
	}
	return min;
}

struct loc select_max_candt(struct loc candidate[NUM],int score_of_candt[NUM]){
	int n,max=-100000001,counter=0;
	for(n=0;n<NUM;n++){
		if(max<score_of_candt[n]){
			max=score_of_candt[n];
			counter=1;
		}else if(max==score_of_candt[n]){
			counter++;
		}
	}
	int temp = rand()%counter + 1;
	for (n=0;n<NUM;n++){
		if (score_of_candt[n]==max){
			temp--;
			if (temp==0){
				return candidate[n];
			}
		}
	}
}
//输入一个棋盘与谁先手的信息first,计算得分。
int cal_board_score4ai(int Board[15][15],int t,int first){//t是ai执子
	int anti,player;
	if(first==1)
		player=2,anti=1;
	else
		player=1,anti=2;
	
	
	struct SingleScore player_BoardScore[15][15];
	struct SingleScore anti_BoardScore[15][15];
	initgrade(player_BoardScore,anti_BoardScore);
	cal_situation(player,Board,player_BoardScore);
	cal_situation(anti,Board,anti_BoardScore);
	cal_score(player,first,player_BoardScore);
	cal_score(anti,first,anti_BoardScore);
	change_score(player_BoardScore,anti_BoardScore,Board,t);
	//以下不考虑多步以后的禁手
	int n,k,sum=0;
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			sum+=(player_BoardScore[n][k].score-anti_BoardScore[n][k].score);
	return sum;
}
/*获胜点的得分+--99999999,还有一种策略是从1搜索到deep-1层，先扫描低层再高层，（复杂度的阶不变），一旦低层时有获胜点出现，就不继续扫描了，否则返回扫描deep-1层的值*/

int is_to_win(int s,int t,int Board[15][15],int player)
{
	struct SingleInfo a[4]={{0,0},{0,0},{0,0},{0,0}};
	int n;
	a[0]=cal0(s,t,player,Board);//横
	a[1]=cal1(s,t,player,Board);//竖
	a[2]=cal2(s,t,player,Board);//左下-右上
	a[3]=cal3(s,t,player,Board);//左上-右下
	int live[7];
	int half[7];
	int dead[7];
	for(n=0;n<7;n++)
		live[n]=half[n]=dead[n]=0;	
	int temp;
	for(n=0;n<4;n++)
	{
		temp=a[n].linkNum;
				
		if(a[n].oppNum==0)
			live[temp]++;
		else if(a[n].oppNum==1)
			half[temp]++;
		else if(a[n].oppNum==2)
			dead[temp]++;
		else if(a[n].oppNum==3)
			half[temp]+=2;
	}	
	if(player==2){
		if(live[4]>=2 || live[3]>=2 || half[4]>=2)
			return 1;
		else if(live[4]>=1)
			return 1;
		else if(half[4]>=1 && live[3]>=1)
			return 1;
		else 
			return 0; 
	}
	else if(player==1){
		if(live[4]>=1)
			return 1;
		else if(half[4]>=1 && live[3]>=1)
			return 1;
		else 
			return 0; 
	}	
}

int already_five(int s,int t,int Board[15][15],int player)
{			
	struct loc l;
	l.i=s,l.j=t;
	if(is_five0(l,l,player,Board) || is_five1(l,l,player,Board) || is_five2(l,l,player,Board) || is_five3(l,l,player,Board))
		return 1;
	else
		return 0;	
}


int evaluate1(int first,int t,int step,int deep,struct loc candt,int Board[15][15])
{	int anti;
	if(t==1)anti=2;
	else anti=1;
	
	int g,h,temp[15][15];
	for(g=0;g<15;g++)
		for(h=0;h<15;h++){
			temp[g][h]=Board[g][h];
		}
	temp[candt.i][candt.j]=t;
	int scre[15][15];
	for(g=0;g<15;g++)
		for(h=0;h<15;h++){
			if(anti==2){
				if(temp[g][h]==0){
					struct loc loc1;
					loc1.i=g,loc1.j=h;
					scre[g][h]=evaluate2(first,t,step+1,deep-1,loc1,candt,temp);
				}
				else
					scre[g][h]=100000000;	
			}else{
				if(temp[g][h]==0 && !be_baned(g,h,anti,temp)){
					struct loc loc1;
					loc1.i=g,loc1.j=h;
					scre[g][h]=evaluate2(first,t,step+1,deep-1,loc1,candt,temp);
				}
				else
					scre[g][h]=100000000;	
			}
		}
	return min_ar(scre);
}

int be_baned(int s,int t,int player,int Board[15][15]){
	if(Board[15][15]!=0)
		return 1;
	else{
		struct SingleScore BoardScore[15][15];
		initgrade(BoardScore,BoardScore);
		cal_situation(player,Board,BoardScore);
		//int is_ban(int s,int t,int player,int Board[15][15],struct SingleScore BoardScore[15][15])
		if(is_ban(s,t,player,Board,BoardScore))
			return 1;
	}
	return 0;
}



int re_grade_loc(int s,int t,int player,int Board[15][15]){
		struct SingleInfo a[4]={{0,0},{0,0},{0,0},{0,0}};
		int n;
		a[0]=cal0(s,t,player,Board);//横
		a[1]=cal1(s,t,player,Board);//竖
		a[2]=cal2(s,t,player,Board);//左下-右上
		a[3]=cal3(s,t,player,Board);//左上-右下
		int live[7];
		int half[7];
		int dead[7];
		for(n=0;n<7;n++)
			live[n]=half[n]=dead[n]=0;	
		int temp;
		for(n=0;n<4;n++)
		{
			temp=a[n].linkNum;
				
			if(a[n].oppNum==0)
				live[temp]++;
			else if(a[n].oppNum==1)
				half[temp]++;
			else if(a[n].oppNum==2)
				dead[temp]++;
			else if(a[n].oppNum==3)
				half[temp]+=2;
		}	
		return cal_grade_point(live,half,dead);
}

int evaluate2(int first,int t,int step,int deep,struct loc loc1,struct loc loc0,int Board[15][15]){
	int anti;
	if(t==1)anti=2;
	else anti=1;
	
	int g,h,temp[15][15];
	for(g=0;g<15;g++)
		for(h=0;h<15;h++){
			temp[g][h]=Board[g][h];
		}
	temp[loc1.i][loc1.j]=t;
	int g1,g2;
	g1=re_grade_loc(loc0.i,loc0.j,anti,Board);
	g2=re_grade_loc(loc1.i,loc1.j,t,Board);
	return g1-g2;
}

int min_ar(int score[15][15]){
	int s=score[0][0];
	int x,y;
	for(x=0;x<15;x++)
		for(y=0;y<15;y++){
			if(s>score[x][y])
				s=score[x][y];
		}
	return s;
}
int max_ar(int score[15][15]){
	int s=score[0][0];
	int x,y;
	for(x=0;x<15;x++)
		for(y=0;y<15;y++){
			if(s<score[x][y])
				s=score[x][y];
		}
	return s;
}
struct loc MaxMin2(int first,int t,int deep,struct SingleScore aiBoardScore[15][15],struct SingleScore manBoardScore[15][15],int Board[15][15])//deep层数=向后看的步数
{	struct loc aaa;
	int score[15][15],g,h;
	for(g=0;g<15;g++)
		for(h=0;h<15;h++){
			if(t==2){
				if(Board[g][h]==0){
					struct loc loc1;
					loc1.i=g,loc1.j=h;
					score[g][h]=evaluate1(first,t,0,deep-1,loc1,Board);
				}
				else
					score[g][h]=-100000000;	
			}else{
				if(Board[g][h]==0 && !be_baned(g,h,t,Board)){
					struct loc loc1;
					loc1.i=g,loc1.j=h;
					score[g][h]=evaluate1(first,t,0,deep-1,loc1,Board);
				}
				else
					score[g][h]=-100000000;	
			}
		}
	int max=max_ar(score);
	for(g=0;g<15;g++)
		for(h=0;h<15;h++){
			if(score[g][h]==max)
				aaa.i=g,aaa.j=h;
		}
	return aaa;
}

int no_five(int temp[15][15],int player){
	int m,n;
	for(m=0;m<15;m++)
		for(n=0;n<15;n++)
		{
			if(already_five(m,n,temp,player))
				return 0;
		}
	return 1;
}
