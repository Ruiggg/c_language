#include "statement.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define DEPTH 2//层数
extern int aRecordBoard2[SIZE][SIZE];
extern i;
struct SingleScore ai_BoardScore[15][15];//记录此刻棋盘上ai方的连珠状态以及得分
struct SingleScore man_BoardScore[15][15];//记录此刻棋盘上man方的连珠状态以及得分
//ai下棋函数
struct point ai_play(int t,int first,int step)
{	
	
	initgrade(ai_BoardScore,man_BoardScore);//因为后面不会计算非空点，所以要初始化
	struct point a;//储存ai要下的棋子的坐标，以及是否退出游戏的信息
	struct loc loc1;//记录要下的棋子坐标
	//计算出对方的执子颜色
	int anti;
	if(t==1)
		anti=2;
	else
		anti=1;
	//if(step<=3)
		//loc1=MaxMin(first,t,1,ai_BoardScore,man_BoardScore,aRecordBoard2);//前2步不要算那么久
	//else
		loc1=MaxMin(first,t,DEPTH,ai_BoardScore,man_BoardScore,aRecordBoard2);//极大极小值算法求落子位置
	ai_set(t,loc1.i,loc1.j);	//落子	
	a.x=15-loc1.i;
	a.y=loc1.j+'a';
	a.is_quit=-1;
	return a;	
}

//下子操作（n:棋子类型（1：黑子；2：白子），i,j是落子坐标）
void ai_set(int n,int i,int j)
{
	if((n==1 || n==2) && i>=0 && i<15 && j>=0 && j<15 && aRecordBoard2[i][j]==0)
		aRecordBoard2[i][j]=n;
	else
		printf("\n critical error in void ai_set(...) in ai_play.c\n");
}
//找到棋盘里对于ai来讲，得分最高的点
//参数：记录ai与man的各个点连珠状态和得分的结构数组
//返回：得分最大值的坐标
struct loc find_max(struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15]){
	struct loc locc={0,0};
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
		{
			if(ai_BoardScore[s][t].score+man_BoardScore[s][t].score > ai_BoardScore[locc.i][locc.j].score+man_BoardScore[locc.i][locc.j].score)//得分是ai与man的该点得分之和
			{
				locc.i=s;locc.j=t;
			}
		}
	return locc;
}
//初始化记录我方与对方的各个点连珠状态和得分的结构数组，以防止后面使用时越界现象
//参数就是这两个结构数组
void initgrade(struct SingleScore player_BoardScore[15][15],struct SingleScore anti_BoardScore[15][15])
{
	int i,j,n;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++){
			player_BoardScore[i][j].score=anti_BoardScore[i][j].score=0;//得分初始化为0
			for(n=0;n<4;n++){
				player_BoardScore[i][j].si[n].linkNum=anti_BoardScore[i][j].si[n].linkNum=0;//连子数设为0
				player_BoardScore[i][j].si[n].oppNum=anti_BoardScore[i][j].si[n].oppNum=0;//活、半活、死的信息都初始化为0	
			}
		}
}
//根据记录状态信息的结构数组的各个点的连珠状态，计算每个点的得分，并储存在该数组里
//参数：player:棋子颜色（1：黑；2：白），BoardScore即上面的结构数组
void cal_score(int player,int first,struct SingleScore BoardScore[15][15])//first已经不用了，以后再删吧
{
	int live[7];//live[i]记录活i的个数
	int half[7];//half[i]记录半活i的个数
	int dead[7];//death[i]记录死i的个数
	int n;
	for(n=0;n<7;n++)
		live[n]=half[n]=dead[n]=0;//首先初始化为0
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)//扫描全部
		{	
			int temp;
			for(n=0;n<4;n++)//四个方向
			{
				temp=BoardScore[s][t].si[n].linkNum;//temp为如果下这个点，将形成的连珠个数，由于这儿没有考虑此点是否被占，但死计算状态数组时没有计算被占点，所以这个传入的数组必须初始化，否则linkNum将可能大于6，越界
				
				if(BoardScore[s][t].si[n].oppNum==0)
					live[temp]++;
				else if(BoardScore[s][t].si[n].oppNum==1)
					half[temp]++;
				else if(BoardScore[s][t].si[n].oppNum==2)
					dead[temp]++;
				else if(BoardScore[s][t].si[n].oppNum==3)
					half[temp]+=2;//oppNum=3仅当同一个方向成双四
			}	
			
			BoardScore[s][t].score=cal_grade_point(live,half,dead);//调用函数，计算这一点的得分
			for(n=0;n<7;n++)
				live[n]=half[n]=dead[n]=0;	//重新归0，下次再用
		}
}
//输入活i,半活i，死i的个数，返回得分
int cal_grade_point(int live[],int half[],int dead[])
{
	if(live[5]>=1 || half[5]>=1 || dead[5]>=1)//能成5分最高
		return 100000;
	else if(live[4]>=1 || half[4]>=2)//其次（由于我们比较得分是比较人机得分和，所以小于上一级的一半）
		return 49999;
	else if(live[3]>=2)
		return 24999;
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
//计算状态函数
//输入棋子类型，棋盘，以及记录所有点状态的结构数组，改变该数组的状态信息
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

//计算一个点的状态（只看横向）
//参数：位置s,t; 棋子player; 棋盘Board
//返回一个SingleInfo类型的结构，记录连子个数和活、半活、死的信息
struct SingleInfo cal0(int s,int t,int player,int Board[15][15])//横着,player depends on whether ai is white or black player
{	
	struct SingleInfo a={0,0};//初始化
	int i=1,count=0,anti;
	struct loc l;//建一个loc型结构，用来作为参数传递给后面的函数
	l.i=s,l.j=t;
	if(player==1)//计算对手的棋子
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
		a.oppNum=0;//活三
	}
	else if(m==1){
		a.linkNum=3;
		a.oppNum=1;//半活三
	}else if((m=which_two0(l,l,player,Board))==2){
		a.linkNum=2;
		a.oppNum=0;//活二
	}
	else if(m==1){
		a.linkNum=2;	
		a.oppNum=1;//半活二
	}
	else{//都不是的话只需要扫描连起来的个数与两边的障碍数
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
//计算一个点的状态（只看纵向），其他同上
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
//计算一个点的状态（只看左上-右下），其他同上
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
//计算一个点的状态（只看左下-右上），其他同上
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

//判断横向，下了a,是否成一个过b的五
//输入:loc类型结构a,b,player:棋子类型；Board棋盘
//返回：2：长连 1：成五；0：不能成5
int is_five0(struct loc a,struct loc b,int player,int Board[15][15])//a:point waiting to be judged b:point should be included in live5 etc.. if any
{	
	int s=a.i,t=a.j;
	int n,k;
	int temp[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体棋盘复制过来
	temp[s][t]=player;//下上a点
	int sign=0,count=0,y=t-1;//sign记录是否扫描到b点
	if(a.i==b.i && a.j==b.j)//如果a,b是同一点，则认为扫描到了
		sign++;
	while(y>=0 && temp[s][y]==player){//横着向左扫描
		if(s==b.i && y==b.j)
		sign++;	
		count++,y--;
	}	
	y=t+1;
	while(y<=14 && temp[s][y]==player){//横着向右扫描
		if(s==b.i && y==b.j)
		sign++;
		count++,y++;
	}
	if(count==4 && sign>0)//除了自己扫描到4个点而且扫过b
		return 1;
	if(count>4 && sign>0)//扫过b而且长连
		return 2;
	else//其他
		return 0;

}
//横着：
//return:0-no 4; 1-half 4; 2-live 4 ;判断如果下在a点，会不会成过b点的活四，冲四，或其他
//参数：记录a,b坐标的结构，player:棋子类型，Board:棋盘
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
	while(y>=0 && i<=5 && Board[x][y]==player)//向左扫描至多5个点，计算连珠
		{count_lk++,i++,y--;}
	i=1;
	x=s,y=t+1;
	while(y<=14 && i<=5 && Board[x][y]==player)//向右扫描至多5个点，计算连珠
		{count_lk++,i++,y++;}
	struct loc c;
	for(y=t-1;y>=t-4 && y>=0;y--){//向左扫至多4个点
		c.i=s,c.j=y;//扫到的点的坐标存在c
		if(temp[s][y]==0 && is_five0(c,b,player,temp)==1)//如果这一点没有被占，而且能成一个过点b的五
			count++;//那么count加1
	}
	for(y=t+1;y<=t+4 && y<=14;y++){
		c.i=s,c.j=y;
		if(temp[s][y]==0 && is_five0(c,b,player,temp)==1)//如果这一点没有被占，而且能成一个过点b的五
			count++;//那么count加1
	}
	if(count>=2 && count_lk<4)//下了a，有两个能成过a的五连珠的点，但相邻的连珠数小于4，说明是一个方向的双冲四
		return 3;
	else if(count>=2)//下了a，有两个能成过a的五连珠的点，但相邻的连珠数不小于4，说明四活四
		return 2;
	else if(count==1)//只有一个点成五，半活四
		return 1;
	else//其他
		return 0;		
}
//判断如果下了点a，只看横向，能不能成过点b的活三或者半活三
//return : 2-live 3; 1-half 3; 0-o.w.
//参数：要判断的点a,必须过的点b，棋子类型player,棋盘Board
int which_three0(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半活4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;	//落子
	
	int x=s,y;
	struct loc c;
	//向左扫描3个点，判断有没有能过点b的活四、半活四的点
	for(y=t-1;y>=t-3 && y>=0;y--){
		c.i=s,c.j=y;
		if(temp[x][y]==0 && which_four0(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four0(c,b,player,temp)==1)
			count1++;	
	}
	//向右扫描3个点，判断有没有能过点b的活四、半活四的点	
	for(y=t+1;y<=t+3 && y<=14;y++){
		c.i=s,c.j=y;
		if(temp[x][y]==0 && which_four0(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four0(c,b,player,temp)==1)
			count1++;
	}
	//有成活四的点——活三——返回2
	//有成半活四的点——半活三——返回1
	//其他——返回0
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}
//判断如果下了点a，只看横向，能不能成过点b的活二或者半活二
//return : 2-live 2; 1-half 2; 0-o.w.
//参数：要判断的点a,必须过的点b，棋子类型player,棋盘Board
int which_two0(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活3,半活3的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;	
	
	int x=s,y;
	struct loc c;
	//向左扫描2个点，判断有没有能过点b的活3、半活3的点
	for(y=t-1;y>=t-2 && y>=0;y--){
		c.i=s,c.j=y;
		if(temp[x][y]==0 && which_three0(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three0(c,b,player,temp)==1)
			count1++;
			
	}
	//向左扫描2个点，判断有没有能过点b的活3、半活3的点	
	for(y=t+1;y<=t+2 && y<=14;y++){
		c.i=s,c.j=y;
		if(temp[x][y]==0 && which_three0(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three0(c,b,player,temp)==1)
			count1++;
	}
	//有成活3的点——活3——返回2
	//有成半活3的点——半活3——返回1
	//其他——返回0
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}
//竖着：
//查看如果下在了点a,能否成过b的活5，或者长连
//a:被分析的点，b能否过的点，player棋子，Board棋盘
//返回：2——长连，1——成5，0——其他
int is_five1(struct loc a,struct loc b,int player,int Board[15][15])//a:point waiting to be judged b:point should be included in live5 etc.. if any
{	
	int s=a.i,t=a.j;
	int n,k;
	int temp[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;//下子
	int sign=0,count=0,x=s-1;
	if(a.i==b.i && a.j==b.j)//如果a,b在同一点，则一定经过b
		sign++;
	//向上扫描，直到遇到与player不同色的棋子
	while(x>=0 && temp[x][t]==player){
		if(x==b.i && t==b.j)
		sign++;	
		count++,x--;
	}	
	//向下扫描，直到遇到与player不同色的棋子
	x=s+1;
	while(x<=14 && temp[x][t]==player){
		if(x==b.i && t==b.j)
		sign++;
		count++,x++;
	}
	//有成活5的点——返回1
	//有成长连的点——返回2
	//其他——返回0
	if(count==4 && sign>0)
		return 1;
	if(count>4 && sign>0)
		return 2;
	else
		return 0;
}

//竖着：
//return:0-no 4; 1-half 4; 2-live 4 ;判断如果下在a点，会不会成过b点的活四，冲四，或其他
//参数：记录a,b坐标的结构，player:棋子类型，Board:棋盘
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
	while(x>=0 && i<=5 && Board[x][y]==player)//向上扫描至多5个点，计算连珠
		{count_lk++,i++,x--;}
	i=1;
	x=s+1,y=t;
	while(x<=14 && i<=5 && Board[x][y]==player)//向下扫描至多5个点，计算连珠
		{count_lk++,i++,x++;}
	struct loc c;
	//向左至多扫4个点
	for(x=s-1;x>=s-4 && x>=0;x--){
		c.i=x,c.j=t;//扫到的点坐标存在c
		if(temp[x][t]==0 && is_five1(c,b,player,temp)>=1)//如果点c没有被占，而且如果下上c能成一个过b的5
			count++;
	}
	
	for(x=s+1;x<=s+4 && x<=14;x++){
		c.i=x,c.j=t;//扫到的点坐标存在c
		if(temp[x][t]==0 && is_five1(c,b,player,temp)>=1)//如果点c没有被占，而且如果下上c能成一个过b的5
			count++;
	}
	//有两个点能成五但四连子数目小于4——双冲四
	//有两个点成5，连子数目不小于4——活四
	//只有一个点成5——半活四
	//其他
	if(count>=2 && count_lk<4)
		return 3;
	else if(count>=2)
		return 2;
	else if(count==1)
		return 1;
	else
		return 0;		
}
//判断如果下了a，只看纵向，能否成过b的活三、半活三
//参数：点a,b的坐标，棋子player,棋盘Board
//return : 2-live 3; 1-half 3; 0-o.w.
int which_three1(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;//落子	
	
	int x,y=t;
	struct loc c;
	//向上扫描3个点，判断有没有成能过b的活四、半活四的点
	for(x=s-1;x>=s-3 && x>=0;x--){
		c.i=x,c.j=t;
		if(temp[x][y]==0 && which_four1(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four1(c,b,player,temp)==1)
			count1++;	
	}
	//向下扫描3个点，判断有没有成能过b的活四、半活四的点
	for(x=s+1;x<=s+3 && x<=14;x++){
		c.i=x,c.j=t;
		if(temp[x][y]==0 && which_four1(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four1(c,b,player,temp)==1)
			count1++;
	}
	//有成活4的点——活3——返回2
	//只有成半活4的点——半活3——返回1
	//其他——返回0
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}
//判断如果下了a，只看纵向，能否成过b的活2、半活2
//参数：点a,b的坐标，棋子player,棋盘Board
//return : 2-live 2; 1-half 2; 0-o.w.
int which_two1(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活3,半活3的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;//落子
	
	int x,y=t;
	struct loc c;
	//向上扫描2个点，判断有没有成能过b的活3、半活3的点
	for(x=s-1;x>=s-2 && x>=0;x--){
		c.i=x,c.j=t;
		if(temp[x][y]==0 && which_three1(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three1(c,b,player,temp)==1)
			count1++;
	}
	//向下扫描3个点，判断有没有成能过b的活3、半活3的点
	for(x=s+1;x<=s+2 && x<=14;x++){
		c.i=x,c.j=t;
		if(temp[x][y]==0 && which_three1(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three1(c,b,player,temp)==1)
			count1++;
	}
	//有成活3的点——活2——返回2
	//只有成半活3的点——半活2——返回1
	//其他——返回0	
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}


//左上-右下:
//查看如果下在了点a,能否成过b的活5，或者长连
//a:被分析的点，b能否过的点，player棋子，Board棋盘
//返回：2——长连，1——成5，0——其他
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
	if(a.i==b.i && a.j==b.j)//如果a,b在同一点，则一定经过b
		sign++;
	//向左上扫描，直到遇到与player不同色的棋子	
	while(x>=0 && y>=0 && temp[x][y]==player){
		if(x==b.i && y==b.j)
		sign++;	
		count++,x--,y--;
	}	
	x=s+1,y=t+1;
	//向右下扫描，直到遇到与player不同色的棋子	
	while(x<=14 && y<=14 && temp[x][y]==player){
		if(x==b.i && y==b.j)
		sign++;
		count++,x++,y++;
	}
	//有成活5的点——返回1
	//有成长连的点——返回2
	//其他——返回0
	if(count==4 && sign>0)
		return 1;
	if(count>4 && sign>0)
		return 2;
	else
		return 0;
}
//左上——右下：
//return:0-no 4; 1-half 4; 2-live 4 ;判断如果下在a点，会不会成过b点的活四，冲四，或其他
//参数：记录a,b坐标的结构，player:棋子类型，Board:棋盘
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
	while(x>=0 && y>=0 && i<=5 && Board[x][y]==player)//向左上扫描至多5个点，计算连珠
		{count_lk++,i++,x--,y--;}
	i=1;
	x=s+1,y=t+1;
	while(y<=14 && x<=14 && i<=5 && Board[x][y]==player)//向右下扫描至多5个点，计算连珠
		{count_lk++,i++,y++,x++;}
	
	struct loc c;
	for(x=s-1,y=t-1;x>=s-4 && x>=0 &&y>=t-4 && y>=0;x--,y--){
		c.i=x,c.j=y;//扫到的点坐标存在c
		if(temp[x][y]==0 && is_five2(c,b,player,temp)>=1)//如果点c没有被占，而且如果下上c能成一个过b的5
			count++;
	}
	for(x=s+1,y=t+1;x<=s+4 && x<=14 &&y<=t+4 && y<=14;x++,y++){
		c.i=x,c.j=y;//扫到的点坐标存在c
		if(temp[x][y]==0 && is_five2(c,b,player,temp)>=1)//如果点c没有被占，而且如果下上c能成一个过b的5
			count++;
	}
	//有两个点能成五但四连子数目小于4——双冲四
	//有两个点成5，连子数目不小于4——活四
	//只有一个点成5——半活四
	//其他
	if(count>=2 && count_lk<4)
		return 3;
	else if(count>=2)
		return 2;
	else if(count==1)
		return 1;
	else
		return 0;
}

//判断如果下了a，只看左上-右下方向上，能否成过b的活3、半活3
//参数：点a,b的坐标，棋子player,棋盘Board
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
	//向左上扫描3个点，判断有没有成能过b的活4、半活4的点
	for(x=s-1,y=t-1;x>=s-3 && x>=0 && y>=t-3 && y>=0;x--,y--){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_four2(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four2(c,b,player,temp)==1)
			count1++;
	}
	//向右下扫描3个点，判断有没有成能过b的活4、半活4的点
	for(x=s+1,y=t+1;x<=s+3 && x<=14 && y<=t+3 && y<=14;x++,y++){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_four2(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four2(c,b,player,temp)==1)
			count1++;
	}
	//有成活4的点——活3——返回2
	//只有成半活4的点——半活3——返回1
	//其他——返回0
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}

//判断如果下了a，只看左上-右下方向上，能否成过b的活2、半活2
//参数：点a,b的坐标，棋子player,棋盘Board
//return : 2-live 2; 1-half 2; 0-o.w.
int which_two2(struct loc a,struct loc b,int player,int Board[15][15]){
	int s=a.i,t=a.j;
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;//落子

	int x=s,y=t;
	struct loc c;
	//向左上扫描2个点，判断有没有成能过b的活3、半活3的点
	for(x=s-1,y=t-1;x>=s-2 && x>=0 && y>=t-2 && y>=0;x--,y--){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_three2(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three2(c,b,player,temp)==1)
			count1++;
	}
	//向右下扫描2个点，判断有没有成能过b的活3、半活3的点
	for(x=s+1,y=t+1;x<=s+2 && x<=14 && y<=t+2 && y<=14;x++,y++){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_three2(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three2(c,b,player,temp)==1)
			count1++;
	}
	//有成活3的点——活2——返回2
	//只有成半活3的点——半活2——返回1
	//其他——返回0
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}

//左下-右上：
//查看如果下在了点a,能否成过b的活5，或者长连
//a:被分析的点，b能否过的点，player棋子，Board棋盘
//返回：2——长连，1——成5，0——其他
int is_five3(struct loc a,struct loc b,int player,int Board[15][15])//a:point waiting to be judged b:point should be included in live5 etc.. if any
{
	int s=a.i,t=a.j;
	int n,k;
	int temp[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;//落子
	int sign=0,count=0,x=s+1,y=t-1;//sign记录是否扫描过b
	if(a.i==b.i && a.j==b.j)//如果a,b是同一点，则一定经过b
		sign++;
	//向左下扫描至遇到不为player的点，记录扫描到的点数
	while(x<=14 && y>=0 && temp[x][y]==player){
		if(x==b.i && y==b.j)
		sign++;
		count++,x++,y--;
	}
	x=s-1,y=t+1;
	//向右上扫描至遇到不为player的点，记录扫描到的点数
	while(x>=0 && y<=14 && temp[x][y]==player){
		if(x==b.i && y==b.j)
		sign++;
		count++,x--,y++;
	}
	//有成活5的点——返回1
	//有成长连的点——返回2
	//其他——返回0
	if(count==4 && sign>0)
		return 1;
	if(count>4 && sign>0)
		return 2;
	else
		return 0;
}
//左下—右上：
//return:0-no 4; 1-half 4; 2-live 4 ;判断如果下在a点，会不会成过b点的活四，冲四，或其他
//参数：记录a,b坐标的结构，player:棋子类型，Board:棋盘
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
	while(x<=14 && y>=0 && i<=5 && Board[x][y]==player)//向左下扫描至多5个点，计算连珠
		{count_lk++,i++,x++,y--;}
	i=1;
	x=s-1,y=t+1;
	while(y<=14 && x>=0 && i<=5 && Board[x][y]==player)//向右上扫描至多5个点，计算连珠
		{count_lk++,i++,y++,x--;}
	struct loc c;
	//向左下读至多4个点
	for(x=s+1,y=t-1;x<=s+4 && x<=14 &&y>=t-4 && y>=0;x++,y--){
		c.i=x,c.j=y;//把读到的点的坐标记在c
		if(temp[x][y]==0 && is_five3(c,b,player,temp)>=1)//如果点c没有被占，而且如果下了c能成一个过b的5
			count++;
	}
	//向右上读至多4个点
	for(x=s-1,y=t+1;x>=s-4 && x>=0 &&y<=t+4 && y<=14;x--,y++){
		c.i=x,c.j=y;//把读到的坐标记在c
		if(temp[x][y]==0 && is_five3(c,b,player,temp)>=1)//如果点c没有被占，而且如果下c能成一个过b的5
			count++;
	}
	//有两个点能成五但四连子数目小于4——双冲四
	//有两个点成5，连子数目不小于4——活四
	//只有一个点成5——半活四
	//其他
	if(count>=2 && count_lk<4)
		return 3;
	else if(count>=2)
		return 2;
	else if(count==1)
		return 1;
	else
		return 0;
}

//判断如果下了a，只看左下-右上方向，能否成过b的活3、半活3
//参数：点a,b的坐标，棋子player,棋盘Board
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
	//向左下扫描3个点，判断有没有成能过b的活4、半活4的点
	for(x=s+1,y=t-1;x<=s+3 && x<=14 && y>=t-3 && y>=0;x++,y--){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_four3(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four3(c,b,player,temp)==1)
			count1++;
	}
	//向右上扫描3个点，判断有没有成能过b的活4、半活4的点
	for(x=s-1,y=t+1;x>=s-3 && x>=0 && y<=t+3 && y<=14;x--,y++){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_four3(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four3(c,b,player,temp)==1)
			count1++;
	}
	//有成活4的点——活3——返回2
	//只有成半活4的点——半活3——返回1
	//其他——返回0
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
	//向左下扫描2个点，判断有没有成能过b的活3、半活3的点
	for(x=s+1,y=t-1;x<=s+2 && x<=14 && y>=t-2 && y>=0;x++,y--){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_three3(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three3(c,b,player,temp)==1)
			count1++;
	}
	//向右下扫描2个点，判断有没有成能过b的活3、半活3的点
	for(x=s-1,y=t+1;x>=s-2 && x>=0 && y<=t+2 && y<=14;x--,y++){
		c.i=x,c.j=y;
		if(temp[x][y]==0 && which_three3(c,b,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_three3(c,b,player,temp)==1)
			count1++;
	}
	//有成活3的点——活2——返回2
	//只有成半活3的点——半活2——返回1
	//其他——返回0
	if(count2>0)
		return 2;
	else if(count1>0)
		return 1;
	else
		return 0;
}
//在当前局势下，判断是否被禁
//参数：s,t坐标；player棋子;Board棋盘;BoardScore是player在整个棋盘的连珠、得分信息
//return 0:not ban 1:ban
int is_ban(int s,int t,int player,int Board[15][15],struct SingleScore BoardScore[15][15]){
	int live[7];
	int half[7];
	int dead[7];
	int n;
	//初始化
	for(n=0;n<7;n++)
		live[n]=half[n]=dead[n]=0;	
	int temp;
	//计算活i,半活i,死i的个数
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
	//禁手：（1）被占（2）长连（3）双四（4）双三（5）组合
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
//返回要下的子的坐标
struct loc MaxMin(int first,int t,int deep,struct SingleScore aiBoardScore[15][15],struct SingleScore manBoardScore[15][15],int Board[15][15])//deep层数=向后看的步数
{	
	struct loc loc1;
	int anti;
	//计算对手的执子
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
//把选出的点存在结构数组candt里
void select_point(int t,int first,int num,struct loc candt[NUM],int Board[15][15],struct SingleScore player_BoardScore[15][15],struct SingleScore anti_BoardScore[15][15])
{	//先算出对手的棋子颜色
	int anti;
	if(t==1)
		anti=2;
	else
		anti=1;
	struct loc temp={0,0};
	initgrade(player_BoardScore,anti_BoardScore);//初始化
	cal_situation(t,Board,player_BoardScore);//计算我方的局势
	cal_situation(anti,Board,anti_BoardScore);//计算对手的局势
	cal_score(t,first,player_BoardScore);//根据我方局势，计算我方分数
	cal_score(anti,first,anti_BoardScore);//根据对方局势，计算对方分数
	change_score(player_BoardScore,anti_BoardScore,Board,t);//判断禁手来改变分数，这个分数是给“我”看的
	temp=find_max(player_BoardScore,anti_BoardScore);//找到最大值点
	
	int s;
	//初始化候选点数组
	for(s=0;s<NUM;s++)
		candt[s].i=candt[s].j=-1;
	int m=0,n,k;
	int grade[15][15];
	//计算每个点最终得分（对于ai而言）
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			grade[n][k]=anti_BoardScore[n][k].score+player_BoardScore[n][k].score;	
	//找出那些点（NUM个）	
	for(m=0;m<NUM;m++){
		candt[m]=max_of2d_array(grade);
		grade[candt[m].i][candt[m].j]=-100000;
	}
}
//寻找2维数组的最大元素的坐标
//输入一个15*15的二维数组
//返回最大值的坐标
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
//搜索打分函数
//参数：（1）first记录人先手还是ai先手的信息(2)t棋子(3)step当前层数(4)deep共搜索层数(5)candt一个点的坐标(6)Board棋盘
//返回：这个点的得分
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
	//如果下了这个子能成5，则不再搜索
	if(already_five(candt.i,candt.j,temp,t)){
		if(t==1 && first==1)//人先走且t是黑棋——t是人的棋
			return -99999999;//返回一个非常小的数
		else if(t==1 && first==0)//人后走且t是黑棋——t是ai的棋
			return 99999999;//返回一个非常大的数
		else if(t==2 && first==1)//人先走且t是白棋——t是ai的棋
			return 99999999;//返回一个非常大的数
		else if(t==2 && first==0)//人后走且t是白棋——t是人的棋
			return -99999999;//返回一个非常小的数
	}else if(is_to_win(candt.i,candt.j,temp,t) && no_five(temp,anti)){//有必胜棋而且对手没有成5的棋
		if(t==1 && first==1)//人先走且t是黑棋——t是人的棋
			return -99999998;//返回一个非常小的数
		else if(t==1 && first==0)//人后走且t是黑棋——t是ai的棋
			return 99999998;//返回一个非常大的数
		else if(t==2 && first==1)//人先走且t是白棋——t是ai的棋
			return 99999998;//返回一个非常大的数
		else if(t==2 && first==0)//人后走且t是白棋——t是人的棋
			return -99999998;//返回一个非常小的数
	}
	
	//递归求值
	//如果当前层数为偶数
	if((step%2)==0){
		//如果深度是0，则直接返回
		if(deep==0){
			return cal_board_score4ai(temp,t,first);
		}else if(deep>0){
			struct loc candidate[NUM];//记录对手NUM个得分最高的点的坐标 
			struct SingleScore player_BoardScore[15][15];//记录我方的连珠信息和得分
			struct SingleScore anti_BoardScore[15][15];//记录对方的连珠信息和得分
			select_point(anti,first,NUM,candidate,temp,player_BoardScore,anti_BoardScore);//为对手找出NUM个候选点
			int score_of_candt[NUM];//记录对手分别在这NUM个得分最高点下棋以后棋盘的得分
			int l;
			int NextBoard[NUM][15][15];//记录对手下上棋之后的棋盘
			//把原棋盘分别复制到这NUM棋盘
			for(l=0;l<NUM;l++){
				for(n=0;n<15;n++)
					for(k=0;k<15;k++){
						NextBoard[l][n][k]=temp[n][k];
					}
			}
			//分别替对手下棋
			for(l=0;l<NUM;l++){
				if(candidate[l].i>=0 && candidate[l].j>=0){
						NextBoard[l][candidate[l].i][candidate[l].j]=anti;
				}
			}
			//分别计算帮对手下好棋以后棋盘的分数
			step++,deep--;
			for(n=0;n<NUM;n++)
				if(candidate[n].i>=0 && candidate[n].j>=0)
					score_of_candt[n]=evaluate(first,anti,step,deep,candidate[n],NextBoard[n]);//搜索deep-1层，计算每个的得分
				else
					score_of_candt[n]=-100000000;
			return min_of_array(score_of_candt);//返回最小值
		}
	}else if((step%2)==1){
		if(deep==0){
			return cal_board_score4ai(temp,t,first);
		}else if(deep>0){
			struct loc candidate[NUM];//记录对手NUM个得分最高的点的坐标 
			struct SingleScore player_BoardScore[15][15];//记录我方的连珠信息和得分
			struct SingleScore anti_BoardScore[15][15];//记录对方的连珠信息和得分
			select_point(t,NUM,first,candidate,temp,player_BoardScore,anti_BoardScore);//为对手找出NUM个候选点
			int score_of_candt[NUM];//记录对手分别在这NUM个得分最高点下棋以后棋盘的得分
			int l;
			int NextBoard[NUM][15][15];//记录对手下上棋之后的棋盘
			//把原棋盘分别复制到这NUM棋盘
			for(l=0;l<NUM;l++){
				for(n=0;n<15;n++)
					for(k=0;k<15;k++){
						NextBoard[l][n][k]=temp[n][k];
					}
			}
			//分别替对手下棋
			for(l=0;l<NUM;l++){
				if(candidate[l].i>=0 && candidate[l].j>=0){
					NextBoard[l][candidate[l].i][candidate[l].j]=anti;
				}
			}
			//分别计算帮对手下好棋以后棋盘的分数
			step++,deep--;
			for(n=0;n<NUM;n++)
				if(candidate[n].i>=0 && candidate[n].j>=0)
					score_of_candt[n]=evaluate(first,anti,step,deep,candidate[n],NextBoard[n]);//搜索deep-1层，计算每个的得分
				else
					score_of_candt[n]=100000000;
			return max_of_array(score_of_candt);//返回最大值
		}
	}
}
//求一个数组里最大值
//输入一个数组
//返回元素最大值
int max_of_array(int score_of_candt[NUM]){
	int n,max=-100000001;
	for(n=0;n<NUM;n++){
		if(max<score_of_candt[n])
			max=score_of_candt[n];
	}
	return max;
}
//求一个数组里最小值
//输入一个数组
//返回元素最小值
int min_of_array(int score_of_array[NUM]){
	int n,min=100000001;
	for(n=0;n<NUM;n++){
		if(min>score_of_array[n])
			min=score_of_array[n];
	}
	return min;
}
//找到的妇女最高点
//输入候选每个点的坐标数组与得分数组
//返回对应分数最高的那个点
struct loc select_max_candt(struct loc candidate[NUM],int score_of_candt[NUM]){
	int n,max=-100000001,counter=0;
	//先求得分最高是多少，有几个
	for(n=0;n<NUM;n++){
		if(max<score_of_candt[n]){
			max=score_of_candt[n];
			counter=1;
		}else if(max==score_of_candt[n]){
			counter++;
		}
	}
	//再从得分最高的点里随即选择一个返回
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
	//通过谁先手的信息，计算出man和ai各执什么颜色的棋子
	if(first==1)
		player=2,anti=1;
	else
		player=1,anti=2;
	
	struct SingleScore player_BoardScore[15][15];
	struct SingleScore anti_BoardScore[15][15];
	initgrade(player_BoardScore,anti_BoardScore);//初始化
	cal_situation(player,Board,player_BoardScore);//计算局势
	cal_situation(anti,Board,anti_BoardScore);//计算局势
	cal_score(player,first,player_BoardScore);//打分
	cal_score(anti,first,anti_BoardScore);//打分
	change_score(player_BoardScore,anti_BoardScore,Board,t);//根据禁手改分
	//以下不考虑多步以后的禁手
	int n,k,sum=0;
	//计算这个棋盘的得分
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			sum+=(player_BoardScore[n][k].score-anti_BoardScore[n][k].score);
	return sum;
}
//判断是否能下出必胜的棋局（只能判断一部分情况）
//输入（1）s,t是横、纵坐标（2）Board棋盘（3）player棋子颜色（1：黑； 2：白）
//返回：1——能出现  0——不出现
int is_to_win(int s,int t,int Board[15][15],int player)
{
	struct SingleInfo a[4]={{0,0},{0,0},{0,0},{0,0}};//记录四个方向的连珠情况
	int n;
	a[0]=cal0(s,t,player,Board);//横
	a[1]=cal1(s,t,player,Board);//竖
	a[2]=cal2(s,t,player,Board);//左下-右上
	a[3]=cal3(s,t,player,Board);//左上-右下
	int live[7];
	int half[7];
	int dead[7];
	//根据连珠情况判断活i,半活i，死i
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
	//如果后手，则不考虑禁手
	if(player==2){
		if(live[4]>=2 || half[4]>=2)
			return 1;
		else if(live[4]>=1)
			return 1;
		else if(half[4]>=1 && live[3]>=1)
			return 1;
		else 
			return 0; 
	}//否则，被禁手禁的必胜局面不包括
	else if(player==1){
		if(live[4]>=1)
			return 1;
		else if(half[4]>=1 && live[3]>=1)
			return 1;
		else 
			return 0; 
	}	
}
//判断是否下了这一步就能赢
int already_five(int s,int t,int Board[15][15],int player)
{			
	struct loc l;
	l.i=s,l.j=t;
	if(is_five0(l,l,player,Board) || is_five1(l,l,player,Board) || is_five2(l,l,player,Board) || is_five3(l,l,player,Board))
		return 1;
	else
		return 0;	
}

//判断整个棋盘是否有某个点，下上就能成五
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
