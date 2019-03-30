cfour: cfourmain.c
	gcc -Wall -std=c11 InitialMenus.h SecondaryMenus.h GraphFunctions.h ResultChecker.h BoardHandling.h cfourmain.c -lm -o cfour
