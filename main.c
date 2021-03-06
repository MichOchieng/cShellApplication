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
int terminate();
char * reader();
char ** parser();
void changeDirectory(char ** input);
char * workingDir();
void printString();
void welcome();

DIR *dir;
struct dirent *name;
char * input;
char ** parseArray;

int main(int argc, char ** argv){   
    if (argc > 1)
    {
        printString(argv);
    }else{
        shell();
    }     
    return 0;
}

void shell(){    
    welcome();
    bool on = true;
    // Will always run at very least once
    do{        
       execute(parser(reader()));  
       input = NULL;
       parseArray = NULL;
       free(input);
       free(parseArray);          
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
    input = (char*) malloc(sizeof(char) * pow(2,n)); // Allocates memory, char type pointer
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
    unsigned int n = 1; // Size of the parse array  
    unsigned int i = 0; // Used for looping through parse array  
    // Will contain tokens from the input array for later use
    parseArray = malloc(sizeof(char) * pow(2,n));
    // Regular delimeters for strtok method
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
                // printf("Increasing alloted memory...\n");
                n++;
                parseArray = realloc(parseArray, pow(2,n)*sizeof(char*));
                // printf("Increase successful!\n");
            }
            i++;
            token = strtok(NULL,delims);
        }  
    parseArray[i] = NULL;     
    return parseArray;
}

void execute(char ** args){
    int status;
    int thisID = fork();
    char *paths[]={"cd","cat","ls","util/echo"};

    char *cd = "cd";
    char *ls = "ls";
    char *l = "l";    
    char *echo = "echo";
    char *cat = "cat";
    char *exitt = "exit";
    // Handles child process 
    if (thisID == 0){       
        // Directs to correct command based on the first token in the args array
        // Using execvp so that I can access the exe files even after changing directories
        if (strcmp(args[0],cd) == 0){            
            // No child born
            changeDirectory(args);
        }else if (strcmp(args[0],ls) == 0 || strcmp(args[0],l) == 0 ){            
            execvp(paths[2],args);            
        }else if (strcmp(args[0],echo) == 0){
            execvp(paths[3],args);
        }else if (strcmp(args[0],cat) == 0){
            execvp(paths[1],args);
        }else if (strcmp(args[0],exitt) == 0){
            terminate();        
        }else{
            // Handles undefined commands
            printf("%s",args[0]);
            printf(": command not found \n");
        }                      
    }
    else if(thisID == -1){
        // Error in forking
        printf("Error forking.");        
    }
    else{
        // Wait for the child process   
        wait(&status);                  
    }    
}

// Changes directory depending on the given inputs (Doesn't use quotation marks)
void changeDirectory(char ** input){
    unsigned int n = 1;       
    char * directory = malloc(sizeof(char) * pow(2,n));
    // Should place white space between tokenized path names
    if (input[2] != NULL){        
        int i = 1;        
        while (input[i] != NULL){
            directory = strcat(directory,input[i]);
            if(input[i+1]!=NULL){
                // Will only add white space to tokens in the middle of path (wont add to last element)
                directory = strcat(directory," ");
            }            
            if(i == pow(2,n)){
                // Increase the size of the alloted memory                
                n++;
                directory = realloc(directory, pow(2,n)*sizeof(char*));                
            }
            i++;
        }          
        if (chdir(directory) != 0){
            printf("%s",directory);
            printf(": No such file in directory");
        }        
        directory = NULL;    
        free(directory);    
    }        
    else if(chdir(input[1]) != 0){        
        printf("%s",input[1]);
        printf(": No such file in directory \n");     
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
    buf = NULL;
    free(buf);
    return dirName;
}

int terminate(){    
    char c;
    printf("Are you sure you want to exit? [y/n]\n");
    c = getchar();
    if (c == 'y'){
        kill(0,SIGKILL);
    }
    else if(c == 'n'){
        printf("Returning to shell...\n");
        shell();
    }
    else{
        printf(": is not an option, try again.\n");
    }   
}

// Takes command line arguments and prints them
void printString(char ** args){
    int i = 1;    
    while (args[i] != NULL){        
        printf("%s",args[i]);
        printf(" ");
        i++;
    }
    printf("\n");
}

void welcome(){
    char *fileName = "welcome";
    FILE *file;
    file = fopen(fileName,"r");
    if(file == NULL){
        printf("File cannot be opened.\n");
        exit(0);
    }  
    char c = fgetc(file);
    while(c!=EOF){
        printf("%c",c);
        c = fgetc(file);
    }
    fclose(file);
}
