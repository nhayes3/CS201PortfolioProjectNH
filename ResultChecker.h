#include <stdio.h>

/*
 * checkResults function with int return type and two parameters
 * This function simply prints out the result of a concluded game.
 * It is called after a result is determined in the main function,
 * and that result determines what this function prints. It then
 * returns the incremented stat that corresponds to the correct
 * result of the game.
 */
int checkResults(int updateStat, char result) {
  if (result == '1') {
    printf("Player 1 Wins!\n");
  }
  else if (result == '2') {
    printf("Player 2 Wins!\n");
  }
  else if (result == 'D') {
    printf("It's a Draw!\n");
  }
  else if (result == 'P') {
    printf("Player Wins!\n");
  }
  else if (result == 'C') {
    printf("Computer Wins!\n");
  }
  return ++updateStat;
}
