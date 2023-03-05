#include <stdio.h>
#include <time.h>
#include <string.h>
#include <poll.h>
#include "serialization.h"
#include "communication.h"

static long int _generate_seq_num(){

    long int upper = 99999999;
    long int lower = 10000000;

    return (long int) ((rand() % (upper - lower + 1)) + lower);
}

int ropen(const char *pathname, char *mode){

    if(pathname == NULL || mode == NULL){

        perror("Nie podano nazwy ścieżki lub trybu ! \n");
        return -1;
    }

    int result;

    long int seq_num = _generate_seq_num();

    InitialData* initial_data_ptr = createInitialData(12345678, seq_num, "open");
    
    unsigned char initial_response_buffer[sizeof(InitialResponse)];
    unsigned char open_response_buffer[sizeof(OpenResponse)];

    result = send_to_server(initial_data_ptr, sizeof(InitialData));

    if(result == -1){

        return -1;

    }

    result = receive_from_server(initial_response_buffer, sizeof(InitialResponse));

    if(result == -1){

        return -1;

    }

    InitialResponse* initial_response_ptr = (InitialResponse*)initial_response_buffer;

    if(initial_response_ptr->seq_num != seq_num){

        perror("Serwer obsłużył nieznane żądanie ! \n");
        return -1;

    }

    if(initial_response_ptr->err_flag == -1){

        perror("Błąd autoryzacji ! \n");
        return -1;
    }

    seq_num = _generate_seq_num();

    OpenRequest* open_req_ptr = createOpenRequest(12345678, seq_num, pathname, mode);

    result = send_to_server(open_req_ptr, sizeof(OpenRequest));

    if(result == -1){

        return -1;

    }

    result = receive_from_server(open_response_buffer, sizeof(OpenResponse));

    if(result == -1){

        return -1;

    }

    OpenResponse* open_response_ptr = (OpenResponse*)open_response_buffer;
    
    return open_response_ptr->file_desc;

}

ssize_t rread(void *buf, size_t count, int file_desc){

    if(buf == NULL ){

        perror("Nie podano bufora lub wskaźnika na plik ! \n");
        return -1;
    }

    int result;

    long int seq_num = _generate_seq_num();

    InitialData* initial_data_ptr = createInitialData(12345678, seq_num, "read");

    unsigned char initial_response_buffer[sizeof(InitialResponse)];
    unsigned char read_response_buffer[sizeof(ReadResponse)];

    result = send_to_server(initial_data_ptr, sizeof(InitialData));

    if(result == -1){

        return (ssize_t)-1;
    }

    result = receive_from_server(initial_response_buffer, sizeof(InitialResponse));

    if(result == -1){

        return (ssize_t)-1;
    }

    InitialResponse* initial_response_ptr = (InitialResponse*)initial_response_buffer;

    if(initial_response_ptr->seq_num != seq_num){

        perror("Serwer obsłużył nieznane żądanie ! \n");
        return -1;

    }

    if(initial_response_ptr->err_flag == -1){

        perror("Błąd autoryzacji ! \n");
        return -1;
    }

    seq_num = _generate_seq_num();

    ReadRequest* read_req_ptr = createReadRequest(12345678, seq_num, count, file_desc);

    result = send_to_server(read_req_ptr, sizeof(ReadRequest));

    if(result == -1){

        return (ssize_t)-1;
    }

    result = receive_from_server(read_response_buffer, sizeof(ReadResponse));

    if(result == -1){

        return (ssize_t)-1;
    }

    ReadResponse* read_response_ptr = (ReadResponse*)read_response_buffer;

    memcpy(buf, read_response_ptr->data, count);

    return read_response_ptr->count;
}

ssize_t rwrite(void *buf, size_t count, int file_desc){

    if(buf == NULL){

        perror("Nie podano bufora lub wskaźnika na plik ! \n");
        return -1;
    }

    int result;

    long int seq_num = _generate_seq_num();

    InitialData* initial_data_ptr = createInitialData(12345678, seq_num, "write");

    unsigned char initial_response_buffer[sizeof(InitialResponse)];
    unsigned char write_response_buffer[sizeof(WriteResponse)];

    result = send_to_server(initial_data_ptr, sizeof(InitialData));

    if(result == -1){

        return (ssize_t)-1;
    }

    result = receive_from_server(initial_response_buffer, sizeof(InitialResponse));

    if(result == -1){

        return (ssize_t)-1;
    }

    InitialResponse* initial_response_ptr = (InitialResponse*)initial_response_buffer;

    if(initial_response_ptr->seq_num != seq_num){

        perror("Serwer obsłużył nieznane żądanie ! \n");
        return -1;

    }

    if(initial_response_ptr->err_flag == -1){

        perror("Błąd autoryzacji ! \n");
        return -1;
    }

    WriteRequest* write_req_ptr = createWriteRequest(12345678, seq_num, count, buf, file_desc);

    result = send_to_server(write_req_ptr, sizeof(WriteRequest));

    if(result == -1){

        return (ssize_t)-1;
    }

    result = receive_from_server(write_response_buffer, sizeof(WriteResponse));

    if(result == -1){

        return (ssize_t)-1;
    }

    WriteResponse* write_response_ptr = (WriteResponse*)write_response_buffer;

    return write_response_ptr->count;

}

off_t rlseek(off_t offset, int whence, int file_desc){

    long int seq_num = _generate_seq_num();

    int result;

    InitialData* initial_data_ptr = createInitialData(12345678, seq_num, "lseek");

    unsigned char initial_response_buffer[sizeof(InitialResponse)];
    unsigned char lseek_response_buffer[sizeof(LseekResponse)];

    result = send_to_server(initial_data_ptr, sizeof(InitialData));

    if(result == -1){

        return (off_t)-1;
    }

    result = receive_from_server(initial_response_buffer, sizeof(InitialResponse));

    if(result == -1){

        return (off_t)-1;
    }

    InitialResponse* initial_response_ptr = (InitialResponse*)initial_response_buffer;

    if(initial_response_ptr->seq_num != seq_num){

        perror("Serwer obsłużył nieznane żądanie ! \n");
        return (off_t)-1;

    }

    if(initial_response_ptr->err_flag == -1){

        perror("Błąd autoryzacji ! \n");
        return (off_t)-1;
    }

    LseekRequest* read_req_ptr = createLseekRequest(12345678, seq_num, offset, whence, file_desc);

    result = send_to_server(read_req_ptr, sizeof(LseekRequest));

    if(result == -1){

        return (off_t)-1;
    }

    result = receive_from_server(lseek_response_buffer, sizeof(LseekResponse));

    if(result == -1){

        return (off_t)-1;
    }

    LseekResponse* lseek_response_ptr = (LseekResponse*)lseek_response_buffer;

    return lseek_response_ptr->result;
} 

int rchmod(const char *pathname, mode_t mode){

    if(pathname == NULL){

        return -1;
    }

    int result;

    long int seq_num = _generate_seq_num();

    InitialData* initial_data_ptr = createInitialData(12345678, seq_num, "chmod");

    unsigned char initial_response_buffer[sizeof(InitialResponse)];
    unsigned char chmod_response_buffer[sizeof(ChmodResponse)];

    result = send_to_server(initial_data_ptr, sizeof(InitialData));

    if(result == -1){

        return -1;
    }

    result = receive_from_server(initial_response_buffer, sizeof(InitialResponse));

    if(result == -1){

        return -1;
    }

    InitialResponse* initial_response_ptr = (InitialResponse*)initial_response_buffer;

    if(initial_response_ptr->seq_num != seq_num){

        perror("Serwer obsłużył nieznane żądanie ! \n");
        return -1;

    }

    if(initial_response_ptr->err_flag == -1){

        perror("Błąd autoryzacji");
        return -1;

    }


    seq_num = _generate_seq_num();

    ChmodRequest* chmod_req_ptr = createChmodRequest(12345678, seq_num, pathname, mode);

    result = send_to_server(chmod_req_ptr, sizeof(ChmodRequest));

    if(result == -1){

        return -1;
    }

    result = receive_from_server(chmod_response_buffer, sizeof(ChmodResponse));

    if(result == -1){

        return -1;
    }

    ChmodResponse* chmod_response_ptr = (ChmodResponse*)chmod_response_buffer;

    return chmod_response_ptr->result;

} 

int unlink(const char *pathname){

    long int seq_num = _generate_seq_num();

    int result;

    InitialData* initial_data_ptr = createInitialData(12345678, seq_num, "unlink");

    unsigned char initial_response_buffer[sizeof(InitialResponse)];
    unsigned char unlink_response_buffer[sizeof(UnlinkResponse)];

    result = send_to_server(initial_data_ptr, sizeof(InitialData));

    if(result == -1){

        return -1;
    }

    result = receive_from_server(initial_response_buffer, sizeof(InitialResponse));

    if(result == -1){

        return -1;
    }

    InitialResponse* initial_response_ptr = (InitialResponse*)initial_response_buffer;

    if(initial_response_ptr->seq_num != seq_num){

        perror("Serwer obsłużył nieznane żądanie ! \n");
        return -1;

    }

    if(initial_response_ptr->err_flag == -1){

        perror("Błąd autoryzacji ! \n");
        return -1;
    }

    seq_num = _generate_seq_num();

    UnlinkRequest* unlink_req_ptr = createUnlinkRequest(12345678, seq_num, pathname);

    result = send_to_server(unlink_req_ptr, sizeof(UnlinkRequest));

    if(result == -1){

        return -1;
    }

    result = receive_from_server(unlink_response_buffer, sizeof(UnlinkResponse));

    if(result == -1){

        return -1;
    }

    UnlinkResponse* unlink_response_ptr = (UnlinkResponse*)unlink_response_buffer;

    return unlink_response_ptr->result;
    
} 

int rename(const char *oldpath, const char *newpath){

    if(oldpath == NULL || newpath == NULL){

        return -1;
    }

    long int seq_num = _generate_seq_num();

    int result;

    InitialData* initial_data_ptr = createInitialData(12345678, seq_num, "rename");

    unsigned char initial_response_buffer[sizeof(InitialResponse)];
    unsigned char rename_response_buffer[sizeof(RenameResponse)];

    result = send_to_server(initial_data_ptr, sizeof(InitialData));

    if(result == -1){

        return -1;
    }

    result = receive_from_server(initial_response_buffer, sizeof(InitialResponse));

    if(result == -1){

        return -1;
    }

    InitialResponse* initial_response_ptr = (InitialResponse*)initial_response_buffer;

    if(initial_response_ptr->seq_num != seq_num){

        perror("Serwer obsłużył nieznane żądanie ! \n");
        return -1;

    }

    if(initial_response_ptr->err_flag == -1){

        perror("Błąd autoryzacji ! \n");
        return -1;
    }

    seq_num = _generate_seq_num();

    RenameRequest* rename_req_ptr = createRenameRequest(12345678, seq_num, oldpath, newpath);

    result = send_to_server(rename_req_ptr, sizeof(RenameRequest));

    if(result == -1){

        return -1;
    }

    result = receive_from_server(rename_response_buffer, sizeof(RenameResponse));

    if(result == -1){

        return -1;
    }

    RenameResponse* rename_response_ptr = (RenameResponse*)rename_response_buffer;

    return rename_response_ptr->result;

} 