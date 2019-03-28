#include <stdio.h>
#include <stdbool.h>

int placePiece(char** board, int rows, int cols, int colPlayed) {
  static int k;
  if (board[rows - 1][colPlayed] == ' ') {
    return (rows - 1);
  }
  else {
    for (k = 0; k < rows; k++) {
      if ((board[k][colPlayed] == ' ') && (board[k + 1][colPlayed] != ' ')) {
        return k;
      }
    }
  }
  return 0; //will never be reached
}

bool checkDraw(char** board, int rows, int cols) {
  static int d;
  int flag = 0;
  for (d = 0; d < cols; d++) {
    if (board[0][d] != ' '){
      flag++;
    }
  }
  if (flag == cols) {
    return 1;
  }
  return 0;
}

int checkWinningPosition2(char** board, int rows, int cols) {
  int loopCol;
  int loopRow;
  int rowPos = rows - 1;
  int colPos = cols - 1;
  for (loopCol = 0; loopCol < cols; loopCol++) {
    for (loopRow = 0; loopRow < rows; loopRow++) {
      if (((rowPos - loopRow) > 2) && ((colPos - loopCol) > 2)) {
        if ((board[loopRow][loopCol] == board[loopRow + 1][loopCol + 1])
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
        if ((board[loopRow][loopCol] == board[loopRow + 1][loopCol])
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
        if ((board[loopRow][loopCol] == board[loopRow][loopCol + 1])
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
        if ((board[loopRow][loopCol] == board[loopRow - 1][loopCol + 1])
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

int negamax(char** board, int rows, int cols, bool player, int alpha, int beta, int numMoves) {
  if(checkDraw(board, rows, cols)) {
    return 0;
  }
  int h;
  int bestrow;
  for (h = 0; h < cols; h++) {
    if (board[0][h] == ' ') {
      bestrow = placePiece(board, rows, cols, h);
      if (player) {
        board[bestrow][h] = 'o';
        if (checkWinningPosition2(board, rows, cols) == 10) {
          board[bestrow][h] = ' ';
          return h;
        }
        board[bestrow][h] = ' ';
      }
      else if (!player) {
        board[bestrow][h] = 'x';
        if (checkWinningPosition2(board, rows, cols) == -10) {
          board[bestrow][h] = ' ';
          return h;
        }
        board[bestrow][h] = ' ';
      }
    }
  }

  int bestScore = (((rows*cols - 1) - numMoves)/2);
  int bestCol;

  if (beta > bestScore) {
    beta = bestScore;
    if (alpha >= beta) return beta;
  }

  for (h = 0; h < cols; h++) {
    if (board[0][h] == ' ') {
      bestrow = placePiece(board, rows, cols, h);
      if (player) {
        board[bestrow][h] = 'o';
        int score = -negamax(board, rows, cols, !player, -beta, -alpha, numMoves++);
        board[bestrow][h] = ' ';
        if (score >= beta) return score;
        if (score > alpha) {
          alpha = score;
          bestCol = h;
        }
      }
      else if (!player) {
        board[bestrow][h] = 'x';
        int score = -negamax(board, rows, cols, !player, -beta, -alpha, numMoves++);
        board[bestrow][h] = ' ';
        if (score >= beta) return score;
        if (score > alpha) {
          alpha = score;
          bestCol = h;
        }
      }
    }
  }
  //printf("%d", bestScore);
  return bestCol;
}
