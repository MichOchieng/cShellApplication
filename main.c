#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define cdPath "util/changeDirectory.c"
#define lsPath "util/listShows.c"
#define echoPath "util/echo.c"
#define catPath "util/concatenate.c"


void shell();
// void listShows();
// void changeDirectory();
// void concatenate();
// void ecco();
void execute(char ** args);
void terminate();
char * reader();
char ** parser();
void welcome();

int main(){   
    shell(); 
    return 0;
}

void shell(){    
    welcome();
    bool on = true;
    // Will always run at very least once
    do{       
    //    parser(reader());
       execute(parser(reader()));
    }while(on); 
}

// Returns pointer to users input
char * reader(){
    unsigned int n = 1; // Size of the input string
    unsigned int i = 0; // Used for looping through char array
    // Allocate memory
    char * input = (char*) malloc(sizeof(char) * pow(2,n)); // Allocates memory, char type pointer
    // Fill memory with input
    if(input !=NULL){ // Wont take in any loose pointers
        // While the user is inputing and hasn't hit enter
        char nextChar;
        while ((nextChar = getchar()) != '\n')
        {           
            // Add their input to the allocated memory block
            input[i] = nextChar;            
            // If the memory block is too small for their input
            if(i == pow(2,n)){
                // Increase the size of the alloted memory
                // printf("Increasing alloted memory...\n");
                n++;
                input = realloc(input, pow(2,n)*sizeof(char));
                // printf("Increase successful!\n");
            }
            i++;
        }        
    }   
    printf("You entered: %s\n",input);
    return input;
}

// Returns a command and argument
char ** parser(char * input){
    unsigned int n = 1; // Size of the parse array  
    unsigned int i = 0; // Used for looping through parse array  
    // Will contain tokens from the input array for later use
    char ** parseArray = malloc(sizeof(char) * pow(2,n));
    // Delimeters for strtok method
    const char delims[] = " \n\t\r\v\f";
    // Temperary holder for input string tokens
    char * token = strtok(input,delims);   

    while (token != NULL)
        {           
            // Add token to parse array
            parseArray[i] = token;            
            // If the memory block is too small for their input
            if(i == pow(2,n)){
                // Increase the size of the alloted memory
                printf("Increasing alloted memory...\n");
                n++;
                parseArray = realloc(parseArray, pow(2,n)*sizeof(char*));
                printf("Increase successful!\n");
            }
            i++;
            token = strtok(NULL,delims);
        }    
    return parseArray;
}

void execute(char ** args){
    int thisID = fork();

    char *cd = "cd";
    char *ls = "ls";
    char *echo = "echo";
    char *cat = "cat";
    // Handles child process 
    if (thisID == 0){
        printf("---child born\n");
        if (strcmp(args[0],cd) == 0){
            printf("Send to CD file\n");
        }else if (strcmp(args[0],ls) == 0){
            printf("Send to ls file\n");
        }else if (strcmp(args[0],echo) == 0){
            printf("Send to echo file\n");
        }else if (strcmp(args[0],cat) == 0){
            printf("Send to cat file\n");
        }else{
            // printf(*args[0],": command not found %p\n");
        }                      
    }
    else if(thisID < 0){
        // Error in forking
        printf("Error forking, exitting.");
        exit(0);
    }
    else{
        // Wait for the child process
            
    }
    
}

void welcome(){
    printf("Welcome to my shell.\n");
}