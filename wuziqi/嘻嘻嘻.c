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

