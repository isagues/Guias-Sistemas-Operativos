#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char const *argv[]){
    sleep(3);
    printf("I'm a %s and my PID is: %d. Goodbye!\n",argv[0],getpid());
    exit(0);
    return 0;
}
