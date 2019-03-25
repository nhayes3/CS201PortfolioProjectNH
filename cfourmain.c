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

bool checkWinningPosition(int rows, int cols, char board[rows][cols], int start_row, int start_col) {
  static char piece;
  piece = board[start_row][start_col];
  static int count;
  count = 0;
  int a;

  if (start_row >= 4) {
    for (a = 1; a < 4; a++) {
      if (piece == board[start_row - a][start_col]) count++;
      if (count == 3) return 1;
    }
  }
  count = 0;
  if ((rows - start_row) >= 4) {
    for (a = 1; a < 4; a++) {
      if (piece == board[start_row + a][start_col]) count++;
      if (count == 3) return 1;
    }
  }
  count = 0;
  if (start_col >= 3) {
    for (a = 1; a < 4; a++) {
      if (piece == board[start_row][start_col - a]) count++;
      if (count == 3) return 1;
    }
  }
  count = 0;
  if ((cols - start_col) >= 4) {
    for (a = 1; a < 4; a++) {
      if (piece == board[start_row][start_col + a]) count++;
      if (count == 3) return 1;
    }
  }
  return 0;
}

int main(void) {
  createMenuScreen();

  int menu_select;
  int play_col;
  int play_row;
  bool player;

  int rows = 7;
  int cols = 6;

  char board[rows][cols];
  memset(board, 'z', sizeof board);

  select_again:
  scanf("%d", &menu_select);
  switch(menu_select) {
    case 1:
      printf("1");
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
          if (checkWinningPosition(rows, cols, board, play_row, play_col)) break;
          player = !player;
        }
        if (!player) {
          printf("Player 1 wins!");
        }
        else if (player) {
          printf("Player 2 wins!");
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
