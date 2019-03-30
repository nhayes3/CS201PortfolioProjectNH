#include <stdio.h>
#include <stdbool.h>

/*
 * printStandingsScreen function with void return type and four parameters
 * This function prints the standings screen after a Connect Four game has
 * been completed. The isPvC variable determines whether it prints the
 * menu for player vs computer or player vs player standings, and the three
 * stats passed correspond to the wins per side and draws. This menu
 * displays values only for sequences of games; if the player decides
 * to not play again, the stats reset to 0, and the stats shown here are
 * stored in the stats option in the main menu.
 */
void printStandingsScreen(bool isPvC, int stat1, int stat2, int draws) {
  printf(" ___________________\n");
  if (isPvC) {                                    //prints player vs computer standings
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
    if (draws < 10) {
      printf("| Draws: %d          |\n", draws);
    }
    else {
      printf("| Draws: %d         |\n", draws);
    }
  printf("|___________________|\n");
  }
  else if (!isPvC) {                            //prints player vs player standings
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
    if (draws < 10) {
      printf("| Draws: %d          |\n", draws);
    }
    else {
      printf("| Draws: %d         |\n", draws);
    }
    printf("|___________________|\n");
  }
}

/*
 * printRecentStats function with void return type and six parameters
 * This function prints the overall win/loss/draw stats for both player vs
 * computer and player vs player games throughout the execution of the entire
 * program. It is called from the main selection menu, and prints out each
 * of the six stats. If statements are used to keep the menu frame consistent
 * for both one and two digit numbers.
 */
void printRecentStats(int p1W, int p2W, int ppDraws, int pW, int cW, int pcDraws) {
  printf(" ____________________________________________ \n");
  printf("|          Player vs. Player Stats           |\n");
  if (p1W < 10) {                                                          //spacing for one digit values
    printf("| Player 1 Wins: %d                           |\n", p1W);
  }
  else {                                                                   //spacing for two digit values
    printf("| Player 1 Wins: %d                          |\n", p1W);
  }
  if (p2W < 10) {
    printf("| Player 2 Wins: %d                           |\n", p2W);
  }
  else {
    printf("| Player 2 Wins: %d                          |\n", p2W);
  }
  if (ppDraws < 10) {
    printf("| Draws: %d                                   |\n", ppDraws);
  }
  else {
    printf("| Draws: %d                                  |\n", ppDraws);
  }
  printf("|                                            |\n");
  printf("|         Player vs. Computer Stats          |\n");
  if (pW < 10) {
    printf("| Player Wins: %d                             |\n", pW);
  }
  else {
    printf("| Player Wins: %d                            |\n", pW);
  }
  if (cW < 10) {
    printf("| Computer Wins: %d                           |\n", cW);
  }
  else {
    printf("| Computer Wins: %d                          |\n", cW);
  }
  if (pcDraws < 10) {
    printf("| Draws: %d                                   |\n", pcDraws);
  }
  else {
    printf("| Draws: %d                                  |\n", pcDraws);
  }
  printf("|____________________________________________|\n");
}

/*
 * printPlayAgainScreen function with void return type and no parameters
 * This simply prints a menu prompt for the player to choose to play again
 * or not. Response handling is in the main .c file.
 */
void printPlayAgainScreen() {
  printf(" ____________________\n");
  printf("| Play again?        |\n");
  printf("| Y: Yes             |\n");
  printf("| N: No              |\n");
  printf("|____________________|\n");
}
