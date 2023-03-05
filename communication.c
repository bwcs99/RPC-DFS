#include "communication.h"
#include "serialization.h"
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<poll.h>

int socket_desc;
struct sockaddr_in server_address;
size_t server_struct_length;
int initialized = 0;

static int _initialize(){

    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    server_struct_length = sizeof(server_address);

    if(socket_desc < 0){

        perror("Błąd - nie można utworzyć socketa ! \n");
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(INET_ADDR);

    initialized = 1;

    return 1;
}

int send_to_server(void* request, size_t request_size){

    if(initialized == 0){

        _initialize();

    }

    int time_out = 2000;

    struct pollfd fds[1];

    fds[0].fd = socket_desc;
    fds[0].events = POLLOUT | POLLWRBAND;

    unsigned char request_buffer[request_size];

    memset(request_buffer, '\0', request_size);
    memcpy(request_buffer, request, request_size);

    int result = poll(fds, 1, time_out);

    if(result > 0){

        if(sendto(socket_desc, request_buffer, request_size, 
        0, 
        (struct sockaddr*)&server_address, (socklen_t)server_struct_length) < 0){

            perror("Nie można wysłać rozmiaru struktury do serwera ! \n");
            return -1;
        }

    } else if(result <= 0){

        result = poll(fds, 1, time_out);

        if(result > 0){

            if(sendto(socket_desc, request_buffer, request_size, 
            0, 
            (struct sockaddr*)&server_address, (socklen_t)server_struct_length) < 0){

                perror("Nie można wysłać rozmiaru struktury do serwera ! \n");
                return -1;
            }

        } else {

            return -1;
        }
    }

    return 1;

}

int receive_from_server(void* answer_buffer, size_t size_to_read){

    int time_out = 2000;

    struct pollfd fds[1];

    fds[0].fd = socket_desc;
    fds[0].events = POLLIN | POLLRDBAND;

    if(answer_buffer == NULL){
        perror("Podano pusty bufor na odpowiedź ! \n");
        return -1;
    }

    if(initialized == 0){

        _initialize();

    }

    int result = poll(fds, 1, time_out);

    if(result > 0){

        if(recvfrom(socket_desc, answer_buffer, size_to_read, 0, 
        (struct sockaddr*)&server_address, (socklen_t*)&server_struct_length) < 0){
            perror("Nie można odebrać odpowiedzi od serwera ! \n");
            return -1;
        }

    } else if(result <= 0){

        result = poll(fds, 1, time_out);

        if(result > 0){

            if(recvfrom(socket_desc, answer_buffer, size_to_read, 0, 
                (struct sockaddr*)&server_address, (socklen_t*)&server_struct_length) < 0){
                perror("Nie można odebrać odpowiedzi od serwera ! \n");
                return -1;
            }

        } else{

            return -1;
        }

    }

    return 1;
    

}