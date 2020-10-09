#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void echo(char ** input);

int main(int argc,char ** argv){   
    echo(argv);
    return 0;
}

void echo(char ** input){
    int i = 1;    
    // Will make a new line if only echo is entered
    if(input[1] == NULL ){
        printf("\n");
    }
    else{
        while (input[i] != NULL){        
            printf("%s",input[i]);
            printf(" ");
            i++;
        }
        printf("\n");
    }    
}
