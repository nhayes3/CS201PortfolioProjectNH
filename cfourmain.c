#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "InitialMenus.h"
#include "SecondaryMenus.h"
#include "GraphFunctions.h"
#include "ResultChecker.h"

void createBoardScreen(char** board, int rows, int cols) {
  static int i;
  static int j;
  static int k;
  for (i = 0; i < cols; i++) {
    printf("____");
  }
  printf("_\n");
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      printf("| %c ", board[i][j]);
    }
    printf("|\n");
    for (k = 0; k < cols; k++) {
      printf("----");
    }
    printf("-\n");
  }
}

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
  response:
  scanf("%c", &answer);
  if (answer == 'Y' || answer == 'y') {
    return 1;
  }
  else if (answer == 'N' || answer == 'n') {
    return 0;
  }
  else {
    printf("Invalid selection: use Y/N to respond.\n");
    goto response;
  }
  return 0; //unreachable
}

int main(void) {
  printLogo();

  int play_col;
  int play_row;
  bool player;
  bool newGame;
  int numMoves = 0;
  char exit;

  int rows, cols;
  printf("Enter the number of rows: ");
  scanf("%d", &rows);
  printf("\n");
  printf("Enter the number of columns: ");
  scanf("%d", &cols);
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

  int menu_select;
  while (1) {
    scanf("%d", &menu_select);
    switch(menu_select) {
      case 1:
        newgame_1:
        createBoardScreen(board, rows, cols);
          while (1) {
            reselect_c:
            printf("What column would you like to play in?");
            scanf("%d", &play_col);
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
            numMoves++;
            createBoardScreen(board, rows, cols);
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

          //printf("%d", bestMove(rows, cols, temp));
          //play_col = bestMove(rows, cols, temp);
          //play_row = placePiece(rows, cols, temp, play_col);
          //printf("%d ", play_row);
          //board[play_row][play_col] = 'o';

          //int bestScore = negamax(board, rows, cols, 1);
            play_col = negamax(board, rows, cols, 1, -9999999, 9999999, numMoves);
            play_row = placePiece(board, rows, cols, play_col);
            board[play_row][play_col] = 'o';
            numMoves++;
            createBoardScreen(board, rows, cols);
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
          }
          break;
      case 2:
        newgame_2:
        player = 0;
        createBoardScreen(board, rows, cols);
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
          createBoardScreen(board, rows, cols);
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
        }
        break;
      case 3:
        printRecentStats(memP1Wins, memP2Wins, memPPDraws, memPWins, memCWins, memPCDraws);
        //getchar();
        scanf("%c", &exit);
        while (1) {
          if (exit == 'E' || exit == 'e') {
            goto newexec;
          }
          else {
            printf("Invalid selection: use E to exit.\n");
            scanf("%c", &exit);
          }
        }
        break;
      case 4:
        freeArray(board, rows, cols);

        printf("\nEnter new number of rows: ");
        scanf("%d", &rows);
        printf("\nEnter new number of columns: ");
        scanf("%d", &cols);

        char **board = (char **)malloc(rows * sizeof(char *));

        int r;
        for (r = 0; r < rows; r++) {
          board[r] = (char *)malloc(cols * sizeof(char));
        }

        resetArray(board, rows, cols);

        break;
      case 5:
        return 0;
        break;
      default:
        printf("That is not a valid selection!\n");
        break;
      }
    }

  return 0;
}
