#include <stdio.h>
#include <stdbool.h>

/*
 * placePiece function with int return type and four parameters
 * This function searches in the board, iterating from the top to the bottom
 * in the column that the user or computer selected. It finds the first empty
 * row above a piece, or the bottom of the board, and returns it. Error checking
 * for full columns is done outside of this function, before it is ever called.
 */
int placePiece(char** board, int rows, int cols, int colPlayed) {
  static int k;
  if (board[rows - 1][colPlayed] == ' ') {           //checks for empty column
    return (rows - 1);
  }
  else {                                             //iterates to empty row
    for (k = 0; k < rows; k++) {
      if ((board[k][colPlayed] == ' ') && (board[k + 1][colPlayed] != ' ')) {
        return k;
      }
    }
  }
  return 0;                                          //should never be reached
}

/*
 * checkDraw function with bool return type and three parameters
 * This function checks to see if the board is full by iterating across the
 * top row of the array, checking to see if each position is occupied by
 * a piece. If every position is full, it returns true; otherwise, it
 * returns false.
 */
bool checkDraw(char** board, int rows, int cols) {
  int d;
  int flag = 0;
  for (d = 0; d < cols; d++) {                     //iterates through top row
    if (board[0][d] != ' '){
      flag++;
    }
  }
  if (flag == cols) {                              //checks if all positions are full
    return 1;
  }
  return 0;
}

/*
 * checkWinningPosition2 function with int return type and three parameters
 * This function iterates through the entire board array, checking if either
 * type of piece has four in a row in any direction. There is a separate if
 * statement for each direction (vertical, horizontal, negative slope diagonal,
 * and positive slope diagonal). Each of these if statements are protected by
 * if statements that prevent from accessing the array out of bounds. The
 * function returns 10 if the computer/player 2 wins, or -10 if the player/
 * player 1 wins.
 */
int checkWinningPosition2(char** board, int rows, int cols) {
  int loopCol;
  int loopRow;
  int rowPos = rows - 1;
  int colPos = cols - 1;
  for (loopCol = 0; loopCol < cols; loopCol++) {                 //checks every board position
    for (loopRow = 0; loopRow < rows; loopRow++) {
      if (((rowPos - loopRow) > 2) && ((colPos - loopCol) > 2)) {
        if ((board[loopRow][loopCol] == board[loopRow + 1][loopCol + 1])           //checks for negative slope diagonal
        && (board[loopRow + 1][loopCol + 1] == board[loopRow + 2][loopCol + 2])
        && (board[loopRow + 2][loopCol + 2] == board[loopRow + 3][loopCol + 3])) {
          if (board[loopRow][loopCol] == 'x') {
            return -10;
          }
          else if (board[loopRow][loopCol] == 'o') {
            return 10;
          }
        }
      }
      if ((rowPos - loopRow) > 2) {
        if ((board[loopRow][loopCol] == board[loopRow + 1][loopCol])               //checks for vertical
        && (board[loopRow + 1][loopCol] == board[loopRow + 2][loopCol])
        && (board[loopRow + 2][loopCol] == board[loopRow + 3][loopCol])) {
          if (board[loopRow][loopCol] == 'x') {
            return -10;
          }
          else if (board[loopRow][loopCol] == 'o') {
            return 10;
          }
        }
      }
      if ((colPos - loopCol) > 2) {
        if ((board[loopRow][loopCol] == board[loopRow][loopCol + 1])               //checks for horizontal
        && (board[loopRow][loopCol + 1] == board[loopRow][loopCol + 2])
        && (board[loopRow][loopCol + 2] == board[loopRow][loopCol + 3])) {
          if (board[loopRow][loopCol] == 'x') {
            return -10;
          }
          else if (board[loopRow][loopCol] == 'o') {
            return 10;
          }
        }
      }
      if (((colPos - loopCol) > 2) && (loopRow > 2)) {
        if ((board[loopRow][loopCol] == board[loopRow - 1][loopCol + 1])           //checks for positive slope vertical
        && (board[loopRow - 1][loopCol + 1] == board[loopRow - 2][loopCol + 2])
        && (board[loopRow - 2][loopCol + 2] == board[loopRow - 3][loopCol + 3])) {
          if (board[loopRow][loopCol] == 'x') {
            return -10;
          }
          else if (board[loopRow][loopCol] == 'o') {
            return 10;
          }
        }
      }
    }
  }
  return 0;
}

/*
 * calculateBoardScore with int return type and three parameters
 * This function returns the score of the current position reflected by the
 * contents in the board array. The score is incremented by a scaled amount
 * depending on the number of pieces the computer has played, with more points
 * being added for connected pieces. The score is decremented similarly for
 * pieces belonging to the player. This function is used in the function that
 * determins the computer's move, with the concept that the best possible move,
 * outside of instantly winning or preventing a player win, is to prevent the
 * player from connecting pieces while setting the computer up with more
 * opportunities to threaten wins. If statements surround each checker to
 * prevent the array from being accessed out of bounds.
 */
int calculateBoardScore(char** board, int rows, int cols) {
  int h;
  int u;
  int tracker = 0;

  for (h = 0; h < rows; h++) {
    for (u = 0; u < cols; u++) {
      if (board[h][u] == 'x') tracker--;                                 //for individual pieces
      else if (board[h][u] == 'o') tracker++;

      if ((rows - h) > 1) {                                             //for two pieces connected
        if ((board[h][u] == 'x') && (board[h][u] == board[h + 1][u])) {
          tracker -= 4;
        }
        else if ((board[h][u] == 'o') && (board[h][u] == board[h + 1][u])) {
          tracker += 4;
        }
      }
      if ((cols - u) > 1) {
        if ((board[h][u] == 'x') && (board[h][u] == board[h][u + 1])) {
          tracker -= 4;
        }
        else if ((board[h][u] == 'o') && (board[h][u] == board[h][u + 1])) {
          tracker += 4;
        }
      }

      if ((rows - h) > 2) {                                            //for three pieces connected
        if ((board[h][u] == 'x') && (board[h][u] == board[h + 1][u]) && (board[h + 1][u] == board[h + 2][u])) {
          tracker -= 10;
        }
        else if ((board[h][u] == 'o') && (board[h][u] == board[h + 1][u]) && (board[h + 1][u] == board[h + 2][u])) {
          tracker += 10;
        }
      }
      if ((cols - u) > 2) {
        if ((board[h][u] == 'x') && (board[h][u] == board[h][u + 1]) && (board[h][u + 1] == board[h][u + 2])) {
          tracker -= 10;
        }
        else if ((board[h][u] == 'o') && (board[h][u] == board[h][u + 1]) && (board[h][u + 1] == board[h][u + 2])) {
          tracker += 10;
        }
      }
    }
  }
  return tracker;
}

/*
 * findOptimalPosition function with int return type and five parameters
 * This function iterates through possible moves given the current position
 * as reflected in the board array. It recursively calls itself, with the
 * base case returning the position's score at a specified depth. Each
 * recursive call changest the player, allowing the function to simulate
 * both computer and player moves. Optimally, it would iterate through every
 * possible combination of moves, using the calculateBoardScore function to
 * obtain the optimal move; however, due to a high runtime, it is limited
 * to a certain number of moves.
 * This function was adapted from the mini-max algorithm, a common algorithm
 * used in games like Connect 4. It was modified heavily in sections, but this
 * specific function was adapted from Pascal Pons' negamax algorithm.
 * Source: http://blog.gamesolver.org/solving-connect-four/03-minmax/
 */
int findOptimalPosition(char** board, int rows, int cols, bool player, int depth) {
  int h;
  int bestrow;
  int bestCol;

  if (depth >= 2) {                                     //depth limited base case
    return calculateBoardScore(board, rows, cols);
  }
  else if (checkDraw(board, rows, cols)) {              //full board base case
    return calculateBoardScore(board, rows, cols);
  }

  int bestScore = -(rows * cols);                       //initializes low score

  for (h = 0; h < cols; h++) {                          //iterates through columns
    if (board[0][h] == ' ') {                           //checks if column is full
      bestrow = placePiece(board, rows, cols, h);
      if (player) {
        board[bestrow][h] = 'o';                        //places computer piece
        ++depth;
        int score = -findOptimalPosition(board, rows, cols, !player, depth); //goes to next move
        if (score > bestScore) {                       //after recursions finish, finds best score
          bestScore = score;                           //and corresponding best column
          bestCol = h;
        }
        board[bestrow][h] = ' ';                       //resets played piece
      }
      else if (!player) {                              //same process, places player piece
        board[bestrow][h] = 'x';
        ++depth;
        int score = -findOptimalPosition(board, rows, cols, !player, depth);
        if (score > bestScore) {
          bestScore = score;
          bestCol = h;
        }
        board[bestrow][h] = ' ';
      }
    }
  }
  return bestCol;                                     //returns best column from position with best score
}

/*
 * columnDecider function with int return type and three parameters
 * This function is the function called when the computer tries to determine
 * the best move in the main function. Initially, it checks if it can win in
 * one move by placing a piece in each column and checking it in the win function.
 * Next, it checks if the player has a win in the same way. If either of these
 * return true, the computer returns the appropriate column to either win or
 * stop a player win. If neither is possible, it calls the findOptimalPosition
 * function in order to use the calculateBoardScore function to determine the
 * best column to play in to reach an optimal solution.
 */
int columnDecider(char** board, int rows, int cols) {
  static int z;
  int winRow;
  int bestCol;

  for (z = 0; z < cols; z++) {                         //checks for a computer win in one move
    if (board[0][z] == ' ') {
      winRow = placePiece(board, rows, cols, z);
      board[winRow][z] = 'o';
      if (checkWinningPosition2(board, rows, cols) == 10) {
        board[winRow][z] = ' ';
        return z;
      }
      else {
        board[winRow][z] = ' ';
      }
    }
  }
  for (z = 0; z < cols; z++) {                        //checks to block a player win in one move
    if (board[0][z] == ' ') {
      winRow = placePiece(board, rows, cols, z);
      board[winRow][z] = 'x';
      if (checkWinningPosition2(board, rows, cols) == -10) {
        board[winRow][z] = ' ';
        return z;
      }
      else {
        board[winRow][z] = ' ';
      }
    }
  }

  bestCol = findOptimalPosition(board, rows, cols, 1, 0);    //finds column that reaches optimal position

  return bestCol;
}
