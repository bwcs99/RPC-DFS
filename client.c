#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/random.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "communication.h"
#include "serialization.h"
#include "interface.h"

int main(void){

    
    printf("Wysyłam żądanie do serwera ! \n");

    int file_desc1 = ropen("tests/file_1.txt", "w");
    int file_desc2 = ropen("tests/file_2.txt", "r");
    int file_desc3 = ropen("tests/file_3.txt", "r");
    int file_desc4 = ropen("tests/file_4.txt", "r");
    int file_desc5 = ropen("tests/file_5.txt", "r");

    char data[200] = "abcdefghijklmnoqprst";
    char contents[20];

    ssize_t result = rwrite(data, 20, file_desc1);

    printf("Odpowiedź z serwera: %ld \n", result);

    result = rread(contents, 10, file_desc2);

    printf("Wiadomość: %s \n", contents);

    off_t res = rlseek(4, SEEK_CUR, file_desc3);

    printf("Odpowiedź z serwera: %jd \n", res);

    int int_result = unlink("tests/file_6.txt");

    printf("Rezultat: %d \n", int_result);

    int_result = rename("tests/file_5.txt", "tests/file_-1.txt");

    printf("Ostatni rezultat: %d \n", int_result);

    int_result = rchmod("tests/file_7.txt", S_IRWXG | S_IRWXO);

    printf("Rezultat z serwera: %d \n", int_result);

    return 0;
}
