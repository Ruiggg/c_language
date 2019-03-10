#include <stdio.h>
#include "statement.h"
#define SIZE 15
int main(){
	int BBB[15][15]={{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			 {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  	{0, 0, 0, 0, 0, 2, 2, 1, 1, 0, 2, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 1, 2, 0, 0, 
    2, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 2, 0, 1, 0, 0}, {0, 0, 
    0, 0, 0, 2, 1, 2, 2, 1, 0, 2, 2, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 2, 
    0, 1, 0, 0}, {0, 0, 0, 0, 2, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 
    0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 2, 0, 1, 2, 0, 0, 0, 0, 
    0, 0}, {0, 0, 0, 0, 2, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0}, {
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	struct loc cnm={12,11};
	int n,score_of_candt,first=1,t=1,step=3,deep=1;
		score_of_candt=evaluate(first,t,step,deep-1,cnm,BBB);
	printf("%d\n",score_of_candt);
	
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
			return -99999999;
		else if(t==2 && first==0)
			return 99999999;
	}else if(is_to_win(candt.i,candt.j,temp,t) /*&& !is_to_win(candt.i,candt.j,temp,anti)*/){
		if(t==1 && first==1)//人先走且t是黑棋——t是人的棋
			return -99999998;
		else if(t==1 && first==0)
			return 99999998;
		else if(t==2 && first==1)
			return -99999998;
		else if(t==2 && first==0)
			return 99999998;
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
		else if(live[4]>=1 && live[3]>=1)
			return 1;
		else if(half[4]>=1 && live[3]>=1)
			return 1;
		else 
			return 0; 
	}
	else if(player==1){
		if(live[4]>=1 && live[3]>=1)
			return 1;
		else if(half[4]>=1 && live[3]>=1)
			return 1;
		else 
			return 0; 
	}	
}

int already_five(int s,int t,int Board[15][15],int player)
{			
	if(is_five0(s,t,player,Board) || is_five1(s,t,player,Board) || is_five2(s,t,player,Board) || is_five3(s,t,player,Board))
		return 1;
	else
		return 0;	
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
	else if((m=which_four0(s,t,player,Board))==3){
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
	else if((m=which_four1(s,t,player,Board))==3){
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
	else if((m=which_four2(s,t,player,Board))==3){
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
	else if((m=which_four3(s,t,player,Board))==3){
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
	
	int count_lk=1;//为了区分活四和双冲四，需要看连起来的棋子个数
	x=s,y=t-1;
	while(y>=0 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,y--;}
	i=1;
	x=s,y=t+1;
	while(y<=14 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,y++;}
	
	
	for(y=t-1;y>=t-4 && y>=0;y--){
		if(temp[s][y]==0 && is_five0(s,y,player,temp)>=1)
			count++;
	}
	
	for(y=t+1;y<=t+4 && y<=14;y++){
		if(temp[s][y]==0 && is_five0(s,y,player,temp)>=1)
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
	
	int count_lk=1;//为了区分活四和双冲四，需要看连起来的棋子个数
	x=s-1,y=t;
	while(x>=0 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,x--;}
	i=1;
	x=s+1,y=t;
	while(x<=14 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,x++;}
	
	
	for(x=s-1;x>=s-4 && x>=0;x--){
		if(temp[x][t]==0 && is_five1(x,t,player,temp)>=1)
			count++;
	}
	
	for(x=s+1;x<=x+4 && x<=14;x++){
		if(temp[x][t]==0 && is_five1(x,t,player,temp)>=1)
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
	
	int count_lk=1;//为了区分活四和双冲四，需要看连起来的棋子个数
	x=s-1,y=t-1;
	while(x>=0 && y>=0 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,x--,y--;}
	i=1;
	x=s+1,y=t+1;
	while(y<=14 && x<=14 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,x++,y++;}
	
	
	for(x=s-1,y=t-1;x>=s-4 && x>=0 && y>=t-4 && y>=0;y--,x--){
		if(temp[x][y]==0 && is_five2(x,y,player,temp)>=1)
			count++;
	}
	
	for(x=s+1,y=t+1;x<=s+4 && x<=14 && y<=t+4 && y<=14;x++,y++){
		if(temp[x][y]==0 && is_five2(x,y,player,temp)>=1)
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
	
	int count_lk=1;//为了区分活四和双冲四，需要看连起来的棋子个数
	x=s+1,y=t-1;
	while(x<=14 && y>=0 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,x++,y--;}
	i=1;
	x=s-1,y=t+1;
	while(x>=0 && y<=14 && i<=5 && Board[x][y]==player)
		{count_lk++,i++,x--,y++;}
	
	
	for(x=s+1,y=t-1;x<=s+4 && x<=14 && y>=t-4 && y>=0;y--,x++){
		if(temp[x][y]==0 && is_five3(x,y,player,temp)>=1)
			count++;
	}
	
	for(x=s-1,y=t+1;x>=s-4 && x>=0 && y<=t+4 && y<=14;x--,y++){
		if(temp[x][y]==0 && is_five3(x,y,player,temp)>=1)
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

