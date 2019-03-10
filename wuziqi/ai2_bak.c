#include "statement.h"
#include <stdio.h>
#define SIZE 15

extern int aRecordBoard2[SIZE][SIZE];

struct SingleScore ai_BoardScore[15][15];
struct SingleScore man_BoardScore[15][15];
//ai下棋函数
struct point ai_play(int t,int first)
{	
	
	initgrade(ai_BoardScore,man_BoardScore);
	struct point a;
	struct loc loc1,loc2,temp;
	
	int anti;
	if(t==1)
		anti=2;
	else
		anti=1;
		
	cal_situation_ai(t,aRecordBoard2,ai_BoardScore);
	cal_situation_man(anti,aRecordBoard2,man_BoardScore);
	cal_score_ai(t,first,ai_BoardScore);
	cal_score_man(anti,first,man_BoardScore);
	
	/*loc1=find_max_man();
	loc2=find_max_ai();
	
	if(ai_BoardScore[loc2.i][loc2.j].score >= man_BoardScore[loc1.i][loc1.j].score){
		ai_set(t,loc2.i,loc2.j);
		a.x=15-loc2.i;
		a.y=loc2.j+'a';
		a.is_quit=-1;
	}	
	else{
		ai_set(t,loc1.i,loc1.j);		
		a.x=15-loc1.i;
		a.y=loc1.j+'a';
		a.is_quit=-1;
	} 	
//a.x=15-i;
//a.y=j+'a';
*/

	loc1=find_max(ai_BoardScore,man_BoardScore);
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


void initgrade(struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15])
{
	int i,j,n;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++){
			ai_BoardScore[i][j].score=man_BoardScore[i][j].score=0;
			for(n=0;n<4;n++){
				ai_BoardScore[i][j].si[n].linkNum=man_BoardScore[i][j].si[n].linkNum=0;
				ai_BoardScore[i][j].si[n].oppNum=man_BoardScore[i][j].si[n].oppNum=0;	
			}
		}
}

void cal_score_ai(int player,int first,struct SingleScore ai_BoardScore[15][15])//
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
			
			if(first==0){
				if(!is_ban(s,t,player,aRecordBoard2))
					ai_BoardScore[s][t].score=cal_grade_point(live,half,dead);
				else
					ai_BoardScore[s][t].score=-1;	
			}
			else{
				if(aRecordBoard2[s][t]==0)
					ai_BoardScore[s][t].score=cal_grade_point(live,half,dead);
				else
					ai_BoardScore[s][t].score=-1;	
			}
			
			for(n=0;n<6;n++)
				live[n]=half[n]=dead[n]=0;	//重新归0，下次再用
		}
}


int cal_grade_point(int live[],int half[],int dead[])
{
	if(live[5]>=1 || half[5]>=1 || dead[5]>=1)
		return 10000;
	else if(live[4]>=1)
		return 2499*live[4];
	else if(half[4]>=1 && live[3]>=1)
		return 2450;
	else if(live[3]>=2)
		return 601*live[3];
	else if(half[4]>=1)
		return 150*half[4];
	else if(live[3]>0)
		return 149;
	else if(half[3]>=1)
		return 35*half[3];
	else if(live[2]>=1)
		return 8*live[2];
	else if(half[2]>=1)
		return 5;
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

void cal_situation_ai(int player,int Board[15][15],struct SingleScore ai_BoardScore[15][15])
{
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
			if(aRecordBoard2[s][t]==0){//只扫描空位置
				ai_BoardScore[s][t].si[0]=cal0(s,t,player,Board);//横
				ai_BoardScore[s][t].si[1]=cal1(s,t,player,Board);//竖
				ai_BoardScore[s][t].si[2]=cal2(s,t,player,Board);//左下-右上
				ai_BoardScore[s][t].si[3]=cal3(s,t,player,Board);//左上-右下
			}
}

struct SingleInfo cal0(int s,int t,int player,int Board[15][15])//横着,player depends on whether ai is white or black player
{	
	struct SingleInfo a={0,0};
	int i=1,count=0,anti;
	
	if(player==1)
		anti=2;
	else if(player==2)
		anti=1;
	
	int m;
	if((m=is_five0(s,t,player,Board))==2){
		a.linkNum=6;
		a.oppNum=0;//长连将被禁掉，所以这个值没有意义
	}
	else if(m==1){
		a.linkNum=5;
		a.oppNum=0;//如果能成5，活不活同样重要，这个值不参考
	}
	else if((m=which_four0(s,t,player,Board))==2){
		a.linkNum=4;
		a.oppNum=0;//活四
	}
	else if(m==1){
		a.linkNum=4;
		a.oppNum=1;//半活四
	}
	else if((m=which_three0(s,t,player,Board))==2){
		a.linkNum=3;
		a.oppNum=0;
	}
	else if(m==1){
		a.linkNum=3;
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
	
	if(player==1)
		anti=2;
	else if(player==2)
		anti=1;
	
	
	int m;
	if((m=is_five1(s,t,player,Board))==2){
		a.linkNum=6;
		a.oppNum=0;//长连将被禁掉，所以这个值没有意义
	}
	else if(m==1){
		a.linkNum=5;
		a.oppNum=0;//如果能成5，活不活同样重要，这个值不参考
	}
	else if((m=which_four1(s,t,player,Board))==2){
		a.linkNum=4;
		a.oppNum=0;//活四
	}
	else if(m==1){
		a.linkNum=4;
		a.oppNum=1;//半活四
	}
	else if((m=which_three1(s,t,player,Board))==2){
		a.linkNum=3;
		a.oppNum=0;
	}
	else if(m==1){
		a.linkNum=3;
		a.oppNum=1;
	}
	else{
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
	
	if(player==1)
		anti=2;
	else if(player==2)
		anti=1;
	
	int m;
	if((m=is_five2(s,t,player,Board))==2){
		a.linkNum=6;
		a.oppNum=0;//长连将被禁掉，所以这个值没有意义
	}
	else if(m==1){
		a.linkNum=5;
		a.oppNum=0;//如果能成5，活不活同样重要，这个值不参考
	}
	else if((m=which_four2(s,t,player,Board))==2){
		a.linkNum=4;
		a.oppNum=0;//活四
	}
	else if(m==1){
		a.linkNum=4;
		a.oppNum=1;//半活四
	}
	else if((m=which_three2(s,t,player,Board))==2){
		a.linkNum=3;
		a.oppNum=0;
	}
	else if(m==1){
		a.linkNum=3;
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
	
	if(player==1)
		anti=2;
	else if(player==2)
		anti=1;
	int m;
	if((m=is_five3(s,t,player,Board))==2){
		a.linkNum=6;
		a.oppNum=0;//长连将被禁掉，所以这个值没有意义
	}
	else if(m==1){
		a.linkNum=5;
		a.oppNum=0;//如果能成5，活不活同样重要，这个值不参考
	}
	else if((m=which_four3(s,t,player,Board))==2){
		a.linkNum=4;
		a.oppNum=0;//活四
	}
	else if(m==1){
		a.linkNum=4;
		a.oppNum=1;//半活四
	}
	else if((m=which_three3(s,t,player,Board))==2){
		a.linkNum=3;
		a.oppNum=0;
	}
	else if(m==1){
		a.linkNum=3;
		a.oppNum=1;
	}
	else{
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

void cal_score_man(int player,int first,struct SingleScore man_BoardScore[15][15])//传进的player是ren的子
{
	int anti;
	if(player==2)
		anti=1;
	else if(anti==1)	
		anti=2;
	
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
			//不考虑人的禁手（日后再改，先解决主要矛盾再说）
			if(first==0){
				if(!is_ban(s,t,anti,aRecordBoard2))
					man_BoardScore[s][t].score=cal_grade_point(live,half,dead);
				else
					man_BoardScore[s][t].score=-1;	
			}
			else{
				if(aRecordBoard2[s][t]==0)
					man_BoardScore[s][t].score=cal_grade_point(live,half,dead);
				else
					man_BoardScore[s][t].score=-1;	
			}
			
			for(n=0;n<6;n++)
				live[n]=half[n]=dead[n]=0;
		}
}

void cal_situation_man(int player,int Board[15][15],struct SingleScore man_BoardScore[15][15])//传来的player是人的子
{
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
			if(aRecordBoard2[s][t]==0){
				man_BoardScore[s][t].si[0]=cal0(s,t,player,Board);//横
				man_BoardScore[s][t].si[1]=cal1(s,t,player,Board);//竖
				man_BoardScore[s][t].si[2]=cal2(s,t,player,Board);//左下-右上
				man_BoardScore[s][t].si[3]=cal3(s,t,player,Board);//左上-右下
			}
}
int is_five0(int s,int t,int player,int Board[15][15])
{
	int n,k;
	int temp[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int count=0,y=t-1;
	
	while(y>=0 && temp[s][y]==player)
		count++,y--;
	y=t+1;
	while(y<=14 && temp[s][y]==player)
		count++,y++;
	
	if(count==4)
		return 1;
	if(count>4)
		return 2;
	else
		return 0;
}

//return:0-no 4; 1-half 4; 2-live 4 ;判断如果下了这个子，会不会成活四，冲四，或其他
int which_four0(int s,int t,int player,int Board[15][15]){
	struct SingleInfo a={0,0};
	int i=1,count=0;//count 记录能成5的点的个数
	int temp[15][15];
	int n,k,x,y;
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	
	for(y=t-1;y>=t-4 && y>=0;y--){
		if(temp[s][y]==0 && is_five0(s,y,player,temp)>=1)
			count++;
	}
	
	for(y=t+1;y<=t+4 && y<=14;y++){
		if(temp[s][y]==0 && is_five0(s,y,player,temp)>=1)
			count++;
	}
	
	if(count>=2)
		return 2;
	else if(count==1)
		return 1;
	else
		return 0;
}

//return : 2-live 3; 1-half 3; 0-o.w.
int which_three0(int s,int t,int player,int Board[15][15]){
	struct SingleInfo a={0,0};
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int x=s,y;
	for(y=t-1;y>=t-3 && y>=0;y--){
		if(temp[x][y]==0 && which_four0(x,y,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four0(x,y,player,temp)==1)
			count1++;
			
	}
	
	for(y=t+1;y<=t+3 && y<=14;y++){
		if(temp[x][y]==0 && which_four0(x,y,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four0(x,y,player,temp)==1)
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
int is_five1(int s,int t,int player,int Board[15][15])
{
	int n,k;
	int temp[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int count=0,x=s-1;
	
	while(x>=0 && temp[x][t]==player)
		count++,x--;
	x=s+1;
	while(x<=14 && temp[x][t]==player)
		count++,x++;
	
	if(count==4)
		return 1;
	if(count>4)
		return 2;
	else
		return 0;
}

//return:0-no 4; 1-half 4; 2-live 4
int which_four1(int s,int t,int player,int Board[15][15]){
	int i=1,count=0;//count 记录能成5的点的个数
	int temp[15][15];
	int n,k,x,y;
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	
	for(x=s-1;x>=s-4 && x>=0;x--){
		if(temp[x][t]==0 && is_five1(x,t,player,temp)>=1)
			count++;
	}
	
	for(x=s+1;x<=x+4 && x<=14;x++){
		if(temp[x][t]==0 && is_five1(x,t,player,temp)>=1)
			count++;
	}
	
	if(count>=2)
		return 2;
	else if(count==1)
		return 1;
	else
		return 0;
}

//return : 2-live 3; 1-half 3; 0-o.w.
int which_three1(int s,int t,int player,int Board[15][15]){
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int y=t,x;
	for(x=s-1;x>=s-3 && x>=0;x--){
		if(temp[x][y]==0 && which_four1(x,y,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four1(x,y,player,temp)==1)
			count1++;
	}
	
	for(x=s+1;x<=s+3 && x<=14;x++){
		if(temp[x][y]==0 && which_four1(x,y,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four1(x,y,player,temp)==1)
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
int is_five2(int s, int t,int player,int Board[15][15])
{
	int n,k;
	int temp[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int count=0,x=s-1,y=t-1;
	
	while(x>=0 && y>=0 && temp[x][y]==player)
		count++,x--,y--;
	y=t+1;
	x=s+1;
	while(x<=14 && y<=14 && temp[x][y]==player)
		count++,x++,y++;
	
	if(count==4)
		return 1;
	if(count>4)
		return 2;
	else
		return 0;
}

//return:0-no 4; 1-half 4; 2-live 4
int which_four2(int s,int t,int player,int Board[15][15]){
	int i=1,count=0;//count 记录能成5的点的个数
	int temp[15][15];
	int n,k,x,y;
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	
	for(x=s-1,y=t-1;x>=s-4 && x>=0 && y>=t-4 && y>=0;y--,x--){
		if(temp[x][y]==0 && is_five2(x,y,player,temp)>=1)
			count++;
	}
	
	for(x=s+1,y=t+1;x<=s+4 && x<=14 && y<=t+4 && y<=14;x++,y++){
		if(temp[x][y]==0 && is_five2(x,y,player,temp)>=1)
			count++;
	}
	
	if(count>=2)
		return 2;
	else if(count==1)
		return 1;
	else
		return 0;
}

//return : 2-live 3; 1-half 3; 0-o.w.
int which_three2(int s,int t,int player,int Board[15][15]){
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int x=s,y=t;
	for(x=s-1,y=t-1;x>=s-3 && x>=0 && y>=t-3 && y>=0;y--,x--){
		if(temp[x][y]==0 && which_four2(x,y,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four2(x,y,player,temp)==1)
			count1++;
	}
	
	for(x=s+1,y=t+1;x<=14 && x<=s+3 && y<=t+3 && y<=14;y++,x++){
		if(temp[x][y]==0 && which_four2(x,y,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four2(x,y,player,temp)==1)
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
int is_five3(int s, int t,int player,int Board[15][15])
{
	int n,k;
	int temp[15][15];
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int count=0,x=s+1,y=t-1;
	
	while(x<=14 && y>=0 && temp[x][y]==player)
		count++,x++,y--;
	y=t+1;
	x=s-1;
	while(x>=0 && y<=14 && temp[x][y]==player)
		count++,x--,y++;
	
	if(count==4)
		return 1;
	if(count>4)
		return 2;
	else
		return 0;
}

//return:0-no 4; 1-half 4; 2-live 4
int which_four3(int s,int t,int player,int Board[15][15]){
	int i=1,count=0;//count 记录能成5的点的个数
	int temp[15][15];
	int n,k,x,y;
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	
	for(x=s+1,y=t-1;x<=s+4 && x<=14 && y>=t-4 && y>=0;y--,x++){
		if(temp[x][y]==0 && is_five3(x,y,player,temp)>=1)
			count++;
	}
	
	for(x=s-1,y=t+1;x>=s-4 && x>=0 && y<=t+4 && y<=14;x--,y++){
		if(temp[x][y]==0 && is_five3(x,y,player,temp)>=1)
			count++;
	}
	
	if(count>=2)
		return 2;
	else if(count==1)
		return 1;
	else
		return 0;
}

//return : 2-live 3; 1-half 3; 0-o.w.
int which_three3(int s,int t,int player,int Board[15][15]){
	int temp[15][15];
	int n,k,count2=0,count1=0;//记录能成活4,半和4的个数
	for(n=0;n<15;n++)
		for(k=0;k<15;k++)
			temp[n][k]=Board[n][k];//把这整体复制过来
	temp[s][t]=player;
	int x=s,y=t;
	for(x=s+1,y=t-1;x<=s+3 && x<=14 && y>=t-3 && y>=0;y--,x++){
		if(temp[x][y]==0 && which_four3(x,y,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four3(x,y,player,temp)==1)
			count1++;
	}
	
	for(x=s-1,y=t+1;x>=0 && x>=s-3 && y<=t+3 && y<=14;y++,x--){
		if(temp[x][y]==0 && which_four3(x,y,player,temp)==2)
			count2++;
		else if(temp[x][y]==0 && which_four3(x,y,player,temp)==1)
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
int is_ban(int s,int t,int player,int Board[15][15]){
	int live[7];
	int half[7];
	int dead[7];
	int n;
	for(n=0;n<7;n++)
		live[n]=half[n]=dead[n]=0;	
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
	if(Board[s][t]!=0)
		return 1;
	else if(live[6]>0 || half[6]>0 || dead[6]>0)
		return 1;
	else if(live[4]>=2 || live[3]>=2)
		return 1;
	else //暂时每考虑双活四的特殊情况，明天再说把 1.4.0：45
		return 0;	
}




