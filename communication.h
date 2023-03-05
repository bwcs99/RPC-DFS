#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include "serialization.h"

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define PORT 2001
#define INET_ADDR "127.0.0.1"

static int _initialize();

int send_to_server(void* request, size_t request_size);
int receive_from_server(void* answer_buffer, size_t size_to_read);

#endif