#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define width 7
#define height 6

//fills board with '.' character
//input: 
//	board: the game board
void  clearBoard(char board[width][height]) {
	//nested for-loop runs through every (x,y) in the board
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			board[x][y] = '.';
		}
	}
}

//prints the game board to the console
//input:
//	board: the game board, initialized
void printBoard(char board[width][height]) {
	printf("   ");
	//prints label row, i.e "A B C D E F G "
	for(int i = 0; i < width; i++) {
		printf("%c ", 65 + i);
	}
	printf("\n");
	//runs through board, printing each row (with 0,0 in the bottom left) and printing row num on left
	for(int y = height - 1; y >= 0; y--) {
		printf("%d  ", y + 1);
		for(int x = 0; x < width; x++) {
			printf("%c ", board[x][y]);
		}
		printf("\n");
	}
}

//checks if a given point is in the bounds of the game board
//input:
//	x: horizontal coordinate
//	y: vertical coordinate
//output: true if inbounds, false if out of bounds
_Bool inBounds(int x, int y) {
	return x >= 0 && x < width && y >= 0 && y < height;
}

//checks weather there's four or more contiguous pieces of the same type in a given spot
//input:
//	x: horizontal coordinate, 0 <= x < width
//	y: vertical coordinate, 0 <= y < height
//	board: the game board, initialized
//output: true if yes, false if no
_Bool checkSpot(char board[width][height], int x, int y) {
	int checkDir(char[width][height], int, int, int, int, char);
	if(board[x][y] != '.') {
		//runs through all directions represented by (dx, dy) vectors
		for(int dx = -1; dx <= 1; dx++) {
			for(int dy = -1; dy <= 1; dy++) {
				if(dx != 0 || dy != 0) {
					//checks if the contiguous tiles in (dx, dy) direction and in (-dx, -dy) drection (exact opposite) add to a connect four
					if (checkDir(board, x, y, dx, dy, board[x][y]) + checkDir(board, x, y, -dx, -dy, board[x][y]) - 1 >= 4) return 1;
				}
			}
		}
	}
	return 0;
}

//checks if the top piece of a row is part of four of more contiguous pieces
//input:
//	board: the game board, initialized
//	x: horizontal coordinate, 0 <= x < width
//returns: true if yes, false if no
_Bool checkCol(char board[width][height], int x) {
	int topPiece(char[width][height], int);
	//saves toppiece in given column
	int y = topPiece(board, x);
	return checkSpot(board, x, y);
}

//finds the number of contiguous pieces of the same type in a given direction
//input:
//	board: the game board, initialized
//	x: horizontal coordinate, 0 <= x < width
//	y: vertical coordinate, 0 <= y <  height
//	dx: step to be taken horizontally, included in {-1, 0, 1}
//	dy: step to be taken vertically, included in {-1, 0, 1}
//	p: the character being checked for
//returns: integer representing contiguous pieces
int checkDir(char board[width][height], int x, int y, int dx, int dy, char p) {
	int i = 0;
	//moving in (dx, dy) direction, keeps itterating until target is no longer p
	while(inBounds(x + dx * i, y + dy * i) && board[(x + dx * i)][(y + dy * i)] == p) {
		i++;
	}
	return i;
}

//puts a tile in the gameboard at lowest possible point given a column
//input:
//	board: the game board, initialized
//	x: horizontal coordinate, 0 <= x < width
//	tile: tile to be dropped
//returns: boolean representing weather the drop was successful
_Bool dropTile(char board[width][height], int x, char tile) {
	int topPiece(char[width][height], int);
	//saves y value of top piece
	int y = topPiece(board, x);
	if (y < height - 1) {
		board[x][y + 1] = tile;
		return 1;
	}
	return 0;
}

//runs a human input turn
//input:
//	board: the game board, initialized
//	tile: the tile the player is using
//returns: character representing slot the player placed into
char playerTurn(char board[width][height], char tile) {
	printBoard(board);
	//saves player input
	char inp[2];
	printf("Slot: ");
	scanf("%s", inp);
	
	if(inp[0] >= 'a' && inp[0] < 'a' + width) {
		inp[0] = 'A' + (inp[0] - 'a');
	}
	dropTile(board, inp[0] - 'A', tile);

	return inp[0];
}

//returns the top piece in a given column
//input:
//	board: the game board, initialized
//	x: horizontal coordinate, 0 <= x < width
//returns: int representing vertical coordinate of the top piece (-1 if column is empty)
int topPiece(char board[width][height], int x) {
	int y = height - 1;
	//runs from top of board down looking for first open spot
	while(y >= 0 && board[x][y] == '.') y--;
	return y;
}

//represents a potential move
struct Move {
	//horizontal coordinate
	int x;
	//contiguous pieces added to or blocked
	int comeup;
};

//finds the best move to play given any gamestate
//input:
//	board: the game board, initialized
//returns: int representing horizontal coordinate of found move
int findBest(char board[width][height]) {
	//saves running best move
	struct Move best = {0, 0};
	//runs through possible moves
	for(int x = 0; x < width; x++) {
		//y value of potential move
		int y = topPiece(board, x) + 1;
		//checking inbounds
		if(y < height) {
			//runs through all directions and checks the length of the streak of tiles (either type) that would beadded to or blocked by this move
			for(int dx = -1; dx <= 1; dx++) {
				for(int dy = -1; dy <= 1; dy++) {
					int cu = 0;
					char c4 = board[x + dx][y + dy];
					if(inBounds(x + dx, y + dy) && c4 != '.') 
						cu += checkDir(board, x + dx, y + dy, dx, dy, board[x + dx][y + dy]);
					if(inBounds(x - dx, y - dy) && board[x - dx][y - dy] != '.') {
						int cu2 = checkDir(board, x - dx, y - dy, -dx, -dy, board[x - dx][y - dy]);
						if(board[x - dx][y - dy] == c4) {
							cu += cu2;
						} else if (cu2 > cu) {
							cu = cu2;
						}
					}
					//checks if current move is best and saves it if so
					if(cu >= best.comeup) {
						best.x = x;
						best.comeup = cu;
					}
					
				}
			}
		}
	}
	return best.x;
}

//runs an AI turn
//input:
//	board: the game board, initialized
//	tile: the tile the AI is using
//returns: character representing slot the AI placed into
char AITurn(char board[width][height], char tile) {
	//saves char representing move and runs turn
	int move = findBest(board);
	dropTile(board, move, tile);
	return 'A' + move;
}

//runs the main game loop
//input:
// pFirst: user choice on taking first move, pFirst = 'y' || anything else
void runGame(char pFirst) {

	//creates board, uninitialized
	char board[width][height];
	//initializes board
	clearBoard(board);

	//creates pTurn variable to keep track of whos turn it is
	_Bool pTurn = pFirst == 'y' ? 1 : 0;
	//creates moves array of size width * height + 1, the max moves possible
	char moves[width * height + 1];
	//create move counter, to index moves
	int move = 0;
	//creates mark variable to keep track of the tile being used
	char mark = 'X';
	//creates gameActive varble to run while loop
	int gameActive = 1;
	//creates win variable to tell weather the game was a draw or now
	_Bool win;

	//runs while the game hasn't finished
	while(gameActive) {
		//runs turn and saves move to array
		if(pTurn) { moves[move] = playerTurn(board, mark); }
		else { moves[move] = AITurn(board, mark); }
		// printf("%c\n", mark);

		//checks last column placed into for winning
		if(checkCol(board, moves[move] - 'A')) {
			win = 1;
			gameActive = 0;
		//checks if enough moves have been played to make a draw
		} else if (move == width * height - 1) {
			win = 0;
			gameActive = 0;
		}

		//alternates turn and tile, itterates move
		mark = mark == 'X' ? 'O' : 'X';
		pTurn = pTurn == 1 ? 0 : 1;
		move++;
	}

	char winner[10];
	char player[10];

	//tell who won and who went first
	if(pFirst == 'y') {
		strcpy(player, "Human");
		strcpy(winner, move % 2 != 0 ? "Human" : "Computer");
	} else {
		strcpy(player, "Computer");
		strcpy(winner, move % 2 == 0 ? "Human" : "Computer");
	}
	if(move == width * height) strcpy(winner, "Draw");
	printBoard(board);

	//print post game message
	printf("\n--- Game Ovar ---\nWinner: %s\nFirst Player: %s\nMoves: ", winner, player);
	for(int i = 0; i < move; i++) {
		printf("%c ", moves[i]);
	}
	printf("\n");
}

int main() {


	printf("CONNECT FOUR\n\nDo you want to go first? (y/n): ");
	char pFirst;
	scanf("%c", &pFirst);
	printf("\n");

	runGame(pFirst);
	
	return 0;
}


