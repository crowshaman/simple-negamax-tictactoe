#include <stdio.h>
#include <string.h>

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

void print_board(char board[][9])
{
	printf("\n\n");
	int row = 0;
	for(int i=0;i<10;i++)
	{

		row = 0;
		for(int j=1;j<10;j++)
		{
			if(board[i][j-1]==1) printf(" x "); else if(board[i][j-1]==-1) printf(" o "); else printf("   ");

			if(j%3==0&&j!=0&&j!=9) 
			{
				if(row==0) printf("\t 0 | 1 | 2");
				if(row==1) printf("\t 3 | 4 | 5");

				printf("\n-----------\t-----------\n");
				row++;
			}

			else if(j!=9)	printf("|");
		}

		if(row==2) printf("\t 6 | 7 | 8");
	}
	
	printf("\n\n");
}

int main()
{
	char board[10][9];

	char win_msg[3][20] = {"Player O wins!\n\n", "Game is a draw!\n\n", "Player X wins!\n\n"};

	memset(board[0], 0, 9);

	int side=1, pos;

	while(!game_over(board[0]))
	{
		print_board(board);
		printf("Enter move: ");
		scanf("%d", &pos);

		board[0][pos] = side;

		if(game_over(board[0]))
			break;

		int move = get_move(board[0], -side);

		board[0][move] = -side;
	}

	print_board(board);

	printf("%s", win_msg[analyze_board(board[0], 1) + 1]);

	return 0;
}