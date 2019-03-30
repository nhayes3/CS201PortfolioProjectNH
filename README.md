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

