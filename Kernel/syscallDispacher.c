#include <stdint.h>
#include <stdarg.h>
#include <syscallDispatcher.h>
#include <naiveConsole.h>
#include <stdinout.h>
#include <videoDriver.h>
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
        else if(rax==28){
            int zoom = va_arg(args, int);
            sys_zoom(zoom);
        }
        else if(rax==43){
            int color = va_arg(args, int);
            int x = va_arg(args, int);
            int y = va_arg(args, int);
            sys_draw(color,x,y);
        }
        else if(rax==44){
            int * width = va_arg(args, int *);
            int * height = va_arg(args, int *);
            sys_screenDetails(width,height);
        }
        else if(rax==45){
            int x = va_arg(args, int);
            int y = va_arg(args, int);
            sys_setCursor(x,y);
        }
        else if(rax==46){
            sys_clockTime();
        }
        else if(rax==87){
            uint64_t * milis = va_arg(args, uint64_t *);
            sys_getMilis(milis);
        }
        else if(rax==2){
            char * charac = va_arg(args, char *);
            sys_getcharNL(charac);
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
    else if(fd == STDERR)
        write(buffer, count, 0x00ff0000, 0);
}
void sys_zoom(int zoom){
    if(zoom == 1){
        zoomIn();
    }
    else if(zoom==-1){
        zoomOut();
    }

}
void sys_draw(int color, int x, int y){
    drawPixel(color, x, y);
}

void sys_screenDetails(int * width, int * height){
    getScreenDetails(width,height);
}

void sys_setCursor(int x, int y){
    setCursor(x,y);
}

void sys_clockTime(){
    clockTime();
}

void sys_getMilis(uint64_t * milis){
    *milis=getMS();
}

void sys_getcharNL(char * charac){
    *charac=getcharNonLoop();
}