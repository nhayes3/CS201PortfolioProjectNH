#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "InitialMenus.h"
#include "SecondaryMenus.h"
#include "GraphFunctions.h"
#include "ResultChecker.h"
#include "BoardHandling.h"

void resetArray(char** board, int rows, int cols) {
  static int v;
  static int b;
  for (v = 0; v < rows; v++) {
    for (b = 0; b < cols; b++) {
      board[v][b] = ' ';
    }
  }
}

void freeArray(char** board, int rows, int cols) {
  static int m;
  for (m = 0; m < rows; m++) {
    free(board[m]);
  }
  free(board);
}

bool playAgainResponse() {
  char answer;
  getchar();
  answer = getchar();
  while (1) {
    if (answer == 'Y' || answer == 'y') {
      return 1;
    }
    else if (answer == 'N' || answer == 'n') {
      return 0;
    }
    else {
      if (answer == '\n') {
        printf("Invalid selection: use Y/N to respond.\n");
      }
      answer = getchar();
    }
  }
  return 0; //unreachable
}

int main(void) {
  printLogo();

  int play_col;
  int play_row;
  bool player;
  bool newGame;
  char exit;
  int corner;
  char buffer;

  int rows, cols;
  printf("\n\t\t\tInitial Setup");
  printf("\n\t\t      -----------------\n");
  printf("Note: The board will be printed differently for large board sizes.\n");
  printf("\n\t\tEnter the number of rows: ");
  enterrows:
  if (scanf("%d", &rows) != 1) {
    while (1) {
      buffer = getchar();
      if (buffer == '\n') {
        printf("\t    Please enter a number greater than 3.\n");
        printf("\n\t\tEnter the number of rows: ");
        goto enterrows;
      }
    }
  }
  if (rows < 4) {
    printf("\t    Please enter a number greater than 3.\n");
    printf("\n\t\tEnter the number of rows: ");
    goto enterrows;
  }
  printf("\n\t\tEnter the number of columns: ");
  entercols:
  if (scanf("%d", &cols) != 1) {
    while (1) {
      buffer = getchar();
      if (buffer == '\n') {
        printf("\t    Please enter a number greater than 3.\n");
        printf("\n\t\tEnter the number of columns: ");
        goto entercols;
      }
    }
  }
  if (cols < 4) {
    printf("\t    Please enter a number greater than 3.\n");
    printf("\n\t\tEnter the number of columns: ");
    goto entercols;
  }
  printf("\n");

  char **board = (char **)malloc(rows * sizeof(char *));

  int r;
  for (r = 0; r < rows; r++) {
    board[r] = (char *)malloc(cols * sizeof(char));
  }

  resetArray(board, rows, cols);

  int playerOneWins = 0;
  int playerTwoWins = 0;
  int pvpDraws = 0;
  int playerWins = 0;
  int compWins = 0;
  int compDraws = 0;
  int memP1Wins = 0;
  int memP2Wins = 0;
  int memPPDraws = 0;
  int memPWins = 0;
  int memCWins = 0;
  int memPCDraws = 0;

  newexec:
  resetArray(board, rows, cols);
  memP1Wins += playerOneWins;
  memP2Wins += playerTwoWins;
  memPPDraws += pvpDraws;
  memPWins += playerWins;
  memCWins += compWins;
  memPCDraws += compDraws;
  playerOneWins = 0;
  playerTwoWins = 0;
  pvpDraws = 0;
  playerWins = 0;
  compWins = 0;
  compDraws = 0;

  createMenuScreen();

  char menu_select;
  getchar();
  menu_select = getchar();
  printf("\n");
  while (1) {
    switch(menu_select) {
      case '1':
        newgame_1:
        if ((rows > 100) || (cols > 100)) {
          printf("\nNote: After the first move, the board will be\n");
          printf("printed in a section around each move.\n\n");
        }
        else if ((rows > 40) || (cols > 40)) {
          printf("1 2\n3 4\n");
          printf("Enter the segment of the board to print: ");
          select_1:
          if (scanf("%d", &corner) != 1) {
            while (1) {
              buffer = getchar();
              if (buffer == '\n') {
                printf("Please enter a number between 1 and 4.\n");
                printf("Enter the segment of the board to print: ");
                goto select_1;
              }
            }
          }
          if ((corner != 1) && (corner != 2) && (corner != 3) && (corner != 4)) {
            printf("Please enter a number between 1 and 4.\n");
            printf("Enter the segment of the board to print: ");
            goto select_1;
          }
          printSegmentedBoard(board, rows, cols, corner);
        }
        else {
          createBoardScreen(board, rows, cols);
        }
        while (1) {
          printf("What column would you like to play in?");
          reselect_c:
          if (scanf("%d", &play_col) != 1) {
            while (1) {
              buffer = getchar();
              if (buffer == '\n') {
                printf("Please enter a number between 0 and %d.\n", cols);
                printf("What column would you like to play in?");
                goto reselect_c;
              }
            }
          }
          if ((play_col < 0) || (play_col > cols)) {
            printf("That is not a valid column to play in.\n");
            goto reselect_c;
          }
          else if (board[0][play_col - 1] != ' ') {
            printf("That column is full.\n");
            goto reselect_c;
          }
          play_col--;
          play_row = placePiece(board, rows, cols, play_col);
          board[play_row][play_col] = 'x';
          if ((rows > 100) || (cols > 100)) {
            printSectionedScreen(board, rows, cols, play_row, play_col);
          }
          else if ((rows > 40) || (cols > 40)) {
            printSegmentedBoard(board, rows, cols, corner);
          }
          else {
            createBoardScreen(board, rows, cols);
          }
          if (checkWinningPosition2(board, rows, cols) == -10) {
            playerWins = checkResults(playerWins, 'P');
            printStandingsScreen(1, playerWins, compWins, compDraws);
            printPlayAgainScreen();
            newGame = playAgainResponse();
            if (newGame) {
              resetArray(board, rows, cols);
              goto newgame_1;
            }
            else {
              goto newexec;
            }
            break;
          }
          else if (checkDraw(board, rows, cols)) {
            printf("It's a draw!\n");
            compDraws++;
            printStandingsScreen(1, playerWins, compWins, compDraws);
            printPlayAgainScreen();
            newGame = playAgainResponse();
            if (newGame) {
              resetArray(board, rows, cols);
              goto newgame_1;
            }
            else {
              goto newexec;
            }
            break;
          }
          printf("Computer thinking...\n");
          play_col = columnDecider(board, rows, cols);
          play_row = placePiece(board, rows, cols, play_col);
          board[play_row][play_col] = 'o';
          if ((rows > 100) || (cols > 100)) {
            printSectionedScreen(board, rows, cols, play_row, play_col);
          }
          else if ((rows > 40) || (cols > 40)) {
            printSegmentedBoard(board, rows, cols, corner);
          }
          else {
            createBoardScreen(board, rows, cols);
          }
          if (checkWinningPosition2(board, rows, cols) == 10) {
            compWins = checkResults(compWins, 'C');
            printStandingsScreen(1, playerWins, compWins, compDraws);
            printPlayAgainScreen();
            newGame = playAgainResponse();
            if (newGame) {
              resetArray(board, rows, cols);
              goto newgame_1;
            }
            else {
              goto newexec;
            }
            break;
          }
          else if (checkDraw(board, rows, cols)) {
            compDraws = checkResults(compDraws, 'D');
            printStandingsScreen(1, playerWins, compWins, compDraws);
            printPlayAgainScreen();
            newGame = playAgainResponse();
            if (newGame) {
              resetArray(board, rows, cols);
              goto newgame_1;
            }
            else {
              goto newexec;
            }
            break;
          }
          if (((rows > 40) && (rows <= 100)) || ((cols > 40) && (cols <= 100))) {
            printf("1 2\n3 4\n");
            printf("Enter the segment of the board to print: ");
            select_2:
            if (scanf("%d", &corner) != 1) {
              while (1) {
                buffer = getchar();
                if (buffer == '\n') {
                  printf("Please enter a number between 1 and 4.\n");
                  printf("Enter the segment of the board to print: ");
                  goto select_2;
                }
              }
            }
            if ((corner != 1) && (corner != 2) && (corner != 3) && (corner != 4)) {
              printf("Please enter a number between 1 and 4.\n");
              printf("Enter the segment of the board to print: ");
              goto select_2;
            }
            printSegmentedBoard(board, rows, cols, corner);
          }
        }
        break;
      case '2':
        newgame_2:
        player = 0;
        if ((rows > 100) || (cols > 100)) {
          printf("\nNote: After the first move, the board will be\n");
          printf("printed in a section around each move.\n\n");
        }
        else if ((rows > 40) || (cols > 40)) {
          printf("1 2\n3 4\n");
          printf("Enter the segment of the board to print: ");
          select_3:
          if (scanf("%d", &corner) != 1) {
            while (1) {
              buffer = getchar();
              if (buffer == '\n') {
                printf("Please enter a number between 1 and 4.\n");
                printf("Enter the segment of the board to print: ");
                goto select_3;
              }
            }
          }
          if ((corner != 1) && (corner != 2) && (corner != 3) && (corner != 4)) {
            printf("Please enter a number between 1 and 4.\n");
            printf("Enter the segment of the board to print: ");
            goto select_3;
          }
          printSegmentedBoard(board, rows, cols, corner);
        }
        else {
          createBoardScreen(board, rows, cols);
        }
        while (1) {
          if (!player) {
            printf("Player 1's turn.\n");
          }
          else if (player) {
            printf("Player 2's turn.\n");
          }
          printf("What column would you like to play in?");
          reselect:
          if (scanf("%d", &play_col) != 1) {
            while (1) {
              buffer = getchar();
              if (buffer == '\n') {
                printf("Please enter a number between 0 and %d.\n", cols);
                printf("What column would you like to play in?");
                goto reselect;
              }
            }
          }
          if ((play_col < 0) || (play_col > cols)) {
            printf("That is not a valid column to play in.\n");
            goto reselect;
          }
          else if (board[0][play_col - 1] != ' ') {
            printf("That column is full.\n");
            goto reselect;
          }
          play_col--;
          play_row = placePiece(board, rows, cols, play_col);
          if (!player) {
            board[play_row][play_col] = 'x';
          }
          else if (player) {
            board[play_row][play_col] = 'o';
          }
          if ((rows > 100) || (cols > 100)) {
            printSectionedScreen(board, rows, cols, play_row, play_col);
          }
          else if ((rows > 40) || (cols > 40)) {
            printSegmentedBoard(board, rows, cols, corner);
          }
          else {
            createBoardScreen(board, rows, cols);
          }
          if (checkWinningPosition2(board, rows, cols) == -10) {
            playerOneWins = checkResults(playerOneWins, '1');
            printStandingsScreen(0, playerOneWins, playerTwoWins, pvpDraws);
            printPlayAgainScreen();
            newGame = playAgainResponse();
            if (newGame) {
              resetArray(board, rows, cols);
              goto newgame_2;
            }
            else {
              goto newexec;
            }
            break;
          }
          else if (checkWinningPosition2(board, rows, cols) == 10) {
            playerTwoWins = checkResults(playerTwoWins, '2');
            printStandingsScreen(0, playerOneWins, playerTwoWins, pvpDraws);
            printPlayAgainScreen();
            newGame = playAgainResponse();
            if (newGame) {
              resetArray(board, rows, cols);
              goto newgame_2;
            }
            else {
              goto newexec;
            }
            break;
          }
          else if (checkDraw(board, rows, cols)) {
            pvpDraws = checkResults(pvpDraws, 'D');
            printStandingsScreen(0, playerOneWins, playerTwoWins, pvpDraws);
            printPlayAgainScreen();
            newGame = playAgainResponse();
            if (newGame) {
              resetArray(board, rows, cols);
              goto newgame_2;
            }
            else {
              goto newexec;
            }
            break;
          }
          player = !player;
          if (((rows > 40) && (rows <= 100)) || ((cols > 40) && (cols <= 100))) {
            printf("1 2\n3 4\n");
            printf("Enter the segment of the board to print: ");
            select_4:
            if (scanf("%d", &corner) != 1) {
              while (1) {
                buffer = getchar();
                if (buffer == '\n') {
                  printf("Please enter a number between 1 and 4.\n");
                  printf("Enter the segment of the board to print: ");
                  goto select_4;
                }
              }
            }
            if ((corner != 1) && (corner != 2) && (corner != 3) && (corner != 4)) {
              printf("Please enter a number between 1 and 4.\n");
              printf("Enter the segment of the board to print: ");
              goto select_4;
            }
            printSegmentedBoard(board, rows, cols, corner);
          }
        }
        break;
      case '3':
        printRecentStats(memP1Wins, memP2Wins, memPPDraws, memPWins, memCWins, memPCDraws);
        printf("Press E to exit.\n");
        getchar();
        exit = getchar();
        while (1) {
          if (exit == 'E' || exit == 'e') {
            goto newexec;
          }
          else {
            if (exit == '\n') {
              printf("Invalid selection: use E to exit.\n");
            }
            exit = getchar();
          }
        }
        break;
      case '4':
        return 0;
        break;
      default:
        if (menu_select == '\n') {
          printf("That is not a valid selection!\n");
          printf("Selection: ");
        }
        menu_select = getchar();
        break;
      }
    }

  freeArray(board, rows, cols);

  return 0;
}
