#define XWIN 1
#define OWIN -1
#define TIE 0

int minmaxvalue(int *, int );
int max_value(int *);
int min_value(int *);
int minmaxvalueab(int *, int , int , int );
int max_valueab(int *, int , int );
int min_valueab(int *, int , int );
float minmaxvaluest(int *, int , int );
float max_valuest(int *, int );
float min_valuest(int *, int );

int minmax_tictactoe(int *board, int turn)
{ 
	//put your code here:
	//it must return X(1), O(2) or NONE(0) for tie.
	//use the function game_status(board), to evaluate a board
	//it returns X(1) if X wins, O(2) if O wins or NONE(0) if tie or game is not finished
	//the program will keep track of the number of boards evaluated
	//int result = game_status(board);
	int result = minmaxvalue(board,turn);
	if(result==XWIN)
		{result=X;}
	else if(result==OWIN)
		{result=O;}
	else
		{result=NONE;}
	return result;	
}

int minmaxvalue(int *board, int turn)
{
	int result = game_status(board);
	if(result==X)
		{result=XWIN;}
	else if(result==O)
		{result=OWIN;}
	else
		{result=TIE;}

	if(result != TIE)
	{
		return result;
	}
	bool complete = true;
	for(int i=0;i<9;i++)
	{
		if(board[i]==NONE)
		{
			complete = false;
		}
	}
	if(complete == true)
	{
		return TIE;
	}
	if(turn == X)
	{
		return max_value(board);
	}
	if(turn == O)
	{
		return min_value(board);
	}

	return TIE;
}

int max_value(int *board)
{
	int v = -10;
	int curv;
	for(int i=0;i<9;i++)
	{
		if(board[i]==NONE)
		{
			board[i] = X;
			curv = minmaxvalue(board,O);
			board[i] = NONE;
			if(curv > v)
				{v = curv;}
		}
	}
	return v;
}

int min_value(int *board)
{
	int v = 10;
	int curv;
	for(int i=0;i<9;i++)
	{
		if(board[i]==NONE)
		{
			board[i] = O;
			curv = minmaxvalue(board,X);
			board[i] = NONE;
			if(curv < v)
				{v = curv;}
		}
	}
	return v;
}

int abprun_tictactoe(int *board, int turn)
{ 
	//put your code here:
	//it must return X(1), O(2) or NONE(0) for tie.
	//use the function game_status(board), to evaluate a board
	//it returns X(1) if X wins, O(2) if O wins or NONE(0) if tie or game is not finished
	//the program will keep track of the number of boards evaluated
	//int result = game_status(board);
	int result = minmaxvalueab(board,turn,-10,10);
	if(result==XWIN)
		{result=X;}
	else if(result==OWIN)
		{result=O;}
	else
		{result=NONE;}
	return result;	
}

int minmaxvalueab(int *board, int turn, int a, int b)
{
	int result = game_status(board);
	if(result==X)
		{result=XWIN;}
	else if(result==O)
		{result=OWIN;}
	else
		{result=TIE;}

	if(result != TIE)
	{
		return result;
	}
	bool complete = true;
	for(int i=0;i<9;i++)
	{
		if(board[i]==NONE)
		{
			complete = false;
		}
	}
	if(complete == true)
	{
		return TIE;
	}
	if(turn == X)
	{
		return max_valueab(board,a,b);
	}
	if(turn == O)
	{
		return min_valueab(board,a,b);
	}

	return TIE;
}

int max_valueab(int *board, int a, int b)
{
	int v = -10;
	int curv;
	for(int i=0;i<9;i++)
	{
		if(board[i]==NONE)
		{
			board[i] = X;
			curv = minmaxvalueab(board,O,a,b);
			board[i] = NONE;
			if(curv == XWIN)
				{return XWIN;}
			if(curv > v)
				{v = curv;}
			if(v >= b)
				{return v;}
			if(v > a)
				{a = v;}
		}
	}
	return v;
}

int min_valueab(int *board, int a, int b)
{
	int v = 10;
	int curv;
	for(int i=0;i<9;i++)
	{
		if(board[i]==NONE)
		{
			board[i] = O;
			curv = minmaxvalueab(board,X,a,b);
			board[i] = NONE;
			if(curv == OWIN)
				{return OWIN;}
			if(curv < v)
				{v = curv;}
			if(v <= a)
				{return v;}
			if(v < b)
				{b = v;}

		}
	}
	return v;
}

float st_tictactoe_win(int *board, int turn)
{
	//put your code here:
	//it must return a float value between 0 and 1
	//the error margin is +/- 1%
	float probability = minmaxvaluest(board, turn, turn);
	return probability;
}

float st_tictactoe_winortie(int *board, int turn)
{
	//put your code here:
	//it must return a float value between 0 and 1
	//the error margin is +/- 1%
	int otherturn;
	if(turn==X)
		{otherturn=O;}
	else
		{otherturn=X;}
	float probability = minmaxvaluest(board,turn,otherturn);
	probability = 1.00-probability;
	return probability;
}


float minmaxvaluest(int *board, int turn, int originalturn)
{
	int result = game_status(board);
	if(result==originalturn)
		{return 1;}
	else if(result!=0)
		{return 0;}

	bool complete = true;
	for(int i=0;i<9;i++)
	{
		if(board[i]==NONE)
		{
			complete = false;
		}
	}
	if(complete == true)
	{
		return 0;
	}
	if(turn == X && originalturn == X)
	{
		return max_valuest(board,originalturn);
	}
	if(turn == O && originalturn == X)
	{
		return min_valuest(board,originalturn);
	}
	if(turn == O && originalturn == O)
	{
		return max_valuest(board,originalturn);
	}
	if(turn == X && originalturn == O)
	{
		return min_valuest(board,originalturn);
	}

	return 0;
}


float max_valuest(int *board, int originalturn)
{
	int count=0,nextturn;
	float v=-10,probability=0,curv;
	if(originalturn==X)
		{nextturn=O;}
	else
		{nextturn=X;}
	for(int i=0;i<9;i++)
	{
		if(board[i]==NONE)
		{
			board[i] = originalturn;
			curv = minmaxvaluest(board,nextturn,originalturn)/9.00;
			board[i] = NONE;
			if(curv > v)
				{v = curv;}
			probability += curv;
		}
		else
			{count++;}
	}
	probability += count*v;
	return probability;
}

float min_valuest(int *board, int originalturn)
{
	int count=0,thisturn;
	float v=10,probability=0,curv;
	if(originalturn==X)
		{thisturn=O;}
	else
		{thisturn=X;}
	for(int i=0;i<9;i++)
	{
		if(board[i]==NONE)
		{
			board[i] = thisturn;
			curv = minmaxvaluest(board,originalturn,originalturn)/9.00;
			board[i] = NONE;
			if(curv < v)
				{v = curv;}
			probability += curv;
		}
		else
			{count++;}
	}
	probability += count*v;
	return probability;
}



