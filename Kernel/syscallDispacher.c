#include <stdint.h>
#include <stdarg.h>
#include <syscallDispatcher.h>
#include <naiveConsole.h>
#include <stdinout.h>
#include <time.h>

void syscallDispatcher(uint64_t rax, ...){
    va_list args;
    va_start(args,rax);
    switch(rax){
        case 1:
        FDS fd = va_arg(args, FDS);
        const char * buffer = va_arg(args, const char *);
        size_t count = va_arg(args, size_t);
        size_t color = va_arg(args, size_t);
        sys_write(fd, buffer, count, color);
        break;
        case 0:
        FDS fd = va_arg(args,FDS);
        char * buffer = va_arg(args, char *);
        size_t count = va_arg(args, size_t);
        sys_read(fd,buffer,count);
        break;
        case 35:
        int secs = va_arg(args, int);
        sys_sleep(secs);
        break;

    }
    va_end(args);
}
void sys_sleep(int secs){
    sleep(secs);
}
void sys_read(FDS fd, char * buffer, size_t count){
    switch (fd)
    {
    case STDIN:
        read(buffer,count);
        break;
    
    default:
        break;
    }
}
void sys_write(FDS fd, const char * buffer, size_t count, size_t color){
    switch (fd)
    {
        case STDOUT:
            write(buffer, count, color);
        break;
        case STDERR:
            write(buffer, count, 0x00ff0000);
        break;
    }
}