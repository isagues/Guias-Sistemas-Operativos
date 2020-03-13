// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// c.c
// Prints the stdin on stdout while counting the lines
#define  _GNU_SOURCE
#include <stdio.h>

int main(int argc, char const *argv[]){
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    int linecount = 0;
    while((linelen = getline(&line, &linecap, stdin)) > 0){
        linecount++;
        printf("Line %d: ", linecount);
        fwrite(line,linelen,1,stdout);
    }
    return 0;
}
