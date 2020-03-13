// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
    #include <stdio.h>
    #include <dirent.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <stdlib.h>
    #include <fcntl.h>

    enum forkOutputs{ERROR = -1, SON = 0};

int main(int argc, char const *argv[]){
    
    int fd;
    if((fd = open("targetFile.txt", O_CREAT | O_WRONLY,((mode_t) 000777))) == ERROR ){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    switch (fork()){
        case ERROR:
            perror("An error ocurred trying to fork\n");
            exit(EXIT_FAILURE);
        case SON:

            if(dup2(fd,STDOUT_FILENO) == ERROR ){
                perror("An error ocurred trying to chage the fd\n");
                exit(EXIT_FAILURE);
            }

            if(close(fd) == ERROR){
                 perror("Error closing file");
                exit(EXIT_FAILURE);
            }

            execl("./p.out","./p.out",(char *)NULL);
            perror("execve failed. \n");
            exit(EXIT_FAILURE); 
        default:
        break;
    }
    
     if(close(fd) == ERROR){
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    if(wait(NULL) == ERROR ){
        perror("Error waiting. \n");
        exit(EXIT_FAILURE); 
    }

    return 0;
}