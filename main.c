#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

void shell();
void execute(char ** args);
void terminate();
char * reader();
char ** parser();
void welcome();

struct inputInfo{
    char ** parseArray;
    int parseArrayLength;
};

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
    return input;
}

// Returns a command and argument
char ** parser(char * input){
    struct inputInfo inputInfo;

    unsigned int n = 1; // Size of the parse array  
    unsigned int i = 0; // Used for looping through parse array  
    // Will contain tokens from the input array for later use
    inputInfo.parseArray = malloc(sizeof(char) * pow(2,n));
    // Delimeters for strtok method
    const char delims[] = " \n\t\r\v\f";
    // Temperary holder for input string tokens
    char * token = strtok(input,delims);   

    while (token != NULL)
        {           
            // Add token to parse array
            inputInfo.parseArray[i] = token;            
            // If the memory block is too small for their input
            if(i == pow(2,n)){
                // Increase the size of the alloted memory
                // printf("Increasing alloted memory...\n");
                n++;
                inputInfo.parseArray = realloc(inputInfo.parseArray, pow(2,n)*sizeof(char*));
                // printf("Increase successful!\n");
            }
            i++;
            token = strtok(NULL,delims);
        }
       inputInfo.parseArrayLength = i;
    return inputInfo.parseArray;
}

void execute(char ** args){
    int status;
    int thisID = fork();
    char *paths[]={"util/cd","util/cat","util/ls","util/echo"};

    char *cd = "cd";
    char *ls = "ls";
    char *l = "l";    
    char *echo = "echo";
    char *cat = "cat";
    // Handles child process 
    if (thisID == 0){       
        // Directs to correct command based on the first token in the args array
        if (strcmp(args[0],cd) == 0){            
            execv(paths[0],args);
        }else if (strcmp(args[0],ls) == 0 || strcmp(args[0],l) == 0 ){
            execv(paths[2],args);
        }else if (strcmp(args[0],echo) == 0){
            execv(paths[3],args);
        }else if (strcmp(args[0],cat) == 0){
            execv(paths[1],args);
        }else{
            // Handles undefined commands
            printf("%s",args[0]);
            printf(": command not found \n");
        }                      
    }
    else if(thisID == -1){
        // Error in forking
        printf("Error forking, exitting.");
        exit(0);
    }
    else{
        // Wait for the child process   
        wait(&status);           
    }
    
}

void terminate(){
    // Ask's if user wants to leave fr
    // Yes -> exit() No-> back to main
}

void welcome(){
    printf("Welcome to my shell.\n");
}