#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

#define NONE 0
#define X 1
#define O 2
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define NORMAL  "\x1b[0m"


void set_board(int *, char *);
void print_board(int *);
char *legend(int );
char simbol(int );
void set_cell(int *,int ,int ,int );
int get_cell(int *, int ,int );
int game_status(int *board);
int explored ;

#include "student_code.c"

bool run_experiment(char *board, int next, int win, int gmme, int gabe, float probw, float probwot);

int main(int n, char **args)
{
	
	char board1[] = "O X"
                    "XXO"
                    "OX ";
	int next1=X;
	int win1=X;
	int mme1=4;
	int abe1=2;
	float pw1=.8889;
	float pwot1=1;

	char board2[] = " OX"
                    "   "
                    "   ";
	int next2=X;
	int win2=X;
	int mme2=8232;
	int abe2=1250;
	float pw2=.6257;
	float pwot2=.8376;

	char board3[] = "OXX"
                    "OO "
                    "   ";
	int next3=X;
	int win3=O;
	int mme3=27;
	int abe3=9;
	float pw3=.0768;
	float pwot3=.0768;

	char board4[] = "O  "
                    " X "
                    "   ";
	int next4=X;
	int win4=NONE;
	int mme4=6812;
	int abe4=1535;
	float pw4=.5675;
	float pwot4=.7777;

	char board5[] = "XXO"
                    "OXX"
                    "OXO";
	int next5=X;
	int win5=X;
	int mme5=1;
	int abe5=1;
	float pw5=1;
	float pwot5=1;

	char board6[] = "OXX"
                    "XO "
                    "XOO";
	int next6=X;
	int win6=O;
	int mme6=1;
	int abe6=1;
	float pw6=0;
	float pwot6=0;
	

	char board7[] = "   "
                    "   "
                    "   ";


	int next7=X;
	int win7=NONE;
	int mme7=549946;
	int abe7=94978;
	float pw7=.5367;
	float pwot7=.7170;

	// add full and over 

	printf ("Board 1\n");
	bool exp1 = run_experiment(board1,next1,win1,mme1,abe1,pw1,pwot1);
	printf ("Board 2\n");
	bool exp2 = run_experiment(board2,next2,win2,mme2,abe2,pw2,pwot2);
	printf ("Board 3\n");
	bool exp3 = run_experiment(board3,next3,win3,mme3,abe3,pw3,pwot3);
	printf ("Board 4\n");
	bool exp4 = run_experiment(board4,next4,win4,mme4,abe4,pw4,pwot4);
	printf ("Board 5\n");
	bool exp5 = run_experiment(board5,next5,win5,mme5,abe5,pw5,pwot5);
	printf ("Board 6\n");
	bool exp6 = run_experiment(board6,next6,win6,mme6,abe6,pw6,pwot6);
	printf ("Board 7\n");
	bool exp7 = run_experiment(board7,next7,win7,mme7,abe7,pw7,pwot7);
	
	return exp1||exp2||exp3||exp4||exp5||exp6;
}

char *legend(int c)
{
	static char x[]="X";
	static char o[]="O";
	static char n[]="Nobody";
	if (c==X)
		return x;
	if (c==O)
		return o;
	return n;
}

void set_board(int *map, char *data)
{
	for (int y=0;y<9;y++)
	{
		map[y]=data[y]=='X'?X:data[y]=='O'?O:NONE;
	}
}

char simbol(int c)
{
	if (c==X)
		return 'X';
	if (c==O)
		return 'O';
	return ' ';
}

void print_board(int *board)
{
	printf("%c|%c|%c\n",simbol(board[0]),simbol(board[1]),simbol(board[2]));
	printf("-----\n");
	printf("%c|%c|%c\n",simbol(board[3]),simbol(board[4]),simbol(board[5]));
	printf("-----\n");
	printf("%c|%c|%c\n",simbol(board[6]),simbol(board[7]),simbol(board[8]));
}

void set_cell(int *b,int y,int x,int s)
{
	b[y*3+x]=s;
}

int get_cell(int *b, int y,int x)
{
	return b[y*3+x];
}

int game_status(int *board)
{
	//print_board(board);
	explored++;
	//diags
	if (board[0]==X && board[4]==X && board[8]==X) return X;
	if (board[2]==X && board[4]==X && board[6]==X) return X;

	//horizontal
	if (board[0]==X && board[1]==X && board[2]==X) return X;
	if (board[3]==X && board[4]==X && board[5]==X) return X;
	if (board[6]==X && board[7]==X && board[8]==X) return X;
	
	//vertical
	if (board[0]==X && board[3]==X && board[6]==X) return X;
	if (board[1]==X && board[4]==X && board[7]==X) return X;
	if (board[2]==X && board[5]==X && board[8]==X) return X;

	//diags
	if (board[0]==O && board[4]==O && board[8]==O) return O;
	if (board[2]==O && board[4]==O && board[6]==O) return O;

	//horizontal
	if (board[0]==O && board[1]==O && board[2]==O) return O;
	if (board[3]==O && board[4]==O && board[5]==O) return O;
	if (board[6]==O && board[7]==O && board[8]==O) return O;
	
	//vertical
	if (board[0]==O && board[3]==O && board[6]==O) return O;
	if (board[1]==O && board[4]==O && board[7]==O) return O;
	if (board[2]==O && board[5]==O && board[8]==O) return O;

	return NONE;//tie or unfinished
}

bool run_experiment(char *board, int next, int win, int gmme, int gabe, float probw, float probwot)
{
	int b[9];
	set_board(b,board);
	print_board(b);
	explored = 0;
	int wmm = minmax_tictactoe(b,next);
	int mme=explored;
	explored = 0;
	int wabp = abprun_tictactoe(b,next);
	int abpe=explored;
	explored = 0;
	float prob_win = st_tictactoe_win(b,next);
	explored = 0;
	float prob_winortie = st_tictactoe_winortie(b,next);
	explored = 0;
	
	printf ("%s moves Result :\n- MIN-MAX: %s wins ",legend(next),legend(wmm));
	if (wmm!=win)
		printf ("(%sFail%s)",RED,NORMAL);
	else
		printf ("(%sPass%s)",GREEN,NORMAL);
	printf(" board explored %d",mme);
	if (mme!=gmme)
		printf ("(%sFail%s)",RED,NORMAL);
	else
		printf ("(%sPass%s)",GREEN,NORMAL);
	
	printf ("\n- ALPHA-BETA: %s wins ",legend(wabp));
	if (wabp!=win)
		printf ("(%sFail%s)",RED,NORMAL);
	else
		printf ("(%sPass%s)",GREEN,NORMAL);
	printf(" board explored %d",abpe);
	if (abpe>gabe)
		printf ("(%sFail%s)",RED,NORMAL);
	else
		printf ("(%sPass%s)",GREEN,NORMAL);
	
	printf ("\n- Stochastic : %2.2f%\% probability of winning",prob_win*100);
	if (prob_win<probw-.01 || prob_win>probw+.01 )
		printf ("(%sFail%s), ",RED,NORMAL);
	else
		printf ("(%sPass%s), ",GREEN,NORMAL);

	printf ("%2.2f%\% probability of not losing",prob_winortie*100);
	if (prob_winortie<probwot-.01 || prob_winortie>probwot+.01 )
		printf ("(%sFail%s)",RED,NORMAL);
	else
		printf ("(%sPass%s)",GREEN,NORMAL);
	printf("\n");
	printf("\n");
	return !(wmm==win && mme==gmme && wabp==win && abpe<=gabe);
}