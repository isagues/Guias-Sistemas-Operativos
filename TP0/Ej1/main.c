// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_PATHNAME_LEN 1000
#define SPACER_CHAR '\t'

#define S_IFMT  ((mode_t) 0170000)	
#define S_IFREG ((mode_t) 0100000)
#define S_IFDIR ((mode_t) 0040000)

#define INITIAL_DEPTH 0

enum errors{ERROR = -1, NO_ERROR = 0};
enum identifier{ID_FILE = 'f', ID_DIR = 'd'};
enum argcValues{NO_PATH_PROVIDED = 1, PATH_PROVIDED = 2};
enum argvValues{FILE_NAME = 0, PATH = 1};


void getCurrentPath(char * pathname);
void concatPath(char * pathname, char * extra);
void copyPath(const char * source, char * target, size_t size);
void recursiveTree(char *pathmane, char spacerChar, int depth);
void printLine(char identifier, int depth, char spacerChar,char * entryName);
void auxRecursiveTree(DIR *dirStream, char spacerChar, int depth, char *pathmane );


int main(int argc, char const *argv[]){

    char pathname[MAX_PATHNAME_LEN];

    switch (argc){

        case PATH_PROVIDED:
            copyPath(argv[PATH],pathname,MAX_PATHNAME_LEN);
            break;

        case NO_PATH_PROVIDED:
            getCurrentPath(pathname);
            break;

        default:
            perror("Invalid amount of arguments\n");
            exit(EXIT_FAILURE);
            break;
    }

    printf("%s\n",pathname);

    recursiveTree(pathname, SPACER_CHAR, INITIAL_DEPTH);

    return EXIT_SUCCESS;
}

void recursiveTree(char *pathname, char spacerChar, int depth){

    DIR * dirStream = opendir(pathname);

    if( dirStream == NULL){
        printf("An error ocurred trying to open the directory. \n");
        exit(EXIT_FAILURE);
    }

    auxRecursiveTree(dirStream,spacerChar,depth + 1, pathname);

    if(closedir(dirStream) == ERROR){
        perror("An error ocurred closing the DIR stream\n");
        exit(EXIT_FAILURE);
    }
    
}

void auxRecursiveTree(DIR *dirStream, char spacerChar, int depth, char *pathname ){
    
    struct dirent *entry = readdir(dirStream);

    if( entry == NULL ){
        if( errno ==  NO_ERROR){
            return;
        } else {
            printf("An error ocurred reading a directory \n");
            exit(EXIT_FAILURE);
        }
    } else {
        struct stat entryStat;
        int pathLen = strlen(pathname);

        concatPath(pathname,entry->d_name);
        
        //Obtencion de la informacion de la entrada actual
        if( stat(pathname, &entryStat) == ERROR ){
            printf("An error ocurred accesing an entry info \n");
            exit(EXIT_FAILURE);
        }

        switch ( entryStat.st_mode & S_IFMT ){

            case S_IFREG:
                printLine(ID_FILE,depth,spacerChar,entry->d_name);
                break;

            case S_IFDIR:
                if((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)){
                    printLine(ID_DIR,depth,spacerChar,entry->d_name);
                    recursiveTree(pathname, spacerChar, depth);
                }
            break;

            default:
                break;
        }

        pathname[pathLen] = '\0';

        auxRecursiveTree(dirStream, spacerChar, depth,pathname);
    }
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

void copyPath(const char * source, char * target, size_t size){
     if( strlen(source) + 1 >= size){
        printf("Pathname too large to copy. \n");
        exit(EXIT_FAILURE);
    } else {
        strncpy(target,source,size);
        //Tengo una duda aca, inicialmente hacia un strcpy pero PVS me decia que podia resultar en overflow. Si ya revise la longitud, puede dar overflow?
        target[size - 1] = '\0';
    }
}

void printLine(char identifier, int depth, char spacerChar,char * entryName){
    putchar(identifier);
    for (size_t i = 0; i < depth; i++){
        putchar(spacerChar);
    }
    printf("%s \n",entryName);
}