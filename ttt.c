#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>

int evaluate_game(char char board[][9], int s)
{
	for(int i=1;i<10;i++)
	{
		
	}

}

int analyze_board(char *node, int side)
{	
	//check win on rows for X
	if(node[0]==side&&node[1]==side&&node[2]==side||
		node[3]==side&&node[4]==side&&node[5]==side||
		node[6]==side&&node[7]==side&&node[8]==side)
		return 1;

	//check win on columns for X
	if(node[0]==side&&node[3]==side&&node[6]==side||
		node[1]==side&&node[4]==side&&node[7]==side||
		node[2]==side&&node[5]==side&&node[8]==side)
		return 1;

	//check win diagonals for X
	if(node[0]==side&&node[4]==side&&node[8]==side||
		node[2]==side&&node[4]==side&&node[6]==side)
		return 1;

	//check win on rows for O
	if(node[0]==-side&&node[1]==-side&&node[2]==-side||
	node[3]==-side&&node[4]==-side&&node[5]==-side||
	node[6]==-side&&node[7]==-side&&node[8]==-side)
		return -1;

	//check win on columns for O
	if(node[0]==-side&&node[3]==-side&&node[6]==-side||
		node[1]==-side&&node[4]==-side&&node[7]==-side||
		node[2]==-side&&node[5]==-side&&node[8]==-side)
		return -1;

	//check win diagonals for O
	if(node[0]==-side&&node[4]==-side&&node[8]==-side||
		node[2]==-side&&node[4]==-side&&node[6]==-side)
		return -1;

	//check if any square is empty, if true game is still in progress
	for(int i=0;i<9;i++)
		if(node[i]==0)
			return -2;

	//game is a draw, no wins and board full
	return 0;
}

int negamax(char *node, int depth, int side, int top)
{
	int cb = analyze_board(node, side);

	if(depth == 0 || cb != -2)
		return cb;

	int bestScore = -2;
	int bestMove = -2;
	int v;

	for(int i=0;i<9;i++)
	{
		if(node[i] != 0)
			continue;

		node[i] = side;
		v = -negamax(node, depth - 1, -side, 0);
		node[i] = 0;

		if(v >= bestScore)
		{
			bestScore = v;
			bestMove = i;
		}		
	}

	if(top)
		return bestMove;
	else
		return bestScore;
}

// get the best move depth = 9
int get_move(char *node, int side)
{
	return negamax(node, 9, side, 1);
}

int game_over(char *board)
{
	if(analyze_board(board, 1)>-2)
		return 1;
	else
		return 0;
}

void print_board(char board[][9], char *symbols)
{

	int row = 0, col = 0, c_count = 0, r_count = 0;
	for(int i=1;i<10;i++)
	{
		col = 0;
		
		col = c_count * 16;
		for(int j=0;j<9;j++)
		{
			if(j!=0&&j!=3&&j!=6&&j!=9) mvaddch(row, col, '|');

			col += 2;
			mvaddch(row, col, symbols[board[i][j]+1]);
			col += 2;

			if(j==2||j==5||j==8)
			{
				row++;
				col = c_count * 16;
				move(row, col);
				if(j!=8){ addstr("-------------"); row++; }
			}
		}
		c_count++;

		if(c_count==3)
		{
			c_count = 0;
			r_count++;
		}

		row = r_count * 7;
	}
}

static void finish(int sig)
{
    endwin();

    exit(0);
}

int main()
{
	char board[10][9];

	char win_msg[3][20] = {"Player O wins!\n\n", "Game is a draw!\n\n", "Player X wins!\n\n"};
	char symbols[3] = {'o', ' ', 'x'};

	for(int i=0;i<10;i++)
		memset(board[i], 0, 9);

	int side=1, pos;

	(void) signal(SIGINT, finish);      /* arrange interrupts to terminate */

    (void) initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    (void) echo();         /* echo input - in color */

	while(!game_over(board[0]))
	{
		print_board(board, symbols);
		refresh();
		//printf("Enter move: ");
		scanf("%d", &pos);

		board[0][pos] = side;

		if(game_over(board[0]))
			break;

		int move = get_move(board[0], -side);

		board[0][move] = -side;
	}

	print_board(board, symbols);

	printf("%s", win_msg[analyze_board(board[0], 1) + 1]);

	finish(0);

	return 0;
}