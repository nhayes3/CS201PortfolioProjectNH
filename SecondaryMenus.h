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
    if (draws < 10) {
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
    if (draws < 10) {
      printf("| Draws: %d          |\n", draws);
    }
    else {
      printf("| Draws: %d         |\n", draws);
    }
    printf("|___________________|\n");
  }
}

void printRecentStats(int p1W, int p2W, int ppDraws, int pW, int cW, int pcDraws) {
  printf(" ____________________________________________ \n");
  printf("|          Player vs. Player Stats           |\n");
  if (p1W < 10) {
    printf("| Player 1 Wins: %d                           |\n", p1W);
  }
  else {
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
    printf("| Draws: %d                                  |\n", pcDraws);
  }
  printf("|____________________________________________|\n");
}

void printPlayAgainScreen() {
  printf(" ____________________\n");
  printf("| Play again?        |\n");
  printf("| Y: Yes             |\n");
  printf("| N: No              |\n");
  printf("|____________________|\n");
}
