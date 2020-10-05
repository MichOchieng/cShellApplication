#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include "headers/main.h"

void shell();
void test();
void listShows();
void changeDirectory();
void concatenate();
void ecco();
void terminate();
void reader(char in);
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
        reader();
        // Parses input
        // Executes command
    }while(on); 
}

void reader(){
    int multiplier = 1;
    // Allocate memory
    char * inString = malloc(sizeof(char) * multiplier);
    // If memory allocated is too litte/much re-allocate
    
    fgets(input,25,stdin);
    printf("You entered: %s\n",input);
}

void test(){
    printf("\nTesting");
}

void welcome(){
    printf("Welcome to my shell.\n");
}