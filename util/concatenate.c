#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

FILE *file;
void cat(char ** input);

int main(int argc,char ** argv){  
    cat(argv);
    return 0;
}

void cat(char ** input){
    // Goes through and prints all files given
    int i = 1;
    while (input[i] != NULL){
        file = fopen(input[i],"r");
        // Checks to see if the file exists
        if (file == NULL){
            printf("%s",input[i]);
            printf(": No such file in directory \n");            
        }else{
            // If the file exists loops over the entire file and prints
            char c = fgetc(file);
            while(c != EOF){
                printf("%c",c);
                c = fgetc(file);
            }
            printf("\n");
        }        
     i++;   
    }
    fclose(file);
}