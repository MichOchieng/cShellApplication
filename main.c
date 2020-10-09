#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>

void shell();
void execute(char ** args);
void terminate();
char * reader();
char ** parser();
void changeDirectory(char ** input);
char * workingDir();
void welcome();

DIR *dir;
struct dirent *name;

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
       execute(parser(reader()));
    }while(on); 
}

// Returns pointer to users input
char * reader(){
    char * dirName = workingDir();
    printf("%s",dirName);
    printf(": ");
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
    char *exit = "exit";
    // Handles child process 
    if (thisID == 0){       
        // Directs to correct command based on the first token in the args array
        if (strcmp(args[0],cd) == 0){            
            // No child born
            changeDirectory(args);
        }else if (strcmp(args[0],ls) == 0 || strcmp(args[0],l) == 0 ){
            execv(paths[2],args);
        }else if (strcmp(args[0],echo) == 0){
            execv(paths[3],args);
        }else if (strcmp(args[0],cat) == 0){
            execv(paths[1],args);
        }else if (strcmp(args[0],exit) == 0){
            terminate();
        }else{
            // Handles undefined commands
            printf("%s",args[0]);
            printf(": command not found \n");
        }                      
    }
    else if(thisID == -1){
        // Error in forking
        printf("Error forking, exitting.");        
    }
    else{
        // Wait for the child process   
        wait(&status);           
    }
    
}

void changeDirectory(char ** input){
    if (input[2] != NULL){
        printf("Too many arguments given\n");
    }else{        
        chdir(input[1]);
    }   
}

// Returns the current working directory (from example in source 10)
char * workingDir(){
    long size = pathconf(".",_PC_PATH_MAX);
    char * dirName; 
    char * buf;
    if((buf = (char *)malloc((size_t)size))!= NULL){
        dirName = getcwd(buf,(size_t)size);
    }
    return dirName;
}

void terminate(){    
    char c;
    printf("Are you sure you want to exit? [y/n]\n");
    c = getchar();
    if (c == 'y'){
        printf("Goodbye\n");
        exit(0);
    }
    else if(c == 'n'){
        printf("Returning to shell...\n");
        shell();
    }
    else{
        printf(": is not an option, try again.\n");
    }   
}

void welcome(){
    printf("Welcome to my shell.\n");
}