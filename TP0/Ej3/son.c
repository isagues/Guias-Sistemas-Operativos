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

int main(int argc, char const *argv[]){
    sleep(3);
    printf("I'm a %s and my PID is: %d. Goodbye!\n",argv[0],getpid());
    exit(0);
    return 0;
}
