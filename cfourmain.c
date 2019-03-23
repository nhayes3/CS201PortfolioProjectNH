#include <stdio.h>
#include <stdlib.h>

struct node {
  int xCoor;
  int yCoor;
  int player1;
  int player2;
  int filled;
  struct piece *topLeft;
  struct piece *left;
  struct piece *botLeft;
  struct piece *bot;
  struct piece *botRight;
  struct piece *right;
  struct piece *topRight;
  struct piece *top;
};

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

void createBoardScreen() { //int column, int row) {
  printf(" __________________________________ \n");
  for (int i = 1; i <= 6; i++) {
    //if (i == row) {

    //}
    printf("|    |    |    |    |    |    |    |\n");
    printf("|    |    |    |    |    |    |    |\n");
    printf("|____|____|____|____|____|____|____|\n");
  }
}

int main(void) {
  createMenuScreen();

  int menu_select;
  int play_col;
  //struct node* Piece = (struct node*)malloc(sizeof(struct node));

  select_again:
  scanf("%d", &menu_select);
  switch(menu_select) {
    case 1:
      printf("1");
      break;
    case 2:
      createBoardScreen();
      //enter number of rows
      //enter number of columns
      //error checking for r,c < 0 or r,c too large
      printf("What column would you like to play1 in?");
      scanf("%d", &play_col);
      /*if (play_col == 1) {
        *Piece->xCoor = 1;
        *Piece->topLeft = NULL;
        *Piece->left = NULL;
        *Piece->botLeft = NULL;
        *Piece->player1 = 1;
        *Piece->player2 = 0;
        *Piece->filled = 1;
      *}
      *else if (play_col == 7) {
      *  Piece->xCoor = 7;
      *  Piece->topRight = NULL;
      *  Piece->right = NULL;
      *  Piece->botRight = NULL;
      *  Piece->player1 = 1;
      *  Piece->player2 = 0;
      *  Piece->filled = 1;
      *}
      *else {
      *  Piece->xCoor = play_col;
      *  Piece->player1 = 1;
      *  Piece->player2 = 0;
      *  Piece->filled = 1;
    }*/
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
