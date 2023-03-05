#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "serialization.h"

OpenRequest* createOpenRequest(long int auth_token, long int seq_num, const char* path_name, char* mode){

    OpenRequest* open_req_ptr = malloc(sizeof(OpenRequest));

    if(open_req_ptr == NULL){

        perror("Nie można zaalokować pamięci ! \n");
        return NULL;

    }
    memset(open_req_ptr->path_name, '\0', sizeof(open_req_ptr->path_name));
    memset(open_req_ptr->mode, '\0', sizeof(open_req_ptr->mode));

    open_req_ptr->seq_num = seq_num;
    open_req_ptr->auth_token = auth_token;

    strcpy(open_req_ptr->path_name, path_name);
    strcpy(open_req_ptr->mode, mode);

    return open_req_ptr;
}

OpenResponse* createOpenResponse(long int seq_num, int file_desc){

    OpenResponse* open_resp_ptr = malloc(sizeof(OpenResponse));

    if(open_resp_ptr == NULL){

        perror("Nie można zaalokować pamięci na odpowiedź ! \n");
        return NULL;

    }

    open_resp_ptr->seq_num = seq_num;

    open_resp_ptr->file_desc = file_desc;

    return open_resp_ptr;  
}

InitialData* createInitialData(long int auth_token, long int seq_num, char* request_name){

    InitialData* init_data_ptr = malloc(sizeof(InitialData));

    if(init_data_ptr == NULL){

        perror("Nie można zaalokować pamięci ! \n");
        return NULL;

    }

    init_data_ptr->auth_token = auth_token;
    init_data_ptr->seq_num = seq_num;
    
    memset(init_data_ptr->request_name, '\0', sizeof(init_data_ptr->request_name));

    strcpy(init_data_ptr->request_name, request_name);

    return init_data_ptr;
   
}

InitialResponse* createInitialResponse(long int seq_num, int err_flag){

    InitialResponse* init_response_ptr = malloc(sizeof(InitialResponse));

    if(init_response_ptr == NULL){

        perror("Nie można zaalokować pamięci ! \n");
        return NULL;

    }

    init_response_ptr->seq_num = seq_num;
    init_response_ptr->err_flag = err_flag;

    return init_response_ptr;
}

ReadRequest* createReadRequest(long int auth_token, long int seq_num, size_t count, int file_desc){

    ReadRequest* read_req_ptr = malloc(sizeof(ReadRequest));

    if(read_req_ptr == NULL){

        perror("Nie można zaalokować pamięci na żądanie ! \n");
        return NULL;
    }

    read_req_ptr->auth_token = auth_token;
    read_req_ptr->seq_num = seq_num;
    read_req_ptr->count = count;
    read_req_ptr->file_desc = file_desc;

    return read_req_ptr;
}

ReadResponse* createReadResponse(long int seq_num, ssize_t count, unsigned char* data){

    ReadResponse* read_response_ptr = malloc(sizeof(ReadResponse));

    size_t _count = 0;

    if(count >= 0){ 

        _count = (size_t)count;

    }

    if(read_response_ptr == NULL){

        perror("Nie można zaalokować pamięci na żądanie ! \n");
        return NULL;

    }

    read_response_ptr->seq_num = seq_num;
    read_response_ptr->count = count;

    memset(read_response_ptr->data, '\0', sizeof(read_response_ptr->data));

    memcpy(read_response_ptr->data, data, _count);

    return read_response_ptr;
}

WriteRequest* createWriteRequest(long int auth_token, long int seq_num, size_t count, void* data, int file_desc){

    WriteRequest* write_request_ptr = malloc(sizeof(WriteRequest));

    if(write_request_ptr == NULL){

        perror("Nie można zaalokować pamięci na żądanie ! \n");
        return NULL;

    }

    write_request_ptr->auth_token = auth_token;
    write_request_ptr->seq_num = seq_num;
    write_request_ptr->count = count;
    write_request_ptr->file_desc = file_desc;

    memset(write_request_ptr->data, '\0', sizeof(write_request_ptr->data));

    memcpy(write_request_ptr->data, data, count);

    return write_request_ptr;

}

WriteResponse* createWriteResponse(long int seq_num, ssize_t count){

    WriteResponse* write_response_ptr = malloc(sizeof(WriteResponse));

    if(write_response_ptr == NULL){
        perror("Nie można zaalokować pamięci ! \n");
        return NULL;
    }

    write_response_ptr->seq_num = seq_num;
    write_response_ptr->count = count;

    return write_response_ptr;
}

ChmodRequest* createChmodRequest(long int auth_token, long int seq_num, const char* pathname, mode_t mode){

    ChmodRequest* chmod_req_ptr = malloc(sizeof(ChmodRequest));

    if(chmod_req_ptr == NULL){

        return NULL;
    }

    chmod_req_ptr->auth_token = auth_token;
    chmod_req_ptr->seq_num = seq_num;
    chmod_req_ptr->mode = mode;

    memset(chmod_req_ptr->pathname, '\0', sizeof(chmod_req_ptr->pathname));
    memcpy(chmod_req_ptr->pathname, pathname, strlen(pathname));

    return chmod_req_ptr;
}

ChmodResponse* createChmodResponse(long int seq_num, int result){

    ChmodResponse* chmod_response_ptr = malloc(sizeof(ChmodResponse));

    if(chmod_response_ptr == NULL){

        return NULL;
    }

    chmod_response_ptr->seq_num = seq_num;
    chmod_response_ptr->result = result;

    return chmod_response_ptr;
}

UnlinkRequest* createUnlinkRequest(long int auth_token, long int seq_num, const char* pathname){

    UnlinkRequest* unlink_req_ptr = malloc(sizeof(UnlinkRequest));

    if(unlink_req_ptr == NULL){

        return NULL;

    }

    unlink_req_ptr->auth_token = auth_token;
    unlink_req_ptr->seq_num = seq_num;

    memset(unlink_req_ptr->pathname, '\0', sizeof(unlink_req_ptr->pathname));
    memcpy(unlink_req_ptr->pathname, pathname, strlen(pathname));

    return unlink_req_ptr;
}

UnlinkResponse* createUnlinkResponse(long int seq_num, int result){

    UnlinkResponse* unlink_response_ptr = malloc(sizeof(UnlinkResponse));

    if(unlink_response_ptr == NULL){

        return NULL;

    }

    unlink_response_ptr->seq_num = seq_num;
    unlink_response_ptr->result = result;

    return unlink_response_ptr;
}

RenameRequest* createRenameRequest(long int auth_token, long int seq_num, const char* old_path, const char* new_path){

    RenameRequest* rename_req_ptr = malloc(sizeof(RenameRequest));

    if(rename_req_ptr == NULL){

        return NULL;

    }

    rename_req_ptr->auth_token = auth_token;
    rename_req_ptr->seq_num = seq_num;

    memset(rename_req_ptr->old_path, '\0', sizeof(rename_req_ptr->old_path));
    memset(rename_req_ptr->new_path, '\0', sizeof(rename_req_ptr->new_path));

    memcpy(rename_req_ptr->old_path, old_path, strlen(old_path));
    memcpy(rename_req_ptr->new_path, new_path, strlen(new_path));

    return rename_req_ptr;
}

RenameResponse* createRenameResponse(long int seq_num, int result){

    RenameResponse* rename_response_ptr = malloc(sizeof(RenameResponse));

    if(rename_response_ptr == NULL){

        return NULL;

    }

    rename_response_ptr->seq_num = seq_num;
    rename_response_ptr->result = result;

    return rename_response_ptr;
}

LseekRequest* createLseekRequest(long int auth_token, long int seq_num, off_t offset, int whence, int file_desc){

    LseekRequest* lseek_req_ptr = malloc(sizeof(LseekRequest));

    if(lseek_req_ptr == NULL){

        return NULL;
    }

    lseek_req_ptr->auth_token = auth_token;
    lseek_req_ptr->seq_num = seq_num;
    lseek_req_ptr->offset = offset;
    lseek_req_ptr->whence = whence;
    lseek_req_ptr->file_desc = file_desc;

    return lseek_req_ptr;
}

LseekResponse* createLseekResponse(long int seq_num, off_t result){

    LseekResponse* lseek_resp_ptr = malloc(sizeof(LseekResponse));

    if(lseek_resp_ptr == NULL){

        return NULL;

    }

    lseek_resp_ptr->seq_num = seq_num;
    lseek_resp_ptr->result = result;

    return lseek_resp_ptr;
}