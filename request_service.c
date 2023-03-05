#include<stdio.h>
#include<unistd.h>
#include "request_service.h"

FILE* handle_open_request(const char *pathname, char *mode){

    if(pathname == NULL || mode == NULL){
        perror("Podano nie właściwe dane ! \n");
        return NULL;
    }

    File* stream = fopen(pathname, mode);

    return stream;
}

int handle_chmod_request(const char *pathname, mode_t mode){

    if(pathname == NULL){
        perror("Nie podano ścieżki do pliku ! \n");
        return -1;
    }

    
}