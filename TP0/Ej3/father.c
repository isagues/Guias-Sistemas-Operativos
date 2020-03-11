// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdlib.h>


#define CHILD_COUNT 10
#define MAX_PATHNAME_LEN 1000
enum forkOutputs{ERROR = -1, SON = 0};

int main(int argc, char const *argv[]){
    
    pid_t pid;
    
    char pathname[MAX_PATHNAME_LEN];
    
    char * newArgv[2];
    newArgv[0] = "./son.out";
    newArgv[1] = NULL;

    if( getcwd(pathname, MAX_PATHNAME_LEN) == NULL ){
        perror("An error ocurred trying to get the current working directory. \n");
        exit(EXIT_FAILURE);
    }

    if( strlen(pathname) + strlen("/") + strlen(newArgv[0]) + 1 > MAX_PATHNAME_LEN ){
        perror("Pathname too large to process. \n");
        exit(EXIT_FAILURE);
    } else {
        strcat(pathname, "/");
        strcat(pathname, newArgv[0]);
    }
    
    for (int i = 0; i < CHILD_COUNT; i++){
        pid = fork();
        switch (pid){
            case ERROR:
                perror("An error ocurred trying to fork\n");
                exit(EXIT_FAILURE);
                break;
            case SON:
                execv(pathname,newArgv);
                perror("execve failed. \n");
                exit(EXIT_FAILURE); 
                break;
        }
    }

    for (int i = 0; i < CHILD_COUNT; i++){
        if((pid = wait(NULL)) == -1){
            perror("An error ocurred waiting for a son\n");
            exit(EXIT_FAILURE);
        }
        printf("My son with PID: %d finished. \n", pid);
    }
    return 0;
}