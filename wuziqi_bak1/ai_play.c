#define PLAYER 2
#define SIZE 15

extern int aRecordBoard2[SIZE][SIZE];

void ai_play(void)
{	
	int sign=1;
	int i,j;
		for(i=0;i<SIZE;i++)
			for(j=0;j<SIZE;j++)
				if(aRecordBoard2[i][j]==0 && sign==1)
				{	
					aRecordBoard2[i][j]=PLAYER;
					sign=0;
				}
					
		
}


