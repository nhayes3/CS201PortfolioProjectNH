#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

void printLogo() {
  printf("/\\----------------------------------------------------/\\\n");
  printf("|  _____   _____                    ____   ____  _____ |\n");
  printf("| |       |     |  |\\   |  |\\   |  |      |        |   |\n");
  printf("| |       |     |  | \\  |  | \\  |  |___   |        |   |\n");
  printf("| |       |     |  |  \\ |  |  \\ |  |      |        |   |\n");
  printf("| |_____  |_____|  |   \\|  |   \\|  |____  |____    |   |\n");
  printf("|                                                      |\n");
  printf("\\/----------------------------------------------------\\/\n");
  printf(" _______________________________________________________\n");
  printf("| CS 201 Project: Connect Four by Nathan Hayes          |\n");
  printf("| CWID: 11780930                      3/29/19           |\n");
  printf("|_______________________________________________________|\n");
}
//add 4 to CONNECT 4 logo
//center text in intro box
//add extra line above text in box
void createMenuScreen() {
  printf(" ____________________________ \n");
  for (int i = 0; i < 10; i++) {
    switch(i) {
      case 1:
        printf("| 1: Play vs. Computer       |\n");
        break;
      case 3:
        printf("| 2: Play vs. Human          |\n");
        break;
      case 5:
        printf("| 3: Recent Stats            |\n");
        break;
      case 7:
        printf("| 4: Change Board Size       |\n");
        break;
      case 9:
        printf("| 5: Quit Program            |\n");
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

int placePiece(int rows, int cols, char board[rows][cols], int colPlayed) {
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

bool checkDraw(int rows, int cols, char board[rows][cols]) {
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

int negamax(int rows, int cols, char board[rows][cols], bool player, int alpha, int beta, int numMoves) {
  if(checkDraw(rows, cols, board)) {
    return 0;
  }
  int h;
  int bestrow;
  for (h = 0; h < cols; h++) {
    if (board[0][h] == ' ') {
      bestrow = placePiece(rows, cols, board, h);
      if (player) {
        board[bestrow][h] = 'o';
        if (checkWinningPosition2(rows, cols, board) == 10) {
          board[bestrow][h] = ' ';
          return h;
        }
        board[bestrow][h] = ' ';
      }
      else if (!player) {
        board[bestrow][h] = 'x';
        if (checkWinningPosition2(rows, cols, board) == -10) {
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
      bestrow = placePiece(rows, cols, board, h);
      if (player) {
        board[bestrow][h] = 'o';
        int score = -negamax(rows, cols, board, !player, -beta, -alpha, numMoves++);
        board[bestrow][h] = ' ';
        if (score >= beta) return score;
        if (score > alpha) {
          alpha = score;
          bestCol = h;
        }
      }
      else if (!player) {
        board[bestrow][h] = 'x';
        int score = -negamax(rows, cols, board, !player, -beta, -alpha, numMoves++);
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

/*int maxFunc(int one, int two) {
*  if (one > two) return one;
*  else return two;
*}
*
*int minFunc(int one, int two) {
*  if (one > two) return two;
*  else return one;
*}
*
*int computeVal(int rows, int cols, char board[rows][cols], int depth, bool player, int alpha, int beta) {
*  int val = checkWinningPosition2(rows, cols, board);
*  int newrow;
*  int bestVal;
*  int c;
*  if (val == 10) {
*    return val;
*  }
*  else if (val == -10) {
*    return val;
*  }
*  else if (checkDraw(rows, cols, board)) {
*    return 0;
*  }
*  else if (depth == 10) {
*    return -1;
*  }
*  if (player) {
*    bestVal = -9999999;
*     if (board[0][c] == 'z') {
*        newrow = placePiece(rows, cols, board, c);
*        board[newrow][c] = 'o';
*        bestVal = maxFunc(bestVal, computeVal(rows, cols, board, depth + 1, !player, alpha, beta));
*        alpha = maxFunc(alpha, bestVal);
*        board[newrow][c] = 'z';
*        if (beta <= alpha) {
*          break;
*        }
*        //board[newrow][c] = 'z';
*      }
*    }
*    return bestVal;
*  }
*  else if (!player) {
*    bestVal = 9999999;
*    for (c = 0; c < cols; c++) {
*      if (board[0][c] == 'z') {
*        newrow = placePiece(rows, cols, board, c);
*        board[newrow][c] = 'x';
*        bestVal = minFunc(bestVal, computeVal(rows, cols, board, depth + 1, !player, alpha, beta));
*        beta = minFunc(beta, bestVal);
*        board[newrow][c] = 'z';
*        if (beta <= alpha) {
*          break;
*        }
*        //board[newrow][c] = 'z';
*      }
*    }
*    return bestVal;
*  }
*}
*
*int bestMove(int rows, int cols, char newAr[rows][cols]) {
*  int bestMove = 0;
*  int bestMoveVal = -1000;
*  int l;
*  int newrow;
*  int val;
*  for (l = 0; l < cols; l++) {
*    if (newAr[0][l] == 'z') {
*      newrow = placePiece(rows, cols, newAr, l);
*      newAr[newrow][l] = 'o';
*      val = computeVal(rows, cols, newAr, 0, 1, -9999999, 9999999);
*      newAr[newrow][l] = 'z';
*      if (val > bestMoveVal) {
*        bestMoveVal = val;
*        bestMove = l;
*      }
*    }
*  }
*  printf("%d ", bestMove);
*  return bestMove;
}*/

void copyArray(int rows, int cols, char board[rows][cols], char temp[rows][cols]) {
  int p;
  int q;
  for (p = 0; p < rows; p++) {
    for (q = 0; q < cols; q++) {
      temp[p][q] = board[p][q];
    }
  }
}

void printStandingsScreen(bool isPvC, int stat1, int stat2, int draws) {
  printf(" ___________________\n");
  if (isPvC) {
    if (stat1 < 10) {
      printf("| Player wins: %d    |\n", stat1);
    }
    else {
      printf("| Player wins: %d   |\n", stat1);
    }
    if (stat2 < 10) {
      printf("| Computer wins: %d  |\n", stat2);
    }
    else {
      printf("| Computer wins: %d |\n", stat2);
    }
    if (stat1 < 10) {
      printf("| Draws: %d          |\n", draws);
    }
    else {
      printf("| Draws: %d         |\n", draws);
    }
  printf("|___________________|\n");
  }
  else if (!isPvC) {
    if (stat1 < 10) {
      printf("| Player 1 wins: %d  |\n", stat1);
    }
    else {
      printf("| Player 1 wins: %d |\n", stat1);
    }
    if (stat2 < 10) {
      printf("| Player 2 wins: %d  |\n", stat2);
    }
    else {
      printf("| Player 2 wins: %d |\n", stat2);
    }
    if (stat1 < 10) {
      printf("| Draws: %d          |\n", draws);
    }
    else {
      printf("| Draws: %d         |\n", draws);
    }
    printf("|___________________|\n");
  }
}

void printRecentStats(int p1W, int p2W, int ppDraws, int pW, int cW, int pcDraws) {
  printf("meme");
}

void printPlayAgainScreen() {
  printf(" ____________________\n");
  printf("| Play again?        |\n");
  printf("| Y: Yes             |\n");
  printf("| N: No              |\n");
  printf("|____________________|\n");
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

  char board[rows][cols];

  char temp[rows][cols];
  memset(temp, ' ', sizeof temp);

  int playerOneWins, playerTwoWins, pvpDraws, playerWins, compWins, compDraws = 0;
  int memP1Wins, memP2Wins, memPPDraws, memPWins, memCWins, memPCDraws = 0;

  newexec:
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
  memset(board, ' ', sizeof board);
  createMenuScreen();

  int menu_select;
  while (1) {
    scanf("%d", &menu_select);
    switch(menu_select) {
      case 1:
        newgame_1:
        createBoardScreen(rows, cols, board);
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
            play_row = placePiece(rows, cols, board, play_col);
            board[play_row][play_col] = 'x';
            numMoves++;
            createBoardScreen(rows, cols, board);
            if (checkWinningPosition2(rows, cols, board) == -10) {
              printf("Human wins!\n");
              playerWins++;
              printStandingsScreen(1, playerWins, compWins, compDraws);
              printPlayAgainScreen();
              newGame = playAgainResponse();
              if (newGame) {
                memset(board, ' ', sizeof board);
                goto newgame_1;
              }
              else {
                goto newexec;
              }
              break;
            }
            else if (checkDraw(rows, cols, board)) {
              printf("It's a draw!\n");
              compDraws++;
              printStandingsScreen(1, playerWins, compWins, compDraws);
              printPlayAgainScreen();
              newGame = playAgainResponse();
              if (newGame) {
                memset(board, ' ', sizeof board);
                goto newgame_1;
              }
              else {
                goto newexec;
              }
              break;
            }
            printf("Computer thinking...\n");
            copyArray(rows, cols, board, temp);

          //printf("%d", bestMove(rows, cols, temp));
          //play_col = bestMove(rows, cols, temp);
          //play_row = placePiece(rows, cols, temp, play_col);
          //printf("%d ", play_row);
          //board[play_row][play_col] = 'o';

          //int bestScore = negamax(rows, cols, board, 1);
            play_col = negamax(rows, cols, board, 1, -9999999, 9999999, numMoves);
            play_row = placePiece(rows, cols, board, play_col);
            board[play_row][play_col] = 'o';
            numMoves++;
            createBoardScreen(rows, cols, board);
            if (checkWinningPosition2(rows, cols, board) == 10) {
              printf("Computer wins!\n");
              compWins++;
              printStandingsScreen(1, playerWins, compWins, compDraws);
              printPlayAgainScreen();
              newGame = playAgainResponse();
              if (newGame) {
                memset(board, ' ', sizeof board);
                goto newgame_1;
              }
              else {
                goto newexec;
              }
              break;
            }
            else if (checkDraw(rows, cols, board)) {
              printf("It's a draw!\n");
              compDraws++;
              printStandingsScreen(1, playerWins, compWins, compDraws);
              printPlayAgainScreen();
              newGame = playAgainResponse();
              if (newGame) {
                memset(board, ' ', sizeof board);
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
          else if (board[0][play_col - 1] != ' ') {
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
          if (checkWinningPosition2(rows, cols, board) == -10) {
            printf("Player 1 wins!\n");
            playerOneWins++;
            printStandingsScreen(0, playerOneWins, playerTwoWins, pvpDraws);
            printPlayAgainScreen();
            newGame = playAgainResponse();
            if (newGame) {
              memset(board, ' ', sizeof board);
              goto newgame_2;
            }
            else {
              goto newexec;
            }
            break;
          }
          else if (checkWinningPosition2(rows, cols, board) == 10) {
            printf("Player 2 wins!\n");
            playerTwoWins++;
            printStandingsScreen(0, playerOneWins, playerTwoWins, pvpDraws);
            printPlayAgainScreen();
            newGame = playAgainResponse();
            if (newGame) {
              memset(board, ' ', sizeof board);
              goto newgame_2;
            }
            else {
              goto newexec;
            }
            break;
          }
          else if (checkDraw(rows, cols, board)) {
            printf("It's a draw!\n");
            pvpDraws++;
            printStandingsScreen(0, playerOneWins, playerTwoWins, pvpDraws);
            printPlayAgainScreen();
            newGame = playAgainResponse();
            if (newGame) {
              memset(board, ' ', sizeof board);
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
        while (1) {
          scanf("%c", &exit);
          if (exit == 'E' || exit == 'e') {
            goto newexec;
          }
          else {
            printf("Invalid selection: use E to exit.\n");
          }
        }
        break;
      case 4:
        printf("4");
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
