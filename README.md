# <p align = "center">Project1</p>
# <p align = "center">Connect Four Instructions</p>
## <p align = "center">CS 201</p>
#### <p align = "center">Nathan Hayes - 3/30/19</p> 

**Setup Procedure**

&ensp;&ensp;&ensp;&ensp;On first use of this program, run `make` in the Ubuntu command line.
This will compile the program `cfourmain.c` alongside multiple helper files containing functions, such
as `BoardHandling.h`, `ResultChecker.h`, `GraphFunctions.h`, `SecondaryMenus.h`, and `InitialMenus.h`. If, 
for some reason, there is an issue with the makefile, the full compilation command is as follows:
`gcc -Wall -std=c11 BoardHandling.h ResultChecker.h GraphFunctions.h SecondaryMenus.h InitialMenus.h cfourmain.c -lm -o cfour`.
This will create an executable file named `cfour`, which can be run using `./cfour`.

**Startup Procedure**

&ensp;&ensp;&ensp;&ensp;Once the program has started, it will print an introductory Connect Four logo. After this, it will
prompt the user to enter the number of rows and columns they would like for the board. This is set at the beginning of program
execution, and cannot be changed during runtime; however, the user has the option to quickly exit the program from the main
menu, enabling a simple second execution to change the board size. The prompts for the board size allow integer inputs greater than 4,
so as to preserve the win condition of Connect Four that requires four pieces to be connected in a row. Any non-integer inputs
will be handled by a few error checking statements, preventing infinite loops or unintentional output while re-prompting the user
for correct input. Very large board sizes are acceptable, as the program is capable of allocating memory up to very large dimensions
(100,000 being the highest tested value for allocating memory); however, this will render the runtime of functions used for playing
the game excessively long. Once proper dimensions have been read in from user input, the program will then print the menu used
for selecting a game mode, viewing statistics from games played during the full execution of the program, and exiting the program.

#### <p align = "center">Menu Options</p>

**Player vs Computer**

&ensp;&ensp;&ensp;&ensp;M
