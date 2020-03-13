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
    #define NUMER_OF_SONS 2

    #define MAX_PATHNAME_LEN 1000

    enum forkOutputs{ERROR = -1, SON = 0};
    void getCurrentPath(char * pathname);
    void concatPath(char * pathname, char * extra);

int main(int argc, char const *argv[]){
    
    int pipefd[2];

    if(pipe(pipefd) == ERROR){
        perror("An error ocurred creating the pipe\n");
        exit(EXIT_FAILURE);
    }

    switch (fork()){
        case ERROR:
            perror("An error ocurred trying to fork\n");
            exit(EXIT_FAILURE);
        case SON:
            
            if(dup2(pipefd[PIPE_OUT],STDIN_FILENO) == ERROR ){
                perror("An error ocurred trying to chage the fd\n");
                exit(EXIT_FAILURE);
            }
            close(pipefd[PIPE_OUT]);
            close(pipefd[PIPE_IN]);

            execl("./c.out","./c.out",(char *)NULL);
            perror("execve failed. \n");
            exit(EXIT_FAILURE); 
        default:
        break;
    }

    switch (fork()){
        case ERROR:
            perror("An error ocurred trying to fork\n");
            exit(EXIT_FAILURE);
        case SON:

            if(dup2(pipefd[PIPE_IN],STDOUT_FILENO) == ERROR ){
                perror("An error ocurred trying to chage the fd\n");
                exit(EXIT_FAILURE);
            }
            
            close(pipefd[PIPE_IN]);
            close(pipefd[PIPE_OUT]);
            
            execl("./p.out","./p.out",(char *)NULL);
            perror("execve failed. \n");
            exit(EXIT_FAILURE); 
        default:
        break;
    }

    close(pipefd[PIPE_IN]);
    close(pipefd[PIPE_OUT]);

    for (size_t i = 0; i < NUMER_OF_SONS; i++){
        if(wait(NULL) == ERROR ){
            perror("Error waiting. \n");
            exit(EXIT_FAILURE); 
        }
    }
    return 0;
}

void getCurrentPath(char * pathname){
    if( getcwd(pathname, MAX_PATHNAME_LEN) == NULL ){
        perror("An error ocurred trying to get the current working directory. \n");
        exit(EXIT_FAILURE);
    }
}

void concatPath(char * pathname, char * extra){
    if( strlen(pathname) + strlen("/") + strlen(extra) + 1 > MAX_PATHNAME_LEN ){
        perror("Pathname too large to process. \n");
        exit(EXIT_FAILURE);
    } else {
        strcat(pathname, "/");
        strcat(pathname, extra);
    }
}