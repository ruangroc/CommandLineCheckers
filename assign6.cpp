/*************************************************************************************
 * Program Filename: assign6.cpp
 * Author: Anita Ruangrotsakun
 * Date: 15 March 2018
 * Description: allows two users to play checkers
 * Input: executable and board dimensions (8x8, 10x10, or 12x12)
 * Output: prints to the screen
 * ***********************************************************************************/
#include <iostream>
#include <cstring>

using namespace std;

/*******************************************************************************
 * Function: check_8
 * Description: checks if board_size dimension is "8x8"
 * Parameters: char* board_size
 * Input: input must be a dynamic cstring
 * Output: must return an int
 * ***************************************************************************/
int check_8(char* board_size) {
	char eight[] = "8x8";
	bool flag = true;

	for (int i = 0; i < 3; i++) {
		if (board_size[i] != eight[i]) {
			flag = false;
			break;
		}
	}
	if (flag == true) {
		return 8;
	}
	else {
		return 0;
	}
}


/*******************************************************************************
 * Function: check_10
 * Description: checks if board_size dimension is "10x10"
 * Parameters: char* board_size
 * Input: input must be a dynamic cstring
 * Output: must return an int
 * ****************************************************************************/
int check_10(char* board_size) {
	char ten[] = "10x10";
	bool flag = true;

	for (int i = 0; i < 5; i++) {
		if (board_size[i] != ten[i]) {
			flag = false;
			break;
		}
	}

	if (flag == true) {
		return 10;
	}
	else {
		return 0;
	}
}


/*******************************************************************************
 * Function: check_12
 * Description: checks if board_size dimension is "12x12"
 * Parameters: char* board_size
 * Input: input must be a dynamic cstring
 * Output: must return an int
 * ****************************************************************************/
int check_12(char* board_size) {
	char twelve[] = "12x12";
	bool flag = true;

	for (int i = 0; i < 5; i++) {
		if (board_size[i] != twelve[i]) {
			flag = false;
			break;
		}
	}
	if (flag == true) {
		return 12;
	}
	else {
		return 0;
	}
}


/********************************************************************************
 * Function: check_size
 * Description: checks the dimensions given and returns a corresponding int
 * Parameters: char* board_size
 * Input: input must be a dynamic cstring
 * Output: must return an int
 * *****************************************************************************/
int check_size(char* board_size) {
	int size = 0;

	if (check_8(board_size) == 8) {
		return 8;
	}
	else if (check_10(board_size) == 10) {
		return 10;
	}
	else if (check_12(board_size) == 12) {
		return 12;
	}
	else {
		return 0;
	}
}


/*********************************************************************************
 * Function: print_board
 * Description: prints the board
 * Parameters: char** board, int rows, int cols
 * Input: must have access to the checkerboard and its dimensions (rows and cols)
 * Output: prints the board and pieces with color
 * ******************************************************************************/
void print_board(char** board, int rows, int cols) {
	if (cols == 11) {
		cols = 13;    //adjusting for extra index in top most row
	}
	if (cols == 13) {
		cols = 17;    //adjusting for extra indices in top most row
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (j == 0) {
				//prints left hand column labels (A-whatever)
				cout << " " << board[i][j];
			}	
			else if (i == 0) {
				if (j < 10) {
					cout << "  " << board[i][j] << " ";
				}
				//the following is for double digit coordinate labels
				else if (j == 10 || j == 12 || j == 14) {
	 				cout << " " << board[i][j];
				}
				else if (j == 11 || j == 13 || j == 15) {
					cout << board[i][j] << " ";
				}
			}
			else if ((board[i][j] == ' ') &&
				((i%2 == 0 && j%2 == 0) || (i%2 == 1 && j%2 == 1))) {
				cout << "|\033[37;47m " << board[i][j] << " ";
			}
			else if ((board[i][j] == ' ') && 
				((i%2 == 1 && j%2 == 0) || (i%2 == 0 && j%2 == 1))) {
				cout << "|\033[37;40m " << board[i][j] << " ";
			}
			else {
				if (board[i][j] == 'x' || board[i][j] == 'X') {
					cout << "|\033[31;40m " << board[i][j] << " ";
				}
				else if (board[i][j] == 'o' || board[i][j] == 'O') {
					cout << "|\033[37;40m " << board[i][j] << " ";
				} 
			}
			cout << "\033[0m";
		}
		cout << endl;
	}
}


/*********************************************************************************
 * Function: check_spaces
 * Description: checks for correct spacing of coordinates in path of travel cstring
 * Parameters: char* path
 * Input: input must be a dynamic cstring
 * Output: musr return a bool
 * ******************************************************************************/
bool check_spaces(char* path) {
	int len = strlen(path) + 1;
	int count = 0;

	for (int i = 0; i < len; i++) {
		if (path[i] == ' ') {
			count++;
		}
	}

	if (count == 0) {
		return false;
	}

	for (int i = 0; i < len; i++) {
		if (path[i] == ' ' && i == (len - 1)) {
			//checks if previous not a number and next not a space or null
			if ((path[i-1] < '0' || path[i-1] > '9')
			    || (path[i+1] != ' ' || path[i+1] != '\0')) {
				return false;
			}
		}
		else if (path[i] == ' ') {
			//checks if previous is a number and next is a letter
			if ((path[i-1] < '0' || path[i-1] > '9')
			    || (path[i+1] < 'A' || path[i+1] > 'Z')) {
				return false;
			}
		}
	}

	return true;
}


/***********************************************************************************
 * Function: valid_11
 * Description: checks for a valid coordinate for a 10x10 board
 * Parameters: char* path, int i (for index)
 * Input: input must be a dynamic cstring and an index
 * Output: must return a bool
 * *********************************************************************************/
bool valid_11(char* path, int i) {
	if ((i+2) < strlen(path) && path[i+2] != ' ') {
		if (path[i+1] != '1' || path[i+2] != '0') {
			return false;
		}
	}
	else {
		if (path[i+1] < '1' || path[i+1] > '9') {
			return false;
		}
	}

	return true;
}


/**********************************************************************************
 * Function: valid_13
 * Description: checks for a valid coordinate for a 12x12 board
 * Parameters: char* path, int i
 * Input: input must be a dynamic cstring and an index
 * Output; must return a bool
 * ********************************************************************************/
bool valid_13(char* path, int i) {
	if ((i+2) < strlen(path) && path[i+2] != ' ') {
		if (path[i+1] != '1' || (path[i+2] < '0' || path[i+2] > '2')) {
			return false;
		}
	}
	else {
		if (path[i+1] < '1' || path[i+1] > '9') {
			return false;
		}
	}

	return true;
}


/***********************************************************************************
 * Function: valid_input
 * Description: checks if user has entered a valid intended path of travel
 * Parameters: char* path, int rows
 * Input: input must be dynamic cstring and and int for number of indices to check
 * Output: must return a bool
 * *********************************************************************************/
bool valid_input(char* path, int rows) {	
	if (strlen(path) < 5) {     //need at least two coordinates
		return false;
	}

	if (check_spaces(path) == false) {
		return false;
	}

	for (int i = 0; i < strlen(path); i++) {
		//enter if path[i] is a letter
		if (path[i] >= 'A'  && path[i] <= (char) (rows + 63)) {
			if (rows == 9) {
				//checks if 1-8 after a letter
				if (path[i+1] < '1' || path[i+1] > '8') {
					return false;
				}
			}
			else if (rows == 11) {
				//checks if 1-9 or 10 after a letter
				if (valid_11(path, i) == false) {
					return false;
				}
			}
			else if (rows == 13) {
				//checks if 1-9 or 10-12 after a letter
				if (valid_13(path, i) == false)  {
					return false;
				}
			}
		} 
		else if (path[i] != ' ' && !(path[i] >= '0' && path[i] <= '9')) {
			return false;
		}
	}

	return true;
}


/**********************************************************************************
 * Function: num_tokens
 * Description: gets the number of subunits (coordiantes) in the path cstring
 * Parameters: char copy[]
 * Input: must have access to a static copy of the intended path of travel
 * Output: returns the number of tokens (returns an int)
 * *******************************************************************************/
int num_tokens(char* path) {
	char copy[30];
	memset(copy, '\0', 30);
	strcpy(copy, path);
	int count = 0;
	char delim[] = " ";
	char* token = strtok(copy, delim);

	while (token) {
		count++;
		token = strtok(NULL, delim);
	}
	delete token;

	return count;
}


/**********************************************************************************
 * Function: col_num
 * Description: returns the index for a 2 digit coordinate number
 * Parameters: char* token
 * Input: input must be a dynamic cstring
 * Output: must return an int
 * *******************************************************************************/
int col_num(char* token) {
	int num = 0;

	if (token[2] == '0') {
		return 10;
	}
	else if (token[2] == '1') {
		return 11;
	}
	else if (token[2] == '2') {
		return 12;
	}
}


/**********************************************************************************
 * Function: from_coord
 * Description: converts the cstring token into indices for a from coordinate
 * Parameters: char* t, int & from_row, int & from_col
 * Input: must have access to the coordinate, from_row, and from_col variables
 * Output: alters from_row and from_col
 * ********************************************************************************/
void from_coord(char* t, int & from_row, int & from_col) {
	char token[4];
	memset(token, '\0', 4);
	int i = 0;

	while (t[i] != '\0') {
		token[i] = t[i];
		i++;
	}

	if (strlen(token) == 2) {
		from_row = ((int) token[0] - 64);
		from_col = ((int) token[1] - 48);
	}
	else if (strlen(token) == 3) {
		from_row = ((int) token[0] - 64);
		from_col = col_num(token);
	}
}


/***********************************************************************************
 * Function: to_coord
 * Description: converts the cstring token into indices for a to coordinate
 * Parameters: char* t, int & to_row, int & to_col
 * Input: input must be a dynamic cstring and two ints
 * Output: alters to_row and to_col
 * ********************************************************************************/
void to_coord(char* t, int & to_row, int & to_col) {
	char token[4];
	memset(token, '\0', 4);
	int i = 0;

	while (t[i] != '\0') {
		token[i] = t[i];
		i++;
	}

	if (strlen(token) == 2) {
		to_row = ((int) token[0] - 64);
		to_col = ((int) token[1] - 48);
	}
	else if (strlen(token) == 3) {
		to_row = ((int) token[0] - 64);
		to_col = col_num(token);
	}
}


/*************************************************************************************
 * Function: moves_xO
 * Description: checks valid moves for an x (which is also half the moves for an O)
 * Parameters: char** board, int player, int from_row, int from_col, int to_row, int to_col
 * Input: must have access to the board and who the current player is, and other inputs must be the indices for from and to coordinates
 * Output: returns a bool
 * **********************************************************************************/
bool moves_xO(char** board, int player, int from_row, 
	      int from_col, int to_row, int to_col) {

	//1 row up, 1 col right
	if ((from_row-1 == to_row) && (from_col+1 == to_col)) {
		return true;
	} 
	//1 row up, 1 col left
	else if ((from_row-1 == to_row) && (from_col-1 == to_col)) {
		return true;
	} 
	//2 rows up, 2 cols right
	else if ((from_row-2 == to_row) && (from_col+2 == to_col)) {
		//check if an o can jump an x
		if (player == 0 && (board[from_row-1][from_col+1] == 'x'
		    || board[from_row-1][from_col+1] == 'X')) {
			return true;
		}
		//check if an x can jump an o
		else if (player == 1 && (board[from_row-1][from_col+1] == 'o'
			 || board[from_row-1][from_col+1] == 'O')) {
			return true;
		}
	}
	//2 rows up, 2 cols left
	else if ((from_row-2 == to_row) && (from_col-2 == to_col)) {
		//check if an o can jump an x
		if (player == 0 && (board[from_row-1][from_col-1] == 'x'
		    || board[from_row-1][from_col-1] == 'X')) {
			return true;
		}
		//check if an x can jump an o
		else if (player == 1 && (board[from_row-1][from_col-1] == 'o'
			 || board[from_row-1][from_col-1] == 'O')) {
			return true;
		}
	}

	return false;
}


/************************************************************************************
 * Function: moves_oX
 * Description: checks valid move for an o (which is also half of X moves)
 * Parameters: char** board, int player, int from_row, int from_col, int to_row, int to_col
 * Input: must have access to the board, know which player, and have the coordinate indices
 * Output: must return a bool
 * *********************************************************************************/
bool moves_oX(char** board, int player, int from_row,
	      int from_col, int to_row, int to_col) {

	//1 row down, 1 col right
	if ((from_row+1 == to_row) && (from_col+1 == to_col)) {
		return true;
	}
	//1 row down, 1 col left
	else if ((from_row+1 == to_row) && (from_col-1 == to_col)) {
		return true;
	}
	//2 rows down, 2 cols right
	else if ((from_row+2 == to_row) && (from_col+2 == to_col)) {
		//check if an o can jump an x
		if (player == 0 && (board[from_row+1][from_col+1] == 'x'
		    || board[from_row+1][from_col+1] == 'X')) {
			return true;
		}
		//check if an x can jump an o
		else if (player == 1 && (board[from_row+1][from_col+1] == 'o'
			 || board[from_row+1][from_col+1] == 'O')) {
			return true;
		}
	}
	//2 rows down, 2 cols left
	else if ((from_row+2 == to_row) && (from_col-2 == to_col)) {
		//check if an o can jump an x
		if (player == 0 && (board[from_row+1][from_col-1] == 'x'
		    || board[from_row+1][from_col-1] == 'X')) {
			return true;
		}
		//check if an x can jump an o
		else if (player == 1 && (board[from_row+1][from_col-1] == 'o'
			 || board[from_row+1][from_col-1] == 'O')) {
			return true;
		}
	}

	return false;
}


/************************************************************************************
 * Function: correct_piece
 * Description: checks if the player is moving one of their own pieces
 * Parameters: char** board, int player, int from_row, int from_col, int to_row
 * Input: must have access to the board, must know the index for whose turn it is, must know the from coordinate indices, and must know the to coordinate row
 * Output: must return a bool
 * ***********************************************************************************/
bool correct_piece(char** board, int player, int from_row, int from_col, int to_row) {
	char from_val = board[from_row][from_col];

	if (player == 0) {
		//checks o/O piece for player 0
		if (from_val != 'o' && from_val != 'O') {
			return false;
		}
		//checks o moves only forward (top to bottom)
		if (from_val == 'o' && to_row < from_row) {
			return false;
		}
	}
	else if (player == 1) {
		//checks x/X piece for player 1
		if (from_val != 'x' && from_val != 'X') {
			return false;
		}
		//checks x moves only forward (bottom to top)
		if (from_val == 'x' && to_row > from_row) {
			return false;
		}
	}

	return true;
}


/************************************************************************************
 * Function: correct_move
 * Description: checks for valid moves for a certain piece
 * Parameters: char** board, int player, int from_row, int from_col, int to_row, int to_col
 * Input: must have access to the board, know who the current player is, and know the from and to coordinates
 * Output: returns a bool
 * **********************************************************************************/
bool correct_move(char** board, int player, int from_row,
		  int from_col, int to_row, int to_col) {

	char from_val = board[from_row][from_col];

	if (from_val == 'o' && 
	    moves_oX(board,player,from_row,from_col,to_row,to_col) == false) {
		return false;
	}
	else if (from_val == 'x' && 
		moves_xO(board,player,from_row,from_col,to_row,to_col) == false) {
		return false;
	}
	else if ((from_val == 'O' || from_val == 'X') &&
		 (moves_xO(board,player,from_row,from_col,to_row,to_col) == false &&
		  moves_oX(board,player,from_row,from_col,to_row,to_col) == false)) {
		return false;
	}

	return true;
}


/**********************************************************************************
 * Function: check_move
 * Description: checks the validity of one move
 * Parameters: char** board, int player, int from_row, int from_col, int to_row, int to_col
 * Input: must have access to the board, know who the current player is, and have the from and to coordinates
 * Output: returns a bool
 * ********************************************************************************/
bool check_move(char** board, int player, int from_row,
		int from_col, int to_row, int to_col, bool multi_flag) {

	if (multi_flag == false && board[to_row][to_col] != ' ') {
		return false;
	}

	if ((from_row % 2 == 0 && from_col % 2 == 0) 
	    || (from_row % 2 == 1 && from_col %2 == 1)) {   //checking dark square
		return false;
	}

	if ((to_row % 2 == 0 && to_col % 2 == 0)
	    || (to_row % 2 == 1 && to_col % 2 == 1)) {     //checking dark square
		return false;
	}

	if (multi_flag == false && 
	    correct_piece(board, player, from_row, from_col, to_row) == false) {
		return false;
	}

	if (multi_flag == false) {
		if (correct_move(board, player, from_row, from_col, 
		    to_row, to_col) == false) {

			return false;
		}
	}
	else if (multi_flag == true) {
		if (moves_oX(board,player,from_row,from_col,to_row,to_col) == false &&
		    moves_xO(board,player,from_row,from_col,to_row,to_col) == false) {
			return false;
		}
	}

	return true;
}


/*********************************************************************************
 * Function: two_tokens
 * Description: gets the first two tokens of a cstring for the from and to coord indices
 * Parameters: char copy[], int & from_row, int & from_col, int & to_row, int & to_col
 * Input: must have access to the static copy of path and coordinate indices
 * Output: alters the indices
 * *******************************************************************************/
void two_tokens(char copy[], int & from_row, int & from_col, int & to_row, int & to_col){
	char delim[] = " ";
	char* token; 
	token = strtok(copy, delim);
	from_coord(token, from_row, from_col);
	token = strtok(NULL, delim);
	to_coord(token, to_row, to_col);
}


/***********************************************************************************
 * Function: valid_move
 * Description: checks if an intended path of travel is valid on the board
 * Parameters: char** board, int rows, int cols, char* path, int player
 * Input: must have access to the board and its dimensions, as well as intended path and current player
 * Output: returns a bool
 * *********************************************************************************/
bool valid_move(char** board, int rows, int cols, char* path, int player) {
	char copy[30];
	memset(copy, '\0', 30);
	strcpy(copy, path);

	int num_coords = num_tokens(path);
	int from_row, from_col, to_row, to_col;
	bool multi_flag = false;

	if (num_coords == 2) {
		two_tokens(copy, from_row, from_col, to_row, to_col);
		if (check_move(board, player, from_row, from_col, 
		    to_row, to_col, multi_flag) == false) {
			return false;
		}
	}
	else {
		multi_flag = true;
		two_tokens(copy, from_row, from_col, to_row, to_col);
		char delim[] = " ";

		for (int i = 0; i < ((num_coords/2)-1); i++) {
			char* token = strtok(NULL, delim);
			from_coord(token, from_row, from_col);
			token = strtok(NULL, delim);
			to_coord(token, to_row, to_col);

			if (check_move(board, player, from_row, from_col,
			    to_row, to_col, multi_flag) == false) {
				return false;
			}
		}
	}

	return true;
}


/*********************************************************************************
 * Function: inc_capture
 * Description: increments the count of captured pieces and removes the piece from the board
 * Parameters: char** board, int row, int col, int & x_captured, int & o_captured
 * Input: must have access to the the board and counts of captured pieces and the coordinates of the piece that was jumped
 * Output: alters the count of captured pieces and the board
 * *******************************************************************************/
void inc_capture(char** board, int row, int col, int & x_captured, int & o_captured) {
	if (board[row][col] == 'o') {
		o_captured++;
	}
	else if (board[row][col] == 'x') {
		x_captured++;
	}
	else if (board[row][col] == 'O') {
		o_captured += 2;
	}
	else if (board[row][col] == 'X') {
		x_captured += 2;
	}

	board[row][col] = ' ';
}


/***********************************************************************************
 * Function: capture
 * Description: checks if a piece has jumped another
 * Parameters: char** board, int fr, int fc, int tr, int tc, int & x_captured, int & o_captured
 * Input: must have access to the board, must know the indices for the from and to coordinates, and must have access to counts of captured pieces
 * Output: alters the board
 * *********************************************************************************/
void capture(char** board, int fr, int fc, int tr, int tc,
	     int & x_captured, int & o_captured) {

	//2 rows down, 2 cols right
	if ((fr+2 == tr) && (fc+2 == tc)) {
		inc_capture(board, (fr+1), (fc+1), x_captured, o_captured);
	}
	//2 rows down, 2 cols left
	else if ((fr+2 == tr) && (fc-2 == tc)) {
		inc_capture(board, (fr+1), (fc-1), x_captured, o_captured);
	}
	//2 rows up, 2 cols right
	else if ((fr-2 == tr) && (fc+2 == tc)) {
		inc_capture(board, (fr-1), (fc+1), x_captured, o_captured);
	}
	//2 rows up, 2 cols left
	else if ((fr-2 == tr) && (fc-2 == tc)) {
		inc_capture(board, (fr-1), (fc-1), x_captured, o_captured);
	}
}


/**************************************************************************************
 * Function: kinged
 * Description: kings a piece if it has reached the opposite end of the board and removes a piece from the count of captured pieces for the other player
 * Parameters: char** board, int to_row, int to_col, int & x_captured, int & o_captured, int_rows
 * Input: must have access to the board and its row length, the indices for the to coordinate, and the counts of x's and o's captured
 * Output: alters the board
 * ************************************************************************************/
void kinged(char** board, int to_row, int to_col,int & x_captured, 
	    int & o_captured, int rows) {

	if (to_row == 1 && board[to_row][to_col] == 'x') {
		board[to_row][to_col] = 'X';
		x_captured--;
	}
	else if (to_row == (rows-1) && board[to_row][to_col] == 'o') {
		board[to_row][to_col] = 'O';
		o_captured--;
	}
}


/**********************************************************************************
 * Function: single_move
 * Description: moves a piece on the board
 * Parameters: char** board, char copy[], int from_row, int from_col, int to_row, int to_col, int & x_captured, int & o_captured, int rows
 * Input: must have access to the board and its row length, the indices for the from and to coordinates, and counts for x's and o's captured
 * Ouput: alters the board
 * ********************************************************************************/
void single_move(char** board, char copy[], int from_row, int from_col, int to_row, 
		 int to_col, int & x_captured, int & o_captured, int rows) {

	char delim[] = " ";
	char* token; 

	token = strtok(copy, delim);
	from_coord(token, from_row, from_col);
	token = strtok(NULL, delim);
	to_coord(token, to_row, to_col);

	board[to_row][to_col] = board[from_row][from_col];
	board[from_row][from_col] = ' ';

	capture(board, from_row, from_col, to_row, to_col, x_captured, o_captured);

	kinged(board, to_row, to_col, x_captured, o_captured, rows);

	//delete [] token;
}


/*************************************************************************************
 * Function: copy_token
 * Description: copies what a token pointer is pointing to into an array
 * Parameters: char* t, char token[]
 * Input: must be a pointer to a token and a static array
 * Output: alters the array token
 * ***********************************************************************************/
void copy_token(char* t, char token[]) {
	int i = 0;

	while (t[i] != '\0') {
		token[i] = t[i];
		i++;
	}
}


/*************************************************************************************
 * Function: get_subcopy
 * Description: gets the subcopy for multi_moves to feed into single_move
 * Parameters: char copy[], char subcopy[], int index
 * Inputs: must have access to copy of path, the subcopy array, and index of for loop
 * Output: alters the array subcopy
 * **********************************************************************************/
void get_subcopy(char copy[], char subcopy[], int index) {
	char delim[] = " ";
	char* t1 = NULL;
	char* t2 = NULL;

	if (index == 0) {   //get first coord of copy
		t1 = strtok(copy, delim);
	}
	else {    //discard first pair(s) of coords
		t1 = strtok(copy, delim);
		for (int i = 0; i < (2*index); i++) {
			t1 = strtok(NULL, delim);
		}
	}
	t2 = strtok(NULL, delim);

	char token1[4];
	char token2[4];

	memset(token1, '\0', 4);
	memset(token2, '\0', 4);

	copy_token(t1, token1);
	copy_token(t2, token2);

	strncpy(subcopy, token1, strlen(token1));
	subcopy[strlen(subcopy)] = ' ';   //add space between coords
	strncat(subcopy, token2, strlen(token2));   //append token2 to subcopy

	t1 = NULL;
	t2 = NULL;
}


/************************************************************************************
 * Function: multi_moves
 * Description: makes sub-copies of path for single_move to operate one when the path holds more than one coordinate
 * Parameters: char** board, char copy[], int from_row, int from_col, int to_row, int to_col, int & x_captured, int & o_captured, int rows, char* path
 * Input: must have access to the board and its row length, the indices for the from and to coordinates, and counts for x's and o's captured
 * Output: alters the board
 * **********************************************************************************/
void multi_moves(char** board, char copy[], int from_row, int from_col, int to_row,
		 int to_col, int & x_captured, int & o_captured, int rows, char* path) {

	char subcopy[10];
	int num_coords = num_tokens(path);

	for (int i = 0; i < (num_coords/2); i++) {
		memset(subcopy, '\0', 10);
		char loop_copy[strlen(copy)+1];
		strcpy(loop_copy, copy);
		get_subcopy(loop_copy, subcopy, i);
		single_move(board, subcopy, from_row, from_col, to_row,
			    to_col, x_captured, o_captured, rows);
	}
}


/***********************************************************************************
 * Function: move_piece
 * Description: moves a piece on the board according to how many coordinates there are
 * Parameters: char** board, char* path, int rows, int & x_captured, int & o_captured
 * Inputs: must have access to the board and its row length, must have access to the path of travel, and must have access to counts of x's and o's captured
 * Outputs: alters values on the board
 * ********************************************************************************/
void move_piece(char** board, char* path, int rows, int & x_captured, int & o_captured) {
	char copy[20];
	strcpy(copy, path);
	int num_coords = num_tokens(path);
	int from_row, from_col, to_row, to_col;

	if (num_coords == 2) {
		single_move(board, copy, from_row, from_col, to_row, to_col, 
			    x_captured, o_captured, rows);
	}
	else {
		multi_moves(board, copy, from_row, from_col, to_row, to_col,
			    x_captured, o_captured, rows, path);
	}
}


/**************************************************************************************
 * Function: take_turn
 * Description: allows a player to move one of their pieces
 * Parameters: char** board, int rows, int cols, int & x_captured, int & o_captured, int player
 * Input: must have access to the board and its dimensions, as well as counts for the pieces captured and the index for the current player
 * Output: alters the board
 * ***********************************************************************************/
void take_turn(char** board, int rows, int cols, int & x_captured, 
		int & o_captured, int player) {

	char* path = new char[30];
	memset(path, '\0', 30);
	bool flag = false;

	while (flag == false) {
		cout << "Please enter the coordinates for the path of travel." << endl;
		cout << "A space should separate each coordinate." << endl;
		cout << "Repeat a coordinate if making more than one jump." << endl;
		cout << "Example: A1 B2 B2 C3" << endl;

		memset(path, '\0', 30);
		cin.get(path, 30, '\n');
		cin.ignore();
		cin.clear();

		if (valid_input(path, rows) == true) {
			if (valid_move(board, rows, cols, path, player) == true) {
				flag = true;
			}
		}
	} 

	move_piece(board, path, rows, x_captured, o_captured);
	delete [] path;
}


/************************************************************************************
 * Function: end_game
 * Description: checks if game should end yet
 * Parameters: char** board, int rows, int cols, int x_captured, int o_captured
 * Input: need access to the board, its row length, and counts for pieces captured
 * Output: returns a bool
 ***********************************************************************************/
bool end_game(char** board, int rows, int x_captured, int o_captured) {
	if (rows == 9 && (x_captured == 12 || o_captured == 12)) {
		return true;
	}
	else if (rows == 11 && (x_captured == 20 || o_captured == 20)) {
		return true;
	}
	else if (rows == 13 && (x_captured == 30 || o_captured == 30)) {
		return true;
	}

	return false;
}


/**********************************************************************************
 * Function: declare_winner
 * Description: declares who the winner is after comparing number of pieces captured
 * Parameters: int x_captured, int o_captured
 * Input: need the counts of pieces captured
 * Output: prints text to screen
 * ********************************************************************************/
void declare_winner(int x_captured, int o_captured) {
	if (x_captured > o_captured) {
		cout << endl << "Player O wins!" << endl;
	}
	else if (o_captured > x_captured) {
		cout << endl << "Player X wins!" << endl;
	}
}


/**********************************************************************************
 * Function: play_game
 * Description: facilitates the gameplay of checkers
 * Parameters: char** board, char* board_size
 * Input: must have access to the board and its dimensions
 * Output: alters the board
 * ********************************************************************************/
void play_game(char** board, char* board_size) {
	bool flag = false;
	int x_captured = 0;   //number of x's captured by player O
	int o_captured = 0;   //number of o's captured by player X
	int rows = 1 + check_size(board_size);
	int cols = 1 + check_size(board_size);

	while (flag == false) {
		for (int i = 0; i < 2; i++) {
			print_board(board, rows, cols);
			cout << endl << "-------------------------" << endl;
			if (i == 0) {
				cout  << "Player O's Turn!" << endl;
			}
			else if (i == 1) {
				cout  << "Player X's Turn!" << endl;
			}
			cout << "-------------------------" << endl << endl;

			take_turn(board, rows, cols, x_captured, o_captured, i);

			cout << endl << "-------------------------" << endl;
			cout << "Player O has " << x_captured << " x pieces" << endl;
			cout << "Player X has " << o_captured << " o pieces" << endl;
			cout << "-------------------------" << endl << endl;

			if (end_game(board, rows, x_captured, o_captured) == true) {
				flag = true;
				break;
			}
		}
	}
	
	declare_winner(x_captured, o_captured);
}


/******************************************************************************
 * Function: pieces_12
 * Description: initializes values for the checker pieces on a 12x12 board
 * Parameters: char** board
 * Input: must have access to the 12x12 checkerboard
 * Output: alters values in the array
 * ***************************************************************************/
void pieces_12(char** board) {
	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 13; j++) {
			if ((i%2 == 1 && j%2 == 0) || (i%2 == 0 && j%2 == 1)) {
				board[i][j] = 'o';
			}
			else {
				board[i][j] = ' ';
			}
		}
	}

	for (int i = 8; i < 13; i++) {
		for (int j = 1; j < 13; j++) {
			if ((i%2 == 1 && j%2 == 0) || (i%2 == 0 && j%2 == 1)) {
				board[i][j] = 'x';
			}
			else {
				board[i][j] = ' ';
			}
		}
	}
}


/*******************************************************************************
 * Function: coord_12
 * Description: sets up the coordinate labels and null rows for a 12x12 board
 * Parameters: char** board
 * Input: must have access to the 12x12 checkerboard
 * Output: alters values in the array
 * ****************************************************************************/
void coord_12(char** board) {
	for (int i = 6; i < 8; i++) {
		for (int j = 1; j < 13; j++) {
			board[i][j] = ' ';
		}
	}

	for (int i = 1; i < 13; i++) {
		board[i][0] = (char) (i + 64);
	}

	for (int j = 0; j < 16; j++) {
		if (j == 0) {
			board[0][j] = ' ';
		}
		else if (j < 10) {
			board[0][j] = (char) (j + 48);
		}
		else if (j == 10 || j == 12 || j == 13 || j == 14) {
			board[0][j] = '1';   //for double digit coordinate labels
		}
		else if (j == 11) {
			board[0][j] = '0';
		}
		else if (j == 15) {
			board[0][j] = '2';
		}
	}
}


/********************************************************************************
 * Function: pieces_10
 * Description: initializes values for the checker pieces on a 10x10 board
 * Parameters: char** board
 * Input: must have access to the 10x10 checkerboard
 * Output: alters values in the array
 * *****************************************************************************/
void pieces_10(char** board) {
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 11; j++) {
			if ((i%2 == 1 && j%2 == 0) || (i%2 == 0 && j%2 == 1)) {
				board[i][j] = 'o';
			}
			else {
				board[i][j] = ' ';
			}
		}
	}

	for (int i = 7; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			if ((i%2 == 1 && j%2 == 0) || (i%2 == 0 && j%2 == 1)) {
				board[i][j] = 'x';
			}
			else {
				board[i][j] = ' ';
			}
		}
	}
}


/*********************************************************************************
 * Function: coord_10
 * Description: sets up the coordinate labels and null rows for a 10x10 board
 * Parameters: char** board
 * Input: must have access to the 10x10 checkerboard
 * Output: alters values in the array
 * ******************************************************************************/
void coord_10(char** board) {
	for (int i = 5; i < 7; i++) {          //spaces for middle two rows
		for (int j = 1; j < 11; j++) {
			board[i][j] = ' ';
		}
	}

	for (int i = 1; i < 11; i++) {        //letters A-J for left most col
		board[i][0] = (char) (i + 64);
	}

	for (int j = 0; j < 12; j++) {
		if (j == 0 && j < 10) {       //space for (0,0)
			board[0][j] = ' ';
		}
		else if (j == 10) {           //this is the '1' for '10'
			board[0][j] = '1';
		}
		else if (j == 11) {           //this is the '0' for '10'
			board[0][j] = '0';
		}
		else {                        //otherwise, top most row gets numbers
			board[0][j] = (char) (j + 48);
		}
	}
}


/**********************************************************************************
 * Function: pieces_8
 * Description: initializes values for the checker pieces on an 8x8 board
 * Parameters: char** board
 * Input: must have access to the 8x8 checkerboard
 * Output: alters values within the array
 * *******************************************************************************/
void pieces_8(char** board) {
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 9; j++) {
			if ((i%2 == 1 && j%2 == 0) || (i%2 == 0 && j%2 == 1)) {
				board[i][j] = 'o';
			}
			else {
				board[i][j] = ' ';
			}
		}
	}

	for (int i = 6; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if ((i%2 == 1 && j%2 == 0) || (i%2 == 0 && j%2 == 1)) {
				board[i][j] = 'x';
			}
			else {
				board[i][j] = ' ';
			}
		}
	}
}


/**********************************************************************************
 * Function: coord_8
 * Description: sets up the coordinate labels and null rows for an 8x8 board
 * Parameters: char** board
 * Input: must have access to the 8x8 checkerboard
 * Output: initializes coordinate col and row and null rows
 * *******************************************************************************/
void coord_8(char** board) {
	for (int i = 4; i < 6; i++) {           //spaces for middle two rows
		for (int j = 1; j < 9; j++) {
			board[i][j] = ' ';
		}
	}

	for (int i = 1; i < 9; i++) {           //letters for left most col
		board[i][0] = (char) (i + 64);
	}

	for (int j = 0; j < 9; j++) {
		if (j == 0) {                    //space for (0,0)
			board[0][j] = ' ';
		}
		else {                           //top most row gets numbers
			board[0][j] = (char) (j + 48);
		}
	}
}


/**********************************************************************************
 * Function: set_board
 * Description: sets up the checkerboard for an 8x8, 10x10, or 12x12 board
 * Parameters: char** board, char* board_size
 * Input: must have access to the board and its size
 * Output: alters values in the checkerboard (initializes the array)
 * *******************************************************************************/
void set_board(char** board, char* board_size) {
	if (check_size(board_size) == 8) {
		pieces_8(board);
		coord_8(board);
	}
	else if (check_size(board_size) == 10) {
		pieces_10(board);
		coord_10(board);
	}
	else if (check_size(board_size) == 12) {
		pieces_12(board);
		coord_12(board);
	}
}


/**********************************************************************************
 * Function: create_board
 * Description: creates an 8x8, 10x10, or 12x12 board according to user's choice
 * Parameters: char* board_size
 * Input: must have the dimensions of the board the user wants to play on
 * Output: returns a pointer to the board
 * *******************************************************************************/
char** create_board(char* board_size) {
	if (check_size(board_size) == 8) {
		char** board = new char*[9];
		for (int i = 0; i < 9; i++) {
			board[i] = new char[9];
		}
		return board;
	}
	else if (check_size(board_size) == 10) {
		char** board = new char*[11];
		board[0] = new char[12];    //extra index because 2 chars in "10"
		for (int i = 1; i < 11; i++) {
			board[i] = new char[11];
		}
		return board;
	}
	else if (check_size(board_size) == 12) {
		char** board = new char*[13];
		board[0] = new char[16];   //extra indices for double digits (10,11,12)
		for (int i = 1; i < 13; i++) {
			board[i] = new char[13];
		}
		return board;
	}
}


/********************************************************************************
 * Function: check_arg
 * Description: checks the command line argument to see if it's a valid board size
 * Parameters: char* argv[1] 
 * Input: should be a dynamic cstring 
 * Output: returns a bool
 * ******************************************************************************/
bool check_arg(char* board_size) {
	if (strlen(board_size) == 0) {
		return false;
	}

	if (strlen(board_size) == 3 && check_size(board_size) == 8) {
		return true;
	}
	else if (strlen(board_size) == 5 && check_size(board_size) == 10) {
		return true;
	}
	else if (strlen(board_size) == 5 && check_size(board_size) == 12) {
		return true;
	}
	else {
		return false;
	}
}


/*********************************************************************************
 * Function: get_size
 * Description: gets the correct size option from user
 * Parameters: none
 * Input: none
 * Output: must return a dynamic cstring containing the board's dimensions
 * *******************************************************************************/
char* get_size() {
	bool flag = false;
	char* board_size = new char[6];
	char* input = new char[256];

	for (int i = 0; i < 6; i++) {
		board_size[i] = '\0';
	}

	for (int i = 0; i < 256; i++) {
		input[i] = '\0';
	}

	do {
		cout << "What size of board will you be playing with?" << endl;
		cout << "Please enter 8x8, 10x10, or 12x12" << endl;
		cin >> input;
		cin.ignore();
		cin.clear();

		if (strlen(input) != 0) {
			strncpy(board_size, input, strlen(input));
			if (check_arg(board_size) == true) {
				flag = true;
			}
		}
	} while (flag == false);

	delete [] input;
	return board_size;
}


/**********************************************************************************
 * Function: delete_board
 * Description: deletes the checkerboard after game has ended
 * Parameters: char** board, char* board_size
 * Input: must have access to the board and its size
 * Output: deletes the dynamid 2D array
 * *******************************************************************************/
void delete_board(char** board, char* board_size) {
	int rows = 0;

	if (check_size(board_size) == 8) {
		rows = 9;
	}
	else if (check_size(board_size) == 10) {
		rows = 11;
	}
	else if (check_size(board_size) == 12) {
		rows = 13;
	}

	for (int i = 0; i < rows; i++) {
		delete [] board[i];
	}
	delete [] board;
}


int main(int argc, char** argv) {
	char* board_size;

	if (argc == 2 && check_arg(argv[1]) == true) {
		board_size = new char[strlen(argv[1])+1];
		strcpy(board_size, argv[1]);
	}
	else {
		board_size = get_size();
	}

	char** board;
	board = create_board(board_size);
	set_board(board, board_size);
	play_game(board, board_size);
	delete_board(board, board_size);

	delete [] board_size;
	return 0;
}
