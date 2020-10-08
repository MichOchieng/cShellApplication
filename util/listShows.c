#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

void ls(char ** input);
DIR *dir;
struct dirent *name;

int main(int argc,char ** argv){  
    ls(argv);
    return 0;
}

void ls(char ** input){
    char * func2 = "-l";
    // For ls alone
    if (input[1] == NULL){ 
        dir = opendir("."); // Opens current directory       
        if (dir == NULL){
            printf("Error finding working directory.");
        }else{            
            // Reads the current directory
            while ((name = readdir(dir)) != NULL){
                // Should add a '/' after folders
                if ((name->d_type) == 4){                    
                    printf("%s",name->d_name);
                    printf("/ ");
                }
                else{
                    printf("%s ",name->d_name);
                }              
                
            } 
            printf("\n"); 
        }             
    }    
    // For ls -Dir- commands
    else if (input[1] != NULL){
        int i = 1;
        while (input[i] != NULL){
            dir = opendir(input[i]); // Opens current directory       
            if (dir == NULL){
                printf("Error finding working directory.");
                break;
            }else{            
                // Reads the current directory
                while ((name = readdir(dir)) != NULL){
                    // Should add a '/' after folders
                    if ((name->d_type) == 4){                    
                        printf("%s",name->d_name);
                        printf("/ ");
                    }
                    else{
                        printf("%s ",name->d_name);
                    }              
                    
                }
                printf("\n");   
            }
            i++;
        }
        
    }
    
    closedir(dir);
    
}