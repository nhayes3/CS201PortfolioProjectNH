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

//increase efficiency
//start at position [rows][cols]
//run until an entire row is blank

int calculateBoardScore(char** board, int rows, int cols) {
  int h;
  int u;
  int tracker = 0;

  for (h = 0; h < rows; h++) {
    for (u = 0; u < cols; u++) {
      if (board[h][u] == 'x') tracker--;
      else if (board[h][u] == 'o') tracker++;

      if ((rows - h) > 1) {
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

      if ((rows - h) > 2) {
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
  if (checkWinningPosition2(board, rows, cols) == 10) {
    tracker += 10000;
  }
  else if (checkWinningPosition2(board, rows, cols) == -10) {
    tracker -= 10000;
  }
  else if (checkDraw(board, rows, cols)) {
    tracker = 0;
  }
  return tracker;
}

int negamax(char** board, int rows, int cols, bool player, int depth) {//, int bestScore, int bestCol) {
  int h;
  int bestrow;
  int bestCol;

  if (depth == 2) {
    return calculateBoardScore(board, rows, cols);
  }
  else if (checkDraw(board, rows, cols)) {
    return calculateBoardScore(board, rows, cols);
  }

  int bestScore = -(rows * cols);

  for (h = 0; h < cols; h++) {
    if (board[0][h] == ' ') {
      bestrow = placePiece(board, rows, cols, h);
      if (player) {
        board[bestrow][h] = 'o';
        int score = -negamax(board, rows, cols, !player, depth++);//calculateBoardScore(board, rows, cols);
        //printf(">Computer @ Depth = %d plays in %d with %d score.\n", depth, h, score);
        if (score > bestScore) {
          bestScore = score;
          bestCol = h;
          //printf(">Computer @ Depth = %d sets bestCol to %d with %d score.\n", depth, bestCol, bestScore);
        }
        /*if (depth == 4) {
          board[bestrow][h] = ' ';
          return bestCol;
        }*/
        //negamax(board, rows, cols, !player, depth++, bestScore, bestCol);
        board[bestrow][h] = ' ';
      }
      else if (!player) {
        board[bestrow][h] = 'x';
        int score = -negamax(board, rows, cols, !player, depth++);//calculateBoardScore(board, rows, cols);
        //printf(">Player @ Depth = %d plays in %d with %d score.\n", depth, h, score);
        if (score > bestScore) {
          bestScore = score;
          bestCol = h;
          //printf(">Computer @ Depth = %d sets bestCol to %d with %d score.\n", depth, bestCol, bestScore);
        }
        /*if (depth == 4) {
          board[bestrow][h] = ' ';
          return bestCol;
        }*/
        //negamax(board, rows, cols, !player, depth++, bestScore, bestCol);
        board[bestrow][h] = ' ';
      }
    }
  }
  return bestCol;
}


int columnDecider(char** board, int rows, int cols) {
  static int z;
  int winRow;
  int bestCol;

  for (z = 0; z < cols; z++) {
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
  for (z = 0; z < cols; z++) {
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

  bestCol = negamax(board, rows, cols, 1, 0); //, 0, -10000, 0);
  printf("%d\n", bestCol);

  return bestCol;
}
