#include <stdint.h> 
#include <stdlib.h>

typedef enum{
    STDOUT = 1,
    STDERR
} FDS;


void syscallDispatcher(uint64_t rax, ...);
void  sys_write(FDS fd, const char *buf, size_t count);