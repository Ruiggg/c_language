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
#define NUM 3
void ai_set(int n,int i,int j);
struct loc find_max_man(void);
struct loc find_max_ai(void);
//void cal_score_ai(int player,int first,struct SingleScore ai_BoardScore[15][15]);
int cal_grade_point(int live[],int half[],int dead[]);
//void cal_situation_ai(int player,int Board[15][15],struct SingleScore ai_BoardScore[15][15]);
struct SingleInfo cal0(int s,int t,int player,int Board[15][15]);
struct SingleInfo cal1(int s,int t,int player,int Board[15][15]);
struct SingleInfo cal2(int s,int t,int player,int Board[15][15]);
struct SingleInfo cal3(int s,int t,int player,int Board[15][15]);
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
struct loc find_max(struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15]);
struct loc MaxMin(int first,int t,int deep,struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15],int Board[15][15]);
struct loc MaxMin2(int first,int t,int deep,struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15],int Board[15][15]);
int max_ar(int score[15][15]);
int min_ar(int score[15][15]);
int evaluate2(int first,int t,int step,int deep,struct loc loc1,struct loc loc0,int Board[15][15]);
int re_grade_loc(int s,int t,int player,int Board[15][15]);
int be_baned(int s,int t,int player,int Board[15][15]);
int evaluate1(int first,int t,int step,int deep,struct loc candt,int Board[15][15]);
int no_five(int temp[15][15],int player);

void select_point(int t,int first,int num,struct loc candt[NUM],int Board[15][15],struct SingleScore ai_BoardScore[15][15],struct SingleScore man_BoardScore[15][15]);
int evaluate(int first,int t,int step,int deep,struct loc candt,int Board[15][15]);
int max_of_array(int score_of_candt[NUM]);
int min_of_array(int score_of_array[NUM]);
struct loc select_max_candt(struct loc candidate[NUM],int score_of_candt[NUM]);
int cal_board_score4ai(int Board[15][15],int t,int first);

int is_to_win(int s,int t,int Board[15][15],int player);
int already_five(int s,int t,int Board[15][15],int player);

struct loc_value {
	int x1;
	int x2;
	int Value;
};
struct loc max_of2d_array(int grade[15][15]);
//int is_ban_man(int s,int t,int player,int Board[15][15]);
/*
#define FIVE 0
#define LIVE_FOUR 1
#define DOUBLE_DIE_FOUR 1
#define DIE_FOUR_LIVE_THREE 1
#define DOUBLE_LIVE_THREE 2
#define DIE_LIVE_THREE 3
#define DIE_FOUR 4
#define LOW_DIE_FOUR 5
#define SINGLE_LIVE_THREE 6
#define JUMP_LIVE_THREE 7
#define DOUBLE_LIVE_TWO 8
#define LIVE_TWO 9
#define LOW_LIVE_TWO 10
#define DIE_THREE 11
#define DIE_TWO 12
*/
