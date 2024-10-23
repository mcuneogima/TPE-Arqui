#include <stdint.h>
#include <stdarg.h>
#include <syscallDispatcher.h>
#include <naiveConsole.h>
#include <stdinout.h>
#include <time.h>

void syscallDispatcher(uint64_t rax, ...){
    va_list args;
    va_start(args,rax);
        if(rax==1){
            FDS fd = va_arg(args, FDS);
        const char * buffer = va_arg(args, const char *);
        size_t count = va_arg(args, size_t);
        size_t color = va_arg(args, size_t);
        size_t background = va_arg(args, size_t);
        sys_write(fd, buffer, count, color, background);
        }
        else if(rax==0){
            FDS fd = va_arg(args,FDS);
        char * buffer = va_arg(args, char *);
        size_t count = va_arg(args, size_t);
        sys_read(fd,buffer,count);
        }
        else if(rax==35){
            int secs = va_arg(args, int);
            sys_sleep(secs);
        }
    va_end(args);
}

void sys_sleep(int secs){
    sleep(secs);
}
void sys_read(FDS fd, char * buffer, size_t count){
    if( fd == STDIN )
        read(buffer,count);    
}
void sys_write(FDS fd, const char * buffer, size_t count, size_t color, size_t background){

    if (fd == STDOUT)
        write(buffer, count, color, background);
    if(fd == STDERR)
        write(buffer, count, 0x00ff0000, 0);
}