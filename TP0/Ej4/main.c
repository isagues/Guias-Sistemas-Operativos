// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define CHILD_COUNT 10
enum forkOutputs{ERROR=-1, SON};

int main(int argc, char const *argv[]){

    for (int i = 0; i < CHILD_COUNT; i++){
        switch (fork()){
            case ERROR:
                perror("An error ocurred trying to fork\n");
                exit(EXIT_FAILURE);
            case SON:
                exit(EXIT_SUCCESS);
        }
    }
    sleep(10);
    return 0;
}
