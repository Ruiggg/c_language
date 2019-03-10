
#define SIZE 15

extern int aRecordBoard2[SIZE][SIZE];
struct loc {
	int i;
	int j;
};

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
//ai下棋函数
struct point ai_play(int t)
{	
	struct point a;
	struct loc loc1,loc2,temp;
	
	cal_situation_ai(t);
	cal_score_ai();
	cal_score_man();
	
	loc1=find_max_man(t);
	loc2=find_max_ai(t);
	
	if(ai_BoardScore[loc2.i][loc2.j].score>man_BoardScore[loc.i][loc1.j].score){
		ai_set(t,loc1.i,loc1.j);
		a.x=loc1.i;
		a.y=loc1.j;
		a.is_quit=-1;
		return a;
	}	
	else{
		ai_set(t,loc2.i,loc2.j);		
		a.x=loc2.i;
		a.y=loc2.j;
		a.is_quit=-1;
		return a;
	} 		
}

//下子操作
void ai_set(int n,int i,int j)
{
	if(n==1 || n==2)
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
		
	cal_situation_ai();
	
	int s,t;
	for(s=0;s<SIZE;s++)
		for(t=0;t<SIZE;t++)
		{	
			int temp;
			for(n=0;n<4;n++)
			{
				temp=ai_BoardScore[s][t].SingleInfo[n].linkNum;
				
				if(ai_BoardScore[s][t].SingleInfo[n].oppNum==0)
					live[temp]++;
				else if(ai_BoardScore[s][t].SingleInfo[n].oppNum==1)
					half[temp]++;
				else if(ai_BoardScore[s][t].SingleInfo[n].oppNum==2)
					dead[temp]++;
			}	
			
			ai_BoardScore[s][t].score=cal_grade_point(live,half,dead);
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
				ai_BoardScore[s][t].SingleInfo[0]=cal0(s,t,player);
				ai_BoardScore[s][t].SingleInfo[1]=cal1(s,t,player);
				ai_BoardScore[s][t].SingleInfo[2]=cal2(s,t,player);
				ai_BoardScore[s][t].SingleInfo[3]=cal3(s,t,player);
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
		
	while(t>=0 && i<=5 && aRecordBoard2[s][t--]==player)
			count++,i++;
			
	if(t>=0){
		if(aRecordBoard2[s][t]==anti)
			a.oppNum++;
	}
	i=1;
	while(t<=14 && i<=5 && aRecordBoard2[s][t++]==player)
			count++,i++;
	
	if(t<=14){
		if(aRecordBoard2[s][t]==anti)
			a.oppNum++;
	}
	
	a.linkNum=count;
	return a;
}









