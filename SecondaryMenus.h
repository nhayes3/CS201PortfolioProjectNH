#include <stdio.h>
#include <stdbool.h>

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
  if ((p1W < 10) && (p2W < 10) && (ppDraws < 10) && (pW < 10) && (cW < 10) && (pcDraws < 10)) {
    printf(" ____________________________________________ \n");
    printf("|          Player vs. Player Stats           |\n");
    printf("| Player 1 Wins: %d                           |\n", p1W);
    printf("| Player 2 Wins: %d                           |\n", p2W);
    printf("| Draws: %d                                   |\n", ppDraws);
    printf("|                                            |\n");
    printf("|         Player vs. Computer Stats          |\n");
    printf("| Player Wins: %d                             |\n", pW);
    printf("| Computer Wins: %d                           |\n", cW);
    printf("| Draws: %d                                   |\n", pcDraws);
    printf("|____________________________________________|\n");
  }
  else {
    printf(" _____________________________________________ \n");
    printf("|          Player vs. Player Stats            |\n");
    printf("| Player 1 Wins: %d                           |\n", p1W);
    printf("| Player 2 Wins: %d                           |\n", p2W);
    printf("| Draws: %d                                   |\n", ppDraws);
    printf("|                                             |\n");
    printf("|         Player vs. Computer Stats           |\n");
    printf("| Player Wins: %d                             |\n", pW);
    printf("| Computer Wins: %d                           |\n", cW);
    printf("| Draws: %d                                   |\n", pcDraws);
    printf("|_____________________________________________|\n");
  }
}

void printPlayAgainScreen() {
  printf(" ____________________\n");
  printf("| Play again?        |\n");
  printf("| Y: Yes             |\n");
  printf("| N: No              |\n");
  printf("|____________________|\n");
}
