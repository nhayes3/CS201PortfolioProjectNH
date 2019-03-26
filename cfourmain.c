#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void createMenuScreen() {
  printf(" ____________________________ \n");
  for (int i = 0; i < 8; i++) {
    switch(i) {
      case 1:
        printf("| 1: Play vs. computer       |\n");
        break;
      case 3:
        printf("| 2: Play vs. human          |\n");
        break;
      case 5:
        printf("| 3: Recent stats            |\n");
        break;
      case 7:
        printf("| 4: Options                 |\n");
        break;
      default:
        printf("|                            |\n");
    }
  }
  printf("|____________________________|\n");
}

void createBoardScreen(int rows, int cols, char board[rows][cols]) {
  static int i;
  static int j;
  printf(" __________________________________ \n");
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }
}

int placePiece(int rows, int cols, char board[rows][cols], int colPlayed) {
  static int k;
  if (board[rows - 1][colPlayed] == 'z') {
    return (rows - 1);
  }
  else {
    for (k = 0; k < rows; k++) {
      if ((board[k][colPlayed] == 'z') && (board[k + 1][colPlayed] != 'z')) {
        return k;
      }
    }
  }
  return 0; //will never be reached
}

bool checkDraw(int rows, int cols, char board[rows][cols]) {
  static int d;
  int flag = 0;
  for (d = 0; d < cols; d++) {
    if (board[0][d] != 'z'){
      flag++;
    }
  }
  if (flag == cols) {
    return 1;
  }
  return 0;
}

int checkWinningPosition2(int rows, int cols, char board[rows][cols]) {
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
            return 1000000;
          }
          else if (board[loopRow][loopCol] == 'o') {
            return -1000000;
          }
        }
      }
      if ((rowPos - loopRow) > 2) {
        if ((board[loopRow][loopCol] == board[loopRow + 1][loopCol])
        && (board[loopRow + 1][loopCol] == board[loopRow + 2][loopCol])
        && (board[loopRow + 2][loopCol] == board[loopRow + 3][loopCol])) {
          if (board[loopRow][loopCol] == 'x') {
            return 1000000;
          }
          else if (board[loopRow][loopCol] == 'o') {
            return -1000000;
          }
        }
      }
      if ((colPos - loopCol) > 2) {
        if ((board[loopRow][loopCol] == board[loopRow][loopCol + 1])
        && (board[loopRow][loopCol + 1] == board[loopRow][loopCol + 2])
        && (board[loopRow][loopCol + 2] == board[loopRow][loopCol + 3])) {
          if (board[loopRow][loopCol] == 'x') {
            return 1000000;
          }
          else if (board[loopRow][loopCol] == 'o') {
            return -1000000;
          }
        }
      }
      if (((colPos - loopCol) > 2) && (loopRow < 2)) {
        if ((board[loopRow][loopCol] == board[loopRow - 1][loopCol + 1])
        && (board[loopRow - 1][loopCol + 1] == board[loopRow - 2][loopCol + 2])
        && (board[loopRow - 2][loopCol + 2] == board[loopRow - 3][loopCol + 3])) {
          if (board[loopRow][loopCol] == 'x') {
            return 1000000;
          }
          else if (board[loopRow][loopCol] == 'o') {
            return -1000000;
          }
        }
      }
    }
  }
  return 0;
}

int maxFunc(int one, int two) {
  if (one > two) return one;
  else return two;
}

int minFunc(int one, int two) {
  if (one > two) return two;
  else return one;
}

int computeVal(int rows, int cols, char board[rows][cols], int depth, bool player, int alpha, int beta) {
  int val = checkWinningPosition2(rows, cols, board);
  int newrow;
  int bestVal;
  int c;
  if (val == 1000000) {
    return val;
  }
  else if (val == -1000000) {
    return val;
  }
  else if (checkDraw(rows, cols, board)) {
    return 0;
  }
  else if (depth == 5) {
    return 0;
  }
  if (player) {
    bestVal = -10000000;
    for (c = 0; c < cols; c++) {
      if (board[0][c] == 'z') {
        newrow = placePiece(rows, cols, board, c);
        board[newrow][c] = 'o';
        bestVal = maxFunc(bestVal, computeVal(rows, cols, board, depth + 1, !player, alpha, beta));
        alpha = maxFunc(alpha, bestVal);
        board[newrow][c] = 'z';
        if (beta <= alpha) {
          break;
        }
      }
    }
    return bestVal;
  }
  else if (!player) {
    bestVal = 10000000;
    for (c = 0; c < cols; c++) {
      if (board[0][c] == 'z') {
        newrow = placePiece(rows, cols, board, c);
        board[newrow][c] = 'x';
        bestVal = minFunc(bestVal, computeVal(rows, cols, board, depth + 1, !player, alpha, beta));
        beta = minFunc(beta, bestVal);
        board[newrow][c] = 'z';
        if (beta <= alpha) {
          break;
        }
      }
    }
    return bestVal;
  }
}

int bestMove(int rows, int cols, char newAr[rows][cols]) {
  int bestMove = 0;
  int bestMoveVal = -100000000;
  int l;
  int newrow;
  int val;
  for (l = 0; l < cols; l++) {
    if (newAr[0][l] == 'z') {
      newrow = placePiece(rows, cols, newAr, l);
      newAr[newrow][l] = 'o';
      val = computeVal(rows, cols, newAr, 0, 1, -10000000, 10000000);
      newAr[newrow][l] = 'z';
      if (val > bestMoveVal) {
        bestMoveVal = val;
        bestMove = l;
      }
    }
  }
  printf("%d ", bestMove);
  return bestMove;
}

void copyArray(int rows, int cols, char board[rows][cols], char temp[rows][cols]) {
  int p;
  int q;
  for (p = 0; p < rows; p++) {
    for (q = 0; q < cols; q++) {
      temp[p][q] = board[p][q];
    }
  }
}

int main(void) {
  createMenuScreen();

  int menu_select;
  int play_col;
  int play_row;
  bool player;

  int rows, cols;
  printf("Enter the number of rows: ");
  scanf("%d", &rows);
  printf("\n");
  printf("Enter the number of columns: ");
  scanf("%d", &cols);
  printf("\n");

  char board[rows][cols];
  memset(board, 'z', sizeof board);

  char temp[rows][cols];
  memset(temp, 'z', sizeof temp);

  select_again:
  scanf("%d", &menu_select);
  switch(menu_select) {
    case 1:
      createBoardScreen(rows, cols, board);
        while (1) {
          reselect_c:
          printf("What column would you like to play in?");
          scanf("%d", &play_col);
          if ((play_col < 0) || (play_col > cols)) {
            printf("That is not a valid column to play in.\n");
            goto reselect_c;
          }
          else if (board[0][play_col - 1] != 'z') {
            printf("That column is full.\n");
            goto reselect_c;
          }
          play_col--;
          play_row = placePiece(rows, cols, board, play_col);
          board[play_row][play_col] = 'x';
          createBoardScreen(rows, cols, board);
          if (checkWinningPosition2(rows, cols, board)) {
            printf("Human wins!\n");
            break;
          }
          else if (checkDraw(rows, cols, board)) {
            printf("It's a draw!\n");
            break;
          }
          printf("Computer thinking...\n");
          copyArray(rows, cols, board, temp);
          //printf("%d", compColumnSelect(rows, cols, temp, 1, play_row, play_col));
          //play_col = compColumnSelect(rows, cols, temp, 1, play_row, play_col);
          //printf("%d", bestMove(rows, cols, temp));
          play_col = bestMove(rows, cols, temp);
          play_row = placePiece(rows, cols, temp, play_col);
          printf("%d ", play_row);
          board[play_row][play_col] = 'o';
          createBoardScreen(rows, cols, board);
          if (checkWinningPosition2(rows, cols, board)) {
            printf("Computer wins!\n");
            break;
          }
          else if (checkDraw(rows, cols, board)) {
            printf("It's a draw!\n");
            break;
          }
        }
      break;
    case 2:
      player = 0;
      createBoardScreen(rows, cols, board);
        while (1) {
          if (!player) {
            printf("Player 1's turn.\n");
          }
          else if (player) {
            printf("Player 2's turn.\n");
          }
          reselect:
          printf("What column would you like to play in?");
          scanf("%d", &play_col);
          if ((play_col < 0) || (play_col > cols)) {
            printf("That is not a valid column to play in.\n");
            goto reselect;
          }
          else if (board[0][play_col - 1] != 'z') {
            printf("That column is full.\n");
            goto reselect;
          }
          play_col--;
          play_row = placePiece(rows, cols, board, play_col);
          if (!player) {
            board[play_row][play_col] = 'x';
          }
          else if (player) {
            board[play_row][play_col] = 'o';
          }
          createBoardScreen(rows, cols, board);
          if (checkWinningPosition2(rows, cols, board) == 1000000) {
            printf("Player 1 wins!");
            break;
          }
          else if (checkWinningPosition2(rows, cols, board) == -1000000) {
            printf("Player 2 wins!");
            break;
          }
          else if (checkDraw(rows, cols, board)) {
            printf("It's a draw!");
            break;
          }
          player = !player;
        }
      break;
    case 3:
      printf("3");
      break;
    case 4:
      printf("4");
      break;
    default:
      printf("That is not a valid selection!\n");
      createMenuScreen();
      goto select_again;
  }
  return 0;
}
