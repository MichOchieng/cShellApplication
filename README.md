Basic Shell 
==================================
Basic shell application that supports ls,cat,echo and cd commands.
# Functions

void  changeDirectory(char ** input); &emsp;&emsp;&emsp; // Changes directory to that of the given input\
void  shell();  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; // Runs the shell until user exits\
void  printString();  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; // Takes command line arguments and prints them\
void  execute(char ** args);  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; // Depending on input will execute shell functions (ls,cat,echo,cd and exit)\
void welcome(); &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; // Loads welcome message to shell\
char * workingDir();&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; // Returns the current working directory\
char * reader(); &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; // Returns pointer to users input\
char ** parser(); &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; // Returns a command and argument\
int terminate();  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; // Kills the shell depending on user input\


