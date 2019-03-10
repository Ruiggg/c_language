#include <stdio.h>

struct loc{
	int i;
	int j;
};
int which_four1(struct loc a,struct loc b,int player,int Board[15][15]);
int is_five2(struct loc a,struct loc b,int player,int Board[15][15]);
int which_two1(struct loc a,struct loc b,int player,int Board[15][15]);
int main(){
		int array[15][15]={{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  					{1, 0, 0, 0, 0, 2, 2, 1, 1, 0, 2, 0, 0, 0, 0}, 
  					{0, 0, 0, 0, 1, 1, 2, 0, 0, 2, 1, 0, 0, 0, 0}, 
  					{0, 0, 0, 0, 1, 1, 1, 2, 1, 0, 2, 0, 1, 0, 0}, 
  					{0, 0, 0, 0, 1, 2, 1, 2, 2, 1, 0, 2, 2, 0, 0}, 
  					{0, 0, 0, 0, 2, 0, 1, 1, 1, 1, 2, 0, 1, 0, 0},
  					{1, 0, 0, 0, 0, 1, 1, 1, 1 ,2, 0, 0, 0, 0, 0}, 
  					{1, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 0}, 
  					{2, 0, 0, 0, 0, 2, 0, 1, 2, 0, 0, 0, 0, 0, 0},
  					{0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 0}, 
  					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  					{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	int s,t,player=1;
	struct loc x; 
	printf("enter 2 number:");
	scanf("%d%d",&x.i,&x.j);
	printf("Value=%d\n",is_five2(x,x,player,array));
}
//double half four:3  live four:2   half four:1   else:0
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
//左上-右下
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

