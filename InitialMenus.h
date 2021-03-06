#include <stdio.h>

/*
 * printLogo function with void return type and no parameters
 * This function simply prints the Connect Four logo at program startup.
 */
void printLogo() {
  printf("/\\-------------------------------------------------------------/\\\n");
  printf("|  _____   _____                    ____   ____  _____          |\n");
  printf("| |       |     |  |\\   |  |\\   |  |      |        |      |   | |\n");
  printf("| |       |     |  | \\  |  | \\  |  |___   |        |      |___| |\n");
  printf("| |       |     |  |  \\ |  |  \\ |  |      |        |          | |\n");
  printf("| |_____  |_____|  |   \\|  |   \\|  |____  |____    |          | |\n");
  printf("|                                                               |\n");
  printf("\\/-------------------------------------------------------------\\/\n");
  printf("     _______________________________________________________\n");
  printf("    |     CS 201 Project: Connect Four by Nathan Hayes      |\n");
  printf("    |     CWID: 11780930                       3/29/19      |\n");
  printf("    |_______________________________________________________|\n");
}

/*
 * createMenuScreen function with void return type and no parameters
 * This function prints the menu screen and prompts the user for a selection.
 * The selection is handled in the main function, alongside error checking for
 * the corresponding inputs. This is called at startup, and after any submenu
 * is exited.
 */
void createMenuScreen() {
  printf(" ____________________________ \n");
  for (int i = 0; i < 8; i++) {
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
        printf("| 4: Quit Program            |\n");
        break;
      default:
        printf("|                            |\n");
    }
  }
  printf("|____________________________|\n");
  printf("\nSelection: ");
}
