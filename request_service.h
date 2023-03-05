#include<stdio.h>
#include<unistd.h>

#ifndef REQUEST_SERVICE_H
#define REQUEST_SERVICE_H

FILE* handle_open_request(const char *pathname, char *mode);

ssize_t handle_read_request(void *buf, size_t count);
ssize_t handle_write_request(void *buf, size_t count);
off_t handle_lseek_request(off_t offset, int whence);

int handle_chmod_request(const char *pathname, mode_t mode);
int handle_unlink_request(const char *pathname);
int handle_rename_request(const char *oldpath, const char *newpath);

#endif