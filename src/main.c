#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "error.h"
#define BUFFER_SIZE 4096
#define ARG_MAX_LEN 100
#define TYPE_MODE 0x1
#define FILE_MODE 0x0
void *handler = NULL;

int
load_library(char *libname)
{
    if (handler != NULL)
        dlclose(handler);
    char buff[256] = "./";
    if(libname[0] != '.' || libname[0] != '/')
        strncat(buff,libname,strlen(libname));
    handler = dlopen(buff,RTLD_NOW);
    if(handler == NULL)
        return 1;
    return 0;
}
int
call_method(char *methodname)
{
    void (*func)(void);
    char *error;
    func = dlsym(handler,methodname);
    if ((error = dlerror())!=NULL)
        return 1;
    (*func)();
    return 0;
}
int 
exec_command(char *str)
{
    char arg[ARG_MAX_LEN];
    while((*str) == ' ')str++;
    if(!strlen(str) || *str == '#' || *str == ';')
        return 0;
    if ( sscanf(str,"use %s",arg) == 1) {
        if(load_library(arg))
            exit_error("Load library error\n");

        return 0;
    }
    else if(sscanf(str,"call %s",arg) == 1) {
        if (call_method(arg))
            exit_error("Call method error\n");
        return 0;
    }
    return 1;
}

void 
init_app(FILE *fd,int mode)
{
    char buffer[BUFFER_SIZE];
    char *pos;
    pos = buffer;
    int len;
    if(mode)
        printf("-----> ");
    while(fgets(pos,BUFFER_SIZE,fd) != NULL) {
        len = strlen(pos);
        if (pos[len-1] == '\n') {
            if (pos[len-2] == '\\') {
                pos = &pos[len-2];
                continue;
            }
                
            pos[len-1] = 0;
            if (exec_command(buffer))
                fprintf(stderr,"Syntax error!\n");
            pos = buffer;
            if(mode)
                printf("-----> ");
        }
            
        
    }
    exit(0);
}

int 
main(int argc,char **argv)
{
    if (argc < 2) 
        init_app(stdin,TYPE_MODE);
    FILE *fd;
    fd = fopen(argv[1],"r");
    if (fd == NULL)
        exit_perror(argv[1]);
    init_app(fd,FILE_MODE);
}