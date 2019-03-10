#ifndef _STATEMENT_H
#define _STATEMENT_H

struct point {
	int x;//记录纵坐标（1～15）
	int y;//记录横坐标（a~f）
	int is_quit;//记录是否退出：-1：不退出 1：退出
};  
struct loc {//记录坐标
	int i;//纵坐标1~15
	int j;//横坐标a~f
};

struct SingleInfo {//记录一个点的连珠信息
	int linkNum;//表示下上这个点，能成 活/半活/死 几
	int oppNum;//2：死 1：半活 0：活
};

struct SingleScore {
	struct SingleInfo si[4];//记录一点的4个方向的连珠信息
	int score;//记录该点得分
};

struct loc_value {
	int x1;//纵坐标1～15
	int x2;//横坐标a~f
	int Value;//得分
};
#define NUM 3 //记录每层取出几个点
void ai_set(int n,int i,int j);//ai下子函数

int cal_grade_point(int live[],int half[],int dead[]);//根据活i/半活i/死i 的信息计算得分

struct SingleInfo cal0(int s,int t,int player,int Board[15][15]);//横向扫描
struct SingleInfo cal1(int s,int t,int player,int Board[15][15]);//纵向扫描
struct SingleInfo cal2(int s,int t,int player,int Board[15][15]);//左下右上
struct SingleInfo cal3(int s,int t,int player,int Board[15][15]);//左上右下

void cal_score(int player,int first,struct SingleScore BoardScore[15][15]);
void cal_situation(int player,int Board[15][15],struct SingleScore BoardScore[15][15]);
void initgrade(struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15]);
void change_score(struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15],int Board[15][15],int player);

int is_five0(struct loc a,struct loc b,int player,int temp[15][15]);
int is_five1(struct loc a,struct loc b,int player,int temp[15][15]);
int is_five2(struct loc a,struct loc b,int player,int temp[15][15]);
int is_five3(struct loc a,struct loc b,int player,int temp[15][15]);

int which_four0(struct loc a,struct loc b,int player,int Board[15][15]);
int which_four1(struct loc a,struct loc b,int player,int Board[15][15]);
int which_four2(struct loc a,struct loc b,int player,int Board[15][15]);
int which_four3(struct loc a,struct loc b,int player,int Board[15][15]);

int which_three0(struct loc a,struct loc b,int player,int Board[15][15]);
int which_three1(struct loc a,struct loc b,int player,int Board[15][15]);
int which_three2(struct loc a,struct loc b,int player,int Board[15][15]);
int which_three3(struct loc a,struct loc b,int player,int Board[15][15]);

int which_two0(struct loc a,struct loc b,int player,int Board[15][15]);
int which_two1(struct loc a,struct loc b,int player,int Board[15][15]);
int which_two2(struct loc a,struct loc b,int player,int Board[15][15]);
int which_two3(struct loc a,struct loc b,int player,int Board[15][15]);

int is_ban(int s,int t,int player,int Board[15][15],struct SingleScore BoardScore[15][15]);
struct loc find_max(struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15]);//找到得分最高点
struct loc MaxMin(int first,int t,int deep,struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15],int Board[15][15]);//极大极小值搜索找到得分最高点


int no_five(int temp[15][15],int player);//如果全棋盘没有成五的点

void select_point(int t,int first,int num,struct loc candt[NUM],int Board[15][15],struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15]);//找出NUM个候选点
int evaluate(int first,int t,int step,int deep,struct loc candt,int Board[15][15]);//估值
int max_of_array(int score_of_candt[NUM]);
int min_of_array(int score_of_array[NUM]);
struct loc select_max_candt(struct loc candidate[NUM],int score_of_candt[NUM]);//找出候选点里得分最大的
int cal_board_score4ai(int Board[15][15],int t,int first);//计算当前棋盘的得分

int is_to_win(int s,int t,int Board[15][15],int player);
int already_five(int s,int t,int Board[15][15],int player);


struct loc max_of2d_array(int grade[15][15]);

#endif
