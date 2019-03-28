#include <stdio.h>

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
