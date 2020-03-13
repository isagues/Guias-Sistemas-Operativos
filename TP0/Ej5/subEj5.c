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

    #define PROGRAM_1 1
    #define CONDITION 2
    #define PROGRAM_2 3

    #define MATCH 0

    #define NUMER_OF_ASRGS 4

    enum forkOutputs{ERROR = -1, SON = 0};

int main(int argc, char const *argv[]){
    
    int exitStatus;
    
    if(argc != NUMER_OF_ASRGS){
        perror("Invalid amount of arguments");
        exit(EXIT_FAILURE);
    }

    switch (fork()){
        case ERROR:
            perror("An error ocurred trying to fork\n");
            exit(EXIT_FAILURE);
        case SON:
            execl(argv[PROGRAM_1],argv[PROGRAM_1],(char *)NULL);
            perror("execve failed. \n");
            exit(EXIT_FAILURE); 
        default:

        if(wait( &exitStatus) == ERROR ){
            perror("Error waiting. \n");
            exit(EXIT_FAILURE); 
        }

        if(strcmp(argv[CONDITION],"&") == MATCH){
            if(exitStatus != 0)
                return exitStatus;
        } else if(strcmp(argv[CONDITION],"|") == MATCH ){
            if( exitStatus == 0)
                return 0;
        } else if(strcmp(argv[CONDITION],"#") != MATCH){
            perror("Invalid operation");
            exit(EXIT_FAILURE);
        }
        break;
    }

    switch (fork()){
        case ERROR:
            perror("An error ocurred trying to fork\n");
            exit(EXIT_FAILURE);
        case SON:
            execl(argv[PROGRAM_2],argv[PROGRAM_2],(char *)NULL);
            perror("execve failed. \n");
            exit(EXIT_FAILURE); 
        default:
        break;
    }

    if(wait(&exitStatus) == ERROR ){
        perror("Error waiting. \n");
        exit(EXIT_FAILURE); 
        
    }
    return exitStatus;
}