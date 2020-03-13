// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// p.c
// Prints numbers from 0 to MAX - 1 with a delay

#include <stdio.h>
#include <unistd.h>
#define _GNU_SOURCES

#define MAX 5
#define DELAY 1

int main(int argc, char const *argv[]){
   // setvbuf(stdout,NULL,_IONBF,0);
    for (int i = 0; i < MAX; i++){
        printf("%d\n",i);
        sleep(DELAY);
    }
    return 0;
}