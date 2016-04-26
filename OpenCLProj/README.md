ROLLIN Antoine (ra408576)

# Concurrent Systems #


Source files (/src) :
- main.c : contains the main program
- project.c : contains the treatment matrix function (Taylor)
- utils.c : contains the argument parsing and display functions
---
- matrix.c : contains the matrix functions (init, heat, free, etc.)
- region.c : contains the region functions (creation, etc.)
---
- argument.c : contains the structure of a thread function parameter 
- condbarrier.c : contains the barrier implementation using condition variables
- sembarrier.c : contains the barrier implementation using semaphores
---
- version0.c : contains the treatments functions for the first step (iterative)
- version1.c : contains the treatments functions for the second step (posix barrier)
- version2.c : contains the treatments functions for the third step (barrier with condition variable)
- version3.c : contains the treatments functions for the fourth step (barrier with semaphore)


Binary file (/bin) - after compilation : 
- project : executable used to launch the program


Compilation : 	make
Execution :	./bin/project [-options]

Options:	
-i [N] -e [0-5] -s [0-9] -t [0-5] -m -M -a
