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

/*
 * CS 201 Project
 * Connect Four
 * Nathan Hayes
 * 11780930
 * 3/29/19
 */

/*
 * resetArray function with void return type and three parameters
 * This function is passed the board array, with the board's dimensions.
 * It uses two for loops to iterate through the entire array, setting
 * each value to a space, thereby resetting the board to an empty state
 * for use in a new Connect Four game.
 */
void resetArray(char** board, int rows, int cols) {
  static int v;
  static int b;
  for (v = 0; v < rows; v++) {
    for (b = 0; b < cols; b++) {
      board[v][b] = ' ';            //set each location to a space
    }
  }
}

/*
 * freeArray function with void return type and three parameters
 * This function is passed the board array, with the board's dimensions.
 * Using a for loop, it frees the memory allocated to one dimension of
 * the array, then frees the remaining memory to avoid memory leaks.
 */
void freeArray(char** board, int rows, int cols) {
  static int m;
  for (m = 0; m < rows; m++) {
    free(board[m]);                 //free memory for one dimension
  }
  free(board);                      //free memory for other dimension
}

/*
 * playAgainResponse function with bool return type and no parameters
 * This function reads in user input after being called once a Connect
 * Four game has concluded. It protects against inproper input and returns
 * true if the player wants to play again; false if the player wants to
 * exit.
 */
bool playAgainResponse() {
  char answer;
  getchar();
  answer = getchar();
  while (1) {
    if (answer == 'Y' || answer == 'y') {            //play again
      return 1;
    }
    else if (answer == 'N' || answer == 'n') {       //exit
      return 0;
    }
    else {                                           //error checking input
      if (answer == '\n') {
        printf("Invalid selection: use Y/N to respond.\n");
      }
      answer = getchar();
    }
  }
  return 0; //unreachable
}

/*
 * main function
 * In the main function, important variables are initialized, and the board
 * array is allocated. Then, the menu is printed, allowing the user to select
 * between playing against the computer, playing against another player,
 * viewing recent win/loss/draw statistics, and exiting the program. The
 * flow of the program is contained here, with many of the prompts and
 * calls to other functions. Most large print statements and logic for
 * editing the board is outsourced to another function.
 */
int main(void) {
  printLogo();                                  //prints Connect Four logo

  int play_col;                                //column being played in
  int play_row;                                //row being played in
  bool player;                                 //toggles between player 1 and 2
  bool newGame;                                //restarts or ends game
  char exit;                                   //for exiting stats menu
  int corner;                                  //for printing medium-sized boards
  char buffer;                                 //for error checking input

  int rows, cols;                              //receives board dimensions
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

  char **board = (char **)malloc(rows * sizeof(char *));  //allocates memory for array

  int r;
  for (r = 0; r < rows; r++) {
    board[r] = (char *)malloc(cols * sizeof(char));
  }

  resetArray(board, rows, cols);                         //sets each location to a space

  int playerOneWins = 0;                                 //initializes all stats to 0
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
  memP1Wins += playerOneWins;                            //updates long-term stats
  memP2Wins += playerTwoWins;                            //and clears short-term stats
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

  createMenuScreen();                                    //prints menu

  char menu_select;                                      //player input for menu
  getchar();
  menu_select = getchar();
  printf("\n");
  while (1) {
    switch(menu_select) {
      case '1':                                          //player vs computer case
        newgame_1:
        if ((rows > 100) || (cols > 100)) {              //prints board depending on size
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
        while (1) {                                        //player input for placing piece
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
          play_row = placePiece(board, rows, cols, play_col);     //places piece
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
          if (checkWinningPosition2(board, rows, cols) == -10) {           //checks for win
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
          else if (checkDraw(board, rows, cols)) {                   //checks for draw
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
          printf("Computer thinking...\n");                    //places computer piece
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
          if (checkWinningPosition2(board, rows, cols) == 10) {      //checks for win
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
          else if (checkDraw(board, rows, cols)) {                 //checks for draw
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
          if (((rows > 40) && (rows <= 100)) || ((cols > 40) && (cols <= 100))) {           //allows user to update medium board
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
      case '2':                                       //player vs player case
        newgame_2:
        player = 0;
        if ((rows > 100) || (cols > 100)) {                 //prints board
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
          if (!player) {                                   //determines player
            printf("Player 1's turn.\n");
          }
          else if (player) {
            printf("Player 2's turn.\n");
          }
          printf("What column would you like to play in?");     //player input for placing piece
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
          play_col--;                                           //places piece
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
          if (checkWinningPosition2(board, rows, cols) == -10) {            //checks for player 1 win
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
          else if (checkWinningPosition2(board, rows, cols) == 10) {         //checks for player 2 win
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
          else if (checkDraw(board, rows, cols)) {                           //checks for draw
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
          player = !player;                                                //changes player
          if (((rows > 40) && (rows <= 100)) || ((cols > 40) && (cols <= 100))) {    //allows player to update board
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
      case '3':                                    //stats screen case
        printRecentStats(memP1Wins, memP2Wins, memPPDraws, memPWins, memCWins, memPCDraws);    //prints stats screen
        printf("Press E to exit.\n");              //checks player input for exiting stats screen
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
      case '4':                                   //exiting program case
        return 0;
        break;
      default:                                    //checks incorrect input for menu navigation
        if (menu_select == '\n') {
          printf("That is not a valid selection!\n");
          printf("Selection: ");
        }
        menu_select = getchar();
        break;
      }
    }

  freeArray(board, rows, cols);                    //frees memory for board array

  return 0;                                        //should not be reached
}
