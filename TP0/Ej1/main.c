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

void auxRecursiveTree(DIR *dirStream, char spacerChar, int depth, char *pathmane );
void recursiveTree(char *pathmane, char spacerChar, int depth);

int main(int argc, char const *argv[]){
    //Si me dan un path, desde ese path. Sino desde PWD
    char pathname[MAX_PATHNAME_LEN];

    if(argc <= 1 ){
        //Errores manejados todos juntos. Habria que comunicar especificamente cual sucedio.
        if( getcwd(pathname, MAX_PATHNAME_LEN) == NULL ){
            printf("An error ocurred trying to get the current working directory. \n");
            exit(EXIT_FAILURE);
        }
    } else {
        if( strlen(argv[1]) + 1 >= MAX_PATHNAME_LEN){
            printf("Pathname too large to process. \n");
            exit(EXIT_FAILURE);
        } else {
            //Tengo una duda aca, inicialmente hacia un strcpy pero PVS me decia que podia resultar en overflow. Si ya revise la longitud, puede dar overflow?
            strncpy(pathname,argv[1],MAX_PATHNAME_LEN);
            pathname[MAX_PATHNAME_LEN - 1] = '\0';
        }
    }
    
    printf("%s\n",pathname);
    recursiveTree(pathname, SPACER_CHAR, INITIAL_DEPTH);
    return 0;
}

void recursiveTree(char *pathname, char spacerChar, int depth){

    DIR * dirStream = opendir(pathname);
    //Errores manejados todos juntos.
    if( dirStream == NULL){
        printf("An error ocurred trying to open the directory. \n");
        exit(EXIT_FAILURE);
    }
   auxRecursiveTree(dirStream,spacerChar,depth+1, pathname);

   if(closedir(dirStream) == -1){
       perror("An error ocurred closing the DIR stream\n");
       exit(EXIT_FAILURE);
   }
    
}

void auxRecursiveTree(DIR *dirStream, char spacerChar, int depth, char *pathname ){
    
    struct dirent *entry = readdir(dirStream);

    if( entry == NULL ){
        if( errno == 0 ){
            return;
        } else {
            printf("An error ocurred reading a directory \n");
            exit(EXIT_FAILURE);
        }
    } else {
        struct stat entryStat;
        int pathLen = strlen(pathname);

        if(pathLen + strlen(entry->d_name) + 1 >= MAX_PATHNAME_LEN ){
            printf("The path name is too long \n");
            exit(EXIT_FAILURE);
        }else{
            strcat(pathname, "/");
            strcat(pathname, entry->d_name);
        }
        
        //Obtencion de la informacion de la entrada actual
        if( stat(pathname, &entryStat) == -1 ){
            printf("An error ocurred accesing an entry info \n");
            exit(EXIT_FAILURE);
        }

        //Procesado de la entrada
        if( (entryStat.st_mode & S_IFMT) == S_IFREG ){
            putchar('f');
            for (size_t i = 0; i < depth; i++){
                putchar(spacerChar);
            }
            printf("%s \n",entry->d_name);
        } else if( ( (entryStat.st_mode & S_IFMT) == S_IFDIR ) && (strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)){
            putchar('d');
            for (size_t i = 0; i < depth; i++){
                putchar(spacerChar);
            }
            printf("%s \n",entry->d_name);
            
            recursiveTree(pathname, spacerChar, depth);
            
        }
        pathname[pathLen] = '\0';
        auxRecursiveTree(dirStream, spacerChar, depth,pathname);
    }
}
