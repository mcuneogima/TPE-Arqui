#include <stdint.h>
#include <stdarg.h>
#include <syscallDispatcher.h>
#include <naiveConsole.h>

void syscallDispatcher(uint64_t rax, ...){
    va_list args;
    va_start(args,rax);
    switch(rax){
        case 4:
        FDS fd = va_arg(args, FDS);
        const char * buffer = va_arg(args, const char *);
        size_t count = va_arg(args, size_t);
        sys_write(fd, buffer, count);
        break;

    }
    va_end(args);
}
void sys_write(FDS fd, const char * buffer, size_t count){
    switch (fd)
    {
        case STDOUT:

        break;
        case STDERR:

        break;
    }
}