#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<unistd.h>
#include "serialization.h"
#include "request_service.h"

int check_in_valid_auth(long int auth_tok, long int* valid_tokens, size_t count){

    for(int i = 0 ; i < count ; i++){

        if(valid_tokens[i] == auth_tok){
            return 1;
        }
    }

    return -1;
}

int main(void){

    int socket_desc;
    int file_desc;

    int auth_result;

    struct sockaddr_in server_address, client_address;

    InitialData* initial_req;
    FILE* file_ptr;
    OpenRequest* open_req_ptr;
    WriteRequest* write_request_ptr;
    ReadRequest* read_req_ptr;
    LseekRequest* lseek_req_ptr;
    ChmodRequest* chmod_req_ptr;
    UnlinkRequest* unlink_req_ptr;
    RenameRequest* rename_req_ptr;

    long int valid_auth_tokens[5] = {12345678, 87654321, 11112222, 34434466, 87878787};

    unsigned char initial_req_buffer[sizeof(InitialData)];
    unsigned char open_req_buffer[sizeof(OpenRequest)];
    unsigned char read_req_buffer[sizeof(ReadRequest)];
    unsigned char write_req_buffer[sizeof(WriteRequest)];
    unsigned char lseek_req_buffer[sizeof(LseekRequest)];
    unsigned char chmod_req_buffer[sizeof(ChmodRequest)];
    unsigned char data[200];

    size_t client_struct_length = sizeof(client_address);

    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(socket_desc <= -1 ){

        perror("Błąd tworzenia gniazda ! \n");
        return -1;

    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(2001);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(socket_desc, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){

        perror("Nie można zbindować się do portu ! \n");
        return -1;

    }

    while(1){

        if(recvfrom(socket_desc, initial_req_buffer, sizeof(InitialData), 
        0, (struct sockaddr*)&client_address, (socklen_t*)&client_struct_length) < 0){

            perror("Nie można odebrać rozmiaru struktur od klientów ! \n");
            close(socket_desc);

            return -1;

        }


        initial_req = (InitialData*)initial_req_buffer;

        auth_result = check_in_valid_auth(initial_req->auth_token, valid_auth_tokens, 5);

        InitialResponse* init_resp_ptr = createInitialResponse(initial_req->seq_num, auth_result);

        if(sendto(socket_desc, init_resp_ptr, sizeof(InitialResponse), 0, 
        (struct sockaddr*)&client_address, (socklen_t)client_struct_length) < 0){

            perror("Nie można wysłać odpowiedzi do klienta ! \n");
            return -1;
        }

        free(init_resp_ptr);

        if(strcmp(initial_req->request_name, "open") == 0){

            memset(open_req_buffer, '\0', sizeof(OpenRequest));

            if(recvfrom(socket_desc, open_req_buffer, sizeof(OpenRequest), 
            0, (struct sockaddr*)&client_address, (socklen_t*)&client_struct_length) < 0){

                perror("Nie można odebrać żądania od klienta ! \n");
                return -1;

            }

            open_req_ptr = (OpenRequest*)open_req_buffer;

            file_ptr = fopen(open_req_ptr->path_name, open_req_ptr->mode);

            file_desc = fileno(file_ptr);

            OpenResponse* open_response_ptr = createOpenResponse(open_req_ptr->seq_num, file_desc);

            if(sendto(socket_desc, open_response_ptr, sizeof(OpenResponse), 0, 
            (struct sockaddr*)&client_address, (socklen_t)client_struct_length) < 0){
                perror("Nie można wysłać odpowiedzi do klienta ! \n");
                return -1;
            }

            free(open_response_ptr);


        } else if(strcmp(initial_req->request_name, "write") == 0){

            memset(write_req_buffer, '\0', sizeof(WriteRequest));

            if(recvfrom(socket_desc, write_req_buffer, sizeof(WriteRequest), 
            0, (struct sockaddr*)&client_address, (socklen_t*)&client_struct_length) < 0){

                perror("Nie można odebrać żądania od klienta ! \n");
                return -1;

            }

            write_request_ptr = (WriteRequest*)write_req_buffer;

            ssize_t result = write(write_request_ptr->file_desc, write_request_ptr->data, write_request_ptr->count);

            WriteResponse* write_response_ptr = createWriteResponse(write_request_ptr->seq_num, result);

            if(sendto(socket_desc, write_response_ptr, sizeof(WriteResponse), 0, 
            (struct sockaddr*)&client_address, (socklen_t)client_struct_length) < 0){
                perror("Nie można wysłać odpowiedzi do klienta ! \n");
                return -1;
            }

            free(write_response_ptr);

        } else if(strcmp(initial_req->request_name, "read") == 0){

            memset(read_req_buffer, '\0', sizeof(ReadRequest));

            if(recvfrom(socket_desc, read_req_buffer, sizeof(ReadRequest), 
            0, (struct sockaddr*)&client_address, (socklen_t*)&client_struct_length) < 0){

                perror("Nie można odebrać żądania od klienta ! \n");
                return -1;

            }

            read_req_ptr = (ReadRequest*)read_req_buffer;

            memset(data, '\0', sizeof(data));

            ssize_t result = read(read_req_ptr->file_desc, data, read_req_ptr->count);

            ReadResponse* read_resp_ptr = createReadResponse(read_req_ptr->seq_num, result, data);

            if(sendto(socket_desc, read_resp_ptr, sizeof(ReadResponse), 0, 
            (struct sockaddr*)&client_address, (socklen_t)client_struct_length) < 0){
                perror("Nie można wysłać odpowiedzi do klienta ! \n");
                return -1;
            }

            free(read_resp_ptr);

        } else if(strcmp(initial_req->request_name, "lseek") == 0){

            memset(lseek_req_buffer, '\0', sizeof(LseekRequest));

            if(recvfrom(socket_desc, lseek_req_buffer, sizeof(LseekRequest), 
            0, (struct sockaddr*)&client_address, (socklen_t*)&client_struct_length) < 0){

                perror("Nie można odebrać żądania od klienta ! \n");
                return -1;

            }

            lseek_req_ptr = (LseekRequest*)lseek_req_buffer;

            off_t result = lseek(lseek_req_ptr->file_desc, lseek_req_ptr->offset, lseek_req_ptr->whence);

            LseekResponse* lseek_response_ptr = createLseekResponse(lseek_req_ptr->seq_num, result);

            if(sendto(socket_desc, lseek_response_ptr, sizeof(LseekResponse), 0, 
            (struct sockaddr*)&client_address, (socklen_t)client_struct_length) < 0){
                perror("Nie można wysłać odpowiedzi do klienta ! \n");
                return -1;
            }

            free(lseek_response_ptr);

        } else if(strcmp(initial_req->request_name, "chmod") == 0){

            memset(chmod_req_buffer, '\0', sizeof(ChmodRequest));

            if(recvfrom(socket_desc, chmod_req_buffer, sizeof(ChmodRequest), 
            0, (struct sockaddr*)&client_address, (socklen_t*)&client_struct_length) < 0){

                perror("Nie można odebrać żądania od klienta ! \n");
                return -1;

            }
            
            chmod_req_ptr = (ChmodRequest*) chmod_req_buffer;

            int result = chmod(chmod_req_ptr->pathname, chmod_req_ptr->mode);

            ChmodResponse* chmod_resp_ptr = createChmodResponse(chmod_req_ptr->seq_num, result);

            if(sendto(socket_desc, chmod_resp_ptr, sizeof(ChmodResponse), 0, 
            (struct sockaddr*)&client_address, (socklen_t)client_struct_length) < 0){
                perror("Nie można wysłać odpowiedzi do klienta ! \n");
                return -1;
            }

            free(chmod_resp_ptr);


        } else if(strcmp(initial_req->request_name, "unlink") == 0){

            unsigned char unlink_req_buffer[sizeof(UnlinkRequest)];

            memset(unlink_req_buffer, '\0', sizeof(UnlinkRequest));

            if(recvfrom(socket_desc, unlink_req_buffer, sizeof(UnlinkRequest), 
            0, (struct sockaddr*)&client_address, (socklen_t*)&client_struct_length) < 0){

                perror("Nie można odebrać żądania od klienta ! \n");
                return -1;

            }

            unlink_req_ptr = (UnlinkRequest*) unlink_req_buffer;

            int result = unlink(unlink_req_ptr->pathname);

            UnlinkResponse* unlink_resp_ptr = createUnlinkResponse(unlink_req_ptr->seq_num, result);

            if(sendto(socket_desc, unlink_resp_ptr, sizeof(UnlinkResponse), 0, 
            (struct sockaddr*)&client_address, (socklen_t)client_struct_length) < 0){
                perror("Nie można wysłać odpowiedzi do klienta ! \n");
                return -1;
            }

            free(unlink_resp_ptr);


        } else if(strcmp(initial_req->request_name, "rename") == 0){

            unsigned char rename_req_buffer[sizeof(RenameRequest)];

            memset(rename_req_buffer, '\0', sizeof(RenameRequest));

            if(recvfrom(socket_desc, rename_req_buffer, sizeof(RenameRequest), 
            0, (struct sockaddr*)&client_address, (socklen_t*)&client_struct_length) < 0){

                perror("Nie można odebrać żądania od klienta ! \n");
                return -1;

            }

            rename_req_ptr = (RenameRequest*)rename_req_buffer;

            int result = rename(rename_req_ptr->old_path, rename_req_ptr->new_path);

            RenameResponse* rename_resp_ptr = createRenameResponse(rename_req_ptr->seq_num, result);

            if(sendto(socket_desc, rename_resp_ptr, sizeof(RenameResponse), 0, 
            (struct sockaddr*)&client_address, (socklen_t)client_struct_length) < 0){
                perror("Nie można wysłać odpowiedzi do klienta ! \n");
                return -1;
            }
            
            free(rename_resp_ptr);

        }
    }

    close(socket_desc);

    return 0;
}