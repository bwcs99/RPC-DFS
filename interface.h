#include<stdio.h>

#ifndef INTERFACE_H
#define INTERFACE_H

static long int _generate_seq_num();

int ropen(const char *pathname, char *mode);

ssize_t rread(void *buf, size_t count, int file_desc);
ssize_t rwrite(void *buf, size_t count, int file_desc);
off_t rlseek(off_t offset, int whence, int file_desc); 

int rchmod(const char *pathname, mode_t mode); 
int unlink(const char *pathname); 
int rename(const char *oldpath, const char *newpath); 

#endif