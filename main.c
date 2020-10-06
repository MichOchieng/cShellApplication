#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "headers/main.h"

void shell();
void test();
void listShows();
void changeDirectory();
void concatenate();
void ecco();
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
        // Takes in user input
        parser(reader());    
        // Parses input

        // Executes command
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
            printf("Token: %s\n",token);
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

void welcome(){
    printf("Welcome to my shell.\n");
}