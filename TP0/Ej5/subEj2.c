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

    #define PIPE_IN 1
    #define PIPE_OUT 0
    #define NUMER_OF_SONS 1

    #define MAX_PATHNAME_LEN 1000

    enum forkOutputs{ERROR = -1, SON = 0};
    void getCurrentPath(char * pathname);
    void concatPath(char * pathname, char * extra);

int main(int argc, char const *argv[]){
    
    switch (fork()){
        case ERROR:
            perror("An error ocurred trying to fork\n");
            exit(EXIT_FAILURE);
        case SON:

            execl("./p.out","./p.out",(char *)NULL);
            perror("execve failed. \n");
            exit(EXIT_FAILURE); 
        default:
        break;
    }

    for (size_t i = 0; i < NUMER_OF_SONS; i++){
        if(wait(NULL) == ERROR ){
            perror("Error waiting. \n");
            exit(EXIT_FAILURE); 
        }
    }
    return 0;
}