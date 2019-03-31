# <p align = "center">Portfolio Project</p>
# <p align = "center">Connect Four Instructions</p>
## <p align = "center">CS 201&ensp;-&ensp;Dr. Monica Anderson Herzog</p>
#### <p align = "center">Nathan Hayes - 3/30/19</p>
#### <p align = "center">Github User: nhayes3&ensp;&ensp;&ensp;Github ID: 48812998</p>

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

&ensp;&ensp;&ensp;&ensp;Once the menu has been printed, it reads in user input into a character variable, with '1' corresponding to
the player vs computer game option. This input is error checked as well, with any input that does not correspond to one of the menu
options being caught by the default case in the following case statement. The input is then buffered until a newline occurs, preventing
the while loop from printing the error statement too many times. As soon as the case for player vs computer is entered, a series of
if statements determines how the board is printed. This is covered two sections down, under *Board Size Handling*. While any size board,
within the limits of the memory allocation mentioned above, can be printed, the computer algorithm, described in the next paragraph,
does have runtime limitations for larger board sizes. Around dimensions of 500 x 500 it starts experiencing some slowdown, with most
dimensions under this running within a time reasonable for playing. Around dimensions of 1000 x 1000 it experiences major slowdown,
with the algorithm still returning a move within one minute thirty seconds - playable, but slower than some users may prefer. While the
algorithm can still successfully analyze boards larger than this, the runtime will continue to increase, making 1000 x 1000 the 
preferable limit. 

&ensp;&ensp;&ensp;&ensp;Once the game has been started, the program will prompt the user for the column they wish to play in. 
Depending on the size of the board, the player may be able to see all possible columns or not; however, they will be able to
enter any integer between 1 and the number of columns they entered at the program's start regardless of how much of the board is
displayed. Once again, error checking is employed when this user input is accepted, this time also checking for full columns and
integers outside the range of the board. Once proper input is accepted, functions are used to determine the proper row to place
the piece in, and the computer algorithm is called in order to determine the computer's optimal move.

&ensp;&ensp;&ensp;&ensp;For the purposes of this Connect Four program, the computer's optimal move is assumed to meet one of three
quantifiers. The first one simply checks to see if the computer has a way to win in one move. If this is the case, the computer will
make that move and end the game. The second one simply checks to see if the player has a way to win if it was their move. If this
is the case, the computer will make that move first, thus blocking the player from winning. Finally, the third quantifier employs a
variation of the minimax algorithm, a popular algorithm used for traversing all possible future positions in the game. It takes
advantage of the two-dimensional array data structure by building a graph out of all possible positions, oscillating between
player and computer moves to simulate all possible future positions to a specified depth. This algorithm is somewhat inefficient
without other algorithms to help store data, which is why the first two cases and a depth limit are employed. The variation of this
minimax algorithm used is based off of [an algorithm designed by Pascal Pons](http://blog.gamesolver.org/solving-connect-four/03-minmax/). Once it reaches a certain depth, it evaluates the score of each position, which form the leaves of the constructed tree.
This score is determined by another function, which assigns points based off of the number of pieces each player has, as well as
how many of those pieces are connected. It interprets the optimal move as a move which minimizes the number of two- and three-in-a-row
pieces the player has, while maximizing the number of two- and three-in-a-row pieces the computer has. The minimax algorithm then
returns the column that corresponds to the maximum leaf score found, and the main function then places the piece accordingly, passing
the move back to the player. Of course, whenever the move is passed between player and computer, the main function also calls functions
to check if either player has won, or if the board is full and a draw has been reached. Specifications on these functions can be
found in the comments of the source code. The description of what happens once a game is completed can be found three sections down,
in *Game Conclusion Handling*.

**Player vs Player**

&ensp;&ensp;&ensp;&ensp;This option is accessed similarly to the description of **Player vs Computer** above, with user input of '2'.
The same error checking on the input occurs, and the board is then printed in a way dependent on the dimensions, as described in the
next section, *Board Size Handling*. This gamemode uses a player boolean variable to determine whether it is Player 1 or Player 2 to
move, with false corresponding to Player 1 and true corresponding to Player 2. It prompts the appropriate player to move, and then
accepts user input with the same process and error checking as described in **Player vs Computer**, paragraph 2. It also checks if
either player has won or if the board is full and the game is a draw after each move. Once again, when the game is completed,
the program goes through the process described two sections below, *Game Conclusion Handling*.

*Board Size Handling*

&ensp;&ensp;&ensp;&ensp;Given the ASCII-based interface of this program, large board sizes cannot be printed in their entirety without
very poor formatting. As a result, this program uses three different functions, with each one corresponding to a different size range,
in order to display the board in a readable way, even if the entire board is never displayed. For boards sized with both dimensions larger than 4 but smaller than 40, the entire
board is printed, with ASCII characters surrounding the contents of the board array. For very small monitors, this may still cause
formatting issues, but for the standard sizes that this program was tested on, the entire Connect Four board will be displayed
without any awkward formatting. For boards sized with either dimension larger than 40 but both smaller than 100, the user will be prompted to pick which section of the board
they would like to view. The board is broken up into four segments, each representing a "corner" of the board. User input is accepted,
with '1' corresponding to the top left of the board (0 to half of the columns and 0 to half of the rows), '2' corresponding to the
top right of the board (half of the columns to the total columns and 0 to half of the rows), '3' corresponding to the bottom left
of the board (0 to half of the columns and half of the rows to the total rows), and '4' corresponding to the bottom right of the
board (half of the columns to the total columns and half of the rows to the total rows). Of course, error checking is done for this
input as well. For boards sized with either dimension larger than 100, the user will be prompted to pick a column to play in without
being able to see the board, for their first move only. After this, the board handling function will print a subsection of the board,
corresponding to 20 spaces in every cardinal direction from the piece that was just played. To help the player accurately input their
move in large boards, column numbers from 1 to 99 are displayed beneath the column they correspond to; due to the limitations of the
ASCII-based interface, numbers larger than three digits are not displayed. For this final board display function, if statements
protect the loops as they search 20 spaces in cardinal directions, so as to prevent the function from accessing the array out of bounds.
This is true for other functions that traverse the array as well, such as the board scoring function for the computer algorithm, and the
winning position checking function.

*Game Conclusion Handling*

&ensp;&ensp;&ensp;&ensp;Once one of the win or draw checking functions evaluates to true, the program then executes two functions.
First, it prints out the win/draw statistics of that sequence of games. Then, it prompts the player to play again. If the user
inputs 'Y'/'y', the win/draw statistics are maintained, and a new game is started. If the user inputs 'N'/'n', the win/draw
statistics are copied to other variables, which are maintained in the menu option covered in the next section, **Recent Statistics**.
Then, the program exits to the main menu, letting the user pick between the options again. This user input is once again checked
for incorrect input, preventing loops or unintended output from occuring if the user enters incorrect characters, or strings of
characters.

**Recent Statistics**

&ensp;&ensp;&ensp;&ensp;This option is accessed similarly to the process described at the start of **Player vs Computer**, with user
input of '3'. It displays all of the win/draw statistics stored during the duration of the entire program. This allows the user to
see their total number of wins, losses, or draws against either the computer or another player, in addition to being able to view
those same statistics for only a sequence of games after each game. User input is used to exit this screen and return to the main
selection menu as well, with similar error checking for inputs that are not 'E' or 'e'.

**Exit Program**

&ensp;&ensp;&ensp;&ensp;This option is accessed similar to the process described at the start of **Player vs Computer**, with user
input of '4'. It simply ends program execution.

**Youtube Video Overview**

&ensp;&ensp;&ensp;&ensp;[This video](https://www.youtube.com/watch?v=adW6XKbHWNE) briefly shows the files included in the program and
demonstrates proper execution of all the functionality included in this program. 

<p align = "center"><a href="http://www.youtube.com/watch?feature=player_embedded&v=adW6XKbHWNE" target="_blank"><img src="http://img.youtube.com/vi/adW6XKbHWNE/0.jpg" alt="preview" width="240" height="180" border="10" /></a></p>
