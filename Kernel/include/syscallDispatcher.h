#include <stdint.h> 
#include <stdlib.h>

typedef enum{
    STDIN = 0,
    STDOUT = 1,
    STDERR = 2
} FDS;


void syscallDispatcher(uint64_t rax, ...);
void  sys_write(FDS fd, const char *buf, size_t count, size_t color);
void sys_read(FDS fd, char * buffer, size_t count);
