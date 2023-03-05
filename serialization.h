#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

typedef struct InitialData{
    
    long int auth_token;
    long int seq_num;

    char request_name[100];

} InitialData;

typedef struct InitialResponse{

    long int seq_num;

    int err_flag;

} InitialResponse;

typedef struct OpenRequest{

    long int auth_token;
    long int seq_num;

    char path_name[60];
    char mode[5];
    
} OpenRequest;

typedef struct OpenResponse{

    long int seq_num;

    int file_desc;


} OpenResponse;

typedef struct ReadRequest{

    long int auth_token;
    long int seq_num;

    size_t count;
    int file_desc;


} ReadRequest;

typedef struct ReadResponse{

    long int seq_num;

    ssize_t count;
    unsigned char data[200];

} ReadResponse;

typedef struct WriteRequest {

    long int auth_token;
    long int seq_num;

    size_t count;

    char data[200];
    int file_desc;

} WriteRequest;

typedef struct WriteResponse{

    long int seq_num;

    ssize_t count;

} WriteResponse;

typedef struct LseekRequest{

    long int auth_token;
    long int seq_num;

    off_t offset;
    int whence;

    int file_desc;

} LseekRequest;

typedef struct LseekResponse{

    long int seq_num;

    off_t result;

} LseekResponse;

typedef struct ChmodRequest{
    
    long int auth_token;
    long int seq_num;

    char pathname[200];

    mode_t mode;

} ChmodRequest;

typedef struct ChmodResponse{

    long int seq_num;

    int result;

} ChmodResponse;

typedef struct UnlinkRequest{

    long int auth_token;
    long int seq_num;

    char pathname[200];

} UnlinkRequest;

typedef struct UnlinkResponse{

    long int seq_num;

    int result;

} UnlinkResponse;

typedef struct RenameRequest{

    long int auth_token;
    long int seq_num;

    char old_path[200];
    char new_path[200];

} RenameRequest;

typedef struct RenameResponse{

    long int seq_num;

    int result;

} RenameResponse;

InitialData* createInitialData(long int auth_token, long int seq_num, char* request_name);
InitialResponse* createInitialResponse(long int seq_num, int err_flag);
OpenRequest* createOpenRequest(long int auth_token, long int seq_num, const char* path_name, char* mode);
OpenResponse* createOpenResponse(long int seq_num, int file_desc);
ReadRequest* createReadRequest(long int auth_token, long int seq_num, size_t count, int file_desc);
ReadResponse* createReadResponse(long int seq_num, ssize_t count, unsigned char* data);
WriteRequest* createWriteRequest(long int auth_token, long int seq_num, size_t count, void* data, int file_desc);
WriteResponse* createWriteResponse(long int seq_num, ssize_t count);
LseekRequest* createLseekRequest(long int auth_token, long int seq_num, off_t offset, int whence, int file_desc);
LseekResponse* createLseekResponse(long int seq_num, off_t result);
ChmodRequest* createChmodRequest(long int auth_token, long int seq_num, const char* pathname, mode_t mode);
ChmodResponse* createChmodResponse(long int seq_num, int result);
UnlinkRequest* createUnlinkRequest(long int auth_token, long int seq_num, const char* pathname);
UnlinkResponse* createUnlinkResponse(long int seq_num, int result);
RenameRequest* createRenameRequest(long int auth_token, long int seq_num, const char* old_path, const char* new_path);
RenameResponse* createRenameResponse(long int seq_num, int result);
#endif